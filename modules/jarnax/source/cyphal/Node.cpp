#include "core/Status.hpp"
#include "core/units/MicroSeconds.hpp"
#include "core/vsnprint.hpp"

#include <uavcan/diagnostic/Record_1_1.h>
#include "jarnax/cyphal/Interface.hpp"
#include "jarnax/cyphal/Node.hpp"
#include "jarnax/cyphal/Types.hpp"

#include "cmake.hpp"
#include "memory.hpp"
#include "polyfill.hpp"

#include "jarnax/print.hpp"

namespace jarnax {
namespace cyphal {

constexpr static size_t MinimumPublishers{2};     // Heartbeat + Records
constexpr static size_t MinimumSubscribers{1};    // At least one subscriber required
constexpr static size_t MinimumRequests{1};       // At least one request required
constexpr static size_t MinimumResponses{3};      // GetInfo, ExecuteCommand, GetTransportStatistics

static_assert(MaxNumberOfPublishers > MinimumPublishers, "MaxNumberOfPublishers must be greater than MinimumPublishers");
static_assert(MaxNumberOfSubscribers > MinimumSubscribers, "MaxNumberOfSubscribers must be greater than MinimumSubscribers");
static_assert(MaxNumberOfRequests > MinimumRequests, "MaxNumberOfRequests must be greater than MinimumRequests");
static_assert(MaxNumberOfResponses > MinimumResponses, "MaxNumberOfResponses must be greater than MinimumResponses");

Node::Node(jarnax::Timer const& timer, cyphal::Interface& interface, cyphal::UniqueId const& uid)
    : Node(timer, interface, anonymous, uid) {}

Node::Node(jarnax::Timer const& timer, cyphal::Interface& interface, cyphal::NodeId const id, cyphal::UniqueId const& uid)
    : timer_(timer)
    , interface_(interface)
    , id_(id)
    , uid_(uid)
    , health_(Health::Caution)
    , mode_(Mode::Initialization)
    , publishers_()
    , subscribers_()
    , requesters_()
    , responders_()
    , executor_(nullptr)
    , internal_registered_(false)
    , outstanding_command_{false}
    , command_value_{0U}
    , command_parameters_{}
    , command_status_{ExecuteStatus::Success} {}

bool Node::RunOnce(void) {
    core::units::MicroSeconds now = timer_.GetMicroseconds();

    if (not internal_registered_) {
        core::Status status;
        status = Publish(HeartbeatSubjectId, *this, HeartbeatPeriod);    // Example period of 1 second
        if (not status) {
            return false;
        }
        status = Publish(PortListSubjectId, *this, PortListPeriod);    // Example period of 10 second
        if (not status) {
            return false;
        }
        status = Serve(GetInfoServiceId, *this);
        if (not status) {
            return false;
        }
        status = Serve(ExecuteCommandServiceId, *this);
        if (not status) {
            return false;
        }
        status = Serve(GetTransportStatisticsServiceId, *this);
        if (not status) {
            return false;
        }
        internal_registered_ = true;
    }

    // for all responders, check if they need to respond
    for (std::size_t i = 0u; i < responders_.size(); ++i) {
        // is the server valid, has it already responded
        if (responders_[i].server != nullptr and not responders_[i].responded) {
            // is the deadline not yet reached?
            if (now < responders_[i].deadline) {
                SerializedMessage response;
                auto status = responders_[i].server->GetResponse(responders_[i].id, response);
                if (status.IsNotReady()) {
                    continue;    // Skip to the next responder if not ready
                }
                // response should now point to the server's storage
                if (not response.IsEmpty()) {
                    Respond(responders_[i].id, responders_[i].requester, response);
                }
            }
            // if success or error, mark the server as having responded
            responders_[i].responded = true;
            responders_[i].deadline = core::units::MicroSeconds{0u};    // no deadline now
        }
    }

    // Clients make their own requests, we don't query them, we only deliver the response.

    // check the periods of the publishers to know if the message should be published now
    for (std::size_t i = 0u; i < publishers_.size(); ++i) {
        if (publishers_[i].publisher != nullptr) {
            SerializedMessage broadcast;
            // check if the period has expired and call the publisher's OnPublish method
            // release time could be zero, which means we query EVERY cycle.
            if (now >= publishers_[i].release) {
                publishers_[i].publisher->OnPublish(publishers_[i].id, broadcast);
            }
            // the publisher owns the memory associated with the serialized broadcast message
            if (not broadcast.IsEmpty()) {
                publishers_[i].statistics.count++;
                auto status = Publish(publishers_[i].id, broadcast);
                if (status) {
                    publishers_[i].statistics.passed++;
                    // Update the release time for the next period (this may slip but should catch up)
                    if (publishers_[i].release.value() > 0U) {
                        // how much are we over?
                        auto diff = now - publishers_[i].release;
                        // if it's less than the period, we are late so adjust the next release time accordingly
                        if (diff < publishers_[i].period) {
                            // should be back on track
                            publishers_[i].release = now + publishers_[i].period - diff;
                        } else {
                            // we are significantly late, just schedule the next release based on the current time
                            publishers_[i].release = now + publishers_[i].period;
                        }
                    }
                } else {
                    // TODO increment counters?
                    publishers_[i].statistics.failed++;
                }
            }
        }
    }

    // once this returns false, we'll be automatically dismissed from the Service.
    return true;
}

size_t Node::GetActiveSubscribers() const {
    size_t count = 0u;
    for (std::size_t i = 0u; i < subscribers_.size(); ++i) {
        if (subscribers_[i].subscriber != nullptr) {
            ++count;
        }
    }
    return count;
}

size_t Node::GetActivePublishers() const {
    size_t count = 0u;
    for (std::size_t i = 0u; i < publishers_.size(); ++i) {
        if (publishers_[i].publisher != nullptr) {
            ++count;
        }
    }
    return count;
}

size_t Node::GetActiveRequesters() const {
    size_t count = 0u;
    for (std::size_t i = 0u; i < requesters_.size(); ++i) {
        if (requesters_[i].client != nullptr) {
            ++count;
        }
    }
    return count;
}

size_t Node::GetActiveResponders() const {
    size_t count = 0u;
    for (std::size_t i = 0u; i < responders_.size(); ++i) {
        if (responders_[i].server != nullptr) {
            ++count;
        }
    }
    return count;
}

core::Status Node::Subscribe(SubjectId id, Subscriber& subscriber) {
    // Search all subscriber records to find an available slot for this subscription
    for (std::size_t i = 0u; i < subscribers_.size(); ++i) {
        if (subscribers_[i].subscriber == nullptr) {
            subscribers_[i].subscriber = &subscriber;
            subscribers_[i].id = id;
            subscribers_[i].statistics.count = 0u;
            return core::Status{};
        }
    }
    return core::Status{core::Result::NotAvailable, core::Cause::Resource};
}

core::Status Node::Publish(SubjectId id, SerializedMessage msg) {
    // Nothing is registered, just passed down to the interface
    Metadata metadata{
        id_,
        NodeId{0U},    // Broadcast to all nodes
        PortId{id},
        timer_.GetMicroseconds()
    };
    return interface_.Send(metadata, msg);
}

core::Status Node::Publish(SubjectId id, Publisher& publisher) {
    return Publish(id, publisher, core::units::MicroSeconds{0u});
}

core::Status Node::Publish(SubjectId id, Publisher& publisher, core::units::MicroSeconds period) {
    for (std::size_t i = 0u; i < publishers_.size(); ++i) {
        if (publishers_[i].publisher == nullptr) {
            publishers_[i].publisher = &publisher;
            publishers_[i].period = period;
            publishers_[i].id = id;
            publishers_[i].statistics.Reset();
            return core::Status{};
        }
    }
    return core::Status{core::Result::NotAvailable, core::Cause::Resource};
}

core::Status Node::Request(ServiceId id, NodeId recipient, Client& client, SerializedMessage msg) {
    // register for a later response (if not present) and then send if registered
    for (std::size_t i = 0u; i < requesters_.size(); ++i) {
        if (requesters_[i].client == nullptr) {
            requesters_[i].client = &client;
            requesters_[i].id = id;
            requesters_[i].statistics.Reset();
            requesters_[i].deadline = timer_.GetMicroseconds() + ServiceTimeout;
        }
        if (requesters_[i].client == &client and requesters_[i].id == id) {
            requesters_[i].statistics.count++;
            Metadata metadata{
                id_,
                recipient,    // Targeted node
                PortId{id, PortId::Style::Request},
                timer_.GetMicroseconds()
            };
            auto status = interface_.Send(metadata, msg);
            if (status) {
                requesters_[i].statistics.passed++;
            } else {
                requesters_[i].statistics.failed++;
            }
            return status;
        }
    }
    return core::Status{core::Result::NotAvailable, core::Cause::Resource};
}

core::Status Node::Respond(ServiceId id, NodeId recipient, SerializedMessage msg) {
    Metadata metadata{
        id_,
        recipient,    // Targeted node
        PortId{id, PortId::Style::Response},
        timer_.GetMicroseconds()
    };
    return interface_.Send(metadata, msg);
}

core::Status Node::Serve(ServiceId id, Server& server) {
    // the servers should be unique and can't be duplicated per id
    for (std::size_t i = 0u; i < responders_.size(); ++i) {
        if (responders_[i].server == &server && responders_[i].id == id) {
            return core::Status{};
        }
    }
    // not found, so register
    for (std::size_t i = 0u; i < responders_.size(); ++i) {
        if (responders_[i].server == nullptr) {
            responders_[i].server = &server;
            responders_[i].id = id;
            responders_[i].requester = 0U;
            responders_[i].statistics.Reset();
            responders_[i].deadline = core::units::MicroSeconds{0u};    // the time limit is initialized at reception
            return core::Status{};
        }
    }
    return core::Status{core::Result::NotAvailable, core::Cause::Resource};
}

core::Status Node::Dismiss(SubjectId id, Subscriber& subscriber) {
    for (std::size_t i = 0u; i < subscribers_.size(); ++i) {
        if (&subscriber == subscribers_[i].subscriber and id == subscribers_[i].id) {
            subscribers_[i].subscriber = nullptr;
            subscribers_[i].id = 0U;
            subscribers_[i].statistics.Reset();
            return core::Status{};
        }
    }
    return core::Status{core::Result::NotAvailable, core::Cause::Resource};
}

core::Status Node::Dismiss(SubjectId id, Publisher& publisher) {
    for (std::size_t i = 0u; i < publishers_.size(); ++i) {
        if (&publisher == publishers_[i].publisher and id == publishers_[i].id) {
            // clear out the publisher record
            publishers_[i].publisher = nullptr;
            publishers_[i].id = 0U;
            publishers_[i].statistics.Reset();
            publishers_[i].period = core::units::MicroSeconds{0u};
            return core::Status{};
        }
    }
    return core::Status{core::Result::NotAvailable, core::Cause::Resource};
}

core::Status Node::Dismiss(ServiceId id, Client& client) {
    for (std::size_t i = 0u; i < requesters_.size(); ++i) {
        if (&client == requesters_[i].client and id == requesters_[i].id) {
            // clear out the request record
            requesters_[i].client = nullptr;
            requesters_[i].recipient = anonymous;
            requesters_[i].id = 0U;
            requesters_[i].statistics.Reset();
            requesters_[i].deadline = core::units::MicroSeconds{0u};
            return core::Status{};
        }
    }
    return core::Status{core::Result::NotAvailable, core::Cause::Resource};
}

core::Status Node::Dismiss(ServiceId id, Server& server) {
    for (std::size_t i = 0; i < responders_.size(); ++i) {
        if (&server == responders_[i].server and id == responders_[i].id) {
            // clear out the server record
            responders_[i].server = nullptr;
            responders_[i].id = 0U;
            responders_[i].requester = 0U;
            responders_[i].statistics.Reset();
            responders_[i].deadline = core::units::MicroSeconds{0u};
            return core::Status{};
        }
    }
    return core::Status{core::Result::NotAvailable, core::Cause::Resource};
}

void Node::Print(Severity severity, char const* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    core::vsnprint(print_buffer_, sizeof(print_buffer_), fmt, args);
    va_end(args);
    uavcan_diagnostic_Record_1_1 record{};
    uavcan_diagnostic_Record_1_1_initialize_(&record);
    record.timestamp.microsecond = timer_.GetMicroseconds().value();
    record.severity.value = polyfill::to_underlying(severity);
    size_t len = strings::length(print_buffer_);
    if (len > sizeof(record.text.elements)) {
        len = sizeof(record.text.elements);
    }
    memory::copy(record.text.elements, print_buffer_, len);
    record.text.count = len;
    size_t out_len = diagnostic_record_blob_.size();
    auto result = uavcan_diagnostic_Record_1_1_serialize_(&record, diagnostic_record_blob_.data(), &out_len);
    if (result == NUNAVUT_SUCCESS) {
        SerializedMessage msg{diagnostic_record_blob_.data(), out_len};
        auto status = Publish(DiagnosticRecordSubjectId, msg);
        if (not status) {
            diagnostic_statistics_.failed++;
        } else {
            diagnostic_statistics_.passed++;
        }
    } else {
        jarnax::print("Failed to serialize diagnostic record: %d\n", result);
        diagnostic_statistics_.failed++;
    }
}

void Node::OnReceive(Metadata const& metadata, SerializedMessage msg) {
    if (metadata.port_id.type == PortId::Type::Subject) {
        // search for each subscriber of this type
        for (std::size_t i = 0u; i < subscribers_.size(); ++i) {
            if (subscribers_[i].subscriber != nullptr and metadata.port_id.value<SubjectId>() == subscribers_[i].id) {
                // call the subscriber's callback
                subscribers_[i].statistics.count++;
                subscribers_[i].subscriber->OnBroadcast(metadata.port_id.value<SubjectId>(), msg);
                subscribers_[i].statistics.passed++;    // can't fail
                // there can be many subscribers for the same subject
            }
        }
    } else if (metadata.port_id.type == PortId::Type::Service) {
        if (metadata.port_id.style == PortId::Style::Response) {
            for (std::size_t i = 0u; i < requesters_.size(); ++i) {
                if (requesters_[i].client != nullptr and metadata.source == requesters_[i].recipient and
                    metadata.port_id.value<ServiceId>() == requesters_[i].id) {
                    // call the client's callback
                    requesters_[i].statistics.count++;
                    requesters_[i].client->OnResponse(metadata.port_id.value<ServiceId>(), metadata.source, msg);
                    requesters_[i].statistics.passed++;    // can't fail
                    requesters_[i].recipient = anonymous;
                    // do not clear the Service ID!
                    // there can only be one handler of a service call
                    break;
                }
            }
        } else if (metadata.port_id.style == PortId::Style::Request) {
            for (std::size_t i = 0u; i < responders_.size(); ++i) {
                if (responders_[i].server != nullptr and metadata.port_id.value<ServiceId>() == responders_[i].id) {
                    // call the server's callback
                    responders_[i].statistics.count++;
                    responders_[i].server->OnRequest(metadata.port_id.value<ServiceId>(), metadata.source, msg);
                    responders_[i].statistics.passed++;                                     // can't fail
                    responders_[i].requester = metadata.source;                             // remember who
                    responders_[i].deadline = timer_.GetMicroseconds() + ServiceTimeout;    // set the response deadline
                    // there can only be one handler of a service request
                    break;
                }
            }
        }
    }
}

void Node::OnRequest(ServiceId id, NodeId sender, SerializedMessage msg) {
    (void)sender;
    if (id == GetInfoServiceId) {
        // handle the GetInfo request (it's zero size, so there's nothing to do)
    } else if (id == ExecuteCommandServiceId and not outstanding_command_) {
        // handle the ExecuteCommand request
        uavcan_node_ExecuteCommand_Request_1_3 request;
        uavcan_node_ExecuteCommand_Request_1_3_initialize_(&request);
        size_t inout_buffer_size = msg.size();
        auto ret = uavcan_node_ExecuteCommand_Request_1_3_deserialize_(&request, msg.data(), &inout_buffer_size);
        if (ret == NUNAVUT_SUCCESS and inout_buffer_size > 0) {
            outstanding_command_ = true;
            command_value_ = request.command;
            memory::fill<char>(command_parameters_, 0);
            memory::copy<char>(command_parameters_, reinterpret_cast<char const*>(request.parameter.elements), request.parameter.count);
            // fill the difference between the actual parameter count and the fixed size
            if (request.parameter.count < ExecuteCommandRequestCommandStringSize) {
                memory::fill<char>(
                    command_parameters_ + request.parameter.count, 0, ExecuteCommandRequestCommandStringSize - request.parameter.count
                );
            }
            command_status_ = OnCommand(command_value_, command_parameters_);
            if (command_status_ == ExecuteStatus::BadCommand) {
                if (executor_) {
                    command_status_ = OnCommand(command_value_, command_parameters_);
                }
            }
            // the status should be returned from the RunOnce now
        }
    }
}

core::Status Node::GetResponse(ServiceId id, SerializedMessage& msg) {
    if (id == GetInfoServiceId) {
        uavcan_node_GetInfo_Response_1_0 response{};
        // fill in the fields!
        response.protocol_version.major = 1;
        response.protocol_version.minor = 0;    // not yet v1.1!
        response.hardware_version.major = 1;
        response.hardware_version.minor = 0;
        response.software_version.major = cmake::project::version.major;
        response.software_version.minor = cmake::project::version.minor;
        size_t inout_buffer_size = get_info_response_blob_.size();
        auto ret = uavcan_node_GetInfo_Response_1_0_serialize_(&response, get_info_response_blob_.data(), &inout_buffer_size);
        if (ret != NUNAVUT_SUCCESS) {
            return core::Status{core::Result::NotEnough, core::Cause::Resource};
        } else if (ret == NUNAVUT_SUCCESS) {
            msg = SerializedMessage{get_info_response_blob_.data(), inout_buffer_size};
            return core::Status{};
        }
    } else if (id == ExecuteCommandServiceId) {
        if (outstanding_command_) {
            uavcan_node_ExecuteCommand_Response_1_3 response{};

            // find out the status.
            if (command_status_ != ExecuteStatus::BadCommand) {
                command_status_ = GetCommandResult(command_value_, reinterpret_cast<char*>(response.output.elements), response.output.count);
                if (command_status_ == ExecuteStatus::BadCommand and executor_) {
                    command_status_ =
                        executor_->GetCommandResult(command_value_, reinterpret_cast<char*>(response.output.elements), response.output.count);
                }
            }
            response.status = polyfill::to_underlying(command_status_);
            size_t inout_buffer_size = execute_command_response_blob_.size();
            auto ret = uavcan_node_ExecuteCommand_Response_1_3_serialize_(&response, execute_command_response_blob_.data(), &inout_buffer_size);
            if (ret != NUNAVUT_SUCCESS) {
                return core::Status{core::Result::NotEnough, core::Cause::Resource};
            } else if (ret == NUNAVUT_SUCCESS) {
                // update the msg with the response data pointer and size
                msg = SerializedMessage{execute_command_response_blob_.data(), inout_buffer_size};
                outstanding_command_ = false;
                return core::Status{};
            }
        }
    } else if (id == GetTransportStatisticsServiceId) {
        uavcan_node_GetTransportStatistics_Response_0_1 response{};
        TransportStatistics statistics{};
        auto status = interface_.GetStatistics(statistics);
        if (not status) {
            // the transport could not produce statistics; report zeros rather than letting the request time out
            statistics = {};
        }
        // transfer statistics apply to the whole transport
        response.transfer_statistics.num_emitted = statistics.transfer.num_emitted;
        response.transfer_statistics.num_received = statistics.transfer.num_received;
        response.transfer_statistics.num_errored = statistics.transfer.num_errored;
        // per interface statistics
        size_t const count = (statistics.num_interfaces < MaxNetworkInterfaces) ? statistics.num_interfaces : MaxNetworkInterfaces;
        response.network_interface_statistics.count = count;
        for (size_t i = 0U; i < count; ++i) {
            response.network_interface_statistics.elements[i].num_emitted = statistics.network_interfaces[i].num_emitted;
            response.network_interface_statistics.elements[i].num_received = statistics.network_interfaces[i].num_received;
            response.network_interface_statistics.elements[i].num_errored = statistics.network_interfaces[i].num_errored;
        }
        size_t inout_buffer_size = get_transport_statistics_response_blob_.size();
        auto ret =
            uavcan_node_GetTransportStatistics_Response_0_1_serialize_(&response, get_transport_statistics_response_blob_.data(), &inout_buffer_size);
        if (ret != NUNAVUT_SUCCESS) {
            return core::Status{core::Result::NotEnough, core::Cause::Resource};
        } else if (ret == NUNAVUT_SUCCESS) {
            msg = SerializedMessage{get_transport_statistics_response_blob_.data(), inout_buffer_size};
            return core::Status{};
        }
    } else {
        return core::Status{core::Result::NotExpected, core::Cause::Parameter};
    }
    return core::Status{};
}

void Node::OnResponse(ServiceId id, NodeId responder, SerializedMessage msg) {
    (void)responder;
    (void)msg;
    if (id == GetInfoServiceId) {
        // handle the GetInfo response
    } else if (id == ExecuteCommandServiceId) {
        // handle the ExecuteCommand response
    }
}

core::Status Node::OnPublish(SubjectId id, SerializedMessage& msg) {
    if (id == HeartbeatSubjectId) {
        // handle the Heartbeat message
        uavcan_node_Heartbeat_1_0 heartbeat{};
        auto seconds = timer_.GetSeconds();
        heartbeat.uptime = static_cast<uint32_t>(seconds.value());
        heartbeat.health.value = polyfill::to_underlying(health_);
        heartbeat.mode.value = polyfill::to_underlying(mode_);
        heartbeat.vendor_specific_status_code = 0;    // TODO set the actual vendor-specific status code
        size_t inout_buffer_size = heartbeat_blob_.size();
        auto ret = uavcan_node_Heartbeat_1_0_serialize_(&heartbeat, heartbeat_blob_.data(), &inout_buffer_size);
        if (ret == NUNAVUT_SUCCESS) {
            msg = SerializedMessage{heartbeat_blob_.data(), inout_buffer_size};
            return core::Status{};
        }
    } else if (id == PortListSubjectId) {
        // handle the PortList message
        port_list_ = {};

        // Subject lists are tagged unions. Populate the sparse_list form with a valid count and tag.
        port_list_.publishers._tag_ = 1U;
        port_list_.publishers.sparse_list.count = 0U;
        for (size_t i = 0; i < publishers_.count(); ++i) {
            if (publishers_[i].publisher != nullptr) {
                uavcan_node_port_SubjectID_1_0 subject_id{};
                subject_id.value = static_cast<uint16_t>(publishers_[i].id);
                port_list_.publishers.sparse_list.elements[port_list_.publishers.sparse_list.count++] = subject_id;
            }
        }

        port_list_.subscribers._tag_ = 1U;
        port_list_.subscribers.sparse_list.count = 0U;
        for (size_t i = 0; i < subscribers_.count(); ++i) {
            if (subscribers_[i].subscriber != nullptr) {
                uavcan_node_port_SubjectID_1_0 subject_id{};
                subject_id.value = static_cast<uint16_t>(subscribers_[i].id);
                port_list_.subscribers.sparse_list.elements[port_list_.subscribers.sparse_list.count++] = subject_id;
            }
        }

        // Service ID lists are bit-packed masks, so initialize to zero before setting bits.
        memory::fill<uint8_t>(port_list_.clients.mask_bitpacked_, 0U, sizeof(port_list_.clients.mask_bitpacked_));
        for (size_t i = 0; i < requesters_.count(); ++i) {
            if (requesters_[i].client != nullptr) {
                uint16_t const service_id = static_cast<uint16_t>(requesters_[i].id.value);
                size_t const index = static_cast<size_t>(service_id / 8U);
                size_t const bit = static_cast<size_t>(service_id % 8U);
                port_list_.clients.mask_bitpacked_[index] |= static_cast<uint8_t>(1U << bit);
            }
        }

        memory::fill<uint8_t>(port_list_.servers.mask_bitpacked_, 0U, sizeof(port_list_.servers.mask_bitpacked_));
        for (size_t i = 0; i < responders_.count(); ++i) {
            if (responders_[i].server != nullptr) {
                uint16_t const service_id = static_cast<uint16_t>(responders_[i].id.value);
                size_t const index = static_cast<size_t>(service_id / 8U);
                size_t const bit = static_cast<size_t>(service_id % 8U);
                port_list_.servers.mask_bitpacked_[index] |= static_cast<uint8_t>(1U << bit);
            }
        }

        size_t inout_buffer_size = port_list_blob_.size();
        auto ret = uavcan_node_port_List_1_0_serialize_(&port_list_, port_list_blob_.data(), &inout_buffer_size);
        if (ret == NUNAVUT_SUCCESS) {
            msg = SerializedMessage{port_list_blob_.data(), inout_buffer_size};
            return core::Status{};
        }
    } else {
        return core::Status{core::Result::NotExpected, core::Cause::Parameter};
    }
    return core::Status{};
}

void Node::OnBroadcast(SubjectId id, SerializedMessage msg) {
    (void)msg;
    if (id == HeartbeatSubjectId) {
        // handle the Heartbeat broadcast being received
    }
    return;
}

ExecuteStatus Node::OnCommand(uint16_t command, char const parameters[Executor::ParamterSize]) {
    (void)parameters;
    if (command == uavcan_node_ExecuteCommand_Request_1_3_COMMAND_RESTART) {
        // TODO setup the restart to happen in about a second
        return ExecuteStatus::Success;
    } else if (command == uavcan_node_ExecuteCommand_Request_1_3_COMMAND_POWER_OFF) {
        // TODO support power off?
        return ExecuteStatus::BadCommand;
    } else if (command == uavcan_node_ExecuteCommand_Request_1_3_COMMAND_BEGIN_SOFTWARE_UPDATE) {
        // TODO support software update?
        return ExecuteStatus::BadCommand;
    } else if (command == uavcan_node_ExecuteCommand_Request_1_3_COMMAND_FACTORY_RESET) {
        // TODO support factory reset?
        return ExecuteStatus::BadCommand;
    } else if (command == uavcan_node_ExecuteCommand_Request_1_3_COMMAND_EMERGENCY_STOP) {
        // TODO support emergency stop?
        return ExecuteStatus::BadCommand;
    } else if (command == uavcan_node_ExecuteCommand_Request_1_3_COMMAND_STORE_PERSISTENT_STATES) {
        // TODO store data in flash or EEPROM
        return ExecuteStatus::BadCommand;
    } else if (command == uavcan_node_ExecuteCommand_Request_1_3_COMMAND_IDENTIFY) {
        // TODO cause the node to identify itself (e.g., blink an LED)
        return ExecuteStatus::BadCommand;
    }
    return ExecuteStatus::BadCommand;
}

ExecuteStatus Node::GetCommandResult(uint16_t command, char response[Executor::ResponseSize], size_t& out_response_size) {
    memory::fill(response, 0, Executor::ResponseSize);
    out_response_size = 0;
    if (command == uavcan_node_ExecuteCommand_Request_1_3_COMMAND_RESTART) {
        // TODO provide the result for the restart command
        return ExecuteStatus::Success;
    } else if (command == uavcan_node_ExecuteCommand_Request_1_3_COMMAND_POWER_OFF) {
        // TODO provide the result for the power off command
        return ExecuteStatus::BadCommand;
    } else if (command == uavcan_node_ExecuteCommand_Request_1_3_COMMAND_BEGIN_SOFTWARE_UPDATE) {
        // TODO provide the result for the software update command
        return ExecuteStatus::BadCommand;
    } else if (command == uavcan_node_ExecuteCommand_Request_1_3_COMMAND_FACTORY_RESET) {
        // TODO provide the result for the factory reset command
        return ExecuteStatus::BadCommand;
    } else if (command == uavcan_node_ExecuteCommand_Request_1_3_COMMAND_EMERGENCY_STOP) {
        // TODO provide the result for the emergency stop command
        return ExecuteStatus::BadCommand;
    } else if (command == uavcan_node_ExecuteCommand_Request_1_3_COMMAND_STORE_PERSISTENT_STATES) {
        // TODO provide the result for the store persistent states command
        return ExecuteStatus::BadCommand;
    } else if (command == uavcan_node_ExecuteCommand_Request_1_3_COMMAND_IDENTIFY) {
        // TODO provide the result for the identify command
        return ExecuteStatus::BadCommand;
    }
    return ExecuteStatus::BadCommand;
}

}    // namespace cyphal
}    // namespace jarnax

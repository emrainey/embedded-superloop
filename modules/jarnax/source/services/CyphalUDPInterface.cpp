#include "jarnax/services/CyphalUDPInterface.hpp"

#include <cstring>

namespace jarnax {
namespace cyphal {

namespace {

/// All outgoing transfers use Nominal priority; the Interface API does not expose priority yet.
constexpr UdpardPriority DefaultPriority{UdpardPriorityNominal};

constexpr bool SamePort(PortId const& lhs, PortId const& rhs) {
    if (lhs.type != rhs.type) {
        return false;
    }
    bool const same = (lhs.type == PortId::Type::Subject)    //
                          ? (lhs.subject.value == rhs.subject.value)
                          : ((lhs.style == rhs.style) and (lhs.service.value == rhs.service.value));
    return same;
}

}    // namespace

UdpardMicrosecond CyphalUDPInterface::NowUs() const {
    return clock_.GetMicroseconds();
}

core::Status CyphalUDPInterface::MapResult(std::int32_t result) const {
    if (result >= 0) {
        return core::Status{};    // Success
    }
    switch (-result) {
        case UDPARD_ERROR_ARGUMENT: return core::Status{core::Result::InvalidValue, core::Cause::Parameter};
        case UDPARD_ERROR_MEMORY: return core::Status{core::Result::NotEnough, core::Cause::Resource};
        case UDPARD_ERROR_CAPACITY: return core::Status{core::Result::ExceededLimit, core::Cause::Resource};
        case UDPARD_ERROR_ANONYMOUS: return core::Status{core::Result::NotConfigured, core::Cause::Configuration};
        default: return core::Status{core::Result::Failure, core::Cause::Unknown};
    }
}

CyphalUDPInterface::CyphalUDPInterface(O1HeapPool& heap, udp::NodeId node_id, udp::Socket& socket, MicrosecondClock& clock)
    : heap_{heap}
    , socket_{socket}
    , clock_{clock}
    , local_node_id_{node_id}
    , initialized_{false}
    , tx_memory_{}
    , rx_memory_{}
    , tx_{}
    , dispatcher_{}
    , service_endpoint_{}
    , service_group_joined_{false}
    , listener_{nullptr}
    , listener_node_id_{0U} {
    tx_memory_ = heap_.GetMemoryResource();
    rx_memory_ = heap_.GetRxMemoryResources();

    std::int_fast8_t const tx_init = udpardTxInit(&tx_, &local_node_id_, TxQueueCapacity, tx_memory_);
    if (tx_init < 0) {
        return;
    }
    tx_.mtu = UDPARD_MTU_DEFAULT;

    std::int_fast8_t const dispatcher_init = udpardRxRPCDispatcherInit(&dispatcher_, rx_memory_);
    if (dispatcher_init < 0) {
        return;
    }

    UdpardUDPIPEndpoint endpoint{};
    std::int_fast8_t const dispatcher_start = udpardRxRPCDispatcherStart(&dispatcher_, local_node_id_, &endpoint);
    if (dispatcher_start < 0) {
        return;
    }
    service_endpoint_.ip_address = endpoint.ip_address;
    service_endpoint_.udp_port = endpoint.udp_port;

    initialized_ = true;
}

CyphalUDPInterface::~CyphalUDPInterface() {
    for (auto& sub : subscriptions_) {
        if (sub.used) {
            udpardRxSubscriptionFree(&sub.sub);
            sub.used = false;
        }
    }
    for (auto& port : service_ports_) {
        if (port.used) {
            (void)udpardRxRPCDispatcherCancel(&dispatcher_, port.service_id.value, port.is_request);
            port.used = false;
        }
    }
    while (UdpardTxItem const* item = udpardTxPeek(&tx_)) {
        UdpardTxItem* const taken = udpardTxPop(&tx_, item);
        udpardTxFree(tx_memory_, taken);
    }
}

bool CyphalUDPInterface::Execute() {
    if (not initialized_) {
        return true;
    }
    // Drain the prioritized TX queue, highest priority first.
    while (UdpardTxItem const* item = udpardTxPeek(&tx_)) {
        udp::Endpoint const destination{item->destination.ip_address, item->destination.udp_port};
        core::Span<std::uint8_t const> const payload{
            static_cast<std::uint8_t const*>(item->datagram_payload.data), item->datagram_payload.size
        };
        core::Status const status = socket_.Send(destination, payload);
        UdpardTxItem* const taken = udpardTxPop(&tx_, item);
        udpardTxFree(tx_memory_, taken);
        if (not status.IsSuccess()) {
            statistics_.transfer.num_errored++;
            statistics_.network_interfaces[0U].num_errored++;
            break;    // do not spin; retry on the next Execute cycle
        }
        statistics_.transfer.num_emitted++;
        statistics_.network_interfaces[0U].num_emitted++;
    }
    statistics_.num_interfaces = 1U;
    return true;
}

core::Status CyphalUDPInterface::RegisterListener(NodeId id, Listener& listener) {
    listener_ = &listener;
    listener_node_id_ = id;
    return core::Status{};
}

CyphalUDPInterface::Subscription* CyphalUDPInterface::FindSubscription(SubjectId subject) {
    for (auto& sub : subscriptions_) {
        if (sub.used and (sub.subject_id.value == subject.value)) {
            return &sub;
        }
    }
    return nullptr;
}

CyphalUDPInterface::Subscription* CyphalUDPInterface::FindFreeSubscription() {
    for (auto& sub : subscriptions_) {
        if (not sub.used) {
            return &sub;
        }
    }
    return nullptr;
}

CyphalUDPInterface::ServicePort* CyphalUDPInterface::FindServicePort(ServiceId id, bool is_request) {
    for (auto& port : service_ports_) {
        if (port.used and (port.service_id.value == id.value) and (port.is_request == is_request)) {
            return &port;
        }
    }
    return nullptr;
}

CyphalUDPInterface::ServicePort* CyphalUDPInterface::FindFreeServicePort() {
    for (auto& port : service_ports_) {
        if (not port.used) {
            return &port;
        }
    }
    return nullptr;
}

core::Status CyphalUDPInterface::ListenSubject(PortId port_id) {
    SubjectId const subject = port_id.subject;
    if (FindSubscription(subject) != nullptr) {
        return core::Status{core::Result::NotExpected, core::Cause::State};    // already listening
    }
    Subscription* const slot = FindFreeSubscription();
    if (slot == nullptr) {
        return core::Status{core::Result::ExceededLimit, core::Cause::Resource};
    }
    std::int_fast8_t const result =
        udpardRxSubscriptionInit(&slot->sub, static_cast<UdpardPortID>(subject.value), MaxExtent, rx_memory_);
    if (result < 0) {
        return MapResult(result);
    }
    udp::Endpoint const group{slot->sub.udp_ip_endpoint.ip_address, slot->sub.udp_ip_endpoint.udp_port};
    core::Status const join = socket_.Join(group, *this);
    if (not join.IsSuccess()) {
        udpardRxSubscriptionFree(&slot->sub);
        return join;
    }
    slot->used = true;
    slot->subject_id = subject;
    return core::Status{};
}

core::Status CyphalUDPInterface::ListenService(PortId port_id) {
    ServiceId const service = port_id.service;
    bool const is_request = (port_id.style == PortId::Style::Request);
    if (FindServicePort(service, is_request) != nullptr) {
        return core::Status{core::Result::NotExpected, core::Cause::State};    // already listening
    }
    ServicePort* const slot = FindFreeServicePort();
    if (slot == nullptr) {
        return core::Status{core::Result::ExceededLimit, core::Cause::Resource};
    }
    std::int_fast8_t const listen =
        udpardRxRPCDispatcherListen(&dispatcher_, &slot->port, static_cast<UdpardPortID>(service.value), is_request, MaxExtent);
    if (listen < 0) {
        return MapResult(listen);
    }
    if (not service_group_joined_) {
        core::Status const join = socket_.Join(service_endpoint_, *this);
        if (not join.IsSuccess()) {
            (void)udpardRxRPCDispatcherCancel(&dispatcher_, static_cast<UdpardPortID>(service.value), is_request);
            return join;
        }
        service_group_joined_ = true;
    }
    slot->used = true;
    slot->service_id = service;
    slot->is_request = is_request;
    return core::Status{};
}

core::Status CyphalUDPInterface::Listen(PortId port_id) {
    if (not initialized_) {
        return core::Status{core::Result::NotInitialized, core::Cause::Resource};
    }
    if ((port_id.type == PortId::Type::Subject) and (port_id.style == PortId::Style::Neither)) {
        return ListenSubject(port_id);
    } else if ((port_id.type == PortId::Type::Service) and (port_id.style != PortId::Style::Neither)) {
        return ListenService(port_id);
    } else {
        return core::Status{core::Result::InvalidValue, core::Cause::Parameter};
    }
}

core::Status CyphalUDPInterface::RemoveSubject(PortId port_id) {
    SubjectId const subject = port_id.subject;
    Subscription* const slot = FindSubscription(subject);
    if (slot == nullptr) {
        return core::Status{core::Result::NotExpected, core::Cause::State};    // not listening
    }
    udp::Endpoint const group{slot->sub.udp_ip_endpoint.ip_address, slot->sub.udp_ip_endpoint.udp_port};
    udpardRxSubscriptionFree(&slot->sub);
    slot->used = false;
    return socket_.Leave(group);
}

core::Status CyphalUDPInterface::RemoveService(PortId port_id) {
    ServiceId const service = port_id.service;
    bool const is_request = (port_id.style == PortId::Style::Request);
    ServicePort* const slot = FindServicePort(service, is_request);
    if (slot == nullptr) {
        return core::Status{core::Result::NotExpected, core::Cause::State};    // not listening
    }
    std::int_fast8_t const cancel =
        udpardRxRPCDispatcherCancel(&dispatcher_, static_cast<UdpardPortID>(service.value), is_request);
    slot->used = false;
    if (cancel < 0) {
        return MapResult(cancel);
    }
    // Leave the multicast group only when the last service port is gone.
    bool any_left = false;
    for (auto& port : service_ports_) {
        any_left |= port.used;
    }
    if (not any_left and service_group_joined_) {
        service_group_joined_ = false;
        return socket_.Leave(service_endpoint_);
    }
    return core::Status{};
}

core::Status CyphalUDPInterface::Remove(PortId port_id) {
    if (not initialized_) {
        return core::Status{core::Result::NotInitialized, core::Cause::Resource};
    }
    if ((port_id.type == PortId::Type::Subject) and (port_id.style == PortId::Style::Neither)) {
        return RemoveSubject(port_id);
    } else if ((port_id.type == PortId::Type::Service) and (port_id.style != PortId::Style::Neither)) {
        return RemoveService(port_id);
    } else {
        return core::Status{core::Result::InvalidValue, core::Cause::Parameter};
    }
}

bool CyphalUDPInterface::IsListening(PortId port_id) const {
    for (auto const& sub : subscriptions_) {
        if (sub.used and SamePort(port_id, PortId{sub.subject_id})) {
            return true;
        }
    }
    for (auto const& port : service_ports_) {
        if (port.used and SamePort(port_id, PortId{port.service_id, port.is_request ? PortId::Style::Request : PortId::Style::Response})) {
            return true;
        }
    }
    return false;
}

CyphalUDPInterface::TransferIdCounter* CyphalUDPInterface::FindTransferCounter(PortId port_id, udp::NodeId peer) {
    TransferIdCounter* free_slot = nullptr;
    for (auto& counter : transfer_ids_) {
        if (not counter.used) {
            if (free_slot == nullptr) {
                free_slot = &counter;
            }
            continue;
        }
        bool const same_value = (counter.value ==
                                 ((port_id.type == PortId::Type::Subject) ? port_id.subject.value : port_id.service.value));
        bool const same_kind = (counter.type == port_id.type) and (counter.style == port_id.style);
        bool const same_peer = (counter.type == PortId::Type::Subject) or (counter.peer == peer);
        if (same_value and same_kind and same_peer) {
            return &counter;
        }
    }
    if (free_slot != nullptr) {
        free_slot->used = true;
        free_slot->type = port_id.type;
        free_slot->style = port_id.style;
        free_slot->value =
            (port_id.type == PortId::Type::Subject) ? port_id.subject.value : port_id.service.value;
        free_slot->peer = peer;
        free_slot->next = 0U;
    }
    return free_slot;
}

CyphalUDPInterface::PendingRequest* CyphalUDPInterface::RememberRequest(
    ServiceId service_id, udp::NodeId client, UdpardTransferID transfer_id) {
    PendingRequest* slot = const_cast<PendingRequest*>(FindPendingRequest(service_id, client));
    if (slot == nullptr) {
        for (auto& pending : pending_requests_) {
            if (not pending.used) {
                slot = &pending;
                break;
            }
        }
    }
    if (slot == nullptr) {
        // Overwrite the oldest entry (index zero) as a simple eviction policy.
        slot = &pending_requests_[0];
    }
    slot->used = true;
    slot->service_id = service_id;
    slot->client = client;
    slot->transfer_id = transfer_id;
    return slot;
}

CyphalUDPInterface::PendingRequest const* CyphalUDPInterface::FindPendingRequest(
    ServiceId service_id, udp::NodeId client) const {
    for (auto const& pending : pending_requests_) {
        if (pending.used and (pending.service_id.value == service_id.value) and (pending.client == client)) {
            return &pending;
        }
    }
    return nullptr;
}

core::Status CyphalUDPInterface::Send(Metadata& metadata, SerializedMessage msg) {
    if (not initialized_) {
        return core::Status{core::Result::NotInitialized, core::Cause::Resource};
    }
    UdpardPayload const payload{msg.count(), msg.data()};
    UdpardMicrosecond const deadline = NowUs() + BroadcastTimeout.value();

    std::int32_t result = 0;
    if ((metadata.port_id.type == PortId::Type::Subject) and (metadata.port_id.style == PortId::Style::Neither)) {
        TransferIdCounter* const counter = FindTransferCounter(metadata.port_id, udp::anonymous);
        if (counter == nullptr) {
            return core::Status{core::Result::ExceededLimit, core::Cause::Resource};
        }
        UdpardTransferID const transfer_id = counter->next;
        result = udpardTxPublish(
            &tx_, deadline, DefaultPriority, static_cast<UdpardPortID>(metadata.port_id.subject.value), transfer_id, payload,
            this);
        if (result > 0) {
            counter->next = transfer_id + 1U;    // increment only on success per the library contract
        }
    } else if (
        (metadata.port_id.type == PortId::Type::Service) and (metadata.port_id.style == PortId::Style::Request)) {
        ServiceId const service = metadata.port_id.service;
        TransferIdCounter* const counter = FindTransferCounter(metadata.port_id, metadata.recipient);
        if (counter == nullptr) {
            return core::Status{core::Result::ExceededLimit, core::Cause::Resource};
        }
        UdpardTransferID const transfer_id = counter->next;
        result = udpardTxRequest(
            &tx_, deadline, DefaultPriority, static_cast<UdpardPortID>(service.value),
            static_cast<UdpardNodeID>(metadata.recipient), transfer_id, payload, this);
        if (result > 0) {
            counter->next = transfer_id + 1U;
        }
    } else if (
        (metadata.port_id.type == PortId::Type::Service) and (metadata.port_id.style == PortId::Style::Response)) {
        ServiceId const service = metadata.port_id.service;
        PendingRequest const* const pending = FindPendingRequest(service, metadata.recipient);
        if (pending == nullptr) {
            return core::Status{core::Result::NotExpected, core::Cause::State};    // no request to respond to
        }
        result = udpardTxRespond(
            &tx_, deadline, DefaultPriority, static_cast<UdpardPortID>(service.value),
            static_cast<UdpardNodeID>(metadata.recipient), pending->transfer_id, payload, this);
    } else {
        return core::Status{core::Result::InvalidValue, core::Cause::Parameter};
    }

    core::Status const status = MapResult(result);
    if (not status.IsSuccess()) {
        statistics_.transfer.num_errored++;
        statistics_.network_interfaces[0U].num_errored++;
    }
    return status;
}

core::Status CyphalUDPInterface::GetStatistics(TransportStatistics& statistics) {
    statistics = statistics_;
    return core::Status{};
}

void CyphalUDPInterface::DeliverTransfer(UdpardRxTransfer const& transfer, PortId port_id) {
    if (listener_ == nullptr) {
        return;
    }
    // Empty transfers (e.g. GetInfo requests) are valid and delivered as zero-length messages.
    size_t const expected =
        (transfer.payload_size < rx_scratch_.size()) ? transfer.payload_size : rx_scratch_.size();
    if (expected > 0U) {
        size_t const gathered = udpardGather(transfer.payload, expected, rx_scratch_.data());
        if (gathered == 0U) {
            return;
        }
    }
    NodeId const recipient =
        (port_id.type == PortId::Type::Service) ? local_node_id_ : udp::anonymous;
    Metadata const metadata{
        static_cast<NodeId>(transfer.source_node_id), recipient, port_id,
        core::units::MicroSeconds{transfer.timestamp_usec}
    };
    SerializedMessage const msg{rx_scratch_.data(), expected};
    listener_->OnReceive(metadata, msg);
    statistics_.transfer.num_received++;
    statistics_.network_interfaces[0U].num_received++;
}

void CyphalUDPInterface::OnDatagramReceived(udp::Endpoint const& destination, std::uint8_t* data, std::size_t size) {
    if ((not initialized_) or (data == nullptr) or (size == 0U)) {
        return;
    }
    // The library takes ownership of the payload buffer; allocate a copy from the shared heap.
    void* copy = heap_.allocate(size);
    if (copy == nullptr) {
        statistics_.transfer.num_errored++;
        statistics_.network_interfaces[0U].num_errored++;
        return;
    }
    std::memcpy(copy, data, size);
    UdpardMutablePayload const payload{size, copy};

    if (destination == service_endpoint_) {
        UdpardRxRPCTransfer transfer{};
        std::int_fast8_t const result =
            udpardRxRPCDispatcherReceive(&dispatcher_, NowUs(), payload, 0U, nullptr, &transfer);
        if (result > 0) {
            ServiceId const service{static_cast<std::uint16_t>(transfer.service_id)};
            if (transfer.is_request) {
                (void)RememberRequest(
                    service, static_cast<udp::NodeId>(transfer.base.source_node_id), transfer.base.transfer_id);
                DeliverTransfer(
                    transfer.base,
                    PortId{service, PortId::Style::Request});
            } else {
                DeliverTransfer(transfer.base, PortId{service, PortId::Style::Response});
            }
            udpardRxFragmentFree(transfer.base.payload, rx_memory_.fragment, rx_memory_.payload);
        }
    } else {
        Subscription* slot = nullptr;
        for (auto& sub : subscriptions_) {
            if (sub.used                                                                    //
                and (sub.sub.udp_ip_endpoint.ip_address == destination.ip_address)          //
                and (sub.sub.udp_ip_endpoint.udp_port == destination.udp_port)) {
                slot = &sub;
                break;
            }
        }
        if (slot != nullptr) {
            UdpardRxTransfer transfer{};
            std::int_fast8_t const result =
                udpardRxSubscriptionReceive(&slot->sub, NowUs(), payload, 0U, &transfer);
            if (result > 0) {
                DeliverTransfer(transfer, PortId{slot->subject_id});
                udpardRxFragmentFree(transfer.payload, rx_memory_.fragment, rx_memory_.payload);
            }
        } else {
            heap_.deallocate(copy, size);    // nobody is listening on this group
        }
    }
}

}    // namespace cyphal
}    // namespace jarnax

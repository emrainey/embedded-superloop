#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstring>

#include "cmake.hpp"
#include "gtest/Status.hpp"
#include "jarnax/JumpTimer.hpp"
#include "jarnax/cyphal/MockInterface.hpp"
#include "jarnax/cyphal/MockNodeHelpers.hpp"
#include "jarnax/cyphal/Node.hpp"

namespace {

using jarnax::cyphal::ExecuteCommandServiceId;
using jarnax::cyphal::Executor;
using jarnax::cyphal::GetInfoServiceId;
using jarnax::cyphal::GetTransportStatisticsServiceId;
using jarnax::cyphal::HeartbeatSubjectId;
using jarnax::cyphal::MaxExtent;
using jarnax::cyphal::Metadata;
using jarnax::cyphal::MockInterface;
using jarnax::cyphal::Node;
using jarnax::cyphal::NodeId;
using jarnax::cyphal::PortId;
using jarnax::cyphal::SerializedMessage;
using jarnax::cyphal::ServiceId;
using jarnax::cyphal::SubjectId;
using jarnax::cyphal::TransportStatistics;
using jarnax::cyphal::UniqueId;
using ::testing::Return;

core::Status const send_failure{core::Result::Failure, core::Cause::Peripheral};

class TestNode : public Node {
public:
    using Node::Node;

    jarnax::cyphal::ExecuteStatus CallOnCommand(uint16_t command, char const parameters[Executor::ParamterSize]) {
        return OnCommand(command, parameters);
    }

    jarnax::cyphal::ExecuteStatus CallGetCommandResult(uint16_t command, char response[Executor::ResponseSize], size_t& response_size) {
        return GetCommandResult(command, response, response_size);
    }

    core::Status CallOnPublish(SubjectId id, SerializedMessage& msg) { return OnPublish(id, msg); }

    core::Status CallGetResponse(ServiceId id, SerializedMessage& msg) { return GetResponse(id, msg); }

    void CallOnRequest(ServiceId id, NodeId sender, SerializedMessage msg) { OnRequest(id, sender, msg); }
};

class CyphalNodeTest : public ::testing::Test {
public:
    CyphalNodeTest()
        : interface()
        , unique_id{{0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F}}
        , node{timer, interface, NodeId{42U}, unique_id}
        , message{} {}

    virtual ~CyphalNodeTest() = default;

    void SetUp() override {
        unique_id = UniqueId{{0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F}};
        // Any setup code if needed
    }

    void TearDown() override {
        // Any teardown code if needed
    }

protected:
    jarnax::JumpTimer timer;
    MockInterface interface;
    UniqueId unique_id;
    Node node;
    SerializedMessage message;
};

TEST_F(CyphalNodeTest, ConstructorStoresAnonymousNodeIdentity) {
    Node node{timer, interface, NodeId{0u}, unique_id};

    EXPECT_EQ(node.GetId(), NodeId{0U});
    EXPECT_EQ(node.GetUniqueId(), unique_id);
}

TEST_F(CyphalNodeTest, ConstructorStoresNodeIdentity) {
    NodeId const node_id{42U};
    Node node{timer, interface, node_id, unique_id};

    EXPECT_EQ(node.GetId(), node_id);
    EXPECT_EQ(node.GetUniqueId(), unique_id);
}

TEST_F(CyphalNodeTest, RunOnceRemainsActiveAsTimeAdvances) {
    EXPECT_TRUE(node.RunOnce());

    timer.Jump(core::units::MicroSeconds{1000000U});

    EXPECT_TRUE(node.RunOnce());
}

TEST_F(CyphalNodeTest, RunOnceAcceptsPublisherPeriodAfterTimeJump) {
    jarnax::cyphal::mock::MockPublisher publisher;
    EXPECT_STATUS_EQ(node.Publish(SubjectId{17U}, publisher, core::units::MicroSeconds{100U}), core::Result::Success, core::Cause::Unknown);

    timer.Jump(core::units::MicroSeconds{100U});

    EXPECT_TRUE(node.RunOnce());
}

TEST_F(CyphalNodeTest, PublishUsesCurrentTimerForHeartbeatMetadata) {
    timer.Jump(core::units::MicroSeconds{1234U});
    TestNode test_node{timer, interface, NodeId{42U}, unique_id};
    uint8_t buffer[MaxExtent]{};
    SerializedMessage msg{buffer, sizeof(buffer)};

    EXPECT_CALL(interface, Send(testing::_, testing::_))
        .WillOnce(
            testing::DoAll(
                testing::Invoke([&](Metadata& sent, SerializedMessage) {
                    EXPECT_EQ(sent.source, NodeId{42U});
                    EXPECT_EQ(sent.recipient, NodeId{0U});
                    EXPECT_EQ(sent.timestamp.value(), 1234U);
                }),
                Return(core::Status{})
            )
        );

    core::Status const actual = test_node.Publish(SubjectId{17U}, msg);
    ASSERT_STATUS_EQ(actual, core::Result::Success, core::Cause::Unknown);
}

TEST_F(CyphalNodeTest, HeartbeatOnPublishUsesNodeHealthAndModeDefaults) {
    TestNode test_node{timer, interface, NodeId{42U}, unique_id};
    uint8_t buffer[uavcan_node_Heartbeat_1_0_EXTENT_BYTES_];
    SerializedMessage msg{buffer, sizeof(buffer)};

    EXPECT_TRUE(test_node.CallOnPublish(HeartbeatSubjectId, msg).IsSuccess());

    uavcan_node_Heartbeat_1_0 heartbeat{};
    size_t size = msg.size();
    auto ret = uavcan_node_Heartbeat_1_0_deserialize_(&heartbeat, msg.data(), &size);

    ASSERT_EQ(ret, NUNAVUT_SUCCESS);
    EXPECT_EQ(heartbeat.health.value, polyfill::to_underlying(jarnax::cyphal::Health::Caution));
    EXPECT_EQ(heartbeat.mode.value, polyfill::to_underlying(jarnax::cyphal::Mode::Initialization));
}

TEST_F(CyphalNodeTest, GetInfoResponseContainsExpectedProtocolAndVersion) {
    TestNode test_node{timer, interface, NodeId{42U}, unique_id};
    uint8_t buffer[jarnax::cyphal::GetInfoResponseExtent];
    SerializedMessage msg{buffer, sizeof(buffer)};

    EXPECT_TRUE(test_node.CallGetResponse(GetInfoServiceId, msg).IsSuccess());

    uavcan_node_GetInfo_Response_1_0 response{};
    size_t size = msg.size();
    auto ret = uavcan_node_GetInfo_Response_1_0_deserialize_(&response, msg.data(), &size);

    ASSERT_EQ(ret, NUNAVUT_SUCCESS);
    EXPECT_EQ(response.protocol_version.major, 1U);
    EXPECT_EQ(response.protocol_version.minor, 0U);
    EXPECT_EQ(response.hardware_version.major, 1U);
    EXPECT_EQ(response.hardware_version.minor, 0U);
    EXPECT_EQ(response.software_version.major, cmake::project::version.major);
    EXPECT_EQ(response.software_version.minor, cmake::project::version.minor);
}

TEST_F(CyphalNodeTest, GetTransportStatisticsResponseContainsInterfaceStatistics) {
    TestNode test_node{timer, interface, NodeId{42U}, unique_id};
    uint8_t buffer[jarnax::cyphal::GetTransportStatisticsExtent];
    SerializedMessage msg{buffer, sizeof(buffer)};

    TransportStatistics stats;
    stats.transfer.num_emitted = 100U;
    stats.transfer.num_received = 50U;
    stats.transfer.num_errored = 3U;
    stats.num_interfaces = 2U;
    stats.network_interfaces[0].num_emitted = 60U;
    stats.network_interfaces[0].num_received = 30U;
    stats.network_interfaces[0].num_errored = 1U;
    stats.network_interfaces[1].num_emitted = 40U;
    stats.network_interfaces[1].num_received = 20U;
    stats.network_interfaces[1].num_errored = 2U;

    EXPECT_CALL(interface, GetStatistics(testing::_))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(stats), Return(core::Status{})));

    EXPECT_TRUE(test_node.CallGetResponse(GetTransportStatisticsServiceId, msg).IsSuccess());

    uavcan_node_GetTransportStatistics_Response_0_1 response{};
    size_t size = msg.size();
    auto ret = uavcan_node_GetTransportStatistics_Response_0_1_deserialize_(&response, msg.data(), &size);

    ASSERT_EQ(ret, NUNAVUT_SUCCESS);
    EXPECT_EQ(response.transfer_statistics.num_emitted, 100U);
    EXPECT_EQ(response.transfer_statistics.num_received, 50U);
    EXPECT_EQ(response.transfer_statistics.num_errored, 3U);
    EXPECT_EQ(response.network_interface_statistics.count, 2U);
    EXPECT_EQ(response.network_interface_statistics.elements[0].num_emitted, 60U);
    EXPECT_EQ(response.network_interface_statistics.elements[0].num_received, 30U);
    EXPECT_EQ(response.network_interface_statistics.elements[0].num_errored, 1U);
    EXPECT_EQ(response.network_interface_statistics.elements[1].num_emitted, 40U);
    EXPECT_EQ(response.network_interface_statistics.elements[1].num_received, 20U);
    EXPECT_EQ(response.network_interface_statistics.elements[1].num_errored, 2U);
}

TEST_F(CyphalNodeTest, GetTransportStatisticsResponseHandlesNoInterfaces) {
    TestNode test_node{timer, interface, NodeId{42U}, unique_id};
    uint8_t buffer[jarnax::cyphal::GetTransportStatisticsExtent];
    SerializedMessage msg{buffer, sizeof(buffer)};

    EXPECT_CALL(interface, GetStatistics(testing::_)).WillOnce(Return(core::Status{}));

    EXPECT_TRUE(test_node.CallGetResponse(GetTransportStatisticsServiceId, msg).IsSuccess());

    uavcan_node_GetTransportStatistics_Response_0_1 response{};
    size_t size = msg.size();
    auto ret = uavcan_node_GetTransportStatistics_Response_0_1_deserialize_(&response, msg.data(), &size);

    ASSERT_EQ(ret, NUNAVUT_SUCCESS);
    EXPECT_EQ(response.transfer_statistics.num_emitted, 0U);
    EXPECT_EQ(response.transfer_statistics.num_received, 0U);
    EXPECT_EQ(response.transfer_statistics.num_errored, 0U);
    EXPECT_EQ(response.network_interface_statistics.count, 0U);
}

TEST_F(CyphalNodeTest, GetTransportStatisticsResponseReportsZerosWhenInterfaceFails) {
    TestNode test_node{timer, interface, NodeId{42U}, unique_id};
    uint8_t buffer[jarnax::cyphal::GetTransportStatisticsExtent];
    SerializedMessage msg{buffer, sizeof(buffer)};

    EXPECT_CALL(interface, GetStatistics(testing::_)).WillOnce(Return(send_failure));

    EXPECT_TRUE(test_node.CallGetResponse(GetTransportStatisticsServiceId, msg).IsSuccess());

    uavcan_node_GetTransportStatistics_Response_0_1 response{};
    size_t size = msg.size();
    auto ret = uavcan_node_GetTransportStatistics_Response_0_1_deserialize_(&response, msg.data(), &size);

    ASSERT_EQ(ret, NUNAVUT_SUCCESS);
    EXPECT_EQ(response.transfer_statistics.num_emitted, 0U);
    EXPECT_EQ(response.transfer_statistics.num_received, 0U);
    EXPECT_EQ(response.transfer_statistics.num_errored, 0U);
    EXPECT_EQ(response.network_interface_statistics.count, 0U);
}

TEST_F(CyphalNodeTest, ExecuteCommandRoundTripSucceedsForRestart) {
    TestNode test_node{timer, interface, NodeId{42U}, unique_id};
    uavcan_node_ExecuteCommand_Request_1_3 request{};
    uavcan_node_ExecuteCommand_Request_1_3_initialize_(&request);
    request.command = uavcan_node_ExecuteCommand_Request_1_3_COMMAND_RESTART;
    static constexpr char parameter_text[] = "restart";
    request.parameter.count = sizeof(parameter_text) - 1U;
    std::memcpy(request.parameter.elements, parameter_text, request.parameter.count);

    uint8_t request_buffer[uavcan_node_ExecuteCommand_Request_1_3_EXTENT_BYTES_];
    size_t request_size = sizeof(request_buffer);
    auto request_ret = uavcan_node_ExecuteCommand_Request_1_3_serialize_(&request, request_buffer, &request_size);
    ASSERT_EQ(request_ret, NUNAVUT_SUCCESS);

    SerializedMessage request_msg{request_buffer, request_size};
    test_node.CallOnRequest(ExecuteCommandServiceId, NodeId{1U}, request_msg);

    uint8_t response_buffer[uavcan_node_ExecuteCommand_Response_1_3_EXTENT_BYTES_];
    SerializedMessage response_msg{response_buffer, sizeof(response_buffer)};
    EXPECT_TRUE(test_node.CallGetResponse(ExecuteCommandServiceId, response_msg).IsSuccess());

    uavcan_node_ExecuteCommand_Response_1_3 response{};
    size_t response_size = response_msg.size();
    auto response_ret = uavcan_node_ExecuteCommand_Response_1_3_deserialize_(&response, response_msg.data(), &response_size);

    ASSERT_EQ(response_ret, NUNAVUT_SUCCESS);
    EXPECT_EQ(response.status, uavcan_node_ExecuteCommand_Response_1_3_STATUS_SUCCESS);
}

TEST_F(CyphalNodeTest, RestartCommandIsAccepted) {
    char const parameters[Executor::ParamterSize]{};

    EXPECT_EQ(
        (TestNode{timer, interface, NodeId{42U}, unique_id}.CallOnCommand(uavcan_node_ExecuteCommand_Request_1_3_COMMAND_RESTART, parameters)),
        jarnax::cyphal::ExecuteStatus::Success
    );
}

TEST_F(CyphalNodeTest, UnsupportedCommandsAreRejected) {
    char const parameters[Executor::ParamterSize]{};
    TestNode test_node{timer, interface, NodeId{42U}, unique_id};
    uint16_t const commands[] = {
        uavcan_node_ExecuteCommand_Request_1_3_COMMAND_POWER_OFF,
        uavcan_node_ExecuteCommand_Request_1_3_COMMAND_BEGIN_SOFTWARE_UPDATE,
        uavcan_node_ExecuteCommand_Request_1_3_COMMAND_FACTORY_RESET,
        uavcan_node_ExecuteCommand_Request_1_3_COMMAND_EMERGENCY_STOP,
        uavcan_node_ExecuteCommand_Request_1_3_COMMAND_STORE_PERSISTENT_STATES,
        uavcan_node_ExecuteCommand_Request_1_3_COMMAND_IDENTIFY,
        0x1234U,
    };

    for (uint16_t const command : commands) {
        EXPECT_EQ(test_node.CallOnCommand(command, parameters), jarnax::cyphal::ExecuteStatus::BadCommand);
    }
}

TEST_F(CyphalNodeTest, RestartCommandResultClearsResponse) {
    char response[Executor::ResponseSize];
    for (char& value : response) {
        value = static_cast<char>(0xA5);
    }
    size_t response_size = sizeof(response);
    TestNode test_node{timer, interface, NodeId{42U}, unique_id};

    EXPECT_EQ(
        test_node.CallGetCommandResult(uavcan_node_ExecuteCommand_Request_1_3_COMMAND_RESTART, response, response_size),
        jarnax::cyphal::ExecuteStatus::Success
    );
    EXPECT_EQ(response_size, 0U);
    for (char const value : response) {
        EXPECT_EQ(value, 0);
    }
}

TEST_F(CyphalNodeTest, UnsupportedCommandResultsAreRejectedAndCleared) {
    char response[Executor::ResponseSize];
    for (char& value : response) {
        value = static_cast<char>(0xA5);
    }
    size_t response_size = sizeof(response);
    TestNode test_node{timer, interface, NodeId{42U}, unique_id};

    EXPECT_EQ(test_node.CallGetCommandResult(0x1234U, response, response_size), jarnax::cyphal::ExecuteStatus::BadCommand);
    EXPECT_EQ(response_size, 0U);
    for (char const value : response) {
        EXPECT_EQ(value, 0);
    }
}

TEST_F(CyphalNodeTest, PublishSendsBroadcastSubject) {
    SubjectId const subject_id{17U};
    core::Status const expected{core::Result::Success, core::Cause::State};
    EXPECT_CALL(interface, Send(testing::_, testing::_))
        .WillOnce(
            testing::DoAll(
                testing::Invoke([&](Metadata& sent, SerializedMessage) {
                    EXPECT_EQ(sent.source, NodeId{42U});
                    EXPECT_EQ(sent.recipient, NodeId{0U});
                    EXPECT_EQ(sent.port_id.type, PortId::Type::Subject);
                    EXPECT_EQ(sent.port_id.style, PortId::Style::Neither);
                    EXPECT_EQ(sent.port_id.value<SubjectId>(), subject_id);
                }),
                Return(expected)
            )
        );

    core::Status const actual = node.Publish(subject_id, message);

    ASSERT_STATUS_EQ(actual, core::Result::Success, core::Cause::State);
}

TEST_F(CyphalNodeTest, RequestSendsTargetedServiceRequest) {
    ServiceId const service_id{23U};
    NodeId const recipient{9U};
    Node node{timer, interface, NodeId{7U}, unique_id};
    jarnax::cyphal::mock::MockClient client{};
    EXPECT_CALL(interface, Send(testing::_, testing::_))
        .WillOnce(
            testing::DoAll(
                testing::Invoke([&](Metadata& sent, SerializedMessage) {
                    EXPECT_EQ(sent.source, NodeId{7U});
                    EXPECT_EQ(sent.recipient, recipient);
                    EXPECT_EQ(sent.port_id.type, PortId::Type::Service);
                    EXPECT_EQ(sent.port_id.style, PortId::Style::Request);
                    EXPECT_EQ(sent.port_id.value<ServiceId>(), service_id);
                }),
                Return(core::Status{})
            )
        );
    core::Status const actual = node.Request(service_id, recipient, client, message);

    ASSERT_STATUS_EQ(actual, core::Result::Success, core::Cause::Unknown);
}

TEST_F(CyphalNodeTest, RespondSendsTargetedServiceResponse) {
    ServiceId const service_id{23U};
    NodeId const recipient{9U};
    Node node{timer, interface, NodeId{7U}, unique_id};
    EXPECT_CALL(interface, Send(testing::_, testing::_))
        .WillOnce(
            testing::DoAll(
                testing::Invoke([&](Metadata& sent, SerializedMessage) {
                    EXPECT_EQ(sent.source, NodeId{7U});
                    EXPECT_EQ(sent.recipient, recipient);
                    EXPECT_EQ(sent.port_id.type, PortId::Type::Service);
                    EXPECT_EQ(sent.port_id.style, PortId::Style::Response);
                    EXPECT_EQ(sent.port_id.value<ServiceId>(), service_id);
                }),
                Return(core::Status{})
            )
        );

    core::Status const actual = node.Respond(service_id, recipient, message);

    ASSERT_STATUS_EQ(actual, core::Result::Success, core::Cause::Unknown);
}

TEST_F(CyphalNodeTest, SubscribeFailsWhenAllSlotsAreUsed) {
    jarnax::cyphal::mock::MockSubscriber subscribers[jarnax::cyphal::MaxNumberOfSubscribers];
    for (std::size_t i = 0U; i < jarnax::cyphal::MaxNumberOfSubscribers; ++i) {
        core::Status const status = node.Subscribe(SubjectId{static_cast<uint16_t>(i)}, subscribers[i]);
        ASSERT_TRUE(status.IsSuccess()) << "subscription slot " << i;
    }

    jarnax::cyphal::mock::MockSubscriber extra;
    ASSERT_STATUS_EQ(
        node.Subscribe(SubjectId{static_cast<uint16_t>(jarnax::cyphal::MaxNumberOfSubscribers)}, extra),
        core::Result::NotAvailable,
        core::Cause::Resource
    );
}

TEST_F(CyphalNodeTest, PublishRegistrationFailsWhenAllSlotsAreUsed) {
    jarnax::cyphal::mock::MockPublisher publishers[jarnax::cyphal::MaxNumberOfPublishers];
    for (std::size_t i = 0U; i < jarnax::cyphal::MaxNumberOfPublishers; ++i) {
        core::Status const status = node.Publish(SubjectId{static_cast<uint16_t>(i)}, publishers[i]);
        ASSERT_TRUE(status.IsSuccess()) << "publisher slot " << i;
    }

    jarnax::cyphal::mock::MockPublisher extra;
    ASSERT_STATUS_EQ(
        node.Publish(SubjectId{static_cast<uint16_t>(jarnax::cyphal::MaxNumberOfPublishers)}, extra),
        core::Result::NotAvailable,
        core::Cause::Resource
    );
}

TEST_F(CyphalNodeTest, RequestFailsWhenAllSlotsAreUsed) {
    EXPECT_CALL(interface, Send(testing::_, testing::_)).WillRepeatedly(Return(core::Status{}));
    jarnax::cyphal::mock::MockClient clients[jarnax::cyphal::MaxNumberOfRequests];
    for (std::size_t i = 0U; i < jarnax::cyphal::MaxNumberOfRequests; ++i) {
        ASSERT_STATUS_EQ(
            node.Request(ServiceId{static_cast<uint16_t>(i)}, NodeId{static_cast<uint16_t>(i)}, clients[i], message),
            core::Result::Success,
            core::Cause::Unknown
        );
    }

    jarnax::cyphal::mock::MockClient extra;
    ASSERT_STATUS_EQ(
        node.Request(ServiceId{static_cast<uint16_t>(jarnax::cyphal::MaxNumberOfRequests)}, NodeId{1U}, extra, message),
        core::Result::NotAvailable,
        core::Cause::Resource
    );
}

TEST_F(CyphalNodeTest, ServeFailsWhenAllSlotsAreUsed) {
    jarnax::cyphal::mock::MockServer servers[jarnax::cyphal::MaxNumberOfResponses];
    for (std::size_t i = 0U; i < jarnax::cyphal::MaxNumberOfResponses; ++i) {
        ASSERT_STATUS_EQ(node.Serve(ServiceId{static_cast<uint16_t>(i)}, servers[i]), core::Result::Success, core::Cause::Unknown);
    }

    jarnax::cyphal::mock::MockServer extra;
    ASSERT_STATUS_EQ(
        node.Serve(ServiceId{static_cast<uint16_t>(jarnax::cyphal::MaxNumberOfResponses)}, extra), core::Result::NotAvailable, core::Cause::Resource
    );
}

TEST_F(CyphalNodeTest, PublishReturnsInterfaceFailure) {
    EXPECT_CALL(interface, Send(testing::_, testing::_)).WillOnce(Return(send_failure));

    core::Status const actual = node.Publish(SubjectId{17U}, message);

    ASSERT_STATUS_EQ(actual, core::Result::Failure, core::Cause::Peripheral);
}

TEST_F(CyphalNodeTest, RequestReturnsInterfaceFailure) {
    EXPECT_CALL(interface, Send(testing::_, testing::_)).WillOnce(Return(send_failure));
    jarnax::cyphal::mock::MockClient client;

    core::Status const actual = node.Request(ServiceId{23U}, NodeId{9U}, client, message);

    ASSERT_STATUS_EQ(actual, core::Result::Failure, core::Cause::Peripheral);
}

TEST_F(CyphalNodeTest, RespondReturnsInterfaceFailure) {
    EXPECT_CALL(interface, Send(testing::_, testing::_)).WillOnce(Return(send_failure));

    core::Status const actual = node.Respond(ServiceId{23U}, NodeId{9U}, message);

    ASSERT_STATUS_EQ(actual, core::Result::Failure, core::Cause::Peripheral);
}

TEST_F(CyphalNodeTest, DismissSubscriberFailsWhenNotRegistered) {
    jarnax::cyphal::mock::MockSubscriber subscriber;

    ASSERT_STATUS_EQ(node.Dismiss(SubjectId{17U}, subscriber), core::Result::NotAvailable, core::Cause::Resource);
}

TEST_F(CyphalNodeTest, DismissPublisherFailsWhenNotRegistered) {
    jarnax::cyphal::mock::MockPublisher publisher;

    ASSERT_STATUS_EQ(node.Dismiss(SubjectId{17U}, publisher), core::Result::NotAvailable, core::Cause::Resource);
}

TEST_F(CyphalNodeTest, DismissClientFailsWhenNotRegistered) {
    jarnax::cyphal::mock::MockClient client;

    ASSERT_STATUS_EQ(node.Dismiss(ServiceId{23U}, client), core::Result::NotAvailable, core::Cause::Resource);
}

TEST_F(CyphalNodeTest, DismissServerFailsWhenNotRegistered) {
    jarnax::cyphal::mock::MockServer server;

    ASSERT_STATUS_EQ(node.Dismiss(ServiceId{23U}, server), core::Result::NotAvailable, core::Cause::Resource);
}

}    // namespace

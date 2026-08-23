#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" {
#include "udpard.h"
}

#include "core/units/MicroSeconds.hpp"
#include "jarnax/cyphal/O1HeapPool.hpp"
#include "jarnax/services/CyphalUDPInterface.hpp"
#include "jarnax/services/MockUDPSocket.hpp"

namespace {

using namespace ::testing;    // NOLINT(google-build-using-namespace)
using jarnax::cyphal::CyphalUDPInterface;
using jarnax::cyphal::GetInfoServiceId;
using jarnax::cyphal::Interface;
using jarnax::cyphal::Metadata;
using jarnax::cyphal::NodeId;
using jarnax::cyphal::PortId;
using jarnax::cyphal::SerializedMessage;
using jarnax::cyphal::ServiceId;
using jarnax::cyphal::SubjectId;
using jarnax::cyphal::udp::Endpoint;
using jarnax::cyphal::udp::MockSocket;

constexpr std::uint16_t LocalNodeId{42U};
constexpr std::uint16_t RemoteNodeId{100U};
constexpr SubjectId TestSubject{1234U};

/// A deterministic microsecond clock for deadline and timestamp control.
class FakeClock final : public jarnax::cyphal::MicrosecondClock {
public:
    std::uint64_t GetMicroseconds(void) const override { return now_us_; }

    void Set(std::uint64_t microseconds) { now_us_ = microseconds; }

private:
    std::uint64_t now_us_{0U};
};

/// Captures transfers delivered by the interface.
class TestListener final : public Interface::Listener {
public:
    void OnReceive(Metadata const& metadata, SerializedMessage msg) override {
        count++;
        last_source = metadata.source;
        last_recipient = metadata.recipient;
        last_type = metadata.port_id.type;
        last_style = metadata.port_id.style;
        if (metadata.port_id.type == PortId::Type::Subject) {
            last_subject = metadata.port_id.subject.value;
            last_service = 0U;
        } else {
            last_subject = 0U;
            last_service = metadata.port_id.service.value;
        }
        last_timestamp = metadata.timestamp;
        data.assign(msg.data(), msg.data() + msg.count());
    }

    size_t count{0U};
    NodeId last_source{0U};
    NodeId last_recipient{0U};
    PortId::Type last_type{PortId::Type::Subject};
    PortId::Style last_style{PortId::Style::Neither};
    std::uint16_t last_subject{0U};
    std::uint16_t last_service{0U};
    core::units::MicroSeconds last_timestamp{0ULL};
    std::vector<std::uint8_t> data;
};

/// Produces valid Cyphal/UDP datagrams with libudpard so that RX paths can be
/// exercised without hand-building wire formats.
class DatagramProducer final {
public:
    explicit DatagramProducer(jarnax::cyphal::O1HeapPool& heap)
        : memory_{heap.GetMemoryResource()}
        , node_id_{RemoteNodeId} {
        EXPECT_EQ(udpardTxInit(&tx_, &node_id_, 8U, memory_), 0);
        tx_.mtu = UDPARD_MTU_DEFAULT;
    }

    ~DatagramProducer() {
        while (UdpardTxItem const* item = udpardTxPeek(&tx_)) {
            UdpardTxItem* const taken = udpardTxPop(&tx_, item);
            udpardTxFree(memory_, taken);
        }
    }

    /// Publishes a message on a subject; returns the datagram to feed into the interface.
    bool Publish(std::uint16_t subject_id, UdpardTransferID transfer_id, std::vector<std::uint8_t> const& message) {
        UdpardPayload const payload{message.size(), message.data()};
        std::int32_t const result =
            udpardTxPublish(&tx_, 1000000ULL, UdpardPriorityNominal, subject_id, transfer_id, payload, nullptr);
        return result > 0;
    }

    /// Sends an RPC request to the given server node.
    bool Request(std::uint16_t service_id, std::uint16_t server_node, UdpardTransferID transfer_id) {
        UdpardPayload const payload{0U, nullptr};
        std::int32_t const result = udpardTxRequest(
            &tx_, 1000000ULL, UdpardPriorityNominal, service_id, static_cast<UdpardNodeID>(server_node), transfer_id,
            payload, nullptr);
        return result > 0;
    }

    /// Sends an RPC response to the given client node.
    bool Respond(std::uint16_t service_id, std::uint16_t client_node, UdpardTransferID transfer_id,
                 std::vector<std::uint8_t> const& message) {
        UdpardPayload const payload{message.size(), message.data()};
        std::int32_t const result = udpardTxRespond(
            &tx_, 1000000ULL, UdpardPriorityNominal, service_id, static_cast<UdpardNodeID>(client_node), transfer_id,
            payload, nullptr);
        return result > 0;
    }

    /// Takes the next queued datagram out of the producer.
    bool Take(Endpoint& destination, std::vector<std::uint8_t>& payload) {
        UdpardTxItem const* item = udpardTxPeek(&tx_);
        if (item == nullptr) {
            return false;
        }
        destination.ip_address = item->destination.ip_address;
        destination.udp_port = item->destination.udp_port;
        auto const* data = static_cast<std::uint8_t const*>(item->datagram_payload.data);
        payload.assign(data, data + item->datagram_payload.size);
        UdpardTxItem* const taken = udpardTxPop(&tx_, item);
        udpardTxFree(memory_, taken);
        return true;
    }

private:
    UdpardMemoryResource memory_;
    UdpardNodeID node_id_;
    UdpardTx tx_{};
};

class CyphalUDPInterfaceTest : public Test {
protected:
    void SetUp() override {
        interface_ = std::make_unique<CyphalUDPInterface>(heap_, static_cast<NodeId>(LocalNodeId), socket_, clock_);
        ASSERT_TRUE(interface_->IsInitialized());
    }

    jarnax::cyphal::O1HeapPool& heap_{jarnax::cyphal::O1HeapPool::Instance()};
    NiceMock<MockSocket> socket_{};
    FakeClock clock_;
    TestListener listener_;
    std::unique_ptr<CyphalUDPInterface> interface_;
};

TEST_F(CyphalUDPInterfaceTest, Empty) {
    ASSERT_NE(interface_, nullptr);
}

TEST_F(CyphalUDPInterfaceTest, RegisterListenerSucceedsAndReplaces) {
    EXPECT_TRUE(interface_->RegisterListener(LocalNodeId, listener_).IsSuccess());
    TestListener second{};
    EXPECT_TRUE(interface_->RegisterListener(LocalNodeId, second).IsSuccess());
}

TEST_F(CyphalUDPInterfaceTest, ListenSubjectJoinsMulticastGroup) {
    Endpoint joined{};
    EXPECT_CALL(socket_, Join(_, _))
        .WillOnce(DoAll(SaveArg<0>(&joined), Return(core::Status{})))
        .WillRepeatedly(Return(core::Status{}));

    EXPECT_TRUE(interface_->Listen(PortId{TestSubject}).IsSuccess());
    EXPECT_TRUE(interface_->IsListening(PortId{TestSubject}));
    EXPECT_NE(joined.udp_port, 0U);    // derived from the subject by libudpard

    // Duplicate subscription is rejected
    EXPECT_EQ(
        interface_->Listen(PortId{TestSubject}).GetResult(), core::Result::NotExpected);

    // Removal leaves the group
    EXPECT_CALL(socket_, Leave(_)).WillOnce(Return(core::Status{}));
    EXPECT_TRUE(interface_->Remove(PortId{TestSubject}).IsSuccess());
    EXPECT_FALSE(interface_->IsListening(PortId{TestSubject}));

    // Removing again fails
    EXPECT_EQ(interface_->Remove(PortId{TestSubject}).GetResult(), core::Result::NotExpected);

    // Verify expectations at this checkpoint
    Mock::VerifyAndClearExpectations(&socket_);
}

TEST_F(CyphalUDPInterfaceTest, ListenServicePortsJoinServiceGroupOnce) {
    Endpoint service_endpoint{};
    EXPECT_CALL(socket_, Join(_, _))
        .Times(1)
        .WillOnce([&service_endpoint](Endpoint const& endpoint, jarnax::cyphal::udp::DatagramHandler&) {
            service_endpoint = endpoint;
            return core::Status{};
        });

    auto const request = PortId{GetInfoServiceId, PortId::Style::Request};
    auto const response = PortId{GetInfoServiceId, PortId::Style::Response};
    // Both ports share the node's single RPC multicast group; only one Join is issued.
    EXPECT_TRUE(interface_->Listen(request).IsSuccess());
    EXPECT_TRUE(interface_->Listen(response).IsSuccess());
    EXPECT_TRUE(interface_->IsListening(request));
    EXPECT_TRUE(interface_->IsListening(response));
    EXPECT_NE(service_endpoint.udp_port, 0U);    // derived from the local node-ID by libudpard

    // Duplicates are rejected
    EXPECT_EQ(interface_->Listen(request).GetResult(), core::Result::NotExpected);
    EXPECT_EQ(interface_->Listen(response).GetResult(), core::Result::NotExpected);

    EXPECT_CALL(socket_, Leave(_)).WillOnce(Return(core::Status{}));
    EXPECT_TRUE(interface_->Remove(response).IsSuccess());     // group still needed by request port
    EXPECT_TRUE(interface_->Remove(request).IsSuccess());      // last port leaves the group
    EXPECT_FALSE(interface_->IsListening(request));
    EXPECT_FALSE(interface_->IsListening(response));

    Mock::VerifyAndClearExpectations(&socket_);
}

TEST_F(CyphalUDPInterfaceTest, ListenRejectsInvalidPorts) {
    // A service port explicitly styled as Neither is invalid
    EXPECT_EQ(
        interface_->Listen(PortId{GetInfoServiceId, PortId::Style::Neither}).GetResult(), core::Result::InvalidValue);
}

TEST_F(CyphalUDPInterfaceTest, ListenFailsWhenSubscriptionsExhausted) {
    ON_CALL(socket_, Join(_, _)).WillByDefault(Return(core::Status{}));
    for (std::size_t i = 0U; i < CyphalUDPInterface::MaxSubscriptions; ++i) {
        EXPECT_TRUE(interface_->Listen(PortId{SubjectId{static_cast<std::uint16_t>(100U + i)}}).IsSuccess());
    }
    EXPECT_EQ(
        interface_->Listen(PortId{SubjectId{static_cast<std::uint16_t>(200U)}}).GetResult(),
        core::Result::ExceededLimit);
}

TEST_F(CyphalUDPInterfaceTest, SendPublishesToSubjectMulticastGroup) {
    ON_CALL(socket_, Join(_, _)).WillByDefault(Return(core::Status{}));
    EXPECT_TRUE(interface_->Listen(PortId{TestSubject}).IsSuccess());

    std::vector<std::uint8_t> message{1U, 2U, 3U, 4U};
    Metadata metadata{LocalNodeId, jarnax::cyphal::udp::anonymous, PortId{TestSubject},
                      core::units::MicroSeconds{0ULL}};
    EXPECT_TRUE(interface_->Send(metadata, SerializedMessage{message.data(), message.size()}).IsSuccess());

    // Drain: exactly one datagram goes out on the subject multicast group
    Endpoint sent_to{};
    std::size_t payload_size = 0U;
    EXPECT_CALL(socket_, Send(_, _))
        .WillOnce([&sent_to, &payload_size](Endpoint const& destination, core::Span<std::uint8_t const> payload) {
            sent_to = destination;
            payload_size = payload.count();
            return core::Status{};
        });
    EXPECT_TRUE(interface_->Execute());

    EXPECT_EQ(sent_to.udp_port, 9382U);    // the Cyphal/UDP well-known port
    EXPECT_GT(payload_size, message.size());    // header plus CRC are added

    jarnax::cyphal::TransportStatistics statistics{};
    EXPECT_TRUE(interface_->GetStatistics(statistics).IsSuccess());
    EXPECT_EQ(statistics.num_interfaces, 1U);
    EXPECT_EQ(statistics.transfer.num_emitted, 1U);
    EXPECT_EQ(statistics.network_interfaces[0U].num_emitted, 1U);

    Mock::VerifyAndClearExpectations(&socket_);
}

TEST_F(CyphalUDPInterfaceTest, ExecuteReportsTransmitErrors) {
    ON_CALL(socket_, Join(_, _)).WillByDefault(Return(core::Status{}));
    EXPECT_TRUE(interface_->Listen(PortId{TestSubject}).IsSuccess());

    std::vector<std::uint8_t> message{1U};
    Metadata metadata{LocalNodeId, jarnax::cyphal::udp::anonymous, PortId{TestSubject},
                      core::units::MicroSeconds{0ULL}};
    EXPECT_TRUE(interface_->Send(metadata, SerializedMessage{message.data(), message.size()}).IsSuccess());

    EXPECT_CALL(socket_, Send(_, _)).WillOnce(Return(core::Status{core::Result::Failure, core::Cause::Peripheral}));
    EXPECT_TRUE(interface_->Execute());

    jarnax::cyphal::TransportStatistics statistics{};
    EXPECT_TRUE(interface_->GetStatistics(statistics).IsSuccess());
    EXPECT_EQ(statistics.transfer.num_emitted, 0U);
    EXPECT_EQ(statistics.transfer.num_errored, 1U);

    Mock::VerifyAndClearExpectations(&socket_);
}

TEST_F(CyphalUDPInterfaceTest, ReceiveDeliversSubjectTransferToListener) {
    ON_CALL(socket_, Join(_, _)).WillByDefault(Return(core::Status{}));
    EXPECT_TRUE(interface_->Listen(PortId{TestSubject}).IsSuccess());
    EXPECT_TRUE(interface_->RegisterListener(LocalNodeId, listener_).IsSuccess());

    // Produce a valid single-frame transfer from remote node 42... er, RemoteNodeId.
    DatagramProducer producer{heap_};
    std::vector<std::uint8_t> const message{9U, 8U, 7U};
    ASSERT_TRUE(producer.Publish(TestSubject.value, 7U, message));

    Endpoint from{};
    std::vector<std::uint8_t> datagram{};
    ASSERT_TRUE(producer.Take(from, datagram));

    clock_.Set(5000000ULL);    // 5 seconds since boot
    interface_->OnDatagramReceived(from, datagram.data(), datagram.size());

    EXPECT_EQ(listener_.count, 1U);
    EXPECT_EQ(listener_.last_source, RemoteNodeId);
    EXPECT_EQ(listener_.last_type, PortId::Type::Subject);
    EXPECT_EQ(listener_.last_subject, TestSubject.value);
    EXPECT_EQ(listener_.data, message);
    EXPECT_GE(listener_.last_timestamp.value(), 5000000ULL);    // timestamp is in microseconds

    jarnax::cyphal::TransportStatistics statistics{};
    EXPECT_TRUE(interface_->GetStatistics(statistics).IsSuccess());
    EXPECT_EQ(statistics.transfer.num_received, 1U);
}

TEST_F(CyphalUDPInterfaceTest, ReceiveIgnoresUnknownGroupsAndBadDatagrams) {
    ON_CALL(socket_, Join(_, _)).WillByDefault(Return(core::Status{}));
    EXPECT_TRUE(interface_->Listen(PortId{TestSubject}).IsSuccess());
    EXPECT_TRUE(interface_->RegisterListener(LocalNodeId, listener_).IsSuccess());

    // A valid datagram for a group nobody subscribes to is dropped without delivery.
    DatagramProducer producer{heap_};
    std::vector<std::uint8_t> const message{1U, 2U};
    ASSERT_TRUE(producer.Publish(4000U, 1U, message));    // a different, valid subject
    Endpoint unknown_group{};
    std::vector<std::uint8_t> datagram{};
    ASSERT_TRUE(producer.Take(unknown_group, datagram));
    interface_->OnDatagramReceived(unknown_group, datagram.data(), datagram.size());
    EXPECT_EQ(listener_.count, 0U);

    // A malformed (all zero) datagram on the subscribed group is discarded by libudpard.
    std::uint8_t junk[4] = {0U, 0U, 0U, 0U};
    ASSERT_TRUE(producer.Publish(TestSubject.value, 2U, message));
    Endpoint subscribed{};
    std::vector<std::uint8_t> good_datagram{};
    ASSERT_TRUE(producer.Take(subscribed, good_datagram));
    interface_->OnDatagramReceived(subscribed, junk, sizeof(junk));
    EXPECT_EQ(listener_.count, 0U);

    // Empty datagrams are dropped outright.
    interface_->OnDatagramReceived(subscribed, nullptr, 0U);
    EXPECT_EQ(listener_.count, 0U);
}

TEST_F(CyphalUDPInterfaceTest, ServiceRequestResponseRoundTrip) {
    ON_CALL(socket_, Join(_, _)).WillByDefault(Return(core::Status{}));
    auto const request_port = PortId{GetInfoServiceId, PortId::Style::Request};
    auto const response_port = PortId{GetInfoServiceId, PortId::Style::Response};
    EXPECT_TRUE(interface_->Listen(request_port).IsSuccess());
    EXPECT_TRUE(interface_->Listen(response_port).IsSuccess());
    EXPECT_TRUE(interface_->RegisterListener(LocalNodeId, listener_).IsSuccess());

    // A remote client sends us a GetInfo request.
    DatagramProducer producer{heap_};
    ASSERT_TRUE(producer.Request(GetInfoServiceId.value, LocalNodeId, 3U));
    Endpoint from{};
    std::vector<std::uint8_t> datagram{};
    ASSERT_TRUE(producer.Take(from, datagram));
    interface_->OnDatagramReceived(from, datagram.data(), datagram.size());

    ASSERT_EQ(listener_.count, 1U);
    EXPECT_EQ(listener_.last_type, PortId::Type::Service);
    EXPECT_EQ(listener_.last_style, PortId::Style::Request);
    EXPECT_EQ(listener_.last_service, GetInfoServiceId.value);
    EXPECT_EQ(listener_.last_source, RemoteNodeId);
    EXPECT_EQ(listener_.last_recipient, LocalNodeId);

    // We respond via the Interface API; the recorded request transfer-ID is echoed.
    std::vector<std::uint8_t> response_message{5U, 6U};
    Metadata metadata{LocalNodeId, RemoteNodeId, response_port, core::units::MicroSeconds{0ULL}};
    EXPECT_TRUE(interface_->Send(metadata, SerializedMessage{response_message.data(), response_message.size()})
                    .IsSuccess());

    // The response goes to the client's RPC multicast group when drained.
    Endpoint sent_to{};
    EXPECT_CALL(socket_, Send(_, _))
        .WillOnce([&](Endpoint const& destination, core::Span<std::uint8_t const>) {
            sent_to = destination;
            return core::Status{};
        });
    EXPECT_TRUE(interface_->Execute());

    // The response is addressed to the client's own RPC multicast group (node 100).
    Endpoint const expected_client_group{0xEF010000U | static_cast<std::uint32_t>(RemoteNodeId), 9382U};
    EXPECT_TRUE(sent_to == expected_client_group);

    // The produced response is consumable as a valid RPC response transfer.
    ASSERT_TRUE(producer.Respond(GetInfoServiceId.value, LocalNodeId, 3U, response_message));
    Endpoint response_from{};
    std::vector<std::uint8_t> response_datagram{};
    ASSERT_TRUE(producer.Take(response_from, response_datagram));
    interface_->OnDatagramReceived(response_from, response_datagram.data(), response_datagram.size());

    ASSERT_EQ(listener_.count, 2U);
    EXPECT_EQ(listener_.last_type, PortId::Type::Service);
    EXPECT_EQ(listener_.last_style, PortId::Style::Response);
    EXPECT_EQ(listener_.last_service, GetInfoServiceId.value);
    EXPECT_EQ(listener_.data, response_message);

    jarnax::cyphal::TransportStatistics statistics{};
    EXPECT_TRUE(interface_->GetStatistics(statistics).IsSuccess());
    EXPECT_EQ(statistics.transfer.num_received, 2U);

    Mock::VerifyAndClearExpectations(&socket_);
}

TEST_F(CyphalUDPInterfaceTest, SendResponseWithoutRequestFails) {
    auto const response_port = PortId{GetInfoServiceId, PortId::Style::Response};
    Metadata metadata{LocalNodeId, RemoteNodeId, response_port, core::units::MicroSeconds{0ULL}};
    std::uint8_t byte{0U};
    EXPECT_EQ(
        interface_->Send(metadata, SerializedMessage{&byte, 1U}).GetResult(), core::Result::NotExpected);
}

}    // namespace

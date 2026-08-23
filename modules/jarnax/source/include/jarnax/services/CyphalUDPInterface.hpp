#ifndef JARNAX_SERVICES_CYPHAL_UDP_INTERFACE_HPP
#define JARNAX_SERVICES_CYPHAL_UDP_INTERFACE_HPP

#include <cstddef>
#include <cstdint>

#include <core/Array.hpp>
#include <core/Status.hpp>

extern "C" {
#include "udpard.h"
}

#include "jarnax/Loopable.hpp"
#include "jarnax/cyphal/Interface.hpp"
#include "jarnax/cyphal/O1HeapPool.hpp"
#include "jarnax/services/CyphalUDPSocket.hpp"

namespace jarnax {
namespace cyphal {

/// Provides the current time in microseconds since boot.
/// Implemented by the application (e.g. adapted from jarnax::Ticker) and injected
/// into the interface so that this generic module needs no architecture dependencies.
class MicrosecondClock {
public:
    virtual std::uint64_t GetMicroseconds(void) const = 0;

protected:
    ~MicrosecondClock() = default;
};

/// The concrete Cyphal/UDP transport implementing cyphal::Interface on top of libudpard.
/// Applications never touch udpard types directly; they use Listen/Send/RegisterListener
/// and drive the object from the SuperLoop via Loopable::Execute (TX drain).
/// Incoming datagrams are pushed in by a udp::Socket implementation (hypha on target).
class CyphalUDPInterface final : public Interface, public Loopable, public udp::DatagramHandler {
public:
    /// The maximum number of subjects which can be listened to concurrently.
    static constexpr std::size_t MaxSubscriptions{8U};
    /// The maximum number of service ports (requests and responses combined).
    static constexpr std::size_t MaxServicePorts{8U};
    /// The maximum number of tracked transfer-ID counters for outgoing transfers.
    static constexpr std::size_t MaxTransferIds{16U};
    /// The maximum number of remembered service requests awaiting our response.
    static constexpr std::size_t MaxPendingRequests{8U};
    /// The capacity of the libudpard TX queue in datagrams.
    static constexpr std::size_t TxQueueCapacity{32U};

    /// Constructs the interface.
    /// @param heap The O1Heap backed pool shared by all udpard allocations.
    /// @param node_id The local Cyphal node-ID; anonymous (0xFFFF) cannot use services.
    /// @param socket The UDP/IP stack abstraction; its lifetime must exceed ours.
    /// @param ticker The time source used for transfer deadlines and timestamps.
    CyphalUDPInterface(O1HeapPool& heap, udp::NodeId node_id, udp::Socket& socket, MicrosecondClock& clock);
    virtual ~CyphalUDPInterface() override;

    //+=== LOOPABLE INTERFACE ===
    bool Execute() override;

    //+=== CYPHAL INTERFACE ===
    core::Status RegisterListener(NodeId id, Listener& listener) override;
    core::Status Listen(PortId port_id) override;
    core::Status Remove(PortId port_id) override;
    bool IsListening(PortId port_id) const override;
    core::Status Send(Metadata& metadata, SerializedMessage msg) override;
    core::Status GetStatistics(TransportStatistics& statistics) override;

    //+=== DATAGRAM HANDLER ===
    void OnDatagramReceived(udp::Endpoint const& destination, std::uint8_t* data, std::size_t size) override;

    /// @return True when all libudpard pipelines initialized successfully.
    bool IsInitialized() const { return initialized_; }

private:
    struct Subscription final {
        bool used{false};
        SubjectId subject_id{0U};
        UdpardRxSubscription sub{};
    };

    struct ServicePort final {
        bool used{false};
        UdpardRxRPCPort port{};
        ServiceId service_id{0U};
        bool is_request{false};
    };

    struct TransferIdCounter final {
        bool used{false};
        PortId::Type type{PortId::Type::Subject};
        PortId::Style style{PortId::Style::Neither};
        std::uint16_t value{0U};
        udp::NodeId peer{0U};
        UdpardTransferID next{0U};
    };

    struct PendingRequest final {
        bool used{false};
        ServiceId service_id{0U};
        udp::NodeId client{0U};
        UdpardTransferID transfer_id{0U};
    };

    UdpardMicrosecond NowUs() const;
    core::Status MapResult(std::int32_t result) const;
    core::Status ListenSubject(PortId port_id);
    core::Status ListenService(PortId port_id);
    core::Status RemoveSubject(PortId port_id);
    core::Status RemoveService(PortId port_id);
    Subscription* FindSubscription(SubjectId subject);
    Subscription* FindFreeSubscription();
    ServicePort* FindServicePort(ServiceId id, bool is_request);
    ServicePort* FindFreeServicePort();
    TransferIdCounter* FindTransferCounter(PortId port_id, udp::NodeId peer);
    PendingRequest* RememberRequest(ServiceId service_id, udp::NodeId client, UdpardTransferID transfer_id);
    PendingRequest const* FindPendingRequest(ServiceId service_id, udp::NodeId client) const;
    void DeliverTransfer(UdpardRxTransfer const& transfer, PortId port_id);

    O1HeapPool& heap_;
    udp::Socket& socket_;
    MicrosecondClock& clock_;
    udp::NodeId local_node_id_;
    bool initialized_;

    UdpardMemoryResource tx_memory_;
    UdpardRxMemoryResources rx_memory_;
    UdpardTx tx_;
    UdpardRxRPCDispatcher dispatcher_;
    udp::Endpoint service_endpoint_{};
    bool service_group_joined_{false};

    Listener* listener_;
    NodeId listener_node_id_;

    core::Array<Subscription, MaxSubscriptions> subscriptions_{};
    core::Array<ServicePort, MaxServicePorts> service_ports_{};
    core::Array<TransferIdCounter, MaxTransferIds> transfer_ids_{};
    core::Array<PendingRequest, MaxPendingRequests> pending_requests_{};

    core::Array<std::uint8_t, MaxExtent> rx_scratch_{};

    TransportStatistics statistics_{};
};

}    // namespace cyphal
}    // namespace jarnax

#endif    // JARNAX_SERVICES_CYPHAL_UDP_INTERFACE_HPP

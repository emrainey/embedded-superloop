#ifndef JARNAX_CYPHAL_NODE_HPP
#define JARNAX_CYPHAL_NODE_HPP

#include "core/Status.hpp"
#include "jarnax/cyphal/Service.hpp"

namespace jarnax {
namespace cyphal {

/// The Node implements basic functionality for the Cyphal Network.
/// The Heartbeat, GetInfo, GetTransportStatistics, diagnostic Records, and Register Access are implemented here.
class Node : protected cyphal::Server, protected cyphal::Client, protected cyphal::Subscriber, protected cyphal::Publisher {
public:
    ///
    Node(cyphal::Service& service, cyphal::UniqueId const& uid);
    virtual ~Node() = default;

protected:
    /// The reference to the service managing this node.
    cyphal::Service& service_;

    //+=== CYPHAL SERVER INTERFACE ===
    core::Status OnRequest(ServiceId id, SerializedMessage msg) override;
    core::Status GetResponse(ServiceId id, SerializedMessage msg) override;
    //+=== CYPHAL CLIENT INTERFACE ===
    core::Status OnResponse(ServiceId id, SerializedMessage msg) override;
    //+=== CYPHAL SUBSCRIBER INTERFACE ===
    core::Status OnReceive(SubjectId id, SerializedMessage msg) override;
    //+=== CYPHAL PUBLISHER INTERFACE ===
    core::Status OnPublish(SubjectId id, SerializedMessage& msg) override;

    /// The unique identifier for this node in the Cyphal network, published in GetInfo
    cyphal::UniqueId uid_;
};

}    // namespace cyphal
}    // namespace jarnax

#endif    // JARNAX_CYPHAL_NODE_HPP

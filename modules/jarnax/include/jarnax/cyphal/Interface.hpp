#ifndef JARNAX_CYPHAL_INTERFACE_HPP
#define JARNAX_CYPHAL_INTERFACE_HPP

#include <core/Status.hpp>
#include <core/units/MicroSeconds.hpp>

#include "jarnax/cyphal/Types.hpp"

namespace jarnax {
namespace cyphal {

/// The tagged identifier for a port in the Cyphal network, which can be either a subject or a service but not both and not neither.
class PortId {
public:
    enum class Type : uint8_t {
        Subject = 1,
        Service
    };

    enum class Style : uint8_t {
        Neither = 0,
        Request,
        Response
    };
    constexpr PortId() = delete;
    constexpr PortId(SubjectId s)
        : type(Type::Subject)
        , style(Style::Neither)
        , subject(s) {}
    constexpr PortId(ServiceId s, Style st = Style::Request)
        : type(Type::Service)
        , style(st)
        , service(s) {}

    /// The type of the port, indicating whether it is a subject or a service.
    Type type;
    Style style;

    /// The value of the port, which can be either a subject or a service depending on the type.
    union {
        SubjectId subject;
        ServiceId service;
    };

    /// Uses SFINAE to return the value given the type.
    template <typename T>
    constexpr T value() const {
        if constexpr (std::is_same_v<T, SubjectId>) {
            return subject;
        } else if constexpr (std::is_same_v<T, ServiceId>) {
            return service;
        }
    }
};

/// The metadata of a message in the Cyphal network.
struct Metadata {
    Metadata() = delete;
    constexpr Metadata(NodeId src, NodeId rec, PortId pid, core::units::MicroSeconds ts)
        : source(src)
        , recipient(rec)
        , port_id(pid)
        , timestamp(ts) {}

    constexpr Metadata(Metadata const& other)
        : source(other.source)
        , recipient(other.recipient)
        , port_id(other.port_id)
        , timestamp(other.timestamp) {}

    NodeId source;       ///< The node ID of the message source.
    NodeId recipient;    ///< The node ID of the message recipient (broadcast will be "all").
    PortId port_id;      ///< The port ID of the message, which can be either a subject or a service (and then request or response).
    core::units::MicroSeconds timestamp;    ///< The timestamp when the message was operated on.
};

/// The Interface class defines the abstract interface for communication over a Cyphal network (CAN/UDP/Serial/etc.)
/// Implementations will provide the concrete behavior for broadcasting messages, sending requests, and responding to requests over the network as
/// well as managing subscriptions and service advertisements.
class Interface {
public:
    /// The Listener class defines the interface for receiving messages from the Cyphal interface
    class Listener {
    public:
        /// Called when a transfer is received.
        virtual void OnReceive(Metadata const& metadata, SerializedMessage msg) = 0;

    protected:
        ~Listener() = default;
    };

    /// Registers the Listener with the interface.
    /// @param id The node ID for which the listener is being registered.
    /// @param listener The listener to register.
    /// @return Status indicating success or failure.
    virtual core::Status RegisterListener(NodeId id, Listener& listener) = 0;

    /// Adds a node to listen to a specific subject.
    /// @param port_id The subject ID to listen to.
    /// @return Status indicating success or failure.
    virtual core::Status Listen(PortId port_id) = 0;

    /// Removes a node from listening to a specific subject.
    /// @param port_id The subject ID to stop listening to.
    /// @return Status indicating success or failure.
    virtual core::Status Remove(PortId port_id) = 0;

    /// Checks if a node is currently listening to a specific subject.
    /// @param port_id The subject ID to check.
    /// @return True if the node is listening to the subject, false otherwise.
    virtual bool IsListening(PortId port_id) const = 0;

    /// Sends a message from the specified node over the given port.
    /// @param metadata The metadata of the message, including the sender and port ID.
    /// @param msg The serialized message to send.
    /// @return Status indicating success or failure.
    virtual core::Status Send(Metadata& metadata, SerializedMessage msg) = 0;

protected:
    ~Interface() = default;
};

}    // namespace cyphal
}    // namespace jarnax

#endif    // JARNAX_CYPHAL_INTERFACE_HPP

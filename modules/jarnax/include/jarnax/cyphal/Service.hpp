#ifndef JARNAX_CYPHAL_SERVICE_HPP
#define JARNAX_CYPHAL_SERVICE_HPP

#include <core/Span.hpp>
#include <core/Uint.hpp>
#include <core/units/MicroSeconds.hpp>

namespace jarnax {
namespace cyphal {

/// The unique identifier for a subject in the Cyphal network from 0 to 8191 (13 bits).
using SubjectId = core::uint16_<13>;

/// The unique identifier for a service in the Cyphal network from 0 to 511 (9 bits).
using ServiceId = core::uint16_<9>;

/// The serialized representation of a message in the Cyphal network.
using SerializedMessage = core::Span<std::uint8_t>;

/// The unique identifier for a node in the Cyphal network (16 bytes).
using UniqueId = core::Array<std::uint8_t, 16>;

/// The server interface for handling incoming service requests and providing responses.
class Server {
public:
    /// Called when a new request has been received
    core::Status OnRequest(ServiceId id, SerializedMessage msg) = 0;
    /// Called each cycle after OnRequest until either the response is ready or an error occurs
    core::Status GetResponse(ServiceId id, SerializedMessage msg) = 0;
};

/// The client interface for handling responses to service requests.
class Client {
public:
    /// Called when the response from the Request returns
    core::Status OnResponse(ServiceId id, SerializedMessage msg) = 0;
};

/// The publisher interface for providing messages to be published.
class Publisher {
public:
    /// Called to see if a message is ready in the case of no period
    /// Called to obtain a message after the period expired in the case of a timed message
    /// @param msg Set this to your storage of the output message
    core::Status OnPublish(SubjectId id, SerializedMessage& msg) = 0;
};

/// The subscriber interface for handling incoming messages.
class Subscriber {
public:
    /// Called when a message has been received.
    void OnReceive(SubjectId id, SerializedMessage msg) = 0;
};

/// The pure virtual service interface for managing subscriptions, publications, and service requests.
class Service {
public:
    /// Subscribes to a message for future delivery
    core::Status Subscribe(SubjectId id, Subscriber&) = 0;
    /// Publishes a serialized message right now
    core::Status Publish(SubjectId id, SerializedMessage msg) = 0;
    /// Publishes a message when available (publisher is queried later)
    core::Status Publish(SubjectId id, Publisher&) = 0;
    /// Publishes a message on a certain period (publisher is called on period expired)
    core::Status Publish(SubjectId id, Publisher&, core::units::Microseconds period) = 0;
    /// Publishes a Request to a Server
    core::Status Request(ServiceId id, Client&, SerializedMessage msg) = 0;
    /// Directly responds to the request from a Client
    core::Status Respond(ServiceId id, Server&, SerializedMessage msg) = 0;
    /// Registers a Server for a specific Id.
    core::Status Serve(ServiceId id, Server&) = 0;

    /// Dismisses a subscription, publication, or service registration.
    core::Status Dismiss(SubjectId id, Subscriber&) = 0;
    /// Dismisses a subscription, publication, or service registration.
    core::Status Dismiss(SubjectId id, Publisher&) = 0;
    /// Dismisses a subscription, publication, or service registration.
    core::Status Dismiss(ServiceId id, Client&) = 0;
    /// Dismisses a subscription, publication, or service registration.
    core::Status Dismiss(ServiceId id, Server&) = 0;
};

}    // namespace cyphal
}    // namespace jarnax

#endif    // JARNAX_CYPHAL_SERVICE_HPP

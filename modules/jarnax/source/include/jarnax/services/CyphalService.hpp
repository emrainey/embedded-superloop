#ifndef JARNAX_SERVICES_CYPHAL_SERVICE_HPP
#define JARNAX_SERVICES_CYPHAL_SERVICE_HPP

#include <cstddef>

#include <core/Array.hpp>
#include <core/units/MicroSeconds.hpp>

#include "jarnax/Loopable.hpp"

#include "jarnax/cyphal/Service.hpp"

namespace jarnax {
namespace cyphal {

/// Holds information relevant to a published message in the Cyphal network
class PublishRecord {
    Publisher* publisher{nullptr};
    core::units::Microseconds period{0u};
    SubjectId id{0U};
    std::size_t extent{0u};    /// The largest a message could be in bytes
    std::size_t count{0U};     /// The number sent.
    // TODO add other tracking information
};

/// Holds information relevant to a subscribed message in the Cyphal network
class SubscriberRecord {
    Subscriber* subscriber{nullptr};
    SubjectId id{0U};
    std::size_t extent{0u};    ///< The largest a message could be in bytes
    std::size_t count{0u};     ///< The number received
    // TODO add other tracking information
};

/// Holds information relevant to a service request in the Cyphal network
class RequestRecord {
    Client* client{nullptr};
    ServiceId id{0U};
    std::size_t extent{0u};                    ///< The largest a message could be in bytes
    std::size_t count{0u};                     ///< The number sent
    core::units::Microseconds deadline{0u};    ///< The time when a response should be received to be considered on time.
    // TODO add other tracking information
};

/// Holds information relevant to a service response in the Cyphal network
class ResponseRecord {
    Server* server{nullptr};
    ServiceId id{0U};
    std::size_t extent{0u};                    ///< The largest a message could be in bytes
    std::size_t count{0u};                     ///< The number received
    core::units::Microseconds deadline{0u};    ///< The time when it has to respond by
    // TODO add other tracking information (like how long it took to respond)
};

//======================================================
// These should be moved to a configuration header
constexpr static std::size_t MaxNumberOfPublishers{8U};
constexpr static std::size_t MaxNumberOfSubscribers{8U};
constexpr static std::size_t MaxNumberOfRequests{8U};
constexpr static std::size_t MaxNumberOfServers{8U};
//======================================================

/// The implementation of the Cyphal Service.
class CyphalService : public cyphal::Service, public Loopable {
public:
    CyphalService() = default;
    virtual ~CyphalService() = default;

    //+=== LOOPABLE INTERFACE ===
    core::Status Execute() override;

    //+=== CYPHAL SERVICE INTERFACE ===
    core::Status Subscribe(SubjectId id, Subscriber&) override;
    core::Status Publish(SubjectId id, Publisher&) override;
    core::Status Publish(SubjectId id, SerializedMessage msg) override;
    core::Status Publish(SubjectId id, Publisher&, core::units::Microseconds period) override;
    core::Status Request(ServiceId id, Client&, SerializedMessage msg) override;
    core::Status Respond(ServiceId id, Server&, SerializedMessage msg) override;
    core::Status Serve(ServiceId id, Server&) override;
    core::Status Dismiss(SubjectId id, Subscriber&) override;
    core::Status Dismiss(SubjectId id, Publisher&) override;
    core::Status Dismiss(ServiceId id, Client&) override;
    core::Status Dismiss(ServiceId id, Server&) override;

protected:
    core::Array<PublishRecord, MaxNumberOfPublishers> publishers_;
    core::Array<SubscriberRecord, MaxNumberOfSubscribers> subscribers_;
    core::Array<RequestRecord, MaxNumberOfRequests> requests_;
    core::Array<ResponseRecord, MaxNumberOfServers> servers_;
};

}    // namespace cyphal
}    // namespace jarnax

#endif    // JARNAX_SERVICES_CYPHAL_SERVICE_HPP

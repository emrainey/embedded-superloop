#include "jarnax/services/CyphalService.hpp"
#include "core/Status.hpp"

namespace jarnax {
namespace cyphal {

CyphalService::CyphalService() {}

CyphalService::~CyphalService() {}

core::Status CyphalService::Subscribe(SubjectId id, Subscriber& subscriber) {
    // Implementation goes here
    return core::Status{};
}

core::Status CyphalService::Publish(SubjectId id, SerializedMessage msg) {
    // Implementation goes here
    return core::Status{};
}

core::Status CyphalService::Publish(SubjectId id, Publisher& publisher) {
    // Implementation goes here
    return core::Status{};
}

core::Status CyphalService::Publish(SubjectId id, Publisher& publisher, core::units::Microseconds period) {
    // Implementation goes here
    return core::Status{};
}

core::Status CyphalService::Request(ServiceId id, Client& client, SerializedMessage msg) {
    // Implementation goes here
    return core::Status{};
}

core::Status CyphalService::Respond(ServiceId id, Server& server, SerializedMessage msg) {
    // Implementation goes here
    return core::Status{};
}

core::Status CyphalService::Serve(ServiceId id, Server& server) {
    // Implementation goes here
    return core::Status{};
}

core::Status CyphalService::Dismiss(SubjectId id, Subscriber& subscriber) {
    for (std::size_t i = 0u; i < subscribers_.size(); ++i) {
        if (&subscriber == subscribers_[i].subscriber) {
            // clear out the subscriber record
            subscribers_[i].subscriber = nullptr;
            subscribers_[i].id = 0U;
            subscribers_[i].extent = 0u;
            subscribers_[i].count = 0u;
            subscribers_[i].deadline = core::units::Microseconds{0u};
            return core::Status{};
        }
    }
    return core::Status{core::Result::NotAvailable, core::Cause::Resource};
}

core::Status CyphalService::Dismiss(SubjectId id, Publisher& publisher) {
    for (std::size_t i = 0u; i < publishers_.size(); ++i) {
        if (&publisher == publishers_[i].publisher) {
            // clear out the publisher record
            publishers_[i].publisher = nullptr;
            publishers_[i].id = 0U;
            publishers_[i].extent = 0u;
            publishers_[i].count = 0u;
            publishers_[i].deadline = core::units::Microseconds{0u};
            return core::Status{};
        }
    }
    return core::Status{core::Result::NotAvailable, core::Cause::Resource};
}

core::Status CyphalService::Dismiss(ServiceId id, Client& client) {
    for (std::size_t i = 0u; i < requests_.size(); ++i) {
        if (&client == requests_[i].client) {
            // clear out the request record
            requests_[i].client = nullptr;
            requests_[i].id = 0U;
            requests_[i].extent = 0u;
            requests_[i].count = 0u;
            requests_[i].deadline = core::units::Microseconds{0u};
            return core::Status{};
        }
    }
    return core::Status{core::Result::NotAvailable, core::Cause::Resource};
}

core::Status CyphalService::Dismiss(ServiceId id, Server& server) {
    for (std::size_t i = 0; i < servers_.size(); ++i) {
        if (&server == servers_[i].server) {
            // clear out the server record
            servers_[i].server = nullptr;
            servers_[i].id = 0U;
            servers_[i].extent = 0u;
            servers_[i].count = 0u;
            servers_[i].deadline = core::units::Microseconds{0u};
            return core::Status{};
        }
    }
    return core::Status{core::Result::NotAvailable, core::Cause::Resource};
}

}    // namespace cyphal
}    // namespace jarnax

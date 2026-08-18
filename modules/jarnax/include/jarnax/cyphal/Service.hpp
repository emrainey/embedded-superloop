#ifndef JARNAX_CYPHAL_SERVICE_HPP
#define JARNAX_CYPHAL_SERVICE_HPP

/// @file
/// The Cyphal Service Declaration and Interface Definitions

#include <core/Span.hpp>
#include <core/Uint.hpp>
#include <core/units/MicroSeconds.hpp>
#include "jarnax/cyphal/Node.hpp"

namespace jarnax {
namespace cyphal {

/// The pure virtual service interface managing the Cyphal Node and the underlying implementation details.
class Service {
public:
    Service() = default;
    virtual ~Service() = default;

    /// Adds a node to the service.
    virtual core::Status Enlist(cyphal::Node* node) = 0;
    /// Remove a node from the service.
    virtual core::Status Dismiss(cyphal::Node* node) = 0;

protected:
    /// The set of nodes that are managed by this service.
    core::Array<cyphal::Node*, 1> nodes_;
};

}    // namespace cyphal
}    // namespace jarnax

#endif    // JARNAX_CYPHAL_SERVICE_HPP

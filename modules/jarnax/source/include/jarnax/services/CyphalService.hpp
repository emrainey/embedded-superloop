#ifndef JARNAX_SERVICES_CYPHAL_SERVICE_HPP
#define JARNAX_SERVICES_CYPHAL_SERVICE_HPP

#include <cstddef>

#include <core/Array.hpp>
#include <core/units/MicroSeconds.hpp>

#include "jarnax/Loopable.hpp"

#include "jarnax/cyphal/Service.hpp"

namespace jarnax {
namespace cyphal {

//+=== Should be in a configuration header or a more appropriate location for global constants.
/// The maximum number of nodes that the Cyphal Service can manage on this platform.
static constexpr std::size_t MaxNumberOfNodes = 2;

/// The implementation of the Cyphal Service.
class CyphalService : public cyphal::Service, public Loopable {
public:
    CyphalService();
    virtual ~CyphalService() = default;

    //+=== LOOPABLE INTERFACE ===
    bool Execute() override;

    //+=== CYPHAL SERVICE INTERFACE ===
    core::Status Enlist(cyphal::Node* node) override;
    core::Status Dismiss(cyphal::Node* node) override;

protected:
    core::Array<cyphal::Node*, MaxNumberOfNodes> m_nodes{};
};

}    // namespace cyphal
}    // namespace jarnax

#endif    // JARNAX_SERVICES_CYPHAL_SERVICE_HPP

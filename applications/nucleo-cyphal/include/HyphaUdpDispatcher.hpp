#ifndef APP_HYPHA_UDP_DISPATCHER_HPP
#define APP_HYPHA_UDP_DISPATCHER_HPP

#include <cstddef>

#include <core/Array.hpp>

extern "C" {
#include "hypha_ip/hypha_ip.h"
}

#include "jarnax/services/CyphalUDPDispatcher.hpp"

namespace nucleo {
namespace cyphal {

/// Adapts libhypha's single UDP callback to Cyphal multicast endpoint dispatch.
class HyphaUdpDispatcher final : public jarnax::cyphal::udp::Dispatcher {
public:
    static constexpr std::size_t MaxEndpoints{9U};

    HyphaUdpDispatcher(HyphaIpContext_t& context, HyphaIpNetworkInterface_t const& network_interface);

    core::Status Join(jarnax::cyphal::udp::Endpoint const& multicast_endpoint,
                      jarnax::cyphal::udp::DatagramHandler& handler) override;
    core::Status Leave(jarnax::cyphal::udp::Endpoint const& multicast_endpoint) override;
    core::Status Send(jarnax::cyphal::udp::Endpoint const& destination,
                      core::Span<std::uint8_t const> payload) override;

    /// Delivers a datagram received by CyphalApp's libhypha callback to its registered handler.
    void Dispatch(HyphaIpMetaData_t const& metadata, HyphaIpSpan_t datagram);

private:
    struct Registration final {
        bool used{false};
        jarnax::cyphal::udp::Endpoint endpoint{};
        jarnax::cyphal::udp::DatagramHandler* handler{nullptr};
    };

    static HyphaIpIPv4Address_t ToHyphaAddress(std::uint32_t address);
    static std::uint32_t ToEndpointAddress(HyphaIpIPv4Address_t address);
    static core::Status ToStatus(HyphaIpStatus_e status);

    HyphaIpContext_t& context_;
    HyphaIpNetworkInterface_t const& network_interface_;
    core::Array<Registration, MaxEndpoints> registrations_{};
};

}    // namespace cyphal
}    // namespace nucleo

#endif    // APP_HYPHA_UDP_DISPATCHER_HPP
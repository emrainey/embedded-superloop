#ifndef JARNAX_NET_IP_V4_ROUTE_HPP
#define JARNAX_NET_IP_V4_ROUTE_HPP

/// @file
/// IPv4 Route Definitions

#include "jarnax/net/Interface.hpp"

namespace jarnax {
namespace net {
namespace ip {
namespace v4 {

/// An IPv4 Route is a mapping of a destination network (defined by an address and a mask) to a next hop (defined by an address) and an interface
/// (defined by an index or name).
class Route {
public:
    /// @brief Must have at least 1 interface to make a default route
    Route(Interface& interface);

    /// @brief A constructor for a route with a specific destination network and interface
    Route(Address network, uint8_t prefix_length, Interface& interface);

    /// @brief Checks if this route could be used to route a packet to the given destination address (i.e. if the destination address is in the same
    /// network as this route) or if this is a default route (i.e. the network is 0.0.0.0/0) or if the destination address is the limited broadcast
    /// address (i.e. 255.255.255.255) or the local broadcast address for the network (i.e. the broadcast address for the subnet defined by the
    /// network and mask) or is a multicast address (i.e. in the 224.x.x.x to 239.x.x.x range)
    bool CouldRoute(Address destination) const;

    Address network;    ///< The destination network for this route (defined by an address and a mask). This can either a the same as or a subset of
                        ///< the interface network.
    Address netmask;    ///< The subnet mask for the destination network
    net::Interface& interface;    ///< The interface to use for this route
};

namespace local {
/// The common default route for local addresses (i.e. 127.x.x.x)
extern Route loopback_route;
}    // namespace local

}    // namespace v4
}    // namespace ip
}    // namespace net
}    // namespace jarnax

#endif    // JARNAX_NET_IP_V4_ROUTE_HPP

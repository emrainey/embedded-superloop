#ifndef JARNAX_NET_IP_V4_INTERFACE_HPP
#define JARNAX_NET_IP_V4_INTERFACE_HPP

#include "jarnax/net/ip/v4/Address.hpp"

namespace jarnax {
namespace net {
namespace ip {
namespace v4 {

/// The IPv4 Interface Class represents a network interface with an assigned IP address and other details.
class Interface {
public:
    Interface() = default;
    Interface(Address address, Address netmask);
    Interface(Address address, Address netmask, Address gateway);

    /// Checks if this interface has a valid configuration (i.e. has an address and netmask, and the address is not the network or broadcast address
    /// for the subnet)
    bool IsValid() const;

    /// Checks if this interface could receive a packet sent from the given source address (i.e. if the source address is in the same subnet as this
    /// interface or is the broadcast address for the subnet)
    bool CouldReceive(Address source) const;

    Address address;      ///< The IP address assigned to this interface
    Address netmask;      ///< The subnet mask for this interface
    Address network;      ///< The network range for this interface (deduced from the address and netmask)
    Address broadcast;    ///< The broadcast address for this interface (deduced from the address and netmask)
    Address gateway;      ///< The default gateway for this interface
};

namespace local {
/// The common interface for local addresses (i.e. 127.x.x.x)
extern Interface loopback_interface;
}    // namespace local

}    // namespace v4
}    // namespace ip
}    // namespace net
}    // namespace jarnax

#endif    // JARNAX_NET_IP_V4_INTERFACE_HPP

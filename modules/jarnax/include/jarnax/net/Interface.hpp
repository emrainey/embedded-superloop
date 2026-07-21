#ifndef JARNAX_NET_INTERFACE_HPP
#define JARNAX_NET_INTERFACE_HPP

#include "jarnax/net/ethernet/Driver.hpp"
#include "jarnax/net/eui/Address.hpp"
#include "jarnax/net/ip/v4/Address.hpp"

namespace jarnax {
namespace net {

/// The IPv4 Interface Class represents a network interface with an assigned IP address and other details.
class Interface {
public:
    Interface(ethernet::Driver& driver, eui48::Address mac, ip::v4::Address address, ip::v4::Address netmask);
    Interface(ethernet::Driver& driver, eui48::Address mac, ip::v4::Address address, ip::v4::Address netmask, ip::v4::Address gateway);

    /// Checks if this interface has a valid configuration (i.e. has an address and netmask, and the address is not the network or broadcast address
    /// for the subnet)
    bool IsValid() const;

    /// Checks if this interface could receive a packet sent from the given source address (i.e. if the source address is in the same subnet as this
    /// interface or is the broadcast address for the subnet)
    bool CouldReceive(ip::v4::Address source) const;

    ///

protected:
    ethernet::Driver& driver_;     ///< The Ethernet driver associated with this interface, which is used to send and receive packets on the network.
public:
    eui48::Address mac_address;    ///< The MAC address of this interface
    ip::v4::Address address;       ///< The IP address assigned to this interface
    ip::v4::Address netmask;       ///< The subnet mask for this interface
    ip::v4::Address network;       ///< The network range for this interface (deduced from the address and netmask)
    ip::v4::Address broadcast;     ///< The broadcast address for this interface (deduced from the address and netmask)
    ip::v4::Address gateway;       ///< The default gateway for this interface
};

namespace local {
/// The common interface for local addresses (i.e. 127.x.x.x)
extern Interface loopback_interface;
}    // namespace local

}    // namespace net
}    // namespace jarnax

#endif    // JARNAX_NET_INTERFACE_HPP

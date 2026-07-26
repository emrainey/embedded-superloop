#ifndef JARNAX_NET_ETHERNET_TYPES__HPP_
#define JARNAX_NET_ETHERNET_TYPES__HPP_
/// @file
/// The EtherType enumeration for various Ethernet protocols.

#include <cstdint>

namespace jarnax {
namespace net {
namespace ethernet {

/// The EtherType field of an Ethernet frame, which indicates the protocol encapsulated in the payload of the frame. This enumeration defines some
/// common EtherType values, such as IPv4, ARP, and IPv6. The values are represented in hexadecimal, as they appear in the actual Ethernet frame.
/// @note This is not an exhaustive list of EtherTypes, but it can be expanded as needed to include additional protocols.
/// @warning This is defined in host byte order, so it may need to be converted to network byte order (big-endian) when constructing or parsing
/// Ethernet frames, depending on the endianness of the host system.
enum class EtherType : uint16_t {
    IPv4 = 0x0800,    ///< Internet Protocol version 4 (IPv4)
    ARP = 0x0806,     ///< Address Resolution Protocol (ARP)
    // WakeOnLan = 0x0842,    ///< Wake-on-LAN
    // IPv6 = 0x86DD,         ///< Internet Protocol version 6 (IPv6)
    // VLAN = 0x8100,         ///< IEEE 802.1Q VLAN-tagged frame  (unsupported for now)
    // EtherCAT = 0x88A4,    //!< EtherCAT Protocol (unsupported for now)
};

/// Returns a string representation of the given EtherType.
char const* ToString(EtherType type);

}    // namespace ethernet
}    // namespace net
}    // namespace jarnax

#endif    // JARNAX_NET_ETHERNET_TYPES__HPP_

#ifndef JARNAX_NET_ARP_PACKET__HPP_
#define JARNAX_NET_ARP_PACKET__HPP_

/// @file
/// The ARP Packet Declaration

#include "jarnax/net/configuration.hpp"
#include "jarnax/net/ethernet/Frame.hpp"
#include "jarnax/net/eui/Address.hpp"
#include "jarnax/net/ip/v4/Address.hpp"

namespace jarnax {
namespace net {
namespace arp {

enum class HardwareType : uint16_t {
    Ethernet = 1,    ///< Ethernet (10Mb) --- This is the most common hardware type and is used for Ethernet networks.
};

enum class Opcode : uint16_t {
    Request = 1,    ///< ARP Request, used to request the MAC address associated with a given IPv4 address.
    Reply = 2,      ///< ARP Reply, used to respond to an ARP Request with the MAC address associated with the requested IPv4 address.
};

/// The ARP Packet structure definition. This structure is used to represent an ARP packet in memory, allowing for easy manipulation and access to the
/// various fields of the packet. The structure is designed to be packed, ensuring that there is no padding between the fields, which is important for
/// correctly interpreting the raw bytes of an ARP packet.
/// @note The fields of the ARP packet are represented in host order! Use the FlipByteOrder function to convert between host order and network order
/// when constructing or parsing ARP packets.
struct Packet final {
    uint16_t hardware_type;               ///< The Hardware Type field of the ARP packet, which indicates the type of hardware used for the local
                                          ///< network (e.g., Ethernet).
    ethernet::EtherType protocol_type;    ///< The Protocol Type field of the ARP packet, which indicates the type of protocol used in the payload of
                                          ///< the ARP packet (e.g., IPv4).
    uint8_t hardware_size;                ///< The Hardware Size field of the ARP packet, which indicates the
                                          ///< length of the hardware address in bytes (e.g., 6 for Ethernet).
    uint8_t protocol_size;    ///< The Protocol Size field of the ARP packet, which indicates the length of the protocol address in bytes (e.g., 4 for
                              ///< IPv4).
    Opcode opcode;            ///< The Opcode field of the ARP packet, which indicates the type of ARP message (e.g., request or reply).
    eui48::Address sender_mac;    ///< The Sender MAC Address field of the ARP packet, which contains the MAC address of the sender of the ARP packet.
    ip::v4::Address sender_ip;    ///< The Sender IP Address field of the ARP packet, which contains the IPv4 address of the sender of the ARP packet.

    /// The Target MAC Address field of the ARP packet, which contains the MAC address of the intended recipient of the
    /// ARP packet (for ARP requests, this field is typically set to 00:00:00:00:00:00).
    eui48::Address target_mac;

    /// The Target IP Address field of the ARP packet, which contains the IPv4 address of the intended recipient of the ARP packet.
    ip::v4::Address target_ip;

    /// Flips the ARP packet from network order to host order or vice versa. This is necessary because the fields of the ARP packet are represented in
    /// network byte order (big-endian) when transmitted over the network, but they may be represented in host byte order (which can be little-endian
    /// or big-endian depending on the architecture) when stored in memory. This function ensures that the fields of the ARP packet are correctly
    /// interpreted regardless of the endianness of the host system.
    inline void Flip() {
        hardware_type = static_cast<ethernet::EtherType>(__builtin_bswap16(static_cast<uint16_t>(hardware_type)));
        protocol_type = static_cast<ethernet::EtherType>(__builtin_bswap16(static_cast<uint16_t>(protocol_type)));
        opcode = static_cast<Opcode>(__builtin_bswap16(static_cast<uint16_t>(opcode)));
        // Addresses are not flipped because they are represented as byte arrays, so their byte order is not affected by endianness.
    }
};
static_assert(sizeof(Packet) == 28U, "ARP packet must be exactly 28 bytes");

}    // namespace arp
}    // namespace net
}    // namespace jarnax

#endif    // JARNAX_NET_ARP_PACKET__HPP_

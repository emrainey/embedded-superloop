#ifndef JARNAX_NET_ETH_FRAME__HPP_
#define JARNAX_NET_ETH_FRAME__HPP_

/// @file
/// The Ethernet Frame structure definition for Jarnax's Ethernet driver implementation. This structure is used to represent an Ethernet frame in
/// memory, allowing for easy manipulation and access to the various fields of the frame. The structure is designed to be packed, ensuring that there
/// is no padding between the fields,

#include "jarnax/net/configuration.hpp"
#include "jarnax/net/ethernet/Types.hpp"
#include "jarnax/net/eui/Address.hpp"
#include "jarnax/net/ip/v4/Packet.hpp"
// #include "jarnax/net/ip/v6/Packet.hpp"
#include "jarnax/net/arp/Packet.hpp"

namespace jarnax {
namespace net {
namespace ethernet {

/// The Ethernet Frame structure definition. This structure is used to represent an Ethernet frame in memory, allowing for easy manipulation and
/// access to the various fields of the frame. The structure is designed to be packed, ensuring that there is no padding between the fields, which is
/// important for correctly interpreting the raw bytes of an Ethernet frame.
struct Frame final {
    struct Header final {
        constexpr Header()
            : destination{}
            , source{}
            , type(EtherType::IPv4) {}    ///< Default constructor initializes the EtherType

        /// Parameterized Constructor for constant references
        constexpr Header(eui48::Address const& dest, eui48::Address const& src, EtherType t)
            : destination{dest}
            , source{src}
            , type{t} {}

        /// Swaps the source and destination addresses of the Ethernet frame, which can be useful when constructing a response frame (e.g., an ARP
        /// reply) based on an incoming frame. This allows the response frame to be sent back to the original sender of the incoming frame.
        void SwapAddress() {
            eui48::Address temp = destination;
            destination = source;
            source = temp;
        }

        eui48::Address destination;    ///< The destination MAC address of the Ethernet frame, represented as an EUI-48 address.
        eui48::Address source;         ///< The source MAC address of the Ethernet frame, represented as an EUI-48 address.
        EtherType type;                ///< The EtherType field of the Ethernet frame, indicating the protocol encapsulated in the payload.

        inline void Flip() {
            type = static_cast<EtherType>(__builtin_bswap16(static_cast<uint16_t>(type)));
            // Addresses are not flipped because they are represented as byte arrays, so their byte order is not affected by endianness.
        }
    };    ///< Ensure that the header is packed without any padding.
    static_assert(sizeof(Header) == ethernet::HeaderSize, "Ethernet header must be exactly this size");
    //+=== MEMORY ======================================+
    Header header;
    union Payload {
        Payload()
            : data{} {}
        arp::Packet arp;        ///< The payload of the Ethernet frame, interpreted as an ARP packet if the EtherType indicates ARP.
        ip::v4::Packet ipv4;    ///< The payload of the Ethernet frame, interpreted as an IPv4 packet if the EtherType indicates IPv4.
        // ip::v6::Packet ipv6;    ///< The payload of the Ethernet frame, interpreted as an IPv6 packet if the EtherType indicates IPv6.
        uint8_t data[ethernet::MediaTransmissionUnit];    ///< The payload of the Ethernet frame, which can contain up to the MTU size of data.
    } payload;
    //+=== MEMORY ======================================+
};

static_assert(sizeof(Frame) >= 64, "Ethernet frames must be at least 64 bytes");
static_assert(sizeof(Frame) <= 9000, "Ethernet frames must be at most 9000 bytes");

/// A helper function to check if a given EtherType is a known type that we can handle in our Ethernet driver implementation. This can be used to
/// quickly determine if we can parse the payload of an Ethernet frame based on its EtherType, and can help us identify unsupported or unknown
/// protocols that we may want to log or ignore.
constexpr bool IsKnownType(EtherType type) {
    switch (type) {
        case EtherType::IPv4:
        case EtherType::ARP:
            // case EtherType::WakeOnLan:
            // case EtherType::IPv6:
            // case EtherType::VLAN:
            return true;
        default:
            return false;
    }
}

}    // namespace ethernet
}    // namespace net
}    // namespace jarnax

#endif    // JARNAX_NET_ETH_FRAME__HPP_

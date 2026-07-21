#ifndef JARNAX_NET_IP_V4_PACKET__HPP_
#define JARNAX_NET_IP_V4_PACKET__HPP_

/// @file
/// The IPv4 Packet Declaraction

#include "jarnax/net/configuration.hpp"
#include "jarnax/net/ip/v4/Address.hpp"
#include "jarnax/net/ip/v4/Datagram.hpp"

namespace jarnax {
namespace net {
namespace ip {
namespace v4 {

/// The Protocol field of the IPv4 packet, which indicates the protocol encapsulated in the payload of the packet (e.g., TCP, UDP).
enum class Protocol : uint16_t {
    ICMP = 1,    ///< Internet Control Message Protocol (ICMP)
    TCP = 6,     ///< Transmission Control Protocol (TCP)
    UDP = 17,    ///< User Datagram Protocol (UDP)
};

/// The IPv4 Packet structure definition. This structure is used to represent an IPv4 packet in memory, allowing for easy manipulation and access to
/// the various fields of the packet. The structure is designed to be packed, ensuring that there is no padding between the fields, which is important
/// for correctly interpreting the raw bytes of an IPv4 packet.
class Packet final {
    /// The Header structure represents the header of the IPv4 packet, containing all the fields defined in the IPv4 specification. The fields are
    /// defined according to the standard layout of an IPv4 header, and the structure is packed to ensure that there is no padding between the fields,
    /// which is crucial for correctly interpreting the raw bytes of an IPv4 packet.
    class Header final {
    public:
        constexpr Header()
            : ecn{0U}
            , dscp{0U}
            , IHL{5U}
            , version{4U}
            , total_length{0U}
            , identification{0U}
            , fragment_offset{0U}
            , more_fragments{0U}
            , do_not_fragment{1U}
            , protocol{Protocol::TCP}
            , time_to_live{64U}
            , header_checksum{0U}
            , source_address{}
            , destination_address{} {}
        // +=== MEMORY ======================================+
        // === 0x0000 - 0x0003 ===
        /// The Explicit Congestion Notification (ECN) field of the IPv4 packet, which is used for indicating network congestion without dropping
        /// packets.
        uint16_t ecn           : 2;
        /// The Differentiated Services Code Point (DSCP) field of the IPv4 packet, which indicates the quality of service
        /// desired for the packet.
        uint16_t dscp          : 6;
        /// The Internet Header Length (IHL) field of the IPv4 packet, which indicates the length of the header in 32-bit words.
        /// The minimum value is 5 (20 bytes), and the maximum value is 15 (60 bytes).
        uint16_t IHL           : 4;
        uint16_t const version : 4;    ///< The Version field of the IPv4 packet, which indicates the version of the Internet Protocol used in the
                                       ///< packet. For IPv4, this field is set to 4.
        uint16_t total_length;    ///< The Total Length field of the IPv4 packet, which indicates the length of the entire packet in bytes, including
                                  ///< the header and payload.
        // === 0x0004 - 0x0007 ===
        uint16_t identification;    ///< The Identification field of the IPv4 packet, which is used for uniquely identifying the packet, especially
                                    ///< when fragmentation occurs.
        /// The Fragment Offset field of the IPv4 packet, which indicates the position of the fragment in the original packet.
        uint16_t fragment_offset : 13;
        uint16_t more_fragments  : 1;
        uint16_t do_not_fragment : 1;
        uint16_t                 : 1;
        // === 0x0008 - 0x000B ===
        /// The Protocol field of the IPv4 packet, which indicates the protocol encapsulated in the payload of the packet
        /// (e.g., TCP, UDP).
        Protocol protocol        : 8;
        /// The Time to Live (TTL) field of the IPv4 packet, which indicates the maximum number of hops the packet can
        /// take before being discarded.
        uint16_t time_to_live    : 8;
        uint16_t header_checksum;    ///< The Header Checksum field of the IPv4 packet, which is used for error-checking the header of the packet.
        /// The Source Address field of the IPv4 packet, which contains the IPv4 address of the sender of the packet.
        ip::v4::Address source_address;
        /// The Destination Address field of the IPv4 packet, which contains the IPv4 address of the intended recipient of the packet.
        ip::v4::Address destination_address;
        // +=== MEMORY ======================================+
    };

    constexpr static std::size_t const HeaderSize{sizeof(Header)};    ///< The size of the IPv4 packet header in bytes, which is used to calculate the
                                                                      ///< maximum payload size of the packet based on the MTU.
    static_assert(HeaderSize == 20U, "The IPv4 header must be 20 bytes. No options supported.");

    // +=== MEMORY ======================================+
    Header header;                 ///< The header of the IPv4 packet, containing all the fields defined in the Header structure.
    union {
        udp::Datagram datagram;    ///< The payload of the IPv4 packet, interpreted as an IPv4 datagram.
        uint8_t payload[ethernet::MediaTransmissionUnit - sizeof(Header)];    ///< The payload of the IPv4 packet, which can contain up to the MTU
                                                                              ///< size of data.
    };
    // +=== MEMORY ======================================+
};

}    // namespace v4
}    // namespace ip
}    // namespace net
}    // namespace jarnax

#endif    // JARNAX_NET_IP_V4_PACKET__HPP_

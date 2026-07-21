#ifndef JARNAX_NET_IP_V4_DATAGRAM__HPP_
#define JARNAX_NET_IP_V4_DATAGRAM__HPP_

/// @file
/// The UDP Datagram Declaration

#include "jarnax/net/configuration.hpp"

namespace jarnax {
namespace net {
namespace udp {

/// The UDP datagram contains a header with fields for the source port, destination port, length, and checksum, as well as
/// a payload that can contain up to the maximum size of a UDP datagram (which is determined by the MTU and the size of the IPv4 header). The UDP
/// datagram is used for communication between applications on the network, and it is a connectionless protocol that does not guarantee delivery or
/// order of datagrams. The UDP datagram is encapsulated within an IPv4 packet, which is then encapsulated within an Ethernet frame for transmission
/// over the network.
class Datagram final {
    /// The UDP Header structure definition. This structure is used to represent the header of a UDP datagram in memory, allowing for easy
    /// manipulation and access to the various fields of the header. The structure is designed to be packed, ensuring that there is no padding between
    /// the fields, which is important for network communication where the header must match the format expected by the protocol.
    class Header final {
    public:
        constexpr Header()
            : source_port{0U}
            , destination_port{0U}
            , length{0U}
            , checksum{0U} {}
        // +=== MEMORY ======================================+
        uint16_t source_port;         ///< The Source Port field of the IPv4 datagram, which contains the port number of the sender of the datagram.
        uint16_t destination_port;    ///< The Destination Port field of the IPv4 datagram
                                      ///< contains the port number of the intended recipient of the datagram.
        uint16_t length;              ///< The Length field of the IPv4 datagram, which
                                      ///< indicates the length of the datagram in bytes, including the header and payload.
        uint16_t checksum;    ///< The Checksum field of the IPv4 datagram, which is used for error-checking the header and payload of the datagram.
        // +=== MEMORY ======================================+

        /// @brief Flips the byte order of the fields in the UDP header for network transmission. This is necessary because the fields in the UDP
        /// header are stored in host byte order, but the network expects them in network byte order (big-endian).
        inline void Flip() {
            source_port = __builtin_bswap16(source_port);
            destination_port = __builtin_bswap16(destination_port);
            length = __builtin_bswap16(length);
            checksum = __builtin_bswap16(checksum);
        }
    };

    // +=== MEMORY ======================================+
    Header header;                                                            ///< The header of the IPv4 datagram, containing all the fields
    union {
        uint8_t payload[ethernet::MediaTransmissionUnit - sizeof(Header)];    ///< The payload of the IPv4 datagram, which can contain up to the MTU
                                                                              ///< size of data.
    };
    // +=== MEMORY ======================================+
};

}    // namespace udp
}    // namespace net
}    // namespace jarnax

#endif    // JARNAX_NET_IP_V4_DATAGRAM__HPP_

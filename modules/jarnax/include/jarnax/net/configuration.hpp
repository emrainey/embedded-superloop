#ifndef JARNAX_NET_CONFIGURATION__HPP_
#define JARNAX_NET_CONFIGURATION__HPP_

#include <cstddef>
#include <cstdint>

/// @file
/// The generic types of the Jarnax Networking Stack. This includes things like the MTU, header sizes, and other constants that are used throughout
/// the networking stack. This file is included by all of the networking stack headers, so it should only contain things that are used by multiple
/// components of the networking stack. It should not contain any implementation details or hardware-specific definitions.

namespace jarnax {
/// Networking namespace
namespace net {
/// Ethernet namespace
namespace ethernet {

/// The maximum number of MAC addresses that the Ethernet controller can be configured with. This is used to define the size of the address table in
/// the Ethernet Driver, and it is also used by higher-level network protocols (e.g., ARP, IP) to determine how many addresses they can use for
/// sending and receiving frames on the network. The actual number of addresses that can be configured may be limited by the hardware capabilities of
/// the Ethernet controller, so this constant should be set to the maximum number of addresses that the hardware can support.
constexpr static std::size_t const MaxMACAddressCount{2U};    // One for real MAC and one for Multicast

/// The size of a non-VLAN Ethernet header in bytes. Does not get included in the MTU calculation.
constexpr static std::size_t const HeaderSize{14U};

/// The maximum number of filter entries that the Ethernet controller can handle. This is used to define the size of the filter table in the Ethernet
/// Driver.
constexpr static std::size_t const MaximumFilterEntries{8U};

#if not defined(MTU)
#define MTU 1536U
#endif

/// The standard Ethernet Maximum Transmission Unit (MTU) size, which is the maximum payload size of an Ethernet frame.
constexpr static std::size_t const MediaTransmissionUnit{MTU};
}    // namespace ethernet

/// Internet Protocol namespace
namespace ip {
/// Internet Protocol version 4 namespace
namespace v4 {
/// The maximum size of an IPv4 header in bytes, which is used to calculate the maximum payload size of an IPv4 packet based on the MTU.
constexpr static std::size_t const MaxHeaderSize{20U};

/// The maximum size of an IPv4 packet, which is the MTU minus the size of the IPv4 Header
constexpr static std::size_t const MaxPacketSize{ethernet::MediaTransmissionUnit - MaxHeaderSize};
}    // namespace v4
}    // namespace ip

/// Universal Datagram Protocol namespace
namespace udp {
/// The maximum size of an IPv4 datagram header
constexpr static std::size_t const DatagramHeaderSize{8U};

/// The maximum size of an IPv4 datagram, which is the maximum size of an IPv4 packet minus the size of the IPv4 Datagram Header
constexpr static std::size_t const MaxDatagramSize{ip::v4::MaxPacketSize - DatagramHeaderSize};
}    // namespace udp

/// Address Resolution Protocol namespace
namespace arp {
/// The maximum number of ARP entries that can be stored in the ARP table, which is determined
/// by the size of the ARP table and the size of each entry (1 IP-MAC mapping). The maximum number for a
/// local most networks is 256 entries, but we can set it to a lower value to save memory if we know that we won't have that many devices on the
/// network. This allows us to have a fixed-size ARP table, which can simplify the implementation and reduce memory fragmentation.
constexpr static std::size_t MaxEntries{128U};

/// When enabled the Ethernet Driver will scrap incoming IPv4 packets to automatically learn the MAC-to-IP mappings.
/// @note This is a tad dangerous as the IP Header hasn't been checked yet in the Ethernet Driver if the hardware offloads IP checksum verification is
/// not turned on!
constexpr static bool LearnAddresses{true};
}    // namespace arp

}    // namespace net
}    // namespace jarnax

#endif    // JARNAX_NET_CONFIGURATION__HPP_

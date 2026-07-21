#ifndef JARNAX_NET_TYPES__HPP_
#define JARNAX_NET_TYPES__HPP_

/// @file
/// The generic types of the jarnax::net namespace, which can be used across different

#include <cstddef>
#include <cstdint>

namespace jarnax {
namespace net {

/// The ComponentThroughput struct represents the total number of bytes sent and received by the network stack, which can be used to calculate the
/// throughput of the network.
struct ComponentThroughput final {
    /// The total number of bytes received by the network stack, which can be used to calculate the throughput of the network.
    size_t bytes_received;
    /// The total number of bytes sent by the network stack, which can be used to calculate the throughput of the network.
    size_t bytes_sent;
    /// The total number of units (packets, frames, datagrams, etc.) received by the network stack, which can be used to calculate the throughput of
    /// the network.
    size_t units_received;
    /// The total number of units (packets, frames, datagrams, etc.) sent by the network stack, which can be used to calculate the throughput of the
    /// network.
    size_t units_sent;
    /// The total number of units (packets, frames, datagrams, etc.) dropped by the network stack, which can be used to calculate the throughput of
    /// the network and identify potential issues with the network (receive side)
    size_t units_dropped;
};

/// The Throughput struct represents the throughput of different layers of the network stack, which can be used to monitor the performance of the
/// network.
struct Throughput final {
    ComponentThroughput mac;     ///< The throughput of the MAC layer, which can be used to monitor the performance of the network stack.
    ComponentThroughput arp;     ///< The throughput of the ARP layer, which can be used to monitor the performance of the network stack.
    ComponentThroughput ip;      ///< The throughput of the IP layer, which can be used to monitor the performance of the network stack.
    ComponentThroughput udp;     ///< The throughput of the UDP layer, which can be used to monitor the performance of the network stack.
    ComponentThroughput icmp;    ///< The throughput of the ICMP layer, which can be used to monitor the performance of the network stack.
    ComponentThroughput igmp;    ///< The throughput of the IGMP layer, which can be used to monitor the performance of the network stack.
    /// The throughput of unknown layers, which can be used to monitor the performance of the network stack and identify potential
    /// issues with the network (e.g., if there is a high throughput of unknown layers, it could indicate that there are a lot of
    /// malformed packets or unsupported protocols being received by the network stack).
    ComponentThroughput unknown;
};

}    // namespace net
}    // namespace jarnax

#endif    // JARNAX_NET_TYPES__HPP_

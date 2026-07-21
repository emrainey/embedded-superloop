#ifndef JARNAX_NET_ARP_ENTRY_HPP
#define JARNAX_NET_ARP_ENTRY_HPP

/// @file
/// The ARP Entry Declaration

#include "jarnax/net/eui/Address.hpp"
#include "jarnax/net/ip/v4/Address.hpp"

#include "jarnax/net/configuration.hpp"

#include <array>

namespace jarnax {
namespace net {
namespace arp {

/// An ARP Entry represents a mapping of an IP address to a MAC address, which is used by the ARP protocol to resolve IP addresses to MAC addresses
/// for communication on the local network.
struct Entry final {
    constexpr Entry()
        : ipv4{}
        , mac{{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
        , ttl{0} {}
    /// Parameterized Constructor for constant references
    constexpr Entry(ip::v4::Address const& ipv4_address, eui48::Address const& mac_address, uint32_t time_to_live)
        : ipv4{ipv4_address}
        , mac{mac_address}
        , ttl{time_to_live} {}

    Entry(Entry const&) = default;

    /// The IPv4 address associated with this ARP entry, which is used to identify the device on the network and is the key for the ARP table.
    ip::v4::Address ipv4;
    /// The MAC address associated with this ARP entry, which is used to identify the device on the local network and is the value for the ARP table.
    eui48::Address mac;
    /// The time-to-live (TTL) for this ARP entry, which indicates how long the entry should be considered valid before it is expired and removed from
    /// the ARP table. The TTL is typically measured in seconds, and it can be used to ensure that the ARP table does not become stale with outdated
    /// entries, which can lead to communication issues on the network.
    uint32_t ttl;

    /// Checks if the ARP entry is valid, which can be determined by checking if the TTL is greater than 0. If the TTL is 0, it means that the entry
    /// has expired and should be removed from the ARP table.
    bool IsValid() const { return ttl > 0; }

    /// Equality operator for ARP entries, which can be used to compare two ARP entries for equality. Two ARP entries are considered equal if they
    /// have the same
    bool operator==(Entry const& other) const {
        // both must be valid and have the same IPv4 and MAC addresses to be considered equal
        if (not IsValid() or not other.IsValid()) {
            return false;
        }
        return ipv4 == other.ipv4 and mac == other.mac;
    }

    /// Assignment operator for ARP entries, which can be used to assign one ARP entry to another. This allows for easy updating of ARP entries in the
    /// ARP table when new information is received (e.g., when a new ARP reply is received with updated MAC address information for an IP address).
    Entry& operator=(Entry const& other) {
        if (this != &other) {
            ipv4 = other.ipv4;
            mac = other.mac;
            ttl = other.ttl;
        }
        return *this;
    }

    /// Move Assignment operator for ARP entries, which is deleted to prevent moving of ARP entries. This is because ARP entries are typically stored
    /// in a fixed-size array (the ARP table), and moving an entry could lead to issues with the integrity of the ARP table (e.g., if an entry is
    /// moved out of the table, it could leave a gap in the table that could lead to incorrect behavior when looking up entries).
    Entry& operator=(Entry&&) = delete;

    /// Equality operators for comparing an ARP entry to an IPv4 address, which can be used to quickly check if an ARP entry matches a given IPv4
    /// address. This can be useful when looking up entries in the ARP table based on an IPv4 address.
    bool operator==(ip::v4::Address const& ipv4_address) const { return IsValid() and ipv4 == ipv4_address; }

    /// Equality operator for comparing an ARP entry to a MAC address, which can be used to quickly check if an ARP entry matches a given MAC address.
    /// This can be useful when looking up entries in the ARP table based on a MAC address.
    bool operator==(eui48::Address const& mac_address) const { return IsValid() and mac == mac_address; }

    /// Clears the ARP entry by setting the TTL to 0, which effectively invalidates the entry and indicates that it should be removed from the ARP
    /// table.
    void Clear() {
        ttl = 0;
        ipv4 = ip::v4::Address{};    // reset to default value
        mac = eui48::Address{{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
    }

    /// Decrements the TTL of the ARP entry by 1, which can be used to simulate the passage of time and the expiration of ARP entries in the ARP
    /// table. When the TTL reaches 0, the entry is considered expired and should be removed from the ARP table.
    void DecrementTTL() {
        if (ttl > 0) {
            --ttl;
        }
    }
};

}    // namespace arp
}    // namespace net
}    // namespace jarnax

#endif    // JARNAX_NET_ARP_ENTRY_HPP

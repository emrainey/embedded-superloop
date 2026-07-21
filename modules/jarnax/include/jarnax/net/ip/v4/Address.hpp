#ifndef JARNAX_NET_IP_V4_ADDRESS_HPP
#define JARNAX_NET_IP_V4_ADDRESS_HPP

#include <cstdint>
#include <limits>
#if defined(UNITTEST)
#include <ostream>
#endif

namespace jarnax {
namespace net {
namespace ip {
namespace v4 {

/// @brief An IPv4 Address
/// @note Always kept in network order (big endian) for ease of use with hardware and network protocols
union Address {
public:
    constexpr Address()
        : Address{0, 0, 0, 0} {}
    constexpr Address(std::uint8_t a, std::uint8_t b, std::uint8_t c, std::uint8_t d)
        : octets{a, b, c, d} {}
    constexpr Address(std::uint32_t addr)
        : Address{
              static_cast<std::uint8_t>((addr >> 24) & 0xFF),
              static_cast<std::uint8_t>((addr >> 16) & 0xFF),
              static_cast<std::uint8_t>((addr >> 8) & 0xFF),
              static_cast<std::uint8_t>(addr & 0xFF)
          } {}

    constexpr Address(Address const& other) = default;
    constexpr Address& operator=(Address const& other) = default;

    constexpr Address(Address&& other) = default;
    constexpr Address& operator=(Address&& other) = default;

    /// @brief Checks if this address is a "this" network address (i.e. in the 0.x.x.x range)
    constexpr bool IsThisNetwork() const { return (octets.a == 0); }

    /// @brief Checks if this address is a local address (i.e. in the 127.x.x.x range)
    constexpr bool IsLocal() const {
        return (octets.a == 0b01111111);    // 127 in decimal
    }

    /// @brief Checks if this address is a multicast address (i.e. in the 224.x.x.x to 239.x.x.x range)
    constexpr bool IsMulticast() const {
        return (octets.a >= 0b11100000) && (octets.a <= 0b11101111);    // 224 to 239 in decimal
    }

    /// @brief Checks if this address is a broadcast address (i.e. is the 255.255.255.255)
    constexpr bool IsBroadcast() const {
        return (octets.a == 0b11111111) && (octets.b == 0b11111111) && (octets.c == 0b11111111) && (octets.d == 0b11111111);
    }

    /// @brief Checks if this address is a private address (i.e. in the 10.x.x.x, 172.16.x.x to 172.31.x.x, or 192.168.x.x ranges)
    constexpr bool IsPrivate() const {
        return (octets.a == 0b00001010) ||                                                              // 10 in decimal
               ((octets.a == 0b10101100) && (octets.b >= 0b00010000) && (octets.b <= 0b00011111)) ||    // 172.16 to 172.31 in decimal
               ((octets.a == 0b11000000) && (octets.b == 0b10101000));                                  // 192.168 in decimal
    }

    /// @brief Checks if this address is a link-local address (i.e. in the 169.254.x.x range)
    constexpr bool IsLinkLocal() const {
        return (octets.a == 0b10101001) and (octets.b == 0b11111110);    // 169.254 in decimal
    }

    /// @brief Checks if this address is a Shared Address (i.e. in the 100.64.x.x to 100.127.x.x range)
    constexpr bool IsShared() const {
        return (octets.a == 0b01100100) and (octets.b >= 0b01000000) and (octets.b <= 0b01111111);    // 100.64 to 100.127 in decimal
    }

    /// @brief Checks if this address is a reserved address (i.e. in the 240.x.x.x to 255.x.x.x range)
    constexpr bool IsReserved() const {
        return (octets.a >= 0b11110000);    // 240 to 255 in decimal
    }

    /// @brief Checks if the address is identical to another address
    constexpr bool operator==(Address const& other) const {
        return octets.a == other.octets.a && octets.b == other.octets.b && octets.c == other.octets.c && octets.d == other.octets.d;
    }

    /// @brief Checks if the address is different from another address
    constexpr bool operator!=(Address const& other) const { return !(*this == other); }

    /// @brief A bitwise flip of the address (i.e. the inverse).
    /// Useful for flipping masks to get broadcast addresses and such.
    constexpr Address operator~() const {
        return Address{
            static_cast<uint8_t>(~octets.a), static_cast<uint8_t>(~octets.b), static_cast<uint8_t>(~octets.c), static_cast<uint8_t>(~octets.d)
        };
    }

    /// @brief Extract the address as a single uint32_t value
    explicit operator std::uint32_t() const {
        // return a 32-bit representation of the address from the bytes
        return (static_cast<std::uint32_t>(octets.a) << 24) | (static_cast<std::uint32_t>(octets.b) << 16) |
               (static_cast<std::uint32_t>(octets.c) << 8) | static_cast<std::uint32_t>(octets.d);
    }

#if defined(UNITTEST)
    /// @brief The Stream Print for Addresses for unit testing purposes
    friend std::ostream& operator<<(std::ostream& os, Address const& addr) {
        os << static_cast<int>(addr.octets.a) << "." << static_cast<int>(addr.octets.b) << "." << static_cast<int>(addr.octets.c) << "."
           << static_cast<int>(addr.octets.d);
        return os;
    }
#endif

protected:
    //+=== MEMORY LAYOUT ===+
    /// The octets of the address in network order (big endian)
    struct {
        std::uint8_t a;
        std::uint8_t b;
        std::uint8_t c;
        std::uint8_t d;
    } octets;
    //+=== MEMORY LAYOUT ===+
};
static_assert(sizeof(Address) == sizeof(std::uint32_t), "Address must be 4 bytes in size");

/// The default route for IPv4
constexpr static Address default_route{0, 0, 0, 0};

/// The common IPv4 address for limited broadcast
constexpr static Address limited_broadcast{255, 255, 255, 255};

/// @brief Used by IANA for "this" network (but we can't use that name because it's a reserved keyword in C++)
namespace this_ {
/// The common IPv4 address for "this" network
constexpr static Address network{0, 0, 0, 0};
/// The common broadcast address for "this" network
constexpr static Address broadcast{0, 255, 255, 255};
/// The common subnet mask prefix for this network
constexpr static uint8_t prefix = 8;
}    // namespace this_

/// @brief The namespace for Shared Addresses
namespace shared {
/// The common IPv4 address for shared addresses
constexpr static Address network{100, 64, 0, 0};
constexpr static Address broadcast{100, 127, 255, 255};
/// The common subnet mask prefix for this network
constexpr static uint8_t prefix = 10U;
static_assert(network.IsShared(), "Network address should be shared");
static_assert(broadcast.IsShared(), "Broadcast address should be shared");
}    // namespace shared

/// @brief The namespace for local addresses and loopback addresses
namespace local {
/// The common IPv4 address for localhost
constexpr static Address host{127, 0, 0, 1};
/// The common network range for localhost
constexpr static Address network{127, 0, 0, 0};
/// The common broadcast address for localhost
constexpr static Address broadcast{127, 255, 255, 255};
/// The common subnet mask prefix for local addresses
constexpr static uint8_t prefix = 8U;
/// Ensure that everything checks out
static_assert(host.IsLocal(), "Host address should be local");
static_assert(network.IsLocal(), "Network address should be local");
static_assert(broadcast.IsLocal(), "Broadcast address should be local");
}    // namespace local

/// @brief The namespace for Class A Addresses
namespace A {
constexpr static Address network{10, 0, 0, 0};
constexpr static Address broadcast{10, 255, 255, 255};
/// The common subnet mask prefix for this network
constexpr static uint8_t prefix = 8U;
static_assert(network.IsPrivate(), "Network address should be private");
static_assert(broadcast.IsPrivate(), "Broadcast address should be private");
}    // namespace A

/// @brief The namespace for Class B Addresses
namespace B {
constexpr static Address network{172, 16, 0, 0};
constexpr static Address broadcast{172, 31, 255, 255};
/// The common subnet mask prefix for this network
constexpr static uint8_t prefix = 12U;
static_assert(network.IsPrivate(), "Network address should be private");
static_assert(broadcast.IsPrivate(), "Broadcast address should be private");
}    // namespace B

/// @brief The namespace for Class C Addresses
namespace C {
constexpr static Address network{192, 168, 0, 0};
constexpr static Address broadcast{192, 168, 255, 255};
/// The common subnet mask prefix for this network
constexpr static uint8_t prefix = 16U;
static_assert(network.IsPrivate(), "Network address should be private");
static_assert(broadcast.IsPrivate(), "Broadcast address should be private");
}    // namespace C

/// @brief The namespace for link-local addresses
namespace link {
/// The common IPv4 address for link-local addresses
constexpr static Address network{169, 254, 0, 0};
constexpr static Address broadcast{169, 254, 255, 255};
/// The common subnet mask prefix for this network
constexpr static uint8_t prefix = 16U;
static_assert(network.IsLinkLocal(), "Network address should be link-local");
static_assert(broadcast.IsLinkLocal(), "Broadcast address should be link-local");
}    // namespace link

/// @brief The namespace for multicast features
namespace multicast {
/// @brief The common IPv4 network address for multicast addresses
constexpr static Address network{224, 0, 0, 0};
/// @brief The common IPv4 broadcast address for multicast addresses
/// @note realistically this is never used since multicast addresses don't really have a
/// broadcast address, but it's useful for testing and such
constexpr static Address broadcast{239, 255, 255, 255};
static_assert(network.IsMulticast(), "Network address should be multicast");
static_assert(broadcast.IsMulticast(), "Broadcast address should be multicast");
/// The common subnet mask prefix for this network
constexpr static uint8_t prefix = 4U;
/// @brief The all-systems multicast address
constexpr static Address all{224, 0, 0, 1};
static_assert(all.IsMulticast(), "All-systems address should be multicast");
/// @brief The common IPv4 address for mDNS
constexpr static Address dns{224, 0, 0, 251};
static_assert(dns.IsMulticast(), "DNS address should be multicast");
/// @brief The common IPv4 multicast address for NTP
constexpr static Address ntp{224, 0, 1, 1};
static_assert(ntp.IsMulticast(), "NTP address should be multicast");
}    // namespace multicast

/// @brief A helper function to create a mask using an address divided by a prefix length
/// The prefix is the number of bits in the mask, so a prefix of 24 would create a mask of
/// 11111111.11111111.11111111.00000000 (or 0xFFFFFF00 in hexadecimal)
/// If the prefix length is greater than 32, it will be clamped to 32 (i.e. a prefix of 33 or more will create a mask of all 1s)
constexpr Address operator/(Address const& ip, uint8_t prefix_length) {
    constexpr uint8_t bits = sizeof(std::uint32_t) * 8U;
    constexpr uint32_t limit = std::numeric_limits<uint32_t>::max();
    prefix_length = (prefix_length > bits) ? bits : prefix_length;
    if (prefix_length == 0) {
        return Address{0};    // A prefix of 0 means no bits are in the network portion, so the mask is all 0s
    }
    std::uint32_t mask_value = (limit << (bits - prefix_length));
    return Address(static_cast<std::uint32_t>(ip) & mask_value);
}

/// @brief A helper function to apply a mask to an address to then check against the network address for a subnet
constexpr Address operator&(Address const& ip, Address const& mask) {
    return Address(static_cast<std::uint32_t>(ip) & static_cast<std::uint32_t>(mask));
}

/// @brief A helper function to OR two addresses together, which is useful for calculating broadcast addresses and such
constexpr Address operator|(Address const& ip, Address const& other) {
    return Address(static_cast<std::uint32_t>(ip) | static_cast<std::uint32_t>(other));
}

namespace local {
/// The common subnet mask for local addresses (i.e. 127.x.x.x)
constexpr static Address mask{255, 0, 0, 0};    // /8
}    // namespace local

namespace this_ {
/// The common subnet mask for "this" network addresses (i.e. 0.x.x.x)
constexpr static Address mask{255, 0, 0, 0};    /// /8 since the entire 0.x.x.x range is reserved for "this" network
}    // namespace this_

namespace multicast {
/// The common subnet mask for multicast addresses (i.e. 224.x.x.x to 239.x.x.x)
constexpr static Address mask{240, 0, 0, 0};    // /4
}    // namespace multicast

namespace A {
/// The common subnet mask for Class A addresses (i.e. 10.x.x.x)
constexpr static Address mask{255, 0, 0, 0};    // /8
}    // namespace A

namespace B {
/// The common subnet mask for Class B addresses (i.e. 172.16.x.x to 172.31.x.x)
constexpr static Address mask{255, 240, 0, 0};    // /12
}    // namespace B

namespace C {
/// The common subnet mask for Class C addresses (i.e. 192.168.x.x)
constexpr static Address mask{255, 255, 0, 0};    // /16
}    // namespace C

namespace link {
/// The common subnet mask for link-local addresses (i.e. 169.254.x.x
constexpr static Address mask{255, 255, 0, 0};    // /16
}    // namespace link

namespace shared {
/// The common subnet mask for shared addresses (i.e. 100.64.x.x to 100.127.x.x)
constexpr static Address mask{255, 192, 0, 0};    // /10
}    // namespace shared

}    // namespace v4
}    // namespace ip
}    // namespace net
}    // namespace jarnax

#endif    // JARNAX_NET_IP_V4_ADDRESS_HPP

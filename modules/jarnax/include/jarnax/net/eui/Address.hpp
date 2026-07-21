#ifndef JARNAX_NET_EUI48_ADDRESS_HPP
#define JARNAX_NET_EUI48_ADDRESS_HPP

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace jarnax {
namespace net {
namespace eui {

template <size_t OUI_SIZE, size_t NIC_SIZE>
class Address_ {
public:
    constexpr static size_t OrganizationallyUniqueIdentifierSize = OUI_SIZE;
    constexpr static size_t NetworkInterfaceControllerSpecificSize = NIC_SIZE;
    constexpr static size_t TotalSize = OUI_SIZE + NIC_SIZE;
    using OrganizationallyUniqueIdentifier = std::array<uint8_t, OrganizationallyUniqueIdentifierSize>;
    using NetworkInterfaceControllerSpecific = std::array<uint8_t, NetworkInterfaceControllerSpecificSize>;

    /// Default Constructor initializes the address to all zeros
    constexpr Address_()
        : bytes_{} {}

    /// Construct an EUI-48 address from a std::array of bytes
    explicit constexpr Address_(std::array<uint8_t, TotalSize> const& bytes)
        : bytes_{bytes} {}

    /// Construct an address from individual byte values.
    ///
    /// This overload is enabled with SFINAE only when three conditions are met:
    /// the caller provides exactly TotalSize constructor arguments, every
    /// argument is convertible to uint8_t, and the resulting overload can be
    /// formed for this Address_ specialization. When any of those conditions is
    /// false, this constructor is removed from overload resolution and the
    /// array-based constructor remains the available construction path.
    template <
        typename... Bytes, std::enable_if_t<(sizeof...(Bytes) == TotalSize) && (std::conjunction_v<std::is_convertible<Bytes, uint8_t>...>), int> = 0>
    explicit constexpr Address_(Bytes... bytes)
        : bytes_{{static_cast<uint8_t>(bytes)...}} {}

    constexpr OrganizationallyUniqueIdentifier GetOUI() const {
        OrganizationallyUniqueIdentifier oui{};
        std::copy(bytes_.begin(), bytes_.begin() + OrganizationallyUniqueIdentifierSize, oui.begin());
        return oui;
    }

    constexpr NetworkInterfaceControllerSpecific GetNIC() const {
        NetworkInterfaceControllerSpecific nic{};
        std::copy(bytes_.begin() + OrganizationallyUniqueIdentifierSize, bytes_.end(), nic.begin());
        return nic;
    }

    constexpr bool operator==(Address_ const& other) const { return bytes_ == other.bytes_; }

    constexpr bool operator!=(Address_ const& other) const { return not(*this == other); }

    constexpr bool IsUnicast() const { return (bytes_[0] & 0b1) == 0b0; }

    /// Multicast addresses have the I/G bit (the least significant bit of the first byte) set to 1, which indicates that the address is a multicast
    /// address.
    constexpr bool IsMulticast() const { return (bytes_[0] & 0b1) == 0b1; }

    /// Locally Administered addresses have the U/L bit (the second least significant bit of the first byte) set to 1, which indicates that the
    /// address is
    constexpr bool IsLocallyAdministered() const {
        if constexpr (InvertedUL) {
            return (bytes_[0] & 0b10) == 0b00;    // For EUI-64 addresses, the U/L bit is inverted, so we check if it's 0 instead of 1
        } else {
            return (bytes_[0] & 0b10) == 0b10;    // For EUI-48 addresses, the U/L bit is not inverted, so we check if it's 1
        }
    }
    /// Extended Local addresses have the first byte set to 0xXA
    constexpr bool IsExtendedLocal() const { return (bytes_[0] & 0x0F) == 0x0A; }
    /// Standard Assigned Local addresses have the first byte set to 0xXE
    constexpr bool IsStandardAssignedLocal() const { return (bytes_[0] & 0x0F) == 0x0E; }
    /// Administered Local addresses have the first byte set to 0xX2,
    constexpr bool IsAdministeredLocal() const { return (bytes_[0] & 0x0F) == 0x02; }
    /// Reserved Local addresses have the first byte set to 0xX6
    constexpr bool IsReservedLocal() const { return (bytes_[0] & 0x0F) == 0x06; }
    /// Universally Administered addresses have the X bit set to 0, which means they are not locally administered and are assigned by the IEEE
    /// Registration Authority.
    constexpr bool IsUniversallyAdministered() const {
        if constexpr (InvertedUL) {
            return (bytes_[0] & 0b10) == 0b10;    // For EUI-64 addresses, the U/L bit is inverted, so we check if it's 1 instead of 0
        } else {
            return (bytes_[0] & 0b10) == 0b00;
        }
    }

    /// Allows access to the raw bytes of the address for serialization or other purposes. The bytes are stored in network byte order (big-endian),
    /// which is the standard byte order for EUI addresses.
    /// @warning Will not throw an exception or assert if the index is out of bounds, but will instead return a reference to a dummy variable. This is
    /// not ideal, but it prevents crashes in case of out-of-bounds access.
    constexpr uint8_t& operator[](size_t index) {
        if (index >= TotalSize) {
            return dummy_;
        }
        return bytes_[index];
    }

    /// Const version of the operator[] for read-only access to the bytes of the address.
    /// @warning Will not throw an exception or assert if the index is out of bounds, but will instead return 0. This is not ideal, but it prevents
    /// crashes in case of out-of-bounds access.
    constexpr uint8_t operator[](size_t index) const {
        if (index >= TotalSize) {
            return 0;    // Return 0 if the index is out of bounds to avoid undefined behavior. This is not ideal, but it prevents crashes in case of
                         // out-of-bounds access.
        }
        return bytes_[index];
    }

protected:
    /// The U/L bit is inverted for EUI-64 addresses, so we need to account for that when determining if an
    /// address is locally administered or universally administered
    /// @see RFC 4291, Section 2.5.1: https://datatracker.ietf.org/doc/html/rfc4291#section-2.5.1
    constexpr static bool InvertedUL = (TotalSize == 6) ? false : true;

    /// A dummy variable used for out-of-bounds access in the operator[] overloads. This is not ideal, but it prevents
    /// crashes in case of out-of-bounds access.
    inline static uint8_t dummy_ = 0;

    /// The bytes of the address, stored in a fixed-size array. The size of the array is determined by the OUI and NIC sizes specified in the template
    /// parameters.
    std::array<uint8_t, TotalSize> bytes_{};
};

}    // namespace eui

namespace eui48 {
/// Also known as MAC-48 or just MAC addresses, EUI-48 addresses are 48 bits long and consist of a 24-bit OUI and a 24-bit NIC. They are commonly used
/// for network interfaces and other hardware devices.
using Address = eui::Address_<3, 3>;
static_assert(sizeof(Address) == 6);
static_assert(alignof(Address) == 1);

/// The invalid address is a special address that is used to indicate an invalid or uninitialized address. In EUI-48, the invalid address is
/// represented by all bits set to 0 (i.e., 00:00:00:00:00:00).
constexpr static Address invalid{0x00, 0x00, 0x00, 0x00, 0x00, 0x00};    // An invalid address is all bits set to 0

/// The broadcast address is a special address that is used to send a message to all devices on the network. In EUI-48, the broadcast address is
/// represented by all bits set to 1 (i.e., FF:FF:FF:FF:FF:FF).
constexpr static Address broadcast{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};    // The broadcast address is all bits set to 1

/// The OUI for addresses assigned by the IEEE Registration Authority is 00-00-00
constexpr static Address::OrganizationallyUniqueIdentifier IEEERegistrationAuthority{{0x00, 0x00, 0x00}};

/// The OUI for Multicast addresses is 01-00-5E
constexpr static Address::OrganizationallyUniqueIdentifier Multicast{{0x01, 0x00, 0x5E}};
}    // namespace eui48

namespace eui64 {
/// EUI-64 addresses are 64 bits long and consist of a 24-bit OUI and a 40-bit NIC. They are commonly used for network interfaces in IPv6 and other
/// applications that require a larger address space.
using Address = eui::Address_<3, 5>;
static_assert(sizeof(Address) == 8);
static_assert(alignof(Address) == 1);

/// The invalid address is a special address that is used to indicate an invalid or uninitialized address. In EUI-48, the invalid address is
/// represented by all bits set to 0 (i.e., 00:00:00:00:00:00:00:00).
constexpr static Address invalid{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};    // An invalid address is all bits set to 0

/// The broadcast address is a special address that is used to send a message to all devices on the network. In EUI-48, the broadcast address is
/// represented by all bits set to 1 (i.e., FF:FF:FF:FF:FF:FF:FF:FF).
constexpr static Address broadcast{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};    // The broadcast address is all bits set to 1
}    // namespace eui64

}    // namespace net
}    // namespace jarnax

#endif    // JARNAX_NET_EUI48_ADDRESS_HPP

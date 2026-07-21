#ifndef JARNAX_NET_EUI48_ADDRESS_HPP
#define JARNAX_NET_EUI48_ADDRESS_HPP

#include <array>
#include <cstdint>

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

    /// Construct an EUI-48 address from a byte array
    explicit constexpr Address_(std::array<uint8_t, TotalSize> const& bytes)
        : bytes_{bytes} {}

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

protected:
    /// The U/L bit is inverted for EUI-64 addresses, so we need to account for that when determining if an
    /// address is locally administered or universally administered
    /// @see RFC 4291, Section 2.5.1: https://datatracker.ietf.org/doc/html/rfc4291#section-2.5.1
    constexpr static bool InvertedUL = (TotalSize == 6) ? false : true;

    /// The bytes of the address, stored in a fixed-size array. The size of the array is determined by the OUI and NIC sizes specified in the template
    /// parameters.
    std::array<uint8_t, TotalSize> bytes_{};
};

}    // namespace eui

namespace eui48 {
/// Also known as MAC-48 or just MAC addresses, EUI-48 addresses are 48 bits long and consist of a 24-bit OUI and a 24-bit NIC. They are commonly used
/// for network interfaces and other hardware devices.
using Address = eui::Address_<3, 3>;

constexpr static Address broadcast{{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}};    // The broadcast address is all bits set to 1
}    // namespace eui48

namespace eui64 {
/// EUI-64 addresses are 64 bits long and consist of a 24-bit OUI and a 40-bit NIC. They are commonly used for network interfaces in IPv6 and other
/// applications that require a larger address space.
using Address = eui::Address_<3, 5>;
}    // namespace eui64

}    // namespace net
}    // namespace jarnax

#endif    // JARNAX_NET_EUI48_ADDRESS_HPP

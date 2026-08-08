#include <catch2/catch_test_macros.hpp>

#include <type_traits>

#include "jarnax/net/eui/Address.hpp"

TEST_CASE("EUI-48 Address Test") {
    using Address = jarnax::net::eui48::Address;
    constexpr Address address{0x00, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E};
    REQUIRE(address.GetOUI() == (Address::OrganizationallyUniqueIdentifier{{0x00, 0x1A, 0x2B}}));
    REQUIRE(address.GetNIC() == (Address::NetworkInterfaceControllerSpecific{{0x3C, 0x4D, 0x5E}}));
    REQUIRE(address.IsUnicast());
    REQUIRE_FALSE(address.IsMulticast());
    REQUIRE_FALSE(address.IsLocallyAdministered());
    REQUIRE_FALSE(address.IsExtendedLocal());
    REQUIRE_FALSE(address.IsStandardAssignedLocal());
    REQUIRE_FALSE(address.IsAdministeredLocal());
    REQUIRE_FALSE(address.IsReservedLocal());
    REQUIRE(address.IsUniversallyAdministered());
}

TEST_CASE("EUI-48 Address supports direct six-byte construction") {
    using Address = jarnax::net::eui48::Address;

    static_assert(std::is_constructible_v<Address, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t>);
    static_assert(not std::is_constructible_v<Address, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t>);

    constexpr Address address{0x10, 0x20, 0x30, 0x40, 0x50, 0x60};

    REQUIRE(address == Address{0x10, 0x20, 0x30, 0x40, 0x50, 0x60});
}

TEST_CASE("EUI-64 Address supports direct eight-byte construction") {
    using Address = jarnax::net::eui64::Address;

    static_assert(std::is_constructible_v<Address, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t>);
    static_assert(not std::is_constructible_v<Address, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t>);

    constexpr Address address{0x00, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F, 0x70};

    REQUIRE(address.GetOUI() == (Address::OrganizationallyUniqueIdentifier{{0x00, 0x1A, 0x2B}}));
    REQUIRE(address.GetNIC() == (Address::NetworkInterfaceControllerSpecific{{0x3C, 0x4D, 0x5E, 0x6F, 0x70}}));
}

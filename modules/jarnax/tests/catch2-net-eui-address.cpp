#include <catch2/catch_test_macros.hpp>
#include "jarnax/net/eui/Address.hpp"

TEST_CASE("EUI-48 Address Test") {
    using Address = jarnax::net::eui48::Address;
    constexpr Address address{{0x00, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E}};
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

#include <catch2/catch_test_macros.hpp>
#include "jarnax/net/ip/v4/Address.hpp"
#include "jarnax/net/Interface.hpp"

#include <iostream>

namespace jarnax {
namespace net {
namespace ip {
namespace v4 {

TEST_CASE("IPv4 Address Classification", "[Address]") {
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // Test the classification of different types of IPv4 addresses
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    // This Network
    constexpr Address this_host{0, 1, 2, 3};
    REQUIRE(this_host.IsThisNetwork());
    REQUIRE_FALSE(this_host.IsLocal());
    REQUIRE_FALSE(this_host.IsMulticast());
    REQUIRE_FALSE(this_host.IsBroadcast());
    REQUIRE_FALSE(this_host.IsPrivate());
    REQUIRE_FALSE(this_host.IsLinkLocal());
    REQUIRE_FALSE(this_host.IsShared());
    REQUIRE_FALSE(this_host.IsReserved());

    // Local (Loopback)
    REQUIRE_FALSE(local::host.IsThisNetwork());
    REQUIRE(local::host.IsLocal());
    REQUIRE_FALSE(local::host.IsMulticast());
    REQUIRE_FALSE(local::host.IsBroadcast());
    REQUIRE_FALSE(local::host.IsPrivate());
    REQUIRE_FALSE(local::host.IsLinkLocal());
    REQUIRE_FALSE(local::host.IsShared());
    REQUIRE_FALSE(local::host.IsReserved());

    // Multicast
    REQUIRE_FALSE(multicast::dns.IsThisNetwork());
    REQUIRE_FALSE(multicast::dns.IsLocal());
    REQUIRE(multicast::dns.IsMulticast());
    REQUIRE_FALSE(multicast::dns.IsBroadcast());
    REQUIRE_FALSE(multicast::dns.IsPrivate());
    REQUIRE_FALSE(multicast::dns.IsLinkLocal());
    REQUIRE_FALSE(multicast::dns.IsShared());
    REQUIRE_FALSE(multicast::dns.IsReserved());

    // Broadcast
    REQUIRE_FALSE(limited_broadcast.IsThisNetwork());
    REQUIRE_FALSE(limited_broadcast.IsLocal());
    REQUIRE_FALSE(limited_broadcast.IsMulticast());
    REQUIRE(limited_broadcast.IsBroadcast());
    REQUIRE_FALSE(limited_broadcast.IsPrivate());    // Broadcast is technically private since it's not routable, but it's not defined as private
    REQUIRE_FALSE(limited_broadcast.IsLinkLocal());
    REQUIRE_FALSE(limited_broadcast.IsShared());
    REQUIRE(limited_broadcast.IsReserved());    // Broadcast is also technically reserved since it's not usable for hosts
}

TEST_CASE("Masks for Networks [Masks]") {
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // Test the masks for different types of networks
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    SECTION("This Network") {
        Address network_test = this_::network / this_::prefix;
        REQUIRE(this_::network == network_test);
        Address broadcast_test = this_::network | ~this_::mask;
        REQUIRE(this_::broadcast == broadcast_test);
    }

    SECTION("Multicast") {
        Address network_test_a = multicast::network / multicast::prefix;    // Mask for /4 should be 11110000.0.0.0
        Address network_test_b = multicast::dns / multicast::prefix;        // Mask for /4 should be 11110000.0.0.0
        std::cout << "Multicast Network: " << multicast::network << " Multicast DNS: " << multicast::dns << " Multicast Network: " << network_test_a
                  << " Multicast Network: " << network_test_b << std::endl;
        REQUIRE(multicast::network == network_test_a);
        REQUIRE(multicast::network == network_test_b);
    }

    SECTION("Local (Loopback)") {
        Address network_test = local::host / local::prefix;    // Mask for /8 should be
        REQUIRE(local::network == network_test);
        Address test = local::network | ~local::mask;          // Network address should be the same as the host address since it's a /8
        REQUIRE(local::broadcast == test);
    }

    SECTION("Class A") {
        Address network_test = A::network / A::prefix;    // Mask for /8 should be  11111111.0.0.0
        REQUIRE(A::network == network_test);
        Address test = A::network | ~A::mask;             // Network address should be the same as
        REQUIRE(A::broadcast == test);
    }

    SECTION("Class B") {
        Address network_test = B::network / B::prefix;    // Mask for /12 should be 11111111.11110000.0.0
        REQUIRE(B::network == network_test);
        Address test = B::network | ~B::mask;             // Network address should be the same as
        REQUIRE(B::broadcast == test);
    }

    SECTION("Class C") {
        Address network_test = C::network / C::prefix;    // Mask for /16 should be 11111111.11111111.0.0
        REQUIRE(C::network == network_test);
        Address test = C::network | ~C::mask;             // Network address should be the same as
        REQUIRE(C::broadcast == test);
    }

    SECTION("Link-Local") {
        Address network_test = link::network / link::prefix;    // Mask for /16 should be 11111111.11111111.0.0
        REQUIRE(link::network == network_test);
        Address test = link::network | ~link::mask;             // Network address should be the same as
        REQUIRE(link::broadcast == test);
    }

    SECTION("Shared") {
        Address network_test = shared::network / shared::prefix;    // Mask for /10 should be 11111111.11000000.0.0
        REQUIRE(shared::network == network_test);
        Address test = shared::network | ~shared::mask;             // Network address should be the same as
        REQUIRE(shared::broadcast == test);
    }
}

TEST_CASE("Interface Test") {
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // Test the Interface class and its methods
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    SECTION("Invalid Interface") {
        // Invalid because the address is the default route and the netmask is invalid
        Interface iface{{0, 0, 0, 0}, {0, 0, 0, 0}};
        REQUIRE_FALSE(iface.IsValid());

        // Invalid because the address is the broadcast address for the subnet
        Interface iface2{{192, 168, 1, 255}, {255, 255, 255, 0}};
        REQUIRE_FALSE(iface2.IsValid());

        // Invalid because the address is a multicast address
        Interface iface3{{224, 0, 0, 1}, {240, 0, 0, 0}};
        REQUIRE_FALSE(iface3.IsValid());
    }

    SECTION("Local Host Interface") {
        Interface iface{local::host, local::mask};
        REQUIRE(iface.IsValid());

        REQUIRE(iface.CouldReceive(local::host));               // Should receive packets from itself
        REQUIRE(iface.CouldReceive(local::network));            // Should receive packets from the network address since it's in the same subnet
        REQUIRE(iface.CouldReceive(local::broadcast));          // Should receive packets from the broadcast address since it's in the same subnet
        REQUIRE_FALSE(iface.CouldReceive({192, 168, 1, 1}));    // Should not receive packets from an address outside of the subnet
        // Should receive packets from the limited broadcast address since it's a special case that should be received by all interfaces
        REQUIRE(iface.CouldReceive(limited_broadcast));
        // Should receive packets from multicast addresses since it's a special case that should be received by all interfaces
        REQUIRE(iface.CouldReceive(multicast::dns));
        // Should receive packets from multicast addresses since it's a special case that should be received by all interfaces
        REQUIRE(iface.CouldReceive(multicast::all));
    }

    SECTION("Link Local Interface") {
        Interface iface{{169, 254, 1, 1}, link::mask};
        REQUIRE(iface.IsValid());

        REQUIRE(iface.CouldReceive({169, 254, 1, 2}));          // Should receive packets from the same subnet
        REQUIRE(iface.CouldReceive(link::broadcast));           // Should receive packets from the broadcast address since it's in the same subnet
        REQUIRE_FALSE(iface.CouldReceive({192, 168, 1, 1}));    // Should not receive packets from an address outside of the subnet
        // Should receive packets from the limited broadcast address since it's a special case that should be received by all interfaces
        REQUIRE(iface.CouldReceive(limited_broadcast));
        // Should receive packets from multicast addresses since it's a special case that should be received by all interfaces
        REQUIRE(iface.CouldReceive(multicast::dns));
        // Should receive packets from multicast addresses since it's a special case that should be received by all interfaces
        REQUIRE(iface.CouldReceive(multicast::all));
    }

    SECTION("Class A Interface") {
        Interface iface{{10, 9, 10, 1}, A::mask};
        REQUIRE(iface.IsValid());

        REQUIRE(iface.CouldReceive({10, 9, 10, 2}));            // Should receive packets from the same subnet
        REQUIRE(iface.CouldReceive(A::broadcast));              // Should receive packets from the broadcast address since it's in the same subnet
        REQUIRE_FALSE(iface.CouldReceive({192, 168, 1, 1}));    // Should not receive packets from an address outside of the subnet
        // Should receive packets from the limited broadcast address since it's a special case that should be received by all interfaces
        REQUIRE(iface.CouldReceive(limited_broadcast));
        // Should receive packets from multicast addresses since it's a special case that should be received by all interfaces
        REQUIRE(iface.CouldReceive(multicast::dns));
        // Should receive packets from multicast addresses since it's a special case that should be received by all interfaces
        REQUIRE(iface.CouldReceive(multicast::all));
    }

    SECTION("Class B Interface") {
        Interface iface{{172, 16, 0, 1}, B::mask};
        REQUIRE(iface.IsValid());

        REQUIRE(iface.CouldReceive({172, 16, 0, 2}));           // Should receive packets from the same subnet
        REQUIRE(iface.CouldReceive(B::broadcast));              // Should receive packets from the broadcast address since it's in the same subnet
        REQUIRE_FALSE(iface.CouldReceive({192, 168, 1, 1}));    // Should not receive packets from an address outside of the subnet
        // Should receive packets from the limited broadcast address since it's a special case that should be received by all interfaces
        REQUIRE(iface.CouldReceive(limited_broadcast));
        // Should receive packets from multicast addresses since it's a special case that should be received by all interfaces
        REQUIRE(iface.CouldReceive(multicast::dns));
        // Should receive packets from multicast addresses since it's a special case that should be received by all interfaces
        REQUIRE(iface.CouldReceive(multicast::all));
    }

    SECTION("Class C Interface") {
        Interface iface{{192, 168, 1, 1}, C::mask};
        REQUIRE(iface.IsValid());

        REQUIRE(iface.CouldReceive({192, 168, 1, 2}));          // Should receive packets from the same subnet
        REQUIRE(iface.CouldReceive(C::broadcast));              // Should receive packets from the broadcast address since it's in the same subnet
        REQUIRE_FALSE(iface.CouldReceive({192, 167, 1, 1}));    // Should not receive packets from an address outside of the subnet
        // Should receive packets from the limited broadcast address since it's a special case that should be received by all interfaces
        REQUIRE(iface.CouldReceive(limited_broadcast));
        // Should receive packets from multicast addresses since it's a special case that should be received by all interfaces
        REQUIRE(iface.CouldReceive(multicast::dns));
        // Should receive packets from multicast addresses since it's a special case that should be received by all interfaces
        REQUIRE(iface.CouldReceive(multicast::all));
    }
}

}    // namespace v4
}    // namespace ip
}    // namespace net
}    // namespace jarnax

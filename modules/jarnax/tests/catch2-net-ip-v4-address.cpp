#include <catch2/catch_test_macros.hpp>
#include "core/Status.hpp"
#include "jarnax/net/Interface.hpp"
#include "jarnax/net/ethernet/Driver.hpp"
#include "jarnax/net/ip/v4/Address.hpp"

#include <iostream>

namespace jarnax {
namespace net {

/// A mock driver for testing the Interface class without needing to implement a full Ethernet driver. This allows us to test the logic of the
/// Interface class in isolation.
class MockDriver final : public ethernet::Driver {
public:
    MockDriver() = default;
    ~MockDriver() = default;
    core::Status Initialize(void) override { return core::Status{}; }
    bool Execute(void) override { return true; }
    core::Status Configure(Addresses const&) override { return core::Status{}; }
    jarnax::net::eui48::Address GetMacAddress(size_t) const override { return jarnax::net::eui48::Address{}; }
    core::Status Transmit(ethernet::Frame*) override { return core::Status{}; }
    core::Status Receive(Listener&) override { return core::Status{}; }
    bool IsReady() const override { return true; }
};

namespace ip {
namespace v4 {

TEST_CASE("IPv4 Address Classification", "[Address]") {
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
    REQUIRE_FALSE(limited_broadcast.IsPrivate());
    REQUIRE_FALSE(limited_broadcast.IsLinkLocal());
    REQUIRE_FALSE(limited_broadcast.IsShared());
    REQUIRE(limited_broadcast.IsReserved());
}

TEST_CASE("IPv4 Address Private Range Classification", "[Address][Private]") {
    // Class A private: 10.x.x.x
    REQUIRE(Address{10, 0, 0, 0}.IsPrivate());
    REQUIRE(Address{10, 0, 0, 1}.IsPrivate());
    REQUIRE(Address{10, 255, 255, 255}.IsPrivate());

    // Class B private: 172.16.x.x - 172.31.x.x
    REQUIRE(Address{172, 16, 0, 0}.IsPrivate());
    REQUIRE(Address{172, 16, 0, 1}.IsPrivate());
    REQUIRE(Address{172, 31, 255, 255}.IsPrivate());

    // Class B boundaries: just outside the range
    REQUIRE_FALSE(Address{172, 15, 255, 255}.IsPrivate());
    REQUIRE_FALSE(Address{172, 32, 0, 0}.IsPrivate());

    // Class C private: 192.168.x.x
    REQUIRE(Address{192, 168, 0, 0}.IsPrivate());
    REQUIRE(Address{192, 168, 0, 1}.IsPrivate());
    REQUIRE(Address{192, 168, 255, 255}.IsPrivate());

    // Class C boundaries: just outside
    REQUIRE_FALSE(Address{192, 167, 255, 255}.IsPrivate());
    REQUIRE_FALSE(Address{192, 169, 0, 0}.IsPrivate());

    // Non-private addresses
    REQUIRE_FALSE(Address{8, 8, 8, 8}.IsPrivate());
    REQUIRE_FALSE(Address{1, 1, 1, 1}.IsPrivate());
}

TEST_CASE("IPv4 Address LinkLocal Classification", "[Address][LinkLocal]") {
    REQUIRE(Address{169, 254, 0, 0}.IsLinkLocal());
    REQUIRE(Address{169, 254, 0, 1}.IsLinkLocal());
    REQUIRE(Address{169, 254, 255, 255}.IsLinkLocal());

    // Boundaries
    REQUIRE_FALSE(Address{169, 253, 255, 255}.IsLinkLocal());
    REQUIRE_FALSE(Address{169, 255, 0, 0}.IsLinkLocal());
    REQUIRE_FALSE(Address{168, 254, 0, 0}.IsLinkLocal());
    REQUIRE_FALSE(Address{170, 254, 0, 0}.IsLinkLocal());
}

TEST_CASE("IPv4 Address Shared Classification", "[Address][Shared]") {
    REQUIRE(Address{100, 64, 0, 0}.IsShared());
    REQUIRE(Address{100, 64, 0, 1}.IsShared());
    REQUIRE(Address{100, 127, 255, 255}.IsShared());

    // Boundaries
    REQUIRE_FALSE(Address{100, 63, 255, 255}.IsShared());
    REQUIRE_FALSE(Address{100, 128, 0, 0}.IsShared());
    REQUIRE_FALSE(Address{99, 64, 0, 0}.IsShared());
    REQUIRE_FALSE(Address{101, 64, 0, 0}.IsShared());
}

TEST_CASE("IPv4 Address Reserved and Multicast Boundaries", "[Address][Reserved][Multicast]") {
    // Reserved range: 240.x.x.x - 255.x.x.x
    REQUIRE(Address{240, 0, 0, 0}.IsReserved());
    REQUIRE(Address{240, 0, 0, 1}.IsReserved());
    REQUIRE(Address{255, 255, 255, 254}.IsReserved());
    REQUIRE(Address{255, 255, 255, 255}.IsReserved());

    // Not reserved: 239.x.x.x and below
    REQUIRE_FALSE(Address{239, 255, 255, 255}.IsReserved());

    // Multicast range: 224.x.x.x - 239.x.x.x
    REQUIRE(Address{224, 0, 0, 0}.IsMulticast());
    REQUIRE(Address{224, 0, 0, 1}.IsMulticast());
    REQUIRE(Address{239, 255, 255, 255}.IsMulticast());

    // Multicast boundaries
    REQUIRE_FALSE(Address{223, 255, 255, 255}.IsMulticast());
    REQUIRE_FALSE(Address{240, 0, 0, 0}.IsMulticast());

    // Reserved addresses are not multicast (240+ is reserved, not multicast)
    REQUIRE_FALSE(Address{240, 0, 0, 0}.IsMulticast());
}

TEST_CASE("IPv4 Address Unicast Classification", "[Address][Unicast]") {
    // Normal unicast
    REQUIRE(Address{8, 8, 8, 8}.IsUnicast());
    REQUIRE(Address{192, 168, 1, 1}.IsUnicast());
    REQUIRE(Address{10, 0, 0, 1}.IsUnicast());
    REQUIRE(Address{172, 16, 0, 1}.IsUnicast());

    // Not unicast: multicast
    REQUIRE_FALSE(Address{224, 0, 0, 1}.IsUnicast());
    REQUIRE_FALSE(Address{239, 255, 255, 255}.IsUnicast());

    // Not unicast: broadcast
    REQUIRE_FALSE(Address{255, 255, 255, 255}.IsUnicast());
}

TEST_CASE("IPv4 Address This Network Classification", "[Address][ThisNetwork]") {
    // "This network" is address starting with 0.x.x.x
    REQUIRE(Address{0, 0, 0, 0}.IsThisNetwork());
    REQUIRE(Address{0, 0, 0, 1}.IsThisNetwork());
    REQUIRE(Address{0, 255, 255, 255}.IsThisNetwork());

    // Not "this network"
    REQUIRE_FALSE(Address{1, 0, 0, 0}.IsThisNetwork());
    REQUIRE_FALSE(Address{127, 0, 0, 1}.IsThisNetwork());
}

TEST_CASE("IPv4 Address Local Classification", "[Address][Local]") {
    // Local loopback: 127.x.x.x
    REQUIRE(Address{127, 0, 0, 0}.IsLocal());
    REQUIRE(Address{127, 0, 0, 1}.IsLocal());
    REQUIRE(Address{127, 255, 255, 255}.IsLocal());
    REQUIRE(Address{127, 128, 0, 1}.IsLocal());

    // Not local
    REQUIRE_FALSE(Address{126, 255, 255, 255}.IsLocal());
    REQUIRE_FALSE(Address{128, 0, 0, 0}.IsLocal());
}

TEST_CASE("Masks for Networks [Masks]") {
    SECTION("This Network") {
        Address network_test = this_::network / this_::prefix;
        REQUIRE(this_::network == network_test);
        Address broadcast_test = this_::network | ~this_::mask;
        REQUIRE(this_::broadcast == broadcast_test);
    }

    SECTION("Byte Constructor") {
        Address address_from_bytes{192, 168, 1, 2};
        REQUIRE(address_from_bytes == Address{192, 168, 1, 2});
    }

    SECTION("Uin32_t Contructor") {
        uint32_t raw_address = static_cast<uint32_t>((192 << 24) | (168 << 16) | (1 << 8) | 1);
        Address address_from_uint32{raw_address};
        REQUIRE(address_from_uint32 == Address{192, 168, 1, 1});
    }

    SECTION("Bitwise NOT Operator") {
        Address address{192, 168, 1, 1};
        Address not_address = ~address;
        REQUIRE(not_address == Address{63, 87, 254, 254});
    }

    SECTION("Exhaustive Prefix Division") {
        ip::v4::Address test = limited_broadcast;
        for (uint8_t prefix = 0; prefix <= 32; ++prefix) {
            Address network_test = test / prefix;
            Address broadcast_test = test | ~(test / prefix);
            std::cout << "Test " << static_cast<uint32_t>(test) << " Prefix: " << static_cast<uint32_t>(prefix) << " Network: " << network_test
                      << " Broadcast: " << broadcast_test << std::endl;
            REQUIRE(network_test == (test & (test / prefix)));
        }
    }

    SECTION("Multicast") {
        Address network_test_a = multicast::network / multicast::prefix;
        Address network_test_b = multicast::dns / multicast::prefix;
        std::cout << "Multicast Network: " << multicast::network << " Multicast DNS: " << multicast::dns << " Multicast Network: " << network_test_a
                  << " Multicast Network: " << network_test_b << std::endl;
        REQUIRE(multicast::network == network_test_a);
        REQUIRE(multicast::network == network_test_b);
    }

    SECTION("Local (Loopback)") {
        Address network_test = local::host / local::prefix;
        REQUIRE(local::network == network_test);
        Address test = local::network | ~local::mask;
        REQUIRE(local::broadcast == test);
    }

    SECTION("Class A") {
        Address network_test = A::network / A::prefix;
        REQUIRE(A::network == network_test);
        Address test = A::network | ~A::mask;
        REQUIRE(A::broadcast == test);
    }

    SECTION("Class B") {
        Address network_test = B::network / B::prefix;
        REQUIRE(B::network == network_test);
        Address test = B::network | ~B::mask;
        REQUIRE(B::broadcast == test);
    }

    SECTION("Class C") {
        Address network_test = C::network / C::prefix;
        REQUIRE(C::network == network_test);
        Address test = C::network | ~C::mask;
        REQUIRE(C::broadcast == test);
    }

    SECTION("Link-Local") {
        Address network_test = link::network / link::prefix;
        REQUIRE(link::network == network_test);
        Address test = link::network | ~link::mask;
        REQUIRE(link::broadcast == test);
    }

    SECTION("Shared") {
        Address network_test = shared::network / shared::prefix;
        REQUIRE(shared::network == network_test);
        Address test = shared::network | ~shared::mask;
        REQUIRE(shared::broadcast == test);
    }
}

TEST_CASE("Address Operators and Conversions", "[Address][Operators]") {
    SECTION("operator!=") {
        REQUIRE(Address{192, 168, 1, 1} != Address{192, 168, 1, 2});
        REQUIRE_FALSE(Address{192, 168, 1, 1} != Address{192, 168, 1, 1});
    }

    SECTION("operator uint32_t") {
        Address address{192, 168, 1, 1};
        uint32_t raw = static_cast<uint32_t>(address);
        REQUIRE(raw == static_cast<uint32_t>((192 << 24) | (168 << 16) | (1 << 8) | 1));
    }

    SECTION("operator uint32_t default route") {
        Address address{0, 0, 0, 0};
        uint32_t raw = static_cast<uint32_t>(address);
        REQUIRE(raw == 0);
    }

    SECTION("operator uint32_t broadcast") {
        Address address{255, 255, 255, 255};
        uint32_t raw = static_cast<uint32_t>(address);
        REQUIRE(raw == 0xFFFFFFFF);
    }

    SECTION("operator&") {
        Address address{192, 168, 1, 1};
        Address mask{255, 255, 255, 0};
        Address result = address & mask;
        REQUIRE(result == Address{192, 168, 1, 0});
    }

    SECTION("operator|") {
        Address network{192, 168, 1, 0};
        Address inverse_mask{0, 0, 0, 255};
        Address broadcast = network | inverse_mask;
        REQUIRE(broadcast == Address{192, 168, 1, 255});
    }

    SECTION("Prefix 0 produces zero mask") {
        Address result = limited_broadcast / 0;
        REQUIRE(result == Address{0, 0, 0, 0});
    }

    SECTION("Prefix 32 produces identity") {
        Address result = Address{192, 168, 1, 1} / 32;
        REQUIRE(result == Address{192, 168, 1, 1});
    }

    SECTION("Prefix > 32 is clamped to 32") {
        Address result = Address{192, 168, 1, 1} / 33;
        REQUIRE(result == Address{192, 168, 1, 1});
        result = Address{192, 168, 1, 1} / 255;
        REQUIRE(result == Address{192, 168, 1, 1});
    }
}

TEST_CASE("Interface Test") {
    MockDriver driver;
    eui48::Address mac{{0, 1, 2, 3, 4, 5}};

    SECTION("Invalid Interface") {
        Interface iface{driver, mac, {0, 0, 0, 0}, {0, 0, 0, 0}};
        REQUIRE_FALSE(iface.IsValid());

        Interface iface2{driver, mac, {192, 168, 1, 255}, {255, 255, 255, 0}};
        REQUIRE_FALSE(iface2.IsValid());

        Interface iface3{driver, mac, {224, 0, 0, 1}, {240, 0, 0, 0}};
        REQUIRE_FALSE(iface3.IsValid());
    }

    SECTION("Invalid Interface: address is subnet network address") {
        Interface iface{driver, mac, {192, 168, 1, 0}, {255, 255, 255, 0}};
        REQUIRE_FALSE(iface.IsValid());
    }

    SECTION("Invalid Interface: address is limited broadcast") {
        Interface iface{driver, mac, {255, 255, 255, 255}, {255, 255, 255, 0}};
        REQUIRE_FALSE(iface.IsValid());
    }

    SECTION("Local Host Interface") {
        Interface iface{driver, mac, local::host, local::mask};
        REQUIRE(iface.IsValid());

        REQUIRE(iface.CouldReceiveFrom(local::host));
        REQUIRE(iface.CouldReceiveFrom(local::network));
        REQUIRE(iface.CouldReceiveFrom(local::broadcast));
        REQUIRE_FALSE(iface.CouldReceiveFrom({192, 168, 1, 1}));
        REQUIRE(iface.CouldReceiveFrom(limited_broadcast));
        REQUIRE(iface.CouldReceiveFrom(multicast::dns));
        REQUIRE(iface.CouldReceiveFrom(multicast::all));
    }

    SECTION("Link Local Interface") {
        Interface iface{driver, mac, {169, 254, 1, 1}, link::mask};
        REQUIRE(iface.IsValid());

        REQUIRE(iface.CouldReceiveFrom({169, 254, 1, 2}));
        REQUIRE(iface.CouldReceiveFrom(link::broadcast));
        REQUIRE_FALSE(iface.CouldReceiveFrom({192, 168, 1, 1}));
        REQUIRE(iface.CouldReceiveFrom(limited_broadcast));
        REQUIRE(iface.CouldReceiveFrom(multicast::dns));
        REQUIRE(iface.CouldReceiveFrom(multicast::all));
    }

    SECTION("Class A Interface") {
        Interface iface{driver, mac, {10, 9, 10, 1}, A::mask};
        REQUIRE(iface.IsValid());

        REQUIRE(iface.CouldReceiveFrom({10, 9, 10, 2}));
        REQUIRE(iface.CouldReceiveFrom(A::broadcast));
        REQUIRE_FALSE(iface.CouldReceiveFrom({192, 168, 1, 1}));
        REQUIRE(iface.CouldReceiveFrom(limited_broadcast));
        REQUIRE(iface.CouldReceiveFrom(multicast::dns));
        REQUIRE(iface.CouldReceiveFrom(multicast::all));
    }

    SECTION("Class B Interface") {
        Interface iface{driver, mac, {172, 16, 0, 1}, B::mask};
        REQUIRE(iface.IsValid());

        REQUIRE(iface.CouldReceiveFrom({172, 16, 0, 2}));
        REQUIRE(iface.CouldReceiveTo({172, 16, 0, 1}));
        REQUIRE(iface.CouldReceiveFrom(B::broadcast));
        REQUIRE_FALSE(iface.CouldReceiveFrom({192, 168, 1, 1}));
        REQUIRE(iface.CouldReceiveTo(limited_broadcast));
        REQUIRE(iface.CouldReceiveTo(multicast::dns));
        REQUIRE(iface.CouldReceiveTo(multicast::all));
    }

    SECTION("Class C Interface") {
        Interface iface{driver, mac, {192, 168, 1, 1}, C::mask};
        REQUIRE(iface.IsValid());

        REQUIRE(iface.CouldReceiveFrom({192, 168, 1, 2}));
        REQUIRE(iface.CouldReceiveTo({192, 168, 1, 1}));
        REQUIRE(iface.CouldReceiveFrom(C::broadcast));
        REQUIRE_FALSE(iface.CouldReceiveFrom({192, 167, 1, 1}));
        REQUIRE(iface.CouldReceiveFrom(limited_broadcast));
        REQUIRE(iface.CouldReceiveFrom(multicast::dns));
        REQUIRE(iface.CouldReceiveFrom(multicast::all));
        REQUIRE(iface.CouldReceiveTo(limited_broadcast));
        REQUIRE(iface.CouldReceiveTo(multicast::dns));
        REQUIRE(iface.CouldReceiveTo(multicast::all));
    }

    SECTION("Class C Interface CouldReceiveFrom: subnet broadcast") {
        Interface iface{driver, mac, {192, 168, 1, 1}, C::mask};
        REQUIRE(iface.CouldReceiveFrom(C::broadcast));
    }

    SECTION("Class C Interface CouldReceiveFrom: outside subnet") {
        Interface iface{driver, mac, {192, 168, 1, 1}, C::mask};
        REQUIRE_FALSE(iface.CouldReceiveFrom({192, 167, 1, 1}));
    }
}

TEST_CASE("Interface CouldSendTo", "[Interface][CouldSendTo]") {
    MockDriver driver;
    eui48::Address mac{{0, 1, 2, 3, 4, 5}};

    SECTION("Class A (10.0.0.0/8)") {
        Interface iface{driver, mac, {10, 0, 0, 1}, A::mask};

        REQUIRE(iface.IsValid());
        REQUIRE(iface.CouldSendTo({10, 0, 0, 2}));
        REQUIRE(iface.CouldSendTo({10, 255, 255, 254}));
        REQUIRE(iface.CouldSendTo({10, 1, 2, 3}));
        REQUIRE(iface.CouldSendTo({10, 0, 0, 0}));
        REQUIRE(iface.CouldSendTo(A::broadcast));
        REQUIRE(iface.CouldSendTo(limited_broadcast));
        REQUIRE(iface.CouldSendTo(multicast::dns));
        REQUIRE(iface.CouldSendTo(multicast::all));
        REQUIRE_FALSE(iface.CouldSendTo({11, 0, 0, 1}));
        REQUIRE_FALSE(iface.CouldSendTo({192, 168, 1, 1}));
        REQUIRE_FALSE(iface.CouldSendTo({172, 16, 0, 1}));
        REQUIRE_FALSE(iface.CouldSendTo({169, 254, 1, 1}));
    }

    SECTION("Class B (172.16.0.0/16)") {
        Interface iface{driver, mac, {172, 16, 0, 1}, B::mask};

        REQUIRE(iface.IsValid());
        REQUIRE(iface.CouldSendTo({172, 16, 0, 2}));
        REQUIRE(iface.CouldSendTo({172, 16, 255, 254}));
        REQUIRE(iface.CouldSendTo({172, 16, 128, 1}));
        REQUIRE(iface.CouldSendTo({172, 16, 0, 0}));
        REQUIRE(iface.CouldSendTo(B::broadcast));
        REQUIRE(iface.CouldSendTo(limited_broadcast));
        REQUIRE(iface.CouldSendTo(multicast::dns));
        REQUIRE(iface.CouldSendTo(multicast::all));
        REQUIRE_FALSE(iface.CouldSendTo({172, 15, 255, 255}));
        REQUIRE_FALSE(iface.CouldSendTo({172, 32, 0, 1}));
        REQUIRE_FALSE(iface.CouldSendTo({10, 0, 0, 1}));
    }

    SECTION("Class C (192.168.1.0/24)") {
        ip::v4::Address const subnet_mask{255, 255, 255, 0};
        Interface iface{driver, mac, {192, 168, 1, 1}, subnet_mask};

        REQUIRE(iface.IsValid());
        REQUIRE(iface.CouldSendTo({192, 168, 1, 2}));
        REQUIRE(iface.CouldSendTo({192, 168, 1, 100}));
        REQUIRE(iface.CouldSendTo({192, 168, 1, 254}));
        REQUIRE(iface.CouldSendTo({192, 168, 1, 0}));
        REQUIRE(iface.CouldSendTo({192, 168, 1, 1}));
        REQUIRE(iface.CouldSendTo(ip::v4::Address{192, 168, 1, 255}));
        REQUIRE(iface.CouldSendTo(limited_broadcast));
        REQUIRE(iface.CouldSendTo(multicast::dns));
        REQUIRE(iface.CouldSendTo(multicast::all));
        REQUIRE_FALSE(iface.CouldSendTo({192, 168, 2, 1}));
        REQUIRE_FALSE(iface.CouldSendTo({192, 167, 1, 1}));
        REQUIRE_FALSE(iface.CouldSendTo({10, 0, 0, 1}));
    }

    SECTION("Loopback (127.0.0.0/8)") {
        Interface iface{driver, mac, local::host, local::mask};

        REQUIRE(iface.IsValid());
        REQUIRE(iface.CouldSendTo({127, 0, 0, 1}));
        REQUIRE(iface.CouldSendTo({127, 0, 0, 2}));
        REQUIRE(iface.CouldSendTo({127, 255, 255, 254}));
        REQUIRE(iface.CouldSendTo({127, 0, 0, 0}));
        REQUIRE(iface.CouldSendTo(local::broadcast));
        REQUIRE(iface.CouldSendTo(limited_broadcast));
        REQUIRE(iface.CouldSendTo(multicast::dns));
        REQUIRE(iface.CouldSendTo(multicast::all));
        REQUIRE_FALSE(iface.CouldSendTo({192, 168, 1, 1}));
        REQUIRE_FALSE(iface.CouldSendTo({10, 0, 0, 1}));
    }

    SECTION("Link-Local (169.254.0.0/16)") {
        Interface iface{driver, mac, {169, 254, 1, 1}, link::mask};

        REQUIRE(iface.IsValid());
        REQUIRE(iface.CouldSendTo({169, 254, 1, 2}));
        REQUIRE(iface.CouldSendTo({169, 254, 255, 254}));
        REQUIRE(iface.CouldSendTo({169, 254, 0, 0}));
        REQUIRE(iface.CouldSendTo(link::broadcast));
        REQUIRE(iface.CouldSendTo(limited_broadcast));
        REQUIRE(iface.CouldSendTo(multicast::dns));
        REQUIRE(iface.CouldSendTo(multicast::all));
        REQUIRE_FALSE(iface.CouldSendTo({169, 255, 1, 1}));
        REQUIRE_FALSE(iface.CouldSendTo({168, 254, 1, 1}));
        REQUIRE_FALSE(iface.CouldSendTo({192, 168, 1, 1}));
    }

    SECTION("Default route (0.0.0.0/0) is not sendable") {
        Interface iface{driver, mac, {10, 0, 0, 1}, A::mask};
        REQUIRE_FALSE(iface.CouldSendTo(ip::v4::default_route));
    }

    SECTION("Gateway outside subnet is not sendable") {
        Interface iface{driver, mac, {192, 168, 1, 1}, C::mask, {10, 0, 0, 1}};
        REQUIRE(iface.IsValid());
        REQUIRE_FALSE(iface.CouldSendTo(iface.gateway));
    }

    SECTION("Gateway inside subnet is sendable") {
        Interface iface{driver, mac, {192, 168, 1, 1}, C::mask, {192, 168, 1, 254}};
        REQUIRE(iface.IsValid());
        REQUIRE(iface.CouldSendTo(iface.gateway));
    }

    SECTION("Sending to self is sendable") {
        Interface iface{driver, mac, {192, 168, 1, 1}, C::mask};
        REQUIRE(iface.CouldSendTo(iface.address));
    }

    SECTION("Multicast boundary") {
        Interface iface{driver, mac, {10, 0, 0, 1}, A::mask};
        REQUIRE(iface.CouldSendTo({224, 0, 0, 0}));
        REQUIRE(iface.CouldSendTo({239, 255, 255, 255}));
        REQUIRE_FALSE(iface.CouldSendTo({240, 0, 0, 0}));
    }

    SECTION("CouldSendTo does not check validity") {
        Interface iface{driver, mac, {0, 0, 0, 0}, {0, 0, 0, 0}};
        REQUIRE_FALSE(iface.IsValid());
        REQUIRE(iface.CouldSendTo({192, 168, 1, 1}));
    }
}

}    // namespace v4
}    // namespace ip
}    // namespace net
}    // namespace jarnax

#include <catch2/catch_test_macros.hpp>

#include "jarnax/net/arp/Entry.hpp"

namespace {

constexpr jarnax::net::ip::v4::Address kIpA{192, 168, 1, 10};
constexpr jarnax::net::ip::v4::Address kIpB{192, 168, 1, 11};
constexpr jarnax::net::eui48::Address kMacA{0x10, 0x20, 0x30, 0x40, 0x50, 0x60};
constexpr jarnax::net::eui48::Address kMacB{0x10, 0x20, 0x30, 0x40, 0x50, 0x61};
constexpr jarnax::net::eui48::Address kMacZero{0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

}    // namespace

TEST_CASE("ARP Entry defaults invalid") {
    jarnax::net::arp::Entry entry{};
    REQUIRE_FALSE(entry.IsValid());
    REQUIRE(entry.ttl == 0U);
}

TEST_CASE("ARP Entry equality requires valid entries") {
    jarnax::net::arp::Entry valid_a{kIpA, kMacA, 10U};
    jarnax::net::arp::Entry valid_b{kIpA, kMacA, 99U};
    jarnax::net::arp::Entry invalid{kIpA, kMacA, 0U};

    REQUIRE(valid_a.IsValid());
    REQUIRE(valid_b.IsValid());
    REQUIRE(valid_a == valid_b);
    REQUIRE_FALSE(valid_a == invalid);
}

TEST_CASE("ARP Entry supports IP and MAC match operators") {
    jarnax::net::arp::Entry entry{kIpA, kMacA, 5U};

    REQUIRE(entry == kIpA);
    REQUIRE(entry == kMacA);
    REQUIRE_FALSE(entry == kIpB);
    REQUIRE_FALSE(entry == kMacB);

    entry.ttl = 0U;
    REQUIRE_FALSE(entry == kIpA);
    REQUIRE_FALSE(entry == kMacA);
}

TEST_CASE("ARP Entry clear resets all fields") {
    jarnax::net::arp::Entry entry{kIpA, kMacA, 8U};

    entry.Clear();

    REQUIRE_FALSE(entry.IsValid());
    REQUIRE(entry.ttl == 0U);
    REQUIRE(entry.ipv4 == jarnax::net::ip::v4::Address{});
    REQUIRE(entry.mac == kMacZero);
}

TEST_CASE("ARP Entry decrement ttl saturates at zero") {
    jarnax::net::arp::Entry entry{kIpA, kMacA, 2U};

    entry.DecrementTTL();
    REQUIRE(entry.ttl == 1U);
    REQUIRE(entry.IsValid());

    entry.DecrementTTL();
    REQUIRE(entry.ttl == 0U);
    REQUIRE_FALSE(entry.IsValid());

    entry.DecrementTTL();
    REQUIRE(entry.ttl == 0U);
}

#include <catch2/catch_test_macros.hpp>

#include "jarnax/net/arp/Table.hpp"

namespace {

constexpr jarnax::net::ip::v4::Address kIp1{192, 168, 0, 10};
constexpr jarnax::net::ip::v4::Address kIp2{192, 168, 0, 11};
constexpr jarnax::net::ip::v4::Address kIp3{192, 168, 0, 12};
constexpr jarnax::net::ip::v4::Address kIp4{192, 168, 0, 13};

constexpr jarnax::net::eui48::Address kMac1{{0x00, 0x11, 0x22, 0x33, 0x44, 0x10}};
constexpr jarnax::net::eui48::Address kMac2{{0x00, 0x11, 0x22, 0x33, 0x44, 0x11}};
constexpr jarnax::net::eui48::Address kMac3{{0x00, 0x11, 0x22, 0x33, 0x44, 0x12}};
constexpr jarnax::net::eui48::Address kMac4{{0x00, 0x11, 0x22, 0x33, 0x44, 0x13}};

}    // namespace

TEST_CASE("ARP Table basic capacity and lookup behavior") {
    jarnax::net::arp::Table<3U> table;

    REQUIRE(table.Count() == 0U);
    REQUIRE(table.Available() == 3U);
    REQUIRE(table.Capacity() == 3U);
    REQUIRE(table.Find(kIp1) == nullptr);
    REQUIRE_FALSE(table.Remove(kIp1));
}

TEST_CASE("ARP Table insert and find") {
    jarnax::net::arp::Table<3U> table;

    REQUIRE(table.Insert(kIp1, kMac1, 7U));
    REQUIRE(table.Count() == 1U);

    auto* found = table.Find(kIp1);
    REQUIRE(found != nullptr);
    REQUIRE(found->ipv4 == kIp1);
    REQUIRE(found->mac == kMac1);
    REQUIRE(found->ttl == 7U);
}

TEST_CASE("ARP Table rejects invalid entries") {
    jarnax::net::arp::Table<3U> table;

    REQUIRE_FALSE(table.Insert(kIp1, kMac1, 0U));
    REQUIRE(table.Count() == 0U);
}

TEST_CASE("ARP Table updates existing key without growing") {
    jarnax::net::arp::Table<3U> table;

    REQUIRE(table.Insert(kIp1, kMac1, 5U));
    REQUIRE(table.Count() == 1U);

    REQUIRE(table.Insert(kIp1, kMac2, 9U));
    REQUIRE(table.Count() == 1U);

    auto* found = table.Find(kIp1);
    REQUIRE(found != nullptr);
    REQUIRE(found->mac == kMac2);
    REQUIRE(found->ttl == 9U);
}

TEST_CASE("ARP Table enforces fixed capacity") {
    jarnax::net::arp::Table<3U> table;

    REQUIRE(table.Insert(kIp1, kMac1, 5U));
    REQUIRE(table.Insert(kIp2, kMac2, 5U));
    REQUIRE(table.Insert(kIp3, kMac3, 5U));
    REQUIRE_FALSE(table.Insert(kIp4, kMac4, 5U));

    REQUIRE(table.Count() == 3U);
    REQUIRE(table.Available() == 0U);
}

TEST_CASE("ARP Table remove removes key and frees slot") {
    jarnax::net::arp::Table<3U> table;

    REQUIRE(table.Insert(kIp2, kMac2, 3U));
    REQUIRE(table.Insert(kIp1, kMac1, 3U));
    REQUIRE(table.Insert(kIp3, kMac3, 3U));

    REQUIRE(table.Remove(kIp1));
    REQUIRE_FALSE(table.Remove(kIp1));
    REQUIRE(table.Find(kIp1) == nullptr);
    REQUIRE(table.Count() == 2U);
    REQUIRE(table.Available() == 1U);

    REQUIRE(table.Find(kIp2) != nullptr);
    REQUIRE(table.Find(kIp3) != nullptr);
}

TEST_CASE("ARP Table tick expires entries") {
    jarnax::net::arp::Table<3U> table;

    REQUIRE(table.Insert(kIp1, kMac1, 1U));
    REQUIRE(table.Insert(kIp2, kMac2, 2U));

    table.Tick();
    REQUIRE(table.Find(kIp1) == nullptr);

    auto* second = table.Find(kIp2);
    REQUIRE(second != nullptr);
    REQUIRE(second->ttl == 1U);

    table.Tick();
    REQUIRE(table.Find(kIp2) == nullptr);
    REQUIRE(table.Count() == 0U);
}

TEST_CASE("ARP Table clear empties table") {
    jarnax::net::arp::Table<3U> table;

    REQUIRE(table.Insert(kIp1, kMac1, 5U));
    REQUIRE(table.Insert(kIp2, kMac2, 5U));
    REQUIRE(table.Insert(kIp3, kMac3, 5U));

    table.Clear();

    REQUIRE(table.Count() == 0U);
    REQUIRE(table.Available() == table.Capacity());
    REQUIRE(table.Find(kIp1) == nullptr);
    REQUIRE(table.Find(kIp2) == nullptr);
    REQUIRE(table.Find(kIp3) == nullptr);
}

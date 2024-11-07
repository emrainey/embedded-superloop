#include <catch2/catch_test_macros.hpp>
#include "core/doublelink/Node.hpp"

#include <iostream>

struct Dummy {
    size_t ordinal{0u};
};

std::ostream& operator<<(std::ostream& os, Dummy const& d) {
    os << " Ordinal: " << d.ordinal;
    return os;
}

TEST_CASE("Double Link Items") {
    doublelink::Node<Dummy> node1{1u};
    doublelink::Node<Dummy> node2{node1, 2u};
    doublelink::Node<Dummy> node3{node2, 3u};

    SECTION("Forward Printer") {
        node1.foreach_forward([](doublelink::Node<Dummy> const& node) {
            std::cout << "Ordinal " << node << std::endl;
        });
    }
    SECTION("Backward Printer") {
        node3.foreach_backward([](doublelink::Node<Dummy> const& node) {
            std::cout << "Ordinal " << node << std::endl;
        });
    }
    SECTION("Forward Modifier") {
        node1.foreach_forward([&](doublelink::Node<Dummy>& node) {
            node().ordinal++;
        });
        REQUIRE(node1().ordinal == 2u);
        REQUIRE(node2().ordinal == 3u);
        REQUIRE(node3().ordinal == 4u);
    }
    SECTION("Remove and Count") {
        node2.remove();
        node1.foreach_forward([&](doublelink::Node<Dummy>& node) {
            node().ordinal++;
        });
        REQUIRE(node1().ordinal == 2u);
        REQUIRE(node2().ordinal == 2u);
        REQUIRE(node3().ordinal == 4u);
    }
}

TEST_CASE("Double Link Reverse Insert") {
    doublelink::Node<Dummy> node1{1u};
    doublelink::Node<Dummy> node2{2u};
    doublelink::Node<Dummy> node3{3u};

    node2.insert_before(node3);
    node1.insert_before(node2);

    SECTION("Forward Printer") {
        node1.foreach_forward([](doublelink::Node<Dummy> const& node) {
            std::cout << "Ordinal " << node << std::endl;
        });
        node3.foreach_forward([&](doublelink::Node<Dummy>& node) {
            node().ordinal++;
        });
        REQUIRE(node1().ordinal == 2u);
        REQUIRE(node2().ordinal == 3u);
        REQUIRE(node3().ordinal == 4u);
    }
}
#include <catch2/catch_test_macros.hpp>
#include "core/doublelink/Node.hpp"

#include <iostream>
namespace core {
struct Dummy {
    size_t ordinal{0u};
};

std::ostream& operator<<(std::ostream& os, Dummy const& d) {
    os << " Ordinal: " << d.ordinal;
    return os;
}

class PrintVisitor : public doublelink::Node<Dummy>::Visitor {
public:
    void Visit(doublelink::Node<Dummy>& node) override {
        std::cout << "Ordinal " << node << std::endl;
    }
    void Visit(doublelink::Node<Dummy> const& node) const override {
        std::cout << "Ordinal " << node << std::endl;
    }
};

class CountingVisitor : public doublelink::Node<Dummy>::Visitor {
public:
    void Visit(doublelink::Node<Dummy>& node) override {
        node().ordinal++;
    }
    void Visit(doublelink::Node<Dummy> const&) const override {
        // can't modify const
    }
};

TEST_CASE("Double Link Items") {
    doublelink::Node<Dummy> node1{1u};
    doublelink::Node<Dummy> node2{node1, 2u};
    doublelink::Node<Dummy> node3{node2, 3u};
    PrintVisitor print_visitor;
    CountingVisitor counting_visitor;

    SECTION("Forward Printer") {
        node1.VisitForward(print_visitor);
    }
    SECTION("Backward Printer") {
        node3.VisitBackward(print_visitor);
    }
    SECTION("Forward Modifier") {
        node1.VisitForward(counting_visitor);
        REQUIRE(node1().ordinal == 2u);
        REQUIRE(node2().ordinal == 3u);
        REQUIRE(node3().ordinal == 4u);
    }
    SECTION("Remove and Count") {
        node2.Remove();
        node1.VisitForward(counting_visitor);
        REQUIRE(node1().ordinal == 2u);
        REQUIRE(node2().ordinal == 2u);
        REQUIRE(node3().ordinal == 4u);
    }
}

TEST_CASE("Double Link Reverse Insert") {
    doublelink::Node<Dummy> node1{1u};
    doublelink::Node<Dummy> node2{2u};
    doublelink::Node<Dummy> node3{3u};
    PrintVisitor print_visitor;
    CountingVisitor counting_visitor;

    node2.InsertBefore(node3);
    node1.InsertBefore(node2);

    SECTION("Forward Printer") {
        node1.VisitForward(print_visitor);
        node3.VisitForward(counting_visitor);
        REQUIRE(node1().ordinal == 2u);
        REQUIRE(node2().ordinal == 3u);
        REQUIRE(node3().ordinal == 4u);
    }
}
}  // namespace core
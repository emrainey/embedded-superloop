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
    void Visit(doublelink::Node<Dummy>& node) override { std::cout << "Ordinal " << node << std::endl; }
    void Visit(doublelink::Node<Dummy> const& node) const override { std::cout << "Ordinal " << node << std::endl; }
};

class CountingVisitor : public doublelink::Node<Dummy>::Visitor {
public:
    void Visit(doublelink::Node<Dummy>& node) override {
        node().ordinal += visitation_cout;
        visitation_cout++;
    }
    void Visit(doublelink::Node<Dummy> const&) const override {
        // can't modify const
    }
    size_t visitation_cout{1u};
};

TEST_CASE("Double Link Items") {
    doublelink::Node<Dummy> node1{1u};
    doublelink::Node<Dummy> node2{node1, 2u};
    doublelink::Node<Dummy> node3{node2, 3u};
    PrintVisitor print_visitor;
    CountingVisitor counting_visitor;

    SECTION("Arrangement") {
        REQUIRE(node1.Next() == &node2);
        REQUIRE(node2.Prev() == &node1);
        REQUIRE(node2.Next() == &node3);
        REQUIRE(node3.Prev() == &node2);
        REQUIRE(node1.Prev() == &node3);
        REQUIRE(node3.Next() == &node1);
    }

    SECTION("Forward Printer") {
        node1.VisitForward(print_visitor);
    }
    SECTION("Backward Printer") {
        node3.VisitBackward(print_visitor);
    }
    SECTION("Forward Modifier") {
        node1.VisitForward(counting_visitor);
        CHECK(node1().ordinal == (1u + 1u));
        CHECK(node2().ordinal == (2u + 2u));
        CHECK(node3().ordinal == (3u + 3u));
    }
    SECTION("Forward Remove and Count") {
        node2.Remove();
        node1.VisitForward(counting_visitor);
        CHECK(node1().ordinal == (1u + 1u));
        CHECK(node2().ordinal == (2u + 0u));
        CHECK(node3().ordinal == (3u + 2u));
    }
    SECTION("Backward Modifier") {
        node3.VisitBackward(counting_visitor);
        CHECK(node1().ordinal == (1u + 3u));
        CHECK(node2().ordinal == (2u + 2u));
        CHECK(node3().ordinal == (3u + 1u));
    }
    SECTION("Backward Remove and Count") {
        node2.Remove();
        node3.VisitBackward(counting_visitor);
        CHECK(node1().ordinal == (1u + 2u));
        CHECK(node2().ordinal == (2u + 0u));
        CHECK(node3().ordinal == (3u + 1u));
    }
}

TEST_CASE("Double Link Before Insert") {
    doublelink::Node<Dummy> node1{1u};
    doublelink::Node<Dummy> node2{2u};
    doublelink::Node<Dummy> node3{3u};
    PrintVisitor print_visitor;
    CountingVisitor counting_visitor;

    node2.InsertBefore(node3);
    // node2 <-> node3
    node1.InsertBefore(node2);
    // node1 <-> node2 <-> node3

    SECTION("Arrangement") {
        REQUIRE(node1.Next() == &node2);
        REQUIRE(node2.Prev() == &node1);
        REQUIRE(node2.Next() == &node3);
        REQUIRE(node3.Prev() == &node2);
        REQUIRE(node1.Prev() == &node3);
        REQUIRE(node3.Next() == &node1);
    }
    SECTION("Forward Visitation") {
        node1.VisitForward(print_visitor);
        node1.VisitForward(counting_visitor);
        CHECK(node1().ordinal == (1u + 1u));
        CHECK(node2().ordinal == (2u + 2u));
        CHECK(node3().ordinal == (3u + 3u));
    }

    SECTION("Backward Visitation") {
        node3.VisitBackward(print_visitor);
        node3.VisitBackward(counting_visitor);
        CHECK(node1().ordinal == (1u + 3u));
        CHECK(node2().ordinal == (2u + 2u));
        CHECK(node3().ordinal == (3u + 1u));
    }
}

TEST_CASE("Double Link After Insert") {
    doublelink::Node<Dummy> node1{1u};
    doublelink::Node<Dummy> node2{2u};
    doublelink::Node<Dummy> node3{3u};
    PrintVisitor print_visitor;
    CountingVisitor counting_visitor;

    node2.InsertAfter(node1);
    // node1 <-> node2
    node3.InsertAfter(node2);
    // node1 <-> node2 <-> node3

    SECTION("Arrangement") {
        REQUIRE(node1.Next() == &node2);
        REQUIRE(node2.Prev() == &node1);
        REQUIRE(node2.Next() == &node3);
        REQUIRE(node3.Prev() == &node2);
        REQUIRE(node1.Prev() == &node3);
        REQUIRE(node3.Next() == &node1);
    }
    SECTION("Forward Visitation") {
        node1.VisitForward(print_visitor);
        node1.VisitForward(counting_visitor);
        CHECK(node1().ordinal == (1u + 1u));
        CHECK(node2().ordinal == (2u + 2u));
        CHECK(node3().ordinal == (3u + 3u));
    }

    SECTION("Backward Visitation") {
        node3.VisitBackward(print_visitor);
        node3.VisitBackward(counting_visitor);
        CHECK(node1().ordinal == (1u + 3u));
        CHECK(node2().ordinal == (2u + 2u));
        CHECK(node3().ordinal == (3u + 1u));
    }
}

TEST_CASE("Double Link Middle After Insert") {
    doublelink::Node<Dummy> node1{1u};
    doublelink::Node<Dummy> node2{2u};
    doublelink::Node<Dummy> node3{3u};
    PrintVisitor print_visitor;
    CountingVisitor counting_visitor;

    node3.InsertAfter(node1);
    // node1 <-> node3
    node2.InsertAfter(node1);
    // node1 <-> node2 <-> node3 ?

    SECTION("Arrangement") {
        REQUIRE(node1.Next() == &node2);
        REQUIRE(node2.Prev() == &node1);
        REQUIRE(node2.Next() == &node3);
        REQUIRE(node3.Prev() == &node2);
        REQUIRE(node1.Prev() == &node3);
        REQUIRE(node3.Next() == &node1);
    }
    SECTION("Forward Visitation") {
        node1.VisitForward(print_visitor);
        node1.VisitForward(counting_visitor);
        CHECK(node1().ordinal == (1u + 1u));
        CHECK(node2().ordinal == (2u + 2u));
        CHECK(node3().ordinal == (3u + 3u));
    }

    SECTION("Backward Visitation") {
        node3.VisitBackward(print_visitor);
        node3.VisitBackward(counting_visitor);
        CHECK(node1().ordinal == (1u + 3u));
        CHECK(node2().ordinal == (2u + 2u));
        CHECK(node3().ordinal == (3u + 1u));
    }
}

TEST_CASE("Double Link Middle Before Insert") {
    doublelink::Node<Dummy> node1{1u};
    doublelink::Node<Dummy> node2{2u};
    doublelink::Node<Dummy> node3{3u};
    PrintVisitor print_visitor;
    CountingVisitor counting_visitor;

    node1.InsertBefore(node3);
    // node1 <-> node3
    node2.InsertBefore(node3);
    // node1 <-> node2 <-> node3 ?

    SECTION("Arrangement") {
        REQUIRE(node1.Next() == &node2);
        REQUIRE(node2.Prev() == &node1);
        REQUIRE(node2.Next() == &node3);
        REQUIRE(node3.Prev() == &node2);
        REQUIRE(node1.Prev() == &node3);
        REQUIRE(node3.Next() == &node1);
    }
    SECTION("Forward Visitation") {
        node1.VisitForward(print_visitor);
        node1.VisitForward(counting_visitor);
        CHECK(node1().ordinal == (1u + 1u));
        CHECK(node2().ordinal == (2u + 2u));
        CHECK(node3().ordinal == (3u + 3u));
    }

    SECTION("Backward Visitation") {
        node3.VisitBackward(print_visitor);
        node3.VisitBackward(counting_visitor);
        CHECK(node1().ordinal == (1u + 3u));
        CHECK(node2().ordinal == (2u + 2u));
        CHECK(node3().ordinal == (3u + 1u));
    }
}

TEST_CASE("Double Link Middle Before/After Insert") {
    doublelink::Node<Dummy> node1{1u};
    doublelink::Node<Dummy> node2{2u};
    doublelink::Node<Dummy> node3{3u};
    PrintVisitor print_visitor;
    CountingVisitor counting_visitor;

    node1.InsertBefore(node3);
    // node1 <-> node3
    node2.InsertAfter(node1);
    // node1 <-> node2 <-> node3 ?

    SECTION("Arrangement") {
        REQUIRE(node1.Next() == &node2);
        REQUIRE(node2.Prev() == &node1);
        REQUIRE(node2.Next() == &node3);
        REQUIRE(node3.Prev() == &node2);
        REQUIRE(node1.Prev() == &node3);
        REQUIRE(node3.Next() == &node1);
    }
    SECTION("Forward Visitation") {
        node1.VisitForward(print_visitor);
        node1.VisitForward(counting_visitor);
        CHECK(node1().ordinal == (1u + 1u));
        CHECK(node2().ordinal == (2u + 2u));
        CHECK(node3().ordinal == (3u + 3u));
    }

    SECTION("Backward Visitation") {
        node3.VisitBackward(print_visitor);
        node3.VisitBackward(counting_visitor);
        CHECK(node1().ordinal == (1u + 3u));
        CHECK(node2().ordinal == (2u + 2u));
        CHECK(node3().ordinal == (3u + 1u));
    }
}

TEST_CASE("Double Link Middle After/Before Insert") {
    doublelink::Node<Dummy> node1{1u};
    doublelink::Node<Dummy> node2{2u};
    doublelink::Node<Dummy> node3{3u};
    PrintVisitor print_visitor;
    CountingVisitor counting_visitor;

    node3.InsertAfter(node1);
    // node1 <-> node3
    node2.InsertBefore(node3);
    // node1 <-> node2 <-> node3 ?

    SECTION("Arrangement") {
        REQUIRE(node1.Next() == &node2);
        REQUIRE(node2.Prev() == &node1);
        REQUIRE(node2.Next() == &node3);
        REQUIRE(node3.Prev() == &node2);
        REQUIRE(node1.Prev() == &node3);
        REQUIRE(node3.Next() == &node1);
    }
    SECTION("Forward Visitation") {
        node1.VisitForward(print_visitor);
        node1.VisitForward(counting_visitor);
        CHECK(node1().ordinal == (1u + 1u));
        CHECK(node2().ordinal == (2u + 2u));
        CHECK(node3().ordinal == (3u + 3u));
    }

    SECTION("Backward Visitation") {
        node3.VisitBackward(print_visitor);
        node3.VisitBackward(counting_visitor);
        CHECK(node1().ordinal == (1u + 3u));
        CHECK(node2().ordinal == (2u + 2u));
        CHECK(node3().ordinal == (3u + 1u));
    }
}

}    // namespace core
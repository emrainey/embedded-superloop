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
    virtual ~PrintVisitor() = default;
};

class CountingVisitor : public doublelink::Node<Dummy>::Visitor {
public:
    virtual ~CountingVisitor() = default;
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

TEST_CASE("Double Link Single Node") {
    doublelink::Node<Dummy> node{42u};

    SECTION("Standalone State") {
        REQUIRE(node.Next() == &node);
        REQUIRE(node.Prev() == &node);
        REQUIRE(node().ordinal == 42u);
    }

    SECTION("Const operator()") {
        doublelink::Node<Dummy> const& const_node = node;
        REQUIRE(const_node().ordinal == 42u);
    }

    SECTION("Remove on standalone node is safe") {
        node.Remove();
        REQUIRE(node.Next() == &node);
        REQUIRE(node.Prev() == &node);
    }

    SECTION("Single Node Forward Visit") {
        struct TestVisitor : doublelink::Node<Dummy>::Visitor {
            size_t count{0u};
            virtual ~TestVisitor() = default;
            void Visit(doublelink::Node<Dummy>&) override { ++count; }
            void Visit(doublelink::Node<Dummy> const&) const override {}
        };
        TestVisitor v;
        node.VisitForward(v);
        CHECK(v.count == 1u);
    }

    SECTION("Single Node Backward Visit") {
        struct TestVisitor : doublelink::Node<Dummy>::Visitor {
            size_t count{0u};
            virtual ~TestVisitor() = default;
            void Visit(doublelink::Node<Dummy>&) override { ++count; }
            void Visit(doublelink::Node<Dummy> const&) const override {}
        };
        TestVisitor v;
        node.VisitBackward(v);
        CHECK(v.count == 1u);
    }

    SECTION("Single Node Const Forward Visit") {
        struct TestVisitor : doublelink::Node<Dummy>::Visitor {
            mutable size_t count{0u};
            virtual ~TestVisitor() = default;
            void Visit(doublelink::Node<Dummy>&) override {}
            void Visit(doublelink::Node<Dummy> const&) const override { ++count; }
        };
        TestVisitor const v{};
        doublelink::Node<Dummy> const& const_node = node;
        const_node.VisitForward(v);
        CHECK(v.count == 1u);
    }

    SECTION("Single Node Const Backward Visit") {
        struct TestVisitor : doublelink::Node<Dummy>::Visitor {
            mutable size_t count{0u};
            virtual ~TestVisitor() = default;
            void Visit(doublelink::Node<Dummy>&) override {}
            void Visit(doublelink::Node<Dummy> const&) const override { ++count; }
        };
        TestVisitor const v{};
        doublelink::Node<Dummy> const& const_node = node;
        const_node.VisitBackward(v);
        CHECK(v.count == 1u);
    }
}

TEST_CASE("Double Link Self Insert Guard") {
    doublelink::Node<Dummy> node{1u};
    doublelink::Node<Dummy> other{2u};

    SECTION("InsertAfter self returns immediately") {
        node.InsertAfter(node);
        REQUIRE(node.Next() == &node);
        REQUIRE(node.Prev() == &node);
    }

    SECTION("InsertBefore self returns immediately") {
        node.InsertBefore(node);
        REQUIRE(node.Next() == &node);
        REQUIRE(node.Prev() == &node);
    }

    SECTION("Self InsertAfter does not corrupt subsequent insert") {
        node.InsertAfter(node);
        other.InsertAfter(node);
        REQUIRE(node.Next() == &other);
        REQUIRE(other.Prev() == &node);
        REQUIRE(other.Next() == &node);
        REQUIRE(node.Prev() == &other);
    }

    SECTION("Self InsertBefore does not corrupt subsequent insert") {
        node.InsertBefore(node);
        other.InsertBefore(node);
        REQUIRE(node.Prev() == &other);
        REQUIRE(other.Next() == &node);
        REQUIRE(other.Prev() == &node);
        REQUIRE(node.Next() == &other);
    }
}

TEST_CASE("Double Link Const Traversal") {
    doublelink::Node<Dummy> node1{1u};
    doublelink::Node<Dummy> node2{node1, 2u};
    doublelink::Node<Dummy> node3{node2, 3u};

    struct ConstVisitRecorder : doublelink::Node<Dummy>::Visitor {
        mutable size_t visit_count{0u};
        mutable size_t ordinals[3]{0u, 0u, 0u};
        virtual ~ConstVisitRecorder() = default;
        void Visit(doublelink::Node<Dummy>&) override {}
        void Visit(doublelink::Node<Dummy> const& node) const override {
            ordinals[visit_count++] = node().ordinal;
        }
    };

    SECTION("Const Forward Visit") {
        ConstVisitRecorder const v{};
        doublelink::Node<Dummy> const& const_node = node1;
        const_node.VisitForward(v);
        CHECK(v.visit_count == 3u);
        CHECK(v.ordinals[0] == 1u);
        CHECK(v.ordinals[1] == 2u);
        CHECK(v.ordinals[2] == 3u);
    }

    SECTION("Const Backward Visit") {
        ConstVisitRecorder const v{};
        doublelink::Node<Dummy> const& const_node = node3;
        const_node.VisitBackward(v);
        CHECK(v.visit_count == 3u);
        CHECK(v.ordinals[0] == 3u);
        CHECK(v.ordinals[1] == 2u);
        CHECK(v.ordinals[2] == 1u);
    }
}

TEST_CASE("Double Link Destructor Unlinking") {
    doublelink::Node<Dummy> node1{1u};
    doublelink::Node<Dummy> node3{3u};
    node3.InsertAfter(node1);

    {
        doublelink::Node<Dummy> node2{2u};
        node2.InsertAfter(node1);
        REQUIRE(node1.Next() == &node2);
        REQUIRE(node2.Prev() == &node1);
        REQUIRE(node2.Next() == &node3);
        REQUIRE(node3.Prev() == &node2);
    }

    SECTION("Neighbors rewire after destruction") {
        REQUIRE(node1.Next() == &node3);
        REQUIRE(node3.Prev() == &node1);
        REQUIRE(node1.Prev() == &node3);
        REQUIRE(node3.Next() == &node1);
    }

    SECTION("Traversal still works after node destruction") {
        struct RemainingVisitor : doublelink::Node<Dummy>::Visitor {
            size_t count{0u};
            virtual ~RemainingVisitor() = default;
            void Visit(doublelink::Node<Dummy>&) override { ++count; }
            void Visit(doublelink::Node<Dummy> const&) const override {}
        };
        RemainingVisitor v;
        node1.VisitForward(v);
        CHECK(v.count == 2u);
    }
}

}    // namespace core
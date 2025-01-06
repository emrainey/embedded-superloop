// #define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "core/avl/Node.hpp"

struct Dummy {
    Dummy(int value)
        : value{value} {}
    // Has to have all the comparison operators
    bool operator<(const Dummy& rhs) const { return value < rhs.value; }
    bool operator<=(const Dummy& rhs) const { return value <= rhs.value; }
    bool operator>(const Dummy& rhs) const { return value > rhs.value; }
    bool operator>=(const Dummy& rhs) const { return value >= rhs.value; }
    bool operator==(const Dummy& rhs) const { return value == rhs.value; }
    bool operator!=(const Dummy& rhs) const { return value != rhs.value; }
    std::strong_ordering operator<=>(const Dummy& rhs) const { return value <=> rhs.value; }
    friend std::ostream& operator<<(std::ostream& os, Dummy const& dummy) { return os << dummy.value; }
    int value;
};

TEST_CASE("AVL Nodes") {
    core::avl::Node<Dummy> a{1};
    core::avl::Node<Dummy> b{2};
    core::avl::Node<Dummy> c{3};
    core::avl::Node<Dummy> d{4};
    core::avl::Node<Dummy> e{5};

    SECTION("Root 2 - Insert 1,3") {
        CHECK(b.GetHeight() == 0);
        CHECK(b.GetBalanceFactor() == 0);
        REQUIRE(b.Find(2) == &b);
        REQUIRE(b.Count() == 1);
        //==============================================================================
        REQUIRE(b.Insert(&a));
        CHECK(b.GetHeight() == 1);
        CHECK(b.GetBalanceFactor() == 0);
        CHECK(b.Left() == &a);
        CHECK(b.Right() == nullptr);
        CHECK(b.Find(1) == &a);
        CHECK(a.Parent() == &b);
        REQUIRE(b.Count() == 2);
        //==============================================================================
        REQUIRE(b.Insert(&c));
        CHECK(b.GetHeight() == 1);
        CHECK(b.GetBalanceFactor() == 0);
        CHECK(b.Left() == &a);
        CHECK(b.Right() == &c);
        CHECK(b.Find(3) == &c);
        CHECK(c.Parent() == &b);
        REQUIRE(b.Count() == 3);
    }
    SECTION("Root 4 - Insert 3,2,1") {
        CHECK(d.GetHeight() == 0);
        CHECK(d.GetBalanceFactor() == 0);
        REQUIRE(d.Find(4) == &d);
        std::cout << "d " << d << std::endl;
        std::cout << "==============================================================================" << std::endl;
        REQUIRE(d.Insert(&c));
        CHECK(d.GetHeight() == 1);
        CHECK(d.GetBalanceFactor() == 0);
        REQUIRE(d.Find(3) == &c);
        std::cout << "d " << d << std::endl;
        std::cout << "c " << c << std::endl;
        std::cout << "==============================================================================" << std::endl;
        REQUIRE(d.Insert(&b));
        std::cout << "d " << d << std::endl;
        std::cout << "c " << c << std::endl;
        std::cout << "b " << b << std::endl;
        CHECK(d.GetHeight() == 2);
        CHECK(d.GetBalanceFactor() == 1);
        REQUIRE(d.Find(2) == &b);
        std::cout << "==============================================================================" << std::endl;
        REQUIRE(d.Insert(&a));
        std::cout << "d " << d << std::endl;
        std::cout << "c " << c << std::endl;
        std::cout << "b " << b << std::endl;
        std::cout << "a " << a << std::endl;
        CHECK(d.GetHeight() == 0);    // now a leaf
        CHECK(d.GetBalanceFactor() == 0);
        CHECK(d.Find(1) == nullptr);    // can't find it now as it's not under d
        CHECK(d.Parent() == &c);        // d is not the root
        CHECK(c.IsRoot());              // c is now the root
        CHECK(c.Count() == 4);
        CHECK(b.Parent() == &c);    // this is the root
        CHECK(c.Find(1) == &a);     // can find it under c
        CHECK(c.Left() == &b);      // b is the left child
        CHECK(c.Right() == &d);     // d is the right child
    }
    SECTION("Root 1 - Insert - 2,3,4") {
        REQUIRE(a.Insert(&b));
        REQUIRE(a.Insert(&c));
        REQUIRE(a.Insert(&d));
        // should have rebalanced with 2 as the root
        CHECK(a.GetHeight() == 0);    // now a leaf
        CHECK(a.GetBalanceFactor() == 0);
        CHECK(a.Parent() == &b);
        CHECK(b.IsRoot());         // b is the root
        CHECK(b.Find(1) == &a);    // can find it under b
        CHECK(b.Find(2) == &b);    // can find it under b
        CHECK(b.Find(3) == &c);    // can find it under b
        CHECK(b.Find(4) == &d);    // can find it under b
        CHECK(b.Count() == 4);
    }
    SECTION("Root 3 - Insert 1, Remove 1") {
        REQUIRE(c.Insert(&a));
        CHECK(c.Count() == 2);
        CHECK(a.Parent() == &c);
        CHECK(c.Left() == &a);
        a.Remove();                      // Leaf Remove
        CHECK(a.Parent() == nullptr);    // a is removed
        CHECK(c.Left() == nullptr);      // a is removed
        // c needs to be recalculated too
        CHECK(c.GetHeight() == 0);    // now a leaf
        CHECK(c.GetBalanceFactor() == 0);
        CHECK(c.Count() == 1);
    }
    SECTION("Root 3 - Insert 1,2 Remove 1") {
        REQUIRE(c.Insert(&a));
        REQUIRE(c.Insert(&b));
        CHECK(c.Count() == 3);
        CHECK(a.Parent() == &c);
        CHECK(c.Left() == &a);
        CHECK(a.Right() == &b);
        a.Remove();                 // Middle Remove (Left Side)
        CHECK(a.IsSingular());      // a is removed
        CHECK(c.IsRoot());          // c is still the root
        CHECK(b.Parent() == &c);    // b's parent is c
        CHECK(c.Left() == &b);      // a is removed
        // c needs to be recalculated too
        CHECK(c.GetHeight() == 1);
        CHECK(c.GetBalanceFactor() == 0);
    }
    SECTION("Root 3 - Insert 5,4 Remove 5") {
        REQUIRE(c.Insert(&e));
        REQUIRE(c.Insert(&d));
        CHECK(d.Parent() == &e);
        CHECK(c.Right() == &e);
        CHECK(e.Left() == &d);
        e.Remove();                 // Middle Remove (Right Side)
        CHECK(e.IsSingular());      // e is removed
        CHECK(c.IsRoot());          // c is still the root
        CHECK(d.Parent() == &c);    // d's parent is c
        CHECK(c.Right() == &d);     // e is removed
        // c needs to be recalculated too
        CHECK(c.GetHeight() == 1);
        CHECK(c.GetBalanceFactor() == 0);
    }
    SECTION("Root 3 - Insert 1,2,5,4 - Remove 3") {
        REQUIRE(c.Insert(&a));
        REQUIRE(c.Insert(&b));
        REQUIRE(c.Insert(&e));
        REQUIRE(c.Insert(&d));
        // TODO Remove c, b should become the root
        c.Remove();
        CHECK(b.Parent() == nullptr);     // b is the root (left rightmost)
        CHECK(b.Left() == &a);            // a is the left child
        CHECK(b.Right() == &e);           // e is the right child
        CHECK(c.IsSingular());            // c is removed
        REQUIRE(b.Find(3) == nullptr);    // can't find it under b
    }
}

TEST_CASE("Complex Tree") {
    std::vector<core::avl::Node<Dummy>> nodes;
    // make 100 nodes, each index being it's value
    for (int i = 0; i < 100; ++i) {
        nodes.emplace_back(i);
    }
    core::avl::Node<Dummy>* root = &nodes[44];
    REQUIRE(root->GetHeight() == 0);
    // Top Layer
    root->Insert(&nodes[17]);
    root->Insert(&nodes[78]);
    REQUIRE(root->GetHeight() == 1);
    REQUIRE(root->GetBalanceFactor() == 0);
    // Next level down
    root->Insert(&nodes[12]);
    root->Insert(&nodes[32]);
    root->Insert(&nodes[50]);
    root->Insert(&nodes[88]);
    REQUIRE(root->GetHeight() == 2);
    REQUIRE(root->GetBalanceFactor() == 0);
    // Next level down
    root->Insert(&nodes[8]);
    root->Insert(&nodes[14]);
    root->Insert(&nodes[28]);
    root->Insert(&nodes[36]);
    root->Insert(&nodes[48]);
    root->Insert(&nodes[62]);
    root->Insert(&nodes[84]);
    root->Insert(&nodes[92]);
    REQUIRE(root->GetHeight() == 3);
    REQUIRE(root->GetBalanceFactor() == 0);
    // Next level down
    root->Insert(&nodes[6]);
    root->Insert(&nodes[9]);
    root->Insert(&nodes[13]);
    root->Insert(&nodes[15]);
    root->Insert(&nodes[26]);
    root->Insert(&nodes[30]);
    root->Insert(&nodes[34]);
    root->Insert(&nodes[38]);
    root->Insert(&nodes[46]);
    root->Insert(&nodes[49]);
    root->Insert(&nodes[54]);
    root->Insert(&nodes[64]);
    root->Insert(&nodes[80]);
    root->Insert(&nodes[86]);
    root->Insert(&nodes[94]);
    REQUIRE(root->GetHeight() == 4);

    // Next Level down
    root->Insert(&nodes[63]);
    REQUIRE(root->GetHeight() == 5);
    CHECK(root->Count() == 31);

    REQUIRE(root->IsRoot());

    SECTION("Complex Mid Tree Removal") {
        // we assume this will be the successor given the layout of the tree
        core::avl::Node<Dummy>* successor = root->Find(64);
        REQUIRE(successor != nullptr);
        REQUIRE(successor->Parent() == &nodes[62]);
        REQUIRE(successor->Parent()->Parent() == &nodes[50]);
        REQUIRE(successor->Parent()->Parent()->Parent() == &nodes[78]);
        REQUIRE(successor->Parent()->Parent()->Parent()->Parent() == root);
        REQUIRE(successor->Left() == &nodes[63]);

        root->Remove(78);    // go find the node for 78 and remove it.
        REQUIRE(nodes[78].Parent() == nullptr);
        REQUIRE(nodes[78].IsLeaf());
        REQUIRE(root->Right() != &nodes[78]);    // successor node should not be 78
        REQUIRE(root->Right() == successor);     // successor node should be to the right of root
        CHECK(root->GetHeight() == 4);
        CHECK(root->Find(78) == nullptr);                      // should not be able to find it anywhere
        CHECK(root->Find(successor->Value()) == successor);    // should be able to find the successor
        CHECK(root->Count() == 30);
    }
}

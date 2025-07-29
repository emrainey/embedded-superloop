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
    using Side = core::avl::Side;
    std::vector<core::avl::Node<Dummy>> nodes;
    for (int i = 0; i < 7; ++i) {
        nodes.emplace_back(i);
    }

    SECTION("Assumptions") {
        for (size_t i = 0; i < 7; ++i) {
            CHECK(nodes[i].Value() == static_cast<int>(i));
            CHECK(nodes[i].Height() == 1);
            CHECK(nodes[i].BalanceFactor() == 0);
            CHECK(nodes[i].IsLeaf());
            CHECK(nodes[i].IsRoot());
            CHECK(nodes[i].IsSingular());
            // can always find our own value
            CHECK(nodes[i].Find(static_cast<int>(i)) == &nodes[i]);
        }
    }

    SECTION("Root 2 - Insert 1,3 Print") {
        REQUIRE(nodes[2].Insert(&nodes[1]));
        REQUIRE(nodes[2].Insert(&nodes[3]));
        nodes[2].PrintTree();
        REQUIRE(nodes[2].IsConnected());
        CHECK(nodes[2].IsRoot());
        CHECK(nodes[2].Count() == 3);
        CHECK(nodes[2].Height() == 2);
        REQUIRE(nodes[1].FindRoot() == &nodes[2]);
        REQUIRE(nodes[2].FindRoot() == &nodes[2]);
        REQUIRE(nodes[3].FindRoot() == &nodes[2]);
    }

    SECTION("Root 1 - Insert 0,2") {
        REQUIRE(nodes[1].Insert(&nodes[2]));
        REQUIRE(nodes[1].Find(2) == &nodes[2]);
        CHECK(nodes[1].Height() == 2);
        CHECK(nodes[1].Count() == 2);
        //==============================================================================
        REQUIRE(nodes[1].Insert(&nodes[0]));
        REQUIRE(nodes[1].Find(0) == &nodes[0]);
        CHECK(nodes[1].Height() == 2);
        CHECK(nodes[1].Count() == 3);
        //==============================================================================
        CHECK(nodes[1].BalanceFactor() == 0);
        CHECK(nodes[1].VerifySide(Side::Left, &nodes[0]));
        CHECK(nodes[1].VerifySide(Side::Right, &nodes[2]));
    }
    SECTION("Root 3 - Insert 2,1,0") {
        core::avl::Node<Dummy>* root = &nodes[3];
        REQUIRE(nodes[3].Insert(&nodes[2]));
        CHECK(nodes[3].Height() == 2);
        CHECK(nodes[3].BalanceFactor() == 1);
        REQUIRE(nodes[3].Find(2) == &nodes[2]);
        REQUIRE(nodes[3].Insert(&nodes[1]));
        // now 2 should be root
        REQUIRE(nodes[3].FindRoot() == &nodes[2]);
        REQUIRE(nodes[3].Find(1) == nullptr);    // can't find it now as it's not under d
        REQUIRE(nodes[3].Find(2) == nullptr);    // can't find it now as it's not under d
        CHECK(nodes[3].IsLeaf());
        CHECK(not nodes[3].IsRoot());    // No longer root
        CHECK(nodes[3].Height() == 1);
        CHECK(nodes[3].BalanceFactor() == 0);
        CHECK(nodes[3].Parent() == &nodes[2]);    // 3 is not the root
        CHECK(nodes[2].IsRoot());                 // 2 is now the root
        root = nodes[3].FindRoot();
        REQUIRE(root->Insert(&nodes[0]));
        CHECK(root->Count() == 4);
        CHECK(root->Height() == 3);
        REQUIRE(root->Find(0) == &nodes[0]);    // can find it under c
        CHECK(root->VerifySide(Side::Left, &nodes[1]));
        CHECK(nodes[1].VerifySide(Side::Left, &nodes[0]));
        CHECK(root->VerifySide(Side::Right, &nodes[3]));
    }
    SECTION("Root 1 - Insert 2,3,4") {
        core::avl::Node<Dummy>* root = &nodes[1];
        REQUIRE(root->Insert(&nodes[2]));
        REQUIRE(root->Insert(&nodes[3]));
        // should have rebalanced with 2 as the root
        CHECK(not root->IsRoot());    // 1 is no longer the root
        CHECK(root->FindRoot() == &nodes[2]);
        root = root->FindRoot();    // update
        REQUIRE(root->Insert(&nodes[4]));
        REQUIRE(root->Find(4) == &nodes[4]);
        CHECK(root->Height() == 3);
        CHECK(root->BalanceFactor() == -1);
        CHECK(root->VerifySide(Side::Left, &nodes[1]));
        CHECK(root->VerifySide(Side::Right, &nodes[3]));
        CHECK(nodes[3].VerifySide(Side::Right, &nodes[4]));
        CHECK(root->Count() == 4);
        CHECK(root->Find(1) == &nodes[1]);    // can find it under root
        CHECK(root->Find(2) == &nodes[2]);    // can find it under root
        CHECK(root->Find(3) == &nodes[3]);    // can find it under root
        CHECK(root->Find(4) == &nodes[4]);    // can find it under root
    }
    SECTION("Root 2 - Insert 0, Remove 0") {
        REQUIRE(nodes[2].Insert(&nodes[0]));
        CHECK(nodes[2].Count() == 2);
        CHECK(nodes[0].Parent() == &nodes[2]);
        CHECK(nodes[2].Left() == &nodes[0]);
        nodes[0].Remove();                      // Leaf Remove
        CHECK(nodes[0].Parent() == nullptr);    // a is removed
        CHECK(nodes[2].Left() == nullptr);      // a is removed
        // c needs to be recalculated too
        CHECK(nodes[2].Height() == 1);    // now a leaf
        CHECK(nodes[2].BalanceFactor() == 0);
        CHECK(nodes[2].Count() == 1);
    }
    SECTION("Root 2 - Insert 1,0") {
        REQUIRE(nodes[2].Insert(&nodes[1]));
        REQUIRE(nodes[2].Insert(&nodes[0]));
        // should have rebalanced with 2 as the root
        CHECK(nodes[1].IsRoot());
        CHECK(nodes[0].Parent() == &nodes[1]);
        CHECK(nodes[2].Parent() == &nodes[1]);
        CHECK(nodes[1].Count() == 3);
        CHECK(nodes[1].Height() == 2);
    }
    SECTION("Root 2 - Insert 0,1") {
        core::avl::Node<Dummy>* root = &nodes[2];
        REQUIRE(root->Insert(&nodes[0]));
        REQUIRE(root->Insert(&nodes[1]));
        // should have rebalanced with 2 as the root
        // but went through an intermediate step
        root = root->FindRoot();
        CHECK(root == &nodes[1]);
        CHECK(root->VerifySide(Side::Left, &nodes[0]));
        CHECK(root->VerifySide(Side::Right, &nodes[2]));
    }
    SECTION("Root 2 - Insert 1,3,0 Remove 1") {
        core::avl::Node<Dummy>* root = &nodes[2];
        REQUIRE(nodes[2].Insert(&nodes[1]));
        REQUIRE(nodes[2].Insert(&nodes[3]));
        REQUIRE(nodes[2].Insert(&nodes[0]));
        root = root->FindRoot();
        CHECK(root == &nodes[2]);    // still root
        CHECK(root->Height() == 3);
        CHECK(root->BalanceFactor() == 1);
        CHECK(root->Count() == 4);
        CHECK(root->VerifySide(Side::Left, &nodes[1]));
        CHECK(root->VerifySide(Side::Right, &nodes[3]));
        CHECK(nodes[1].VerifySide(Side::Left, &nodes[0]));
        nodes[1].Remove();               // Middle Remove (Left Side)
        CHECK(nodes[1].IsSingular());    // a is removed
        root = root->FindRoot();
        CHECK(root == &nodes[2]);    // 2 is still the root
        CHECK(root->VerifySide(Side::Left, &nodes[0]));
        CHECK(root->VerifySide(Side::Right, &nodes[3]));
        CHECK(root->Height() == 2);
        CHECK(root->BalanceFactor() == 0);
    }
    SECTION("Root 2 - Insert 1,4,3,5 Remove 4") {
        core::avl::Node<Dummy>* root = &nodes[2];
        REQUIRE(root->Insert(&nodes[1]));
        REQUIRE(root->Insert(&nodes[4]));
        REQUIRE(root->Insert(&nodes[3]));
        REQUIRE(root->Insert(&nodes[5]));
        root = root->FindRoot();
        CHECK(root == &nodes[2]);
        CHECK(root->Height() == 3);
        CHECK(root->BalanceFactor() == -1);
        CHECK(root->VerifySide(Side::Left, &nodes[1]));
        CHECK(root->VerifySide(Side::Right, &nodes[4]));
        CHECK(nodes[4].VerifySide(Side::Left, &nodes[3]));
        CHECK(nodes[4].VerifySide(Side::Right, &nodes[5]));
        nodes[3].Remove();               // Middle Remove (Right Side)
        CHECK(nodes[3].IsSingular());    // e is removed
        root = root->FindRoot();
        CHECK(root == &nodes[2]);
        CHECK(root->IsRoot());    // c is still the root
        CHECK(root->Height() == 3);
        CHECK(root->VerifySide(Side::Right, &nodes[4]));
        CHECK(nodes[4].VerifySide(Side::Right, &nodes[5]));
        // c needs to be recalculated too
        CHECK(root->BalanceFactor() == -1);
    }
    SECTION("Root 2 - Insert 0,1,4,5 - Remove 2") {
        core::avl::Node<Dummy>* root = &nodes[2];
        REQUIRE(root->Insert(&nodes[0]));
        REQUIRE(root->Insert(&nodes[1]));
        REQUIRE(root->Insert(&nodes[4]));
        REQUIRE(root->Insert(&nodes[3]));
        // Remove 2, 1 should become the root (root removal)
        root->Remove();
        CHECK(nodes[1].Parent() == nullptr);    // 1 is the root (left rightmost)
        root = nodes[1].FindRoot();
        CHECK(root == &nodes[1]);
        CHECK(root->VerifySide(Side::Left, &nodes[0]));
        CHECK(root->VerifySide(Side::Right, &nodes[3]));
        CHECK(nodes[3].VerifySide(Side::Right, &nodes[4]));
    }
}

TEST_CASE("Complex Tree 1") {
    using Side = core::avl::Side;
    std::vector<core::avl::Node<Dummy>> nodes;
    // make 100 nodes, each index being it's value
    for (int i = 0; i < 100; ++i) {
        nodes.emplace_back(i);
    }
    core::avl::Node<Dummy>* root = &nodes[44];
    REQUIRE(root->Height() == 1);
    // Top Layer
    root->Insert(&nodes[17]);
    root->Insert(&nodes[78]);
    REQUIRE(root->Height() == 2);
    REQUIRE(root->BalanceFactor() == 0);
    // Next level down
    root->Insert(&nodes[12]);
    root->Insert(&nodes[32]);
    root->Insert(&nodes[50]);
    root->Insert(&nodes[88]);
    REQUIRE(root->Height() == 3);
    REQUIRE(root->BalanceFactor() == 0);
    // Next level down
    root->Insert(&nodes[8]);
    root->Insert(&nodes[14]);
    root->Insert(&nodes[28]);
    root->Insert(&nodes[36]);
    root->Insert(&nodes[48]);
    root->Insert(&nodes[62]);
    root->Insert(&nodes[84]);
    root->Insert(&nodes[92]);
    REQUIRE(root->Height() == 4);
    REQUIRE(root->BalanceFactor() == 0);
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
    REQUIRE(root->Height() == 5);

    // Next Level down
    root->Insert(&nodes[63]);
    REQUIRE(root->Height() == 6);
    CHECK(root->Count() == 31);

    REQUIRE(root->IsRoot());
    REQUIRE(root->IsConnected());
    REQUIRE(root->IsValid());
    root->PrintTree();

    SECTION("Leaf Removal") {
        REQUIRE(root->Remove(63));
        REQUIRE(root->Find(63) == nullptr);
        REQUIRE(nodes[63].IsSingular());
        CHECK(root->Count() == 30);
        CHECK(root->Height() == 5);
    }

    SECTION("Mid Tree Removal") {
        // we assume this will be the successor given the layout of the tree
        core::avl::Node<Dummy>* successor = root->Find(64);
        REQUIRE(successor != nullptr);
        REQUIRE(successor->Parent() == &nodes[62]);
        REQUIRE(successor->Parent()->Parent() == &nodes[50]);
        REQUIRE(successor->Parent()->Parent()->Parent() == &nodes[78]);
        REQUIRE(successor->Parent()->Parent()->Parent()->Parent() == root);
        REQUIRE(successor->Left() == &nodes[63]);

        REQUIRE(root->Remove(78));    // go find the node for 78 and remove it.
        root = root->FindRoot();      // update
        CHECK(root == &nodes[44]);
        CHECK(root->Height() == 5);
        REQUIRE(root->IsConnected());
        REQUIRE(root->IsValid());

        REQUIRE(nodes[78].Parent() == nullptr);
        REQUIRE(nodes[78].IsLeaf());
        REQUIRE(root->Right() != &nodes[78]);                  // successor node should not be 78
        REQUIRE(root->Right() == successor);                   // successor node should be to the right of root
        CHECK(root->Find(78) == nullptr);                      // should not be able to find it anywhere
        CHECK(root->Find(successor->Value()) == successor);    // should be able to find the successor
        CHECK(root->Count() == 30);
        CHECK(root->VerifySide(Side::Right, successor));
    }
}

TEST_CASE("Complex Tree 2") {
    // using Side = core::avl::Side;
    std::vector<core::avl::Node<Dummy>> nodes;
    // make 100 nodes, each index being it's value
    for (int i = 0; i < 100; ++i) {
        nodes.emplace_back(i);
    }
    core::avl::Node<Dummy>* root = &nodes[44];
    REQUIRE(root->Height() == 1);
    // Top Layer
    REQUIRE(root->Insert(&nodes[17]));
    REQUIRE(root->Insert(&nodes[78]));
    REQUIRE(root->Height() == 2);
    REQUIRE(root->BalanceFactor() == 0);
    // Next level down
    REQUIRE(root->Insert(&nodes[32]));
    REQUIRE(root->Insert(&nodes[50]));
    REQUIRE(root->Insert(&nodes[88]));
    REQUIRE(root->Height() == 3);
    REQUIRE(root->BalanceFactor() == 0);
    // Next level down
    REQUIRE(root->Insert(&nodes[48]));
    REQUIRE(root->Insert(&nodes[62]));
    REQUIRE(root->Height() == 4);

    SECTION("Printing") {
        root->PrintTree();
    }
    SECTION("Remove Leaf and Rebalance") {
        REQUIRE(root->Remove(32));
        root = root->FindRoot();
        REQUIRE(root->Find(32) == nullptr);
        CHECK(root->IsConnected());
        CHECK(root->IsValid());
        CHECK(root->Height() == 3);
        auto diff = reinterpret_cast<uintptr_t>(root) - reinterpret_cast<uintptr_t>(&nodes[0]);
        auto index = diff / sizeof(core::avl::Node<Dummy>);
        std::cout << "Root is now " << index << std::endl;
        REQUIRE(root == &nodes[50]);
        REQUIRE(root->Find(32) == nullptr);
        CHECK(nodes[32].IsSingular());
        CHECK(root->Count() == 7);
    }
}

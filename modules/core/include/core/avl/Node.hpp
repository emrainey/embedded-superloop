#ifndef CORE_AVL_NODE_HPP
#define CORE_AVL_NODE_HPP

#include "compiler.hpp"
#include "polyfill.hpp"

#if defined(UNITTEST)
#include <iostream>
#endif

namespace core {
/// @brief The Adelson-Velsky and Landis (AVL) tree is a self-balancing binary search tree. The objects within this space implement a simple version
/// of the AVL.
namespace avl {

enum class Side : int {
    Neither = -1,
    Left = 0,
    Right = 1,
};

/// @brief A template node wrapper class for an AVL tree.
/// @tparam TYPE The type to wrap in the node.
template <Comparible TYPE>    // C++20 Concepts FTW!
class Node {
public:
    /// @brief The balance factor minimum
    static constexpr int BalanceFactorMin{-1};

    /// @brief The balance factor maximum
    static constexpr int BalanceFactorMax{1};

    /// @brief The parameter constructor
    /// @param value
    Node(const TYPE& value)
        : parent_{nullptr}
        , left_{nullptr}
        , right_{nullptr}
        , height_{1}
        , balance_factor_{0}
        , value_{value} {}

    /// @return The mutable value
    TYPE& Value() { return value_; }
    /// @brief The const value
    TYPE const& Value() const { return value_; }
    /// @return The mutable value
    TYPE& operator()() { return Value(); }
    /// @return The const value
    TYPE const& operator()() const { return Value(); }

    /// Inserts the node into the tree
    /// @param node The node to insert
    /// @return True if inserted, false if not
    bool Insert(Node* node) {
        if (node == nullptr) {
            return false;
        }
        Insert(*node);
        ComputeHeight();
        Rebalance();
        return true;
    }

    /// @brief Finds the value in the tree
    /// @param value The value to find
    /// @return The pointer to the Node (which has the value) if found, else nullptr.
    Node* Find(TYPE const& value) {
        auto result = value <=> value_;    // C++20 3-way comparison
        if (result == 0) {
            return this;
        } else if (left_ != nullptr and result < 0) {
            return left_->Find(value);
        } else if (right_ != nullptr and result > 0) {
            return right_->Find(value);
        }
        return nullptr;    // not found
    }

    /// @brief Remove ourselves from the parent's tree and reinsert our children
    void Remove() {
        Side side = Side::Neither;
        if (parent_ == nullptr) {
            // we're the root
        } else {
            side = parent_->Disconnect(this);    // disconnect from the parent
        }
        Node** parent_side = (side == Side::Left) ? &parent_->left_ : &parent_->right_;
        if (IsLeaf()) {
            // nothing extra
        } else if (left_ != nullptr and right_ == nullptr) {
            if (parent_) {
                *parent_side = left_;
            }
            left_->parent_ = parent_;
        } else if (left_ == nullptr and right_ != nullptr) {
            if (parent_) {
                *parent_side = right_;
            }
            right_->parent_ = parent_;
        } else {
            // we have both children, so we have to pick a replacement node
            // find the rightmost child of the left child, this will be less than us
            // we could also pick left most right value which would be just larger than us
            // but smaller than the parent.
            Node* successor = left_->FindSideMost(Side::Right);
            // save the possible left child of the successor (it can't have a right child)
            Node* leftover = successor->left_;
            // remove the successor from the tree (it could have a left child)
            side = successor->parent_->Disconnect(successor);
            // TODO assert(side != Side::Right);
            // assign the left over into the place that the successor was
            successor->parent_->right_ = leftover;
            if (leftover) {
                // setup the leftover's parent to be the successor's old parent
                leftover->parent_ = successor->parent_;
            }
            if (parent_) {    // if we're not the root
                // assign the parent's side to the successor
                *parent_side = successor;
            }
            // assign the successor to our parent
            successor->parent_ = parent_;
            // assign the successor to have the left and right children of ours
            successor->left_ = left_;
            successor->right_ = right_;
            // update their parent pointers as well
            successor->left_->parent_ = successor;
            successor->right_->parent_ = successor;
        }
        // general cleanup
        // find the root node (using our parent)
        Node* root = FindRoot();
        Reset();    // new we can reset ourselves
        // recompute our heights
        root->ComputeHeight();    // visits every node! FIXME2
        root->Rebalance();        // visits every node! FIXME
    }

    /// @brief Removes a value from the tree.
    /// @param value The value to find and remove.
    /// @return true if found and removed, false if not found.
    bool Remove(TYPE const& value) {
        Node* node = Find(value);
        if (node == nullptr) {
            return false;
        }
        node->Remove();
        return true;
    }

    /// @return True if the node has no parent false otherwise.
    bool IsRoot() const { return parent_ == nullptr; }

    /// @return True if either left or right is not nullptr
    bool HasChildren() const { return left_ != nullptr or right_ != nullptr; }

    /// @return True if this node has no left or right children.
    bool IsLeaf() const { return not HasChildren(); }

    /// @return True if the node is alone by itself ( no parent or children )
    bool IsSingular() const { return IsRoot() and IsLeaf(); }

    /// @return True if the node is a valid AVL tree node.
    bool IsValid() const {
        bool left = (left_ != nullptr) ? left_->IsValid() : true;
        bool right = (right_ != nullptr) ? right_->IsValid() : true;
        bool balanced = (BalanceFactorMin <= balance_factor_ and balance_factor_ <= 1);
        return left and right and balanced;
    }

    /// @return The count of the nodes in the tree
    size_t Count() const {
        size_t count = 1;    // ourselves
        if (left_ != nullptr) {
            count += left_->Count();
        }
        if (right_ != nullptr) {
            count += right_->Count();
        }
        return count;
    }

    /// @brief Assures us that the node is connected properly in the tree
    /// @note This does not validate that the tree is balanced (thus AVL)
    bool IsConnected() const {
        bool left_ok = true;
        bool right_ok = true;
        if (left_ != nullptr) {
            if (left_->parent_ != this) {
                left_ok = false;
            } else {
                left_ok = left_->IsConnected();
            }
        }
        if (right_ != nullptr) {
            if (right_->parent_ != this) {
                return false;
            } else {
                right_ok = right_->IsConnected();
            }
        }
        return left_ok and right_ok;
    }

#if defined(UNITTEST)
    /// @return The left Node pointer
    Node* Left() const { return left_; }
    /// @return The right node pointer
    Node* Right() const { return right_; }
    /// @return The parent node pointer
    Node* Parent() const { return parent_; }
    /// @return The height of the node in the graph
    int Height() const { return height_; }
    /// @return The balance factor of this node
    int BalanceFactor() const { return balance_factor_; }

    /// @brief Finds the height of the left node
    /// @return The height value
    int FindLeftHeight() const { return (left_ != nullptr) ? left_->FindLeftHeight() + 1 : 0; }

    /// @brief Verifies that the node is connected to the parent and that the side is correct.
    /// @param side The side to check
    /// @param node The pointer to the node
    /// @return True if the node is connected to the parent and the side is correct.
    bool VerifySide(Side side, Node* node) const {
        if (side == Side::Left) {
            return left_ == node and left_->parent_ == this;
        } else if (side == Side::Right) {
            return right_ == node and right_->parent_ == this;
        }
        return false;
    }

    /// @brief Prints the node
    friend std::ostream& operator<<(std::ostream& os, Node const& node) {
        return os << "avl::Node " << &node << " Value=" << node.value_ << " H=" << node.Height() << " BF=" << node.BalanceFactor()
                  << " Parent=" << node.parent_ << " Left=" << node.left_ << " Right=" << node.right_;
    }

    /// @brief Prints the tree in order
    void PrintTree() const {
        if (left_ != nullptr) {
            left_->PrintTree();
        }
        std::cout << *this << std::endl;
        if (right_ != nullptr) {
            right_->PrintTree();
        }
    }
#endif
    /// @brief Searches up the tree to find the root node.
    /// @return The pointer to the root node. Should never be nullptr!
    Node* FindRoot() {
        Node* node = this;
        while (node->parent_ != nullptr) {
            node = node->parent_;
        }
        return node;
    }

private:
    /// Finds the farthest left or right node in the sub tree starting at this node.
    Node* FindSideMost(Side side) {
        Node* node = this;
        while (node != nullptr) {
            if (side == Side::Right) {
                if (node->right_ != nullptr) {
                    node = node->right_;
                } else {
                    break;
                }
            } else if (side == Side::Left) {
                if (node->left_ != nullptr) {
                    node = node->left_;
                } else {
                    break;
                }
            }
        }
        return node;
    }

    /// @brief Resets the node to a default state. Does not alter the value.
    void Reset() {
        parent_ = nullptr;
        left_ = nullptr;
        right_ = nullptr;
        height_ = 1;
        balance_factor_ = 0;
    }

    // called on a node to disconnect it from the tree
    Side Disconnect(Node* node) {
        if (left_ == node) {
            left_ = nullptr;
            return Side::Left;
        } else if (right_ == node) {
            right_ = nullptr;
            return Side::Right;
        }
        // don't alter node, just ourselves
        return Side::Neither;
    }

    /// @brief Updates this node to a new child from a previous child.
    /// If the previous child is not found, this is a no-op.
    /// @param prev The previous child to remove
    /// @param next The new child to update to
    void Swap(Node* prev, Node* next) {
        if (prev == left_) {
            left_ = next;
            next->parent_ = this;
        } else if (prev == right_) {
            right_ = next;
            next->parent_ = this;
        }
    }

    /// @brief Updates the balance factor of this node in the tree
    void UpdateBalanceFactor() {
        int left = left_ == nullptr ? 0 : left_->height_;
        int right = right_ == nullptr ? 0 : right_->height_;
        balance_factor_ = left - right;
    }

    /// @brief Assumes the subchildren have valid height and updates ours.
    void UpdateHeight() {
        height_ = 1;
        int left = left_ == nullptr ? 0 : left_->height_;
        int right = right_ == nullptr ? 0 : right_->height_;
        height_ += std::max(left, right);
    }

    /// @brief Recursively computes the height of the tree starting at this node.
    /// @return The new height.
    int ComputeHeight() {
        if (left_ != nullptr) {
            left_->ComputeHeight();
        }
        if (right_ != nullptr) {
            right_->ComputeHeight();
        }
        UpdateHeight();
        UpdateBalanceFactor();
        return height_;
    }

    /// @brief Inserts a new node into the tree.
    /// @param node The reference to the node to insert.
    /// @return Returns the new height under the node or INT_MIN if the insertable node is equal to the current node.
    void Insert(Node& node) {
        auto result = node.value_ <=> value_;    // C++20 3-way comparison
        if (result < 0) {
            // goes on left
            if (left_ == nullptr) {
                // this becomes our left
                left_ = &node;
                node.parent_ = this;
            } else {
                left_->Insert(node);
            }
        } else if (result > 0) {
            // goes on right
            if (right_ == nullptr) {
                // this becomes our right
                right_ = &node;
                node.parent_ = this;
            } else {
                right_->Insert(node);
            }
        } else if (result == 0) {
            //  == is not allowed so don't insert in that case!
        }
    }

    /// @brief Recursively rotates the tree to balance it.
    void Rebalance() {
        if (balance_factor_ > 1) {
            // the left has to be valid for this to be true
            // TODO assert(left_);
            if (left_ and left_->right_) {
                left_->Rotate(Side::Left);
            }
            Rotate(Side::Right);
        } else if (balance_factor_ < BalanceFactorMin) {
            // the right has to be valid for this to be true
            // TODO assert(right_);
            if (right_ and right_->left_) {
                right_->Rotate(Side::Right);
            }
            Rotate(Side::Left);
        }
        if (left_) {
            left_->Rebalance();
        }
        if (right_) {
            right_->Rebalance();
        }
    }

    /// @brief Rotates the tree to balance it.
    /// @param side The side under this node to rotate.
    void Rotate(Side side) {
        Node* leaf = (side == Side::Right) ? left_ : right_;
        if (leaf == nullptr) {
            // can't rotate on a nullptr
            return;
        }
        // the leaf's side pointer to the side we're modifying (which is opposite of the rotation)
        Node** leaf_sub = (side == Side::Right) ? &leaf->right_ : &leaf->left_;
        // our own side pointer which needs to be updated
        Node** our_sub = (side == Side::Right) ? &left_ : &right_;
        // if our parent exists, update it to point to the leaf and the leaf to point to it
        if (this->parent_) {
            this->parent_->Swap(this, leaf);
        } else {
            leaf->parent_ = nullptr;
        }
        // my parent becomes the leaf
        this->parent_ = leaf;
        // our side pointer now points to whatever the leaf's side pointer was
        *our_sub = *leaf_sub;
        if (*leaf_sub) {
            // the leaf's side pointer node parent now points to me if it exists
            (*leaf_sub)->parent_ = this;
        }
        // the leaf's side pointer (left or right) now points to me
        *leaf_sub = this;
        // all heights could be different now, recompute from the parent node
        leaf->ComputeHeight();
    }

    // == VARIABLES ============================================================

    Node* parent_;          ///< Pointer to the parent node
    Node* left_;            ///< Pointer to the left node
    Node* right_;           ///< Pointer to the right node
    int height_;            ///< The height of the tree
    int balance_factor_;    ///< The balance factor of the tree
    TYPE value_;            ///< The value of the node
};

}    // namespace avl
}    // namespace core

#endif    // CORE_AVL_NODE_HPP
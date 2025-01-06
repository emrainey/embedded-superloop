#ifndef CORE_AVL_NODE_HPP
#define CORE_AVL_NODE_HPP

#include "compiler.hpp"
#include "polyfill.hpp"

#if defined(UNITTEST)
#include <iostream>
#endif

namespace core {
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
    static constexpr int BalanceFactorMin{-1};
    static constexpr int BalanceFactorMax{1};

    Node(const TYPE& value)
        : parent_{nullptr}
        , left_{nullptr}
        , right_{nullptr}
        , height_{0}
        , balance_factor_{0}
        , value_{value} {}

    TYPE& Value() { return value_; }
    TYPE const& Value() const { return value_; }
    TYPE& operator()() { return Value(); }
    TYPE const& operator()() const { return Value(); }

    bool Insert(Node* node) {
        if (node == nullptr) {
            return false;
        }
        Insert(*node);
        ComputeHeight();
        Rebalance();
        return true;
    }

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
            *parent_side = left_;
            left_->parent_ = parent_;
        } else if (left_ == nullptr and right_ != nullptr) {
            *parent_side = right_;
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
        Node* root = FindRoot();
        // TODO assert(root);
        if (root) {
            root->ComputeHeight();
        }
        Reset();    // reset ourselves
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

#if defined(UNITTEST)
    Node* Left() const { return left_; }
    Node* Right() const { return right_; }
    Node* Parent() const { return parent_; }
    int GetHeight() const { return height_; }
    int GetBalanceFactor() const { return balance_factor_; }

    int FindLeftHeight() const { return (left_ != nullptr) ? left_->FindLeftHeight() + 1 : 0; }

    friend std::ostream& operator<<(std::ostream& os, Node const& node) {
        return os << "avl::Node " << &node << " Value=" << node.value_ << " H=" << node.GetHeight() << " BF=" << node.GetBalanceFactor()
                  << " Parent=" << node.parent_ << " Left=" << node.left_ << " Right=" << node.right_;
    }
#endif

private:
    Node* FindRoot() {
        Node* node = this;
        while (node->parent_ != nullptr) {
            node = node->parent_;
        }
        return node;
    }

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
        height_ = 0;
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

    /// @brief Updates the balance factor of this node in the tree
    void UpdateBalanceFactor() {
        int left = left_ == nullptr ? 0 : left_->height_;
        int right = right_ == nullptr ? 0 : right_->height_;
        balance_factor_ = left - right;
    }

    /// @brief Recursively computes the height of the tree starting at this node.
    /// @return The new height.
    int ComputeHeight() {
        if (IsLeaf()) {
            height_ = 0;
        } else {
            int left = left_ == nullptr ? 0 : left_->ComputeHeight();
            int right = right_ == nullptr ? 0 : right_->ComputeHeight();
            height_ = 1 + std::max(left, right);
        }
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
        // the leaf was this but now inherits my parent
        leaf->parent_ = this->parent_;
        // my parent becomes the leaf
        this->parent_ = leaf;
        // our side pointer now points to whatever the leaf's side pointer was
        *our_sub = *leaf_sub;
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
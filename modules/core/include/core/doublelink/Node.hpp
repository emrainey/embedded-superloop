#ifndef CORE_DOUBLELINK_NODE_HPP_
#define CORE_DOUBLELINK_NODE_HPP_

#include <cstdint>
#include <cstddef>
#if defined(UNITTEST)
#include <iostream>
#endif    // UNITTEST

namespace core {
namespace doublelink {
template <typename TYPE>
class Node {
public:
    /// Default constructor
    template <typename... Args>
    Node(Args&&... args)
        : prev_{this}
        , next_{this}
        , marker_{false}
        , value_{std::forward<Args>(args)...} {}

    /// Constructor with insert next on head node
    template <typename... Args>
    Node(Node& head, Args&&... args)
        : prev_{nullptr}
        , next_{nullptr}
        , marker_{false}
        , value_{std::forward<Args>(args)...} {
        InsertAfter(&head);
    }

    /// Destructor
    ~Node() { Remove(); }

    /// Returns a reference to the value
    TYPE& operator()() { return value_; }

    /// Returns a const reference to the value
    TYPE const& operator()() const { return value_; }

    /// Inserts this node on the right side of the given node
    void InsertAfter(Node& that) { InsertAfter(&that); }

    /// Inserts this node on the left side of then given node
    void InsertBefore(Node& that) { InsertBefore(&that); }

    /// Removes this node from the list
    void Remove() {
        prev_->next_ = next_;
        next_->prev_ = prev_;
        next_ = prev_ = this;
        marker_ = false;
    }

    /// Iterates over the list in the forward direction (over the next pointers)
    /// @param func The function to call for each node.
    void VisitForward(std::function<void(Node&)> func) {
        bool visited = not marker_;
        for (Node* node = this; node->marker_ != visited; node = node->next_) {
            func(*node);
            node->marker_ = visited;
        }
    }

    /// Iterates over the list in the backward direction (over the prev pointers)
    /// @param func The function to call for each node.
    void VisitBackward(std::function<void(Node&)> func) {
        bool visited = not marker_;
        for (Node* node = this; node->marker_ != visited; node = node->prev_) {
            func(*node);
            node->marker_ = visited;
        }
    }

    /// Iterates over the list in the forward direction (over the next pointers)
    /// @param func The function to call for each const node.
    void VisitForward(std::function<void(Node const&)> func) const {
        bool visited = not marker_;
        for (Node* node = this; node->marker_ != visited; node = node->next_) {
            func(*node);
            node->marker_ = visited;
        }
    }

    /// Iterates over the list in the backward direction (over the prev pointers)
    /// @param func The function to call for each const node.
    void VisitBackward(std::function<void(Node const&)> func) const {
        bool visited = not marker_;
        for (Node* node = this; node->marker_ != visited; node = node->prev_) {
            func(*node);
            node->marker_ = visited;
        }
    }

#if defined(UNITTEST)
    /// @brief Overloaded operator<< to print the node
    /// @param os The output stream
    /// @param node The node to print
    friend std::ostream& operator<<(std::ostream& os, Node const& node) {
        os << "Node " << std::hex << &node << " {prev:" << std::hex << node.prev_ << "}, {next: " << std::hex << node.next_ << "}" << node.value_;
        return os;
    }
#endif
private:
    /// Inserts this node on the right side of the given node
    void InsertAfter(Node* that) {
        if (this == that) {
            return;
        }
        this->next_ = that->next_;
        that->next_->prev_ = this;
        that->next_ = this;
        this->prev_ = that;
        this->marker_ = that->marker_;
    }

    /// Inserts this node on the left side of then given node
    void InsertBefore(Node* that) {
        if (this == that) {
            return;
        }
        this->prev_ = that->prev_;
        that->prev_->next_ = this;
        that->prev_ = this;
        this->next_ = that;
        this->marker_ = that->marker_;
    }

    Node* prev_;             ///< The previous node in the list
    Node* next_;             ///< The next node in the list
    mutable bool marker_;    ///< The marker to indicate if the node has been visited
    TYPE value_;             ///< The value of the node
};

}  // namespace doublelink
}  // namespace core

#endif    // CORE_DOUBLELINK_NODE_HPP_
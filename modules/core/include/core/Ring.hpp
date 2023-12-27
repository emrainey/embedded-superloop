#ifndef CORE_RING_HPP_
#define CORE_RING_HPP_

/// @file
/// The Ring Template

#include <cstdint>
#include <cstddef>
#include <type_traits>
#include <utility>

namespace core {

/// A simple non-overwriting Ring Template
/// @tparam TYPE The unit type
/// @tparam COUNT The number of units in the Ring
template <typename TYPE, std::size_t COUNT>
class Ring final {
public:
    /// The value type of the Stack
    using ValueType = TYPE;
    /// The pointer type to a ValueType
    using Pointer = TYPE*;
    /// The pointer to a constant ValueType
    using PointerConst = TYPE const*;
    /// The reference to a ValueType
    using Reference = TYPE&;
    /// The reference to the constant ValueType
    using ReferenceConst = TYPE const&;
    /// The index type of the array, zero based
    using IndexType = std::size_t;
    /// The size type of the array, expresses a number of bytes
    using SizeType = IndexType;
    /// The count type of the array, expresses a count of ValueTypes
    using CountType = SizeType;
    /// The iterator type
    using Iterator = Pointer;
    /// The Iterator of Constant Type
    using IteratorConst = PointerConst;

    /// The default constructor
    Ring() = default;
    /// The default destructor
    ~Ring() = default;

    /// The capacity of the buffer
    constexpr SizeType Capacity() const { return COUNT; }

    /// The number of active elements
    constexpr SizeType Count() const { return count_; }

    /// @brief Returns the active size in bytes of the Ring.
    /// @return The number of bytes consumed by the active elements.
    constexpr SizeType sSize() const { return count_ * sizeof(ValueType); }

    /// @brief Uses a Copy Assignment to put a new element into the Ring
    /// @param element The reference to the element to add
    /// @return True if it was pushed, false otherwise.
    bool Push(ReferenceConst element) {
        if (Count() < Capacity()) {
            buffer_[head_] = element;    // copy assign or simple assign
            ++count_;
            ++head_;
            if (head_ == limit_) {
                head_ = 0u;
            }
            return true;
        }
        return false;
    }

    /// @brief Uses a Copy Assign to remove an item from the Ring an copy it to the output parameter
    /// @param output The reference to the place to copy the element to.
    /// @return True when the
    bool Pop(Reference output) {
        if (Count() > 0) {
            output = buffer_[tail_];    // copy assign or simple assign
            --count_;
            ++tail_;
            if (tail_ == limit_) {
                tail_ = 0u;
            }
            return true;
        }
        return false;
    }

protected:
    ValueType buffer_[COUNT]{};
    IndexType head_{0u};              ///< Head index inclusive (only valid when count > 0)
    IndexType tail_{0u};              ///< Tail Index inclusive (only valid when count > 0)
    IndexType const limit_{COUNT};    ///< The "one-past the end" limit to the index. When equal to this value, the
                                      ///< Ring index should loop to zero.
    SizeType count_{0u};              ///< The count of the number of active elements
};

}    // namespace core

#endif    // CORE_RING_HPP_
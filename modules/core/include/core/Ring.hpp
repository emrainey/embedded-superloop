#ifndef CORE_RING_HPP_
#define CORE_RING_HPP_

/// @file
/// The Ring Template

#include <cstdint>
#include <cstddef>
#include <type_traits>
#include <utility>
#include "core/Span.hpp"

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

    /// The amount of free space in the Ring
    constexpr SizeType Spaces() const { return Capacity() - Count(); }

    /// @brief Returns the active size in bytes of the Ring.
    /// @return The number of bytes consumed by the active elements.
    constexpr SizeType Size() const { return count_ * sizeof(ValueType); }

    /// @brief Returns true when the ring buffer is empty
    constexpr bool IsEmpty() const { return Count() == 0U; }

    /// @brief Returns true when the ring buffer is full
    constexpr bool IsFull() const { return Count() == Capacity(); }

    /// @brief Uses a Copy Assignment to put a new element into the Ring
    /// @param element The reference to the element to add
    /// @return True if it was pushed, false otherwise.
    bool Push(ReferenceConst element) {
        if (Count() < Capacity()) {
            buffer_[tail_] = element;    // copy assign or simple assign
            ++count_;
            ++tail_;
            if (tail_ == limit_) {
                tail_ = 0u;
            }
            return true;
        }
        return false;
    }

    /// @brief Uses a Copy Assign to put a Span of elements into the Ring
    /// @param span The Span of elements to add
    /// @return True if it was pushed, false otherwise.
    bool Push(Span<ValueType const>& span) {
        if (span.count() <= Spaces()) {
            for (auto const& element : span) {
                buffer_[tail_] = element;    // copy assign or simple assign
                ++count_;
                ++tail_;
                if (tail_ == limit_) {
                    tail_ = 0u;
                }
            }
            return true;
        }
        return false;    // not enough space
    }

    /// @brief Uses a Copy Assign to remove an item from the Ring an copy it to the output parameter
    /// @param output The reference to the place to copy the element to.
    /// @return True when the
    bool Pop(Reference output) {
        if (Count() > 0) {
            output = buffer_[head_];    // copy assign or simple assign
            --count_;
            ++head_;
            if (head_ == limit_) {
                head_ = 0u;
            }
            if (IsEmpty()) {
                // reset the tail and head to the beginning
                tail_ = head_ = 0U;
            }
            return true;
        }
        return false;
    }

    /// @return The largest number of contiguous elements in memory (from head forward)
    SizeType MaxContiguousElements() const {
        if (IsEmpty()) {
            return 0;
        }
        if (head_ < tail_) {
            // the tail is ahead of the head, so we can just use the difference
            return tail_ - head_;
        }
        // either head_ == tail_ (full) or head_ > tail_
        // the tail is behind the head, so we can only use up to the limit
        return limit_ - head_;
    }

    /// @brief Drops a specific number of elements off the Ring off the head and does not return them
    /// @param count The number of elements to drop off the head
    /// @return True when the elements were dropped, false when not enough elements were present
    bool Drop(SizeType number) {
        if (number <= Count()) {
            while (number > 0) {
                --count_;
                ++head_;
                if (head_ == limit_) {
                    head_ = 0u;    // wrap around
                }
                --number;
            }
            return true;
        }
        return false;
    }

    /// @brief The indexing operator for mutable access
    ValueType& operator[](size_t index) {
        if (index < Count()) {
            return buffer_[(head_ + index) % limit_];
        } else {
            return buffer_[(head_ + (index % Count())) % limit_];
        }
    }

    /// @brief The indexing operator for constant access
    ValueType const& operator[](size_t index) const {
        if (index < Count()) {
            return buffer_[(head_ + index) % limit_];
        } else {
            return buffer_[(head_ + (index % Count())) % limit_];
        }
    }

protected:
    ValueType buffer_[COUNT]{};       ///< The buffer to hold the elements
    IndexType head_{0u};              ///< Head index inclusive (only valid when count > 0). Where you read from
    IndexType tail_{0u};              ///< Tail Index exclusive (only valid when count > 0). Where you write to
    IndexType const limit_{COUNT};    ///< The "one-past the end" limit to the index. When equal to this value, the
                                      ///< Ring index should loop to zero.
    SizeType count_{0u};              ///< The count of the number of active elements
};

}    // namespace core

#endif    // CORE_RING_HPP_
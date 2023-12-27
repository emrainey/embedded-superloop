#ifndef CORE_STACK_HPP_
#define CORE_STACK_HPP_

/// @file
/// The Stack Template

#include <cstdint>
#include <cstddef>
#include <type_traits>
#include <utility>

namespace core {

/// The simple Stack template index operators and iterators. Stacks are LIFO ordered.
template <typename TYPE, std::size_t COUNT>
class Stack final {
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

    /// Constructor
    Stack()
        : data_{} {}
    /// Destructor
    ~Stack() = default;

    /// Allows mutable access to the array elements in the LIFO order
    /// @warning When count() is zero, values are undefined
    ValueType& operator[](IndexType index) {
        if (count() > 0 and index < count()) {
            return data_[head_ + index];    // bounded index
        } else {
            return data_[limit_ - 1];    // return last element even if uninitialized
        }
    }

    /// Allows const access to the array elements
    /// @warning When count() is zero, values are undefined
    ReferenceConst& operator[](IndexType index) const {
        if (count() > 0 and index < count()) {
            return data_[head_ + index];    // bounded index
        } else {
            return data_[limit_ - 1];    // return last element even if uninitialized
        }
    }

    /// Writes a value to the head of the Stack
    /// @param value The value to write.
    /// @return True if written, false otherwise
    bool Push(ValueType value) {
        bool ret = false;
        if (count() < capacity()) {
            grow();
            data_[head_] = value;    // copy assign
            ret = true;
        }
        return ret;
    }

    /// Reads a value from the head of the Stack, moving the head back.
    /// @param[out] value The value to read into.
    /// @return True if read, false otherwise
    bool Pop(Reference value) {
        bool ret = false;
        if (count() > 0U) {
            value = data_[head_];
            data_[head_] = 0u;    // clear
            shrink();
            ret = true;
        }
        return ret;
    }

    /// Returns the total capacity of the Stack
    constexpr CountType capacity(void) const { return COUNT; }

    /// Return the number of _active_ elements in the Stack
    constexpr CountType count(void) const { return count_; }

    /// Returns the sizeof the _used_ Stack area in bytes
    constexpr SizeType size(void) const { return count_ * sizeof(ValueType); }

    /// Returns the beginning of the Stack
    Iterator begin(void) {
        if (count() > 0U) {
            return &data_[head_];
        } else {
            return end();
        }
    }

    /// @copydoc core::Stack::begin
    IteratorConst begin(void) const {
        if (count() > 0U) {
            return &data_[head_];
        } else {
            return end();
        }
    }

    /// Returns one-past the end of the Stack.
    /// @warning OBVIOUSLY DO NOT DEREFERENCE THIS FIELD!
    Iterator end(void) { return &data_[limit_]; }

    /// @copydoc core::Stack::end
    IteratorConst end(void) const { return &data_[limit_]; }

    /// Emplaces (constructs an object at the head location). Only usable by constructible objects.
    /// @tparam ...Args
    /// @param ...args
    /// @return True if constructed, false if otherwise
    template <typename... ARGS>
    bool emplace(ARGS&&... args) {
        static_assert(std::is_constructible<ValueType, ARGS...>::value, "Object type must be constructible with provided arguments");
        bool ret = false;
        if (count() < capacity()) {
            grow();
            ::new (static_cast<void*>(&data_[head_])) ValueType(std::forward<ARGS>(args)...);
            ret = true;
        }
        return ret;
    }

    /// Destructs an object previously constructed.
    /// @return Returns true on success, false on failure.
    bool dismiss(void) {
        static_assert(std::is_destructible<ValueType>::value, "Object must be destructible");
        bool ret = false;
        if (count() > 0U) {
            data_[head_].~ValueType();    // destruct
            shrink();
            ret = true;
        }
        return ret;
    }

protected:
    /// when releaseing a item, move the head back up until it's at the last element inclusive
    void shrink() {
        if (count_ > 1U) {
            head_++;
        }
        count_--;
    }

    /// When capturing an item, move the head down until the zeroth entry
    void grow() {
        if (count_ >= 1U) {
            head_--;
        }
        count_++;
    }

    IndexType head_{COUNT - 1U};    ///< The first element in the Stack. This the read and write location, inclusive.
    IndexType limit_{COUNT};        ///< The last element in the Stack, exclusive (technically out of bounds!)
    CountType count_{0U};           ///< The number of elements in the Stack
    ValueType data_[COUNT];         ///< The storage of the data values
};

}    // namespace core

#endif    // CORE_STACK_HPP_
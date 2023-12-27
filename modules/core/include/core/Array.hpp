#ifndef CORE_ARRAY_HPP_
#define CORE_ARRAY_HPP_

/// @file
/// The Array Template

#include <cstdint>
#include <cstddef>

namespace core {

/// The simple Array template index operators and iterators.
template <typename TYPE, std::size_t CAPACITY>
class Array final {
public:
    /// The value type of the Array
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
    Array()
        : data_{} {}

    /// Allows mutable access to the array elements
    ValueType& operator[](IndexType index) {
        if (index < CAPACITY) {
            return data_[index];
        } else {
            return data_[index % CAPACITY];    // bounded index
        }
    }

    /// Allows const access to the array elements
    const ValueType& operator[](IndexType index) const {
        if (index < CAPACITY) {
            return data_[index];
        } else {
            return data_[index % CAPACITY];    // bounded index
        }
    }

    /// Return the number of elements in the array
    constexpr CountType count(void) const { return CAPACITY; }

    /// Returns the sizeof the array itself in bytes
    constexpr SizeType size(void) const { return CAPACITY * sizeof(ValueType); }

    /// Returns the beginning of the Array
    Iterator begin(void) { return &data_[0]; }

    /// @copydoc core::Array::begin
    IteratorConst begin(void) const { return &data_[0]; }

    /// Returns one-past the Array.
    /// @warning OBVIOUSLY DO NOT DEREFERENCE THIS FIELD!
    Iterator end(void) { return &data_[CAPACITY]; }

    /// @copydoc core::Array::end
    IteratorConst end(void) const { return &data_[CAPACITY]; }

protected:
    /// The storage of the data values
    ValueType data_[CAPACITY];
};

}    // namespace core

#endif    // CORE_ARRAY_HPP_
#ifndef CORE_ARRAY_HPP_
#define CORE_ARRAY_HPP_

/// @file
/// The Array Template

#include <cstdint>
#include <cstddef>

namespace core {

/// The simple Array template index operators and iterators.
template <typename TYPE, std::size_t COUNT>
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
    Array() : m_data_{} {}

    /// Allows mutable access to the array elements
    ValueType& operator[](IndexType index) {
        if (index < COUNT) {
            return m_data_[index];
        } else {
            return m_data_[index % COUNT];    // bounded index
        }
    }

    /// Allows const access to the array elements
    const ValueType& operator[](IndexType index) const {
        if (index < COUNT) {
            return m_data_[index];
        } else {
            return m_data_[index % COUNT];    // bounded index
        }
    }

    /// Return the number of elements in the array
    constexpr CountType count(void) const { return COUNT; }

    /// Returns the sizeof the array itself in bytes
    constexpr SizeType size(void) const { return COUNT * sizeof(ValueType); }

    /// Returns the beginning of the Array
    Iterator begin(void) { return &m_data_[0]; }

    /// @copydoc core::Array::begin
    IteratorConst begin(void) const { return &m_data_[0]; }

    /// Returns one-past the Array.
    /// @warning OBVIOUSLY DO NOT DEREFERENCE THIS FIELD!
    Iterator end(void) { return &m_data_[COUNT]; }

    /// @copydoc core::Array::end
    IteratorConst end(void) const { return &m_data_[COUNT]; }

protected:
    /// The storage of the data values
    ValueType m_data_[COUNT];
};

}    // namespace core

#endif    // CORE_ARRAY_HPP_
#ifndef CORE_SPAN_HPP_
#define CORE_SPAN_HPP_

/// @file
/// The Span Template

#include <cstdint>
#include <cstddef>

namespace core {

/// The pointer and size pair template. Used to safely index or iterate over some externally controlled memory.
template <typename TYPE>
class Span final {
    // static_assert(std::is_pointer<TYPE>::value, "Must not be a pointer type");
public:
    /// The value type of the Array
    using ValueType = TYPE;
    /// The pointer type to a ValueType
    using Pointer = TYPE*;
    /// The pointer to a constant ValueType
    using Pointer_Const = TYPE const*;
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
    using IteratorConst = Pointer_Const;

    Span() : m_pointer_{nullptr}, m_count_{0U} {}
    Span(Pointer ptr, IndexType count) : m_pointer_{ptr}, m_count_{count} {}
    Span(IndexType count, Pointer ptr) : m_pointer_{ptr}, m_count_{count} {}

    template <IndexType COUNT>
    Span(TYPE (&_array)[COUNT]) : m_pointer_{&_array[0U]}, m_count_{COUNT} {}

    /// Returns the number of elements of the span.
    SizeType count() const { return m_count_; }

    ValueType& operator[](IndexType index) {
        return m_pointer_[index % m_count_];    // bounded index
    }

    const ValueType& operator[](IndexType index) const {
        return m_pointer_[index % m_count_];    // bounded index
    }

    /// Subspan operation
    Span operator()(IndexType offset, IndexType count) {
        if ((offset + count) <= m_count_) {
            return Span{&m_pointer_[offset], count};
        } else {
            return Span{};
        }
    }

    /// Returns the beginning of the Span
    Iterator begin() { return m_pointer_; }

    /// @copydoc core::Span::begin
    IteratorConst begin() const { return m_pointer_; }

    /// Returns one-past the Span.
    /// @warning OBVIOUSLY DO NOT DEREFERENCE THIS FIELD!
    Iterator end() { return m_pointer_ + m_count_; }

    /// @copydoc core::Span::end
    IteratorConst end() const { return m_pointer_ + m_count_; }

protected:
    Pointer m_pointer_;
    std::size_t m_count_;
};

}    // namespace core

#endif    // CORE_SPAN_HPP_
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

    Span()
        : pointer_{nullptr}
        , count_{0U} {}
    Span(Pointer ptr, IndexType count)
        : pointer_{ptr}
        , count_{count} {}
    Span(IndexType count, Pointer ptr)
        : pointer_{ptr}
        , count_{count} {}

    template <IndexType COUNT>
    Span(TYPE (&_array)[COUNT])
        : pointer_{&_array[0U]}
        , count_{COUNT} {}

    /// Returns the number of elements of the span.
    SizeType count() const { return count_; }
    Pointer data() { return pointer_; }
    Pointer_Const data() const { return pointer_; }

    ValueType& operator[](IndexType index) {
        if (index < count_) {
            return pointer_[index];
        }
        return pointer_[index % count_];    // bounded index
    }

    ValueType const& operator[](IndexType index) const {
        if (index < count_) {
            return pointer_[index];
        }
        return pointer_[index % count_];    // bounded index
    }

    /// Subspan operation
    Span operator()(IndexType offset, IndexType count) {
        if ((offset + count) <= count_) {
            return Span{&pointer_[offset], count};
        }
        return Span{};
    }

    /// Subspan operation
    Span subspan(IndexType offset, IndexType count) { return operator()(offset, count); }

    bool operator==(Span const& other) const { return (pointer_ == other.pointer_) && (count_ == other.count_); }
    bool operator!=(Span const& other) const { return not operator==(other); }
    explicit operator bool() const { return pointer_ != nullptr and count_ > 0u; }

    /// Returns the beginning of the Span
    Iterator begin() { return pointer_; }

    /// @copydoc core::Span::begin
    IteratorConst begin() const { return pointer_; }

    /// Returns one-past the Span.
    /// @warning OBVIOUSLY DO NOT DEREFERENCE THIS FIELD!
    Iterator end() { return pointer_ + count_; }

    /// @copydoc core::Span::end
    IteratorConst end() const { return pointer_ + count_; }

protected:
    Pointer pointer_;
    std::size_t count_;
};

}    // namespace core

#endif    // CORE_SPAN_HPP_
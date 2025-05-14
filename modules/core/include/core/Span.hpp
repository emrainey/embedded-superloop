#ifndef CORE_SPAN_HPP_
#define CORE_SPAN_HPP_

/// @file
/// The Span Template

#include <cstdint>
#include <cstddef>
#include <strings.hpp>

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

    /// @brief Default constructor
    Span()
        : pointer_{nullptr}
        , count_{0U} {}

    /// @brief Parameter Constructor
    /// @param ptr The typed pointer to the data
    /// @param count The number of elements the pointer points to
    Span(Pointer ptr, IndexType count)
        : pointer_{ptr}
        , count_{count} {}

    /// @brief Parameter Constructor
    /// @param count The number of elements the pointer points to
    /// @param ptr The typed pointer to the data
    Span(IndexType count, Pointer ptr)
        : pointer_{ptr}
        , count_{count} {}

    /// @brief The array constructor
    /// @tparam COUNT The number of elements in the array
    /// @param _array The reference to the array
    template <IndexType COUNT>
    Span(TYPE (&_array)[COUNT])
        : pointer_{&_array[0U]}
        , count_{COUNT} {}

    /// @brief Copy constructor
    /// @param other The Span to copy from
    Span(Span const& other)
        : pointer_{other.pointer_}
        , count_{other.count_} {}

    /// @brief Move constructor
    /// @param other The Span to move from
    Span(Span&& other) noexcept
        : pointer_{other.pointer_}
        , count_{other.count_} {
        other.pointer_ = nullptr;
        other.count_ = 0U;
    }

    /// @brief Copy assignment operator
    /// @param other The Span to copy from
    /// @return Reference to this Span
    Span& operator=(Span const& other) {
        if (this != &other) {
            pointer_ = other.pointer_;
            count_ = other.count_;
        }
        return *this;
    }

    /// @brief Move assignment operator
    /// @param other The Span to move from
    /// @return Reference to this Span
    Span& operator=(Span&& other) noexcept {
        if (this != &other) {
            pointer_ = other.pointer_;
            count_ = other.count_;
            other.pointer_ = nullptr;
            other.count_ = 0U;
        }
        return *this;
    }

    /// Returns the number of elements of the span.
    SizeType count() const { return count_; }

    /// @return True if the Span is empty (no elements), false otherwise
    bool IsEmpty() const { return count_ == 0U; }

    /// @return The mutable pointer to the data
    Pointer data() { return pointer_; }

    /// @return The const pointer to the data
    Pointer_Const data() const { return pointer_; }

    /// The index operator
    /// @param index The index to access. The index is wrapped if larger than the count.
    /// @return A mutable reference to the element at the index
    ValueType& operator[](IndexType index) {
        if (index < count_) {
            return pointer_[index];
        }
        return pointer_[index % count_];    // bounded index
    }

    /// The index operator
    /// @param index The index to access. The index is wrapped if larger than the count.
    /// @return A const reference to the element at the index
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

    /// Resize this span to a new size which can only be equal to or smaller than the current size.
    /// @param count The new size of the span
    /// @return A refernce to this span
    Span& resize(IndexType count) {
        if (count < count_) {
            count_ = count;
        }
        return *this;
    }

    /// @brief The equality operator
    /// @param other The other Span to compare
    /// @return True if the pointer and the count are the same
    bool operator==(Span const& other) const { return (pointer_ == other.pointer_) && (count_ == other.count_); }

    /// @brief The inequality operator
    /// @param other the other Span to compare
    /// @return False if the pointer and the count are the same
    bool operator!=(Span const& other) const { return not operator==(other); }

    /// @brief The explicit bool which allows easy checks for validity
    /// @return True if the count is positive and the pointer is not nullptr.
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
    Pointer pointer_;      ///< The pointer to the data
    std::size_t count_;    ///< The number of elements in the Span
};

/// @brief A helper function to create a Span from a string literal
/// @param literal A string literal
/// @return A Span of the string literal
/// @note The string literal is converted to a uint8_t pointer and the NUL terminator is not included in the Span's count
inline Span<uint8_t const> SpanFrom(char const* const literal) {
    return Span<uint8_t const>{reinterpret_cast<uint8_t const*>(literal), strings::length(literal)};
}

}    // namespace core

#endif    // CORE_SPAN_HPP_
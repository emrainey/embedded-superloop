#ifndef CORE_SPAN_HPP_
#define CORE_SPAN_HPP_

/// @file
/// The Span Template

#include <cstdint>
#include <cstddef>
#include <strings.hpp>

namespace core {

/// The pointer and size pair template. Used to safely index or iterate over some externally controlled memory.
template <typename TYPE, typename SIZE_TYPE>
class Span_ final {
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
    using IndexType = SIZE_TYPE;
    /// The size type of the array, expresses a number of bytes
    using SizeType = IndexType;
    /// The count type of the array, expresses a count of ValueTypes
    using CountType = SizeType;
    /// The iterator type
    using Iterator = Pointer;
    /// The Iterator of Constant Type
    using IteratorConst = Pointer_Const;

    /// @brief Default constructor
    Span_()
        : pointer_{nullptr}
        , count_{0U} {}

    /// @brief Parameter Constructor
    /// @param ptr The typed pointer to the data
    /// @param count The number of elements the pointer points to
    Span_(Pointer ptr, IndexType count)
        : pointer_{ptr}
        , count_{count} {}

    /// @brief Parameter Constructor
    /// @param count The number of elements the pointer points to
    /// @param ptr The typed pointer to the data
    Span_(IndexType count, Pointer ptr)
        : pointer_{ptr}
        , count_{count} {}

    /// @brief The array constructor
    /// @tparam COUNT The number of elements in the array
    /// @param _array The reference to the array
    template <IndexType COUNT>
    Span_(TYPE (&_array)[COUNT])
        : pointer_{&_array[0U]}
        , count_{COUNT} {}

    /// @brief Copy constructor
    /// @param other The Span_ to copy from
    Span_(Span_ const& other)
        : pointer_{other.pointer_}
        , count_{other.count_} {}

    /// @brief Move constructor
    /// @param other The Span_ to move from
    Span_(Span_&& other) noexcept
        : pointer_{other.pointer_}
        , count_{other.count_} {
        other.pointer_ = nullptr;
        other.count_ = 0U;
    }

    /// @brief Copy assignment operator
    /// @param other The Span_ to copy from
    /// @return Reference to this Span_
    Span_& operator=(Span_ const& other) {
        if (this != &other) {
            pointer_ = other.pointer_;
            count_ = other.count_;
        }
        return *this;
    }

    /// @brief Move assignment operator
    /// @param other The Span_ to move from
    /// @return Reference to this Span_
    Span_& operator=(Span_&& other) noexcept {
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

    /// Return the size of the entire span in bytes.
    SizeType size() const { return count_ * sizeof(ValueType); }

    /// @return True if the Span_ is empty (no elements), false otherwise
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
    Span_ operator()(IndexType offset, IndexType count) {
        if ((offset + count) <= count_) {
            return Span_{&pointer_[offset], count};
        }
        return Span_{};
    }

    /// Subspan operation
    Span_ subspan(IndexType offset, IndexType count) { return operator()(offset, count); }

    /// Resize this span to a new size which can only be equal to or smaller than the current size.
    /// @param count The new size of the span
    /// @return A refernce to this span
    Span_& resize(IndexType count) {
        if (count < count_) {
            count_ = count;
        }
        return *this;
    }

    /// @brief The equality operator
    /// @param other The other Span_ to compare
    /// @return True if the pointer and the count are the same
    bool operator==(Span_ const& other) const { return (pointer_ == other.pointer_) && (count_ == other.count_); }

    /// @brief The inequality operator
    /// @param other the other Span_ to compare
    /// @return False if the pointer and the count are the same
    bool operator!=(Span_ const& other) const { return not operator==(other); }

    /// @brief The explicit bool which allows easy checks for validity
    /// @return True if the count is positive and the pointer is not nullptr.
    explicit operator bool() const { return pointer_ != nullptr and count_ > 0u; }

    /// Returns the beginning of the Span_
    Iterator begin() { return pointer_; }

    /// @copydoc core::Span_::begin
    IteratorConst begin() const { return pointer_; }

    /// Returns one-past the Span_.
    /// @warning OBVIOUSLY DO NOT DEREFERENCE THIS FIELD!
    Iterator end() { return pointer_ + count_; }

    /// @copydoc core::Span_::end
    IteratorConst end() const { return pointer_ + count_; }

    /// @brief Returns a pointer to the Span data but as a different type. This works
    /// if and only if the size of the type is equal to the size of the Span_ and the alignment
    /// of the type is less than or equal to the alignment of the Span_.
    /// @warning This is a dangerous operation and should only be used if you know what you are doing! You can easily
    /// cause undefined behavior if the type is not compatible with the Span_'s data.
    /// @tparam OTHER_TYPE The type to cast to
    /// @return A pointer to the data as the OTHER_TYPE, or nullptr if the size or alignment does not match.
    template <typename OTHER_TYPE>
    OTHER_TYPE* as_single(void) const {
        if (size() == sizeof(OTHER_TYPE) and alignof(OTHER_TYPE) <= alignof(ValueType)) {
            return reinterpret_cast<OTHER_TYPE*>(pointer_);
        } else {
            return nullptr;    // size or align mismatch
        }
    }

protected:
    Pointer pointer_;      ///< The pointer to the data
    std::size_t count_;    ///< The number of elements in the Span_
};

/// @brief A normal span for most use cases.
/// @tparam TYPE The unit of the Span
template <typename TYPE>
using Span = Span_<TYPE, std::size_t>;

/// @brief A helper function to create a Span from a string literal
/// @param literal A string literal
/// @return A Span_ of the string literal
/// @note The string literal is converted to a uint8_t pointer and the NUL terminator is not included in the Span_'s count
inline Span<uint8_t const> SpanFrom(char const* const literal) {
    return Span<uint8_t const>{reinterpret_cast<uint8_t const*>(literal), strings::length(literal)};
}

}    // namespace core

#endif    // CORE_SPAN_HPP_
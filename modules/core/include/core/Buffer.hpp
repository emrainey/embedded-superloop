#pragma once

/// @file
/// core::Buffer Interface

#include <cstdint>
#include <cstddef>

#include <core/Span.hpp>
#include <core/Allocator.hpp>

namespace core {

/// @brief A Buffer is a simple wrapper around a pointer to a block of memory which knows it's Allocator.
template <typename TYPE>
struct Buffer {
    /// @brief The type of the Allocator
    using Type = TYPE;
    /// @brief The pointer to the type
    using Pointer = TYPE*;
    /// @brief The reference to the type
    using Reference = TYPE&;
    /// @brief The type used to express sizes
    using Size = std::size_t;
    /// @brief The type used to express counts
    using Count = std::size_t;
    /// @brief  The type used to express indices
    using Index = std::size_t;

    /// @brief The default allocator to use for the Buffer
    /// @note Uses the default allocator
    Buffer()
        : allocator_{GetDefaultAllocator()}
        , pointer_{nullptr}
        , count_{0U} {}

    /// @brief The parameter allocator to use for the Buffer
    /// @param allocator The allocator to use for the Buffer
    Buffer(Allocator& allocator)
        : allocator_{allocator}
        , pointer_{nullptr}
        , count_{0U} {}

    /// @brief The parameter allocator and count to use for the Buffer
    /// @param count The number of elements to allocate
    /// @param allocator The allocator to use for the Buffer
    Buffer(Count count, Allocator& allocator)
        : allocator_{allocator}
        , pointer_{reinterpret_cast<Pointer>(allocator_.allocate(count * sizeof(Type), alignof(Type)))}
        , count_{count} {
        if (pointer_ == nullptr) {
            count_ = 0U;
        }
    }

    /// @brief The parameter count to use for the Buffer
    /// @param count The number of elements to allocate
    /// @note Uses the default allocator
    Buffer(Count count)
        : Buffer{count, GetDefaultAllocator()} {}

    /// No Copy Constructor
    Buffer(Buffer const&) = delete;

    /// Move Construction is allowed
    Buffer(Buffer&& other)
        : allocator_{other.allocator_}
        , pointer_{other.pointer_}
        , count_{other.count_} {
        other.pointer_ = nullptr;
        other.count_ = 0U;
    }

    /// Copy Assign is not allowed
    Buffer& operator=(Buffer const&) = delete;

    /// Move Assignment is allowed
    Buffer& operator=(Buffer&& other) {
        if (this != &other) {
            this->Release();
            pointer_ = other.pointer_;
            count_ = other.count_;
            allocator_ = other.allocator_;
            other.pointer_ = nullptr;
            other.count_ = 0U;
        }
        return *this;
    }

    /// Deallocates the memory if it is not empty
    ~Buffer() { Release(); }

    /// @return True if the count is zero
    bool IsEmpty() const { return count() == 0U; }

    /// @return The number of bytes allocated
    Size size() const { return count_ * sizeof(Type); }

    /// @return The number of elements allocated
    Count count() const { return count_; }

    /// @return A span to the allocated memory
    Span<Type> as_span() { return Span<Type>{pointer_, count_}; }

    /// @return A span to the allocated memory as `const` type.
    Span<Type const> as_span() const { return Span<Type const>{pointer_, count_}; }

    /// @return A pointer to the allocated memory as a different type than allocated
    template <typename OtherType>
    Span<OtherType> as_span() {
        static_assert(alignof(OtherType) <= alignof(Type), "Alignment of OtherType must be less than or equal to Type");
        static_assert(sizeof(OtherType) <= sizeof(Type), "Size of OtherType must be less than or equal to Type");
        return Span<OtherType>{reinterpret_cast<OtherType*>(pointer_), (count_ * sizeof(Type)) / sizeof(OtherType)};
    }

    /// @return A pointer to the allocated memory as a different type than allocated
    template <typename OtherType>
    Span<OtherType const> as_span() const {
        static_assert(alignof(OtherType) <= alignof(Type), "Alignment of OtherType must be less than or equal to Type");
        static_assert(sizeof(OtherType) <= sizeof(Type), "Size of OtherType must be less than or equal to Type");
        return Span<OtherType const>{reinterpret_cast<OtherType const*>(pointer_), (count_ * sizeof(Type)) / sizeof(OtherType)};
    }

    /// @brief Releases any held memory and sets the internal state to empty
    void Release() {
        if (not IsEmpty()) {
            allocator_.deallocate(pointer_, size(), alignof(Type));
            pointer_ = nullptr;
            count_ = 0U;
        }
    }

protected:
    Allocator& allocator_;    ///< The reference to the allocator
    Pointer pointer_;         ///< The pointer to the allocated memory
    Count count_;             ///< The count of the number of elements allocated
};

}    // namespace core
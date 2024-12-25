#pragma once

#include <cstdint>
#include <cstddef>

#include <core/Span.hpp>
#include <core/Allocator.hpp>

namespace core {

template <typename TYPE>
struct Buffer {
    using Type = TYPE;
    using Pointer = TYPE*;
    using Reference = TYPE&;
    using Size = std::size_t;
    using Count = std::size_t;
    using Index = std::size_t;

    Buffer()
        : allocator_{GetDefaultAllocator()}
        , pointer_{nullptr}
        , count_{0U} {}

    Buffer(Allocator& allocator)
        : allocator_{allocator}
        , pointer_{nullptr}
        , count_{0U} {}

    Buffer(Count count, Allocator& allocator)
        : allocator_{allocator}
        , pointer_{reinterpret_cast<Pointer>(allocator_.allocate(count * sizeof(Type), alignof(Type)))}
        , count_{count} {
        if (pointer_ == nullptr) {
            count_ = 0U;
        }
    }

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
            this->~Buffer();
            pointer_ = other.pointer_;
            count_ = other.count_;
            allocator_ = other.allocator_;
            other.pointer_ = nullptr;
            other.count_ = 0U;
        }
        return *this;
    }

    ~Buffer() {
        if (not IsEmpty()) {
            allocator_.deallocate(pointer_, size(), alignof(Type));
            pointer_ = nullptr;
            count_ = 0U;
        }
    }

    bool IsEmpty() const { return count() == 0U; }

    Size size() const { return count_ * sizeof(Type); }

    Count count() const { return count_; }

    Span<Type> as_span() { return Span<Type>{pointer_, count_}; }

    Span<Type const> as_span() const { return Span<Type const>{pointer_, count_}; }

    template <typename OtherType>
    Span<OtherType> as_span() {
        static_assert(alignof(OtherType) <= alignof(Type), "Alignment of OtherType must be less than or equal to Type");
        static_assert(sizeof(OtherType) <= sizeof(Type), "Size of OtherType must be less than or equal to Type");
        return Span<OtherType>{reinterpret_cast<OtherType*>(pointer_), (count_ * sizeof(Type)) / sizeof(OtherType)};
    }

    template <typename OtherType>
    Span<OtherType const> as_span() const {
        static_assert(alignof(OtherType) <= alignof(Type), "Alignment of OtherType must be less than or equal to Type");
        static_assert(sizeof(OtherType) <= sizeof(Type), "Size of OtherType must be less than or equal to Type");
        return Span<OtherType const>{reinterpret_cast<OtherType const*>(pointer_), (count_ * sizeof(Type)) / sizeof(OtherType)};
    }

protected:
    Allocator& allocator_;
    Pointer pointer_;
    Count count_;
};

}    // namespace core
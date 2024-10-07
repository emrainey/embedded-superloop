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

    Buffer(Allocator& allocator)
        : allocator_{allocator}
        , pointer_{nullptr}
        , count_{0U} {}

    Buffer(Size bytes, Allocator& allocator)
        : allocator_{allocator}
        , pointer_{reinterpret_cast<Pointer>(allocator_.allocate(bytes, alignof(Type)))}
        , count_{0U} {
        if (pointer_ == nullptr) {
            count_ = 0U;
        } else {
            count_ = bytes / sizeof(Type);
        }
    }

    Buffer(Buffer const&) = delete;

    Buffer(Buffer&& other)
        : allocator_{other.allocator_}
        , pointer_{other.pointer_}
        , count_{other.count_} {
        other.pointer_ = nullptr;
        other.count_ = 0U;
    }

    Buffer& operator=(Buffer const&) = delete;

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
        }
    }

    bool IsEmpty() const { return count() == 0U; }

    Size size() const { return count_ * sizeof(Type); }

    Count count() const { return count_; }

    Span<Type> span() { return Span<Type>{pointer_, count_}; }

    Span<Type const> span() const { return Span<Type const>{pointer_, count_}; }

protected:
    Allocator& allocator_;
    Pointer pointer_;
    Count count_;
};

}    // namespace core
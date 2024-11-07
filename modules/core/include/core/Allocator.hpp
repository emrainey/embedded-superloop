#pragma once

#include <cstdint>
#include <cstddef>

namespace core {

class Allocator {
public:
    virtual void* allocate(std::size_t bytes, std::size_t alignment = alignof(std::max_align_t)) = 0;
    virtual void deallocate(void* p, std::size_t bytes, std::size_t alignment = alignof(std::max_align_t)) = 0;

protected:
    ~Allocator() = default;
};

extern Allocator& GetDefaultAllocator() noexcept;

}    // namespace core

#include "core/BitMapHeap.hpp"

#if not defined(DEFAULT_ALLOCATION_BLOCK_SIZE)
#define DEFAULT_ALLOCATION_BLOCK_SIZE 32U
#endif

#if not defined(DEFAULT_ALLOCATION_BLOCK_COUNT)
#define DEFAULT_ALLOCATION_BLOCK_COUNT 32'768U
#endif

namespace core {
Allocator& GetDefaultAllocator() noexcept {
    static BitMapHeap<DEFAULT_ALLOCATION_BLOCK_SIZE, DEFAULT_ALLOCATION_BLOCK_COUNT> defaultAllocator{nullptr, 0U};
    return defaultAllocator;
}
}    // namespace core
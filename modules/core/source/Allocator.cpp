#include "core/BitMapHeap.hpp"

#if not defined(DEFAULT_ALLOCATION_BLOCK_SIZE)
#define DEFAULT_ALLOCATION_BLOCK_SIZE 32U
#endif

#if not defined(DEFAULT_ALLOCATION_BLOCK_COUNT)
#define DEFAULT_ALLOCATION_BLOCK_COUNT 32'768U
#endif

namespace core {
Allocator& GetDefaultAllocator() noexcept {
    static constexpr size_t AlignmentSize = alignof(std::max_align_t);
    alignas(AlignmentSize) static uint8_t heap_storage[DEFAULT_ALLOCATION_BLOCK_SIZE * DEFAULT_ALLOCATION_BLOCK_COUNT];
    static BitMapHeap<DEFAULT_ALLOCATION_BLOCK_SIZE, DEFAULT_ALLOCATION_BLOCK_COUNT, AlignmentSize> default_allocator{
        heap_storage, sizeof(heap_storage)
    };
    return default_allocator;
}
}    // namespace core
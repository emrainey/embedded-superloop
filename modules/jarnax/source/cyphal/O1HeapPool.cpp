#include "jarnax/cyphal/O1HeapPool.hpp"

extern "C" {
#include "o1heap.h"
}

namespace jarnax {
namespace cyphal {

namespace {

alignas(O1HEAP_ALIGNMENT) std::uint8_t arena[O1HeapPool::ArenaSize];

O1HeapInstance& HeapInstance() {
    static O1HeapInstance* const instance = o1heapInit(arena, sizeof(arena));
    return *instance;
}

}    // namespace

O1HeapPool& O1HeapPool::Instance() {
    static O1HeapPool instance;
    return instance;
}

void* O1HeapPool::allocate(std::size_t bytes, std::size_t alignment) {
    if (alignment > O1HEAP_ALIGNMENT) {
        return nullptr;
    }
    return o1heapAllocate(&HeapInstance(), bytes);
}

void O1HeapPool::deallocate(void* pointer, std::size_t bytes, std::size_t alignment) {
    (void)bytes;
    (void)alignment;
    o1heapFree(&HeapInstance(), pointer);
}

UdpardMemoryResource O1HeapPool::GetMemoryResource() {
    return {
        .user_reference = this,
        .deallocate = &O1HeapPool::UdpardDeallocate,
        .allocate = &O1HeapPool::UdpardAllocate,
    };
}

UdpardRxMemoryResources O1HeapPool::GetRxMemoryResources() {
    UdpardMemoryResource const memory = GetMemoryResource();
    return {
        .session = memory,
        .fragment = memory,
        .payload = {
            .user_reference = this,
            .deallocate = &O1HeapPool::UdpardDeallocate,
        },
    };
}

void* O1HeapPool::UdpardAllocate(void* context, std::size_t bytes) {
    auto* const allocator = static_cast<core::Allocator*>(context);
    return allocator->allocate(bytes);
}

void O1HeapPool::UdpardDeallocate(void* context, std::size_t bytes, void* pointer) {
    auto* const allocator = static_cast<core::Allocator*>(context);
    allocator->deallocate(pointer, bytes);
}

}    // namespace cyphal
}    // namespace jarnax
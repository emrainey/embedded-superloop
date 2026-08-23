#ifndef JARNAX_CYPHAL_O1HEAP_POOL_HPP
#define JARNAX_CYPHAL_O1HEAP_POOL_HPP

#include <cstddef>
#include <cstdint>

#include "core/Allocator.hpp"

extern "C" {
#include "udpard.h"
}

namespace jarnax {
namespace cyphal {

/// @brief A fixed O1Heap arena shared by Cyphal/UDP allocations.
class O1HeapPool final : public core::Allocator {
public:
    static O1HeapPool& Instance();

    static constexpr std::size_t ArenaSize{65536U};

    void* allocate(std::size_t bytes, std::size_t alignment = alignof(std::max_align_t)) override;
    void deallocate(void* pointer, std::size_t bytes, std::size_t alignment = alignof(std::max_align_t)) override;

    UdpardMemoryResource GetMemoryResource();
    UdpardRxMemoryResources GetRxMemoryResources();

private:
    O1HeapPool() = default;

    static void* UdpardAllocate(void* context, std::size_t bytes);
    static void UdpardDeallocate(void* context, std::size_t bytes, void* pointer);
};

}    // namespace cyphal
}    // namespace jarnax

#endif    // JARNAX_CYPHAL_O1HEAP_POOL_HPP
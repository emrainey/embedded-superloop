#include <gtest/gtest.h>

#include <cstdint>

#include "core/Allocator.hpp"
#include "jarnax/cyphal/O1HeapPool.hpp"

namespace {

class O1HeapPoolTest : public ::testing::Test {
protected:
    jarnax::cyphal::O1HeapPool& pool_{jarnax::cyphal::O1HeapPool::Instance()};
    core::Allocator& allocator_{pool_};
};

TEST_F(O1HeapPoolTest, Empty) {
    EXPECT_NE(&pool_, nullptr);
}

TEST_F(O1HeapPoolTest, AllocatesAndDeallocatesThroughAllocatorInterface) {
    void* const first = allocator_.allocate(64U, alignof(std::uint64_t));

    ASSERT_NE(first, nullptr);
    allocator_.deallocate(first, 64U, alignof(std::uint64_t));

    void* const second = allocator_.allocate(64U, alignof(std::uint64_t));
    ASSERT_NE(second, nullptr);
    allocator_.deallocate(second, 64U, alignof(std::uint64_t));
}

TEST_F(O1HeapPoolTest, OverAlignedAllocationsAreServedAtMaxAlignment) {
    // o1heap does not reject alignment requests beyond max_align_t; it serves the
    // block at its own (max_align_t) granularity instead.
    // O1HEAP_ALIGNMENT is sizeof(void*) * 2 on every platform, so requesting
    // sizeof(void*) * 4 is always beyond the pool's granularity.
    void* const pointer = allocator_.allocate(1U, sizeof(void*) * 4U);
    ASSERT_NE(pointer, nullptr);
    EXPECT_EQ(reinterpret_cast<std::uintptr_t>(pointer) % alignof(std::max_align_t), 0U);
    allocator_.deallocate(pointer, 1U, sizeof(void*) * 4U);
}

TEST_F(O1HeapPoolTest, ProvidesUdpardMemoryCallbacks) {
    UdpardMemoryResource const memory = pool_.GetMemoryResource();
    void* const allocation = memory.allocate(memory.user_reference, 64U);

    ASSERT_NE(allocation, nullptr);
    memory.deallocate(memory.user_reference, 64U, allocation);
}

TEST_F(O1HeapPoolTest, ProvidesUdpardReceiveMemoryResources) {
    UdpardRxMemoryResources const memory = pool_.GetRxMemoryResources();
    void* const allocation = memory.session.allocate(memory.session.user_reference, 64U);

    ASSERT_NE(allocation, nullptr);
    memory.payload.deallocate(memory.payload.user_reference, 64U, allocation);
}

}    // namespace
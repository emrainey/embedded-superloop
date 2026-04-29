#include <catch2/catch_test_macros.hpp>
#include "core/BitMapHeap.hpp"

/// @brief A small heap with 32 blocks of 32 bytes each
using SmallHeap = core::BitMapHeap<32U, 32U, alignof(std::max_align_t)>;

TEST_CASE("BitMapHeap - Simple") {
    alignas(16) uint8_t storage[1024];
    SmallHeap heap(storage, sizeof(storage), nullptr);
    SECTION("Stats") {
        CHECK(heap.GetStatistics().size_bytes == 1024U);
        CHECK(heap.GetStatistics().used_blocks == 0U);
        CHECK(heap.GetStatistics().free_blocks == 32U);
        CHECK(heap.GetStatistics().waste_bytes == 0U);
        CHECK(heap.GetStatistics().count == 0U);
    }
    SECTION("Single") {
        static constexpr std::size_t AllocSize = 16U;
        core::Buffer<uint8_t> buffer{AllocSize, heap};
        CHECK(buffer.capacity() == AllocSize);
        CHECK(buffer.size() == AllocSize);
        CHECK(not buffer.IsEmpty());
        CHECK(heap.GetStatistics().size_bytes == 1024U);
        CHECK(heap.GetStatistics().used_blocks == 1U);
        CHECK(heap.GetStatistics().free_blocks == 31U);
        CHECK(heap.GetStatistics().waste_bytes == 16U);
        CHECK(heap.GetStatistics().count == 1U);
    }
    SECTION("Double") {
        static constexpr std::size_t AllocSize = 16U;
        core::Buffer<uint8_t> buffer1{AllocSize, heap};
        core::Buffer<uint8_t> buffer2{AllocSize, heap};
        CHECK(buffer1.capacity() == AllocSize);
        CHECK(buffer1.size() == AllocSize);
        CHECK(not buffer1.IsEmpty());
        CHECK(buffer2.capacity() == AllocSize);
        CHECK(buffer2.size() == AllocSize);
        CHECK(not buffer2.IsEmpty());
        CHECK(heap.GetStatistics().size_bytes == 1024U);
        CHECK(heap.GetStatistics().used_blocks == 2U);
        CHECK(heap.GetStatistics().free_blocks == 30U);
        CHECK(heap.GetStatistics().waste_bytes == 32U);
        CHECK(heap.GetStatistics().count == 2U);
    }
    SECTION("Fill") {
        static constexpr std::size_t AllocSize = 16U;
        std::vector<core::Buffer<uint8_t>> buffers;
        for (size_t i = 0u; i < 32U; i++) {
            buffers.emplace_back(AllocSize, heap);
            CHECK(not buffers.back().IsEmpty());
            CHECK(buffers.back().capacity() == AllocSize);
            CHECK(buffers.back().size() == AllocSize);
        }
        CHECK(heap.GetStatistics().size_bytes == 1024U);
        CHECK(heap.GetStatistics().used_blocks == 32U);
        CHECK(heap.GetStatistics().free_blocks == 0U);
        CHECK(heap.GetStatistics().waste_bytes == 32 * 16U);
        CHECK(heap.GetStatistics().count == 32U);
        for (size_t i = 0u; i < 32U; i++) {
            buffers[i].~Buffer();    // destruct
        }
        CHECK(heap.GetStatistics().size_bytes == 1024U);
        CHECK(heap.GetStatistics().used_blocks == 0U);
        CHECK(heap.GetStatistics().free_blocks == 32U);
        CHECK(heap.GetStatistics().waste_bytes == 0U);
        CHECK(heap.GetStatistics().count == 0U);
    }
}

TEST_CASE("Buffers Casting Down") {
    alignas(16) uint8_t storage[1024];
    SmallHeap heap(storage, sizeof(storage), nullptr);
    core::Buffer<uint32_t> buffer1{32U, heap};
    core::Span<uint32_t> span1 = buffer1.as_span();
    SECTION("Check Equal") {
        CHECK(span1.count() == 32U);
        void* tmp = &storage[0];
        CHECK(span1.data() == tmp);
    }

    SECTION("Casting Down Bytes") {
        core::Span<uint8_t> span2 = buffer1.as_span<uint8_t>();
        CHECK(span2.count() == 128U);
        CHECK(span2.data() == reinterpret_cast<uint8_t*>(span1.data()));
    }
    SECTION("Casting Down Shorts") {
        core::Span<uint16_t> span2 = buffer1.as_span<uint16_t>();
        CHECK(span2.count() == 64U);
        CHECK(span2.data() == reinterpret_cast<uint16_t*>(span1.data()));
    }
}

// TEST_CASE("Buffers Casting Up") {
//     alignas(16) uint8_t storage[1024];
//     SmallHeap heap(storage, sizeof(storage), nullptr);
//     core::Buffer<uint8_t> buffer1{32U, heap};
//     core::Span<uint8_t> span1 = buffer1.span();
//     SECTION("Check Equal") {
//         CHECK(span1.count() == 32U);
//         void* tmp = &storage[0];
//         CHECK(span1.data() == tmp);
//     }
//     SECTION("Casting Up Short") {
//         core::Span<uint16_t> span2 = buffer1.span<uint16_t>();
//         CHECK(span2.count() == 8U);
//         CHECK(span2.data() == reinterpret_cast<uint16_t*>(span1.data()));
//     }
//     SECTION("Casting Up Shorts") {
//         core::Span<uint32_t> span2 = buffer1.span<uint32_t>();
//         CHECK(span2.count() == 8U);
//         CHECK(span2.data() == reinterpret_cast<uint32_t*>(span1.data()));
//     }
// }

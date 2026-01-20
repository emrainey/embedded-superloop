#include <catch2/catch_test_macros.hpp>
#include "core/BitMapHeap.hpp"

/// @brief A small heap with 32 blocks of 32 bytes each
using SmallHeap = core::BitMapHeap<32U, 32U, alignof(std::max_align_t)>;

TEST_CASE("BitMapHeap - Simple") {
    alignas(8) uint8_t storage[1024];
    SmallHeap heap(storage, sizeof(storage), nullptr);
    SECTION("Stats") {
        REQUIRE(heap.GetStatistics().size_bytes == 1024U);
        REQUIRE(heap.GetStatistics().used_blocks == 0U);
        REQUIRE(heap.GetStatistics().free_blocks == 32U);
        REQUIRE(heap.GetStatistics().waste_bytes == 0U);
        REQUIRE(heap.GetStatistics().count == 0U);
    }
    SECTION("Single") {
        static constexpr std::size_t AllocSize = 16U;
        core::Buffer<uint8_t> buffer{AllocSize, heap};
        REQUIRE(buffer.capacity() == AllocSize);
        REQUIRE(buffer.size() == AllocSize);
        REQUIRE(not buffer.IsEmpty());
        REQUIRE(heap.GetStatistics().size_bytes == 1024U);
        REQUIRE(heap.GetStatistics().used_blocks == 1U);
        REQUIRE(heap.GetStatistics().free_blocks == 31U);
        REQUIRE(heap.GetStatistics().waste_bytes == 16U);
        REQUIRE(heap.GetStatistics().count == 1U);
    }
    SECTION("Double") {
        static constexpr std::size_t AllocSize = 16U;
        core::Buffer<uint8_t> buffer1{AllocSize, heap};
        core::Buffer<uint8_t> buffer2{AllocSize, heap};
        REQUIRE(buffer1.capacity() == AllocSize);
        REQUIRE(buffer1.size() == AllocSize);
        REQUIRE(not buffer1.IsEmpty());
        REQUIRE(buffer2.capacity() == AllocSize);
        REQUIRE(buffer2.size() == AllocSize);
        REQUIRE(not buffer2.IsEmpty());
        REQUIRE(heap.GetStatistics().size_bytes == 1024U);
        REQUIRE(heap.GetStatistics().used_blocks == 2U);
        REQUIRE(heap.GetStatistics().free_blocks == 30U);
        REQUIRE(heap.GetStatistics().waste_bytes == 32U);
        REQUIRE(heap.GetStatistics().count == 2U);
    }
    SECTION("Fill") {
        static constexpr std::size_t AllocSize = 16U;
        std::vector<core::Buffer<uint8_t>> buffers;
        for (size_t i = 0u; i < 32U; i++) {
            buffers.emplace_back(AllocSize, heap);
            REQUIRE(not buffers.back().IsEmpty());
            REQUIRE(buffers.back().capacity() == AllocSize);
            REQUIRE(buffers.back().size() == AllocSize);
        }
        REQUIRE(heap.GetStatistics().size_bytes == 1024U);
        REQUIRE(heap.GetStatistics().used_blocks == 32U);
        REQUIRE(heap.GetStatistics().free_blocks == 0U);
        REQUIRE(heap.GetStatistics().waste_bytes == 32 * 16U);
        REQUIRE(heap.GetStatistics().count == 32U);
        for (size_t i = 0u; i < 32U; i++) {
            buffers[i].~Buffer();    // destruct
        }
        REQUIRE(heap.GetStatistics().size_bytes == 1024U);
        REQUIRE(heap.GetStatistics().used_blocks == 0U);
        REQUIRE(heap.GetStatistics().free_blocks == 32U);
        REQUIRE(heap.GetStatistics().waste_bytes == 0U);
        REQUIRE(heap.GetStatistics().count == 0U);
    }
}

TEST_CASE("Buffers Casting Down") {
    alignas(8) uint8_t storage[1024];
    SmallHeap heap(storage, sizeof(storage), nullptr);
    core::Buffer<uint32_t> buffer1{32U, heap};
    core::Span<uint32_t> span1 = buffer1.as_span();
    SECTION("Check Equal") {
        REQUIRE(span1.count() == 32U);
        void* tmp = &storage[0];
        REQUIRE(span1.data() == tmp);
    }

    SECTION("Casting Down Bytes") {
        core::Span<uint8_t> span2 = buffer1.as_span<uint8_t>();
        REQUIRE(span2.count() == 128U);
        REQUIRE(span2.data() == reinterpret_cast<uint8_t*>(span1.data()));
    }
    SECTION("Casting Down Shorts") {
        core::Span<uint16_t> span2 = buffer1.as_span<uint16_t>();
        REQUIRE(span2.count() == 64U);
        REQUIRE(span2.data() == reinterpret_cast<uint16_t*>(span1.data()));
    }
}

// TEST_CASE("Buffers Casting Up") {
//     alignas(8) uint8_t storage[1024];
//     SmallHeap heap(storage, sizeof(storage), nullptr);
//     core::Buffer<uint8_t> buffer1{32U, heap};
//     core::Span<uint8_t> span1 = buffer1.span();
//     SECTION("Check Equal") {
//         REQUIRE(span1.count() == 32U);
//         void* tmp = &storage[0];
//         REQUIRE(span1.data() == tmp);
//     }
//     SECTION("Casting Up Short") {
//         core::Span<uint16_t> span2 = buffer1.span<uint16_t>();
//         REQUIRE(span2.count() == 8U);
//         REQUIRE(span2.data() == reinterpret_cast<uint16_t*>(span1.data()));
//     }
//     SECTION("Casting Up Shorts") {
//         core::Span<uint32_t> span2 = buffer1.span<uint32_t>();
//         REQUIRE(span2.count() == 8U);
//         REQUIRE(span2.data() == reinterpret_cast<uint32_t*>(span1.data()));
//     }
// }

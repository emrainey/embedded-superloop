#include <catch2/catch_test_macros.hpp>
#include "core/BitMapHeap.hpp"
#include "core/Buffer.hpp"

TEST_CASE("Buffer - Default Constructor") {
    SECTION("Default constructor uses default allocator") {
        core::Buffer<uint8_t> buffer;
        REQUIRE(buffer.IsEmpty());
        REQUIRE(buffer.capacity() == 0U);
        REQUIRE(buffer.size() == 0U);
    }
}

TEST_CASE("Buffer - Constructor with Allocator") {
    alignas(8) uint8_t storage[1024];
    core::BitMapHeap<32U, 32U> heap(storage, sizeof(storage), nullptr);

    SECTION("Constructor with allocator only creates empty buffer") {
        core::Buffer<uint32_t> buffer{heap};
        REQUIRE(buffer.IsEmpty());
        REQUIRE(buffer.capacity() == 0U);
        REQUIRE(buffer.size() == 0U);
    }

    SECTION("Constructor with count and allocator") {
        core::Buffer<uint32_t> buffer{10U, heap};
        REQUIRE_FALSE(buffer.IsEmpty());
        REQUIRE(buffer.capacity() == 10U);
        REQUIRE(buffer.size() == 40U);    // 10 * sizeof(uint32_t)
    }

    SECTION("Constructor with count using default allocator") {
        core::Buffer<uint16_t> buffer{20U};
        REQUIRE_FALSE(buffer.IsEmpty());
        REQUIRE(buffer.capacity() == 20U);
        REQUIRE(buffer.size() == 40U);    // 20 * sizeof(uint16_t)
    }
}

TEST_CASE("Buffer - Zero-size Allocation") {
    alignas(8) uint8_t storage[1024];
    core::BitMapHeap<32U, 32U> heap(storage, sizeof(storage), nullptr);

    SECTION("Zero-size allocation creates empty buffer") {
        core::Buffer<uint8_t> buffer{0U, heap};
        REQUIRE(buffer.IsEmpty());
        REQUIRE(buffer.capacity() == 0U);
        REQUIRE(buffer.size() == 0U);
    }
}

TEST_CASE("Buffer - Move Constructor") {
    alignas(8) uint8_t storage[1024];
    core::BitMapHeap<32U, 32U> heap(storage, sizeof(storage), nullptr);

    SECTION("Move constructor transfers ownership") {
        core::Buffer<uint32_t> buffer1{10U, heap};
        REQUIRE(buffer1.capacity() == 10U);
        REQUIRE_FALSE(buffer1.IsEmpty());

        core::Buffer<uint32_t> buffer2{std::move(buffer1)};
        REQUIRE(buffer2.capacity() == 10U);
        REQUIRE(buffer2.size() == 40U);
        REQUIRE_FALSE(buffer2.IsEmpty());

        // Original buffer should be empty after move
        REQUIRE(buffer1.IsEmpty());
        REQUIRE(buffer1.capacity() == 0U);
        REQUIRE(buffer1.size() == 0U);
    }

    SECTION("Move constructor with empty buffer") {
        core::Buffer<uint32_t> buffer1{heap};
        REQUIRE(buffer1.IsEmpty());

        core::Buffer<uint32_t> buffer2{std::move(buffer1)};
        REQUIRE(buffer2.IsEmpty());
        REQUIRE(buffer1.IsEmpty());
    }
}

TEST_CASE("Buffer - Move Assignment") {
    alignas(8) uint8_t storage[2048];
    core::BitMapHeap<64U, 32U> heap(storage, sizeof(storage), nullptr);

    SECTION("Move assignment transfers ownership") {
        core::Buffer<uint32_t> buffer1{10U, heap};
        core::Buffer<uint32_t> buffer2{5U, heap};

        REQUIRE(buffer1.capacity() == 10U);
        REQUIRE(buffer2.capacity() == 5U);

        buffer2 = std::move(buffer1);

        REQUIRE(buffer2.capacity() == 10U);
        REQUIRE(buffer2.size() == 40U);
        REQUIRE_FALSE(buffer2.IsEmpty());

        // Original buffer should be empty after move
        REQUIRE(buffer1.IsEmpty());
        REQUIRE(buffer1.capacity() == 0U);
    }

    SECTION("Move assignment to self") {
        core::Buffer<uint32_t> buffer{10U, heap};
        auto* ptr = &buffer;

        buffer = std::move(*ptr);

        // Buffer should remain unchanged
        REQUIRE(buffer.capacity() == 10U);
        REQUIRE_FALSE(buffer.IsEmpty());
    }

    SECTION("Move assignment from empty buffer") {
        core::Buffer<uint32_t> buffer1{heap};
        core::Buffer<uint32_t> buffer2{10U, heap};

        REQUIRE(buffer1.IsEmpty());
        REQUIRE(buffer2.capacity() == 10U);

        buffer2 = std::move(buffer1);

        REQUIRE(buffer2.IsEmpty());
        REQUIRE(buffer1.IsEmpty());
    }
}

TEST_CASE("Buffer - Explicit Release") {
    alignas(8) uint8_t storage[1024];
    core::BitMapHeap<32U, 32U> heap(storage, sizeof(storage), nullptr);

    SECTION("Release deallocates memory") {
        core::Buffer<uint8_t> buffer{32U, heap};
        REQUIRE(buffer.capacity() == 32U);
        REQUIRE(heap.GetStatistics().used_blocks == 1U);

        buffer.Release();

        REQUIRE(buffer.IsEmpty());
        REQUIRE(buffer.capacity() == 0U);
        REQUIRE(buffer.size() == 0U);
        REQUIRE(heap.GetStatistics().used_blocks == 0U);
    }

    SECTION("Release on empty buffer is safe") {
        core::Buffer<uint8_t> buffer{heap};
        REQUIRE(buffer.IsEmpty());

        buffer.Release();    // Should not crash

        REQUIRE(buffer.IsEmpty());
    }

    SECTION("Multiple Release calls are safe") {
        core::Buffer<uint8_t> buffer{32U, heap};
        buffer.Release();
        REQUIRE(buffer.IsEmpty());

        buffer.Release();    // Should not crash

        REQUIRE(buffer.IsEmpty());
    }
}

TEST_CASE("Buffer - as_span Non-const") {
    alignas(8) uint8_t storage[1024];
    core::BitMapHeap<32U, 32U> heap(storage, sizeof(storage), nullptr);

    SECTION("as_span returns valid span") {
        core::Buffer<uint32_t> buffer{10U, heap};
        auto span = buffer.as_span();

        REQUIRE(span.count() == 10U);
        REQUIRE(span.data() != nullptr);
    }

    SECTION("as_span on empty buffer") {
        core::Buffer<uint32_t> buffer{heap};
        auto span = buffer.as_span();

        REQUIRE(span.count() == 0U);
    }

    SECTION("Modify buffer through span") {
        core::Buffer<uint32_t> buffer{5U, heap};
        auto span = buffer.as_span();

        for (size_t i = 0; i < span.count(); ++i) {
            span[i] = static_cast<uint32_t>(i * 100);
        }

        // Verify through another span
        auto span2 = buffer.as_span();
        for (size_t i = 0; i < span2.count(); ++i) {
            REQUIRE(span2[i] == static_cast<uint32_t>(i * 100));
        }
    }
}

TEST_CASE("Buffer - as_span Const") {
    alignas(8) uint8_t storage[1024];
    core::BitMapHeap<32U, 32U> heap(storage, sizeof(storage), nullptr);

    SECTION("const as_span returns const span") {
        core::Buffer<uint32_t> buffer{10U, heap};
        const auto& const_buffer = buffer;
        auto span = const_buffer.as_span();

        REQUIRE(span.count() == 10U);
        REQUIRE(span.data() != nullptr);

        // Verify type is const
        static_assert(std::is_const_v<std::remove_reference_t<decltype(span[0])>>, "Span should return const references");
    }
}

TEST_CASE("Buffer - Type Casting with as_span") {
    alignas(8) uint8_t storage[1024];
    core::BitMapHeap<32U, 32U> heap(storage, sizeof(storage), nullptr);

    SECTION("Cast uint32_t to uint8_t") {
        core::Buffer<uint32_t> buffer{10U, heap};    // 10 * 4 = 40 bytes
        auto span_u8 = buffer.as_span<uint8_t>();

        REQUIRE(span_u8.count() == 40U);    // 40 bytes
        REQUIRE(span_u8.data() != nullptr);
    }

    SECTION("Cast uint32_t to uint16_t") {
        core::Buffer<uint32_t> buffer{10U, heap};    // 10 * 4 = 40 bytes
        auto span_u16 = buffer.as_span<uint16_t>();

        REQUIRE(span_u16.count() == 20U);    // 40 / 2 = 20 uint16_t
        REQUIRE(span_u16.data() != nullptr);
    }

    SECTION("Cast const buffer") {
        core::Buffer<uint32_t> buffer{10U, heap};
        const auto& const_buffer = buffer;
        auto span_u8 = const_buffer.as_span<uint8_t>();

        REQUIRE(span_u8.count() == 40U);
        static_assert(std::is_const_v<std::remove_reference_t<decltype(span_u8[0])>>, "Cast span should return const references");
    }
}

TEST_CASE("Buffer - Different Element Types") {
    alignas(8) uint8_t storage[1024];
    core::BitMapHeap<32U, 32U> heap(storage, sizeof(storage), nullptr);

    SECTION("uint8_t buffer") {
        core::Buffer<uint8_t> buffer{100U, heap};
        REQUIRE(buffer.capacity() == 100U);
        REQUIRE(buffer.size() == 100U);
        REQUIRE_FALSE(buffer.IsEmpty());
    }

    SECTION("uint16_t buffer") {
        core::Buffer<uint16_t> buffer{50U, heap};
        REQUIRE(buffer.capacity() == 50U);
        REQUIRE(buffer.size() == 100U);    // 50 * 2
        REQUIRE_FALSE(buffer.IsEmpty());
    }

    SECTION("uint32_t buffer") {
        core::Buffer<uint32_t> buffer{25U, heap};
        REQUIRE(buffer.capacity() == 25U);
        REQUIRE(buffer.size() == 100U);    // 25 * 4
        REQUIRE_FALSE(buffer.IsEmpty());
    }

    SECTION("uint64_t buffer") {
        core::Buffer<uint64_t> buffer{12U, heap};
        REQUIRE(buffer.capacity() == 12U);
        REQUIRE(buffer.size() == 96U);    // 12 * 8
        REQUIRE_FALSE(buffer.IsEmpty());
    }

    SECTION("Custom struct") {
        struct TestStruct {
            uint32_t a;
            uint32_t b;
            uint64_t c;
        };
        static_assert(sizeof(TestStruct) == 16U, "TestStruct should be 16 bytes");

        core::Buffer<TestStruct> buffer{5U, heap};
        REQUIRE(buffer.capacity() == 5U);
        REQUIRE(buffer.size() == 80U);    // 5 * 16
        REQUIRE_FALSE(buffer.IsEmpty());
    }
}

TEST_CASE("Buffer - Multiple Buffers with Same Heap") {
    alignas(8) uint8_t storage[2048];
    core::BitMapHeap<64U, 32U> heap(storage, sizeof(storage), nullptr);

    SECTION("Multiple buffers don't interfere") {
        core::Buffer<uint8_t> buffer1{32U, heap};
        core::Buffer<uint16_t> buffer2{16U, heap};
        core::Buffer<uint32_t> buffer3{8U, heap};

        REQUIRE(buffer1.capacity() == 32U);
        REQUIRE(buffer2.capacity() == 16U);
        REQUIRE(buffer3.capacity() == 8U);

        REQUIRE(heap.GetStatistics().used_blocks == 3U);

        // Release middle buffer
        buffer2.Release();
        REQUIRE(buffer2.IsEmpty());
        REQUIRE(heap.GetStatistics().used_blocks == 2U);

        // Other buffers should be unaffected
        REQUIRE(buffer1.capacity() == 32U);
        REQUIRE(buffer3.capacity() == 8U);
    }
}

TEST_CASE("Buffer - RAII Behavior") {
    alignas(8) uint8_t storage[1024];
    core::BitMapHeap<32U, 32U> heap(storage, sizeof(storage), nullptr);

    SECTION("Buffer automatically releases on scope exit") {
        REQUIRE(heap.GetStatistics().used_blocks == 0U);

        {
            core::Buffer<uint8_t> buffer{32U, heap};
            REQUIRE(heap.GetStatistics().used_blocks == 1U);
        }    // buffer goes out of scope

        REQUIRE(heap.GetStatistics().used_blocks == 0U);
    }

    SECTION("Multiple buffers in nested scopes") {
        REQUIRE(heap.GetStatistics().used_blocks == 0U);

        core::Buffer<uint8_t> buffer1{16U, heap};
        REQUIRE(heap.GetStatistics().used_blocks == 1U);

        {
            core::Buffer<uint8_t> buffer2{16U, heap};
            REQUIRE(heap.GetStatistics().used_blocks == 2U);

            {
                core::Buffer<uint8_t> buffer3{16U, heap};
                REQUIRE(heap.GetStatistics().used_blocks == 3U);
            }

            REQUIRE(heap.GetStatistics().used_blocks == 2U);
        }

        REQUIRE(heap.GetStatistics().used_blocks == 1U);
    }
}

TEST_CASE("Buffer - Edge Cases") {
    alignas(8) uint8_t storage[1024];
    core::BitMapHeap<32U, 32U> heap(storage, sizeof(storage), nullptr);

    SECTION("IsEmpty consistency") {
        core::Buffer<uint8_t> buffer1{heap};
        REQUIRE(buffer1.IsEmpty() == true);
        REQUIRE((buffer1.capacity() == 0U) == buffer1.IsEmpty());

        core::Buffer<uint8_t> buffer2{1U, heap};
        REQUIRE(buffer2.IsEmpty() == false);
        REQUIRE((buffer2.capacity() == 0U) == buffer2.IsEmpty());
    }

    SECTION("Size and capacity relationship") {
        core::Buffer<uint32_t> buffer{10U, heap};
        REQUIRE(buffer.size() == buffer.capacity() * sizeof(uint32_t));
    }

    SECTION("Move then release") {
        core::Buffer<uint8_t> buffer1{32U, heap};
        core::Buffer<uint8_t> buffer2{std::move(buffer1)};

        REQUIRE(buffer1.IsEmpty());
        buffer1.Release();    // Should be safe on already empty buffer
        REQUIRE(buffer1.IsEmpty());
    }
}

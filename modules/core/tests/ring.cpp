// #define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "core/Ring.hpp"

TEST_CASE("Ring - Push and Pop") {
    constexpr std::size_t Capacity = 5;
    core::Ring<int, Capacity> ring;

    REQUIRE(ring.Capacity() == Capacity);
    REQUIRE(ring.Count() == 0u);
    REQUIRE(ring.Size() == 0u);

    int value = 42;
    REQUIRE(ring.Push(value));
    REQUIRE(ring.Count() == 1u);
    REQUIRE(ring.Size() == sizeof(int));
    REQUIRE(ring.MaxContiguousElements() == 1U);

    int output = 0;
    REQUIRE(ring.Pop(output));
    REQUIRE(output == value);
    REQUIRE(ring.Count() == 0u);
    REQUIRE(ring.Size() == 0u);
    REQUIRE(ring.MaxContiguousElements() == 0U);
}

TEST_CASE("Ring - Push and Pop Multiple") {
    constexpr std::size_t Capacity = 3;
    core::Ring<int, Capacity> ring;

    REQUIRE(ring.IsEmpty());
    REQUIRE(ring.Push(1));
    REQUIRE(ring.Push(2));
    REQUIRE(ring.Push(3));
    REQUIRE_FALSE(ring.Push(4));    // Buffer is full
    REQUIRE(ring.IsFull());
    REQUIRE(ring.MaxContiguousElements() == 3U);

    int output = 0;
    REQUIRE(ring.Pop(output));
    REQUIRE(output == 1);
    REQUIRE(ring.MaxContiguousElements() == 2U);
    REQUIRE(ring.Pop(output));
    REQUIRE(output == 2);
    REQUIRE(ring.MaxContiguousElements() == 1U);
    REQUIRE(ring.Pop(output));
    REQUIRE(output == 3);
    REQUIRE(ring.MaxContiguousElements() == 0U);
    REQUIRE_FALSE(ring.Pop(output));    // Buffer is empty
}

TEST_CASE("Ring - Wrap Around") {
    constexpr std::size_t Capacity = 4;
    core::Ring<int, Capacity> ring;

    REQUIRE(ring.Push(1));
    REQUIRE(ring.Push(2));
    REQUIRE(ring.Push(3));
    REQUIRE(ring.Push(4));
    REQUIRE(ring.MaxContiguousElements() == 4U);

    int output = 0;
    REQUIRE(ring.Pop(output));
    REQUIRE(output == 1);
    REQUIRE(ring.MaxContiguousElements() == 3U);

    REQUIRE(ring.Push(5));
    REQUIRE(ring.MaxContiguousElements() == 3U);

    REQUIRE(ring.Pop(output));
    REQUIRE(output == 2);
    REQUIRE(ring.MaxContiguousElements() == 2U);
    REQUIRE(ring.Pop(output));
    REQUIRE(output == 3);
    REQUIRE(ring.MaxContiguousElements() == 1U);
    REQUIRE(ring.Pop(output));
    REQUIRE(output == 4);
    REQUIRE(ring.MaxContiguousElements() == 1U);
    REQUIRE(ring.Pop(output));
    REQUIRE(output == 5);
    REQUIRE_FALSE(ring.Pop(output));    // Buffer is empty
    REQUIRE(ring.MaxContiguousElements() == 0U);
}

TEST_CASE("Ring - Drops") {
    constexpr std::size_t Capacity = 5;
    core::Ring<int, Capacity> ring;

    REQUIRE(ring.Push(1));
    REQUIRE(ring.Push(2));
    REQUIRE(ring.Push(3));
    REQUIRE(ring.Push(4));
    REQUIRE(ring.Push(5));
    REQUIRE(ring.IsFull());
    REQUIRE(ring.MaxContiguousElements() == 5U);

    REQUIRE(ring.Drop(2));    // Drop first two elements
    REQUIRE(ring.Count() == 3U);
    REQUIRE(ring.MaxContiguousElements() == 3U);

    REQUIRE(ring.Drop(3));
    REQUIRE(ring.IsEmpty());
    REQUIRE(ring.MaxContiguousElements() == 0U);
}

TEST_CASE("Ring - Relative Indexing") {
    constexpr std::size_t Capacity = 5;
    core::Ring<int, Capacity> ring;

    REQUIRE(ring.Push(1));
    REQUIRE(ring.Push(2));
    REQUIRE(ring.Push(3));
    REQUIRE(ring.Push(4));
    REQUIRE(ring.Push(5));
    REQUIRE(ring[0] == 1U);
    REQUIRE(ring[1] == 2U);
    REQUIRE(ring[2] == 3U);
    REQUIRE(ring[3] == 4U);
    REQUIRE(ring[4] == 5U);

    REQUIRE(ring.Drop(2));    // Drop first two elements
    REQUIRE(ring.Count() == 3U);
    REQUIRE(ring.Push(6));
    REQUIRE(ring.Push(7));
    REQUIRE(ring.IsFull());
    REQUIRE(ring[0] == 3U);
    REQUIRE(ring[1] == 4U);
    REQUIRE(ring[2] == 5U);
    REQUIRE(ring[3] == 6U);
    REQUIRE(ring[4] == 7U);

    REQUIRE(ring.Drop(3));
    REQUIRE(ring[0] == 6U);
    REQUIRE(ring[1] == 7U);
    REQUIRE(ring[2] == 6U);
    REQUIRE(ring[3] == 7U);
    REQUIRE(ring[4] == 6U);
    REQUIRE(ring[5] == 7U);
    REQUIRE(ring.Count() == 2U);
    REQUIRE(ring.MaxContiguousElements() == 2U);
}

TEST_CASE("Ring - Span Push") {
    constexpr std::size_t Capacity = 5;
    core::Ring<int, Capacity> ring;
    int buffer[5] = {10, 20, 30, 40, 50};

    core::Span<int const> span{buffer};
    REQUIRE(ring.Push(span));
    REQUIRE(ring.Count() == 5U);
    REQUIRE(ring.MaxContiguousElements() == 5U);

    REQUIRE(ring[0] == 10U);
    REQUIRE(ring[1] == 20U);
    REQUIRE(ring[2] == 30U);
    REQUIRE(ring[3] == 40U);
    REQUIRE(ring[4] == 50U);
    REQUIRE(ring[5] == 10U);    // wraps

    int output = 0;
    REQUIRE(ring.Pop(output));
    REQUIRE(output == 10);
    REQUIRE(ring.MaxContiguousElements() == 4U);
}

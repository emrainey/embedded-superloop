// #define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "core/Ring.hpp"

TEST_CASE("Ring - Push and Pop") {
    constexpr std::size_t Capacity = 5;
    core::Ring<int, Capacity> ring;

    REQUIRE(ring.Capacity() == Capacity);
    REQUIRE(ring.Count() == 0u);
    REQUIRE(ring.sSize() == 0u);

    int value = 42;
    REQUIRE(ring.Push(value));
    REQUIRE(ring.Count() == 1u);
    REQUIRE(ring.sSize() == sizeof(int));

    int output = 0;
    REQUIRE(ring.Pop(output));
    REQUIRE(output == value);
    REQUIRE(ring.Count() == 0u);
    REQUIRE(ring.sSize() == 0u);
}

TEST_CASE("Ring - Push and Pop Multiple") {
    constexpr std::size_t Capacity = 3;
    core::Ring<int, Capacity> ring;

    REQUIRE(ring.Push(1));
    REQUIRE(ring.Push(2));
    REQUIRE(ring.Push(3));
    REQUIRE_FALSE(ring.Push(4));    // Buffer is full

    int output = 0;
    REQUIRE(ring.Pop(output));
    REQUIRE(output == 1);
    REQUIRE(ring.Pop(output));
    REQUIRE(output == 2);
    REQUIRE(ring.Pop(output));
    REQUIRE(output == 3);
    REQUIRE_FALSE(ring.Pop(output));    // Buffer is empty
}

TEST_CASE("Ring - Wrap Around") {
    constexpr std::size_t Capacity = 4;
    core::Ring<int, Capacity> ring;

    REQUIRE(ring.Push(1));
    REQUIRE(ring.Push(2));
    REQUIRE(ring.Push(3));
    REQUIRE(ring.Push(4));

    int output = 0;
    REQUIRE(ring.Pop(output));
    REQUIRE(output == 1);

    REQUIRE(ring.Push(5));

    REQUIRE(ring.Pop(output));
    REQUIRE(output == 2);
    REQUIRE(ring.Pop(output));
    REQUIRE(output == 3);
    REQUIRE(ring.Pop(output));
    REQUIRE(output == 4);
    REQUIRE(ring.Pop(output));
    REQUIRE(output == 5);
    REQUIRE_FALSE(ring.Pop(output));    // Buffer is empty
}

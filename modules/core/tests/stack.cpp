// #define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "core/Stack.hpp"

TEST_CASE("Stack - Push and Pop") {
    constexpr std::size_t Capacity = 5;
    core::Stack<int, Capacity> stack;

    REQUIRE(stack.capacity() == Capacity);
    REQUIRE(stack.count() == 0);
    REQUIRE(stack.size() == 0);

    SECTION("Push a value") {
        int value = 42;
        REQUIRE(stack.Push(value));
        REQUIRE(stack.count() == 1);
        REQUIRE(stack.size() == sizeof(int));
        REQUIRE(stack[0] == value);
    }

    SECTION("Pop a value") {
        int value = 42;
        stack.Push(value);
        int output = 0;
        REQUIRE(stack.Pop(output));
        REQUIRE(output == value);
        REQUIRE(stack.count() == 0);
        REQUIRE(stack.size() == 0);
    }
}

TEST_CASE("Stack - Push and Pop Multiple") {
    constexpr std::size_t Capacity = 3;
    core::Stack<int, Capacity> stack;

    REQUIRE(stack.Push(1));
    REQUIRE(stack.Push(2));
    REQUIRE(stack.Push(3));
    REQUIRE_FALSE(stack.Push(4));    // Stack is full

    int output = 0;
    REQUIRE(stack.Pop(output));
    REQUIRE(output == 3);
    REQUIRE(stack.Pop(output));
    REQUIRE(output == 2);
    REQUIRE(stack.Pop(output));
    REQUIRE(output == 1);
    REQUIRE_FALSE(stack.Pop(output));    // Stack is empty
}

TEST_CASE("Stack - Emplace and Dismiss") {
    struct Data {
        int value{0};
        Data() : value{0} {}
        Data(int value) : value(value) {}
    };

    constexpr std::size_t Capacity = 3;
    core::Stack<Data, Capacity> stack;

    REQUIRE(stack.emplace(1));
    REQUIRE(stack.emplace(2));
    REQUIRE(stack.emplace(3));
    REQUIRE_FALSE(stack.emplace(4));    // Stack is full

    REQUIRE(stack.count() == 3);
    REQUIRE(stack.size() == 3 * sizeof(Data));

    REQUIRE(stack[0].value == 3);
    REQUIRE(stack[1].value == 2);
    REQUIRE(stack[2].value == 1);

    REQUIRE(stack.dismiss());
    REQUIRE(stack.dismiss());
    REQUIRE(stack.dismiss());
    REQUIRE_FALSE(stack.dismiss());    // Stack is empty
}

TEST_CASE("Stack - Iterators") {
    constexpr std::size_t Capacity = 3;
    core::Stack<int, Capacity> stack;

    REQUIRE(stack.Push(1));
    REQUIRE(stack.Push(2));
    REQUIRE(stack.Push(3));

    SECTION("Mutable Iterator") {
        int expectedValue = 3;
        for (auto it = stack.begin(); it != stack.end(); ++it) {
            REQUIRE(*it == expectedValue);
            --expectedValue;
        }
    }

    SECTION("Const Iterator") {
        int expectedValue = 3;
        for (auto it = stack.begin(); it != stack.end(); ++it) {
            REQUIRE(*it == expectedValue);
            --expectedValue;
        }
    }
}

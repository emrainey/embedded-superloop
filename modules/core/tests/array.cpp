// #define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "core/Array.hpp"

TEST_CASE("Array - Accessing Elements") {
    constexpr std::size_t Count = 5;
    core::Array<int, Count> arr;

    REQUIRE(arr.count() == Count);
    REQUIRE(arr.size() == Count * sizeof(int));

    SECTION("Accessing elements") {
        arr[0] = 10;
        arr[1] = 20;
        arr[2] = 30;
        arr[3] = 40;
        arr[4] = 50;

        REQUIRE(arr[0] == 10);
        REQUIRE(arr[1] == 20);
        REQUIRE(arr[2] == 30);
        REQUIRE(arr[3] == 40);
        REQUIRE(arr[4] == 50);
    }

    SECTION("Accessing elements beyond Count") {
        arr[0] = 10;
        arr[1] = 20;
        arr[2] = 30;
        arr[3] = 40;
        arr[4] = 50;

        REQUIRE(arr[5] == 10);
        REQUIRE(arr[6] == 20);
        REQUIRE(arr[7] == 30);
        REQUIRE(arr[8] == 40);
        REQUIRE(arr[9] == 50);

        const core::Array<int, Count>& constArr{arr};
        REQUIRE(constArr[5] == 10);
        REQUIRE(constArr[6] == 20);
        REQUIRE(constArr[7] == 30);
        REQUIRE(constArr[8] == 40);
        REQUIRE(constArr[9] == 50);
    }
}

TEST_CASE("Array - Iterators") {
    constexpr std::size_t Count = 3;
    core::Array<int, Count> arr;

    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;

    SECTION("Mutable Iterator") {
        int expectedValue = 1;
        for (auto it = arr.begin(); it != arr.end(); ++it) {
            REQUIRE(*it == expectedValue);
            ++expectedValue;
        }
    }

    SECTION("Const Iterator") {
        const core::Array<int, Count> constArr{arr};
        int expectedValue = 1;
        for (auto it = constArr.begin(); it != constArr.end(); ++it) {
            REQUIRE(*it == expectedValue);
            ++expectedValue;
        }
    }
}

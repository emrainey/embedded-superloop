// #define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "core/Span.hpp"    // Include the header file containing the Span class

TEST_CASE("Span - Accessing elements", "[span]") {
    int arr[] = {1, 2, 3, 4, 5};
    core::Span<int> spanArray{arr, 5};

    SECTION("Accessing elements using operator[]") {
        REQUIRE(spanArray[0] == 1);
        REQUIRE(spanArray[2] == 3);
        REQUIRE(spanArray[4] == 5);
    }

    SECTION("Accessing elements using iterators") {
        int sum = 0;
        for (auto it = spanArray.begin(); it != spanArray.end(); ++it) {
            sum += *it;
        }
        REQUIRE(sum == 15);
    }
}

TEST_CASE("Span - Subspan feature", "[span]") {
    int arr[] = {1, 2, 3, 4, 5};
    core::Span<int> spanArray{arr, 5};

    SECTION("Subspan with valid offset and count") {
        auto subspan = spanArray(1, 3);
        REQUIRE(subspan.count() == 3);
        REQUIRE(subspan[0] == 2);
        REQUIRE(subspan[1] == 3);
        REQUIRE(subspan[2] == 4);
    }

    SECTION("Subspan with invalid offset and count") {
        auto subspan = spanArray(3, 2);    // at 3 for 2 elements
        REQUIRE(subspan.count() == 2);     // Only 2 elements are valid
        REQUIRE(subspan[0] == 4);
        REQUIRE(subspan[1] == 5);
    }

    SECTION("Subspan with offset equal to the Span count") {
        auto subspan = spanArray(5, 2);    // Offset is equal to the count
        REQUIRE(subspan.count() == 0);     // Subspan is empty
    }
}

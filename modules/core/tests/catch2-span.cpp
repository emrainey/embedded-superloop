// #define CATCH_CONFIG_MAIN
// #include <cstdio>
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

    SECTION("Resize Span") {
        spanArray.resize(3);
        REQUIRE(spanArray.count() == 3);
        REQUIRE(spanArray[0] == 1);
        REQUIRE(spanArray[1] == 2);
        REQUIRE(spanArray[2] == 3);
    }
}

TEST_CASE("Span - Constructors") {
    int arr[] = {1, 2, 3, 4, 5};
    core::Span<int> spanArray{arr, 5};

    SECTION("Default constructor") {
        core::Span<int> emptySpan;
        REQUIRE(emptySpan.count() == 0);
    }

    SECTION("Constructor with pointer and size") {
        core::Span<int> spanFromPointer(arr, 5);
        REQUIRE(spanFromPointer.count() == 5);
        REQUIRE(spanFromPointer[0] == 1);
    }

    SECTION("Copy Constructor") {
        core::Span<int> copiedSpan(spanArray);
        REQUIRE(copiedSpan.count() == 5);
        REQUIRE(copiedSpan[0] == 1);
    }

    SECTION("Copy Assignment") {
        core::Span<int> copiedSpan;
        copiedSpan = spanArray;
        REQUIRE(copiedSpan.count() == 5);
        REQUIRE(copiedSpan[0] == 1);
    }

    SECTION("Move Constructor") {
        core::Span<int> spanArray2{arr, 5};
        core::Span<int> movedSpan(std::move(spanArray2));
        REQUIRE(movedSpan.count() == 5);
        REQUIRE(movedSpan[0] == 1);
        REQUIRE(spanArray2.count() == 0);    // Original span should be empty after move
    }

    SECTION("Move Assignment") {
        core::Span<int> spanArray2{arr, 5};
        core::Span<int> movedSpan;
        movedSpan = std::move(spanArray2);
        REQUIRE(movedSpan.count() == 5);
        REQUIRE(movedSpan[0] == 1);
        REQUIRE(spanArray2.count() == 0);    // Original span should be empty after move
    }
}

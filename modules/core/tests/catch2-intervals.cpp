// #define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "core/Intervals.hpp"

#include <iostream>

TEST_CASE("Intervals") {
    core::Array<core::Interval, 5> intervals{{
        {0, 10},
        {20, 30},
        {40, 50},
        {60, 70},
        {80, 90},
    }};
    REQUIRE(core::IsSortedAndNonOverlapping(intervals));
    SECTION("Find") {
        REQUIRE(core::FindIndex(intervals, 5) == 0);
        REQUIRE(core::FindIndex(intervals, 15) == std::numeric_limits<std::size_t>::max());
        REQUIRE(core::FindIndex(intervals, 25) == 1);
        REQUIRE(core::FindIndex(intervals, 45) == 2);
        REQUIRE(core::FindIndex(intervals, 65) == 3);
        REQUIRE(core::FindIndex(intervals, 85) == 4);
        REQUIRE(core::FindIndex(intervals, 95) == std::numeric_limits<std::size_t>::max());
    }
    SECTION("Contains") {
        REQUIRE(core::Contains(intervals, 5));
        REQUIRE(core::Contains(intervals, 25));
        REQUIRE(core::Contains(intervals, 45));
        REQUIRE(core::Contains(intervals, 65));
        REQUIRE(core::Contains(intervals, 85));
        REQUIRE_FALSE(core::Contains(intervals, 95));
    }
    SECTION("Overlap Check") {
        REQUIRE(core::IsSortedAndNonOverlapping(intervals));
    }
    SECTION("Contains Address") {
        REQUIRE(not core::Interval{5, 7}.contains(4));
        REQUIRE(core::Interval{5, 7}.contains(5));
        REQUIRE(core::Interval{5, 7}.contains(6));
        REQUIRE(core::Interval{5, 7}.contains(7));
        REQUIRE(not core::Interval{5, 7}.contains(8));
    }
    SECTION("Contains Interval") {
        REQUIRE(not core::Interval{5, 7}.contains(core::Interval{4, 6}));
        REQUIRE(core::Interval{5, 7}.contains(core::Interval{5, 7}));
        REQUIRE(core::Interval{5, 7}.contains(core::Interval{5, 6}));
        REQUIRE(core::Interval{5, 7}.contains(core::Interval{6, 7}));
        REQUIRE(not core::Interval{5, 7}.contains(core::Interval{4, 8}));
        REQUIRE(core::Interval{5, 7}.subsumes(core::Interval{4, 8}));
        REQUIRE(core::Interval{4, 8}.contains(core::Interval{5, 7}));
        REQUIRE(not core::Interval{4, 8}.subsumes(core::Interval{5, 7}));
    }
    SECTION("Overlaps") {
        REQUIRE(not core::Interval{5, 7}.overlaps(core::Interval{2, 4}));
        REQUIRE(core::Interval{5, 7}.overlaps(core::Interval{3, 5}));
        REQUIRE(core::Interval{5, 7}.overlaps(core::Interval{4, 6}));
        REQUIRE(core::Interval{5, 7}.overlaps(core::Interval{5, 7}));
        REQUIRE(core::Interval{5, 7}.overlaps(core::Interval{6, 8}));
        REQUIRE(core::Interval{5, 7}.overlaps(core::Interval{7, 9}));
        REQUIRE(not core::Interval{5, 7}.overlaps(core::Interval{8, 10}));
        REQUIRE(core::Interval{5, 7}.overlaps(core::Interval{4, 6}));
        REQUIRE_FALSE(core::Interval{5, 7}.overlaps(core::Interval{8, 9}));
    }
    SECTION("Are Overlapping") {
        core::Array<core::Interval, 2> bad_intervals{{{0, 10}, {5, 15}}};
        REQUIRE_FALSE(core::IsSortedAndNonOverlapping(bad_intervals));
    }
    SECTION("Runtime Sorting") {
        core::Array<core::Interval, 5> unsorted_intervals{{{20, 30}, {0, 10}, {40, 50}, {80, 90}, {60, 70}}};
        std::cout << "Unsorted: " << unsorted_intervals << std::endl;
        REQUIRE_FALSE(core::IsSortedAndNonOverlapping(unsorted_intervals));
        core::Array<core::Interval, 5> sorted_intervals = core::Sort(unsorted_intervals);
        std::cout << "Sorted: " << sorted_intervals << std::endl;
        REQUIRE(core::IsSortedAndNonOverlapping(sorted_intervals));
    }
    SECTION("Constexpr Sorting") {
        constexpr core::Array<core::Interval, 5> const unsorted_intervals{{{20, 30}, {0, 10}, {40, 50}, {80, 90}, {60, 70}}};
        std::cout << "Unsorted: " << unsorted_intervals << std::endl;
        REQUIRE_FALSE(core::IsSortedAndNonOverlapping(unsorted_intervals));
        constexpr core::Array<core::Interval, 5> const sorted_intervals{core::Sort(unsorted_intervals)};
        std::cout << "Sorted: " << sorted_intervals << std::endl;
        static_assert(sorted_intervals[0].start == 0U, "Must be this value exactly");
        static_assert(sorted_intervals[4].start == 80U, "Must be this value exactly");
        REQUIRE(core::IsSortedAndNonOverlapping(sorted_intervals));
    }
}

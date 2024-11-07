#ifndef CORE_INTERVALS_HPP
#define CORE_INTERVALS_HPP

#include <cstdint>
#include <cstddef>
#include <limits>
#include <type_traits>
#if defined(UNITTEST)
#include <cassert>
#include <iostream>
#endif

#include <polyfill.hpp>
#include <core/Array.hpp>

namespace core {

/// @brief Interval structure which contains a start and limit address for a memory region.
/// When placed into a plain array, the array can be used to check if an address is within a valid range.
struct Interval {
    std::uintptr_t start;    ///< Inclusive Start Address
    std::uintptr_t limit;    ///< Inclusive End Address

    constexpr Interval()
        : start{0U}
        , limit{0U} {}

    constexpr Interval(std::uintptr_t _start, std::uintptr_t _limit)
        : start{_start}
        , limit{_limit} {
#if defined(UNITTEST)
        assert(start <= limit);
#endif
    }

    constexpr Interval(Interval const& other) {
        start = other.start;
        limit = other.limit;
    }

    constexpr Interval& operator=(Interval const& other) {
        start = other.start;
        limit = other.limit;
        return *this;
    }

    constexpr bool contains(std::uintptr_t address) const { return (start <= address) and (address <= limit); }

    constexpr bool contains(Interval const& other) const { return (start <= other.start) and (limit >= other.limit); }

    /// When an interval is a subset of another interval.
    constexpr bool subsumes(Interval const& other) const { return other.contains(*this); }

    constexpr bool operator==(Interval const& other) const { return (start == other.start) and (limit == other.limit); }

    constexpr bool operator!=(Interval const& other) const { return not operator==(other); }

    constexpr bool operator<(Interval const& other) const { return (limit < other.start); }

    constexpr bool operator>(Interval const& other) const { return (start > other.limit); }

    // <= and >= are nonsensical for intervals

    constexpr bool overlaps(Interval const& other) const {
        if (other.start < start and start <= other.limit and other.limit < limit) {
            return true;
        }
        if (start < other.start and other.start <= limit and limit < other.limit) {
            return true;
        }
        if (contains(other)) {
            return true;
        }
        return false;
    }

#if defined(UNITTEST)
    friend std::ostream& operator<<(std::ostream& os, Interval const& interval) {
        os << "Interval: [" << interval.start << ", " << interval.limit << "]";
        return os;
    }
#endif
};

/// Finds the index of the interval that contains the given address.
/// @tparam N The number of elemens in the intervals array.
/// @param intervals The pre-sorted array of intervals to search.
/// @param address The address to search for.
/// @return The index of the interval that contains the address, or std::numeric_limits<std::size_t>::max() if not found.
template <std::size_t N>
constexpr std::size_t FindIndex(core::Array<Interval, N> const& intervals, std::uintptr_t address) {
    std::size_t beg = 0;
    std::size_t end = N;    // exclusive index
    std::size_t mid;
    do {
        mid = ((end - beg) / 2) + beg;
#if defined(UNITTEST)
        std::cout << "beg: " << beg << " end: " << end << " mid: " << mid << std::endl;
#endif
        if (intervals[mid].contains(address)) {
            return mid;
        } else if (address < intervals[mid].start) {
            // move to the left
            end = mid;
        } else if (address > intervals[mid].limit) {
            // move to the right (but don't include mid)
            beg = mid + 1;
        }
    } while (beg < end);
    return std::numeric_limits<std::size_t>::max();
}

/// @brief Checks if the given address is within any of the intervals.
/// @tparam N The number of elements in the intervals array.
/// @param intervals The pre-sorted array of intervals to search.
/// @param address The address to search for.
/// @return True if the address is within any of the intervals, false otherwise.
template <std::size_t N>
constexpr bool Contains(core::Array<Interval, N> const& intervals, std::uintptr_t address) {
    return FindIndex(intervals, address) != std::numeric_limits<std::size_t>::max();
}

/// Determines if a set of Intervals are sorted and non-overlapping.
/// @tparam N The number of elements in the intervals array.
/// @param intervals The array of intervals to check.
/// @return True if the intervals are sorted and non-overlapping, false otherwise.
template <std::size_t N>
constexpr bool IsSortedAndNonOverlapping(core::Array<Interval, N>& intervals) {
    for (std::size_t i = 1; i < N; ++i) {
        if (intervals[i - 1].limit >= intervals[i].start) {
            return false;
        }
    }
    return true;
}

/// Determines if a set of Intervals are sorted and non-overlapping.
/// @tparam N The number of elements in the intervals array.
/// @param intervals The array of intervals to check.
/// @return True if the intervals are sorted and non-overlapping, false otherwise.
template <std::size_t N>
constexpr bool IsSortedAndNonOverlapping(core::Array<Interval, N> const& intervals) {
    for (std::size_t i = 1; i < intervals.count(); ++i) {
        if (intervals[i - 1].limit >= intervals[i].start) {
            return false;
        }
    }
    return true;
}

/// Performs a SwapSort on the given subset of the array of intervals.
/// @tparam N The number of elements in the intervals array.
/// @param intervals The array of intervals to sort.
/// @param i The index of the first interval to swap.
/// @param j The index of the second interval to swap.
template <typename TYPE, std::size_t N>
constexpr void SwapSort(core::Array<TYPE, N>& data, std::size_t left, std::size_t right) {
    if (left < right) {
        std::size_t mid = left;
        for (std::size_t i = left + 1; i < right; ++i) {
            if (data[i] < data[left]) {
                mid++;
                polyfill::swap(data[mid], data[i]);
            }
        }
        polyfill::swap(data[left], data[mid]);
        SwapSort(data, left, mid);
        SwapSort(data, mid + 1, right);
    }
}

/// Sorts a given set of Intervals into ascending order and returns them as an Array
/// @tparam N The number of elements in the intervals array.
/// @param intervals The array of intervals to sort.
/// @return The sorted array of intervals.
template <typename TYPE, std::size_t N>
constexpr core::Array<TYPE, N> Sort(core::Array<TYPE, N> const& data) {
    auto sorted = data;    // copy
    SwapSort(sorted, 0, N);
    return sorted;
}

}    // namespace core

#endif    // CORE_INTERVALS_HPP
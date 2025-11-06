#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>
#if defined(UNITTEST)
#include <cassert>
#include <iostream>
#endif

#include <core/Intervals.hpp>

namespace core {

std::size_t FindIndex(Interval const intervals[], size_t count, std::uintptr_t address) {
#if defined(UNITTEST)
    std::cout << "intervals " << intervals << " count:" << count << std::endl;
    for (size_t i = 0; i < count; i++) {
        std::cout << intervals[i] << std::endl;
    }
#endif
    std::size_t beg = 0;
    std::size_t end = count;    // exclusive index
    std::size_t mid;
    do {
        mid = ((end - beg) / 2) + beg;
#if defined(UNITTEST)
        std::cout << "beg: " << beg << " end: " << end << " mid: " << mid << " " << intervals[mid] << std::endl;
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

bool Contains(Interval const intervals[], size_t count, std::uintptr_t address) {
#if defined(UNITTEST)
    std::cout << "intervals " << intervals << " count:" << count << std::endl;
    for (size_t i = 0; i < count; i++) {
        std::cout << intervals[i] << std::endl;
    }
#endif
    return FindIndex(intervals, count, address) != std::numeric_limits<std::size_t>::max();
}

bool IsSortedAndNonOverlapping(Interval const intervals[], size_t count) {
    for (std::size_t i = 1; i < count; ++i) {
        if (intervals[i - 1].limit >= intervals[i].start) {
            return false;
        }
    }
    return true;
}

}    // namespace core

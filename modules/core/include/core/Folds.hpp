#pragma once

#include <cstdint>
#include <cstddef>

namespace core {

/// Sums a variadic number of arguments together
/// @tparam ...NUMBERS
/// @param ...numbers
/// @return
template <typename... NUMBERS>
constexpr auto sum(NUMBERS... numbers) {
    return (numbers + ...);
}

template <typename... NUMBERS>
constexpr auto product(NUMBERS... numbers) {
    return (numbers * ...);
}

template <typename T>
constexpr bool is_strictly_decreasing(T) {
    return true;
}

template <typename T, typename U, typename... NUMBERS>
constexpr bool is_strictly_decreasing(T first, U second, NUMBERS... numbers) {
    return ((first > second) && is_strictly_decreasing(second, numbers...));
}

template <typename T>
constexpr bool is_strictly_increasing(T) {
    return true;
}

template <typename T, typename U, typename... NUMBERS>
constexpr bool is_strictly_increasing(T first, U second, NUMBERS... numbers) {
    return ((first < second) && is_strictly_increasing(second, numbers...));
}

template <typename... BOOLS>
constexpr bool all(BOOLS... bools) {
    return (... && bools);
}

template <typename... BOOLS>
constexpr bool any(BOOLS... bools) {
    return (... || bools);
}

template <typename T, typename U>
constexpr auto max(T v, U w) {
    return (v > w) ? v : w;
}

template <typename NUMBER, typename... NUMBERS>
constexpr auto max(NUMBER first, NUMBERS... numbers) {
    return max(max(first, numbers)...);
}

template <typename T, typename U>
constexpr auto min(T v, U w) {
    return (v < w) ? v : w;
}

template <typename NUMBER, typename... NUMBERS>
constexpr auto min(NUMBER first, NUMBERS... numbers) {
    return min(min(first, numbers)...);
}

}    // namespace core
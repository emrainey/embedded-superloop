#ifndef CORE_FOLDS_HPP_
#define CORE_FOLDS_HPP_

#include <cstdint>
#include <cstddef>

namespace core {

/// Sums a variadic number of arguments together
/// @tparam ...NUMBERS
/// @param ...numbers
/// @return The sum
template <typename... NUMBERS>
constexpr auto sum(NUMBERS... numbers) {
    return (numbers + ...);
}

/// Computes a product of a variadic number of arguments together
/// @tparam ...NUMBERS
/// @param ...numbers
/// @return The product
template <typename... NUMBERS>
constexpr auto product(NUMBERS... numbers) {
    return (numbers * ...);
}

/// Computes if the values of the type are strictly decreasing
/// @tparam T The type
/// @return True if the values are strictly decreasing
template <typename T>
constexpr bool is_strictly_decreasing(T) {
    return true;
}

/// Computes if the values of the type are strictly decreasing
/// @tparam T The type
/// @return True if the values are strictly decreasing
template <typename T, typename U, typename... NUMBERS>
constexpr bool is_strictly_decreasing(T first, U second, NUMBERS... numbers) {
    return ((first > second) && is_strictly_decreasing(second, numbers...));
}

/// Computes if the values of the type are strictly increasing
/// @tparam T The type
/// @return True if the values are strictly increasing
template <typename T>
constexpr bool is_strictly_increasing(T) {
    return true;
}

/// Computes if the values of the type are strictly increasing
/// @tparam T The type
/// @tparam U The type
/// @tparam ...NUMBERS The variadic number of arguments
/// @return True if the values are strictly increasing
template <typename T, typename U, typename... NUMBERS>
constexpr bool is_strictly_increasing(T first, U second, NUMBERS... numbers) {
    return ((first < second) && is_strictly_increasing(second, numbers...));
}

/// @tparam ...BOOLS The set of bools
/// @return True if all the bools are true
template <typename... BOOLS>
constexpr bool all(BOOLS... bools) {
    return (... && bools);
}

/// @brief  Computes if any of the bools are true
/// @tparam ...BOOLS
/// @param ...bools
/// @return True if any are true
template <typename... BOOLS>
constexpr bool any(BOOLS... bools) {
    return (... || bools);
}

/// @brief Computes the maximum of a set of two arguments
/// @tparam T The type
/// @tparam U The type
/// @param v The first value
/// @param w The second value
/// @return The maximum of the two values
template <typename T, typename U>
constexpr auto max(T v, U w) {
    return (v > w) ? v : w;
}

/// @brief Computes the maximum of a variadic number of arguments
/// @tparam NUMBER The first type
/// @tparam ...NUMBERS The rest of the types
/// @param first The first value
/// @param ...numbers The rest of the values
/// @return The maximum of the set of values
template <typename NUMBER, typename... NUMBERS>
constexpr auto max(NUMBER first, NUMBERS... numbers) {
    return max(max(first, numbers)...);
}

/// @brief Computes the minimum of a set of two arguments
/// @tparam T The type
/// @tparam U The type
/// @param v The first value
/// @param w The second value
/// @return The minimum of the two values
template <typename T, typename U>
constexpr auto min(T v, U w) {
    return (v < w) ? v : w;
}

/// @brief Computes the minimum of a variadic number of arguments
/// @tparam NUMBER The first type
/// @tparam ...NUMBERS The rest of the types
/// @param first The first value
/// @param ...numbers The rest of the values
/// @return The minimum of the set of values
template <typename NUMBER, typename... NUMBERS>
constexpr auto min(NUMBER first, NUMBERS... numbers) {
    return min(min(first, numbers)...);
}

}    // namespace core

#endif    // CORE_FOLDS_HPP_
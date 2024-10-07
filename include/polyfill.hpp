#ifndef POLYFILL_HPP_
#define POLYFILL_HPP_

/// @file
/// The C++ PolyFill for features which are not available in the current version of C++

#include <cstdint>
#include <cstddef>
#include <type_traits>

/// Return the number of elements in a C style array
template <typename TYPE, std::size_t N>
constexpr std::size_t dimof(TYPE const (&)[N]) {
    return N;
}

/// Casts an enumeration class value to it's underlying type and returns the value as that type.
/// @tparam ENUM_TYPE The enumeration class type.
template <typename ENUM_TYPE>
constexpr typename std::underlying_type<ENUM_TYPE>::type to_underlying(ENUM_TYPE e) {
    static_assert(std::is_enum<ENUM_TYPE>::value, "Must be an enumeration class");
    return static_cast<typename std::underlying_type<ENUM_TYPE>::type>(e);
}

/// Ensures that the value is a power of two
/// @tparam TYPE
/// @return True if the value is a power of two, false otherwise.
template <typename TYPE>
constexpr bool is_power_of_two(TYPE value) {
    static_assert(std::is_integral<TYPE>::value, "Must be an integral type");
    return ((value != 0U) and ((value & (value - 1U)) == 0U));
}
static_assert(is_power_of_two(1U << 9U), "Must be a power of two");
static_assert(not is_power_of_two(42U), "Must NOT be a power of two");

namespace polyfill {

/// Recursively computes a log2 input value.
/// @param n The value to compute the log2 of
/// @return Returns the log2 value of the input
template <typename TYPE>
constexpr std::uint8_t log2(TYPE value) {
    static_assert(std::is_integral<TYPE>::value, "Must be an integral type");
    return ((value < 2U) ? 0U : 1U + log2(value / 2U));
}
static_assert(log2(1U << 1U) == 1U, "Must be this value exactly");
static_assert(log2(1U << 3U) == 3U, "Must be this value exactly");

}    // namespace polyfill

#endif    // POLYFILL_HPP_
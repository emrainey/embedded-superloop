#ifndef ISO_HPP_
#define ISO_HPP_

/// @file
/// The ISO Prefixes for base 10 and base 2 powers

#include <cstdint>
#include <cstddef>
#include "debug.hpp"

/// Casts an enumeration class value and returns it.
/// @tparam ENUM_TYPE The enumeration class type.
template <typename ENUM_TYPE>
constexpr typename std::underlying_type<ENUM_TYPE>::type to_underlying(ENUM_TYPE e) {
    static_assert(std::is_enum<ENUM_TYPE>::value, "Must be an enumeration class");
    return static_cast<typename std::underlying_type<ENUM_TYPE>::type>(e);
}

namespace iso {

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

/// The prefixes for base 10 and base 2.
namespace prefix {
/// A value of 10^3
constexpr static std::uint32_t kilo = 1000U;
/// A value of 10^6
constexpr static std::uint32_t mega = kilo * kilo;
/// A value of 10^9
constexpr static std::uint32_t giga = kilo * mega;
/// A value of 2^10
constexpr static std::uint32_t kibi = 1024U;
static_assert(log2(kibi) == 10, "Must be this value exactly");
/// A value of 2^20
constexpr static std::uint32_t mebi = kibi * kibi;
static_assert(log2(mebi) == 20, "Must be this value exactly");
/// A value of 2^30
constexpr static std::uint32_t gibi = kibi * mebi;
static_assert(log2(gibi) == 30, "Must be this value exactly");
}    // namespace prefix

}    // namespace iso
#endif    // ISO_HPP_
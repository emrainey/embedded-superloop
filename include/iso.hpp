#ifndef ISO_HPP_
#define ISO_HPP_

/// @file
/// The ISO Prefixes for base 10 and base 2 powers

#include <cstdint>
#include <cstddef>
#include "polyfill.hpp"

/// the ISO (International Standards Organization) namespace
namespace iso {
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
static_assert(polyfill::log2(kibi) == 10, "Must be this value exactly");
/// A value of 2^20
constexpr static std::uint32_t mebi = kibi * kibi;
static_assert(polyfill::log2(mebi) == 20, "Must be this value exactly");
/// A value of 2^30
constexpr static std::uint32_t gibi = kibi * mebi;
static_assert(polyfill::log2(gibi) == 30, "Must be this value exactly");

}    // namespace prefix
}    // namespace iso

#endif    // ISO_HPP_
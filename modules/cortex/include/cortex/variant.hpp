#ifndef CORTEX_VARIANT_HPP_
#define CORTEX_VARIANT_HPP_

#include <cstdint>

/// @file
/// The Cortex Microcontroller Variant Header.
/// This file defines the various Cortex Microcontroller variants and their features.

namespace cortex {
/// The Cortex Microcontroller Variants
enum class Variants : std::uint8_t {
    Unknown = 0,
    M0,
    M0plus,
    M3,
    M4,
    M7,
    M33,
    M35P,
    M55,
    M85,
};
}    // namespace cortex

#if defined(CORTEX_M) and (CORTEX_M == 0)
namespace cortex {
/// The microcontroller variant detected at compile time.
constexpr static Variants microcontroller_variant = Variants::M0;
}    // namespace cortex
#elif defined(CORTEX_M) and (CORTEX_M == 0) and defined(CORTEX_M0PLUS)
namespace cortex {
/// The microcontroller variant detected at compile time.
constexpr static Variants microcontroller_variant = Variants::M0plus;
}    // namespace cortex
#elif defined(CORTEX_M) and (CORTEX_M == 3)
namespace cortex {
/// The microcontroller variant detected at compile time.
constexpr static Variants microcontroller_variant = Variants::M3;
}    // namespace cortex
#elif defined(CORTEX_M) and (CORTEX_M == 4)

#include "cortex/vendor/m4.hpp"

namespace cortex {
/// The microcontroller variant detected at compile time.
constexpr static Variants microcontroller_variant = Variants::M4;
}    // namespace cortex

#elif defined(CORTEX_M) and (CORTEX_M == 7)

#include "cortex/vendor/m7.hpp"

namespace cortex {
/// The microcontroller variant detected at compile time.
constexpr static Variants microcontroller_variant = Variants::M7;
}    // namespace cortex

#elif defined(CORTEX_M) and (CORTEX_M == 33)
namespace cortex {
/// The microcontroller variant detected at compile time.
constexpr static Variants microcontroller_variant = Variants::M33;
}    // namespace cortex
#elif defined(CORTEX_M) and (CORTEX_M == 35)
namespace cortex {
/// The microcontroller variant detected at compile time.
constexpr static Variants microcontroller_variant = Variants::M35P;
}    // namespace cortex
#elif defined(CORTEX_M) and (CORTEX_M == 55)
namespace cortex {
/// The microcontroller variant detected at compile time.
constexpr static Variants microcontroller_variant = Variants::M55;
}    // namespace cortex
#elif defined(CORTEX_M) and (CORTEX_M == 85)
namespace cortex {
/// The microcontroller variant detected at compile time.
constexpr static Variants microcontroller_variant = Variants::M85;
}    // namespace cortex
#else
#warning "CORTEX_M not defined or invalid value"
namespace cortex {
/// The microcontroller variant was not detected at compile time!
constexpr static Variants microcontroller_variant = Variants::Unknown;
}    // namespace cortex
#endif

#endif    // CORTEX_VARIANT_HPP_

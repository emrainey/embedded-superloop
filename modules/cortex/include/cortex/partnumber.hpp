#ifndef CORTEX_PART_NUMBER_HPP_
#define CORTEX_PART_NUMBER_HPP_

#include <cstdint>

/// @file
/// The Cortex Microcontroller Variant Header.
/// This file defines the various Cortex Microcontroller PartNumber and their features.

namespace cortex {
/// The Cortex Microcontroller PartNumber as taken from Data Sheets
enum class PartNumber : std::uint16_t {
    Unknown = 0,
    R18 = 0xC18,
    M0 = 0xC20,
    M3 = 0xC23,
    M4 = 0xC24,
    M7 = 0xC27,
    R52 = 0xD13,
    R82AE = 0xD14,
    R82 = 0xD15,
    R52P = 0xD16,
    M33 = 0xD21,
    M55 = 0xD22,
    M85 = 0xD23,
};

/// @brief Holds the Revision and Patch bits
struct Revision {
    uint8_t patch    : 4;    ///< Patch version number
    uint8_t revision : 4;    ///< Revision number
};

constexpr static Revision r0p0{0, 0};
constexpr static Revision r0p1{0, 1};
constexpr static Revision r0p2{0, 2};
constexpr static Revision r1p0{1, 0};
constexpr static Revision r1p1{1, 1};
constexpr static Revision r1p2{1, 1};

}    // namespace cortex

#if defined(CORTEX_M) and (CORTEX_M == 0)

#include "cortex/vendor/m0.hpp"

namespace cortex {
/// The microcontroller variant detected at compile time.
constexpr static PartNumber microcontroller_part_number = PartNumber::M0;
}    // namespace cortex

#elif defined(CORTEX_M) and (CORTEX_M == 3)

#include "cortex/vendor/m3.hpp"

namespace cortex {
/// The microcontroller variant detected at compile time.
constexpr static PartNumber microcontroller_part_number = PartNumber::M3;
}    // namespace cortex

#elif defined(CORTEX_M) and (CORTEX_M == 4)

#include "cortex/vendor/m4.hpp"

namespace cortex {
/// The microcontroller variant detected at compile time.
constexpr static PartNumber microcontroller_part_number = PartNumber::M4;
}    // namespace cortex

#elif defined(CORTEX_M) and (CORTEX_M == 7)

#include "cortex/vendor/m7.hpp"

namespace cortex {
/// The microcontroller variant detected at compile time.
constexpr static PartNumber microcontroller_part_number = PartNumber::M7;
}    // namespace cortex

#elif defined(CORTEX_M) and (CORTEX_M == 33)

#include "cortex/vendor/m33.hpp"

namespace cortex {
/// The microcontroller variant detected at compile time.
constexpr static PartNumber microcontroller_part_number = PartNumber::M33;
}    // namespace cortex

#elif defined(CORTEX_M) and (CORTEX_M == 55)

#include "cortex/vendor/m55.hpp"

namespace cortex {
/// The microcontroller variant detected at compile time.
constexpr static PartNumber microcontroller_part_number = PartNumber::M55;
}    // namespace cortex

#elif defined(CORTEX_M) and (CORTEX_M == 85)

#include "cortex/vendor/m85.hpp"

namespace cortex {
/// The microcontroller variant detected at compile time.
constexpr static PartNumber microcontroller_part_number = PartNumber::M85;
}    // namespace cortex
#else

#error "CORTEX_M not defined or invalid value"

namespace cortex {
/// The microcontroller variant was not detected at compile time!
constexpr static PartNumber microcontroller_part_number = PartNumber::Unknown;
}    // namespace cortex

#endif

#endif    // CORTEX_PART_NUMBER_HPP_

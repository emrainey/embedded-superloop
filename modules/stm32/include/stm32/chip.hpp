#ifndef STM32_CHIP_H_
#define STM32_CHIP_H_

/// @file
/// The ST Micro 32 Chip Header

#include "stm32/family.hpp"

namespace stm32 {

// declare the namespaces for the different series of STM32 parts. These are defined in their respective headers.
// declare the namespaces for the different series of STM32 parts. These are defined in their respective headers.
namespace f4xx {}
namespace h7xx {}

/// The enumerated supported chips in the STM32 module
enum class Chip : std::uint32_t {
    Undefined = 0U,
    stm32f405rg,
    stm32f407ve,
    stm32h753zi,
};

#if not defined(CHIP)
#define CHIP Undefined
#endif

/// Declares the chip from the enumeration. This is passed on the command line i.e.: -DCHIP=stm32f407ve
constexpr static Chip chip = Chip::CHIP;

}    // namespace stm32

#endif    // STM32_CHIP_H_

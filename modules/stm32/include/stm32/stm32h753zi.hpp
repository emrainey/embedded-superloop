#ifndef STM32H753ZI_HPP_
#define STM32H753ZI_HPP_

/// @file
/// STM32H753ZI Chip-Specific Definitions

#include "iso.hpp"
/// Indicates this chip has Flexible Static Memory Controller
#define STM32_HAS_FSMC 1
/// Indicates this chip has Ethernet MAC
#define STM32_HAS_ETHERNET 1
/// Indicates this chip has Digital Camera Memory Interface
#define STM32_HAS_CAMERA 1

#include "stm32/stm32h7xx.hpp"

/// The ST Micro 32 Namespace
namespace stm32 {

// The package determines the number of GPIOs available
#if defined(STM32H753ZILQFP144) and (STM32H753ZILQFP144 == 1)
/// The number of GPIOs on this part
constexpr static size_t number_of_gpios = 114U;
#else
#pragma message("Unknown PACKAGE therefore unknown number of GPIOs")
#endif

}    // namespace stm32

#endif    // STM32H753ZI_HPP_

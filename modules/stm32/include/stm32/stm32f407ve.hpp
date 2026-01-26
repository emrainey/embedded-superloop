#ifndef STM32F407VE_HPP_
#define STM32F407VE_HPP_

/// @file
/// STM32F407VE Chip-Specific Definitions

#define STM32_HAS_FSMC 1
#define STM32_HAS_ETHERNET 1
#define STM32_HAS_CAMERA 1

#include "stm32/stm32f40xxx.hpp"

/// The ST Micro 32 Namespace
namespace stm32 {

#if defined(STM32F407VELQFP100) and (STM32F407VELQFP100 == 1)
/// The number of GPIOs on this part
constexpr static size_t number_of_gpios = 82U;
#else
#pragma message("Unknown PACKAGE therefore unknown number of GPIOs but " FAMLIY " and " PACKAGE " are set")
#endif

}    // namespace stm32

#endif    // STM32F407VE_HPP_

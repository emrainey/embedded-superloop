#ifndef STM32F405RG_HPP_
#define STM32F405RG_HPP_

/// @file
/// STM32F405RG Chip-Specific Definitions

#undef STM32_HAS_FSMC
#undef STM32_HAS_ETHERNET
#undef STM32_HAS_CAMERA

#include "stm32/stm32f4xx.hpp"

/// The ST Micro 32 Namespace
namespace stm32 {

/// The number of GPIOs on this part
constexpr static size_t number_of_gpios = 51U;

}    // namespace stm32

#endif    // STM32F405RG_HPP_

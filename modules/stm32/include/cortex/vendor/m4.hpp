#ifndef STM32_CORTEX_VENDOR_M4_HPP
#define STM32_CORTEX_VENDOR_M4_HPP

/// @file
/// Cortex M4 Definitions for the STM32 family of microcontrollers

#include "cortex/m4.hpp"

#if defined(STM32F407VE) and (STM32F407VE == 1)
#include "stm32/stm32f407ve.hpp"
#elif defined(STM32F405RG) and (STM32F405RG == 1)
#include "stm32/stm32f405rg.hpp"
#else
#error "Unsupported STM32 Cortex M4 Variant"
#endif

namespace vendor = stm32;

#endif    // STM32_CORTEX_VENDOR_M4_HPP

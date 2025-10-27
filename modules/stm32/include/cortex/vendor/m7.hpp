#ifndef STM32_CORTEX_VENDOR_M7_HPP
#define STM32_CORTEX_VENDOR_M7_HPP

/// @file
/// Cortex M7 Definitions for the STM32 family of microcontrollers

#include "cortex/m7.hpp"

#if defined(STM32H753ZI) and (STM32H753ZI == 1)
#include "stm32/stm32h753zi.hpp"
#else
#error "Unsupported STM32 Cortex M7 Variant"
#endif

namespace vendor = stm32;

#endif    // STM32_CORTEX_VENDOR_M7_HPP

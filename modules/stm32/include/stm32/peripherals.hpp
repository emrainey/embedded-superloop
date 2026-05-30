#ifndef STM32_PERIPHERALS_HPP_
#define STM32_PERIPHERALS_HPP_

/// @file
/// The header to include in any chip specific driver to consolidate the chip/family specific picking of headers
/// @note Common Drivers should ONLY use stm32::peripherals::XXXX for their peripheral namespace, and not the family specific namespaces. This allows
/// the common drivers to be used across different STM32 families without modification.

#include "stm32/chip.hpp"

#if defined(STM32F4)
#include "stm32/stm32f4xx.hpp"
#elif defined(STM32H7)
#include "stm32/stm32h7xx.hpp"
#endif

#endif    // STM32_PERIPHERALS_HPP_

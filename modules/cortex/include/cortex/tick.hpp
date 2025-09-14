#ifndef CORTEX_TICK_HPP_
#define CORTEX_TICK_HPP_

/// @file
/// The Cortex Microcontroller System Tick Header

#include "core/Units.hpp"

namespace cortex {
/// @brief Ticks are held in unit
using Ticks = core::units::Ticks;

/// @brief The number of cycles per second
using Hertz = core::units::Hertz;

/// Gets the Current Ticks since Boot
Ticks GetTickCount(void);

/// Gets the Current Tick Rate per Second
Hertz GetTickRate();

/// Indicates if the System Tick has been enabled
bool IsTickEnabled();

}    // namespace cortex

#endif    // CORTEX_TICK_HPP_

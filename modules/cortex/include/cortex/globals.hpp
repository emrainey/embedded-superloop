#ifndef CORTEX_GLOBALS_HPP_
#define CORTEX_GLOBALS_HPP_

/// @file
/// Declarations fo the Cortex Global Variables

#include "cortex/tick.hpp"
#include "cortex/bist.hpp"

namespace cortex {
/// @brief The number of of ticks since boot.
/// This will be updated by the cortex::handlers::tick() handler so it is considered volatile
/// Stored in the cortex globals.cpp file. This is kept as a uint32_t to minimize the interrupt time.
extern std::uint32_t volatile ticks_since_boot;

/// @brief The flag indicating if the system tick is enabled.
extern bool is_tick_enabled;

/// @brief The built in self test data
/// This will be modified by the BIST handler so it is considered volatile
extern BuiltInSelfTest volatile built_in_self_test;

/// @brief The clock frequency of the Cortex Processor
extern Hertz clock_frequency;

/// @brief The system clock frequency (used by the SYSTICK)
extern Hertz system_clock_frequency;

}    // namespace cortex

#endif    // CORTEX_GLOBALS_HPP_

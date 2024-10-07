/// @file
/// Defines storage for all cortex global variables

#include "configure.hpp"
#include "cortex/bist.hpp"
#include "cortex/tick.hpp"

namespace cortex {

// the defined storage location for the clock frequency of the MCU
Hertz clock_frequency{0U};

// the defined storage location for the system tick feeder clock
Hertz system_clock_frequency{0U};

// the defined storage location for the tick count
std::uint32_t volatile ticks_since_boot{0u};

// the defined storage location for the tick flag
bool is_tick_enabled{false};

// the defined storage location for the built in self test data
BuiltInSelfTest volatile built_in_self_test{};

}    // namespace cortex

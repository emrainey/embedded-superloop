/// @file
/// Defines storage for all cortex global variables

#include <core/BoundsChecker.hpp>
#include <core/Units.hpp>

#include "cortex/bist.hpp"
#include "cortex/linker.hpp"
#include "cortex/tick.hpp"

namespace cortex {

// the defined storage location for the clock frequency of the MCU
LINKER_SECTION(".privileged_data") Hertz clock_frequency{0U};

// the defined storage location for the system tick feeder clock
LINKER_SECTION(".privileged_data") Hertz system_clock_frequency{0U};

// the defined storage location for the tick count
LINKER_SECTION(".privileged_data") std::uint32_t volatile ticks_since_boot{0u};

// the defined storage location for the tick flag
LINKER_SECTION(".privileged_data") bool is_tick_enabled{false};

// the defined storage location for the system state
LINKER_SECTION(".privileged_data") bool is_bist_successful{false};

// the defined storage location for the built in self test data
LINKER_SECTION(".privileged_data") BuiltInSelfTest volatile built_in_self_test{};

/// @brief The system memory checker instance
core::BoundsChecker const bounds_checker{sorted_memory_regions, sorted_region_count[0]};

}    // namespace cortex

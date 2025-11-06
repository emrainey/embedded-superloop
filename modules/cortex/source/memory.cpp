#include "core/Intervals.hpp"
#include "cortex/linker.hpp"
#include "cortex/mcu.hpp"

namespace cortex {

/// @brief The Cortex Microcontroller processor memory regions
LINKER_TYPED_SYMBOL(sorted_memory_regions, core::Interval const);

/// @brief Points to a LONG of the number of regions
LINKER_TYPED_SYMBOL(sorted_region_count, std::uint32_t const);

bool IsValidAddress(std::uintptr_t address) {
    core::Interval const *intervals = sorted_memory_regions;
    size_t count = static_cast<std::size_t>(sorted_region_count[0]);
    return core::Contains(intervals, count, address);
}

}    // namespace cortex

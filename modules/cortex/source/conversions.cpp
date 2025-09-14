#include "core/Conversions.hpp"
#include "configure.hpp"
#include "core/Units.hpp"

/// @file
/// @brief This file contains the conversion functions between different time units and ticks.
/// Ticks are defined in the configure.hpp and are typically the lowest resolution time unit available on the platform.

namespace core {
namespace units {

Ticks ConvertToTicks(Seconds const& time) {
    // e.g. 1/2 seconds = 1/2 * 128 ticks = 64.0 ticks
    float fraction = time.value() * cortex::ticks_per_second;
    return Ticks{static_cast<Ticks::StorageType>(fraction)};
}

Seconds ConvertToSeconds(Ticks const& ticks) {
    // e.g. 64 ticks = 64 / 128 seconds = 0.5 seconds
    float fraction = static_cast<Seconds::StorageType>(ticks.value()) / static_cast<Seconds::StorageType>(cortex::ticks_per_second);
    return Seconds{fraction};
}

}    // namespace units
}    // namespace core

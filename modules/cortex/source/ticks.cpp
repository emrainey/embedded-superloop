/// @file
/// Defines the tick functions for the Cortex M System Tick

#include "configure.hpp"
#include "cortex/globals.hpp"
#include "cortex/tick.hpp"

namespace cortex {

Ticks GetTickCount() {
    return Ticks{ticks_since_boot};
}

Hertz GetTickRate() {
    return Hertz{ticks_per_second};
}

bool IsTickEnabled() {
    return is_tick_enabled;
}

}    // namespace cortex

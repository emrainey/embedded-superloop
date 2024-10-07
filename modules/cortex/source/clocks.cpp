/// @file
/// Defines the Cortex M Clock interface

#include "configure.hpp"
#include "cortex/globals.hpp"

namespace cortex {

Hertz GetClockFrequency() {
    Hertz tmp;
    tmp = clock_frequency;
    return tmp;
}

void SetClockFrequency(Hertz frequency) {
    using namespace core::units;
    if (clock_frequency == 0_Hz) {
        clock_frequency = frequency;
    } else {
        // ignored
    }
}

Hertz GetSystemClockFrequency(void) {
    Hertz tmp;
    tmp = system_clock_frequency;
    return tmp;
}

void SetSystemClockFrequency(Hertz frequency) {
    using namespace core::units;
    if (system_clock_frequency == 0_Hz) {
        system_clock_frequency = frequency;
    } else {
        // ignored
    }
}

}    // namespace cortex

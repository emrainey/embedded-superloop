#ifndef CORTEX_CLOCKS_HPP_
#define CORTEX_CLOCKS_HPP_

#include "cortex/tick.hpp"

namespace cortex {

/// Gets the Clock Frequency of the Cortex Processor
/// @pre cortex::initialize::clocks
Hertz GetClockFrequency(void);

/// Sets the Clock Frequency of the Cortex Processor
/// @warning This should only be called once during boot. This value should be derived from the _already_ configured clock tree from
/// the vendor!
/// @param frequency The frequency to set the cortex clock variables to.
void SetClockFrequency(Hertz frequency);

/// @brief Returns the frequency of the system tick feeder clock.
Hertz GetSystemClockFrequency(void);

/// @brief Set during boot to the system clock frequency.
/// @param frequency The frequency that the system tick is run from.
void SetSystemClockFrequency(Hertz frequency);

}    // namespace cortex

#endif    // CORTEX_CLOCKS_HPP_
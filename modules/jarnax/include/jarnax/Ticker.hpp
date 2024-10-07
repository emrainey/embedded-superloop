#ifndef TICKER_HPP_
#define TICKER_HPP_

/// @file
/// jarnax::Ticker Interface

#include <cstdint>
#include "cortex/tick.hpp"

namespace jarnax {

/// The Storage of the Ticks type in the system
using Ticks = cortex::Ticks;
/// The Storage for cycles per second
using Hertz = cortex::Hertz;
/// The Storage for Time is seconds
using Time = core::units::Seconds;

/// The interface to the System Ticker
class Ticker {
public:
    /// Returns the number of Ticks in the system since boot
    virtual Ticks GetTicksSinceBoot(void) const = 0;

    /// Returns the number of ticks per second
    virtual Hertz GetTicksPerSecond(void) const = 0;

    /// Returns the Time since boot in seconds (as a `float`)
    virtual Time GetTimeSinceBoot(void) const = 0;

    /// Returns the number of biased ticks
    virtual Ticks GetTicks(void) const = 0;

    /// Returns the adjusted time
    virtual Time GetTime(void) const = 0;

    /// Allows the time and ticks to be adjusted by a fixed amount.
    /// A bias of zero sets the time and ticks to be "since boot".
    /// A bias of other values can adjust the time farther into the future.
    virtual void AdjustTicks(Ticks bias) = 0;

    /// Indicates if the System Ticker was configured and is enabled.
    /// @return bool true If running, false otherwise.
    virtual bool IsEnabled(void) const = 0;

protected:
    ~Ticker() = default;
};

/// The global ticker
extern Ticker& GetTicker(void);

}    // namespace jarnax

#endif    // TICKER_HPP_
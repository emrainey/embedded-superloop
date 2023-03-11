#ifndef TICKER_HPP_
#define TICKER_HPP_

/// @file
/// jarnax::Exectuable Interface

#include <cstdint>

namespace jarnax {

/// The Storage of the Ticks type in the system
using Ticks = std::uint64_t;

/// The Storage of the Time type in the system
using Time = float;

/// The interface to the System Ticker
class Ticker {
public:
    /// Returns the number of Ticks in the system since boot
    virtual Ticks GetTicksSinceBoot(void) const = 0;

    /// Returns the number of ticks per second
    virtual Ticks GetTicksPerSecond(void) const = 0;

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
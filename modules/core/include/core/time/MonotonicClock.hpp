#ifndef CORE_TIME_HPP
#define CORE_TIME_HPP

/// @file
/// Monotonic Clock Interface

#include <core/units/MicroSeconds.hpp>

namespace core {
// The time namespace for the core library
namespace time {

// The basic time unit is microseconds
using MicroSeconds = core::units::MicroSeconds;

/// The interface which a monotonic clock must implement
class MonotonicClock {
public:
    /// Returns the current time in microseconds
    /// @note If not adjusted, this time is based on the system clock and is a "time since boot"
    /// @return The current time in microseconds since Epoch if adjusted.
    virtual MicroSeconds Now() const = 0;

protected:
    virtual ~MonotonicClock() = default;
};

}    // namespace time

}    // namespace core

#endif    // CORE_TIME_HPP

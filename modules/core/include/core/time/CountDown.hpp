#ifndef CORE_TIME_COUNTDOWN_HPP
#define CORE_TIME_COUNTDOWN_HPP

/// @file
/// Countdown Timer Implementation

#include "core/time/MonotonicClock.hpp"

namespace core {

namespace time {

/// @brief A countdown timer that can be used to check to see if a duration has elapsed. The countdown has two main uses
/// but in both case it is used to check if a duration has elapsed.
/// In the first usage after the countdown has expired, a @ref Reset is called to use the same duration minus the delta time we were late.
class CountDown {
public:
    /// @brief Construct a new Count Down object with an initial duration.
    /// @param clock The monotonic clock to use for timing
    /// @param duration The countdown duration in microseconds
    CountDown(core::time::MonotonicClock const& clock, MicroSeconds duration);

    /// @brief Indicates if the countdown has expired.
    /// @post Reset() to use the same duration or Restart() to set a new duration.
    /// @return True if expired, False otherwise.
    bool IsExpired() const;

    /// @brief Returns our last lastness delta.
    /// @return The delta time we were late when the countdown expired.
    MicroSeconds GetLateness() const;

    /// @brief Resets the countdown to the original duration minus the delta time we were late.
    void Reset();

    /// @brief Restarts the countdown with a new duration without adjusting for late expiration of the last countdown.
    /// @param new_duration The new duration to use.
    void Restart(MicroSeconds new_duration);

protected:
    /// @brief The reference to the clock
    MonotonicClock const& clock_;
    /// @brief Holds the current relative duration of the countdown. This is the ideal value, not adjusted for late expiration.
    MicroSeconds duration_;
    /// @brief This is the absolute value of the when the countdown expires.
    MicroSeconds limit_;
    /// @brief The last time the countdown was started.
    MicroSeconds last_;
    /// @brief Used to capture how late the expiration was. This will be subtracted from the next duration.
    mutable MicroSeconds delta_late_;
};

}    // namespace time
}    // namespace core

#endif    // CORE_TIME_COUNTDOWN_HPP

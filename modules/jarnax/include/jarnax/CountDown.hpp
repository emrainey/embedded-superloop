#ifndef JARNAX_COUNTDOWN_HPP
#define JARNAX_COUNTDOWN_HPP

#include "core/Units.hpp"
#include "jarnax/Timer.hpp"

namespace jarnax {

/// @brief A countdown timer that can be used to check to see if a duration has elapsed. The countdown has two main uses
/// but in both case it is used to check if a duration has elapsed.
/// In the first usage after the countdown has expired, a @ref Reset is called to use the same duration minus the delta time we were late.
class CountDown {
public:
    /// @brief Construct a new Count Down object with an initial duration.
    /// @param timer
    /// @param duration
    CountDown(Timer const& timer, core::units::Iota duration);

    /// @brief Indicates if the countdown has expired.
    /// @post Reset() to use the same duration or Restart() to set a new duration.
    /// @return True if expired, False otherwise.
    bool IsExpired();

    /// @brief Returns our last lastness delta.
    /// @return The delta time we were late when the countdown expired.
    core::units::Iota GetLateness() const { return delta_late_; }

    /// @brief Resets the countdown to the original duration minus the delta time we were late.
    void Reset();

    /// @brief Restarts the countdown with a new duration without adjusting for late expiration of the last countdown.
    /// @param new_duration The new duration to use.
    void Restart(core::units::Iota new_duration);

protected:
    Timer const& timer_;
    /// @brief Holds the current relative duration of the countdown. This is the ideal value, not adjusted for late expiration.
    core::units::Iota duration_;
    /// @brief This is the absolute value of the when the
    core::units::Iota limit_;
    core::units::Iota last_;
    /// @brief Used to capture how late the expiration was. This will be subtracted from the next duration.
    core::units::Iota delta_late_;
};
}

#endif // JARNAX_COUNTDOWN_HPP
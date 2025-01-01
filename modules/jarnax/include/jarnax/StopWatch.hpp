#ifndef JARNAX_STOPWATCH_HPP
#define JARNAX_STOPWATCH_HPP

#include "core/Units.hpp"
#include "jarnax/Timer.hpp"

namespace jarnax {

class StopWatch {
public:
    /// @brief The Parameter Constructor
    /// @param timer The constant reference to the Timer.
    StopWatch(Timer const& timer);

    /// @brief Captures the Start time and erases the time difference.
    void Start();

    /// @brief Captures the timer difference and erases the start time.
    void Stop();

    /// @brief Returns the time difference in Iota between @ref Stop and @ref Start.
    /// @retval zero If this returns zero, the timer was not started or stopped.
    core::units::Iota GetElapsed() const;

protected:
    Timer const& timer_;         ///< The reference to the timer.
    core::units::Iota start_;    ///< The start time
    core::units::Iota diff_;     ///< The difference between Stop and Start time, or zero.
};

}    // namespace jarnax

#endif    // JARNAX_STOPWATCH_HPP
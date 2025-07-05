#ifndef JARNAX_TIMER_HPP
#define JARNAX_TIMER_HPP

#include "core/Units.hpp"

namespace jarnax {

/// @brief The Timer interface which provides a time in microseconds since it's start.
class Timer {
public:
    /// @brief Returns the elapsed time in iotas (the highest resolution of time, but an arbitrary unit)
    /// @warning The iota is based on the system clock and is not required to be a power of 10.
    /// @note The iota is guaranteed to be monotonic, so it may not be suitable for all timing purposes. However it will LOOP at some point.
    virtual core::units::Iota GetIotas(void) const = 0;

    /// @brief Returns the elapsed time in microseconds.
    virtual core::units::MicroSeconds GetMicroseconds(void) const = 0;

    /// @brief Returns the elapsed time in seconds.
    virtual core::units::Seconds GetSeconds(void) const = 0;

protected:
    ~Timer() = default;
};

/// Returns the higher precision timer for the system.
extern Timer& GetTimer(void);

}    // namespace jarnax

#endif    // JARNAX_TIMER_HPP
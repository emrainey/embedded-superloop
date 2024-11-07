#ifndef JARNAX_TIMER_HPP
#define JARNAX_TIMER_HPP

#include "core/Units.hpp"

namespace jarnax {

/// @brief The Timer interface which provides a time in microseconds since it's start.
class Timer {
public:
    /// @brief Returns the elapsed time in iotas (the highest resolution of time, but an arbitrary unit)
    virtual core::units::Iota GetIotas(void) const = 0;

    /// @brief Returns the elapsed time in microseconds.
    virtual core::units::MicroSeconds GetMicroseconds(void) const = 0;

protected:
    ~Timer() = default;
};

/// Returns the higher precision timer for the system.
extern Timer& GetTimer(void);

}    // namespace jarnax

#endif    // JARNAX_TIMER_HPP
#ifndef JUMP_TIMER_HPP
#define JUMP_TIMER_HPP

/// @file
/// Jump Timer for Time-Based Testing

#include "jarnax/Timer.hpp"

namespace jarnax {

using namespace core::units;

/// The Testing Mock for Timers which can jump forward in time
class JumpTimer : public Timer {
public:
    /// @brief Constructor
    JumpTimer()
        : current_{0U} {}

    /// @brief Default Destructor
    virtual ~JumpTimer() = default;

    /// @brief Gets the current time in iotas
    Iota GetIotas(void) const override { return current_; }

    /// @brief Gets the current time in microseconds
    MicroSeconds GetMicroseconds(void) const override {
        // 1 us = 1 iota
        return MicroSeconds{GetIotas().value()};
    }

    /// @brief Gets the current time in seconds
    Seconds GetSeconds(void) const override {
        // 1 sec = 1'000'000 iotas
        return Seconds{static_cast<Seconds::StorageType>(current_.value()) / 1E6f};
    }

    /// @brief Jumps the timer forward by the specified iotas
    /// @param iotas The number of iotas to jump forward
    void Jump(Iota iotas) {
        current_ = current_ + iotas;
        return;
    }

    /// @brief Jumps the timer forward by the specified microseconds
    /// @param microseconds The number of microseconds to jump forward
    void Jump(MicroSeconds microseconds) {
        // 1 iota == 1 usec
        current_ = current_ + Iota{microseconds.value()};
        return;
    }

protected:
    Iota current_;    ///< The current time in iotas
};

// There's already a global for GetTimer() in the system, even in test mode, so we don't need to create one here.

}    // namespace jarnax

#endif    // JUMP_TIMER_HPP

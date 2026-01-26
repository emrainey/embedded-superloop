#ifndef JUMP_CLOCK_HPP
#define JUMP_CLOCK_HPP

/// @file
/// Jump Clock for Time-Based Testing

#include "core/time/MonotonicClock.hpp"

namespace core {
namespace time {

class JumpClock : public MonotonicClock {
public:
    JumpClock()
        : current_{0U} {}

    virtual ~JumpClock() = default;

    MicroSeconds Now(void) const override { return current_; }

    void Jump(MicroSeconds microseconds) {
        current_ = current_ + microseconds;
        return;
    }

protected:
    MicroSeconds current_;
};

}    // namespace time
}    // namespace core

#endif    // JUMP_CLOCK_HPP

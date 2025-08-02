#ifndef JUMP_TIMER_HPP
#define JUMP_TIMER_HPP

#include "jarnax/Timer.hpp"

namespace jarnax {

using namespace core::units;

class JumpTimer : public Timer {
public:
    JumpTimer()
        : current_{0U} {}

    virtual ~JumpTimer() = default;

    Iota GetIotas(void) const override { return current_; }

    MicroSeconds GetMicroseconds(void) const override {
        // 1 us = 1 iota
        return MicroSeconds{GetIotas().value()};
    }

    Seconds GetSeconds(void) const override {
        // 1 sec = 1'000'000 iotas
        return Seconds{static_cast<Seconds::StorageType>(current_.value()) / 1E6f};
    }

    void Jump(Iota iotas) {
        current_ = current_ + iotas;
        return;
    }

    void Jump(MicroSeconds microseconds) {
        // 1 iota == 1 usec
        current_ = current_ + Iota{microseconds.value()};
        return;
    }

protected:
    Iota current_;
};

// There's already a global for GetTimer() in the system, even in test mode, so we don't need to create one here.

}    // namespace jarnax

#endif    // JUMP_TIMER_HPP
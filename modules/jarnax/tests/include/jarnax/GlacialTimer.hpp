#ifndef GLACIAL_TIMER_HPP
#define GLACIAL_TIMER_HPP

#include "jarnax/Timer.hpp"

namespace jarnax {

using namespace core::units;

class GlacialTimer : public Timer {
public:
    GlacialTimer()
        : current_{0U} {}

    virtual ~GlacialTimer() = default;

    Iota GetIotas(void) const override {
        auto now = current_;
        current_ = now + 1_iota; // Simulate a tick
        return current_;
    }

    MicroSeconds GetMicroseconds(void) const override {
        // 1 us = 1 iota
        return MicroSeconds{GetIotas().value()};
    }

    Seconds GetSeconds(void) const override {
        // 1 sec = 1'000'000 iotas
        return Seconds{static_cast<Seconds::StorageType>(current_.value()) / 1E6f};
    }

protected:
    mutable Iota current_;
};

// There's already a global for GetTimer() in the system, even in test mode, so we don't need to create one here.

}    // namespace jarnax

#endif    // GLACIAL_TIMER_HPP
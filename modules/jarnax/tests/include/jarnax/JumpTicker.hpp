#ifndef JUMP_TICKER_HPP
#define JUMP_TICKER_HPP

#include "jarnax/Ticker.hpp"

namespace jarnax {

using namespace core::units;

class JumpTicker : public Ticker {
public:
    JumpTicker(Ticks starting)
        : current_{0u}
        , bias_{starting} {}
    Ticks GetTicksSinceBoot(void) const override {
        Ticks tmp;
        tmp = current_;
        current_ = current_ + 1_ticks;
        return tmp;
    }
    Hertz GetTicksPerSecond(void) const override { return Hertz{core::units::ticks_per_second.value()}; }
    Time GetTimeSinceBoot(void) const override { return core::units::ConvertToSeconds(GetTicksSinceBoot()); }
    Ticks GetTicks(void) const override { return GetTicksSinceBoot() + bias_; }
    Time GetTime(void) const override { return core::units::ConvertToSeconds(GetTicksSinceBoot() + bias_); }
    void AdjustTicks(Ticks bias) override { bias_ = bias; }
    bool IsEnabled(void) const override { return true; }

    void Jump(Ticks ticks) {
        current_ = current_ + ticks;
        return;
    }

protected:
    mutable Ticks current_{0u};
    Ticks bias_{0u};
};

Ticker &GetTicker() {
    static JumpTicker ticker{0_ticks};
    return ticker;
}

}   // namespace jarnax

#endif // JUMP_TICKER_HPP

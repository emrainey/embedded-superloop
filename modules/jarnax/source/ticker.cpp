#include "jarnax/system.hpp"

namespace jarnax {

// Defined in globals.cpp
extern Ticks volatile tick_count;
extern bool is_tick_running;

/// The internal interface to the Ticker
class TickInterface final : public Ticker {
public:
    TickInterface() : m_bias_{0U} {}
    Ticks GetTicksPerSecond(void) const override { return jarnax::ticks_per_second; }
    Ticks GetTicksSinceBoot(void) const override { return jarnax::tick_count; }
    Ticks GetTicks(void) const override { return jarnax::tick_count + m_bias_; }
    Time GetTimeSinceBoot(void) const override {
        auto ticks = GetTicksSinceBoot();
        return jarnax::tick_period * static_cast<Time>(ticks);
    }
    Time GetTime(void) const override {
        auto ticks = GetTicks();
        return jarnax::tick_period * static_cast<Time>(ticks);
    }
    void AdjustTicks(Ticks bias) override { m_bias_ = bias; }

    bool IsEnabled(void) const override { return jarnax::is_tick_running; }

protected:
    Ticks m_bias_;
};

// Only make it static once we can protect it from direct reference
TickInterface ticker;

Ticker& GetTicker(void) {
    return ticker;
}

}    // namespace jarnax
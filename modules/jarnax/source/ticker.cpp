#include "jarnax/system.hpp"

namespace jarnax {

/// The internal interface to the Ticker
class TickInterface final : public Ticker {
public:
    TickInterface()
        : bias_{0U} {}
    Hertz GetTicksPerSecond(void) const override { return cortex::GetTickRate(); }
    Ticks GetTicksSinceBoot(void) const override { return cortex::GetTickCount(); }
    Ticks GetTicks(void) const override { return cortex::GetTickCount() + bias_; }
    Time GetTimeSinceBoot(void) const override {
        auto ticks = GetTicksSinceBoot();
        return core::units::ConvertToSeconds(ticks);
    }
    Time GetTime(void) const override {
        auto ticks = GetTicks();
        return core::units::ConvertToSeconds(ticks);
    }
    void AdjustTicks(Ticks bias) override { bias_ = bias; }

    bool IsEnabled(void) const override { return cortex::IsTickEnabled(); }

protected:
    Ticks bias_;
};

Ticker& GetTicker(void) {
    static TickInterface ticker;
    return ticker;
}

}    // namespace jarnax
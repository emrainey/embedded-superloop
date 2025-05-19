#include "jarnax/Monitor.hpp"

namespace jarnax {

Monitor::Monitor(jarnax::Timer& timer, jarnax::Indicator& status_indicator, jarnax::Indicator& error_indicator)
    : timer_{timer}
    , status_indicator_{status_indicator}
    , error_indicator_{error_indicator}
    , countdown_{timer, core::units::Iota{500'000U}} {
}

bool Monitor::Execute() {
    if (countdown_.IsExpired()) {
        status_indicator_.Toggle();
        countdown_.Reset();
    }
    return true;
}

}    // namespace jarnax

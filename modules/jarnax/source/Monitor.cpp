#include "jarnax/Monitor.hpp"
#include "core/Conversions.hpp"
#include "debug.hpp"
#include "jarnax/print.hpp"

namespace jarnax {

Monitor::Monitor(jarnax::Timer const& timer, jarnax::Indicator& status_indicator, jarnax::Indicator& error_indicator)
    : timer_{timer}
    , status_indicator_{status_indicator}
    , error_indicator_{error_indicator}
    , countdown_{timer, core::units::ConvertToIota(HalfPeriodStatusBlink)} {}

void Monitor::Report(core::Status status) {
    reported_status_ = status;
}

bool Monitor::Execute() {
    if (countdown_.IsExpired()) {
        status_indicator_.Toggle();
        countdown_.Reset();
    }
    if (reported_status_.IsSuccess()) {
        error_indicator_.Inactive();
    } else {
        error_indicator_.Active();
    }
    auto& log = core::Status::GetLog();
    while (not log.IsEmpty()) {
        core::Status status;
        log.Pop(status);
        if constexpr (debug::Monitor) {
            jarnax::print("Monitor Log: ", status);
        }
    }
    return true;
}

}    // namespace jarnax

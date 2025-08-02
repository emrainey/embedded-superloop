#include "memory.h"
#include "TimerTest.hpp"
#include "jarnax/Assertion.hpp"

using namespace core::units;

core::units::Iota g_lateness;    // global lateness variable

TimerTest::TimerTest()
    : ticker_{jarnax::GetTicker()}
    , timer_{jarnax::GetTimer()}
    , indicator_{jarnax::GetBoardContext().GetTimingIndicator()}
    , countdown_time_msec_{11U}
    , countdown_time_iotas_{core::units::ConvertToIota(countdown_time_msec_)}
    , countdown_{timer_, countdown_time_iotas_}
    , last_value_{0_iota}
    , state_machine_{*this, AppState::High} {
}

bool TimerTest::Execute() {
    if (state_machine_.IsFinal()) {
        state_machine_.Enter();
    }
    state_machine_.RunOnce();
    return true;
}

void TimerTest::OnEnter() {
    jarnax::print("TimerTest::OnEnter\r\n");
    jarnax::print(
        "Using %lu iotas (%lu milliseconds) for each state period\r\n",
        static_cast<unsigned long>(countdown_time_iotas_.value()),
        static_cast<unsigned long>(countdown_time_msec_.value())
    );
    jarnax::print("The Timing Pin will be active and inactive for the above iota period. The high and low should be equal.\r\n");
}

void TimerTest::OnEntry(AppState state) {
    // jarnax::print("TimerTest::OnEntry: %u\r\n", static_cast<std::uint8_t>(state));
    if (state == AppState::High) {
        indicator_.Active();
    } else if (state == AppState::Low) {
        indicator_.Inactive();
    }
}

AppState TimerTest::OnCycle(AppState state) {
    // jarnax::print("TimerTest::OnCycle: %u\r\n", static_cast<std::uint8_t>(state));
    auto now = timer_.GetIotas();    // should always be monotonically increasing
    if (last_value_ > now) {
        // the monotonic timer is not monotonic, need to Alert
        jarnax::print("TimerTest::OnCycle: Timer is NOT monotonic! Last: %" PRIu64 " > Now: %" PRIu64 "\r\n", last_value_.value(), now.value());
    } else if constexpr (false) {
        auto sec = timer_.GetSeconds();
        // This will print A LOT, so don't do it unless you want to see it
        jarnax::print(
            "TimerTest::OnCycle: Timer is monotonic! Last: %" PRIx64 " <= Now: %" PRIx64 " (Sec: %lf)\r\n",
            last_value_.value(),
            now.value(),
            static_cast<double>(sec.value())
        );
    }
    last_value_ = now;    // reset the last value to the current value
    if (state == AppState::High) {
        if (countdown_.IsExpired()) {
            state = AppState::Low;
        }
    } else if (state == AppState::Low) {
        if (countdown_.IsExpired()) {
            state = AppState::High;
        }
    }
    return state;
}

void TimerTest::OnExit(AppState state) {
    // jarnax::print("TimerTest::OnExit: %u\r\n", static_cast<std::uint8_t>(state));
    if constexpr (false) {
        // this is lost after a reset of the countdown so we have to do it here
        g_lateness = countdown_.GetLateness();
        if (g_lateness > 0_iota) {
            // the more this prints the later we become?
            jarnax::print("TimerTest::OnTransition: Lateness: %lu iota\r\n", static_cast<unsigned long>(g_lateness.value()));
        }
    }
    if (state == AppState::High) {
        countdown_.Reset();
    } else if (state == AppState::Low) {
        countdown_.Reset();
    }
}

void TimerTest::OnTransition(AppState from, AppState to) {
    static_cast<void>(from);    // Suppress unused variable warning
    static_cast<void>(to);      // Suppress unused variable warning
    // jarnax::print("TimerTest::OnTransition: %u -> %u\r\n", static_cast<std::uint8_t>(from), static_cast<std::uint8_t>(to));
    // get the lateness of the last countdown
}

void TimerTest::OnExit() {
    // jarnax::print("TimerTest::OnExit\r\n");
}

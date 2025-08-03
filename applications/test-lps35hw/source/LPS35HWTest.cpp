#include "LPS35HWTest.hpp"
#include "board.hpp"
#include "jarnax/Assertion.hpp"
#include "memory.h"

using namespace core::units;

LPS35HWTest::LPS35HWTest()
    : state_machine_{*this, AppState::Idle}
    , lps35hw_driver_{jarnax::GetBoardContext().GetLps35hwDriver()}
    , countdown_{jarnax::GetBoardContext().GetTimer(), core::units::ConvertToIota(core::units::MilliSeconds(1000))} {}

bool LPS35HWTest::Execute() {
    if (state_machine_.IsFinal()) {
        state_machine_.Enter();
    }
    state_machine_.RunOnce();
    return true;
}

void LPS35HWTest::OnEnter() {
    jarnax::print("LPS35HWTest print the values out every once in a while\r\n");
}

void LPS35HWTest::OnEntry(AppState state) {
    // jarnax::print("LPS35HWTest::OnEntry: %u\r\n", static_cast<std::uint8_t>(state));
    if (state == AppState::Idle) {
        // do nothing
        // lps35hw_driver_.PowerOn();
    }
}

AppState LPS35HWTest::OnCycle(AppState state) {
    // jarnax::print("LPS35HWTest::OnCycle: %u\r\n", static_cast<std::uint8_t>(state));
    if (state == AppState::Idle) {
        if (countdown_.IsExpired()) {
            // jarnax::print("LPS35HWTest::OnCycle: %u\r\n", static_cast<std::uint8_t>(state));
            auto pressure = lps35hw_driver_.GetLastPressure();
            auto temperature = lps35hw_driver_.GetLastTemperature();
            jarnax::print("Pressure: %f, Temperature: %f\r\n", static_cast<double>(pressure.value()), static_cast<double>(temperature.value()));
            countdown_.Reset();
        }
    }
    return state;
}

void LPS35HWTest::OnExit(AppState state) {
    // jarnax::print("LPS35HWTest::OnExit: %u\r\n", static_cast<std::uint8_t>(state));
    if (state == AppState::Idle) {
        // nothing
    }
}

void LPS35HWTest::OnTransition(AppState from, AppState to) {
    static_cast<void>(from);
    static_cast<void>(to);
    jarnax::print("LPS35HWTest::OnTransition: %u -> %u\r\n", static_cast<std::uint8_t>(from), static_cast<std::uint8_t>(to));
}

void LPS35HWTest::OnExit() {
    // jarnax::print("LPS35HWTest::OnExit\r\n");
}

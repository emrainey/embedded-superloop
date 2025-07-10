#include "memory.h"
#include "DisplayTest.hpp"
#include "board.hpp"
#include "jarnax/Assertion.hpp"

using namespace core::units;

DisplayTest::DisplayTest(jarnax::drivers::ssd1306::Driver& driver)
    : ticker_{jarnax::GetTicker()}
    , timer_{jarnax::GetTimer()}
    , display_driver_{driver}
    , change_duration_{2'000'000_usec}
    , change_duration_iota_{core::units::ConvertToIota(change_duration_)}
    , countdown_{timer_, change_duration_iota_}
    , state_machine_{*this, AppState::Waiting} {
}

bool DisplayTest::Execute() {
    if (state_machine_.IsFinal()) {
        state_machine_.Enter();
    }
    state_machine_.RunOnce();
    return true;
}

void DisplayTest::OnEnter() {
    jarnax::print("DisplayTest will cycle over powering on and off the display every %" PRIu64 " usec\r\n", change_duration_.value());
}

void DisplayTest::OnEntry(AppState state) {
    jarnax::print("DisplayTest::OnEntry: %u\r\n", static_cast<std::uint8_t>(state));
    if (state == AppState::Waiting) {
        jarnax::print("Booting Display.");
    } else if (state == AppState::DisplayPowerOn) {
        auto& image = display_driver_.GetImage();
        image.clear();
        auto& screen = display_driver_.GetScreen();
        screen.checkerboard();    // Fill the screen with a pattern
        screen.render();
        display_driver_.Update();
    } else if (state == AppState::DisplayPowerOff) {
        auto& image = display_driver_.GetImage();
        image.clear();
        display_driver_.Update();
    } else if (state == AppState::Error) {
        //
    }
}

AppState DisplayTest::OnCycle(AppState state) {
    core::Status status;
    // jarnax::print("DisplayTest::OnCycle: %u\r\n", static_cast<std::uint8_t>(state));
    if (state == AppState::Waiting) {
        status = display_driver_.GetStatus();
        if (status == core::Result::NotReady) {
            // Display is not ready, wait
            jarnax::print(".");
        } else if (status == core::Result::Success) {
            // Display is ready, proceed
            state = AppState::DisplayPowerOn;
        } else {
            jarnax::print("Display is not ready? ", status);
        }
    } else if (state == AppState::DisplayPowerOn) {
        if (countdown_.IsExpired()) {
            state = AppState::DisplayPowerOff;
        }
    } else if (state == AppState::DisplayPowerOff) {
        if (countdown_.IsExpired()) {
            state = AppState::DisplayPowerOn;
        }
    } else if (state == AppState::Error) {
        //
    }
    return state;
}

void DisplayTest::OnExit(AppState state) {
    jarnax::print("DisplayTest::OnExit: %u\r\n", static_cast<std::uint8_t>(state));
    if (state == AppState::Waiting) {
        jarnax::print("\r\n");
    } else if (state == AppState::DisplayPowerOn) {
        countdown_.Reset();
    } else if (state == AppState::DisplayPowerOff) {
        countdown_.Reset();
    } else if (state == AppState::Error) {
        //
    }
}

void DisplayTest::OnTransition(AppState from, AppState to) {
    static_cast<void>(from);
    static_cast<void>(to);
    jarnax::print("DisplayTest::OnTransition: %u -> %u\r\n", static_cast<std::uint8_t>(from), static_cast<std::uint8_t>(to));
}

void DisplayTest::OnExit() {
    // jarnax::print("DisplayTest::OnExit\r\n");
}

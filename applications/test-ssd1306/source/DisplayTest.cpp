#include "DisplayTest.hpp"
#include "board.hpp"
#include "jarnax/Assertion.hpp"
#include "memory.h"

using namespace core::units;

DisplayTest::DisplayTest(jarnax::drivers::ssd1306::Driver& driver)
    : ticker_{jarnax::GetTicker()}
    , timer_{jarnax::GetBoardContext().GetTimer()}
    , display_driver_{driver}
    , change_duration_{2'000'000_usec}
    , change_duration_iota_{core::units::ConvertToIota(change_duration_)}
    , countdown_{timer_, change_duration_iota_}
    , state_machine_{*this, AppState::Waiting} {}

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
    // jarnax::print("DisplayTest::OnEntry: %u\r\n", static_cast<std::uint8_t>(state));
    auto& image = display_driver_.GetImage();
    auto& screen = display_driver_.GetScreen();

    if (state == AppState::Waiting) {
        jarnax::print("Booting Display.\r\n");
        countdown_.Reset();
    } else if (state == AppState::DisplayPowerOn) {
        screen.clear();           // Clear the image buffer
        screen.checkerboard();    // Fill the screen with a checkerboard pattern
        screen.render();          // transfer to the image buffer
        display_driver_.Update();
    } else if (state == AppState::Pattern1) {
        image.pattern(::ssd1306::Image128x32::Pattern::Checkerboard);
        display_driver_.Update();
    } else if (state == AppState::Pattern2) {
        image.pattern(::ssd1306::Image128x32::Pattern::FlippingCounters);
        display_driver_.Update();
    } else if (state == AppState::Pattern3) {
        image.pattern(::ssd1306::Image128x32::Pattern::VerticalStripes);
        display_driver_.Update();
    } else if (state == AppState::Pattern4) {
        image.pattern(::ssd1306::Image128x32::Pattern::HorizontalStripes);
        display_driver_.Update();
    } else if (state == AppState::Pattern5) {
        image.pattern(::ssd1306::Image128x32::Pattern::AA55);
        display_driver_.Update();
    } else if (state == AppState::Pattern6) {
        screen.clear();                       // Clear the image buffer
        screen.write(0, 0, "Hello World");    // Write a message to the screen
        screen.render();                      // transfer to the image buffer
        display_driver_.Update();
    } else if (state == AppState::DisplayPowerOff) {
        image.clear();
        display_driver_.Update();
    } else if (state == AppState::Error) {
        jarnax::print("DisplayTest::OnEntry: Error state\r\n");
    }
}

AppState DisplayTest::OnCycle(AppState state) {
    core::Status status = display_driver_.GetStatus();
    // jarnax::print("DisplayTest::OnCycle: %u\r\n", static_cast<std::uint8_t>(state));
    if (state != AppState::Waiting and not status.IsBusy() and not status.IsSuccess()) {
        jarnax::print("Display Driver is ", status);
    }
    if (state == AppState::Waiting) {
        if (status == core::Result::NotReady) {
            // Display is not ready, wait
            // jarnax::print(".");
        } else if (status == core::Result::Success) {
            // Display is ready, proceed
            state = AppState::DisplayPowerOn;
        } else {
            jarnax::print("Display is not ready? ", status);
            state = AppState::Error;
        }
    } else if (state == AppState::DisplayPowerOn) {
        if (countdown_.IsExpired() and not status.IsBusy()) {
            state = AppState::Pattern1;
        }
    } else if (state == AppState::Pattern1) {
        if (countdown_.IsExpired() and not status.IsBusy()) {
            state = AppState::Pattern2;
        }
    } else if (state == AppState::Pattern2) {
        if (countdown_.IsExpired() and not status.IsBusy()) {
            state = AppState::Pattern3;
        }
    } else if (state == AppState::Pattern3) {
        if (countdown_.IsExpired() and not status.IsBusy()) {
            state = AppState::Pattern4;
        }
    } else if (state == AppState::Pattern4) {
        if (countdown_.IsExpired() and not status.IsBusy()) {
            state = AppState::Pattern5;
        }
    } else if (state == AppState::Pattern5) {
        if (countdown_.IsExpired() and not status.IsBusy()) {
            state = AppState::Pattern6;
        }
    } else if (state == AppState::Pattern6) {
        if (countdown_.IsExpired() and not status.IsBusy()) {
            state = AppState::DisplayPowerOff;
        }
    } else if (state == AppState::DisplayPowerOff) {
        if (countdown_.IsExpired() and not status.IsBusy()) {
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
    } else if (state == AppState::Pattern1) {
        countdown_.Reset();
    } else if (state == AppState::Pattern2) {
        countdown_.Reset();
    } else if (state == AppState::Pattern3) {
        countdown_.Reset();
    } else if (state == AppState::Pattern4) {
        countdown_.Reset();
    } else if (state == AppState::Pattern5) {
        countdown_.Reset();
    } else if (state == AppState::Pattern6) {
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

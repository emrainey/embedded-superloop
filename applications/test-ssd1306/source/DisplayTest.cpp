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
    , state_machine_{*this, AppState::Waiting}
    , has_updated_{false} {}

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
    } else if (state == AppState::Pattern1) {
        image.pattern(::ssd1306::Image128x32::Pattern::Checkerboard);
        display_driver_.Update();
        has_updated_ = false;
        countdown_.Restart(change_duration_iota_);
    } else if (state == AppState::Pattern2) {
        image.pattern(::ssd1306::Image128x32::Pattern::FlippingCounters);
        display_driver_.Update();
        has_updated_ = false;
        countdown_.Restart(change_duration_iota_);
    } else if (state == AppState::Pattern3) {
        image.pattern(::ssd1306::Image128x32::Pattern::VerticalStripes);
        display_driver_.Update();
        has_updated_ = false;
        countdown_.Restart(change_duration_iota_);
    } else if (state == AppState::Pattern4) {
        image.pattern(::ssd1306::Image128x32::Pattern::HorizontalStripes);
        display_driver_.Update();
        has_updated_ = false;
        countdown_.Restart(change_duration_iota_);
    } else if (state == AppState::Pattern5) {
        image.pattern(::ssd1306::Image128x32::Pattern::AA55);
        display_driver_.Update();
        has_updated_ = false;
        countdown_.Restart(change_duration_iota_);
    } else if (state == AppState::Pattern6) {
        screen.clear();                       // Clear the image buffer
        screen.write(0, 0, "Hello World");    // Write a message to the screen
        screen.render();                      // transfer to the image buffer
        display_driver_.Update();
        has_updated_ = false;
        countdown_.Restart(change_duration_iota_);
    } else if (state == AppState::ClearDisplay) {
        image.clear();
        display_driver_.Update();
        has_updated_ = false;
        countdown_.Restart(change_duration_iota_);
    } else if (state == AppState::Error) {
        jarnax::print("DisplayTest::OnEntry: Error state, halting!\r\n");
        countdown_.Restart(change_duration_iota_);
    }
}

AppState DisplayTest::OnCycle(AppState state) {
    // Status is a more lasting condition over IsUpdated which is more of a "pulse"
    auto status = display_driver_.GetStatus();
    if (state != AppState::Waiting and state != AppState::Error and not status.IsSuccess() and not status.IsBusy()) {
        jarnax::print("DisplayTest::OnCycle: Error detected in state %u, transitioning to Error state\r\n", static_cast<std::uint8_t>(state));
        return AppState::Error;
    }
    // Indicates the Update has finished.
    auto updated = display_driver_.IsUpdated();
    if (updated) {
        // convert the flag to a longer lasting condition to make it easier to manage in the state machine.
        has_updated_ = true;
    }
    if (state == AppState::Waiting) {
        if (status.IsSuccess()) {
            state = AppState::Pattern1;
        }
    } else if (state == AppState::Pattern1) {
        if (countdown_.IsExpired() and status.IsSuccess() and has_updated_) {
            state = AppState::Pattern2;
        }
    } else if (state == AppState::Pattern2) {
        if (countdown_.IsExpired() and status.IsSuccess() and has_updated_) {
            state = AppState::Pattern3;
        }
    } else if (state == AppState::Pattern3) {
        if (countdown_.IsExpired() and status.IsSuccess() and has_updated_) {
            state = AppState::Pattern4;
        }
    } else if (state == AppState::Pattern4) {
        if (countdown_.IsExpired() and status.IsSuccess() and has_updated_) {
            state = AppState::Pattern5;
        }
    } else if (state == AppState::Pattern5) {
        if (countdown_.IsExpired() and status.IsSuccess() and has_updated_) {
            state = AppState::Pattern6;
        }
    } else if (state == AppState::Pattern6) {
        if (countdown_.IsExpired() and status.IsSuccess() and has_updated_) {
            state = AppState::ClearDisplay;
        }
    } else if (state == AppState::ClearDisplay) {
        if (countdown_.IsExpired() and status.IsSuccess() and has_updated_) {
            state = AppState::Pattern1;
        }
    } else if (state == AppState::Error) {
        if (countdown_.IsExpired()) {
            state = AppState::ClearDisplay;
        }
    }
    return state;
}

void DisplayTest::OnExit(AppState state) {
    jarnax::print("DisplayTest::OnExit: %u\r\n", static_cast<std::uint8_t>(state));
    if (state == AppState::Waiting) {
        jarnax::print("Display powered on and ready\r\n");
    } else if (state == AppState::Pattern1) {
    } else if (state == AppState::Pattern2) {
    } else if (state == AppState::Pattern3) {
    } else if (state == AppState::Pattern4) {
    } else if (state == AppState::Pattern5) {
    } else if (state == AppState::Pattern6) {
    } else if (state == AppState::ClearDisplay) {
    } else if (state == AppState::Error) {
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

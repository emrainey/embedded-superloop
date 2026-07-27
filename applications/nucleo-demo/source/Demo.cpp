#include "Demo.hpp"
#include "BoardContext.hpp"
#include "board.hpp"
#include "core/Conversions.hpp"
#include "jarnax/Assertion.hpp"
#include "memory.h"

using namespace core::units;

Demo::Demo(jarnax::Ticker& ticker, jarnax::BoardContext& board_context, jarnax::net::Interface& network_interface)
    : ticker_{ticker}
    , timer_{board_context.GetTimer()}
    , usart_driver_{board_context.GetUsartB()}
    , rng_{board_context.GetRandomNumberGenerator()}
    , ethernet_driver_{board_context.GetEthernet()}
    , error_indicator_{board_context.GetErrorIndicator()}
    , user_button_{board_context.GetUserButton()}
    , network_interface_{network_interface}
    , countdown_{timer_, core::units::Iota{250'000U}}
    , state_chart_{*this}
    , inputs_{Inputs::None}
    , button_was_pressed_{false} {}

bool Demo::Execute() {
    if (state_chart_.IsFinal()) {
        state_chart_.Enter();
    }
    if (not button_was_pressed_ and user_button_.IsPressed()) {
        inputs_ = Inputs::UserButtonPressed;
        button_was_pressed_ = true;
        jarnax::print("User Button Pressed\r\n");
    } else if (button_was_pressed_ and not user_button_.IsPressed()) {
        inputs_ = Inputs::UserButtonReleased;
        button_was_pressed_ = false;
        jarnax::print("User Button Released\r\n");
    }

    outputs_ = Outputs::None;
    state_chart_.RunOnce();
    inputs_ = Inputs::None;

    if (outputs_ == Outputs::ErrorIndicatorActive) {
        error_indicator_.Active();
    } else if (outputs_ == Outputs::ErrorIndicatorInactive) {
        error_indicator_.Inactive();
    }

    return true;
}

void Demo::OnEnter() {
    jarnax::print("Demo::OnEnter\r\n");
    network_interface_.PrintConfiguration(core::GetPrinter());
}

void Demo::OnEntry(DemoState state) {
    jarnax::print("Demo::OnEntry: %u\r\n", static_cast<std::uint8_t>(state));
    if (state == DemoState::StartUp) {
        auto hello = core::SpanFrom("Hello World\r\n");
        usart_driver_.Enqueue(hello);
    } else if (state == DemoState::Idle) {
        outputs_ = Outputs::ErrorIndicatorInactive;
        // when entering the Idle state, set the timer to go off 2 seconds later
        countdown_.Restart(core::units::ConvertToIota(2'000'000_usec));
    } else if (state == DemoState::Error) {
        outputs_ = Outputs::ErrorIndicatorActive;
    }
}

void Demo::OnCycle(DemoState state) {
    if (state == DemoState::StartUp) {
        // do nothing
    } else if (state == DemoState::Idle) {
        if (countdown_.IsExpired()) {
            jarnax::Ticks ticks = ticker_.GetTicksSinceBoot();
            jarnax::Time time = ticker_.GetTimeSinceBoot();
            uint32_t random = rng_.GetNextRandom();
            std::uint32_t iotas = static_cast<std::uint32_t>(timer_.GetIotas().value());
            jarnax::print(
                "Demo::Execute: %" PRIu32 " ticks, %lf sec, %" PRIx32 " Iotas: %" PRIu32 "\r\n",
                ticks.value(),
                static_cast<double>(time.value()),
                random,
                iotas
            );
            countdown_.Reset();
        }
    } else if (state == DemoState::Error) {
        // do nothing, the error indicator is already active
    }
}

Demo::Ordinal Demo::OnGuard(DemoState state) const {
    if (state == DemoState::StartUp) {
        if (ethernet_driver_.IsReady()) {
            return 1;    // Take transition 1
        }
    } else if (state == DemoState::Idle) {
        if (inputs_ == Inputs::UserButtonPressed) {
            return 1;    // Take transition 1 when the user button is pressed
        }
    } else if (state == DemoState::Next) {
        if (inputs_ == Inputs::UserButtonReleased) {
            return 1;    // Take transition 1 when the user button is released
        }
    }
    return 0;    // Return 0 to indicate the state should not be exited
}

void Demo::OnExit(DemoState state) {
    jarnax::print("Demo::OnExit: %u\r\n", static_cast<std::uint8_t>(state));
    if (state == DemoState::StartUp) {
    } else if (state == DemoState::Idle) {
    } else if (state == DemoState::Next) {
    } else if (state == DemoState::Error) {
    } else if (state == DemoState::Final) {
    }
}

DemoState Demo::OnTransition(DemoState from, Ordinal ordinal) {
    jarnax::print("Demo::OnTransition: %u Ordinal: %u\r\n", static_cast<std::uint8_t>(from), static_cast<std::uint8_t>(ordinal));
    if (from == DemoState::StartUp) {
        if (ordinal == 1) {
            return DemoState::Idle;    // Transition to the Idle state
        }
    } else if (from == DemoState::Idle) {
        if (ordinal == 1) {
            // Handle the transition from Idle state with ordinal 1
            return DemoState::Next;    // Transition to the Next state
        }
    } else if (from == DemoState::Next) {
        if (ordinal == 1) {
            // Handle the transition from Next state with ordinal 1
            return DemoState::Idle;    // Transition to the Idle state
        }
    } else if (from == DemoState::Error) {
        // always go back to idle
        return DemoState::Idle;    // Transition to the Idle state
    } else if (from == DemoState::Undefined) {
        // the default first state
        return DemoState::StartUp;    // Transition to the StartUp state
    }
    return from;                      // if nothing taken, return existing state
}

void Demo::OnExit() {
    jarnax::print("Demo::OnExit\r\n");
}

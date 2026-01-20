#include "UsartTest.hpp"
#include "board.hpp"
#include "jarnax/Assertion.hpp"
#include "memory.h"

using namespace core::units;
using Level = jarnax::console::Service::Level;

char const* const speech[] = {
    "====================================================\r\n",
    "Mechanic: Somebody set up us the bomb.\r\n",
    "Operator: Main screen turn on\r\n",
    "CATS: All your base are belong to us.\r\n",
    "CATS: You have no chance to survive make your time.\r\n",
    "Captain: Move 'ZIG'.\r\n",
    "Captain: For great justice.\r\n",
    "====================================================\r\n",
};

UsartTest::UsartTest()
    : ticker_{jarnax::GetTicker()}
    , timer_{jarnax::GetBoardContext().GetTimer()}
    , usart_driver_{jarnax::GetBoardContext().GetCameraUsart()}
    , rng_{jarnax::GetBoardContext().GetRandomNumberGenerator()}
    , console_{jarnax::GetBoardContext().GetConsole()}
    , countdown_time_msec_{1000U}
    , countdown_time_iotas_{core::units::ConvertToIota(countdown_time_msec_)}
    , countdown_{timer_, countdown_time_iotas_}
    , state_machine_{*this, AppState::Idle}
    , speech_index_{0U}
    , delivered_{false} {}

bool UsartTest::Execute() {
    if (state_machine_.IsFinal()) {
        state_machine_.Enter();
    }
    state_machine_.RunOnce();
    return true;
}

void UsartTest::OnEnter() {
    jarnax::print("UsartTest::OnEnter\r\n");
    jarnax::print(
        "Using %lu iotas (%lu milliseconds) for timeout\r\n",
        static_cast<unsigned long>(countdown_time_iotas_.value()),
        static_cast<unsigned long>(countdown_time_msec_.value())
    );
    delivered_ = false;
    console_.SetLevel(Level::Debug);
}

void UsartTest::OnEntry(AppState state) {
    // jarnax::print("UsartTest::OnEntry: %u\r\n", static_cast<std::uint8_t>(state));
    if (state == AppState::Idle) {
        delivered_ = false;
        idle_counter_ = 4U;
    } else if (state == AppState::Quote1) {
        delivered_ = false;
    } else if (state == AppState::Speech) {
        speech_index_ = 0U;
    } else if (state == AppState::Error) {
        delivered_ = false;
    } else if (state == AppState::Warning) {
        delivered_ = false;
    } else if (state == AppState::Info) {
        delivered_ = false;
    } else if (state == AppState::Debug) {
        delivered_ = false;
    }
}

AppState UsartTest::OnCycle(AppState state) {
    core::Status status;
    // jarnax::print("UsartTest::OnCycle: %u\r\n", static_cast<std::uint8_t>(state));
    if (state == AppState::Idle) {
        if (not delivered_) {
            char const* const literal = "Hello World!\r\n";
            auto span = core::SpanFrom(literal);
            status = usart_driver_.Enqueue(span);
            if (status.IsSuccess()) {
                delivered_ = true;
            }
        }
        if (idle_counter_ > 0U) {
            if (countdown_.IsExpired()) {
                static_cast<void>(usart_driver_.Enqueue(core::SpanFrom(".")));    // ignore return due to long delay
                idle_counter_--;
                countdown_.Reset();
            }
        } else {
            state = AppState::Quote1;
        }
    } else if (state == AppState::Quote1) {
        if (not delivered_) {
            char const* const literal =
                "I've seen things you people wouldn't believe.\r\nAll those moments will be lost in time,\r\nlike tears in the rain.\r\n";
            status = usart_driver_.Enqueue(core::SpanFrom(literal));
            if (status.IsSuccess()) {
                delivered_ = true;
            }
        }
        if (countdown_.IsExpired()) {
            auto num = rng_.GetNextRandom();
            jarnax::print("RNG = %" PRIu32 "\r\n", num);
            if ((num & 1) == 0) {
                state = AppState::Speech;
            } else {
                state = AppState::Error;
            }
        }
    } else if (state == AppState::Speech) {
        if (speech_index_ < dimof(speech)) {
            auto span = core::SpanFrom(speech[speech_index_]);
            status = usart_driver_.Enqueue(span);
            if (status.IsSuccess()) {
                speech_index_++;
            }
        } else {
            if (countdown_.IsExpired()) {
                state = AppState::Idle;
            }
        }
    } else if (state == AppState::Error) {
        if (not delivered_) {
            console_.Print(Level::Error, "Error, Will Rogers!\r\n");
            delivered_ = true;
        }
        if (countdown_.IsExpired()) {
            state = AppState::Warning;
        }
    } else if (state == AppState::Warning) {
        if (not delivered_) {
            console_.Print(Level::Warning, "Warning, Will Rogers!\r\n");
            delivered_ = true;
        }
        if (countdown_.IsExpired()) {
            state = AppState::Info;
        }
    } else if (state == AppState::Info) {
        if (not delivered_) {
            console_.Print(Level::Info, "Info, Will Rogers!\r\n");
            delivered_ = true;
        }
        if (countdown_.IsExpired()) {
            state = AppState::Debug;
        }
    } else if (state == AppState::Debug) {
        if (not delivered_) {
            console_.Print(Level::Debug, "Debug, Will Rogers!\r\n");
            delivered_ = true;
        }
        if (countdown_.IsExpired()) {
            state = AppState::Idle;
        }
    } else {
        jarnax::print("UsartTest: Unknown state %u\r\n", static_cast<std::uint8_t>(state));
    }
    return state;
}

void UsartTest::OnExit(AppState state) {
    // jarnax::print("UsartTest::OnExit: %u\r\n", static_cast<std::uint8_t>(state));
    if (state == AppState::Idle) {
        countdown_.Reset();
    } else if (state == AppState::Quote1) {
        countdown_.Reset();
    } else if (state == AppState::Speech) {
        countdown_.Reset();
    } else if (state == AppState::Error) {
        countdown_.Reset();
    } else if (state == AppState::Warning) {
        countdown_.Reset();
    } else if (state == AppState::Info) {
        countdown_.Reset();
    } else if (state == AppState::Debug) {
        countdown_.Reset();
    }
}

void UsartTest::OnTransition(AppState from, AppState to) {
    static_cast<void>(from);    // Suppress unused variable warning
    static_cast<void>(to);      // Suppress unused variable warning
    // jarnax::print("UsartTest::OnTransition: %u -> %u\r\n", static_cast<std::uint8_t>(from), static_cast<std::uint8_t>(to));
    // get the lateness of the last countdown
}

void UsartTest::OnExit() {
    // jarnax::print("UsartTest::OnExit\r\n");
}

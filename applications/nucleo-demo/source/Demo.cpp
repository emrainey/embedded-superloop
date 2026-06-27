#include "Demo.hpp"
#include "board.hpp"
#include "jarnax/Assertion.hpp"
#include "memory.h"

using namespace core::units;

Demo::Demo()
    : ticker_{jarnax::GetTicker()}
    , timer_{jarnax::GetBoardContext().GetTimer()}
    , usart_driver_{jarnax::GetBoardContext().GetUsartB()}
    , rng_{jarnax::GetBoardContext().GetRandomNumberGenerator()}
    , error_indicator_{jarnax::GetBoardContext().GetErrorIndicator()}
    , user_button_{jarnax::GetBoardContext().GetUserButton()}
    , copier_{jarnax::GetBoardContext().GetCopier()}    // , winbond_driver_{jarnax::GetBoardContext().GetWinbondDriver()}
    , countdown_{timer_, core::units::Iota{250'000U}}
    , buffer_one_{}
    , buffer_two_{}
    , state_machine_{*this, DemoState::StartUp} {}

void Demo::KeyLoop() {
    if (user_button_.IsPressed()) {
        jarnax::print("User Button Pressed\r\n");
    }
}

void Demo::CopierTest() {
    if (not buffer_test_) {
        memory::fill(buffer_one_, 0x5A, sizeof(buffer_one_));
        memory::fill(buffer_two_, 0x00, sizeof(buffer_two_));
        copier_.Copy(&buffer_one_[0], &buffer_two_[0], sizeof(buffer_one_));
        if (memory::compare(&buffer_one_[0], &buffer_two_[0], sizeof(buffer_one_)) == 0) {
            jarnax::print("PASSED: Buffers are the same\r\n");
        } else {
            jarnax::print("FAILED: Buffers are different\r\n");
        }
        buffer_test_ = true;
    }
}

bool Demo::Execute() {
    if (state_machine_.IsFinal()) {
        state_machine_.Enter();
    }
    state_machine_.RunOnce();
    return true;
}

void Demo::OnEnter() {
    jarnax::print("Demo::OnEnter\r\n");
}

void Demo::OnEntry(DemoState state) {
    jarnax::print("Demo::OnEntry: %u\r\n", static_cast<std::uint8_t>(state));
    if (state == DemoState::StartUp) {
        countdown_.Restart(1'000'000_iota);
        auto hello = core::SpanFrom("Hello World\r\n");
        usart_driver_.Enqueue(hello);
    } else if (state == DemoState::KeyLoop) {
        countdown_.Restart(2'000'000_iota);
    } else if (state == DemoState::CopierTest) {
    } else if (state == DemoState::Idle) {
        countdown_.Restart(500'000_iota);
    } else if (state == DemoState::Error) {
        error_indicator_.Active();
    }
}

DemoState Demo::OnCycle(DemoState state) {
    // jarnax::print("Demo::OnCycle: %u\r\n", static_cast<std::uint8_t>(state));
    if (state == DemoState::StartUp) {
        state = DemoState::KeyLoop;
    } else if (state == DemoState::KeyLoop) {
        KeyLoop();
        if (countdown_.IsExpired()) {
            state = DemoState::CopierTest;
        }
    } else if (state == DemoState::CopierTest) {
        CopierTest();
        state = DemoState::Idle;
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
    return state;
}

void Demo::OnExit(DemoState state) {
    jarnax::print("Demo::OnExit: %u\r\n", static_cast<std::uint8_t>(state));
    if (state == DemoState::StartUp) {
    } else if (state == DemoState::KeyLoop) {
    } else if (state == DemoState::CopierTest) {
    } else if (state == DemoState::Idle) {
    } else if (state == DemoState::Error) {
        error_indicator_.Inactive();
    }
}

void Demo::OnTransition(DemoState from, DemoState to) {
    jarnax::print("Demo::OnTransition: %u -> %u\r\n", static_cast<std::uint8_t>(from), static_cast<std::uint8_t>(to));
}

void Demo::OnExit() {
    jarnax::print("Demo::OnExit\r\n");
}

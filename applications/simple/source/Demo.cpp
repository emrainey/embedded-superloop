#include "memory.h"
#include "Demo.hpp"
#include "board.hpp"

using namespace core::units;

Demo::Demo()
    : ticker_{jarnax::GetTicker()}
    , timer_{jarnax::GetTimer()}
    , usart_driver_{jarnax::GetDriverContext().GetDebugDriver()}
    , rng_{jarnax::GetDriverContext().GetRandomNumberGenerator()}
    , error_indicator_{jarnax::GetDriverContext().GetErrorIndicator()}
    , status_indicator_{jarnax::GetDriverContext().GetStatusIndicator()}
    , wakeup_button_{jarnax::GetDriverContext().GetWakeupButton()}
    , key0_button_{jarnax::GetDriverContext().GetButton0()}
    , key1_button_{jarnax::GetDriverContext().GetButton1()}
    , copier_{jarnax::GetDriverContext().GetCopier()}
    , winbond_driver_{jarnax::GetDriverContext().GetWinbondDriver()}
    , countdown_{timer_, core::units::Iota{250'000U}}
    , buffer_one_{}
    , buffer_two_{}
    , state_machine_{*this, DemoState::StartUp} {
}

void Demo::KeyLoop() {
    if (wakeup_button_.IsPressed()) {
        jarnax::print("Wakeup Pressed\r\n");
    }
    if (key0_button_.IsPressed()) {
        jarnax::print("Key0 Pressed\r\n");
    }
    if (key1_button_.IsPressed()) {
        jarnax::print("Key1 Pressed\r\n");
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
        // winbond_driver_.PowerUp();
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
    jarnax::print("Demo::OnCycle: %u\r\n", static_cast<std::uint8_t>(state));
    if (state == DemoState::StartUp) {
        if (winbond_driver_.IsReady()) {
            state = DemoState::KeyLoop;
        }
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
            jarnax::print("Demo::Execute: %lu ticks, %lf sec, %lx Iotas: %lu\r\n", ticks.value(), time.value(), random, iotas);
            status_indicator_.Active();
            status_indicator_.Inactive();
            countdown_.Reset();
        }
    } else if (state == DemoState::Error) {
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

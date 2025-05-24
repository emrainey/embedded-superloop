#include "memory.h"
#include "Demo.hpp"
#include "board.hpp"
#include "jarnax/Assertion.hpp"

using namespace core::units;

Demo::Demo()
    : ticker_{jarnax::GetTicker()}
    , timer_{jarnax::GetTimer()}
    , usart_driver_{jarnax::GetDriverContext().GetDebugDriver()}
    , rng_{jarnax::GetDriverContext().GetRandomNumberGenerator()}
    , error_indicator_{jarnax::GetDriverContext().GetErrorIndicator()}
    , wakeup_button_{jarnax::GetDriverContext().GetWakeupButton()}
    , key0_button_{jarnax::GetDriverContext().GetButton0()}
    , key1_button_{jarnax::GetDriverContext().GetButton1()}
    , copier_{jarnax::GetDriverContext().GetCopier()}
    , winbond_driver_{jarnax::GetDriverContext().GetWinbondDriver()}
    , i2c_driver_{jarnax::GetDriverContext().GetI2cDriver()}
    , i2c_transaction_{timer_}
    , i2c_buffer_{stm32::i2c_dma_buffer_size, jarnax::GetDriverContext().GetDmaAllocator()}
    , i2c_countdown_{timer_, core::units::Iota{500'000U}}
    , countdown_{timer_, core::units::Iota{250'000U}}
    , buffer_one_{}
    , buffer_two_{}
    , state_machine_{*this, DemoState::StartUp} {
    assertion(not i2c_buffer_.IsEmpty());
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

void Demo::TestI2CWrite(void) {
    if (i2c_transaction_.IsUninitialized()) {
        jarnax::print("I2C Transaction is uninitialized\r\n");
        i2c_transaction_.address.small.read = 0U;
        i2c_transaction_.address.small.address = 0x3DU;    // SSD1306
        i2c_transaction_.send_size = sizeof(buffer_one_);
        i2c_transaction_.receive_size = 0U;
        i2c_transaction_.receive_offset = 0U;
        assertion(not i2c_buffer_.IsEmpty());
        i2c_transaction_.buffer = std::move(i2c_buffer_);
        // tell it that we've initialized the transaction, now it can be queued
        i2c_transaction_.Inform(jarnax::i2c::Transaction::Event::Initialized);
    }
    if (i2c_transaction_.IsInitialized()) {
        jarnax::print("I2C Transaction is initialized\r\n");
        core::Status status = i2c_driver_.Schedule(&i2c_transaction_);
        if (status.IsSuccess()) {
            jarnax::print("I2C Transaction scheduled successfully\r\n");
        } else {
            jarnax::print("I2C Transaction scheduling failed\r\n", status);
        }
    }
    if (i2c_transaction_.IsComplete()) {
        jarnax::print("I2C Transaction is complete\r\n");
        i2c_buffer_ = i2c_transaction_.Relinquish();
        if (i2c_buffer_.IsEmpty()) {
            jarnax::print("I2C Transaction buffer is empty\r\n");
            // TODO Add assert here!
        } else {
            jarnax::print("I2C Transaction buffer size: %zu received %u\r\n", i2c_buffer_.count(), i2c_transaction_.received_size);
            auto read_span = i2c_buffer_.as_span().subspan(i2c_transaction_.receive_offset, i2c_transaction_.receive_size);
            for (std::size_t i = 0; i < read_span.count(); i++) {
                jarnax::print("Buffer[%zu]: %02X\r\n", i, read_span[i]);
            }
        }
        // this will move it back to the Uninitialized state
        i2c_transaction_.Inform(jarnax::i2c::Transaction::Event::Recycle);
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
    jarnax::print("Demo::OnCycle: %u\r\n", static_cast<std::uint8_t>(state));
    if (state == DemoState::StartUp) {
        TestI2CWrite();
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

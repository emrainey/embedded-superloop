#include "memory.h"
#include "I2CTest.hpp"
#include "board.hpp"
#include "jarnax/Assertion.hpp"

using namespace core::units;

I2CTest::I2CTest()
    : ticker_{jarnax::GetTicker()}
    , timer_{jarnax::GetTimer()}
    , i2c_driver_{jarnax::GetBoardContext().GetI2cDriver()}
    , i2c_transaction_{timer_}
    , i2c_buffer_{stm32::i2c_dma_buffer_size, jarnax::GetBoardContext().GetDmaAllocator()}
    , i2c_countdown_{timer_, core::units::Iota{stm32::iota_per_millisecond * 100}}    // 100ms
    , state_machine_{*this, AppState::StartUp} {
    assertion(not i2c_buffer_.IsEmpty());
}

bool I2CTest::Execute() {
    if (state_machine_.IsFinal()) {
        state_machine_.Enter();
    }
    state_machine_.RunOnce();
    return true;
}

core::Status I2CTest::TransactionCycle(std::uint8_t command) {
    if (i2c_transaction_.IsUninitialized()) {
        stats_.uninitialized++;
        i2c_transaction_.address.small.read = 0U;
        i2c_transaction_.address.small.address = ::ssd1306::DefaultAddress;
        i2c_transaction_.desired_count = 1U;
        i2c_transaction_.actual_count = 0U;
        auto span = i2c_buffer_.as_span();
        span[0] = command;    // command to turn on the display
        assertion(not i2c_buffer_.IsEmpty());
        i2c_transaction_.buffer = std::move(i2c_buffer_);
        // tell it that we've initialized the transaction, now it can be queued
        i2c_transaction_.Inform(jarnax::i2c::Transaction::Event::Initialized);
    }
    if (i2c_transaction_.IsInitialized()) {
        stats_.initialized++;
        core::Status status = i2c_driver_.Schedule(&i2c_transaction_);
        if (status.IsSuccess()) {
            stats_.scheduled++;
        } else {
            stats_.failed++;
        }
    }
    if (i2c_transaction_.IsComplete()) {
        stats_.complete++;
        i2c_buffer_ = i2c_transaction_.Relinquish();
        assertion(not i2c_buffer_.IsEmpty());
        if (i2c_transaction_.address.small.read == 1) {
            jarnax::print(
                "I2C Transaction buffer size: %zu received desired: %u, actual %u\r\n",
                i2c_buffer_.capacity(),
                i2c_transaction_.desired_count,
                i2c_transaction_.actual_count
            );
            auto read_span = i2c_buffer_.as_span().subspan(0, i2c_transaction_.actual_count);
            for (std::size_t i = 0; i < read_span.count(); i++) {
                jarnax::print("Buffer[%zu]: %02X\r\n", i, read_span[i]);
            }
        } else {
            // jarnax::print("I2C Transaction buffer size: %zu wrote %u\r\n", i2c_buffer_.count(), i2c_transaction_.actual_count);
        }
        // this will move it back to the Uninitialized state
        core::Status status = i2c_transaction_.GetStatus();
        if (status.IsSuccess()) {
            stats_.succeeded++;
        } else {
            stats_.failed++;
        }
        i2c_transaction_.Inform(jarnax::i2c::Transaction::Event::Recycle);
        return status;
    }
    return core::Status{core::Result::Busy, core::Cause::State};
}

void I2CTest::OnEnter() {
    jarnax::print("I2CTest will cycle over powering on and off the display every 100ms\r\n");
}

void I2CTest::OnEntry(AppState state) {
    // jarnax::print("I2CTest::OnEntry: %u\r\n", static_cast<std::uint8_t>(state));
    if (state == AppState::StartUp) {
        //
    } else if (state == AppState::DisplayOn) {
        //
    } else if (state == AppState::Waiting) {
        //
    } else if (state == AppState::DisplayOff) {
        //
    } else if (state == AppState::Error) {
        //
    }
}

AppState I2CTest::OnCycle(AppState state) {
    // jarnax::print("I2CTest::OnCycle: %u\r\n", static_cast<std::uint8_t>(state));
    if (state == AppState::StartUp) {
        if (i2c_countdown_.IsExpired()) {
            state = AppState::DisplayOn;
        }
    } else if (state == AppState::DisplayOn) {
        if (TransactionCycle(ssd1306::Command::DisplayOn).IsSuccess()) {
            state = AppState::Waiting;
        }
    } else if (state == AppState::Waiting) {
        if (i2c_countdown_.IsExpired()) {
            state = AppState::DisplayOff;
        }
    } else if (state == AppState::DisplayOff) {
        if (TransactionCycle(ssd1306::Command::DisplayOff).IsSuccess()) {
            state = AppState::StartUp;
        }
    } else if (state == AppState::Error) {
        //
    }
    return state;
}

void I2CTest::OnExit(AppState state) {
    // jarnax::print("I2CTest::OnExit: %u\r\n", static_cast<std::uint8_t>(state));
    if (state == AppState::StartUp) {
        i2c_countdown_.Reset();
    } else if (state == AppState::DisplayOn) {
        //
    } else if (state == AppState::Waiting) {
        i2c_countdown_.Reset();
    } else if (state == AppState::DisplayOff) {
        //
    } else if (state == AppState::Error) {
        //
    }
}

void I2CTest::OnTransition(AppState from, AppState to) {
    static_cast<void>(from);
    static_cast<void>(to);
    jarnax::print("I2CTest::OnTransition: %u -> %u\r\n", static_cast<std::uint8_t>(from), static_cast<std::uint8_t>(to));
}

void I2CTest::OnExit() {
    // jarnax::print("I2CTest::OnExit\r\n");
}

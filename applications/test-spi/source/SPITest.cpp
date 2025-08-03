#include "SPITest.hpp"
#include "board.hpp"
#include "jarnax/Assertion.hpp"
#include "memory.h"

using namespace core::units;

SPITest::Statistics* app_statistics = nullptr;

SPITest::SPITest()
    : ticker_{jarnax::GetTicker()}
    , timer_{jarnax::GetTimer()}
    , spi_driver_{jarnax::GetBoardContext().GetSpi2Driver()}
    , spi_transaction_{timer_}
    , spi_buffer_{stm32::spi2_dma_buffer_size, jarnax::GetBoardContext().GetDmaAllocator()}
    , spi_countdown_{timer_, core::units::Iota{stm32::iota_per_millisecond * 1000}}    // 1000ms
    , state_machine_{*this, AppState::Identify} {
    assertion(not spi_buffer_.IsEmpty());
    app_statistics = &stats_;
}

bool SPITest::Execute() {
    if (state_machine_.IsFinal()) {
        state_machine_.Enter();
    }
    state_machine_.RunOnce();
    return true;
}

core::Status SPITest::TransactionCycle(std::uint8_t address, size_t count) {
    if (spi_transaction_.IsUninitialized()) {
        stats_.uninitialized++;
        size_t pad = 1U;
        spi_transaction_.polarity = jarnax::spi::ClockPolarity::IdleHigh;
        spi_transaction_.phase = jarnax::spi::ClockPhase::FirstAfterEdge;
        spi_transaction_.chip_select = nullptr;    // use the NSS from the hardware
        spi_transaction_.crc_polynomial = 0;
        spi_transaction_.use_data_as_bytes = true;
        spi_transaction_.sent_size = 0U;
        spi_transaction_.send_size = 1U + pad + count;
        spi_transaction_.receive_offset = spi_transaction_.send_size;
        spi_transaction_.received_size = 0U;
        spi_transaction_.receive_size = 1U + count + pad;
        auto span = spi_buffer_.as_span();
        memory::fill(span.data(), 0xFF, span.count());    // fill with 0xFF for now
        span[0] = address;                                // the address of the register to read from?
        assertion(not spi_buffer_.IsEmpty());
        spi_transaction_.buffer = std::move(spi_buffer_);
        // tell it that we've initialized the transaction, now it can be queued
        spi_transaction_.Inform(jarnax::spi::Transaction::Event::Initialized);
    }
    if (spi_transaction_.IsInitialized()) {
        stats_.initialized++;
        core::Status status = spi_driver_.Schedule(&spi_transaction_);
        if (status.IsSuccess()) {
            stats_.scheduled++;
        } else {
            stats_.failed++;
        }
    }
    if (spi_transaction_.IsComplete()) {
        stats_.complete++;
        spi_buffer_ = spi_transaction_.Relinquish();
        assertion(not spi_buffer_.IsEmpty());
        if (spi_transaction_.received_size > 0) {
            jarnax::print(
                "SPI Transaction buffer size: %zu send/t: %u/%u receive/d %u/%u\r\n",
                spi_buffer_.capacity(),
                spi_transaction_.send_size,
                spi_transaction_.sent_size,
                spi_transaction_.receive_size,
                spi_transaction_.received_size
            );
            auto read_span = spi_buffer_.as_span().subspan(0, spi_transaction_.sent_size + spi_transaction_.received_size);
            for (std::size_t i = 0; i < read_span.count(); i++) {
                jarnax::print("Buffer[%zu]: 0x%x\r\n", i, read_span[i]);
            }
        } else {
            // jarnax::print("spi Transaction buffer size: %zu wrote %u\r\n", spi_buffer_.count(), spi_transaction_.actual_count);
        }
        // this will move it back to the Uninitialized state
        core::Status status = spi_transaction_.GetStatus();
        if (status.IsSuccess()) {
            stats_.succeeded++;
        } else {
            stats_.failed++;
        }
        spi_transaction_.Inform(jarnax::spi::Transaction::Event::Recycle);
        return status;
    }
    return core::Status{core::Result::Busy, core::Cause::State};
}

void SPITest::OnEnter() {
    jarnax::print("SPITest will cycle over powering on and off the display every 100ms\r\n");
}

void SPITest::OnEntry(AppState state) {
    // jarnax::print("SPITest::OnEntry: %u\r\n", static_cast<std::uint8_t>(state));
    if (state == AppState::Identify) {
        //
    } else if (state == AppState::Waiting) {
        spi_countdown_.Reset();
    } else if (state == AppState::Error) {
        // nothing
    }
}

AppState SPITest::OnCycle(AppState state) {
    // jarnax::print("SPITest::OnCycle: %u\r\n", static_cast<std::uint8_t>(state));
    if (state == AppState::Identify) {
        if (TransactionCycle(0x0F | 0x80, 6U).IsSuccess()) {
            state = AppState::Waiting;
        }
    } else if (state == AppState::Waiting) {
        if (spi_countdown_.IsExpired()) {
            state = AppState::Identify;
        }
    } else if (state == AppState::Error) {
        //
    }
    return state;
}

void SPITest::OnExit(AppState state) {
    // jarnax::print("SPITest::OnExit: %u\r\n", static_cast<std::uint8_t>(state));
    if (state == AppState::Identify) {
        // nothing
    } else if (state == AppState::Waiting) {
        spi_countdown_.Reset();
    } else if (state == AppState::Error) {
        // nothing
    }
}

void SPITest::OnTransition(AppState from, AppState to) {
    static_cast<void>(from);
    static_cast<void>(to);
    jarnax::print("SPITest::OnTransition: %u -> %u\r\n", static_cast<std::uint8_t>(from), static_cast<std::uint8_t>(to));
}

void SPITest::OnExit() {
    // jarnax::print("SPITest::OnExit\r\n");
}

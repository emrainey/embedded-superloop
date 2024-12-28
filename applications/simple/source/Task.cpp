#include "memory.h"
#include "Task.hpp"
#include "board.hpp"

Task::Task()
    : ticker_{jarnax::GetTicker()}
    , timer_{jarnax::GetTimer()}
    , rng_{jarnax::GetDriverContext().GetRandomNumberGenerator()}
    , error_indicator_{jarnax::GetDriverContext().GetErrorIndicator()}
    , status_indicator_{jarnax::GetDriverContext().GetStatusIndicator()}
    , wakeup_button_{jarnax::GetDriverContext().GetWakeupButton()}
    , key0_button_{jarnax::GetDriverContext().GetButton0()}
    , key1_button_{jarnax::GetDriverContext().GetButton1()}
    , copier_{jarnax::GetDriverContext().GetCopier()}
    , countdown_{timer_, core::units::Iota{1000}}    // 1 ms
    , buffer_one_{}
    , buffer_two_{}
    , flash_cs_{jarnax::GetDriverContext().GetFlashChipSelect()}
    , spi_buffer_count_{(1U + 4U + 64U + 1U) / 2U}    // 1 byte command, 4 bytes stuffing, 64 bytes data, 1 byte dummy
    , spi_buffer_{}
    , spi_transaction_{timer_}
    , spi_driver_{jarnax::GetDriverContext().GetSpiDriver()} {
}

void Task::DelayForTicks(jarnax::Ticks ticks) {
    jarnax::Ticks start = ticker_.GetTicks();
    jarnax::Ticks now, diff;
    size_t outer_counter{0U};
    do {
        thumb::nop();
        outer_counter++;
        now = ticker_.GetTicks();
        diff = now - start;
    } while (diff < ticks);
    jarnax::print("Counted to %u\r\n", outer_counter);
}

void Task::ResetTransaction() {
    spi_transaction_.Reset();
    spi_transaction_.phase = jarnax::spi::ClockPhase::ImmediateEdge;
    spi_transaction_.polarity = jarnax::spi::ClockPolarity::IdleLow;
    spi_transaction_.use_hardware_crc = false;
    spi_transaction_.chip_select = &flash_cs_;
    if (spi_transaction_.buffer.IsEmpty()) {
        spi_transaction_.buffer = std::move(spi_buffer_);
    }
    if (not spi_transaction_.buffer.IsEmpty()) {
        auto spi_data = spi_transaction_.buffer.as_span<uint8_t>();
        spi_data.data()[0] = 0x4b;    // read UID
        spi_data.data()[1] = 0x00;    // stuffing
        spi_data.data()[2] = 0x00;    // stuffing
        spi_data.data()[3] = 0x00;    // stuffing
        spi_data.data()[4] = 0x00;    // stuffing
        auto read_span = spi_data.subspan(5, 64U);
        memory::fill(read_span.data(), 0, read_span.count());
        spi_transaction_.send_size = 5U;
        spi_transaction_.receive_size = 64U;
        spi_transaction_.use_data_as_bytes = true;
        spi_transaction_.Inform(jarnax::spi::Transaction::Event::Initialized);
    }
}

bool Task::Execute() {
    if ((GetLoopInfo().system_loop_count & 1) == 0) {
        // be able to trigger a NMI
        // jarnax::yield();
    }
    jarnax::Ticks ticks = ticker_.GetTicksSinceBoot();
    jarnax::Time time = ticker_.GetTimeSinceBoot();
    uint32_t random = rng_.GetNextRandom();
    std::uint32_t iotas = static_cast<std::uint32_t>(timer_.GetIotas().value());

    memory::fill(buffer_one_, 0x5A, sizeof(buffer_one_));
    memory::fill(buffer_two_, 0x00, sizeof(buffer_two_));
    copier_.Copy(&buffer_one_[0], &buffer_two_[0], sizeof(buffer_one_));
    if (memory::compare(&buffer_one_[0], &buffer_two_[0], sizeof(buffer_one_)) == 0) {
        jarnax::print("Buffers are the same\r\n");
    } else {
        jarnax::print("Buffers are different\r\n");
    }

    jarnax::print("Task::Execute: %lu ticks, %lf sec, 0x%lx Iotas: %lu\r\n", ticks.value(), time.value(), random, iotas);
    DelayForTicks(Ticks{64U});
    if (wakeup_button_.IsPressed()) {
        jarnax::print("Wakeup Pressed\r\n");
    }
    if (key0_button_.IsPressed()) {
        jarnax::print("Key0 Pressed\r\n");
        status_indicator_.Active();
    } else {
        status_indicator_.Inactive();
    }
    if (key1_button_.IsPressed()) {
        jarnax::print("Key1 Pressed\r\n");
        error_indicator_.Active();
    } else {
        error_indicator_.Inactive();
    }
    if (spi_transaction_.IsUninitialized()) {
        // allocates the buffer
        spi_buffer_ = core::Buffer<jarnax::spi::DataUnit>{spi_buffer_count_};
        if (spi_buffer_.IsEmpty()) {
            jarnax::print("SPI Buffer Allocation Failed\r\n");
        } else {
            jarnax::print("SPI Buffer Allocated\r\n");
        }
        auto span = spi_buffer_.as_span<uint8_t>();
        jarnax::print("SPI Buffer Span = %p:%u\r\n", span.data(), span.count());
        span = spi_transaction_.buffer.as_span<uint8_t>();
        jarnax::print("SPI Transaction Buffer Span = %p:%u\r\n", span.data(), span.count());
        ResetTransaction();
    } else if (spi_transaction_.IsInitialized()) {
        core::Status status = spi_driver_.Schedule(&spi_transaction_);
        if (status) {
            jarnax::print("SPI Transaction Scheduled\r\n");
        } else {
            jarnax::print("SPI Transaction Failed", status);
        }
    } else if (spi_transaction_.IsComplete()) {
        jarnax::print("SPI Transaction Complete\r\n");
        auto span = spi_buffer_.as_span<uint8_t>();
        jarnax::print("SPI Buffer Span = %p:%u\r\n", span.data(), span.count());
        span = spi_transaction_.buffer.as_span<uint8_t>();
        jarnax::print("SPI Transaction Buffer Span = %p:%u\r\n", span.data(), span.count());
        ResetTransaction();
    }
    return true;
}

#include "memory.h"
#include "Demo.hpp"
#include "board.hpp"

Demo::Demo()
    : ticker_{jarnax::GetTicker()}
    , timer_{jarnax::GetTimer()}
    , rng_{jarnax::GetDriverContext().GetRandomNumberGenerator()}
    , error_indicator_{jarnax::GetDriverContext().GetErrorIndicator()}
    , status_indicator_{jarnax::GetDriverContext().GetStatusIndicator()}
    , wakeup_button_{jarnax::GetDriverContext().GetWakeupButton()}
    , key0_button_{jarnax::GetDriverContext().GetButton0()}
    , key1_button_{jarnax::GetDriverContext().GetButton1()}
    , copier_{jarnax::GetDriverContext().GetCopier()}
    , countdown_{timer_, core::units::Iota{250'000U}}
    , buffer_one_{}
    , buffer_two_{}
    , flash_cs_{jarnax::GetDriverContext().GetFlashChipSelect()}
    , spi_buffer_count_{(32U) / sizeof(jarnax::spi::DataUnit)}
    , spi_buffer_{}
    , spi_transaction_{timer_}
    , spi_driver_{jarnax::GetDriverContext().GetSpiDriver()}
    , spi_countdown_{timer_, core::units::Iota{30U}} {
}

void Demo::DelayForTicks(jarnax::Ticks ticks) {
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

void Demo::InitializeTransaction() {
    // allocates the buffer
    spi_buffer_ = core::Buffer<jarnax::spi::DataUnit>{spi_buffer_count_, jarnax::GetDriverContext().GetDmaAllocator()};
    if (spi_buffer_.IsEmpty()) {
        jarnax::print("SPI Buffer Allocation Failed\r\n");
    } else {
        jarnax::print("SPI Buffer Allocated\r\n");
    }
    auto span = spi_buffer_.as_span<uint8_t>();
    jarnax::print("SPI Buffer Span = %p:%u\r\n", span.data(), span.count());

    spi_transaction_.phase = jarnax::spi::ClockPhase::ImmediateEdge;
    spi_transaction_.polarity = jarnax::spi::ClockPolarity::IdleLow;
    spi_transaction_.use_hardware_crc = false;
    spi_transaction_.chip_select = &flash_cs_;
    if (spi_transaction_.IsEmpty()) {
        spi_transaction_.Assign(std::move(spi_buffer_));
    }
    if (not spi_transaction_.IsEmpty()) {
        auto spi_data = spi_transaction_.buffer.as_span<uint8_t>();
        jarnax::print("SPI Transaction Buffer Span = %p:%u\r\n", spi_data.data(), spi_data.count());
        memory::fill(spi_data.data(), 0, spi_data.count());
        auto write_span = spi_data.subspan(0U, 8U);
        write_span.data()[0] = 0x9F;    // read JEDEC ID
        spi_transaction_.send_size = 1U;
        spi_transaction_.sent_size = 0U;
        spi_transaction_.receive_size = 3U;
        spi_transaction_.received_size = 0U;
        spi_transaction_.use_data_as_bytes = true;
        spi_transaction_.Inform(jarnax::spi::Transaction::Event::Initialized);
    }
}

void Demo::SpiLoop() {
    if (spi_transaction_.IsResetable()) {
        spi_transaction_.Reset();
    } else {
        if (spi_transaction_.IsUninitialized()) {
            InitializeTransaction();
        } else if (spi_transaction_.IsInitialized()) {
            core::Status status = spi_driver_.Schedule(&spi_transaction_);
            if (status) {
                jarnax::print("SPI Transaction Scheduled\r\n");
            } else {
                jarnax::print("SPI Transaction Failed", status);
            }
        } else if (spi_transaction_.IsQueued()) {
            jarnax::print(".");
        } else if (spi_transaction_.IsRunning()) {
            jarnax::print("!");
        } else if (spi_transaction_.IsComplete()) {
            jarnax::print("SPI Transaction Complete\r\n");
            spi_buffer_ = spi_transaction_.Relinquish();
            auto span = spi_buffer_.as_span<uint8_t>();
            // now we hold the buffer
            jarnax::print("SPI Transaction Buffer Span = %p:%u\r\n", span.data(), span.count());
            // print the UID (64 bytes, 8 blocks of 8 bytes is ok)
            auto read_span = spi_buffer_.as_span<uint8_t>().subspan(0U, 3U);
            jarnax::print("SPI Transaction Read Span = %p:%u\r\n", read_span.data(), read_span.count());
            jarnax::print("UID:\r\n");
            for (size_t i = 0U; i < read_span.count(); i++) {
                if ((i % 8U) == 0U and i != 0U) {
                    jarnax::print("\r\n");
                }
                jarnax::print("%hhx ", read_span.data()[i]);
            }
            jarnax::print("\r\n");
            // release the transaction (clears values, deallocates the buffer, etc)
            spi_transaction_.Release();
        }
    }
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
    if (countdown_.IsExpired()) {
        status_indicator_.Active();
        jarnax::Ticks ticks = ticker_.GetTicksSinceBoot();
        jarnax::Time time = ticker_.GetTimeSinceBoot();
        uint32_t random = rng_.GetNextRandom();
        std::uint32_t iotas = static_cast<std::uint32_t>(timer_.GetIotas().value());
        jarnax::print("Demo::Execute: %lu ticks, %lf sec, %lx Iotas: %lu\r\n", ticks.value(), time.value(), random, iotas);
        CopierTest();
        KeyLoop();
        status_indicator_.Inactive();
        error_indicator_.Active();
        DelayForTicks(Ticks{64U});
        error_indicator_.Inactive();
        countdown_.Reset();
    }
    if (spi_countdown_.IsExpired()) {
        SpiLoop();
        spi_countdown_.Reset();
    }
    return true;
}

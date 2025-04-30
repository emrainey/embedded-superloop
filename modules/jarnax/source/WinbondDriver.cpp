#include <memory.hpp>
#include <jarnax/winbond/Driver.hpp>
#include <winbond.hpp>

/// @file
/// The Winbond Flash Driver over SPI
/// @details This driver is used to communicate with the Winbond Flash memory over SPI.

namespace jarnax {
namespace winbond {

Driver::Driver(Timer& timer, spi::Driver& driver, gpio::Output& chip_select, core::Allocator& dma_allocator)
    : Loopable()
    , printer_{core::GetPrinter()}
    , timer_{timer}
    , driver_{driver}
    , chip_select_{chip_select}
    , dma_allocator_{dma_allocator}
    , buffer_size_{(16U + 512U) / sizeof(spi::DataUnit)}
    , transaction_{timer_}
    , buffer_{buffer_size_, dma_allocator}
    , startup_countdown_{timer_, core::units::Iota{30U}}    // 30 microseconds
{
}

Driver::~Driver() {
    buffer_.Release();
}

core::Status Driver::Initialize(void) {
    return Reinitialize();
}

core::Status Driver::Reinitialize(void) {
    // allocates the buffer and releases the old one if it's still there
    buffer_ = core::Buffer<jarnax::spi::DataUnit>{buffer_size_, dma_allocator_};
    if (buffer_.IsEmpty()) {
        printer_("SPI Buffer Allocation Failed\r\n");
        return core::Status{core::Result::NotEnough, core::Cause::Resource};
    } else {
        printer_("SPI Buffer Allocated\r\n");
    }
    transaction_.phase = jarnax::spi::ClockPhase::ImmediateEdge;
    transaction_.polarity = jarnax::spi::ClockPolarity::IdleLow;
    transaction_.use_hardware_crc = false;
    transaction_.chip_select = &chip_select_;
    if (transaction_.IsEmpty()) {
        transaction_.Assign(std::move(buffer_));
    }
    if (not transaction_.IsEmpty()) {
        auto data = transaction_.buffer.as_span<uint8_t>();
        printer_("SPI Transaction Buffer Span = %p:%u\r\n", data.data(), data.count());
        memory::fill(data.data(), 0, data.count());
        auto write_span = data.subspan(0U, 8U);
        write_span.data()[0] = 0x9F;    // read JEDEC ID
        transaction_.send_size = 1U;
        transaction_.sent_size = 0U;
        transaction_.receive_size = 3U;
        transaction_.received_size = 0U;
        transaction_.use_data_as_bytes = true;
        transaction_.Inform(jarnax::spi::Transaction::Event::Initialized);
    }
    return core::Status{core::Result::Success, core::Cause::Unknown};
}

bool Driver::Execute(void) {
    if (transaction_.IsResetable()) {
        transaction_.Reset();
    } else {
        if (transaction_.IsUninitialized()) {
            Reinitialize();
        } else if (transaction_.IsInitialized()) {
            core::Status status = driver_.Schedule(&transaction_);
            if (status) {
                printer_("SPI Transaction Scheduled\r\n");
            } else {
                printer_("SPI Transaction Failed", status);
            }
        } else if (transaction_.IsQueued()) {
            printer_(".");
        } else if (transaction_.IsRunning()) {
            printer_("!");
        } else if (transaction_.IsComplete()) {
            printer_("SPI Transaction Complete\r\n");
            buffer_ = transaction_.Relinquish();
            // now we hold the buffer
            if (not buffer_.IsEmpty()) {
                // print the UID (64 bytes, 8 blocks of 8 bytes is ok)
                auto read_span = buffer_.as_span<uint8_t>().subspan(0U, 3U);
                printer_("SPI Transaction Read Span = %p:%u\r\n", read_span.data(), read_span.count());
                printer_("JEDEC ID:\r\n");
                for (size_t i = 0U; i < read_span.count(); i++) {
                    if ((i % 8U) == 0U and i != 0U) {
                        printer_("\r\n");
                    }
                    printer_("%hhx ", read_span.data()[i]);
                }
                printer_("\r\n");
            }
            // hand it back
            transaction_.buffer = std::move(buffer_);
            // release the transaction (clears values, deallocates the buffer if it had it, etc)
            transaction_.Release();
        }
    }
    return true;
}

}    // namespace winbond
}    // namespace jarnax
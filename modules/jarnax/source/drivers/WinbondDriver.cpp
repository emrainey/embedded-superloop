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
    , state_machine_{*this, *this} {
}

Driver::~Driver() {
    buffer_.Release();
}

core::Status Driver::Initialize(void) {
    state_machine_.Initialize();
    state_machine_.Process(winbond::Event::None);
    return Reinitialize(winbond::Instruction::None);
}

core::Status Driver::Reinitialize(winbond::Instruction instruction) {
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
        write_span.data()[0] = to_underlying(instruction);
        // TODO, look up the value
        transaction_.send_size = 1U;    // 1 byte for the instruction
        transaction_.sent_size = 0U;
        // TODO look up the value
        transaction_.receive_size = 0U;    // 0 bytes for the instruction
        transaction_.received_size = 0U;
        transaction_.use_data_as_bytes = true;
        transaction_.Inform(jarnax::spi::Transaction::Event::Initialized);
    }
    return core::Status{core::Result::Success, core::Cause::Unknown};
}

bool Driver::Execute(void) {
    if (startup_countdown_.IsExpired()) {
        // TODO, check if the chip is powered on
        // TODO, check if the chip is present
        state_machine_.Process(winbond::Event::PowerOn);
        // startup_countdown_.Reset();
    }
    return true;
}

core::Status Driver::Command(winbond::Instruction instruction) {
    core::Status status;
    if (transaction_.IsResetable()) {
        transaction_.Reset();
    } else {
        status = core::Status{core::Result::NotReady, core::Cause::State};
    }
    if (transaction_.IsUninitialized()) {
        Reinitialize(instruction);
    } else {
        status = core::Status{core::Result::NotAvailable, core::Cause::State};
    }
    if (transaction_.IsInitialized()) {
        status = driver_.Schedule(&transaction_);
        if (status.IsSuccess()) {
            printer_("SPI Transaction Scheduled\r\n");
        } else {
            printer_("SPI Transaction Failed", status);
        }
    } else {
        status = core::Status{core::Result::NotInitialized, core::Cause::State};
    }
    return status;
}

bool Driver::IsComplete(void) const {
    if (transaction_.IsComplete()) {
        return true;
    }
    return false;
}

core::Status Driver::GetStatus(void) const {
    return transaction_.GetStatus();
}

void Driver::OnEvent(Event event, core::Status status) {
    if (event == Event::Entered) {
        printer_("OnEvent Entered\r\n");
    } else if (event == Event::Exited) {
        printer_("OnEvent Exited\r\n");
    } else if (event == Event::PowerOn) {
        printer_("OnEvent PowerOn\r\n");
    } else if (event == Event::PowerOff) {
        printer_("OnEvent PowerOff\r\n");
    } else if (event == Event::Faulted) {
        printer_("OnEvent Faulted\r\n");
    }
    printer_("OnEvent", status);
}

// printer_("SPI Transaction Complete\r\n");
// buffer_ = transaction_.Relinquish();
// // now we hold the buffer
// if (not buffer_.IsEmpty()) {
//     // print the UID (64 bytes, 8 blocks of 8 bytes is ok)
//     auto read_span = buffer_.as_span<uint8_t>().subspan(0U, 3U);
//     printer_("SPI Transaction Read Span = %p:%u\r\n", read_span.data(), read_span.count());
//     printer_("JEDEC ID:\r\n");
//     for (size_t i = 0U; i < read_span.count(); i++) {
//         if ((i % 8U) == 0U and i != 0U) {
//             printer_("\r\n");
//         }
//         printer_("%hhx ", read_span.data()[i]);
//     }
//     printer_("\r\n");
// }
// // hand it back
// transaction_.buffer = std::move(buffer_);
// // release the transaction (clears values, deallocates the buffer if it had it, etc)
// transaction_.Release();

}    // namespace winbond
}    // namespace jarnax
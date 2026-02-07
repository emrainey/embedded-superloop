#include "jarnax/drivers/lps35hw/Driver.hpp"
#include "jarnax/print.hpp"
#include "memory.hpp"

namespace jarnax {
namespace drivers {
namespace lps35hw {

constexpr static bool debug{false};    ///< Debug flag for the LPS35HW driver

Driver::Driver(jarnax::Timer const& timer, core::units::Iota duration, jarnax::spi::Driver& spi, core::Allocator& allocator)
    : spi_(spi)
    , buffer_{::lps35hw::LargestTransactionSize, allocator}
    , transaction_{timer}
    , last_pressure_{::lps35hw::MinimumPressure}
    , last_temperature_{::lps35hw::MinimumTemperature}
    , state_machine_{timer, duration, *this} {}

core::Status Driver::Initialize() {
    if (buffer_.IsEmpty()) {
        return core::Status{core::Result::NotEnough, core::Cause::Resource};
    }
    event_ = lps35hw::Event::Initialize;    // Set the event to initialize the state machine
    return core::Status{};
}

core::units::Pressure Driver::GetLastPressure() {
    // Return the last pressure reading
    return last_pressure_;
}

core::units::Temperature Driver::GetLastTemperature() {
    // Return the last temperature reading
    return last_temperature_;
}

core::Status Driver::StartRegisterRead(uint8_t address, uint8_t count) {
    if constexpr (debug) {
        jarnax::print("LPS35HW: StartRegisterRead: address=%x, count=%u\r\n", address, count);
    }
    core::Status status = InitializeTransaction(true, address, count, nullptr);
    if (status.IsSuccess()) {
        // Start the register read operation
        status = spi_.Schedule(&transaction_);
    }
    return status;
}

core::Status Driver::StartRegisterWrite(uint8_t address, uint8_t count, uint8_t value[]) {
    if constexpr (debug) {
        jarnax::print("LPS35HW: StartRegisterWrite: address=%x, count=%u\r\n", address, count);
    }
    core::Status status = InitializeTransaction(false, address, count, value);
    if (status.IsSuccess()) {
        // Start the register write operation
        status = spi_.Schedule(&transaction_);
    }
    return status;
}

core::Status Driver::GetRegisterValue(uint8_t address, uint8_t count, uint8_t value[]) {
    core::Status status;
    if (transaction_.IsComplete()) {
        buffer_ = transaction_.Relinquish();
        // the read section will start at the offset, but will have space for the address and some padding
        size_t preface = sizeof(address) + data_padding_;
        // the span to the buffer
        auto span = buffer_.as_span();
        if constexpr (debug) {
            jarnax::print("LPS35HW: GetRegisterValue: address=%x, count=%u, preface=%" PRIz "\r\n", address, count, preface);
            jarnax::print("SPI Data received: ", span);
        }
        // the address is in the first byte of the transmit side
        ::lps35hw::Address addr{span[0]};
        if (addr.bits.address == address) {
            if (addr.bits.read) {
                size_t offset = transaction_.receive_offset + preface;
                // copy the received data to the value array
                memory::copy(value, &span[offset], count);
            } else {
                // for write operations, we don't return any data
                memory::fill(value, 0xFF, count);    // fill with 0xFF or some other value
            }
            // leave as success
        } else {
            jarnax::print(
                "Address mismatch: expected %" PRIx8 ", but got %" PRIx8 "\r\n",
                static_cast<uint8_t>(address),             // defeat the automatic int promotion
                static_cast<uint8_t>(addr.bits.address)    // defeat the automatic int promotion
            );
            status = core::Status{core::Result::NotExpected, core::Cause::State};
        }
        transaction_.Inform(jarnax::spi::Transaction::Event::Recycle);
    } else {
        status = core::Status{core::Result::NotReady, core::Cause::State};
    }
    return status;
}

void Driver::OnError(core::Status status) {
    if (status.IsSuccess()) {
        // do nothing.
    } else if (status.GetResult() == core::Result::Busy) {
        // handle busy status?
    } else if (status.GetResult() == core::Result::Failure) {
        // something went wrong
        jarnax::print(__func__, status);
    } else {
        // something else went wrong
        jarnax::print(__func__, status);
    }
}

void Driver::OnReading(::lps35hw::RawPressure pressure, ::lps35hw::RawTemperature temperature) {
    last_pressure_ = ::lps35hw::Convert(pressure);
    last_temperature_ = ::lps35hw::Convert(temperature);
}

bool Driver::Execute() {
    if (state_machine_.IsFinal()) {
        state_machine_.Enter();
    }
    if (not state_machine_.IsFinal()) {
        state_machine_.Process(event_);
        event_ = lps35hw::Event::None;    // Reset the event after processing
    }
    return true;
}

core::Status Driver::InitializeTransaction(bool is_read, uint8_t address, uint8_t count, uint8_t data[]) {
    if (transaction_.IsUninitialized()) {
        auto span = buffer_.as_span();
        memory::fill(span.data(), 0xFF, span.count());
        ::lps35hw::Address addr{address};
        addr.bits.read = is_read ? 1 : 0;    // Set the read/write bit
        span[0] = addr.whole;                // Set the address in the first byte
        if (not is_read) {
            if (data == nullptr) {
                return core::Status{core::Result::NotEnough, core::Cause::Resource};
            }
            memory::copy(&span[1], data, count);
        }
        size_t len = sizeof(address) + data_padding_ + count;
        transaction_.chip_select = nullptr;    // use the NSS from the hardware
        transaction_.crc_polynomial = 0;
        transaction_.polarity = jarnax::spi::ClockPolarity::IdleHigh;
        transaction_.phase = jarnax::spi::ClockPhase::FirstAfterEdge;
        transaction_.use_data_as_bytes = true;
        transaction_.sent_size = 0U;
        transaction_.send_size = len;
        transaction_.receive_offset = transaction_.send_size;
        transaction_.received_size = 0U;
        transaction_.receive_size = len;
        /*
            ┌──────┌──────┌──────┌──────┐
        MOSI│addr  │0xFF  │0xFF  │0xFF  │
            └──────└──────└──────└──────┘
            ┌──────┌──────┌──────┌──────┐
        MISO│0xFF  │<val1>│<val2>│<val3>│
            └──────└──────└──────└──────┘
        */

        transaction_.buffer = std::move(buffer_);
        transaction_.Inform(jarnax::spi::Transaction::Event::Initialized);
        return core::Status{};
    }
    return core::Status{core::Result::NotReady, core::Cause::State};
}

}    // namespace lps35hw
}    // namespace drivers
}    // namespace jarnax

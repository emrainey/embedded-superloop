#include "jarnax/drivers/lsm9ds1/Driver.hpp"
#include "jarnax/print.hpp"
#include "lsm9ds1.hpp"
#include "memory.hpp"

namespace jarnax {
namespace drivers {
namespace lsm9ds1 {

constexpr static bool debug{false};    ///< Debug flag for the lsm9ds1 driver

Driver::Driver(
    jarnax::Timer const& timer, core::units::Iota duration, jarnax::spi::Driver& spi, core::Allocator& allocator, jarnax::gpio::Output* cs_ag,
    jarnax::gpio::Output* cs_mag
)
    : timer_{timer}
    , spi_(spi)
    , cs_ag_{cs_ag}
    , cs_mag_{cs_mag}
    , buffer_{::lsm9ds1::LargestTransactionSize, allocator}
    , transaction_{timer}
    , last_acceleration_{{::lsm9ds1::MinimumAcceleration, ::lsm9ds1::MinimumAcceleration, ::lsm9ds1::MinimumAcceleration}, {}}
    , last_gyroscope_{{0, 0, 0}, {}}
    , last_temperature_{{::lsm9ds1::MinimumTemperature}, {}}
    , last_flux_{{::lsm9ds1::MinimumMagneticField, ::lsm9ds1::MinimumMagneticField, ::lsm9ds1::MinimumMagneticField}, {}}
    , completion_handed_off_{false}
    , state_machine_{timer, duration, *this} {
    transaction_.SetCompletionListener(this);
}

core::Status Driver::Initialize() {
    if (buffer_.IsEmpty()) {
        return core::Status{core::Result::NotEnough, core::Cause::Resource};
    }
    event_ = lsm9ds1::Event::Initialize;    // Set the event to initialize the state machine
    return core::Status{};
}

jarnax::lsm9ds1::Tug Driver::GetLastAcceleration() {
    // Return the last acceleration reading
    return last_acceleration_;
}

jarnax::lsm9ds1::Twist Driver::GetLastGyroscope() {
    // Return the last gyroscope reading
    return last_gyroscope_;
}

jarnax::lsm9ds1::Temp Driver::GetLastTemperature() {
    // Return the last temperature reading
    return last_temperature_;
}

jarnax::lsm9ds1::Flux Driver::GetLastFlux() {
    // Return the last magnetic field reading
    return last_flux_;
}

core::Status Driver::StartRegisterRead(uint8_t address, uint8_t count) {
    if constexpr (debug) {
        jarnax::print("lsm9ds1: StartRegisterRead: address=%x, count=%u\r\n", address, count);
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
        jarnax::print("lsm9ds1: StartRegisterWrite: address=%x, count=%u\r\n", address, count);
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
        // Check if the coordinator still owns the transaction
        if (not completion_handed_off_ and spi_.IsOwned(&transaction_)) {
            // Coordinator still owns it, wait for the completion callback
            return core::Status{core::Result::NotReady, core::Cause::State};
        }

        buffer_ = transaction_.Relinquish();
        // the read section will start at the offset, but will have space for the address and some padding
        size_t preface = sizeof(address) + data_padding_;
        // the span to the buffer
        auto span = buffer_.as_span();
        if constexpr (debug) {
            jarnax::print("lsm9ds1: GetRegisterValue: address=%x, count=%u, preface=%" PRIz "\r\n", address, count, preface);
            jarnax::print("SPI Data received: ", span);
        }
        // the address is in the first byte of the transmit side
        ::lsm9ds1::Address addr{span[0]};
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

        // Now that we have ownership, recycle the transaction
        transaction_.Inform(jarnax::spi::Transaction::Event::Recycle);
        completion_handed_off_ = false;    // Reset the flag after recycling
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

void Driver::OnReadingAcceleration(::lsm9ds1::acceleration::Raw x, ::lsm9ds1::acceleration::Raw y, ::lsm9ds1::acceleration::Raw z) {
    last_acceleration_.timestamp = timer_.GetMicroseconds();
    last_acceleration_.data.x = ::lsm9ds1::acceleration::Convert(x, ::lsm9ds1::acceleration::Sensitivity(8));
    last_acceleration_.data.y = ::lsm9ds1::acceleration::Convert(y, ::lsm9ds1::acceleration::Sensitivity(8));
    last_acceleration_.data.z = ::lsm9ds1::acceleration::Convert(z, ::lsm9ds1::acceleration::Sensitivity(8));
}

void Driver::OnReadingGyroscope(::lsm9ds1::gyroscope::Raw x, ::lsm9ds1::gyroscope::Raw y, ::lsm9ds1::gyroscope::Raw z) {
    last_gyroscope_.timestamp = timer_.GetMicroseconds();
    last_gyroscope_.data.x = ::lsm9ds1::gyroscope::Convert(x, ::lsm9ds1::gyroscope::Sensitivity(245));
    last_gyroscope_.data.y = ::lsm9ds1::gyroscope::Convert(y, ::lsm9ds1::gyroscope::Sensitivity(245));
    last_gyroscope_.data.z = ::lsm9ds1::gyroscope::Convert(z, ::lsm9ds1::gyroscope::Sensitivity(245));
}

void Driver::OnReadingTemperature(::lsm9ds1::temperature::Raw temperature) {
    last_temperature_.timestamp = timer_.GetMicroseconds();
    last_temperature_.data = ::lsm9ds1::temperature::Convert(temperature);
}

void Driver::OnReadingFlux(::lsm9ds1::magnetic_field::Raw x, ::lsm9ds1::magnetic_field::Raw y, ::lsm9ds1::magnetic_field::Raw z) {
    last_flux_.timestamp = timer_.GetMicroseconds();
    last_flux_.data.x = ::lsm9ds1::magnetic_field::Convert(x, ::lsm9ds1::magnetic_field::Sensitivity(4));
    last_flux_.data.y = ::lsm9ds1::magnetic_field::Convert(y, ::lsm9ds1::magnetic_field::Sensitivity(4));
    last_flux_.data.z = ::lsm9ds1::magnetic_field::Convert(z, ::lsm9ds1::magnetic_field::Sensitivity(4));
}

bool Driver::Execute() {
    if (state_machine_.IsFinal()) {
        state_machine_.Enter();
    }
    if (not state_machine_.IsFinal()) {
        state_machine_.Process(event_);
        event_ = lsm9ds1::Event::None;    // Reset the event after processing
    }
    return true;
}

void Driver::OnTransactionCompleted(jarnax::spi::Transaction& transaction) {
    if (&transaction == &transaction_) {
        completion_handed_off_ = true;
    }
}

core::Status Driver::InitializeTransaction(bool is_read, uint8_t address, uint8_t count, uint8_t data[]) {
    if (transaction_.IsUninitialized()) {
        auto span = buffer_.as_span();
        memory::fill(span.data(), 0xFFU, span.count());
        ::lsm9ds1::Address addr{address};
        addr.bits.read = is_read ? 1 : 0;    // Set the read/write bit
        span[0] = addr.whole;                // Set the address in the first byte
        if (not is_read) {
            if (data == nullptr) {
                return core::Status{core::Result::NotEnough, core::Cause::Resource};
            }
            memory::copy(&span[1], data, count);
        }
        size_t len = sizeof(address) + data_padding_ + count;
        transaction_.chip_select = cs_ag_;
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
        where addr is R/W + 7 bit addr
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

}    // namespace lsm9ds1
}    // namespace drivers
}    // namespace jarnax

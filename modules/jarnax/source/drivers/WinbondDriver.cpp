#include <memory.hpp>
#include <jarnax/winbond/Driver.hpp>
#include <w25q16bv.hpp>

/// @file
/// The Winbond Flash Driver over SPI
/// @details This driver is used to communicate with the Winbond Flash memory over SPI.

namespace jarnax {
namespace winbond {

/// This is a no-op function to be used as a callback for instruction that do not
/// require additional data to be written to the buffer.
class Empty : public Functor {
public:
    void operator()(core::Span<uint8_t>&) override {
        // do nothing
    }
};

class Addresser : public Functor {
public:
    Addresser(w25q16bv::Address& address)
        : address_{address} {}
    void operator()(core::Span<uint8_t>& data) override {
        // instruction goes into data[0U]
        data[1U] = address_.address[0U];
        data[2U] = address_.address[1U];
        data[3U] = address_.address[2U];
    }

protected:
    w25q16bv::Address address_;
};

class Reseter : public Functor {
public:
    void operator()(core::Span<uint8_t>& data) override {
        // instruction goes into data[0U]
        data[1U] = to_underlying(::w25q16bv::Instruction::ResetDevice);
    }
};

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
    , state_machine_{*this, *this}
    , powered_{false}
    , last_instruction_{Instruction::None}
    , next_event_{Event::None} {
}

Driver::~Driver() {
    buffer_.Release();
}

core::Status Driver::Initialize(void) {
    state_machine_.Initialize();    // Enters the Detection state
    return core::Status{core::Result::Success, core::Cause::State};
}

void Driver::PowerUp(void) {
    if (not powered_) {
        next_event_ = Event::Reset;
    }
}

bool Driver::IsPowered(void) const {
    return powered_;
}

bool Driver::IsIdentified(void) const {
    return identified_;
}

bool Driver::IsReady(void) const {
    return powered_ and identified_;
}

void Driver::PowerDown(void) {
    if (powered_) {
        next_event_ = Event::PowerOff;
    }
}

core::Status Driver::Reinitialize(Instruction instruction, size_t write_size, size_t read_size, Functor& functor) {
    // allocates the buffer and releases the old one if it's still there
    if (buffer_.IsEmpty()) {
        buffer_ = core::Buffer<jarnax::spi::DataUnit>{buffer_size_, dma_allocator_};
    }
    if (buffer_.IsEmpty()) {
        printer_("SPI Buffer Allocation Failed\r\n");
        return core::Status{core::Result::NotEnough, core::Cause::Resource};
    }
    transaction_.phase = jarnax::spi::ClockPhase::FirstAfterEdge;
    transaction_.polarity = jarnax::spi::ClockPolarity::IdleHigh;
    transaction_.use_hardware_crc = false;
    transaction_.chip_select = &chip_select_;
    if (transaction_.IsEmpty()) {
        transaction_.Assign(std::move(buffer_));
    }

    if (not transaction_.IsEmpty()) {
        auto data = transaction_.buffer.as_span<uint8_t>();
        printer_("SPI Transaction Buffer Span = %p:%u\r\n", data.data(), data.count());
        memory::fill(data.data(), 0, data.count());
        auto write_span = data.subspan(0U, write_size);
        write_span[0U] = static_cast<uint8_t>(instruction);
        last_instruction_ = instruction;
        functor(write_span);
        transaction_.send_size = write_size;
        transaction_.sent_size = 0U;
        transaction_.receive_offset = 16U;
        transaction_.receive_size = read_size;
        transaction_.received_size = 0U;
        transaction_.use_data_as_bytes = true;
        transaction_.Inform(jarnax::spi::Transaction::Event::Initialized);
    }
    return core::Status{core::Result::Success, core::Cause::Resource};
}

bool Driver::Execute(void) {
    // only allow processing the state machine if the startup timer is expired
    if (startup_countdown_.IsExpired()) {
        jarnax::print("%s Processing Event %d\r\n", __func__, to_underlying(next_event_));
        state_machine_.Process(next_event_);
        next_event_ = Event::None;
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
        Empty empty;
        // Addresser address{w25q16bv::Address{}};

        if (instruction == winbond::Instruction::EnableReset) {
            Reseter reseter;
            status = Reinitialize(instruction, 2U, 0U, reseter);
        } else if (instruction == winbond::Instruction::ReleasePowerDown) {
            status = Reinitialize(instruction, 4U, 0U, empty);
        } else if (instruction == winbond::Instruction::PowerDown) {
            status = Reinitialize(instruction, 3U, 0U, empty);
        } else if (instruction == winbond::Instruction::ReadUniqueId) {
            status = Reinitialize(instruction, 5U, 13U, empty);
        } else {
            status = core::Status{core::Result::NotAvailable, core::Cause::State};
        }
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

bool Driver::IsCommandComplete(void) const {
    return transaction_.IsComplete();
}

core::Status Driver::GetStatusAndData(void) {
    core::Status status = transaction_.GetStatus();
    if (status.IsSuccess()) {
        auto span = transaction_.buffer.as_span<uint8_t>();
        // get the sent instruction
        w25q16bv::Instruction instruction = last_instruction_;
        auto read_span = span.subspan(transaction_.receive_offset, transaction_.send_size + transaction_.receive_size);
        printer_("SPI Transaction Read Span = %p:%u\r\n", read_span.data(), read_span.count());
        jarnax::print(read_span);
        if (instruction == w25q16bv::Instruction::ReleasePowerDown) {
            uint8_t device_id = read_span[0U];
            printer_("Device ID = %hhx\r\n", device_id);
        } else if (instruction == w25q16bv::Instruction::GetJedecId) {
            printer_("JEDEC ID:\r\n");
            for (size_t i = 0U; i < read_span.count(); i++) {
                if ((i % 8U) == 0U and i != 0U) {
                    printer_("\r\n");
                }
                printer_("%hhx ", read_span.data()[i]);
            }
            printer_("\r\n");
        } else if (instruction == w25q16bv::Instruction::ReadUniqueId) {
            printer_("Unique ID:\r\n");
            for (size_t i = 0U; i < read_span.count(); i++) {
                if ((i % 8U) == 0U and i != 0U) {
                    printer_("\r\n");
                }
                printer_("%hhx ", read_span.data()[i]);
            }
            printer_("\r\n");
        } else if (instruction == w25q16bv::Instruction::PowerDown) {
            printer_("Power Down\r\n");
        } else if (instruction == w25q16bv::Instruction::EnableReset) {
            printer_("Enable Reset\r\n");
        } else if (instruction == w25q16bv::Instruction::ResetDevice) {
            printer_("Reset Device\r\n");
        } else {
            printer_("Instruction %hhx\r\n", to_underlying(instruction));
        }
        // we've gotten the data out of the transaction, so we can recycle it
        transaction_.Inform(jarnax::spi::Transaction::Event::Recycle, status);
    }
    return status;
}

bool Driver::IsPresent(void) const {
    // TODO find a way to use the board definitions to know if the build is using a board where it's present
    return true;
}

void Driver::OnEvent(Event event, core::Status status) {
    if (event == Event::PowerOn) {
        powered_ = true;
    } else if (event == Event::PowerOff) {
        identified_ = false;
        powered_ = false;
    } else if (event == Event::Faulted) {
        // nothing to do here
    } else if (event == Event::Identify) {
        identified_ = true;
        // TODO print ID numbers
    }
    printer_("OnEvent passed %x\r\n", to_underlying(event));
    printer_("OnEvent had status ", status);
}

}    // namespace winbond
}    // namespace jarnax
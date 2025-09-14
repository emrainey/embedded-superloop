#include "stm32/i2c/Driver.hpp"
#include "jarnax/print.hpp"
#include "stm32/configure.hpp"

namespace stm32 {
i2c::Driver* i2c_instances[3] = {nullptr, nullptr, nullptr};
i2c::Driver::Statistics* i2c_statistics[3] = {nullptr, nullptr, nullptr};

// Declare instances of the templates so that they have debugging symbols

void i2c1_event_isr(void) {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::InterIntegratedCircuit1_Event)]++;
    if (i2c_instances[0]) {
        i2c_instances[0]->HandleEvent();
    }
}

void i2c1_error_isr(void) {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::InterIntegratedCircuit1_Error)]++;
    if (i2c_instances[0]) {
        i2c_instances[0]->HandleError();
    }
}

void i2c2_event_isr(void) {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::InterIntegratedCircuit2_Event)]++;
    if (i2c_instances[1]) {
        i2c_instances[1]->HandleEvent();
    }
}

void i2c2_error_isr(void) {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::InterIntegratedCircuit2_Event)]++;
    if (i2c_instances[1]) {
        i2c_instances[1]->HandleError();
    }
}

void i2c3_event_isr(void) {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::InterIntegratedCircuit3_Event)]++;
    if (i2c_instances[2]) {
        i2c_instances[2]->HandleEvent();
    }
}

void i2c3_error_isr(void) {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::InterIntegratedCircuit3_Error)]++;
    if (i2c_instances[2]) {
        i2c_instances[2]->HandleEvent();
    }
}

namespace i2c {

Driver::Driver(
    stm32::peripherals::InterIntegratedCircuit volatile& i2c, jarnax::dma::Manager& dma_driver, Peripheral rx_peripheral, Peripheral tx_peripheral
)
    : jarnax::i2c::Driver{static_cast<jarnax::i2c::Transactor&>(*this)}
    , jarnax::i2c::Transactor{}
    , statistics_{}
    , i2c_{i2c}
    , dma_manager_{dma_driver}
    , rx_peripheral_{rx_peripheral}
    , rx_dma_resource_{nullptr}
    , tx_peripheral_{tx_peripheral}
    , tx_dma_resource_{nullptr}
    , transaction_{nullptr}
    , peripheral_frequency_{0_Hz} {
    if (&i2c == &peripherals::i2c1) {
        i2c_instances[0] = this;
        i2c_statistics[0] = &statistics_;
    } else if (&i2c == &peripherals::i2c2) {
        i2c_instances[1] = this;
        i2c_statistics[1] = &statistics_;
    } else if (&i2c == &peripherals::i2c3) {
        i2c_instances[2] = this;
        i2c_statistics[2] = &statistics_;
    }
}

core::Status Driver::Initialize(core::units::Hertz peripheral_frequency, core::units::Hertz desired_i2c_clock_frequency) {
    if constexpr (configure::use_i2c_as == configure::Mode::Dma) {
        jarnax::print("STM32 I2C Driver: Using DMA for I2C transactions.\r\n");
    } else {
        jarnax::print("STM32 I2C Driver: Using interrupts for I2C transactions.\r\n");
    }

    rx_dma_resource_ = dma_manager_.Assign(rx_peripheral_);
    if (rx_dma_resource_ == nullptr) {
        return core::Status{core::Result::InvalidValue, core::Cause::Configuration};
    }
    tx_dma_resource_ = dma_manager_.Assign(tx_peripheral_);
    if (tx_dma_resource_ == nullptr) {
        dma_manager_.Release(rx_dma_resource_);
        return core::Status{core::Result::InvalidValue, core::Cause::Configuration};
    }
    core::Status status{};
    peripheral_frequency_ = peripheral_frequency;
    // Initialize the DMA resources
    rx_dma_resource_->Initialize(rx_peripheral_);
    tx_dma_resource_->Initialize(tx_peripheral_);
    Reset();
    // Configure the I2C clock control register
    stm32::peripherals::InterIntegratedCircuit::ClockControl clock_control;
    clock_control = i2c_.clock_control;                                                                               // read
    clock_control.bits.clock_control = GetClockDivider(peripheral_frequency, desired_i2c_clock_frequency) & 0xFFF;    // mask to 12 bits
    clock_control.bits.duty = 0;                                                                                      // set to 0 for standard mode
    clock_control.bits.fast_standard_mode = 0;                                                                        // set to 0 for standard mode
    i2c_.clock_control = clock_control;                                                                               // write

    // Set the Freq in the I2C peripheral
    stm32::peripherals::InterIntegratedCircuit::Control2 control2;
    control2 = i2c_.control2;                                // read
    auto mhz = peripheral_frequency.value() / 1'000'000U;    // convert to MHz
    control2.bits.frequency = mhz & 0x3F;                    // mask to 6 bits (0-63)
    i2c_.control2 = control2;                                // write back

    // Enable the I2C peripheral
    stm32::peripherals::InterIntegratedCircuit::Control1 control1;
    control1 = i2c_.control1;                                // read
    control1.bits.peripheral_enable = 1;                     // enable the I2C peripheral
    control1.bits.system_management_bus = 0;                 // disable SMBus mode
    control1.bits.system_management_bus_type = 0;            // set to standard mode
    control1.bits.enable_address_resolution_protocol = 0;    // disable ARP
    control1.bits.enable_packet_error_code = 0;              // disable PEC
    control1.bits.enable_general_call = 0;                   // disable general call
    control1.bits.no_stretch = 0;                            // enable clock stretching
    control1.bits.start = 0;                                 // clear start condition
    control1.bits.stop = 0;                                  // clear stop condition
    control1.bits.acknowledge = 0;                           // disable acknowledge
    i2c_.control1 = control1;                                // write

    return core::Status{core::Result::Success, core::Cause::State};
}

uint32_t Driver::GetClockDivider(core::units::Hertz peripheral_frequency, core::units::Hertz desired_i2c_clock_frequency) {
    // Calculate the clock divider based on the peripheral frequency and desired I2C clock frequency
    std::uint32_t clock_divider = peripheral_frequency.value() / desired_i2c_clock_frequency.value();
    jarnax::print(
        "STM32 I2C Driver: Peripheral Frequency: %" PRIu32 " Hz, Desired I2C Clock Frequency: %" PRIu32 " Hz, Clock Divider: %" PRIu32 "\r\n",
        peripheral_frequency.value(),
        desired_i2c_clock_frequency.value(),
        clock_divider
    );
    return clock_divider;
}

void Driver::Reset(void) {
    // Reset the I2C peripheral
    stm32::peripherals::InterIntegratedCircuit::Control1 control1;
    control1 = i2c_.control1;            // read
    control1.bits.software_reset = 1;    // reset the I2C peripheral
    i2c_.control1 = control1;            // write
    control1 = i2c_.control1;            // read
    control1.bits.software_reset = 0;    // release the I2C peripheral
    i2c_.control1 = control1;            // write
}

void Driver::HandleEvent(void) {
    // Handle the event here
    stm32::peripherals::InterIntegratedCircuit::Status1 status1 = i2c_.status1;    // read
    if constexpr (debug::i2c_isr) {
        jarnax::print(
            "I2C Event Status1 st:%" PRIu32 " a:%" PRIu32 " rne:%" PRIu32 " te:%" PRIu32 " tf:%" PRIu32 "\n",
            static_cast<uint32_t>(status1.bits.start_bit),
            static_cast<uint32_t>(status1.bits.address),
            static_cast<uint32_t>(status1.bits.receive_not_empty),
            static_cast<uint32_t>(status1.bits.transmit_empty),
            static_cast<uint32_t>(status1.bits.byte_transfer_finished)
        );
    }
    if (status1.bits.start_bit) {
        statistics_.events.start++;    // Increment the start condition count
        // write the address out to the bus, this write will clear the START BIT
        if (transaction_ != nullptr and transaction_->address.small.is_large == 0U) {
            i2c_.data.bits.data = transaction_->address.parts[0];    // writes the R/W + the address
        } else {
            // TODO write out two ?
        }
    }
    if (status1.bits.address) {
        stm32::peripherals::InterIntegratedCircuit::Status2 status2;
        status2 = i2c_.status2;                // read, this clears the ADDRESS BIT
        statistics_.events.address_match++;    // Increment the address sent count
    }
    if (status1.bits.byte_transfer_finished) {
        statistics_.events.transfer_finished++;    // Increment the address received count
        if (transaction_) {
            core::Status status{core::Result::Success, core::Cause::State};
            // If there is a transaction, we can inform it of the error
            transaction_->Inform(jarnax::i2c::Transaction::Event::Completed, status);
            transaction_ = nullptr;    // Clear the transaction pointer
        }
    }
    if (status1.bits.system_management_bus_alert) {
        statistics_.events.smbus_alert++;    // Increment the SMBus alert count
    }
    if (status1.bits.receive_not_empty) {
        statistics_.bytes_received++;    // Increment the received byte count
        if (transaction_ != nullptr and transaction_->actual_count < transaction_->desired_count) {
            auto span = transaction_->buffer.as_span().subspan(0, transaction_->desired_count);
            span[transaction_->actual_count] = i2c_.data.bits.data;    // read the data from the I2C peripheral
            transaction_->actual_count++;                              // increment the actual count
        }
    }
    if (status1.bits.transmit_empty) {
        statistics_.transmit_empty++;    // Increment the transmitted byte count
        if (transaction_ != nullptr and transaction_->actual_count < transaction_->desired_count) {
            auto span = transaction_->buffer.as_span().subspan(0, transaction_->desired_count);
            i2c_.data.bits.data = span[transaction_->actual_count++];
        } else {
            // If we have sent all the data, we can set the stop condition
            stm32::peripherals::InterIntegratedCircuit::Control1 control1;
            control1 = i2c_.control1;    // read
            control1.bits.stop = 1;      // set stop condition
            i2c_.control1 = control1;    // write
        }
    }
}

void Driver::HandleError(void) {
    bool should_stop = false;    // Flag to indicate if we should stop the transaction
    core::Status status;
    stm32::peripherals::InterIntegratedCircuit::Status1 status1 = i2c_.status1;
    stm32::peripherals::InterIntegratedCircuit::Status2 status2 = i2c_.status2;
    if (status1.bits.bus_error) {
        statistics_.errors.bus++;    // Increment the bus error count
        should_stop = true;          // Set the flag to stop the transaction
    }
    if (status1.bits.arbitration_lost) {
        statistics_.errors.arbitration_lost++;    // Increment the arbitration lost count
    }
    if (status1.bits.acknowledge_failure) {
        statistics_.errors.acknowledge++;                                            // Increment the acknowledge failure count
        status1.bits.acknowledge_failure = 0;                                        // Clear the acknowledge failure bit
        i2c_.status1 = status1;                                                      // write back the status to clear the acknowledge failure bit
        status = core::Status{core::Result::NotAvailable, core::Cause::Hardware};    // set the status to not available
        should_stop = true;                                                          // Set the flag to stop the transaction
    }
    if (status1.bits.overrun) {
        statistics_.errors.overrun++;                                                // Increment the overrun error count
        status = core::Status{core::Result::NotAvailable, core::Cause::Hardware};    // set the status to not available
        should_stop = true;                                                          // Set the flag to stop the transaction
    }
    if (status1.bits.packet_error_code_error) {
        statistics_.errors.packet_error_code++;    // Increment the packet error code error count
        should_stop = true;                        // Set the flag to stop the transaction
    }
    if (status1.bits.timeout) {
        statistics_.errors.timeout++;                                           // Increment the timeout error count
        status = core::Status{core::Result::Timeout, core::Cause::Hardware};    // set the status to timeout
        should_stop = true;                                                     // Set the flag to stop the transaction
    }
    if (status2.bits.busy) {
        statistics_.errors.busy++;                                           // Increment the timeout error count
        status = core::Status{core::Result::Busy, core::Cause::Hardware};    // set the status to busy
        should_stop = true;                                                  // Set the flag to stop the transaction
    }
    if (should_stop) {
        // If we should stop the transaction, we can set the stop condition
        stm32::peripherals::InterIntegratedCircuit::Control1 control1;
        control1 = i2c_.control1;    // read
        control1.bits.stop = 1;      // set stop condition
        i2c_.control1 = control1;    // write
        if (transaction_) {
            // If there is a transaction, we can inform it of the error
            transaction_->Inform(jarnax::i2c::Transaction::Event::Completed, status);
            transaction_ = nullptr;    // Clear the transaction pointer
        }
    }
}

core::Status Driver::Verify(jarnax::i2c::Transaction& transaction) {
    // is the transaction buffer empty?
    if (not transaction.IsValid()) {
        return core::Status{core::Result::InvalidValue, core::Cause::Parameter};
    }
    return core::Status{core::Result::Success, core::Cause::Parameter};
}

core::Status Driver::Start(jarnax::i2c::Transaction& transaction) {
    // print the buffer count and the first bytes (up to the first 16 if possible)
    jarnax::print(
        "STM32 I2C Driver: Address: %" PRIx8 " Buffer capacity: %" PRIz " count: %" PRIz "\r\n",
        transaction.address.small.address,
        transaction.buffer.capacity(),
        transaction.desired_count
    );
    auto span = transaction.buffer.as_span().subspan(0, (transaction.desired_count <= 16 ? transaction.desired_count : 16U));
    for (size_t i = 0U; i < span.count(); i++) {
        auto byte = span[i];
        jarnax::print("%" PRIx8 " ", byte);    // print the first 16 bytes in hex format
    }
    jarnax::print("\r\n");

    if constexpr (configure::use_i2c_as == configure::Mode::Dma) {
        // enable the interrupts for the I2C peripheral
        stm32::peripherals::InterIntegratedCircuit::Control2 control2;
        control2 = i2c_.control2;                         // read
        control2.bits.error_interrupt_enable = 1;         // enable error interrupt
        control2.bits.event_interrupt_enable = 1;         // enable event interrupt
        control2.bits.direct_memory_access_enable = 1;    // enable DMA for the I2C peripheral
        i2c_.control2 = control2;                         // write
        span = transaction.buffer.as_span().subspan(0, transaction.desired_count);
        // If using DMA, we need to set up the DMA streams for the transaction
        if (transaction.address.small.read) {
            // Set up the RX DMA stream
            rx_dma_resource_->ConfigureCopyFromPeripheral(reinterpret_cast<std::uintptr_t>(&i2c_.data), span);
            rx_dma_resource_->Enable();    // start the RX DMA stream
        } else {
            // Set up the TX DMA stream
            tx_dma_resource_->ConfigureCopyToPeripheral(span, reinterpret_cast<std::uintptr_t>(&i2c_.data));
            tx_dma_resource_->Enable();    // start the TX DMA stream
        }
    } else {
        // enable the interrupts for the I2C peripheral
        stm32::peripherals::InterIntegratedCircuit::Control2 control2;
        control2 = i2c_.control2;                     // read
        control2.bits.error_interrupt_enable = 1;     // enable error interrupt
        control2.bits.event_interrupt_enable = 1;     // enable event interrupt
        control2.bits.buffer_interrupt_enable = 1;    // enable buffer interrupt
        i2c_.control2 = control2;                     // write
        // If not using DMA, we need to set up the I2C peripheral for the transaction
        // the interrupt will handle the transaction?
    }

    // memorize the transaction pointer to so that the interrupt can use it
    transaction_ = &transaction;

    stm32::peripherals::InterIntegratedCircuit::Control1 control1;
    control1 = i2c_.control1;    // read
    control1.bits.start = 1;     // set start condition
    i2c_.control1 = control1;    // write
    //=============================================================
    // The interrupt will likely fire here
    //=============================================================
    return core::Status{core::Result::Success, core::Cause::State};
}

core::Status Driver::Check(jarnax::i2c::Transaction& transaction) {
    if constexpr (configure::use_i2c_as == configure::Mode::Dma) {
        // @TODO check to see if the DMA is complete yet.
    } else {
        // compare the send vs send or received vs receive size
        if (transaction.desired_count > 0 and transaction.actual_count < transaction.desired_count) {
            // If we have not sent all the data, we need to continue sending
            return core::Status{core::Result::Busy, core::Cause::State};
        }
    }
    return core::Status{core::Result::Success, core::Cause::State};
}

core::Status Driver::Cancel(jarnax::i2c::Transaction& transaction) {
    (void)transaction;    // suppress unused parameter warning
    // disable the interrupts for the I2C peripheral
    stm32::peripherals::InterIntegratedCircuit::Control2 control2;
    control2 = i2c_.control2;                     // read
    control2.bits.error_interrupt_enable = 0;     // disable error interrupt
    control2.bits.event_interrupt_enable = 0;     // disable event interrupt
    control2.bits.buffer_interrupt_enable = 0;    // disable buffer interrupt
    i2c_.control2 = control2;                     // write
    // clear the start condition
    stm32::peripherals::InterIntegratedCircuit::Control1 control1;
    control1 = i2c_.control1;    // read
    control1.bits.start = 0;     // clear start condition
    control1.bits.stop = 1;      // set stop condition
    i2c_.control1 = control1;    // write
    Reset();
    return core::Status{core::Result::Success, core::Cause::State};
}
}    // namespace i2c
}    // namespace stm32

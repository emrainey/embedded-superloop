#include "board.hpp"
#include "jarnax/print.hpp"
#include "stm32/i2c/Driver.hpp"

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
Driver::Driver(stm32::registers::InterIntegratedCircuit volatile& i2c, dma::Driver& dma_driver, Peripheral rx_peripheral, Peripheral tx_peripheral)
    : jarnax::i2c::Driver{static_cast<jarnax::i2c::Transactor&>(*this)}
    , jarnax::i2c::Transactor{}
    , statistics_{}
    , i2c_{i2c}
    , dma_driver_{dma_driver}
    , rx_peripheral_{rx_peripheral}
    , rx_dma_stream_{*dma_driver_.Assign(rx_peripheral)}
    , rx_dma_stream_index_{dma::Driver::NumStreams}
    , tx_peripheral_{tx_peripheral}
    , tx_dma_stream_{*dma_driver_.Assign(tx_peripheral)}
    , tx_dma_stream_index_{dma::Driver::NumStreams}
    , transaction_{nullptr} {
    if (&i2c == &registers::i2c1) {
        i2c_instances[0] = this;
        i2c_statistics[0] = &statistics_;
    } else if (&i2c == &registers::i2c2) {
        i2c_instances[1] = this;
        i2c_statistics[1] = &statistics_;
    } else if (&i2c == &registers::i2c3) {
        i2c_instances[2] = this;
        i2c_statistics[2] = &statistics_;
    }
}

core::Status Driver::Initialize(core::units::Hertz peripheral_frequency, core::units::Hertz desired_i2c_clock_frequency) {
    rx_dma_stream_index_ = dma_driver_.GetStreamIndex(rx_dma_stream_);
    tx_dma_stream_index_ = dma_driver_.GetStreamIndex(tx_dma_stream_);
    if (rx_dma_stream_index_ == dma::Driver::NumStreams) {
        return core::Status{core::Result::NotAvailable, core::Cause::Resource};
    }
    if (tx_dma_stream_index_ == dma::Driver::NumStreams) {
        return core::Status{core::Result::NotAvailable, core::Cause::Resource};
    }
    dma_driver_.Initialize(rx_dma_stream_, rx_dma_stream_index_, rx_peripheral_);
    dma_driver_.Initialize(tx_dma_stream_, tx_dma_stream_index_, tx_peripheral_);

    Reset();
    // Configure the I2C clock control register
    stm32::registers::InterIntegratedCircuit::ClockControl clock_control;
    clock_control = i2c_.clock_control;                                                                               // read
    clock_control.bits.clock_control = GetClockDivider(peripheral_frequency, desired_i2c_clock_frequency) & 0xFFF;    // mask to 12 bits
    clock_control.bits.duty = 0;                                                                                      // set to 0 for standard mode
    clock_control.bits.fast_standard_mode = 0;                                                                        // set to 0 for standard mode
    i2c_.clock_control = clock_control;                                                                               // write

    // Set the Freq in the I2C peripheral
    stm32::registers::InterIntegratedCircuit::Control2 control2;
    control2 = i2c_.control2;                                // read
    auto mhz = peripheral_frequency.value() / 1'000'000U;    // convert to MHz
    control2.bits.frequency = mhz & 0x3F;                    // mask to 6 bits (0-63)
    i2c_.control2 = control2;                                // write back

    // Enable the I2C peripheral
    stm32::registers::InterIntegratedCircuit::Control1 control1;
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

    return core::Status{core::Result::Success, core::Cause::Hardware};
}

uint32_t Driver::GetClockDivider(core::units::Hertz peripheral_frequency, core::units::Hertz desired_i2c_clock_frequency) {
    // Calculate the clock divider based on the peripheral frequency and desired I2C clock frequency
    return (peripheral_frequency.value() / (desired_i2c_clock_frequency.value()));
}

void Driver::Reset(void) {
    // Reset the I2C peripheral
    stm32::registers::InterIntegratedCircuit::Control1 control1;
    control1 = i2c_.control1;            // read
    control1.bits.software_reset = 1;    // reset the I2C peripheral
    i2c_.control1 = control1;            // write
    control1 = i2c_.control1;            // read
    control1.bits.software_reset = 0;    // release the I2C peripheral
    i2c_.control1 = control1;            // write
}

void Driver::HandleEvent(void) {
    // Handle the event here
    stm32::registers::InterIntegratedCircuit::Status1 status1 = i2c_.status1;    // read
    if (status1.bits.start_bit) {
        statistics_.events.start++;    // Increment the start condition count
        // write the address out to the bus
        if (transaction_->address.small.is_large == 0U) {
            i2c_.data.bits.data = transaction_->address.parts[0];    // writes the R/W + the address
        } else {
            // TODO write out two ?
        }
    }
    if (status1.bits.address) {
        statistics_.events.address_match++;    // Increment the address sent count
    }
    if (status1.bits.byte_transfer_finished) {
        statistics_.events.transfer_finished++;    // Increment the address received count
        if (transaction_->actual_count == transaction_->desired_count) {
            // If we have sent all the data, we can set the stop condition
            stm32::registers::InterIntegratedCircuit::Control1 control1;
            control1 = i2c_.control1;    // read
            control1.bits.stop = 1;      // set stop condition
            i2c_.control1 = control1;    // write
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
        }
    }
}

void Driver::HandleError(void) {
    bool should_stop = false;    // Flag to indicate if we should stop the transaction
    core::Status status;
    stm32::registers::InterIntegratedCircuit::Status1 status1 = i2c_.status1;
    stm32::registers::InterIntegratedCircuit::Status2 status2 = i2c_.status2;
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
        statistics_.errors.overrun++;    // Increment the overrun error count
        should_stop = true;              // Set the flag to stop the transaction
    }
    if (status1.bits.packet_error_code_error) {
        statistics_.errors.packet_error_code++;    // Increment the packet error code error count
        should_stop = true;                        // Set the flag to stop the transaction
    }
    if (status1.bits.timeout) {
        statistics_.errors.timeout++;    // Increment the timeout error count
        should_stop = true;              // Set the flag to stop the transaction
    }
    if (status2.bits.busy) {
        statistics_.errors.busy++;    // Increment the timeout error count
        should_stop = true;           // Set the flag to stop the transaction
    }
    if (should_stop) {
        // If we should stop the transaction, we can set the stop condition
        stm32::registers::InterIntegratedCircuit::Control1 control1;
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

// @TODO Untested function for follower device.
// void Driver::ProgramAddress(jarnax::i2c::Address& address) {
//     bool is_10_bit_address = false;
//     if (address.small.is_large or address.large.is_large) {
//         is_10_bit_address = true;    // if the address is large, it is a 10-bit address
//     }
//     // Program the address for the transaction
//     stm32::registers::InterIntegratedCircuit::OurAddress1 our_address1;
//     our_address1 = i2c_.our_address1;    // read
//     if (is_10_bit_address) {
//         // If the address is a 10-bit address, we need to set the 10-bit address bits
//         our_address1.bits.addressing_mode = 1;                                // set the address mode to 10-bit
//         our_address1.bits.address0 = (address.large.address >> 0) & 0x1U;     // set the address bit 0
//         our_address1.bits.address7 = (address.large.address >> 1) & 0x7FU;    // set the address bits 1-7
//         our_address1.bits.address10 = (address.large.address >> 8) & 0x3U;    // set the address bits 8-9
//     } else {
//         // If the address is a 7-bit address, we need to set the 7-bit address bits
//         our_address1.bits.addressing_mode = 0;    // set the address size to small
//         our_address1.bits.address0 = 0;
//         our_address1.bits.address7 = address.small.address;    // set the 7-bit address (bits 0-6)
//         our_address1.bits.address10 = 0;
//     }
//     i2c_.our_address1 = our_address1;    // write
// }

core::Status Driver::Start(jarnax::i2c::Transaction& transaction) {
    if constexpr (use_dma_for_i2c) {
        // enable the interrupts for the I2C peripheral
        stm32::registers::InterIntegratedCircuit::Control2 control2;
        control2 = i2c_.control2;                         // read
        control2.bits.error_interrupt_enable = 1;         // enable error interrupt
        control2.bits.event_interrupt_enable = 1;         // enable event interrupt
        control2.bits.direct_memory_access_enable = 1;    // enable DMA for the I2C peripheral
        i2c_.control2 = control2;                         // write
        auto span = transaction.buffer.as_span().subspan(0, transaction.desired_count);
        // If using DMA, we need to set up the DMA streams for the transaction
        if (transaction.address.small.read) {
            // Set up the RX DMA stream
            dma_driver_.CopyFromPeripheral(rx_dma_stream_, span.data(), reinterpret_cast<uint32_t volatile*>(&i2c_.data), span.count());
            dma_driver_.Start(rx_dma_stream_);    // start the RX DMA stream
        } else {
            // Set up the TX DMA stream
            dma_driver_.CopyToPeripheral(tx_dma_stream_, reinterpret_cast<uint32_t volatile*>(&i2c_.data), span.data(), span.count());
            dma_driver_.Start(tx_dma_stream_);    // start the TX DMA stream
        }
    } else {
        // enable the interrupts for the I2C peripheral
        stm32::registers::InterIntegratedCircuit::Control2 control2;
        control2 = i2c_.control2;                     // read
        control2.bits.error_interrupt_enable = 1;     // enable error interrupt
        control2.bits.event_interrupt_enable = 1;     // enable event interrupt
        control2.bits.buffer_interrupt_enable = 1;    // enable buffer interrupt
        i2c_.control2 = control2;                     // write
        // If not using DMA, we need to set up the I2C peripheral for the transaction
        // the interrupt will handle the transaction?
    }

    stm32::registers::InterIntegratedCircuit::Control1 control1;
    control1 = i2c_.control1;    // read
    control1.bits.start = 1;     // set start condition
    i2c_.control1 = control1;    // write

    return core::Status{core::Result::Success, core::Cause::State};
}

core::Status Driver::Check(jarnax::i2c::Transaction& transaction) {
    if constexpr (use_dma_for_i2c) {
        // check to see if the DMA is complete yet.
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
    stm32::registers::InterIntegratedCircuit::Control2 control2;
    control2 = i2c_.control2;                     // read
    control2.bits.error_interrupt_enable = 0;     // disable error interrupt
    control2.bits.event_interrupt_enable = 0;     // disable event interrupt
    control2.bits.buffer_interrupt_enable = 0;    // disable buffer interrupt
    i2c_.control2 = control2;                     // write
    // clear the start condition
    stm32::registers::InterIntegratedCircuit::Control1 control1;
    control1 = i2c_.control1;    // read
    control1.bits.start = 0;     // clear start condition
    control1.bits.stop = 1;      // set stop condition
    i2c_.control1 = control1;    // write
    Reset();
    return core::Status{core::Result::Success, core::Cause::State};
}
}    // namespace i2c
}    // namespace stm32

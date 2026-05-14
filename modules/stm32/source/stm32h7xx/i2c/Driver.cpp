#include "stm32/i2c/Driver.hpp"
#include "cortex/vectors.hpp"
#include "jarnax/print.hpp"
#include "stm32/configure.hpp"

#include "stm32/chip.hpp"

namespace stm32 {
/// Array of pointers to active I2C driver instances (I2C1-3)
i2c::Driver* i2c_instances[3] = {nullptr, nullptr, nullptr};
/// Array of pointers to I2C driver statistics structures (I2C1-3)
i2c::Driver::Statistics* i2c_statistics[3] = {nullptr, nullptr, nullptr};

/// Interrupt service routine for I2C1 event events
void i2c1_event_isr(void) {
    cortex::extended_vector_statistics.count[polyfill::to_underlying(stm32::InterruptRequest::InterIntegratedCircuit1_Event)]++;
    if (i2c_instances[0]) {
        i2c_instances[0]->HandleEvent();
    }
}

/// Interrupt service routine for I2C1 error events
void i2c1_error_isr(void) {
    cortex::extended_vector_statistics.count[polyfill::to_underlying(stm32::InterruptRequest::InterIntegratedCircuit1_Error)]++;
    if (i2c_instances[0]) {
        i2c_instances[0]->HandleError();
    }
}

/// Interrupt service routine for I2C2 event events
void i2c2_event_isr(void) {
    cortex::extended_vector_statistics.count[polyfill::to_underlying(stm32::InterruptRequest::InterIntegratedCircuit2_Event)]++;
    if (i2c_instances[1]) {
        i2c_instances[1]->HandleEvent();
    }
}

/// Interrupt service routine for I2C2 error events
void i2c2_error_isr(void) {
    cortex::extended_vector_statistics.count[polyfill::to_underlying(stm32::InterruptRequest::InterIntegratedCircuit2_Error)]++;
    if (i2c_instances[1]) {
        i2c_instances[1]->HandleError();
    }
}

/// Interrupt service routine for I2C3 event events
void i2c3_event_isr(void) {
    cortex::extended_vector_statistics.count[polyfill::to_underlying(stm32::InterruptRequest::InterIntegratedCircuit3_Event)]++;
    if (i2c_instances[2]) {
        i2c_instances[2]->HandleEvent();
    }
}

/// Interrupt service routine for I2C3 error events
void i2c3_error_isr(void) {
    cortex::extended_vector_statistics.count[polyfill::to_underlying(stm32::InterruptRequest::InterIntegratedCircuit3_Error)]++;
    if (i2c_instances[2]) {
        i2c_instances[2]->HandleError();
    }
}

namespace i2c {

Driver::Driver(
    stm32::peripherals::InterIntegratedCircuit volatile& i2c, jarnax::dma::Manager& dma_manager, Peripheral rx_peripheral, Peripheral tx_peripheral
)
    : jarnax::i2c::Driver{static_cast<jarnax::i2c::Transactor&>(*this)}
    , jarnax::i2c::Transactor{}
    , statistics_{}
    , i2c_{i2c}
    , dma_manager_{dma_manager}
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

    // Configure H7 timing register using a simple divider split.
    auto const total_ticks_raw = GetClockDivider(peripheral_frequency, desired_i2c_clock_frequency);
    auto total_ticks = total_ticks_raw;
    std::uint32_t prescaler = 0U;
    while (total_ticks > 510U and prescaler < 15U) {
        prescaler++;
        total_ticks = total_ticks_raw / (prescaler + 1U);
    }
    if (total_ticks < 4U) {
        total_ticks = 4U;
    }
    auto const scl_low_period = ((total_ticks * 2U) / 3U);
    auto const scl_high_period = total_ticks - scl_low_period;

    stm32::peripherals::InterIntegratedCircuit::Timing timing{};
    timing.bits.prescaler = prescaler & 0x0FU;
    timing.bits.scl_low_period = (scl_low_period > 0U ? (scl_low_period - 1U) : 0U) & 0xFFU;
    timing.bits.scl_high_period = (scl_high_period > 0U ? (scl_high_period - 1U) : 0U) & 0xFFU;
    timing.bits.sda_fall_time = 2U;
    timing.bits.scl_rise_time = 2U;
    i2c_.timing = timing;

    // Enable the I2C peripheral
    stm32::peripherals::InterIntegratedCircuit::Control1 control1;
    control1 = i2c_.control1;               // read
    control1.bits.peripheral_enable = 1;    // enable the I2C peripheral
    control1.bits.smbus_host_address_enable = 0;
    control1.bits.smbus_default_address_enable = 0;
    control1.bits.alert_enable = 0;
    control1.bits.parity_error_check_enable = 0;
    control1.bits.general_call_enable = 0;
    control1.bits.no_stretch = 0;    // enable clock stretching
    i2c_.control1 = control1;        // write

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
    // Reset the I2C peripheral state by toggling PE and clearing ISR flags.
    stm32::peripherals::InterIntegratedCircuit::Control1 control1;
    control1 = i2c_.control1;
    control1.bits.peripheral_enable = 0;
    i2c_.control1 = control1;

    stm32::peripherals::InterIntegratedCircuit::InterruptClear interrupt_clear{};
    interrupt_clear.bits.address_match_clear = 1;
    interrupt_clear.bits.nack_clear = 1;
    interrupt_clear.bits.stop_condition_clear = 1;
    interrupt_clear.bits.bus_error_clear = 1;
    interrupt_clear.bits.arbitration_lost_clear = 1;
    interrupt_clear.bits.overrun_clear = 1;
    interrupt_clear.bits.parity_error_clear = 1;
    interrupt_clear.bits.timeout_flag = 1;
    interrupt_clear.bits.alert_flag_clear = 1;
    i2c_.interrupt_clear = interrupt_clear;

    control1 = i2c_.control1;
    control1.bits.peripheral_enable = 1;
    i2c_.control1 = control1;
}

void Driver::HandleEvent(void) {
    bool should_poll_again = false;
    do {
        stm32::peripherals::InterIntegratedCircuit::InterruptStatus interrupt_status = i2c_.interrupt_status;
        if constexpr (debug::I2cIsr) {
            jarnax::print(
                "I2C Event ISR txis:%" PRIu32 " rxne:%" PRIu32 " tc:%" PRIu32 " stop:%" PRIu32 "\n",
                static_cast<uint32_t>(interrupt_status.bits.transmit_interrupt_status),
                static_cast<uint32_t>(interrupt_status.bits.receive_buffer_not_empty),
                static_cast<uint32_t>(interrupt_status.bits.transmit_complete),
                static_cast<uint32_t>(interrupt_status.bits.stop_detection)
            );
        }
        if (interrupt_status.bits.receive_buffer_not_empty) {
            statistics_.events.receive_not_empty++;
            if (transaction_ != nullptr and transaction_->address.small.read != 0U and transaction_->actual_count < transaction_->desired_count) {
                auto span = transaction_->buffer.as_span().subspan(0, transaction_->desired_count);
                span[transaction_->actual_count] = i2c_.receive_data.bits.receive_data_buffer;
                transaction_->actual_count++;
                statistics_.bytes_received++;
                should_poll_again = true;
            }
        }
        if (interrupt_status.bits.transmit_interrupt_status) {
            statistics_.events.transmit_empty++;
            if (transaction_ != nullptr and transaction_->address.small.read == 0U and transaction_->actual_count < transaction_->desired_count) {
                auto span = transaction_->buffer.as_span().subspan(0, transaction_->desired_count);
                i2c_.transmit_data.bits.transmit_data_buffer = span[transaction_->actual_count];
                transaction_->actual_count++;
                statistics_.bytes_transmitted++;
                should_poll_again = true;
            }
        }
        if (interrupt_status.bits.transmit_complete) {
            statistics_.events.transfer_finished++;    // Increment the transfer-finished count
            if (transaction_ != nullptr and transaction_->actual_count >= transaction_->desired_count) {
                stm32::peripherals::InterIntegratedCircuit::Control2 control2;
                control2 = i2c_.control2;
                control2.bits.stop = 1;
                i2c_.control2 = control2;
                statistics_.events.stop++;
                should_poll_again = true;
            }
        }
        if (interrupt_status.bits.stop_detection) {
            stm32::peripherals::InterIntegratedCircuit::InterruptClear interrupt_clear{};
            interrupt_clear.bits.stop_condition_clear = 1;
            i2c_.interrupt_clear = interrupt_clear;

            if (transaction_ != nullptr) {
                statistics_.completed++;
                core::Status status{core::Result::Success, core::Cause::State};
                transaction_->Inform(jarnax::i2c::Transaction::Event::Completed, status);
                transaction_ = nullptr;
            }
        }
        if (interrupt_status.bits.alert) {
            statistics_.events.smbus_alert++;    // Increment the SMBus alert count
        }
    } while (should_poll_again);
}

void Driver::HandleError(void) {
    bool should_stop = false;    // Flag to indicate if we should stop the transaction
    core::Status status;
    stm32::peripherals::InterIntegratedCircuit::InterruptStatus interrupt_status = i2c_.interrupt_status;
    stm32::peripherals::InterIntegratedCircuit::InterruptClear interrupt_clear{};
    if (interrupt_status.bits.bus_error) {
        statistics_.errors.bus++;    // Increment the bus error count
        should_stop = true;          // Set the flag to stop the transaction
        interrupt_clear.bits.bus_error_clear = 1;
    }
    if (interrupt_status.bits.arbitration_lost) {
        status = core::Status{core::Result::NotReady, core::Cause::Hardware};    // set the status to not available
        statistics_.errors.arbitration_lost++;                                   // Increment the arbitration lost count
        should_stop = true;                                                      // Set the flag to stop the transaction
        interrupt_clear.bits.arbitration_lost_clear = 1;
    }
    if (interrupt_status.bits.nack_flag) {
        statistics_.errors.acknowledge++;                                            // Increment the acknowledge failure count
        status = core::Status{core::Result::NotAvailable, core::Cause::Hardware};    // set the status to not available
        should_stop = true;                                                          // Set the flag to stop the transaction
        interrupt_clear.bits.nack_clear = 1;
    }
    if (interrupt_status.bits.overrun) {
        statistics_.errors.overrun++;                                                 // Increment the overrun error count
        status = core::Status{core::Result::ExceededLimit, core::Cause::Hardware};    // set the status to not available
        should_stop = true;                                                           // Set the flag to stop the transaction
        interrupt_clear.bits.overrun_clear = 1;
    }
    if (interrupt_status.bits.packet_error_code_error) {
        statistics_.errors.packet_error_code++;                                 // Increment the packet error code error count
        status = core::Status{core::Result::Failure, core::Cause::Hardware};    // set the status to not available
        should_stop = true;                                                     // Set the flag to stop the transaction
        interrupt_clear.bits.parity_error_clear = 1;
    }
    if (interrupt_status.bits.timeout) {
        statistics_.errors.timeout++;                                           // Increment the timeout error count
        status = core::Status{core::Result::Timeout, core::Cause::Hardware};    // set the status to timeout
        should_stop = true;                                                     // Set the flag to stop the transaction
        interrupt_clear.bits.timeout_flag = 1;
    }
    if (interrupt_status.bits.busy) {
        statistics_.errors.busy++;                                           // Increment the timeout error count
        status = core::Status{core::Result::Busy, core::Cause::Hardware};    // set the status to busy
        should_stop = true;                                                  // Set the flag to stop the transaction
    }
    i2c_.interrupt_clear = interrupt_clear;

    if (should_stop) {
        // If we should stop the transaction, we can set the stop condition
        stm32::peripherals::InterIntegratedCircuit::Control2 control2;
        control2 = i2c_.control2;     // read
        control2.bits.stop = 1;       // set stop condition
        i2c_.control2 = control2;     // write
        statistics_.events.stop++;    // Increment the stop condition count
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
        static_cast<uint8_t>(transaction.address.small.address),    // defeat the automatic int promotion
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
        stm32::peripherals::InterIntegratedCircuit::Control1 control1;
        control1 = i2c_.control1;
        control1.bits.error_interrupt_enable = 1;
        control1.bits.transfer_complete_interrupt_enable = 1;
        control1.bits.stop_interrupt_enable = 1;
        control1.bits.nack_interrupt_enable = 1;
        control1.bits.transmit_direct_memory_access_enable = transaction.address.small.read == 0U ? 1U : 0U;
        control1.bits.receive_direct_memory_access_enable = transaction.address.small.read != 0U ? 1U : 0U;
        i2c_.control1 = control1;
        span = transaction.buffer.as_span().subspan(0, transaction.desired_count);
        // If using DMA, we need to set up the DMA streams for the transaction
        if (transaction.address.small.read) {
            // Set up the RX DMA stream
            rx_dma_resource_->ConfigureCopyFromPeripheral(reinterpret_cast<std::uintptr_t>(&i2c_.receive_data), span);
            rx_dma_resource_->Enable();    // start the RX DMA stream
        } else {
            // Set up the TX DMA stream
            tx_dma_resource_->ConfigureCopyToPeripheral(span, reinterpret_cast<std::uintptr_t>(&i2c_.transmit_data));
            tx_dma_resource_->Enable();    // start the TX DMA stream
        }
    } else {
        // enable the interrupts for the I2C peripheral
        stm32::peripherals::InterIntegratedCircuit::Control1 control1;
        control1 = i2c_.control1;
        control1.bits.error_interrupt_enable = 1;
        control1.bits.stop_interrupt_enable = 1;
        control1.bits.nack_interrupt_enable = 1;
        control1.bits.transfer_complete_interrupt_enable = 1;
        control1.bits.transmit_interrupt_enable = transaction.address.small.read == 0U ? 1U : 0U;
        control1.bits.receive_interrupt_enable = transaction.address.small.read != 0U ? 1U : 0U;
        control1.bits.transmit_direct_memory_access_enable = 0;
        control1.bits.receive_direct_memory_access_enable = 0;
        i2c_.control1 = control1;
        // If not using DMA, we need to set up the I2C peripheral for the transaction
        // the interrupt will handle the transaction?
    }

    // memorize the transaction pointer to so that the interrupt can use it
    transaction_ = &transaction;

    stm32::peripherals::InterIntegratedCircuit::Control2 control2;
    control2 = i2c_.control2;
    control2.bits.follower_address = static_cast<std::uint32_t>(transaction.address.small.address) << 1U;
    control2.bits.read_write = transaction.address.small.read != 0U ? 1U : 0U;
    control2.bits.address10 = transaction.address.small.is_large != 0U ? 1U : 0U;
    control2.bits.byte_count = static_cast<std::uint32_t>(transaction.desired_count & 0xFFU);
    control2.bits.transfer_reload = transaction.desired_count > 255U ? 1U : 0U;
    control2.bits.autoend = 0;
    control2.bits.start = 1;
    i2c_.control2 = control2;
    statistics_.events.start++;
    //=============================================================
    // The interrupt will likely fire here
    //=============================================================
    return core::Status{core::Result::Success, core::Cause::State};
}

core::Status Driver::Check(jarnax::i2c::Transaction& transaction) {
    if constexpr (configure::use_i2c_as == configure::Mode::Dma) {
        // @TODO check to see if the DMA is complete yet.
    } else {
        // Keep the transaction busy until ISR-level completion clears the active pointer.
        // This avoids reporting success while the final byte/STOP sequence is still in flight.
        if (transaction_ == &transaction) {
            if (transaction.address.small.read == 0U and transaction.desired_count > 0U and transaction.actual_count >= transaction.desired_count) {
                // Hardware should complete write transfers on BTF. If BTF is occasionally
                // missed, finalize here once all bytes were queued to avoid deadline timeouts.
                stm32::peripherals::InterIntegratedCircuit::Control2 control2;
                control2 = i2c_.control2;    // read
                control2.bits.stop = 1;      // set stop condition
                i2c_.control2 = control2;    // write

                core::Status status{core::Result::Success, core::Cause::State};
                transaction_->Inform(jarnax::i2c::Transaction::Event::Completed, status);
                transaction_ = nullptr;
                return status;
            }
            if constexpr (debug::I2c) {
                static std::size_t last_actual_count{static_cast<std::size_t>(-1)};
                static std::uint32_t stagnant_count{0U};
                if (transaction.actual_count == last_actual_count) {
                    stagnant_count++;
                } else {
                    stagnant_count = 0U;
                    last_actual_count = transaction.actual_count;
                }
                if ((stagnant_count & 0x3FU) == 0U) {
                    jarnax::print(
                        "STM32 I2C Check: busy desired=%" PRIz " actual=%" PRIz " stagnant=%" PRIu32 "\r\n",
                        transaction.desired_count,
                        transaction.actual_count,
                        stagnant_count
                    );
                }
            }
            return core::Status{core::Result::Busy, core::Cause::State};
        }
        // compare the send vs send or received vs receive size
        if (transaction.desired_count > 0 and transaction.actual_count < transaction.desired_count) {
            // If we have not sent all the data, we need to continue sending
            return core::Status{core::Result::Busy, core::Cause::State};
        }
    }
    if constexpr (debug::I2c) {
        jarnax::print("STM32 I2C Check: complete desired=%" PRIz " actual=%" PRIz "\r\n", transaction.desired_count, transaction.actual_count);
    }
    return core::Status{core::Result::Success, core::Cause::State};
}

core::Status Driver::Cancel(jarnax::i2c::Transaction& transaction) {
    (void)transaction;    // suppress unused parameter warning
    // disable the interrupts for the I2C peripheral
    stm32::peripherals::InterIntegratedCircuit::Control1 control1;
    control1 = i2c_.control1;
    control1.bits.error_interrupt_enable = 0;
    control1.bits.stop_interrupt_enable = 0;
    control1.bits.nack_interrupt_enable = 0;
    control1.bits.transfer_complete_interrupt_enable = 0;
    control1.bits.transmit_interrupt_enable = 0;
    control1.bits.receive_interrupt_enable = 0;
    control1.bits.transmit_direct_memory_access_enable = 0;
    control1.bits.receive_direct_memory_access_enable = 0;
    i2c_.control1 = control1;

    stm32::peripherals::InterIntegratedCircuit::Control2 control2;
    control2 = i2c_.control2;
    control2.bits.stop = 1;
    i2c_.control2 = control2;
    statistics_.events.stop++;    // Increment the stop condition count
    Reset();
    return core::Status{core::Result::Success, core::Cause::State};
}
}    // namespace i2c
}    // namespace stm32

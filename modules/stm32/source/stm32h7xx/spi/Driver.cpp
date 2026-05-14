#include "stm32/spi/Driver.hpp"
#include "cortex/halt.hpp"
#include "cortex/thumb.hpp"
#include "cortex/vectors.hpp"
#include "jarnax/Assertion.hpp"
#include "jarnax/print.hpp"
#include "stm32/configure.hpp"
#include "stm32/peripherals.hpp"

namespace stm32 {

/// Array of pointers to active SPI driver instances (SPI1-6)
spi::Driver* spi_instances[6] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
/// Array of pointers to SPI driver statistics structures (SPI1-6)
spi::Driver::Statistics* spi_statistics[6] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};

// Declare instances of the templates so that they have debugging symbols

/// Interrupt service routine for SPI1
void spi1_isr(void) {
    cortex::extended_vector_statistics.count[polyfill::to_underlying(stm32::InterruptRequest::SerialPeripheralInterface1)]++;
    if (spi_instances[0]) {
        spi_instances[0]->HandleInterrupt();
    }
}

/// Interrupt service routine for SPI2
void spi2_isr(void) {
    cortex::extended_vector_statistics.count[polyfill::to_underlying(stm32::InterruptRequest::SerialPeripheralInterface2)]++;
    if (spi_instances[1]) {
        spi_instances[1]->HandleInterrupt();
    }
}

/// Interrupt service routine for SPI3
void spi3_isr(void) {
    cortex::extended_vector_statistics.count[polyfill::to_underlying(stm32::InterruptRequest::SerialPeripheralInterface3)]++;
    if (spi_instances[2]) {
        spi_instances[2]->HandleInterrupt();
    }
}

/// Interrupt service routine for SPI4
void spi4_isr(void) {
    cortex::extended_vector_statistics.count[polyfill::to_underlying(stm32::InterruptRequest::SerialPeripheralInterface4)]++;
    if (spi_instances[3]) {
        spi_instances[3]->HandleInterrupt();
    }
}

/// Interrupt service routine for SPI5
void spi5_isr(void) {
    cortex::extended_vector_statistics.count[polyfill::to_underlying(stm32::InterruptRequest::SerialPeripheralInterface5)]++;
    if (spi_instances[4]) {
        spi_instances[4]->HandleInterrupt();
    }
}

/// Interrupt service routine for SPI6
void spi6_isr(void) {
    cortex::extended_vector_statistics.count[polyfill::to_underlying(stm32::InterruptRequest::SerialPeripheralInterface6)]++;
    if (spi_instances[5]) {
        spi_instances[5]->HandleInterrupt();
    }
}

constexpr static bool trigger_isr_from_start = false;    ///< Whether to trigger the ISR from the start of the transaction

namespace spi {
Driver::Driver(
    stm32::peripherals::SerialPeripheralInterface volatile& spi, jarnax::dma::Manager& dma_driver, cortex::Peripheral rx_peripheral,
    cortex::Peripheral tx_peripheral
)
    : jarnax::spi::Driver{static_cast<jarnax::spi::Transactor&>(*this)}    // initialize the base class by handing off the transactor
    , jarnax::spi::Transactor{}
    , statistics_{}
    , spi_{spi}
    , dma_manager_{dma_driver}
    , rx_peripheral_{rx_peripheral}
    , rx_dma_resource_{nullptr}
    , tx_peripheral_{tx_peripheral}
    , tx_dma_resource_{nullptr}
    , transaction_{nullptr}
    , peripheral_frequency_{0_Hz} {
    if (&spi == &h7xx::spi1) {
        spi_instances[0] = this;
        spi_statistics[0] = &statistics_;
    } else if (&spi == &h7xx::spi2) {
        spi_instances[1] = this;
        spi_statistics[1] = &statistics_;
    } else if (&spi == &h7xx::spi3) {
        spi_instances[2] = this;
        spi_statistics[2] = &statistics_;
    } else if (&spi == &h7xx::spi4) {
        spi_instances[3] = this;
        spi_statistics[3] = &statistics_;
    } else if (&spi == &h7xx::spi5) {
        spi_instances[4] = this;
        spi_statistics[4] = &statistics_;
    } else if (&spi == &h7xx::spi6) {
        spi_instances[5] = this;
        spi_statistics[5] = &statistics_;
    }
}

stm32::peripherals::SerialPeripheralInterface::BaudRateDivider Driver::FindClosestDivider(
    core::units::Hertz peripheral_frequency, core::units::Hertz desired_spi_clock_frequency
) {
    std::uint32_t divisor = peripheral_frequency.value() / desired_spi_clock_frequency.value();
    // e.g. 480MHz / 600KHz = 800
    // e.g. 480MHz / 2MHz = 240
    // e.g. 480MHz / 50MHz = 9.6 -> 10
    // e.g. 480MHz / 133MHz = 3.61 -> 4
    if (divisor <= 2U) {
        return stm32::peripherals::SerialPeripheralInterface::BaudRateDivider::By2;
    } else if (divisor <= 4U) {
        return stm32::peripherals::SerialPeripheralInterface::BaudRateDivider::By4;
    } else if (divisor <= 8U) {
        return stm32::peripherals::SerialPeripheralInterface::BaudRateDivider::By8;
    } else if (divisor <= 16U) {
        return stm32::peripherals::SerialPeripheralInterface::BaudRateDivider::By16;
    } else if (divisor <= 32U) {
        return stm32::peripherals::SerialPeripheralInterface::BaudRateDivider::By32;
    } else if (divisor <= 64U) {
        return stm32::peripherals::SerialPeripheralInterface::BaudRateDivider::By64;
    } else if (divisor <= 128U) {
        return stm32::peripherals::SerialPeripheralInterface::BaudRateDivider::By128;
    } else {
        return stm32::peripherals::SerialPeripheralInterface::BaudRateDivider::By256;
    }
}

core::Status Driver::Initialize(core::units::Hertz peripheral_frequency, core::units::Hertz desired_spi_clock_frequency) {
    if constexpr (configure::use_spi_as == configure::Mode::Dma) {
        jarnax::print("STM32H7 SPI Driver: Using DMA for SPI transactions.\r\n");
    } else {
        jarnax::print("STM32H7 SPI Driver: Using interrupts for SPI transactions.\r\n");
    }
    core::Status status{};
    peripheral_frequency_ = peripheral_frequency;
    rx_dma_resource_ = dma_manager_.Assign(rx_peripheral_);
    if (rx_dma_resource_ == nullptr) {
        return core::Status{core::Result::InvalidValue, core::Cause::Configuration};
    }
    tx_dma_resource_ = dma_manager_.Assign(tx_peripheral_);
    if (tx_dma_resource_ == nullptr) {
        dma_manager_.Release(rx_dma_resource_);
        return core::Status{core::Result::InvalidValue, core::Cause::Configuration};
    }
    rx_dma_resource_->Initialize(rx_peripheral_);
    tx_dma_resource_->Initialize(tx_peripheral_);

    stm32::h7xx::SerialPeripheralInterface::Configuration1 cfg1;
    stm32::h7xx::SerialPeripheralInterface::Configuration2 cfg2;
    stm32::h7xx::SerialPeripheralInterface::Control1 control1;

    std::uint32_t setting = polyfill::to_underlying(FindClosestDivider(peripheral_frequency_, desired_spi_clock_frequency));
    // Configure Configuration1 register
    cfg1 = spi_.configuration1;                            // read
    cfg1.bits.baud_rate_prescaler = (setting & 0x7U);      // set the baud rate divider
    cfg1.bits.data_size = 7U;                              // 8-bit data frame format (dsize = n-1)
    cfg1.bits.cyclic_redundancy_check_enable = 0;          // CRC calculation disabled
    cfg1.bits.receive_direct_memory_access_enable = 0;     // DMA RX disabled (for now)
    cfg1.bits.transmit_direct_memory_access_enable = 0;    // DMA TX disabled (for now)
    spi_.configuration1 = cfg1;                            // write

    // Configure Configuration2 register
    cfg2 = spi_.configuration2;                    // read
    cfg2.bits.leader_mode = 1;                     // master mode
    cfg2.bits.clock_polarity = 0;                  // first clock transition is the first data capture edge
    cfg2.bits.clock_phase = 0;                     // first clock transition is the first data capture edge
    cfg2.bits.least_significant_bit_first = 0;     // MSB first
    cfg2.bits.software_follower_management = 1;    // software slave management (NSS controlled by SW)
    cfg2.bits.follower_output_enable = 1;          // drive the NSS pin as an output
    cfg2.bits.communication_mode = 0U;             // Full duplex mode
    cfg2.bits.serial_protocol = 0U;                // Motorola SPI format
    spi_.configuration2 = cfg2;                    // write

    std::uint32_t const divider = (static_cast<std::uint32_t>(1UL) << (setting + 1U));
    jarnax::print(
        "Peripheral: %" PRIu32 " SPI Divider: %" PRIu32 " Clock Rate: %" PRIu32 "\n",
        peripheral_frequency.value(),
        divider,
        peripheral_frequency.value() / divider
    );

    // Disable SPI for now
    control1 = spi_.control1;                                // read
    control1.bits.serial_peripheral_interface_enable = 0;    // SPI disable (for now)
    spi_.control1 = control1;                                // write

    return core::Status{core::Result::Success, core::Cause::State};
}

void Driver::PrintTransaction(char const* const prefix, jarnax::spi::Transaction const& transaction) const {
    if constexpr (debug::Spi) {
        auto span = transaction.buffer.as_span();
        jarnax::print(
            "%s: SPI transaction: TX: %" PRIz "/%" PRIz " RX: %" PRIz "/%" PRIz " off: %" PRIz " buffer=%p:%" PRIz "\n",
            prefix,
            transaction.sent_size,
            transaction.send_size,
            transaction.received_size,
            transaction.receive_size,
            transaction.receive_offset,
            reinterpret_cast<void const*>(span.data()),
            span.size()
        );
        jarnax::print("Span Data: ", span);
        jarnax::print("Transaction Status:", transaction.GetStatus());
    }
}

core::Status Driver::Verify(jarnax::spi::Transaction& transaction) {
    // the coordinator has already checked the generic parts of the transaction we just
    // have to check the SPI specific parts
    PrintTransaction("Verify", transaction);
    size_t total_size = transaction.receive_size + transaction.send_size;
    if (transaction.buffer.size() < total_size) {
        return core::Status{core::Result::InvalidValue, core::Cause::Parameter};
    }
    // any combination of CPOL/CPHA is valid
    // any setting of use_data_as_bytes is valid
    // any setting of use_hardware_crc is valid
    // either nullptr or a pointer is a valid chip select
    if (transaction.buffer.IsEmpty()) {
        return core::Status{core::Result::InvalidValue, core::Cause::Parameter};
    }
    return core::Status{core::Result::Success, core::Cause::State};
}

core::Status Driver::Start(jarnax::spi::Transaction& transaction) {
    PrintTransaction("Start", transaction);
    // set the device to disabled
    stm32::h7xx::SerialPeripheralInterface::Configuration1 cfg1;
    stm32::h7xx::SerialPeripheralInterface::Configuration2 cfg2;
    stm32::h7xx::SerialPeripheralInterface::InterruptEnable int_enable;

    Disable();    // start disabled

    //=========================================
    // configure the transaction
    cfg1 = spi_.configuration1;                                          // read
    cfg1.bits.data_size = (transaction.use_data_as_bytes) ? 7U : 15U;    // 8-bit or 16-bit data frame format
    cfg1.bits.cyclic_redundancy_check_enable = 0;                        // TODO not supported yet (transaction.use_hardware_crc) ? 1 : 0;
    spi_.configuration1 = cfg1;                                          // write

    cfg2 = spi_.configuration2;                                          // read
    cfg2.bits.clock_polarity = (transaction.polarity == jarnax::spi::ClockPolarity::IdleHigh) ? 1 : 0;
    cfg2.bits.clock_phase = (transaction.phase == jarnax::spi::ClockPhase::FirstAfterEdge) ? 1 : 0;
    spi_.configuration2 = cfg2;    // write
    //=========================================
    transaction_ = &transaction;    // assign the transaction to the driver
    //=========================================
    Select(transaction);
    //=========================================
    Enable();
    //=========================================
    int_enable = spi_.interrupt_enable;                 // read
    int_enable.bits.mode_fault_interrupt_enable = 1;    // Mode Fault interrupt enable
    int_enable.bits.overrun_interrupt_enable = 1;       // Overrun interrupt enable
    if constexpr (stm32::configure::use_spi_as == configure::Mode::Dma) {
        cfg1 = spi_.configuration1;                     // read
        cfg1.bits.transmit_direct_memory_access_enable = (transaction.send_size > 0U);
        cfg1.bits.receive_direct_memory_access_enable = (transaction.receive_size > 0U);
        spi_.configuration1 = cfg1;                              // write
        int_enable.bits.transmit_packet_interrupt_enable = 0;    // no interrupt on TXP
        int_enable.bits.receive_packet_interrupt_enable = 0;     // no interrupt on RXP
        //=========================================
        // configure the DMA (TX then RX)
        if (transaction.send_size > 0U) {
            auto tx_span = transaction.buffer.as_span().subspan(0, transaction.send_size);
            tx_dma_resource_->ConfigureCopyToPeripheral(tx_span, reinterpret_cast<std::uintptr_t>(&spi_.transmit_data.whole));
            tx_dma_resource_->Enable();    // start the DMA stream, TXDREQ will cause the write to happen
        }
        if (transaction.receive_size > 0U) {
            auto rx_span = transaction.buffer.as_span().subspan(transaction.receive_offset, transaction.receive_size);
            rx_dma_resource_->ConfigureCopyFromPeripheral(reinterpret_cast<std::uintptr_t>(&spi_.receive_data.whole), rx_span);
            rx_dma_resource_->Enable();    // start the DMA stream, RXDREQ will cause the read to happen
        }
    } else {
        cfg1 = spi_.configuration1;    // read
        cfg1.bits.transmit_direct_memory_access_enable = 0;
        cfg1.bits.receive_direct_memory_access_enable = 0;
        spi_.configuration1 = cfg1;                                                           // write
        int_enable.bits.transmit_packet_interrupt_enable = (transaction.send_size > 0U);      // interrupt on TXP (transmit packet)
        int_enable.bits.receive_packet_interrupt_enable = (transaction.receive_size > 0U);    // interrupt on RXP (receive packet)
        //=========================================
        if constexpr (stm32::trigger_isr_from_start) {
            if (transaction.send_size > 0U) {
                auto write_span = transaction.buffer.as_span().subspan(0, transaction.send_size);
                spi_.transmit_data.bits.transmit_data = write_span[0];    // write the first byte to the data register
                transaction.sent_size++;                                  // set the sent size to 1
                statistics_.bytes_transmitted++;
            }
        }
        //=========================================
    }
    spi_.interrupt_enable = int_enable;    // write
    return core::Status{core::Result::Success, core::Cause::State};
}

core::Status Driver::Check(jarnax::spi::Transaction& transaction) {
    PrintTransaction("Check", transaction);
    core::Status status;
    bool tx_fault{false};
    bool rx_fault{false};
    // assume true then set false when not complete yet
    bool tx_complete{true};
    bool rx_complete{true};
    if (transaction.sent_size != transaction.send_size and transaction.send_size > 0U) {
        if constexpr (configure::use_spi_as == configure::Mode::Dma) {
            // check the TX stream
            status = tx_dma_resource_->GetStatus();
            if (status.IsSuccess()) {
                transaction.sent_size = transaction.send_size;
            } else if (status.IsBusy()) {
                // wait
                tx_complete = false;
            } else {
                // failure
                tx_fault = true;
            }
        } else {
            tx_complete = false;
        }
    }
    if (transaction.received_size != transaction.receive_size and transaction.receive_size > 0U) {
        if constexpr (configure::use_spi_as == configure::Mode::Dma) {
            // check the rX stream
            status = rx_dma_resource_->GetStatus();
            if (status.IsSuccess()) {
                transaction.received_size = transaction.receive_size;
            } else if (status.IsBusy()) {
                // wait
                rx_complete = false;
            } else {
                // failure
                rx_fault = true;
            }
        } else {
            rx_complete = false;
        }
    }
    if (tx_complete and rx_complete) {
        Cancel(transaction);
        if (tx_fault or rx_fault) {
            return core::Status{core::Result::Failure, core::Cause::Peripheral};
        } else {
            return core::Status{core::Result::Success, core::Cause::State};
        }
    } else {
        return core::Status{core::Result::Busy, core::Cause::State};
    }
}    // namespace stm32

void Driver::Enable(void) {
    // enable the peripheral
    stm32::h7xx::SerialPeripheralInterface::Control1 control1;
    control1 = spi_.control1;                                // read
    control1.bits.serial_peripheral_interface_enable = 1;    // modify
    spi_.control1 = control1;                                // write
}

void Driver::Select(jarnax::spi::Transaction& transaction) {
    if (transaction.chip_select != nullptr) {
        transaction.chip_select->Value(false);    // active low chip select
    } else {
        stm32::h7xx::SerialPeripheralInterface::Control1 control1;
        control1 = spi_.control1;                      // read
        control1.bits.internal_follower_select = 0;    // enable the internal follower select (NSS active)
        spi_.control1 = control1;                      // write
    }
}

void Driver::Deselect(jarnax::spi::Transaction& transaction) {
    if (transaction.chip_select != nullptr) {
        transaction.chip_select->Value(true);    // active low chip select
    } else {
        stm32::h7xx::SerialPeripheralInterface::Control1 control1;
        control1 = spi_.control1;                      // read
        control1.bits.internal_follower_select = 1;    // disable the internal follower select (NSS inactive)
        spi_.control1 = control1;                      // write
    }
}

void Driver::Disable(void) {
    // disable the peripheral
    stm32::h7xx::SerialPeripheralInterface::Control1 control1;
    control1 = spi_.control1;                                // read
    control1.bits.serial_peripheral_interface_enable = 0;    // modify
    spi_.control1 = control1;                                // write
}

core::Status Driver::Cancel(jarnax::spi::Transaction& transaction) {
    PrintTransaction("Cancel", transaction);
    Disable();
    Deselect(transaction);
    if constexpr (configure::use_spi_as == configure::Mode::Dma) {
        // disable the streams
        tx_dma_resource_->Disable();
        rx_dma_resource_->Disable();
    } else {
        // disable the interrupts
        stm32::h7xx::SerialPeripheralInterface::InterruptEnable int_enable = spi_.interrupt_enable;    // read
        int_enable.bits.receive_packet_interrupt_enable = 0;                                           // disable RXP interrupt
        int_enable.bits.transmit_packet_interrupt_enable = 0;                                          // disable TXP interrupt
        spi_.interrupt_enable = int_enable;                                                            // write
    }

    return core::Status{core::Result::Success, core::Cause::State};
}

void Driver::HandleInterrupt(void) {
    stm32::h7xx::SerialPeripheralInterface::Status status;
    stm32::h7xx::SerialPeripheralInterface::InterruptEnable int_enable;
    stm32::h7xx::SerialPeripheralInterface::ReceiveData receive_reg;
    stm32::h7xx::SerialPeripheralInterface::TransmitData transmit_reg;

    status = spi_.status;    // read the status register

    statistics_.interrupts++;
    if constexpr (debug::SpiIsr) {
        jarnax::print(
            "SPI ISR Status: %" PRIx32 " ISRs:%" PRIz " ove:%" PRIu32 " udr:%" PRIu32 " rxp:%" PRIu32 " txp:%" PRIu32 " crce:%" PRIu32
            " modf:%" PRIu32 " busy:%" PRIu32 "\n",
            status.whole,
            statistics_.interrupts,
            static_cast<uint32_t>(status.bits.overrun),
            static_cast<uint32_t>(status.bits.underrun),
            static_cast<uint32_t>(status.bits.receive_packet_available),
            static_cast<uint32_t>(status.bits.transmit_packet_available),
            static_cast<uint32_t>(status.bits.cyclic_redundancy_check_error),
            static_cast<uint32_t>(status.bits.mode_fault),
            static_cast<uint32_t>(status.bits.receive_word_not_empty)
        );
    }
    int_enable = spi_.interrupt_enable;    // read the interrupt enable register
    thumb::nop();
    thumb::nop();
    thumb::nop();
    if (int_enable.bits.receive_packet_interrupt_enable and status.bits.receive_packet_available) {
        // reading from spi_.receive_data will clear the RXP flag
        statistics_.receive_buffer_not_empty++;
        if constexpr (configure::use_spi_as == configure::Mode::Interrupt) {
            if (transaction_->received_size < transaction_->receive_size) {
                constexpr uint32_t mask = ((1 << (sizeof(jarnax::spi::DataUnit) * 8U)) - 1);
                // read the next byte from the SPI receive data register
                auto rx_span = transaction_->buffer.as_span().subspan(transaction_->receive_offset, transaction_->receive_size);
                receive_reg = spi_.receive_data;                                                 // read
                rx_span[transaction_->received_size++] =
                    static_cast<jarnax::spi::DataUnit>(receive_reg.bits.receive_data & mask);    // write to buffer
                if constexpr (debug::SpiIsr) {
                    jarnax::print("SPI Read %" PRIx32 "\n", receive_reg.bits.receive_data);
                }
                statistics_.bytes_received++;
                if (transaction_->received_size == transaction_->receive_size) {
                    int_enable = spi_.interrupt_enable;                     // read
                    int_enable.bits.receive_packet_interrupt_enable = 0;    // disable RXP interrupt
                    spi_.interrupt_enable = int_enable;                     // write
                    statistics_.transfers_received++;
                }
            }
        }
    }

    if (int_enable.bits.transmit_packet_interrupt_enable and status.bits.transmit_packet_available) {
        // writing into spi_.transmit_data will clear the TXP flag
        statistics_.transmit_buffer_empty++;
        if constexpr (configure::use_spi_as == configure::Mode::Interrupt) {
            if (transaction_->sent_size < transaction_->send_size) {
                auto tx_span = transaction_->buffer.as_span().subspan(0, transaction_->send_size);
                transmit_reg.bits.transmit_data = tx_span[transaction_->sent_size++];    // write from the buffer to the register
                spi_.transmit_data = transmit_reg;                                       // write
                statistics_.bytes_transmitted++;
                if (transaction_->sent_size == transaction_->send_size) {
                    int_enable = spi_.interrupt_enable;                      // read
                    int_enable.bits.transmit_packet_interrupt_enable = 0;    // disable TXP interrupt
                    spi_.interrupt_enable = int_enable;                      // write
                    statistics_.transfers_sent++;
                }
            }
        }
    }

    // if all the transactions are done, complete the transaction
    if ((transaction_->sent_size == transaction_->send_size) and (transaction_->received_size == transaction_->receive_size)) {
        Deselect(*transaction_);
        Disable();
        transaction_->Inform(
            jarnax::spi::Transaction::Event::Completed, core::Status{core::Result::Success, core::Cause::State}
        );    // inform the transaction that it is complete
        // forget the pointer
        transaction_ = nullptr;
    }

    if (status.bits.overrun) {
        receive_reg = spi_.receive_data;    // read the data register to clear the overrun flag
        status = spi_.status;               // read the status register again to clear the overrun flag
        statistics_.overrun++;
    }
    if (status.bits.underrun) {
        statistics_.underrun++;
    }
    if (status.bits.cyclic_redundancy_check_error) {
        statistics_.crc_error++;
    }
    if (status.bits.mode_fault) {
        statistics_.mode_fault++;
    }
}

}    // namespace spi
}    // namespace stm32

namespace jarnax {
// Declare the specializations for the Transactor and Coordinator
template class Transactable<spi::Transaction, spi::DefaultRetries>;
template class Transactor<spi::Transaction>;
template class Coordinator<spi::Transaction, spi::DefaultQueueDepth>;
}    // namespace jarnax

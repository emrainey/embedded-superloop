#include "cortex/halt.hpp"
#include "cortex/thumb.hpp"
#include "cortex/vectors.hpp"
#include "jarnax/Assertion.hpp"
#include "jarnax/print.hpp"
#include "stm32/configure.hpp"

#include "stm32/peripherals/ResetAndClockControl.hpp"
#include "stm32/spi/Driver.hpp"

namespace stm32 {

spi::Driver* spi_instances[3] = {nullptr, nullptr, nullptr};
spi::Driver::Statistics* spi_statistics[3] = {nullptr, nullptr, nullptr};

// Declare instances of the templates so that they have debugging symbols

void spi1_isr(void) {
    cortex::extended_vector_statistics.count[to_underlying(stm32::InterruptRequest::SerialPeripheralInterface1)]++;
    if (spi_instances[0]) {
        spi_instances[0]->HandleInterrupt();
    }
}

void spi2_isr(void) {
    cortex::extended_vector_statistics.count[to_underlying(stm32::InterruptRequest::SerialPeripheralInterface2)]++;
    if (spi_instances[1]) {
        spi_instances[1]->HandleInterrupt();
    }
}

void spi3_isr(void) {
    cortex::extended_vector_statistics.count[to_underlying(stm32::InterruptRequest::SerialPeripheralInterface3)]++;
    if (spi_instances[2]) {
        spi_instances[2]->HandleInterrupt();
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
    if (&spi == &peripherals::spi1) {
        spi_instances[0] = this;
        spi_statistics[0] = &statistics_;
    } else if (&spi == &peripherals::spi2) {
        spi_instances[1] = this;
        spi_statistics[1] = &statistics_;
    } else if (&spi == &peripherals::spi3) {
        spi_instances[2] = this;
        spi_statistics[2] = &statistics_;
    }
}

stm32::peripherals::SerialPeripheralInterface::Control1::BaudRateDivider Driver::FindClosestDivider(
    core::units::Hertz peripheral_frequency, core::units::Hertz desired_spi_clock_frequency
) {
    std::uint32_t divisor = peripheral_frequency.value() / desired_spi_clock_frequency.value();
    // e.g. 168MHz / 600KHz = 280
    // e.g. 168MHz / 2MHz = 84
    // e.g. 168MHz / 50MHz = 3.36 -> 3
    // e.g. 168MHz / 133MHz = 1.26 -> 1
    if (divisor <= 2U) {
        return stm32::peripherals::SerialPeripheralInterface::Control1::BaudRateDivider::By2;
    } else if (divisor <= 4U) {
        return stm32::peripherals::SerialPeripheralInterface::Control1::BaudRateDivider::By4;
    } else if (divisor <= 8U) {
        return stm32::peripherals::SerialPeripheralInterface::Control1::BaudRateDivider::By8;
    } else if (divisor <= 16U) {
        return stm32::peripherals::SerialPeripheralInterface::Control1::BaudRateDivider::By16;
    } else if (divisor <= 32U) {
        return stm32::peripherals::SerialPeripheralInterface::Control1::BaudRateDivider::By32;
    } else if (divisor <= 64U) {
        return stm32::peripherals::SerialPeripheralInterface::Control1::BaudRateDivider::By64;
    } else if (divisor <= 128U) {
        return stm32::peripherals::SerialPeripheralInterface::Control1::BaudRateDivider::By128;
    } else {
        return stm32::peripherals::SerialPeripheralInterface::Control1::BaudRateDivider::By256;
    }
}

core::Status Driver::Initialize(core::units::Hertz peripheral_frequency, core::units::Hertz desired_spi_clock_frequency) {
    if constexpr (configure::use_spi_as == configure::Mode::Dma) {
        jarnax::print("STM32 SPI Driver: Using DMA for SPI transactions.\r\n");
    } else {
        jarnax::print("STM32 SPI Driver: Using interrupts for SPI transactions.\r\n");
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

    stm32::peripherals::SerialPeripheralInterface::Control1 control1;
    stm32::peripherals::SerialPeripheralInterface::Control2 control2;

    std::uint32_t setting = to_underlying(FindClosestDivider(peripheral_frequency_, desired_spi_clock_frequency));
    // disable at first
    control1 = spi_.control1;                              // read
    control1.bits.clock_polarity = 0;                      // first clock transition is the first data capture edge
    control1.bits.clock_phase = 0;                         // first clock transition is the first data capture edge
    control1.bits.leader = 1;                              // master mode (MSTR)
    control1.bits.baud_rate = (setting & 0x7U);            // set the baud rate divider
    control1.bits.spi_enable = 0;                          // SPI disable (for now)
    control1.bits.lsbfirst = 0;                            // MSB first
    control1.bits.software_follower_management = 1;        // software slave management (NSS is controlled by us SW)
    control1.bits.internal_follower_select = 1;            // internal slave select, 1 means de-selected
    control1.bits.rxonly = 0;                              // full duplex
    control1.bits.data_frame_format = 0;                   // 8-bit data frame format
    control1.bits.crc_next = 0;                            // CRC next disabled
    control1.bits.crc_enable = 0;                          // CRC calculation disabled
    control1.bits.bidirectional_data_output_enable = 0;    // (ignored)
    control1.bits.bidirectional_data_mode = 0;             // 2-line bidirectional
    spi_.control1 = control1;                              // write

    auto divider = control1.baud_rate_divider();
    jarnax::print(
        "Peripheral: %" PRIu32 " SPI Divider: %" PRIu32 " Clock Rate: %lu\n",
        peripheral_frequency.value(),
        divider,
        peripheral_frequency.value() / divider
    );

    control2 = spi_.control2;                    // read
    control2.bits.follower_output_enable = 1;    // drive the NSS pin as an output
    control2.bits.frame_format = 0;              // motorola SPI format
    spi_.control2 = control2;                    // write

    stm32::peripherals::SerialPeripheralInterface::InterIntegratedCircuitSoundConfiguration i2s_cfg = spi_.i2s_configuration;    // read
    i2s_cfg.bits.i2smod = 0;                                                                                                     // disable the I2S
    spi_.i2s_configuration = i2s_cfg;                                                                                            // write

    control1 = spi_.control1;                                                                                                    // read
    control1.bits.spi_enable = 0;                                                                                                // modify
    spi_.control1 = control1;                                                                                                    // write

    return core::Status{core::Result::Success, core::Cause::State};
}

void Driver::PrintTransaction(char const* const prefix, jarnax::spi::Transaction const& transaction) const {
    if constexpr (debug::spi) {
        auto span = transaction.buffer.as_span();
        jarnax::print(
            "%s: SPI transaction: TX: %" PRIz "/%" PRIz " RX: %" PRIz "/%" PRIz " off: %" PRIz " buffer=%p:%" PRIz "\n",
            prefix,
            transaction.sent_size,
            transaction.send_size,
            transaction.received_size,
            transaction.receive_size,
            transaction.receive_offset,
            span.data(),
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
    peripherals::SerialPeripheralInterface::Control1 control1;
    peripherals::SerialPeripheralInterface::Control2 control2;

    Disable();    // start disabled

    //=========================================
    // configure the transaction
    control1 = spi_.control1;        // read
    control1.bits.data_frame_format = (transaction.use_data_as_bytes) ? 0 : 1;
    control1.bits.crc_enable = 0;    // TODO not supported yet (transaction.use_hardware_crc) ? 1 : 0;
    control1.bits.clock_polarity = (transaction.polarity == jarnax::spi::ClockPolarity::IdleHigh) ? 1 : 0;
    control1.bits.clock_phase = (transaction.phase == jarnax::spi::ClockPhase::FirstAfterEdge) ? 1 : 0;
    spi_.control1 = control1;    // write
    //=========================================
    transaction_ = &transaction;    // assign the transaction to the driver
    //=========================================
    Select(transaction);
    //=========================================
    // assertion(spi_.status.bits.transmit_buffer_empty == 1);
    //=========================================
    Enable();
    //=========================================
    control2 = spi_.control2;                    // read
    control2.bits.error_interrupt_enable = 1;    // interrupt on errors
    if constexpr (stm32::configure::use_spi_as == configure::Mode::Dma) {
        control2.bits.transmit_dma_enable = (transaction.send_size > 0U);
        control2.bits.receive_dma_enable = (transaction.receive_size > 0U);
        control2.bits.transmit_buffer_empty_interrupt_enable = 0;       // no interrupt on TXE
        control2.bits.receive_buffer_not_empty_interrupt_enable = 0;    // no interrupt on RXNE
        //=========================================
        // configure the DMA (TX then RX)
        if (transaction.send_size > 0U) {
            auto tx_span = transaction.buffer.as_span().subspan(0, transaction.send_size);
            tx_dma_resource_->ConfigureCopyToPeripheral(tx_span, reinterpret_cast<std::uintptr_t>(&spi_.data.whole));
            tx_dma_resource_->Enable();    // start the DMA stream, TXE will cause the write to happen
        }
        if (transaction.receive_size > 0U) {
            auto rx_span = transaction.buffer.as_span().subspan(transaction.receive_offset, transaction.receive_size);
            rx_dma_resource_->ConfigureCopyFromPeripheral(reinterpret_cast<std::uintptr_t>(&spi_.data.whole), rx_span);
            rx_dma_resource_->Enable();    // start the DMA stream, RXNE will cause the read to happen
        }
    } else {
        control2.bits.transmit_dma_enable = 0;
        control2.bits.receive_dma_enable = 0;
        control2.bits.transmit_buffer_empty_interrupt_enable = (transaction.send_size > 0U);          // interrupt on TXE
        control2.bits.receive_buffer_not_empty_interrupt_enable = (transaction.receive_size > 0U);    // interrupt on RXNE
        //=========================================
        if constexpr (stm32::trigger_isr_from_start) {
            if (transaction.send_size > 0U) {
                auto write_span = transaction.buffer.as_span().subspan(0, transaction.send_size);
                spi_.data.bits.data = write_span[0];    // write the first byte to the data register
                transaction.sent_size++;                // set the sent size to 1
                statistics_.bytes_transmitted++;
            }
        }
        //=========================================
    }
    spi_.control2 = control2;    // write
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
    peripherals::SerialPeripheralInterface::Control1 control1;
    control1 = spi_.control1;        // read
    control1.bits.spi_enable = 1;    // modify
    spi_.control1 = control1;        // write}
}

void Driver::Select(jarnax::spi::Transaction& transaction) {
    if (transaction.chip_select != nullptr) {
        transaction.chip_select->Value(false);    // active low chip select
    } else {
        peripherals::SerialPeripheralInterface::Control1 control1;
        control1 = spi_.control1;                      // read
        control1.bits.internal_follower_select = 0;    // enable the internal follower select
        spi_.control1 = control1;                      // write
    }
}

void Driver::Deselect(jarnax::spi::Transaction& transaction) {
    if (transaction.chip_select != nullptr) {
        transaction.chip_select->Value(true);    // active low chip select
    } else {
        peripherals::SerialPeripheralInterface::Control1 control1;
        control1 = spi_.control1;                      // read
        control1.bits.internal_follower_select = 1;    // disable the internal follower select
        spi_.control1 = control1;                      // write
    }
}

void Driver::Disable(void) {
    // disable the peripheral
    peripherals::SerialPeripheralInterface::Control1 control1;
    control1 = spi_.control1;        // read
    control1.bits.spi_enable = 0;    // modify
    spi_.control1 = control1;        // write
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
        peripherals::SerialPeripheralInterface::Control2 control2 = spi_.control2;    // read
        control2.bits.transmit_buffer_empty_interrupt_enable = 0;                     // disable TXE interrupt
        control2.bits.receive_buffer_not_empty_interrupt_enable = 0;                  // disable RXNE interrupt
        spi_.control2 = control2;                                                     // write
    }

    return core::Status{core::Result::Success, core::Cause::State};
}

void Driver::HandleInterrupt(void) {
    peripherals::SerialPeripheralInterface::Status status;
    peripherals::SerialPeripheralInterface::Control2 control2;
    peripherals::SerialPeripheralInterface::Data data;

    status = spi_.status;    // read the status register

    statistics_.interrupts++;
    if constexpr (debug::spi_isr) {
        jarnax::print(
            "SPI ISR Status: %" PRIx32 " ISRs:%" PRIz " u:%" PRIu32 " o:%" PRIu32 " tbe:%" PRIu32 " rbne:%" PRIu32 " crce:%" PRIu32 " mf:%" PRIu32
            " b:%" PRIu32 "\n",
            status.whole,
            statistics_.interrupts,
            static_cast<uint32_t>(status.bits.underrun),
            static_cast<uint32_t>(status.bits.overrun),
            static_cast<uint32_t>(status.bits.transmit_buffer_empty),
            static_cast<uint32_t>(status.bits.receive_buffer_not_empty),
            static_cast<uint32_t>(status.bits.crc_error),
            static_cast<uint32_t>(status.bits.mode_fault),
            static_cast<uint32_t>(status.bits.busy)
        );
    }
    control2 = spi_.control2;    // read the control2 register
    thumb::nop();
    thumb::nop();
    thumb::nop();
    if (control2.bits.receive_buffer_not_empty_interrupt_enable and status.bits.receive_buffer_not_empty) {
        // reading from spi_.data will clear the RXNE flag
        statistics_.receive_buffer_not_empty++;
        if constexpr (configure::use_spi_as == configure::Mode::Interrupt) {
            if (transaction_->received_size < transaction_->receive_size) {
                constexpr uint32_t mask = ((1 << (sizeof(jarnax::spi::DataUnit) * 8U)) - 1);
                // read the next byte from the SPI data register
                auto rx_span = transaction_->buffer.as_span().subspan(transaction_->receive_offset, transaction_->receive_size);
                data = spi_.data;                                                                                      // read
                rx_span[transaction_->received_size++] = static_cast<jarnax::spi::DataUnit>(data.bits.data & mask);    // write to buffer
                if constexpr (debug::spi_isr) {
                    jarnax::print("SPI Read %hx\n", data.bits.data);
                }
                statistics_.bytes_received++;
                if (transaction_->received_size == transaction_->receive_size) {
                    control2 = spi_.control2;                                       // read
                    control2.bits.receive_buffer_not_empty_interrupt_enable = 0;    // disable RXNE interrupt
                    spi_.control2 = control2;                                       // write
                    statistics_.transfers_received++;
                }
            }
        }
    }

    if (control2.bits.transmit_buffer_empty_interrupt_enable and status.bits.transmit_buffer_empty) {
        // writing into spi_.data will clear the TXE flag
        statistics_.transmit_buffer_empty++;
        if constexpr (configure::use_spi_as == configure::Mode::Interrupt) {
            if (transaction_->sent_size < transaction_->send_size) {
                auto tx_span = transaction_->buffer.as_span().subspan(0, transaction_->send_size);
                data.bits.data = tx_span[transaction_->sent_size++];    // write from the buffer to the register
                spi_.data = data;                                       // write
                statistics_.bytes_transmitted++;
                //} else {
                // we let this fire one more extra time so that we can disable the TXE interrupt and the transaction
                if (transaction_->sent_size == transaction_->send_size) {
                    control2 = spi_.control2;                                    // read
                    control2.bits.transmit_buffer_empty_interrupt_enable = 0;    // disable TXE interrupt
                    spi_.control2 = control2;                                    // write
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
        data = spi_.data;        // read the data register to clear the overrun flag
        status = spi_.status;    // read the status register again to clear the overrun flag
        statistics_.overrun++;
    }
    if (status.bits.underrun) {
        statistics_.underrun++;
    }
    if (status.bits.crc_error) {
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

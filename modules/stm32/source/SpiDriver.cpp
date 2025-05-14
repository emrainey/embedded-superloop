#include "board.hpp"
#include "jarnax/print.hpp"
#include "stm32/SpiDriver.hpp"
#include "stm32/registers/ResetAndClockControl.hpp"

namespace stm32 {

SpiDriver* g_spi_instances[3] = {nullptr, nullptr, nullptr};

// Declare instances of the templates so that they have debugging symbols

void spi1_isr(void) {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::SerialPeripheralInterface1)]++;
    if (g_spi_instances[0]) {
        g_spi_instances[0]->HandleInterrupt();
    }
}

void spi2_isr(void) {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::SerialPeripheralInterface2)]++;
    if (g_spi_instances[1]) {
        g_spi_instances[1]->HandleInterrupt();
    }
}

void spi3_isr(void) {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::SerialPeripheralInterface3)]++;
    if (g_spi_instances[2]) {
        g_spi_instances[2]->HandleInterrupt();
    }
}

SpiDriver::SpiDriver(
    stm32::registers::SerialPeripheralInterface volatile& spi, dma::Driver& dma_driver, dma::Peripheral rx_peripheral, dma::Peripheral tx_peripheral
)
    : jarnax::spi::Driver{static_cast<jarnax::spi::Transactor&>(*this)}    // initialize the base class by handing off the transactor
    , spi_{spi}
    , dma_driver_{dma_driver}
    , rx_peripheral_{rx_peripheral}
    , rx_dma_stream_{*dma_driver_.Assign(rx_peripheral)}
    , rx_dma_stream_index_{dma::Driver::NumStreams}
    , tx_peripheral_{tx_peripheral}
    , tx_dma_stream_{*dma_driver_.Assign(tx_peripheral)}
    , tx_dma_stream_index_{dma::Driver::NumStreams}
    , transaction_{nullptr} {
    if (&spi == &registers::spi1) {
        g_spi_instances[0] = this;
    } else if (&spi == &registers::spi2) {
        g_spi_instances[1] = this;
    } else if (&spi == &registers::spi3) {
        g_spi_instances[2] = this;
    }
}

stm32::registers::SerialPeripheralInterface::Control1::BaudRateDivider SpiDriver::FindClosestDivider(
    core::units::Hertz peripheral_frequency, core::units::Hertz desired_spi_clock_frequency
) {
    std::uint32_t divisor = peripheral_frequency.value() / desired_spi_clock_frequency.value();
    // e.g. 168MHz / 600KHz = 280
    // e.g. 168MHz / 2MHz = 84
    // e.g. 168MHz / 50MHz = 3.36 -> 3
    // e.g. 168MHz / 133MHz = 1.26 -> 1
    if (divisor <= 2U) {
        return stm32::registers::SerialPeripheralInterface::Control1::BaudRateDivider::By2;
    } else if (divisor <= 4U) {
        return stm32::registers::SerialPeripheralInterface::Control1::BaudRateDivider::By4;
    } else if (divisor <= 8U) {
        return stm32::registers::SerialPeripheralInterface::Control1::BaudRateDivider::By8;
    } else if (divisor <= 16U) {
        return stm32::registers::SerialPeripheralInterface::Control1::BaudRateDivider::By16;
    } else if (divisor <= 32U) {
        return stm32::registers::SerialPeripheralInterface::Control1::BaudRateDivider::By32;
    } else if (divisor <= 64U) {
        return stm32::registers::SerialPeripheralInterface::Control1::BaudRateDivider::By64;
    } else if (divisor <= 128U) {
        return stm32::registers::SerialPeripheralInterface::Control1::BaudRateDivider::By128;
    } else {
        return stm32::registers::SerialPeripheralInterface::Control1::BaudRateDivider::By256;
    }
}

core::Status SpiDriver::Initialize(core::units::Hertz peripheral_frequency, core::units::Hertz desired_spi_clock_frequency) {
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

    stm32::registers::SerialPeripheralInterface::Control1 control1;
    stm32::registers::SerialPeripheralInterface::Control2 control2;

    std::uint32_t setting = to_underlying(FindClosestDivider(peripheral_frequency, desired_spi_clock_frequency));
    // disable at first
    control1 = spi_.control1;                              // read
    spi_.control1.bits.spi_enable = 0;                     // modify
    spi_.control1 = control1;                              // write
    control1.bits.clock_polarity = 0;                      // first clock transition is the first data capture edge
    control1.bits.clock_phase = 0;                         // first clock transition is the first data capture edge
    control1.bits.baud_rate = (setting & 0x7);             // set the baud rate divider
    control1.bits.leader = 1;                              // master mode
    control1.bits.lsbfirst = 0;                            // MSB first
    control1.bits.software_follower_management = 0;        // software slave management (NSS pin is controlled by peripheral)
    control1.bits.internal_follower_select = 0;            // internal slave select
    control1.bits.rxonly = 0;                              // full duplex
    control1.bits.data_frame_format = 0;                   // 16-bit data frame format
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
    control2.bits.follower_output_enable = 0;    // don't enable the follower output
    control2.bits.frame_format = 0;              // motorola SPI format
    spi_.control2 = control2;                    // write

    stm32::registers::SerialPeripheralInterface::InterIntegratedCircuitSoundConfiguration i2c_cfg = spi_.i2s_configuration;    // read
    i2c_cfg.bits.i2smod = 0;                                                                                                   // disable the I2S
    spi_.i2s_configuration = i2c_cfg;                                                                                          // write

    control1 = spi_.control1;        // read
    control1.bits.spi_enable = 0;    // modify
    spi_.control1 = control1;        // write

    return core::Status{core::Result::Success, core::Cause::State};
}

core::Status SpiDriver::Verify(jarnax::spi::Transaction& transaction) {
    // the coordinator has already checked the generic parts of the transaction we just
    // have to check the SPI specific parts
    size_t total_size = transaction.receive_size + transaction.send_size;
    if constexpr (jarnax::debug::spi) {
        jarnax::print(
            "SPI transaction: TX: %u RX: %u total: %u buffer: %u\n",
            transaction.send_size,
            transaction.receive_size,
            total_size,
            transaction.buffer.size()
        );
    }
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

core::Status SpiDriver::Start(jarnax::spi::Transaction& transaction) {
    // set the device to disabled
    registers::SerialPeripheralInterface::Control1 control1;
    registers::SerialPeripheralInterface::Control2 control2;

    control1 = spi_.control1;        // read
    control1.bits.spi_enable = 0;    // modify
    spi_.control1 = control1;        // write
    //=========================================
    // configure the transaction
    control1.bits.data_frame_format = (transaction.use_data_as_bytes) ? 0 : 1;
    control1.bits.crc_enable = (transaction.use_hardware_crc) ? 1 : 0;
    control1.bits.internal_follower_select = 0;
    control1.bits.software_follower_management = 0;
    control1.bits.clock_polarity = (transaction.polarity == jarnax::spi::ClockPolarity::IdleHigh) ? 1 : 0;
    control1.bits.clock_phase = (transaction.phase == jarnax::spi::ClockPhase::FirstAfterEdge) ? 1 : 0;
    spi_.control1 = control1;    // write
    //=========================================
    control2 = spi_.control2;                                       // read
    control2.bits.transmit_buffer_empty_interrupt_enable = 0;       // no interrupt on TXE
    control2.bits.receive_buffer_not_empty_interrupt_enable = 0;    // no interrupt on RXNE
    control2.bits.error_interrupt_enable = 1;                       // interrupt on errors
    if constexpr (stm32::use_dma_for_spi) {
        if (transaction.send_size > 0U) {
            control2.bits.transmit_dma_enable = 1;
            control2.bits.receive_dma_enable = 0;
        } else if (transaction.receive_size > 0U) {
            control2.bits.transmit_dma_enable = 0;
            control2.bits.receive_dma_enable = 1;
        }
    } else {
        control2.bits.transmit_dma_enable = 0;
        control2.bits.receive_dma_enable = 0;
    }
    // if the transaction does not have the chip select set then enable the follower output
    control2.bits.follower_output_enable = (transaction.chip_select == nullptr) ? 0 : 1;
    control2.bits.frame_format = 0;    // motorola SPI format
    spi_.control2 = control2;          // write
    //=========================================
    transaction_ = &transaction;    // assign the transaction to the driver
    //=========================================
    // configure the DMA (TX then RX)
    if (transaction.send_size > 0U) {
        auto tx_span = transaction.buffer.as_span().subspan(0, transaction.send_size);
        dma_driver_.CopyToPeripheral(tx_dma_stream_, reinterpret_cast<uint32_t volatile*>(&spi_.data.whole), tx_span.data(), tx_span.count());
        dma_driver_.Start(tx_dma_stream_);    // start the DMA stream, TXE will cause the write to happen
    } else if (transaction.send_size == 0U) {
        auto rx_span = transaction.buffer.as_span().subspan(transaction.receive_offset, transaction.send_size + transaction.receive_size);
        dma_driver_.CopyFromPeripheral(rx_dma_stream_, rx_span.data(), reinterpret_cast<uint32_t volatile*>(&spi_.data.whole), rx_span.count());
        dma_driver_.Start(rx_dma_stream_);    // start the DMA stream, RXNE will cause the read to happen
    }
    //=========================================
    // enable the peripheral
    if (transaction.chip_select != nullptr) {
        transaction.chip_select->Value(false);    // active low chip select
    }
    //=========================================
    // enable the peripheral to start a transaction
    control1.bits.spi_enable = 1;
    spi_.control1 = control1;    // write

    //=========================================
    return core::Status{core::Result::Success, core::Cause::State};
}

core::Status SpiDriver::Check(jarnax::spi::Transaction& transaction) {
    core::Status status;
    dma::Driver::Flags flags;
    bool fault{false};
    if (transaction.sent_size != transaction.send_size and transaction.send_size > 0U) {
        // check the TX stream
        status = dma_driver_.GetStreamStatus(tx_dma_stream_index_, flags);
        if (status) {
            if constexpr (jarnax::debug::spi) {
                jarnax::print(
                    "SPI TX DMA[%u] flags: c:%u h:%u e:%u dme:%u fe:%u\n",
                    tx_dma_stream_index_,
                    flags.complete,
                    flags.half_complete,
                    flags.error,
                    flags.direct_mode_error,
                    flags.fifo_error
                );
            }
            if (flags.complete) {
                transaction.sent_size = transaction.send_size;
            } else if (flags.error or flags.direct_mode_error or flags.fifo_error) {
                fault = true;
            }
        }
    }
    if (transaction.received_size != transaction.receive_size and transaction.receive_size > 0U) {
        // check the TX stream
        status = dma_driver_.GetStreamStatus(rx_dma_stream_index_, flags);
        if (status) {
            if constexpr (jarnax::debug::spi) {
                jarnax::print(
                    "SPI RX DMA[%u] flags: c:%u h:%u e:%u dme:%u fe:%u\n",
                    rx_dma_stream_index_,
                    flags.complete,
                    flags.half_complete,
                    flags.error,
                    flags.direct_mode_error,
                    flags.fifo_error
                );
            }
            if (flags.complete) {
                transaction.received_size = transaction.receive_size;
            } else if (flags.error or flags.direct_mode_error or flags.fifo_error) {
                fault = true;
            }
        }
    }
    if constexpr (jarnax::debug::spi) {
        registers::SerialPeripheralInterface::Status status_reg = spi_.status;    // read
        jarnax::print(
            "SPI Status u:%u o:%u tbe:%u rbne:%u crce:%u mf:%u b:%u\n",
            status_reg.bits.underrun,
            status_reg.bits.overrun,
            status_reg.bits.transmit_buffer_empty,
            status_reg.bits.receive_buffer_not_empty,
            status_reg.bits.crc_error,
            status_reg.bits.mode_fault,
            status_reg.bits.busy
        );
    }
    if (spi_.status.bits.busy) {
        return core::Status{core::Result::Busy, core::Cause::State};
    }

    Cancel(transaction);
    if (fault) {
        return core::Status{core::Result::Failure, core::Cause::Peripheral};
    } else {
        return core::Status{core::Result::Success, core::Cause::State};
    }
}

core::Status SpiDriver::Cancel(jarnax::spi::Transaction& transaction) {
    // disable the peripheral
    registers::SerialPeripheralInterface::Control1 control1;
    control1 = spi_.control1;        // read
    control1.bits.spi_enable = 0;    // modify
    spi_.control1 = control1;        // write

    // disable the streams
    tx_dma_stream_.configuration.bits.stream_enable = 0;    // read, modify, write
    rx_dma_stream_.configuration.bits.stream_enable = 0;    // read, modify, write

    if (transaction.chip_select != nullptr) {
        transaction.chip_select->Value(true);    // active low chip select
    }

    return core::Status{core::Result::Success, core::Cause::State};
}

void SpiDriver::HandleInterrupt(void) {
    registers::SerialPeripheralInterface::Status status = spi_.status;    // read
    if constexpr (jarnax::debug::spi_isr) {
        jarnax::print(
            "SPI ISR Status: %" PRIx32 " u:%u o:%u tbe:%u rbne:%u crce:%u mf:%u b:%u\n",
            status.whole,
            status.bits.underrun,
            status.bits.overrun,
            status.bits.transmit_buffer_empty,
            status.bits.receive_buffer_not_empty,
            status.bits.crc_error,
            status.bits.mode_fault,
            status.bits.busy
        );
    }
    if (status.bits.overrun) {
        registers::SerialPeripheralInterface::Data data = spi_.data;    // read
        jarnax::print("SPI Overrun, read %x\n", data.bits.data);
        status = spi_.status;    // read
    }

    if (status.bits.transmit_buffer_empty) {
        // disable TXE interrupt in Control2
        // registers::SerialPeripheralInterface::Control2 control2 = spi_.control2;    // read
        // control2.bits.transmit_buffer_empty_interrupt_enable = 0;                   // disable TXE interrupt
        // spi_.control2 = control2;                                                   // write
    }
}

}    // namespace stm32

namespace jarnax {
// Declare the specializations for the Transactor and Coordinator
template class Transactable<spi::Transaction, spi::DefaultRetries>;
template class Transactor<spi::Transaction>;
template class Coordinator<spi::Transaction, spi::DefaultQueueDepth>;
}    // namespace jarnax

#include "compiler.hpp"
#include "stm32/SpiDriver.hpp"
#include "stm32/registers/ResetAndClockControl.hpp"

namespace stm32 {

SpiDriver::SpiDriver(
    stm32::registers::SerialPeripheralInterface volatile& spi,
    dma::Driver& dma_driver,
    stm32::registers::DirectMemoryAccess::Stream volatile& rx_dma_stream,
    stm32::registers::DirectMemoryAccess::Stream volatile& tx_dma_stream
)
    : jarnax::spi::Driver{static_cast<jarnax::spi::Transactor&>(*this)}    // initialize the base class by handing off the transactor
    , spi_{spi}
    , dma_driver_{dma_driver}
    , rx_dma_stream_{rx_dma_stream}
    , tx_dma_stream_{tx_dma_stream} {
    // TODO Assert if the & of a stream is nullptr
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
    stm32::registers::SerialPeripheralInterface::Control1 control1;
    stm32::registers::SerialPeripheralInterface::Control2 control2;
    // disable at first
    control1 = spi_.control1;             // read
    spi_.control1.bits.spi_enable = 0;    // modify
    spi_.control1 = control1;             // write
    std::uint32_t baudrate = to_underlying(FindClosestDivider(peripheral_frequency, desired_spi_clock_frequency));
    control1.bits.clock_polarity = 0;                      // first clock transition is the first data capture edge
    control1.bits.clock_phase = 0;                         // first clock transition is the first data capture edge
    control1.bits.baud_rate = (baudrate & 0x7);            // set the baud rate divider
    control1.bits.leader = 1;                              // master mode
    control1.bits.lsbfirst = 0;                            // MSB first
    control1.bits.software_follower_management = 0;        // software slave management (NSS pin is controlled by peripheral)
    control1.bits.rxonly = 0;                              // full duplex
    control1.bits.data_frame_format = 1;                   // 16-bit data frame format
    control1.bits.crc_enable = 0;                          // CRC calculation disabled
    control1.bits.bidirectional_data_output_enable = 0;    // (ignored)
    control1.bits.bidirectional_data_mode = 0;             // 2-line unidirectional
    spi_.control1 = control1;                              // write

    control2 = spi_.control2;          // read
    control2.bits.frame_format = 0;    // motorola SPI format
    spi_.control2 = control2;          // write

    control1 = spi_.control1;        // read
    control1.bits.spi_enable = 1;    // modify
    spi_.control1 = control1;        // write

    return core::Status{core::Result::Success, core::Cause::State};
}

core::Status SpiDriver::Verify(jarnax::spi::Transaction& transaction) {
    // the coordinator has already checked the generic parts of the transaction we just
    // have to check the SPI specific parts
    size_t size = transaction.receive_size + transaction.send_size;
    if (transaction.buffer.size() < size) {
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

    // configure the transaction
    control1.bits.data_frame_format = (transaction.use_data_as_bytes) ? 0 : 1;
    control1.bits.crc_enable = (transaction.use_hardware_crc) ? 1 : 0;
    control1.bits.internal_follower_select = 0;
    control1.bits.software_follower_management = 0;

    control2 = spi_.control2;                                       // read
    control2.bits.transmit_buffer_empty_interrupt_enable = 0;       // No interrupt on TXE
    control2.bits.receive_buffer_not_empty_interrupt_enable = 0;    // No interrupt on RXNE
    control2.bits.error_interrupt_enable = 0;                       // No interrupt on errors
    // enable DMA on the transactions
    control2.bits.receive_dma_enable = 1;
    control2.bits.transmit_dma_enable = 1;
    // if the transaction does not have the chip select set then enable the follower output
    control2.bits.follower_output_enable = (transaction.chip_select == nullptr) ? 0 : 1;
    spi_.control2 = control2;    // write

    // configure the DMA (TX then RX)
    auto tx_span = transaction.buffer.as_span().subspan(0, transaction.send_size);
    dma_driver_.CopyToPeripheral(tx_dma_stream_, reinterpret_cast<uint32_t volatile*>(&spi_.data.whole), tx_span.data(), transaction.send_size);
    auto rx_span = transaction.buffer.as_span().subspan(transaction.send_size, transaction.receive_size);
    dma_driver_.CopyFromPeripheral(rx_dma_stream_, rx_span.data(), reinterpret_cast<uint32_t volatile*>(&spi_.data.whole), transaction.receive_size);

    // enable the peripheral
    if (transaction.chip_select != nullptr) {
        transaction.chip_select->Value(false);    // active low chip select
    }

    // enable the peripheral to start a transaction
    control1.bits.spi_enable = 1;
    spi_.control1 = control1;    // write
    return core::Status{core::Result::Success, core::Cause::State};
}

core::Status SpiDriver::Check(jarnax::spi::Transaction& transaction) {
    if (transaction.send_size > 0U) {
        // check the TX stream
        size_t tx_left = tx_dma_stream_.number_of_datum.bits.number_of_datum;
        if (tx_left > 0) {
            return core::Status{core::Result::Busy, core::Cause::State};
        }
    }
    if (transaction.receive_size > 0U) {
        // check the RX stream
        size_t rx_left = rx_dma_stream_.number_of_datum.bits.number_of_datum;
        if (rx_left > 0) {
            return core::Status{core::Result::Busy, core::Cause::State};
        }
    }
    if (spi_.status.bits.busy) {
        return core::Status{core::Result::Busy, core::Cause::State};
    }
    Cancel(transaction);
    return core::Status{core::Result::Success, core::Cause::State};
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

}    // namespace stm32
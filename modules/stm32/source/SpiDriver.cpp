#include "compiler.hpp"
#include "stm32/SpiDriver.hpp"
#include "stm32/registers/ResetAndClockControl.hpp"

namespace stm32 {

SpiDriver::SpiDriver(stm32::registers::SerialPeripheralInterface volatile& spi, dma::Driver& dma_driver, DmaBuffer const& dma_memory)
    : jarnax::spi::Driver{static_cast<jarnax::spi::Transactor&>(*this)}    // initialize the base class by handing off the transactor
    , spi_{spi}
    , dma_driver_{dma_driver}
    , dma_memory_{dma_memory}
    , dma_stream_{nullptr} {
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

    control1.bits.clock_polarity = 0;    // first clock transition is the first data capture edge
    control1.bits.clock_phase = 0;       // first clock transition is the first data capture edge
    control1.bits.baud_rate = to_underlying(FindClosestDivider(peripheral_frequency, desired_spi_clock_frequency));
    control1.bits.leader = 1;                              // master mode
    control1.bits.lsbfirst = 0;                            // MSB first
    control1.bits.software_follower_management = 1;        // software slave management (NSS pin is controlled by peripheral)
    control1.bits.rxonly = 0;                              // full duplex
    control1.bits.data_frame_format = 1;                   // 16-bit data frame format
    control1.bits.crc_enable = 0;                          // CRC calculation disabled
    control1.bits.bidirectional_data_output_enable = 0;    // output disabled
    control1.bits.bidirectional_data_mode = 0;             // 2-line unidirectional
    spi_.control1 = control1;                              // write

    control2 = spi_.control2;          // read
    control2.bits.frame_format = 0;    // motorola SPI format
    control2.bits.ssoe = 1;            // enable SS output
    spi_.control2 = control2;          // write

    control1 = spi_.control1;        // read
    control1.bits.spi_enable = 1;    // modify
    spi_.control1 = control1;        // write

    core::Status status = dma_driver_.Acquire(dma_stream_, 11U);    // SPI1_TX
    if (not status) {
        return status;
    }

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
    control1 = spi_.control1;        // read
    control1.bits.spi_enable = 0;    // modify
    spi_.control1 = control1;        // write

    // configure the transaction
    control1.bits.data_frame_format = (transaction.use_data_as_bytes) ? 0 : 1;
    control1.bits.crc_enable = (transaction.use_hardware_crc) ? 1 : 0;

    // enable the peripheral

    // do nothing
    return core::Status{core::Result::Success, core::Cause::State};
}

core::Status SpiDriver::Check(jarnax::spi::Transaction& transaction) {
    // do nothing
    return core::Status{core::Result::Success, core::Cause::State};
}

core::Status SpiDriver::Cancel(jarnax::spi::Transaction& transaction) {
    // do nothing
    return core::Status{core::Result::NotSupported, core::Cause::Configuration};
}

}    // namespace stm32
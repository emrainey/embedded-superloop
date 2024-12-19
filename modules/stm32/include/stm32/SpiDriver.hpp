#ifndef STM32_SPI_DRIVER_HPP
#define STM32_SPI_DRIVER_HPP

#include "core/Units.hpp"
#include "core/Array.hpp"
#include "jarnax/spi/Driver.hpp"
#include "stm32/dma/Driver.hpp"
#include "stm32/registers/SerialPeripheralInterface.hpp"

namespace stm32 {
class SpiDriver : public jarnax::spi::Driver, private jarnax::spi::Transactor {
public:
    static constexpr size_t kDmaMemorySize = 256U;
    using DmaBuffer = core::Array<uint8_t, kDmaMemorySize>;
    SpiDriver(stm32::registers::SerialPeripheralInterface volatile& spi, dma::Driver& dma_driver, DmaBuffer const& dma_memory);

    core::Status Initialize(core::units::Hertz peripheral_frequency, core::units::Hertz desired_spi_clock_frequency);

    stm32::registers::SerialPeripheralInterface::Control1::BaudRateDivider FindClosestDivider(
        core::units::Hertz peripheral_frequency, core::units::Hertz desired_spi_clock_frequency
    );

    //+======[ Transactor Interface ]=======================================================+
    core::Status Verify(jarnax::spi::Transaction& transaction) override;
    core::Status Start(jarnax::spi::Transaction& transaction) override;
    core::Status Check(jarnax::spi::Transaction& transaction) override;
    core::Status Cancel(jarnax::spi::Transaction& transaction) override;

protected:
    stm32::registers::SerialPeripheralInterface volatile& spi_;
    dma::Driver& dma_driver_;
    DmaBuffer const& dma_memory_;
    registers::DirectMemoryAccess::Stream volatile* dma_stream_;
};
}    // namespace stm32

#endif    // STM32_SPI_DRIVER_HPP
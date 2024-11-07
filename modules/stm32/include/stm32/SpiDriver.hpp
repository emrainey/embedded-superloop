#ifndef STM32_SPI_DRIVER_HPP
#define STM32_SPI_DRIVER_HPP

#include "core/Ring.hpp"
#include "jarnax/spi/Driver.hpp"
#include "stm32/registers/SerialPeripheralInterface.hpp"

namespace stm32 {
class SpiDriver : public jarnax::spi::Driver, private jarnax::spi::Transactor {
public:
    SpiDriver(stm32::registers::SerialPeripheralInterface volatile& spi);

    core::Status Initialize(Hertz peripheral_frequency, Hertz desired_spi_clock_frequency);

    //+======[ Transactor Interface ]=======================================================+
    core::Status Verify(jarnax::spi::Transaction& transaction) override;
    core::Status Start(jarnax::spi::Transaction& transaction) override;
    core::Status Check(jarnax::spi::Transaction& transaction) override;
    core::Status Cancel(jarnax::spi::Transaction& transaction) override;


protected:
    stm32::registers::SerialPeripheralInterface volatile& spi_;
};
}    // namespace stm32

#endif    // STM32_SPI_DRIVER_HPP
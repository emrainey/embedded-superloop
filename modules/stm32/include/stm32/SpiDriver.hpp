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
    SpiDriver(
        stm32::registers::SerialPeripheralInterface volatile& spi,
        dma::Driver& dma_driver,
        dma::Peripheral rx_peripheral,
        dma::Peripheral tx_peripheral
    );

    core::Status Initialize(core::units::Hertz peripheral_frequency, core::units::Hertz desired_spi_clock_frequency);

    stm32::registers::SerialPeripheralInterface::Control1::BaudRateDivider FindClosestDivider(
        core::units::Hertz peripheral_frequency, core::units::Hertz desired_spi_clock_frequency
    );

    void HandleInterrupt(void);

    //+======[ Transactor Interface ]=======================================================+
    core::Status Verify(jarnax::spi::Transaction& transaction) override;
    core::Status Start(jarnax::spi::Transaction& transaction) override;
    core::Status Check(jarnax::spi::Transaction& transaction) override;
    core::Status Cancel(jarnax::spi::Transaction& transaction) override;

    struct Statistics {
        uint32_t underrun{0U};      ///< The number of underrun errors
        uint32_t overrun{0U};       ///< The number of overrun errors
        uint32_t crc_error{0U};     ///< The number of CRC errors
        uint32_t mode_fault{0U};    ///< The number of mode faults

        uint32_t bytes_received{0U};       ///< The number of bytes received
        uint32_t bytes_transmitted{0U};    ///< The number of bytes transmitted
    };

    inline Statistics const& GetStatistics(void) const { return statistics_; }

protected:
    Statistics statistics_;    ///< The statistics for the SPI peripheral
    registers::SerialPeripheralInterface volatile& spi_;
    dma::Driver& dma_driver_;
    dma::Peripheral rx_peripheral_;
    registers::DirectMemoryAccess::Stream volatile& rx_dma_stream_;
    size_t rx_dma_stream_index_;
    dma::Peripheral tx_peripheral_;
    registers::DirectMemoryAccess::Stream volatile& tx_dma_stream_;
    size_t tx_dma_stream_index_;
    /// @brief  The current transaction which may need to be altered by an interrupt
    jarnax::spi::Transaction* transaction_;
};
}    // namespace stm32

#endif    // STM32_SPI_DRIVER_HPP
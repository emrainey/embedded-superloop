#ifndef STM32_SPI_DRIVER_HPP
#define STM32_SPI_DRIVER_HPP

#include "core/Array.hpp"
#include "core/Units.hpp"
#include "jarnax/spi/Driver.hpp"
#include "stm32/dma/Manager.hpp"
#include "stm32/registers/SerialPeripheralInterface.hpp"

namespace stm32 {
namespace spi {
class Driver : public jarnax::spi::Driver, private jarnax::spi::Transactor {
public:
    Driver(
        stm32::registers::SerialPeripheralInterface volatile& spi, jarnax::dma::Manager& dma_driver, jarnax::Peripheral rx_peripheral,
        jarnax::Peripheral tx_peripheral
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
        std::size_t interrupts{0U};                  ///< The number of interrupts handled

        std::size_t underrun{0U};                    ///< The number of underrun errors
        std::size_t overrun{0U};                     ///< The number of overrun errors
        std::size_t crc_error{0U};                   ///< The number of CRC errors
        std::size_t mode_fault{0U};                  ///< The number of mode faults
        std::size_t transmit_buffer_empty{0U};       ///< The number of times the transmit buffer was empty
        std::size_t receive_buffer_not_empty{0U};    ///< The number of times the

        std::size_t bytes_received{0U};              ///< The number of bytes received
        std::size_t bytes_transmitted{0U};           ///< The number of bytes transmitted

        std::size_t transfers_received{0U};          ///< The number of TX transfers completed
        std::size_t transfers_sent{0U};              ///< The number of RX transfers completed
    };

    inline Statistics const& GetStatistics(void) const { return statistics_; }

protected:
    /// @brief Enables the SPI peripheral which allows transactions to be started.
    void Enable(void);

    /// @brief Selects the external chip for the transaction.
    /// @param transaction The SPI transaction to select the chip for.
    void Select(jarnax::spi::Transaction& transaction);

    /// @brief Deselects the external chip for the transaction.
    /// @param transaction The SPI transaction to deselect the chip for.
    void Deselect(jarnax::spi::Transaction& transaction);

    /// @brief Disables the SPI peripheral which stops any ongoing transactions.
    void Disable(void);

    /// The statistics for the SPI peripheral
    Statistics statistics_;
    /// @brief The Serial Peripheral Interface registers for this driver
    registers::SerialPeripheralInterface volatile& spi_;
    /// @brief The DMA manager for the SPI driver
    jarnax::dma::Manager& dma_manager_;
    /// @brief  The Peripheral for Receive operations
    jarnax::Peripheral rx_peripheral_;
    /// @brief  The DMA resource for the receive stream
    jarnax::dma::Resource* rx_dma_resource_;
    /// @brief  The Peripheral for Transmit operations
    jarnax::Peripheral tx_peripheral_;
    /// @brief  The DMA resource for the transmit stream
    jarnax::dma::Resource* tx_dma_resource_;
    /// @brief  The current transaction which may need to be altered by an interrupt
    jarnax::spi::Transaction* transaction_;
    /// The peripheral clock frequency
    core::units::Hertz peripheral_frequency_;
};
}    // namespace spi
}    // namespace stm32

#endif    // STM32_SPI_DRIVER_HPP

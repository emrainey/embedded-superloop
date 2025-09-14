#ifndef STM32_I2C_DRIVER_HPP
#define STM32_I2C_DRIVER_HPP
#include "core/Buffer.hpp"
#include "core/Units.hpp"
#include "jarnax/i2c/Driver.hpp"
#include "stm32/dma/Manager.hpp"
#include "stm32/peripherals/InterIntegratedCircuit.hpp"

namespace stm32 {
namespace i2c {
class Driver final : public jarnax::i2c::Driver, private jarnax::i2c::Transactor {
public:
    /// @brief Constructor
    /// @param i2c The I2C peripheral to use
    /// @param dma_manager The DMA Manager to use
    /// @param rx_peripheral The RX peripheral for the DMA Driver
    /// @param tx_peripheral The TX peripheral for the DMA Driver
    Driver(
        stm32::peripherals::InterIntegratedCircuit volatile &i2c, jarnax::dma::Manager &dma_manager, Peripheral rx_peripheral,
        Peripheral tx_peripheral
    );
    ~Driver() = default;

    core::Status Initialize(core::units::Hertz peripheral_frequency, core::units::Hertz desired_i2c_clock_frequency);

    void HandleEvent(void);
    void HandleError(void);

    //+======[ Transactor Interface ]=======================================================+
    core::Status Verify(jarnax::i2c::Transaction &transaction) override;
    core::Status Start(jarnax::i2c::Transaction &transaction) override;
    core::Status Check(jarnax::i2c::Transaction &transaction) override;
    core::Status Cancel(jarnax::i2c::Transaction &transaction) override;

    struct Statistics {
        struct Errors {
            size_t bus{0U};                  ///< The number of bus errors encountered
            size_t arbitration_lost{0U};     ///< The number of times arbitration was lost
            size_t acknowledge{0U};          ///< The number of acknowledge failures
            size_t overrun{0U};              ///< The number of overrun errors
            size_t packet_error_code{0U};    ///< The number of packet error code errors
            size_t timeout{0U};              ///< The number of timeouts encountered
            size_t busy{0U};                 ///< The number of times the bus was busy
        } errors;
        struct Events {
            size_t start{0U};                ///< The number of start conditions generated
            size_t address_match{0U};        ///< The number of address sent events
            size_t transfer_finished{0U};    ///< The number of transfer finished events
            size_t smbus_alert{0U};          ///< The number of SMBus alert events
            size_t stop{0U};                 ///< The number of stop conditions generated
        } events;
        size_t bytes_received{0U};           ///< The number of bytes received
        size_t transmit_empty{0U};           ///< The number of bytes transmitted
    };

    inline Statistics const &GetStatistics(void) const { return statistics_; }

protected:
    void Reset(void);

    uint32_t GetClockDivider(core::units::Hertz peripheral_frequency, core::units::Hertz desired_i2c_clock_frequency);

    // @TODO Untested function
    // void ProgramAddress(jarnax::i2c::Address &address);

    /// The statistics for the I2C peripheral
    Statistics statistics_;
    /// The register reference to the I2C peripheral
    stm32::peripherals::InterIntegratedCircuit volatile &i2c_;
    /// @brief The DMA driver used for I2C transactions
    jarnax::dma::Manager &dma_manager_;
    /// @brief The peripheral used for receiving data
    cortex::Peripheral rx_peripheral_;
    /// @brief The DMA stream used for receiving data
    jarnax::dma::Resource *rx_dma_resource_;
    /// @brief The peripheral used for transmitting data
    cortex::Peripheral tx_peripheral_;
    /// @brief The DMA stream used for transmitting data
    jarnax::dma::Resource *tx_dma_resource_;
    /// @brief  The current transaction which may need to be altered by an interrupt
    jarnax::i2c::Transaction *transaction_;
    /// The peripheral clock frequency
    core::units::Hertz peripheral_frequency_;
};
}    // namespace i2c
}    // namespace stm32

#endif    // STM32_I2C_DRIVER_HPP

#ifndef STM32_I2C_DRIVER_HPP
#define STM32_I2C_DRIVER_HPP
#include "stm32/registers/InterIntegratedCircuit.hpp"
#include "jarnax/i2c/Driver.hpp"
#include "stm32/dma/Driver.hpp"
#include "core/Buffer.hpp"
#include "core/Units.hpp"

namespace stm32 {
namespace i2c {
class Driver final : public jarnax::i2c::Driver, private jarnax::i2c::Transactor {
public:
    Driver(
        stm32::registers::InterIntegratedCircuit volatile &i2c,
        dma::Driver &dma_driver,
        jarnax::Peripheral rx_peripheral,
        jarnax::Peripheral tx_peripheral
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
        size_t bytes_received{0U};    ///< The number of bytes received
        size_t transmit_empty{0U};    ///< The number of bytes transmitted
    };

    inline Statistics const &GetStatistics(void) const { return statistics_; }

protected:
    void Reset(void);

    uint32_t GetClockDivider(core::units::Hertz peripheral_frequency, core::units::Hertz desired_i2c_clock_frequency);

    // @TODO Untested function
    // void ProgramAddress(jarnax::i2c::Address &address);

    Statistics statistics_;    ///< The statistics for the I2C peripheral
    stm32::registers::InterIntegratedCircuit volatile &i2c_;
    dma::Driver &dma_driver_;
    jarnax::Peripheral rx_peripheral_;
    registers::DirectMemoryAccess::Stream volatile &rx_dma_stream_;
    size_t rx_dma_stream_index_;
    jarnax::Peripheral tx_peripheral_;
    registers::DirectMemoryAccess::Stream volatile &tx_dma_stream_;
    size_t tx_dma_stream_index_;
    /// @brief  The current transaction which may need to be altered by an interrupt
    jarnax::i2c::Transaction *transaction_;
};
}    // namespace i2c
}    // namespace stm32

#endif    // STM32_I2C_DRIVER_HPP
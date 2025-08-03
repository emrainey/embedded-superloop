#ifndef STM32_UART_DRIVER_HPP
#define STM32_UART_DRIVER_HPP

#include "core/Allocator.hpp"
#include "core/Units.hpp"
#include "jarnax/uart/Driver.hpp"
#include "stm32/dma/Manager.hpp"
#include "stm32/registers/UniversalAsynchronousReceiverTransmitter.hpp"

namespace stm32 {
namespace uart {
class Driver final : public jarnax::uart::Driver {
public:
    /// @brief Constructor
    /// @param uart The UART peripheral to use
    /// @param dma_driver The DMA Driver to use
    /// @param rx_peripheral The RX peripheral for the DMA Driver
    /// @param tx_peripheral The TX peripheral for the DMA Driver
    Driver(
        registers::UniversalAsynchronousReceiverTransmitter volatile& uart, dma::Manager& dma_driver, jarnax::Peripheral rx_peripheral,
        jarnax::Peripheral tx_peripheral, core::Allocator& dma_allocator
    );

    virtual ~Driver() = default;

    core::Status Initialize(core::units::Hertz peripheral_frequency);

    core::Status Configure(uint32_t baud_rate, bool parity, uint8_t stop_bits) override;
    core::Status Enqueue(core::Span<DataUnit> const& data) override;
    core::Status Dequeue(core::Span<DataUnit>& data) override;

    void HandleInterrupt(void);

protected:
    /// The UART peripheral
    registers::UniversalAsynchronousReceiverTransmitter volatile& uart_;
    /// The DMA Manager
    jarnax::dma::Manager& dma_manager_;
    /// The RX peripheral for the DMA Driver
    jarnax::Peripheral rx_peripheral_;
    jarnax::dma::Resource* rx_dma_resource_;
    /// The TX peripheral for the DMA Driver
    jarnax::Peripheral tx_peripheral_;
    jarnax::dma::Resource* tx_dma_resource_;
    /// @brief The Allocator for use with DMA memory
    core::Allocator& dma_allocator_;
    /// The peripheral clock frequency
    core::units::Hertz peripheral_frequency_;
};
}    // namespace uart
}    // namespace stm32
#endif    // STM32_UART_DRIVER_HPP

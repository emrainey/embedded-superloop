#ifndef STM32_UART_DRIVER_HPP
#define STM32_UART_DRIVER_HPP

#include "jarnax/uart/Driver.hpp"
#include "core/Units.hpp"
#include "stm32/dma/Driver.hpp"
#include "stm32/registers/UniversalAsynchronousReceiverTransmitter.hpp"

namespace stm32 {

class UartDriver : public jarnax::uart::Driver {
public:
    /// @brief Constructor
    /// @param uart The UART peripheral to use
    /// @param dma_driver The DMA Driver to use
    /// @param rx_peripheral The RX peripheral for the DMA Driver
    /// @param tx_peripheral The TX peripheral for the DMA Driver
    UartDriver(
        registers::UniversalAsynchronousReceiverTransmitter volatile& uart,
        dma::Driver& dma_driver,
        dma::Peripheral rx_peripheral,
        dma::Peripheral tx_peripheral,
        core::Allocator& dma_allocator
    );

    core::Status Initialize(core::units::Hertz peripheral_frequency);

    core::Status Configure(uint32_t baud_rate, bool parity, uint8_t stop_bits) override;
    core::Status Enqueue(core::Span<DataUnit> const& data) override;
    core::Status Dequeue(core::Span<DataUnit>& data) override;

    void HandleInterrupt(void);

protected:
    /// The UART peripheral
    registers::UniversalAsynchronousReceiverTransmitter volatile& uart_;
    /// The DMA Driver
    dma::Driver& dma_driver_;
    /// The RX peripheral for the DMA Driver
    dma::Peripheral rx_peripheral_;
    registers::DirectMemoryAccess::Stream volatile& rx_dma_stream_;
    size_t rx_dma_stream_index_;
    /// The TX peripheral for the DMA Driver
    dma::Peripheral tx_peripheral_;
    registers::DirectMemoryAccess::Stream volatile& tx_dma_stream_;
    size_t tx_dma_stream_index_;
    /// @brief The Allocator for use with DMA memory
    core::Allocator& dma_allocator_;
    /// The peripheral clock frequency
    core::units::Hertz peripheral_frequency_;
};

}    // namespace stm32
#endif    // STM32_UART_DRIVER_HPP
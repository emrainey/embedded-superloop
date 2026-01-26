#ifndef STM32_USART_DRIVER_HPP
#define STM32_USART_DRIVER_HPP

#include <core/Allocator.hpp>
#include <core/Buffer.hpp>
#include <core/Statistician.hpp>
#include <jarnax/usart/Driver.hpp>
#include "stm32/dma/Manager.hpp"
#include "stm32/peripherals/UniversalSynchronousAsynchronousReceiverTransmitter.hpp"

namespace stm32 {
namespace usart {

/// @brief The statistics structure for the USART
struct Statistics {
    uint32_t overrun_error{0U};               ///< The number of overrun errors
    uint32_t framing_error{0U};               ///< The number of framing errors
    uint32_t noise_error{0U};                 ///< The number of noise errors
    uint32_t parity_error{0U};                ///< The number of parity errors

    uint32_t idle{0U};                        ///< The number of idle interrupts
    uint32_t receive_buffer_not_empty{0U};    ///< The number of receive buffer not empty interrupts
    uint32_t transmit_buffer_empty{0U};       ///< The number of transmit buffer empty interrupts
    uint32_t transmit_complete{0U};           ///< The number of transmit complete interrupts
    uint32_t line_break_detection{0U};        ///< The number of line break detection interrupts
    uint32_t clear_to_send{0U};               ///< The number of clear to send interrupts

    uint32_t bytes_received{0U};              ///< The number of bytes received
    uint32_t bytes_transmitted{0U};           ///< The number of bytes transmitted
};

/// @brief STM32 USART peripheral driver implementation
/// @details Provides DMA-enabled USART communication for STM32 microcontrollers.
/// Implements the jarnax::usart::Driver interface with STM32-specific hardware control.
class Driver final : public jarnax::usart::Driver, public core::Statistician<Statistics> {
public:
    /// @brief Constructor
    /// @param uart The UART peripheral to use
    /// @param dma_driver The DMA Driver to use
    /// @param rx_peripheral The RX peripheral for the DMA Driver
    /// @param tx_peripheral The TX peripheral for the DMA Driver
    /// @param dma_allocator The Allocator to use for DMA memory
    /// @param dma_allocation_size The size of the DMA allocation to use
    Driver(
        peripherals::UniversalSynchronousAsynchronousReceiverTransmitter volatile& uart, dma::Manager& dma_driver, cortex::Peripheral rx_peripheral,
        cortex::Peripheral tx_peripheral, core::Allocator& dma_allocator, std::size_t dma_allocation_size
    );

    ~Driver() = default;

    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    // Jarnax::Driver Interface
    core::Status Initialize(void) override;
    bool Execute(void) override;
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

    /// @brief Initializes the USART Driver
    /// @param peripheral_frequency The frequency of the peripheral
    /// @return The status of the initialization
    core::Status Initialize(core::units::Hertz peripheral_frequency);

    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    // Jarnax::usart::Driver Interface
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    core::Status Configure(uint32_t baud_rate, bool parity, uint8_t stop_bits) override;
    core::Status Enqueue(core::Span<DataUnit const> const& data) override;
    core::Status Dequeue(core::Span<DataUnit>& data) override;

    /// @brief Handles the USART interrupt(s)
    void HandleInterrupt(void);

protected:
    /// @brief Computes the dividers and sets them for the given baud rate
    /// @details The divider is computed as follows:
    ///          divider = peripheral_frequency / (baud_rate * OVER8)
    /// @param baud_rate The desired baud rate
    void ComputeBaudRate(uint32_t baud_rate) const;

    /// @brief Reads the current baud rate from the dividers and given the peripheral frequency, computes the baud rate
    /// @return Returns the current baud rate as specified through the registers
    uint32_t GetBaudRate(void) const;

    /// The USART peripheral
    peripherals::UniversalSynchronousAsynchronousReceiverTransmitter volatile& usart_;
    /// The DMA Manager
    jarnax::dma::Manager& dma_manager_;
    /// The RX peripheral for the DMA Driver
    cortex::Peripheral rx_peripheral_;
    /// @brief The RX DMA Stream
    jarnax::dma::Resource* rx_dma_resource_;
    /// The TX peripheral for the DMA Driver
    cortex::Peripheral tx_peripheral_;
    /// @brief The TX DMA Stream
    jarnax::dma::Resource* tx_dma_resource_;
    /// @brief The Allocator for use with DMA memory
    core::Allocator& dma_allocator_;
    /// The peripheral clock frequency
    core::units::Hertz peripheral_frequency_;
    /// The RX DMA Buffer
    core::Buffer<DataUnit> rx_dma_buffer_;
    /// @brief The mutable span to access the RX DMA Buffer
    core::Span<DataUnit> rx_span_;
    /// The TX DMA Buffer
    core::Buffer<DataUnit> tx_dma_buffer_;
    /// The TX DMA Flag to indicate that a buffer is ready to be sent
    bool tx_ready_;
    /// The TX Span over the TX DMA Buffer which has data to send
    core::Span<DataUnit> tx_span_;
    /// The current index in the TX DMA Buffer
    size_t tx_index_;
};
}    // namespace usart
}    // namespace stm32
#endif    // STM32_USART_DRIVER_HPP

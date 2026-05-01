#ifndef BOARD_HPP_
#define BOARD_HPP_

/// @file
/// Contains configuration information for this specific board.

#include <cstdint>
#include <memory.hpp>
#include "configure.hpp"
#include "core/Units.hpp"
#include "iso.hpp"

// Pull in the Chip specific definitions
#include "stm32/stm32h753zi.hpp"

/// @internal Here we'll define boards specific sizes, speeds, clocks, features and settings.

namespace stm32 {    // Choices for STM32
using namespace core::units;
/// The HSE value for this board.
constexpr static Hertz high_speed_external_oscillator_frequency = 0_MHz;
/// The LSE value for this board.
constexpr static Hertz low_speed_external_oscillator_frequency{32768U};    // 32_KiHz
/// @brief The desired frequency of the Timer2 counter
constexpr static Hertz timer2_frequency = 40_MHz;
/// @brief The external PHY clock frequency
constexpr static Hertz external_phy_clock_frequency = 25_MHz;
/// Number of bytes per DMA block for the Drivers
constexpr static size_t DmaBlockSize{64U};
/// Number of DMA blocks for the Drivers
constexpr static size_t DmaBlockCount{32U};

/// The Baud Rate for the USART3
constexpr static std::uint32_t usart3_baud_rate = 230400U;
/// The Bus Rate for the I2C1 (I2C A)
constexpr static core::units::Hertz i2c1_bus_frequency = 400_KHz;
/// The Bus Rate for the I2C2 (I2C B)
constexpr static core::units::Hertz i2c2_bus_frequency = 400_KHz;
/// The SPI1 External Frequency
constexpr static core::units::Hertz spi1_bus_frequency = 1_MHz;
/// The UxART DMA Buffer Size
constexpr static std::uint32_t uart_dma_buffer_size = 128U;
/// The UxART DMA Buffer Size
constexpr static std::uint32_t usart_dma_buffer_size = 128U;
/// The I2C DMA Buffer Size
constexpr static std::uint32_t i2c_dma_buffer_size = 256U;
/// The SPI1 DMA Buffer Size
constexpr static std::uint32_t spi1_dma_buffer_size = 256U;
}    // namespace stm32

#endif    // BOARD_HPP_

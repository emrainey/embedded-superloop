#ifndef BOARD_HPP_
#define BOARD_HPP_

/// @file
/// Contains configuration information for this specific board.

#include <array>
#include <cstdint>
#include "configure.hpp"
#include "core/Units.hpp"
#include "iso.hpp"
#include "memory.hpp"

#include "jarnax/net/eui/Address.hpp"

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
/// @brief Select Ethernet PHY interface mode at compile time (true: RMII, false: MII)
constexpr static bool use_rmii_for_ethernet = true;
/// @brief The RMII reference clock frequency (PHY is fed 25 MHz and doubles it to 50 MHz)
constexpr static Hertz rmii_reference_clock_frequency = 50_MHz;
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
/// The Ethernet DMA Block Size (a frame and should be multiple of the align size on the platform)
constexpr static std::uint32_t ethernet_dma_block_size = 2048U;
/// The Ethernet DMA Block Count (more frames mean smore responsiveness)
constexpr static std::uint32_t ethernet_dma_block_count = 16U;
/// The Ethernet DMA Buffer Size (should be enough for N frames of 2048 bytes each)
constexpr static std::uint32_t ethernet_dma_buffer_size = ethernet_dma_block_size * ethernet_dma_block_count;
/// The Default Mac Address for the Ethernet Driver
constexpr static jarnax::net::eui48::Address default_mac_address{0x02, 0x00, 0x00, 0x00, 0x00, 0x01};
/// @brief Default MAC link speed before PHY auto-negotiation completes (true = 100 Mbps)
/// @note The LAN8742A will call ConfigureMacLink again with the negotiated values once the link is up.
constexpr static bool ethernet_default_speed_100m = true;
/// @brief Default MAC duplex mode before PHY auto-negotiation completes (true = full duplex)
constexpr static bool ethernet_default_full_duplex = true;
}    // namespace stm32

#endif    // BOARD_HPP_

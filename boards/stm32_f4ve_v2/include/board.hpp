#ifndef BOARD_HPP_
#define BOARD_HPP_

/// @file
/// Contains configuration information for this specific board.

#include <cstdint>
#include "iso.hpp"
#include <memory.hpp>
#include "core/Units.hpp"

// Pull in the Chip specific definitions
#include "stm32/stm32f407ve.hpp"

/// @internal Here we'll define boards specific sizes, speeds, clocks, features and settings.

/// RTT features
namespace rtt {
using iso::operator""_KiB;
/// The size of the buffer to send to the RTT Host
constexpr static size_t kUpwardBufferSize{4_KiB};
/// The size of the buffer to receive from the RTT Host
constexpr static size_t kDownwardBufferSize{16u};
}    // namespace rtt

namespace jarnax {    // Choices for Jarnax
constexpr static bool use_rtt_for_printf = true;
constexpr static bool use_swo_for_printf = false;
constexpr static bool use_uart_for_printf = false;
constexpr static bool use_logger_for_printf = false;
namespace debug {
constexpr static bool i2c{true};
constexpr static bool i2c_isr{false};
constexpr static bool spi{true};
constexpr static bool spi_isr{true};
constexpr static bool usart{true};
constexpr static bool usart_isr{false};
constexpr static bool dma{true};
constexpr static bool dma_isr{false};
}    // namespace debug
}    // namespace jarnax

namespace cortex {
/// Control SWO features
namespace swo {
/// The flag to control enabling the SWO and TPIU/ITM
constexpr static bool enable{false};
/// The desired SWO baudrate
constexpr static std::size_t baudrate{50'000U};
}    // namespace swo
}    // namespace cortex

namespace stm32 {    // Choices for STM32
using namespace core::units;
/// The HSE value for this board.
constexpr static Hertz high_speed_external_oscillator_frequency = 8_MHz;
/// The LSE value for this board.
constexpr static Hertz low_speed_external_oscillator_frequency{32768U};    // 32_KiHz
/// @brief The desired frequency of the Timer2 counter
constexpr static Hertz timer2_frequency = 12_MHz;
/// The Timer2 Reload value
constexpr static std::uint32_t timer2_reload_value = 12'000'000U;    // 1 second
/// Number of bytes per DMA block for the Drivers
constexpr static size_t DmaBlockSize{64U};
/// Number of DMA blocks for the Drivers
constexpr static size_t DmaBlockCount{32U};

/// The Baud Rate for the USART1
constexpr static std::uint32_t usart1_baud_rate = 230400U;
/// The Bus Rate for the I2C1
constexpr static core::units::Hertz i2c1_bus_frequency = 400_KHz;
/// The SPI2 External Frequency
constexpr static core::units::Hertz spi2_bus_frequency = 6_MHz;    // should get the /8
/// The UxART TX DMA Buffer Size
constexpr static std::uint32_t usart_tx_dma_buffer_size = 128U;
/// The UxART RX DMA Buffer Size
constexpr static std::uint32_t usart_rx_dma_buffer_size = 128U;
/// The I2C DMA Buffer Size
constexpr static std::uint32_t i2c_dma_buffer_size = 256U;
/// The SPI2 DMA Buffer Size
constexpr static std::uint32_t spi2_dma_buffer_size = 256U;
/// The USART TX DMA Switch
constexpr static bool use_dma_for_usart_tx{false};
/// The USART RX DMA Switch
constexpr static bool use_dma_for_usart_rx{false};
/// Enables use of the DMA for SPI transfers
constexpr static bool use_dma_for_spi{false};
/// Enables use of the DMA for I2C transfers
constexpr static bool use_dma_for_i2c{false};
}    // namespace stm32

namespace core {
namespace units {
/// @brief The number of Ticks in a second for this board
constexpr static std::uint32_t ticks_per_second{128U};
/// @brief Defines the system tick period value used to represent the passage of time in floats
constexpr static float tick_period{1.0F / ticks_per_second};
/// @brief The number of iota per second (based on the ClockTree)
constexpr static std::uint32_t iota_per_microsecond = stm32::timer2_frequency.value() / 1'000'000U;
/// @brief The number of iota per second (based on the ClockTree)
constexpr static std::uint32_t iota_per_millisecond = stm32::timer2_frequency.value() / 1'000U;
/// @brief The number of iota per second (based on the ClockTree)
constexpr static std::uint32_t iota_per_second = stm32::timer2_frequency.value() / 1U;
}    // namespace units
}    // namespace core

// This depends on the board specific stated conversions above
#include "core/Conversions.hpp"

namespace winbond {
using iso::operator""_MiB;
using core::units::operator""_MHz;
/// The size of the flash chip in bytes
constexpr static std::size_t flash_size = 16_MiB;
/// @brief The maximum clock frequency of the SPI bus for Read Operations on the Flash W25Q16JV
constexpr static core::units::Hertz spi_bus_frequency{21_MHz};
}    // namespace winbond

#endif    // BOARD_HPP_

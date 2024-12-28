#ifndef BOARD_HPP_
#define BOARD_HPP_

/// @file
/// Contains configuration information for the board.

#include <cstdint>
#include "iso.hpp"
#include "core/Status.hpp"
#include "core/Units.hpp"
#include "jarnax/Ticker.hpp"
#include "stm32/stm32f407ve.hpp"
#include "stm32/Timer.hpp"
#include "stm32/Button.hpp"
#include "stm32/Indicator.hpp"
#include "stm32/SpiDriver.hpp"
#include "stm32/RandomNumberGenerator.hpp"

/// RTT features
namespace rtt {
/// The size of the buffer to send to the RTT Host
constexpr static size_t kUpwardBufferSize{4096u};
/// The size of the buffer to receive from the RTT Host
constexpr static size_t kDownwardBufferSize{16u};
}    // namespace rtt

namespace jarnax {    // Choices for Jarnax
/// Alias the namespace from STM32 as our vendor
constexpr static bool use_rtt_for_printf = true;
constexpr static bool use_swo_for_printf = false;
}    // namespace jarnax

namespace stm32 {    // Choices for STM32
using namespace core::units;
/// The HSE value for this board.
constexpr static Hertz high_speed_external_oscillator_frequency = 8_MHz;
/// The number of iota per second (based on the ClockTree)
constexpr static std::uint32_t iota_per_microsecond = 1U;
}    // namespace stm32

namespace winbond {
using iso::operator""_MiB;
using core::units::operator""_MHz;
/// The size of the flash chip in bytes
constexpr static std::size_t flash_size = 16_MiB;
/// @brief The maximum clock frequency of the SPI bus for Read Operations on the Flash W25Q16JV
constexpr static core::units::Hertz spi_clock_frequency{50_MHz};
}    // namespace winbond

namespace jarnax {

/// @brief The Container pf the Board Specific Drivers and Configuration
/// @TODO Break these up into functional groups for better organization
class DriverContext {
public:
    /// The default constructor
    DriverContext();
    /// Initialization after Construction
    core::Status Initialize(void);
    /// The copy constructor
    DriverContext(DriverContext const&) = delete;
    /// The copy assignment operator
    DriverContext& operator=(DriverContext const&) = delete;
    /// The move constructor
    DriverContext(DriverContext&&) = delete;
    /// The move assignment operator
    DriverContext& operator=(DriverContext&&) = delete;

    /// Returns a reference to the Timer
    jarnax::Timer& GetTimer();

    /// Returns a reference to the Random Number Generator
    jarnax::RandomNumberGenerator& GetRandomNumberGenerator();

    /// Returns the Error Indicator
    jarnax::Indicator& GetErrorIndicator();

    /// Returns the Status Indicator
    jarnax::Indicator& GetStatusIndicator();

    /// Returns the Wakeup Pin
    jarnax::Button& GetWakeupButton();

    /// Returns the Key0 Button
    jarnax::Button& GetButton0();

    /// Returns the Key1 Button
    jarnax::Button& GetButton1();

    /// Returns the Copier
    jarnax::Copier& GetCopier();

    /// Returns the SPI Driver
    jarnax::spi::Driver& GetSpiDriver();

    /// Returns the Flash Chip Select
    jarnax::gpio::Output& GetFlashChipSelect();

protected:
    stm32::Timer timer_;
    /// The Random Number Generator
    stm32::RandomNumberGenerator random_number_generator_;
    stm32::gpio::Pin wakeup_pin_;
    stm32::gpio::Pin mc0_pin_;    ///< Clock output
    stm32::gpio::Pin key0_pin_;
    stm32::gpio::Pin key1_pin_;
    stm32::gpio::Pin error_pin_;
    stm32::gpio::Pin status_pin_;
    /// The Error Indicator
    stm32::Indicator error_indicator_;
    /// The Status Indicator
    stm32::Indicator status_indicator_;
    stm32::Button wakeup_button_;
    stm32::Button key0_button_;
    stm32::Button key1_button_;
    /// The SPI and related pins
    stm32::gpio::Pin spi1_mosi_;
    stm32::gpio::Pin spi1_miso_;
    stm32::gpio::Pin spi1_sclk_;
    stm32::gpio::Pin flash_cs_;
    stm32::gpio::Pin nrf_cs_;
    stm32::gpio::Pin nrf_ce_;
    stm32::gpio::Pin nrf_irq_;
    /// The DMA Driver
    stm32::dma::Driver dma_driver_;
    /// The SPI Driver
    stm32::registers::DirectMemoryAccess::Stream volatile* spi1_rx_dma_stream_;
    stm32::registers::DirectMemoryAccess::Stream volatile* spi1_tx_dma_stream_;
    stm32::SpiDriver spi1_driver_;
};

/// Gets the reference to the DriverContext
DriverContext& GetDriverContext();
}    // namespace jarnax

#endif    // BOARD_HPP_

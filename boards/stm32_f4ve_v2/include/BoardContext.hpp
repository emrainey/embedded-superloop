#ifndef STM32_F4VE_V2_INCLUDE_BOARD_CONTEXT_HPP_
#define STM32_F4VE_V2_INCLUDE_BOARD_CONTEXT_HPP_

/// @file
/// The Board Context for the STM32 F4VE V2 Board

#include "board.hpp"

#include "core/BitMapHeap.hpp"
#include "jarnax.hpp"
#include "jarnax/console/UsartConsole.hpp"
#include "jarnax/winbond/Driver.hpp"
#include "stm32/Button.hpp"
#include "stm32/Indicator.hpp"
#include "stm32/RandomNumberGenerator.hpp"
#include "stm32/Timer.hpp"
#include "stm32/i2c/Driver.hpp"
#include "stm32/spi/Driver.hpp"
#include "stm32/uart/Driver.hpp"
#include "stm32/usart/Driver.hpp"

namespace jarnax {

/// @brief The Container pf the Board Specific Drivers and Services
/// @TODO Break these up into functional groups for better organization
/// @note All interfaces should be abstract, i.e. in jarnax Pure Virtual interfaces
class BoardContext {
public:
    /// The default constructor
    BoardContext();
    /// Initialization after Construction
    core::Status Initialize(void);
    /// The copy constructor
    BoardContext(BoardContext const&) = delete;
    /// The copy assignment operator
    BoardContext& operator=(BoardContext const&) = delete;
    /// The move constructor
    BoardContext(BoardContext&&) = delete;
    /// The move assignment operator
    BoardContext& operator=(BoardContext&&) = delete;
    /// Destructor
    ~BoardContext();

    /// Returns a reference to the Timer
    jarnax::Timer& GetTimer();

    /// Returns a reference to the Random Number Generator
    jarnax::RandomNumberGenerator& GetRandomNumberGenerator();

    /// Returns the Error Indicator
    jarnax::Indicator& GetErrorIndicator();

    /// Returns the Status Indicator
    jarnax::Indicator& GetStatusIndicator();

    /// Returns the Performance Indicator
    jarnax::Indicator& GetPerformanceIndicator();

    /// Returns the Timing Indicator
    jarnax::Indicator& GetTimingIndicator();

    /// Returns the Wakeup Pin
    jarnax::Button& GetWakeupButton();

    /// Returns the Key0 Button
    jarnax::Button& GetButton0();

    /// Returns the Key1 Button
    jarnax::Button& GetButton1();

    /// Returns the Copier
    jarnax::Copier& GetCopier();

    /// Returns the I2C Driver
    jarnax::i2c::Driver& GetI2cDriver();

    /// Returns the SPI Driver
    jarnax::spi::Driver& GetSpiDriver();

    /// Returns the SPI Driver
    jarnax::spi::Driver& GetSpi2Driver();

    /// Returns the debug USART Driver
    jarnax::usart::Driver& GetCameraUsart();

    /// Returns the Flash Chip Select
    jarnax::gpio::Output& GetFlashChipSelect();

    /// Returns the DMA Allocator
    core::Allocator& GetDmaAllocator();

    /// Returns the Winbond Driver
    jarnax::winbond::Driver& GetWinbondDriver();

    /// Return the Console Service
    jarnax::console::Service& GetConsole();

protected:
    stm32::Timer timer_;
    /// The Random Number Generator
    stm32::RandomNumberGenerator random_number_generator_;
    stm32::gpio::Pin wakeup_pin_;         ///< The Wakeup Button Pin
    stm32::gpio::Pin mco1_pin_;           ///< Clock output
    stm32::gpio::Pin mco2_pin_;           ///< Clock output
    stm32::gpio::Pin key0_pin_;           ///< The Key0 Pin
    stm32::gpio::Pin key1_pin_;           ///< The Key1 Pin
    stm32::gpio::Pin error_pin_;          ///< The Error Pin
    stm32::gpio::Pin status_pin_;         ///< The Status Pin
    stm32::gpio::Pin performance_pin_;    ///< The Performance Pin
    stm32::gpio::Pin timing_pin_;         ///< The Timing Pin (for debugging)
    /// The Error Indicator
    stm32::Indicator error_indicator_;
    /// The Status Indicator
    stm32::Indicator status_indicator_;
    /// The Performance Indicator
    stm32::Indicator performance_indicator_;
    /// The timing indicator
    stm32::Indicator timing_indicator_;
    /// @brief The Wakeup Button
    stm32::Button wakeup_button_;
    /// @brief The Key0 Button
    stm32::Button key0_button_;
    /// @brief The Key1 Button
    stm32::Button key1_button_;
    /// The SPI1 Leader Out Follower In (MOSI)
    stm32::gpio::Pin spi1_mosi_;
    /// The SPI1 Master In Slave Out (MISO)
    stm32::gpio::Pin spi1_miso_;
    /// The SPI1 Serial Clock (SCLK)
    stm32::gpio::Pin spi1_sclk_;
    /// The Flash Chip Select (CS)
    stm32::gpio::Pin flash_cs_;
    /// Near Field Chip Select
    stm32::gpio::Pin nrf_cs_;
    /// Near Field Chip Enable
    stm32::gpio::Pin nrf_ce_;
    /// Near Field Interrupt Line
    stm32::gpio::Pin nrf_irq_;
    /// The SPI1 Leader Out Follower In (SPI2_MOSI -> T_MOSI)
    stm32::gpio::Pin spi2_mosi_;
    /// The SPI1 Master In Slave Out (SPI2_MISO -> T_MISO)
    stm32::gpio::Pin spi2_miso_;
    /// The SPI1 Serial Clock (SPI2_SCLK -> T_SCK)
    stm32::gpio::Pin spi2_sclk_;
    /// The TFT Screen Chip Select (T_CS)
    stm32::gpio::Pin spi2_nss_;
    /// The DMA Manager
    stm32::dma::Manager dma_manager_;
    /// The I2C Clock (SCL)
    stm32::gpio::Pin i2c1_scl_;
    /// The I2C Data (SDA)
    stm32::gpio::Pin i2c1_sda_;
    /// The I2C Driver
    stm32::i2c::Driver i2c1_driver_;
    /// The SPI1 Driver
    stm32::spi::Driver spi1_driver_;
    /// The SPI2 Driver
    stm32::spi::Driver spi2_driver_;
    /// The Winbond Driver
    jarnax::winbond::Driver winbond_driver_;
    /// USART1 Transmit Pin
    stm32::gpio::Pin usart1_tx_;
    /// USART1 Receive Pin
    stm32::gpio::Pin usart1_rx_;
    /// USART1 Driver
    stm32::usart::Driver usart1_driver_;
    /// Console Driver
    jarnax::console::UsartConsole usart_console_;
};

/// Gets the reference to the BoardContext
BoardContext& GetBoardContext();

}    // namespace jarnax

#endif    // STM32_F4VE_V2_INCLUDE_BOARD_CONTEXT_HPP_

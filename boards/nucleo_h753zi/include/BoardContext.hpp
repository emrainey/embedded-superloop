#ifndef NUCLEO_H753ZI_INCLUDE_BOARD_CONTEXT_HPP_
#define NUCLEO_H753ZI_INCLUDE_BOARD_CONTEXT_HPP_

/// @file
/// The Board Context for the STM32 H7532 V2 Board

#include "board.hpp"

#include "core/BitMapHeap.hpp"
#include "jarnax.hpp"
#include "jarnax/console/UsartConsole.hpp"
#include "jarnax/drivers/lps35hw/Driver.hpp"
#include "jarnax/drivers/lsm9ds1/Driver.hpp"
#include "jarnax/gpio/Output.hpp"
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

    /// Returns the User Button
    jarnax::Button& GetUserButton();

    /// Returns the Copier
    jarnax::Copier& GetCopier();

    /// Returns the I2C Driver
    jarnax::i2c::Driver& GetI2cA();

    /// Returns the I2C Driver
    jarnax::i2c::Driver& GetI2cB();

    /// Returns the SPI Driver
    jarnax::spi::Driver& GetSpiA();

    /// Returns the debug USARTB Driver
    jarnax::usart::Driver& GetUsartB();

    /// Returns the DMA Allocator
    core::Allocator& GetDmaAllocator();

    /// Return the Console Service
    jarnax::console::Service& GetConsole();

    /// Return the Ethernet Driver
    // jarnax::net::ethernet::Driver& GetEthernet();

protected:
    stm32::Timer timer_;
    /// The Random Number Generator
    stm32::RandomNumberGenerator random_number_generator_;
    stm32::gpio::Pin mco1_pin_;           ///< Clock output
    stm32::gpio::Pin mco2_pin_;           ///< Clock output
    stm32::gpio::Pin user_button_pin_;    ///< The User Button Pin
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
    /// @brief The User Button
    stm32::Button user_button_;
    /// The DMA Manager
    stm32::dma::Manager dma_manager_;
    /// The I2C Clock (SCL)
    stm32::gpio::Pin i2c1_scl_;
    /// The I2C Data (SDA)
    stm32::gpio::Pin i2c1_sda_;
    /// The I2C Driver
    stm32::i2c::Driver i2c1_driver_;
    /// The I2C Clock (SCL)
    stm32::gpio::Pin i2c2_scl_;
    /// The I2C Data (SDA)
    stm32::gpio::Pin i2c2_sda_;
    // The I2C SMBus Alert (SMBA)
    stm32::gpio::Pin i2c2_smba_;
    /// The I2C Driver
    stm32::i2c::Driver i2c2_driver_;
    /// The SPI1 Leader Out Follower In (MOSI)
    stm32::gpio::Pin spi1_mosi_;
    /// The SPI1 Master In Slave Out (MISO)
    stm32::gpio::Pin spi1_miso_;
    /// The SPI1 Serial Clock (SCLK)
    stm32::gpio::Pin spi1_sclk_;
    /// The Flash Chip Select (CS)
    stm32::gpio::Pin spi1_cs_;
    /// The SPI1 Driver
    stm32::spi::Driver spi1_driver_;
    /// USART3 Transmit Pin
    stm32::gpio::Pin usart3_tx_;
    /// USART3 Receive Pin
    stm32::gpio::Pin usart3_rx_;
    /// USART3 Driver
    stm32::usart::Driver usart3_driver_;
    /// Console Driver
    jarnax::console::UsartConsole usart_console_;
    /// ETH RMII Reference Clock (PA1, AF11)
    stm32::gpio::Pin eth_ref_clk_;
    /// ETH RMII MDIO (PA2, AF11) — JP6 must be ON
    stm32::gpio::Pin eth_mdio_;
    /// ETH RMII CRS_DV (PA7, AF11)
    stm32::gpio::Pin eth_crs_dv_;
    /// ETH RMII TXD1 (PB13, AF11) — JP7 must be ON
    stm32::gpio::Pin eth_txd1_;
    /// ETH RMII MDC (PC1, AF11)
    stm32::gpio::Pin eth_mdc_;
    /// ETH RMII RXD0 (PC4, AF11)
    stm32::gpio::Pin eth_rxd0_;
    /// ETH RMII RXD1 (PC5, AF11)
    stm32::gpio::Pin eth_rxd1_;
    /// ETH RMII TX_EN (PG11, AF11)
    stm32::gpio::Pin eth_tx_en_;
    /// ETH RMII TXD0 (PG13, AF11)
    stm32::gpio::Pin eth_txd0_;
};

/// Gets the reference to the BoardContext
BoardContext& GetBoardContext();

}    // namespace jarnax

#endif    // NUCLEO_H753ZI_INCLUDE_BOARD_CONTEXT_HPP_

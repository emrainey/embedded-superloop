#ifndef STM32_H_
#define STM32_H_

#include "cortex/vendor.hpp"
#include "stm32/registers/Debug.hpp"
#include "stm32/registers/ResetAndClockControl.hpp"
#include "stm32/registers/RandomNumberGenerator.hpp"
#include "stm32/registers/GeneralPurposeInputOutput.hpp"
#include "stm32/registers/FlashControl.hpp"
#include "stm32/registers/Timer2.hpp"
#include "stm32/registers/DirectMemoryAccess.hpp"
#include "stm32/registers/SerialPeripheralInterface.hpp"

/// The ST Micro 32 Namespace
namespace stm32 {

using Hertz = cortex::Hertz;

// The STM32 Clock Tree frequencies
struct ClockTree {
    Hertz low_speed_internal;
    Hertz low_speed_external;
    Hertz high_speed_internal;
    Hertz high_speed_external;
    Hertz pll_input;          ///< The frequency of the input to the PLL
    Hertz pll_vco;            ///< The frequency of the VCO
    Hertz pll_output;         ///< The frequency of the PLL output
    Hertz sysclk;             ///< the clock before the AHB/APB divider
    Hertz eth_ptp;            ///< The frequency of the Ethernet PTP clock
    Hertz fclk;               ///< The frequency of the cortex free running clock
    Hertz hclk;               ///< The frequency of the AHB bus, DMA and Core Memory (HCLK)
    Hertz system_timer;       ///< The frequency of the Cortex SYSTICK
    Hertz apbx_peripheral;    ///< The frequency of the APB1 bus (low speed)
    Hertz apbx_timer;         ///< The frequency of the APB2 bus (high speed)
    Hertz pll_i2s;
    Hertz pll_48ck;
    Hertz rtc;
    Hertz rng;
    Hertz usbotg;
    Hertz tim_clk;    ///< The frequency of the TIMx clocks  (TIMxCLK)
};

/// Returns what the vendor considers the frequency of the system.
/// @note Interface
ClockTree const& GetClockTree();

/// @brief Gets the clock frequency for the MCU
/// @return
Hertz& GetClockFrequency();

/// @brief Gets the system tick feeder clock frequency
Hertz& GetSystemClockFrequency();

/// Used to initialize chip specific drivers which need to be brought up very early.
namespace initialize {
/// @brief The required Clock initialization
/// @note Interface
void clocks();

/// @brief The required GPIO initialization
void gpio(void);

/// Initializes the Drivers for the STM32 namespace
void drivers(void);

}    // namespace initialize

/// @brief The STM32 clock configuration.
/// @note This does NOT map to hardware but it does have register values which will so we limit
/// their possible value ranges.
struct ClockConfiguration {
    bool use_internal;
    bool use_bypass;
    Hertz external_clock_frequency;
    //---
    std::uint32_t ahb_divider        : 4;
    std::uint32_t                    : 28;
    std::uint32_t low_speed_divider  : 3;
    std::uint32_t                    : 29;
    std::uint32_t high_speed_divider : 3;
    std::uint32_t                    : 29;
    std::uint32_t mcu_clock1_divider : 3;
    std::uint32_t                    : 29;
    std::uint32_t mcu_clock2_divider : 3;
    std::uint32_t                    : 29;
    std::uint32_t rtc_divider        : 5;
    std::uint32_t                    : 27;
    //---
    std::uint32_t pll_m              : 6;
    std::uint32_t                    : 32 - 6;
    std::uint32_t pll_n              : 9;
    std::uint32_t                    : 32 - 9;
    std::uint32_t pll_p              : 2;
    std::uint32_t                    : 32 - 2;
    std::uint32_t pll_q              : 4;
    std::uint32_t                    : 32 - 4;
};

// Vendor Chips declare this structure
extern ClockConfiguration const default_clock_configuration;

namespace initialize {
/// Initializes the Clock Tree
/// @param external_input_clock_frequency The clock frequency of the external clock (if present)
/// @param clkcfg The configuration of the clock for the system
void clocks(ClockConfiguration const& clkcfg);

/// @brief Vendor specific setup of NVIC for drivers
void nvic(void);
}    // namespace initialize

static constexpr bool has_been_set{true};

}    // namespace stm32

/// If you've included this header you want the stm32 namespace to be your vendor alias
namespace vendor = stm32;

static_assert(::vendor::has_been_set, "The STM32 Vendor has not been set");

#endif    // STM32_H_
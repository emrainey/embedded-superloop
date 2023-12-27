#ifndef STM32_H_
#define STM32_H_

#include "cortex/m4.hpp"
#include "stm32/registers/ResetAndClockControl.hpp"
#include "stm32/registers/RandomNumberGenerator.hpp"

/// The ST Micro 32 Namespace
namespace stm32 {

/// Returns what the vendor considers the frequency of the system.
/// @note Interface
uint32_t GetClockFrequency(void);

/// Used to initialize chip specific drivers which need to be brought up very early.
namespace initialize {

/// @brief The required Clock initialization
/// @note Interface
void clocks();

/// Initializes the Drivers for the STM32 namespace
void drivers(void);

}    // namespace initialize

/// @brief The STM32 clock configuration.
/// @note This does NOT map to hardware but it does have register values which will so we limit
/// their possible value ranges.
struct ClockConfiguration {
    bool use_internal;
    bool use_bypass;
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
};

// Vendor Chips declare this structure
extern ClockConfiguration const default_clock_configuration;

namespace initialize {
/// Initializes the Clock Tree
/// @param input_clock_frequency The desired system clock frequency
/// @param clkcfg The configuration of the clock for the system
void clocks(std::uint32_t input_clock_frequency, ClockConfiguration const& clkcfg);
}    // namespace initialize

}    // namespace stm32

#endif    // STM32_H_
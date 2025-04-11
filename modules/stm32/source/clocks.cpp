#include "core/core.hpp"
#include "core/Status.hpp"
#include "cortex/vectors.hpp"
#include "cortex/tick.hpp"

#include "board.hpp"    // Depends on the build

namespace stm32 {

/// Holds the clock tree values
stm32::ClockTree clock_tree;

stm32::ClockTree const& GetClockTree() {
    return clock_tree;
}

Hertz& GetClockFrequency() {
    return clock_tree.sysclk;
}

Hertz& GetSystemClockFrequency() {
    return clock_tree.system_timer;
}

namespace initialize {

/// @brief Counts how long it took for the high speed oscillator to stabilize (internal or external)
std::uint32_t high_speed_stabilization_counter{0U};
/// @brief Counts how long it took for the final PLL ready count to go around
std::uint32_t pll_clock_stabilization_counter{0u};
/// @brief Counts how long it took for the PLL to become system clock
std::uint32_t system_clock_switch_counter{0u};

void clocks() {
    auto& cfg = stm32::default_clock_configuration;
    if ((cfg.pll_m < 2 or 63 < cfg.pll_m) or (cfg.pll_n < 50 or 432 < cfg.pll_n) or (cfg.pll_q < 2 or 15 < cfg.pll_q)) {
        // The PLL values is out of range
        cortex::spinhalt();
    }
    clocks(cfg);
}

static std::uint32_t GetAHBDivider(std::uint32_t value) {
    switch (value) {
        case 0b0000:
            return 1U;
        case 0b0001:
            return 2U;
        case 0b0010:
            return 4U;
        case 0b0011:
            return 8U;
        case 0b0100:
            return 16U;
        case 0b0101:
            return 64U;
        case 0b0110:
            return 128U;
        case 0b0111:
            return 256U;
        case 0b1000:
            return 512U;
        default:
            return 1U;
    }
}

static std::uint32_t GetAPB1Divider(std::uint32_t value) {
    switch (value) {
        case 0b000:
            return 1U;
        case 0b100:
            return 2U;
        case 0b101:
            return 4U;
        case 0b110:
            return 8U;
        case 0b111:
            return 16U;
        default:
            return 1U;
    }
}

static std::uint32_t GetAPB2Divider(std::uint32_t value) {
    switch (value) {
        case 0b000:
            return 1U;
        case 0b100:
            return 2U;
        case 0b101:
            return 4U;
        case 0b110:
            return 8U;
        case 0b111:
            return 16U;
        default:
            return 1U;
    }
}

/// Initializes the Clock Tree with a given configuration (probably only works for STM32F407VE)
void clocks(ClockConfiguration const& clkcfg) {
    using namespace stm32::registers;
    using namespace core::units;

    if (reset_and_clock_control.configuration.bits.system_clock_switch_status ==
        ResetAndClockControl::Configuration::SystemClockSwitch::PhaseLockLoop) {
        // we're already using the PLL, so don't change anything
        return;
    }

    // Set the Flash Latency so that we can run at the top speed
    FlashControl::AccessControl access_control;
    access_control = flash_control.access_control;    // read
    access_control.bits.latency = 5U;
    access_control.bits.prefetch_enable = 1U;
    access_control.bits.instruction_cache_enable = 1U;
    access_control.bits.data_cache_enable = 1U;
    flash_control.access_control = access_control;    // write

    ResetAndClockControl::Control control;
    ResetAndClockControl::Configuration config;

    control = reset_and_clock_control.control;    // read
    if (clkcfg.use_internal) {
        control.bits.high_speed_external_bypass = 0;
        control.bits.high_speed_external_enable = 0;
        control.bits.high_speed_internal_enable = 1;
        clock_tree.pll_input = high_speed_internal_oscillator_frequency;
    } else {
        control.bits.high_speed_external_bypass = (clkcfg.use_bypass ? 1 : 0);
        control.bits.high_speed_external_enable = 1;
        control.bits.high_speed_internal_enable = 0;
        clock_tree.pll_input = clkcfg.external_clock_frequency;    // take from configuration
    }
    reset_and_clock_control.control = control;    // write

    if (clkcfg.use_internal) {
        do {
            control = reset_and_clock_control.control;    // read
            high_speed_stabilization_counter++;
        } while (control.bits.high_speed_internal_ready == 0);
    } else {
        do {
            control = reset_and_clock_control.control;    // read
            high_speed_stabilization_counter++;
        } while (control.bits.high_speed_external_ready == 0);
    }
    config.bits.system_clock_switch = stm32::registers::ResetAndClockControl::Configuration::SystemClockSwitch::PhaseLockLoop;    // switch to the PLL
    config.bits.ahb_divider = clkcfg.ahb_divider;
    config.bits.apb_low_speed_divider = clkcfg.low_speed_divider;
    config.bits.apb_high_speed_divider = clkcfg.high_speed_divider;
    if (clkcfg.use_internal) {
        config.bits.micro_controller_clock_1_source = ResetAndClockControl::Configuration::Clock1Source::HighSpeedInternal;
        config.bits.micro_controller_clock_1_divider = 0b111;    //  /5
    } else {
        config.bits.micro_controller_clock_1_source = ResetAndClockControl::Configuration::Clock1Source::HighSpeedExternal;
        config.bits.micro_controller_clock_1_divider = 0b111;    //  /5
    }
    config.bits.micro_controller_clock_1_divider = clkcfg.mcu_clock1_divider;
    config.bits.micro_controller_clock_2_source = ResetAndClockControl::Configuration::Clock2Source::PhaseLockLoop;
    config.bits.micro_controller_clock_2_divider = clkcfg.mcu_clock2_divider;
    config.bits.rtc_divider = clkcfg.rtc_divider;

    // Set the PLL Configuration
    ResetAndClockControl::PhaseLockLoopConfiguration pll_config;
    pll_config = reset_and_clock_control.pll_configuration;    // read
    pll_config.bits.main_pll_input_divisor = clkcfg.pll_m;
    pll_config.bits.main_pll_vco_scalar = clkcfg.pll_n;
    pll_config.bits.main_pll_divider = clkcfg.pll_p;
    pll_config.bits.main_pll_divider2 = clkcfg.pll_q;
    if (clkcfg.use_internal) {
        pll_config.bits.main_pll_source = ResetAndClockControl::PhaseLockLoopConfiguration::MainPLLSource::HighSpeedInternal;
    } else {
        pll_config.bits.main_pll_source = ResetAndClockControl::PhaseLockLoopConfiguration::MainPLLSource::HighSpeedExternal;
    }
    reset_and_clock_control.pll_configuration = pll_config;    // save value

    // save value
    reset_and_clock_control.configuration = config;

    control = reset_and_clock_control.control;    // read
    control.bits.main_pll_enable = 1U;            // enable PLL
    reset_and_clock_control.control = control;    // write

    // Wait for PLL Ready
    do {
        control = reset_and_clock_control.control;    // read
        pll_clock_stabilization_counter++;
    } while (control.bits.main_pll_ready == 0);

    // Choose the PLL as the system clock
    config = reset_and_clock_control.configuration;    // read
    config.bits.system_clock_switch = ResetAndClockControl::Configuration::SystemClockSwitch::PhaseLockLoop;
    reset_and_clock_control.configuration = config;    // write
    do {
        config = reset_and_clock_control.configuration;    // read
        system_clock_switch_counter++;
    } while (config.bits.system_clock_switch_status != ResetAndClockControl::Configuration::SystemClockSwitch::PhaseLockLoop);

    // Compute the Clock Tree values from what we just set
    clock_tree.low_speed_internal = 32_kHz;
    clock_tree.low_speed_external = Hertz{32768U};
    clock_tree.high_speed_internal = high_speed_internal_oscillator_frequency;
    clock_tree.high_speed_external = clkcfg.external_clock_frequency;

    std::uint32_t pllm = clkcfg.pll_m;
    std::uint32_t plln = clkcfg.pll_n;
    std::uint32_t pllp = (clkcfg.pll_p * 2U) + 2U;
    std::uint32_t pllq = clkcfg.pll_q;
    // VCO = F_in * (N/M) but if N *F_in is too large (exceeds 32 bits), then we need to divide first
    clock_tree.pll_vco = (clock_tree.pll_input / pllm) * plln;
    clock_tree.pll_output = clock_tree.pll_vco / pllp;
    clock_tree.pll_48ck = clock_tree.pll_vco / pllq;
    // we want to have the system clock be the
    clock_tree.sysclk = clock_tree.pll_output;
    clock_tree.eth_ptp = clock_tree.sysclk;
    clock_tree.fclk = clock_tree.sysclk / GetAHBDivider(clkcfg.ahb_divider);
    clock_tree.hclk = clock_tree.fclk;
    clock_tree.system_timer = clock_tree.fclk / 8U;
    clock_tree.apbx_peripheral = clock_tree.hclk / GetAPB1Divider(clkcfg.low_speed_divider);
    clock_tree.apbx_timer = clock_tree.hclk / GetAPB2Divider(clkcfg.high_speed_divider);
    clock_tree.rtc = clock_tree.high_speed_external / clkcfg.rtc_divider;
    clock_tree.tim_clk = clock_tree.hclk;
    // clock_tree.rng = clock_tree.sysclk;
}

}    // namespace initialize
}    // namespace stm32

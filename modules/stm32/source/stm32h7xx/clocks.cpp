#include "core/Status.hpp"
#include "core/core.hpp"
#include "cortex/halt.hpp"
#include "cortex/thumb.hpp"
#include "cortex/tick.hpp"
#include "cortex/vectors.hpp"
#include "stm32/Initialize.hpp"
#include "stm32/f4xx/ResetAndClockControl.hpp"
#include "stm32/h7xx/ResetAndClockControl.hpp"
#include "stm32/peripherals.hpp"

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

void clocks(void) {
    // @FIXME until I can figure out the linker problem, this has to be called here instead of in configure.cpp
    early_power();
    auto& cfg = stm32::default_clock_configuration;
    if ((cfg.pll_m < 1U or 63U < cfg.pll_m) or (cfg.pll_n < 4U or 512U < cfg.pll_n) or (cfg.pll_p < 1U or 128U < cfg.pll_p) or
        (cfg.pll_q < 1U or 128U < cfg.pll_q) or (cfg.pll_r < 1U or 128U < cfg.pll_r)) {
        // The PLL values is out of range
        cortex::spinhalt();
    }
    clocks(cfg);
}

static std::uint32_t GetAHBDivider(std::uint32_t value) {
    switch (value) {
        case 0b0000:
            return 1U;
        case 0b1000:
            return 2U;
        case 0b1001:
            return 4U;
        case 0b1010:
            return 8U;
        case 0b1011:
            return 16U;
        case 0b1100:
            return 64U;
        case 0b1101:
            return 128U;
        case 0b1110:
            return 256U;
        case 0b1111:
            return 512U;
        default:
            return 1U;
    }
}

static std::uint32_t GetD1CoreDivider(std::uint32_t value) {
    switch (value) {
        case 0b1000:
            return 2U;
        case 0b1001:
            return 4U;
        case 0b1010:
            return 8U;
        case 0b1011:
            return 16U;
        default:
            return 1U;
    }
}

static std::uint32_t GetAPBDivider(std::uint32_t value) {
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
    using namespace stm32::peripherals;
    using namespace core::units;
    constexpr std::uint32_t mco1_hsi = 0b000U;
    constexpr std::uint32_t mco1_hse = 0b010U;
    constexpr std::uint32_t mco2_system_clock = 0b000U;

    if (reset_and_clock_control.configuration.bits.system_clock_switch_status ==
        h7xx::ResetAndClockControl::Configuration::SystemClockSwitch::PhaseLockLoopClock) {
        // we're already using the PLL, so don't change anything
        return;
    }

    // Set flash wait states for high-speed operation before increasing clocks.
    FlashControl::AccessControl access_control;
    access_control = flash_control.access_control;    // read
    access_control.bits.latency = 5U;
    access_control.bits.wrhighfreq = 0b10U;
    flash_control.access_control = access_control;    // write

    ResetAndClockControl::Control control;
    ResetAndClockControl::Configuration config;
    ResetAndClockControl::Domain1ClockConfiguration d1cfg;
    ResetAndClockControl::Domain2ClockConfiguration d2cfg;
    ResetAndClockControl::Domain3ClockConfiguration d3cfg;
    ResetAndClockControl::PllClockSourceSelection pll_source;
    ResetAndClockControl::Pll1DividerConfiguration pll_divider;
    ResetAndClockControl::Pll1FractionalConfiguration pll_fractional;

    bool const use_hsi = (clkcfg.pll_source == 0U) or clkcfg.use_internal;
    bool const use_csi = (clkcfg.pll_source == 1U) or clkcfg.use_csi;
    bool const use_hse = (clkcfg.pll_source == 2U) or (not clkcfg.use_internal);

    control = reset_and_clock_control.control;    // read
    control.bits.high_speed_external_bypass = (use_hse and clkcfg.use_bypass) ? 1U : 0U;
    control.bits.high_speed_external_enable = use_hse ? 1U : 0U;
    control.bits.high_speed_internal_enable = use_hsi ? 1U : 0U;
    control.bits.low_power_internal_oscillator_enable = use_csi ? 1U : 0U;
    control.bits.pll1_enable = 0U;                // disable PLL1 before configuration
    reset_and_clock_control.control = control;    // write

    if (use_hsi) {
        do {
            control = reset_and_clock_control.control;    // read
            high_speed_stabilization_counter++;
        } while (control.bits.high_speed_internal_ready == 0);
    }
    if (use_hse) {
        do {
            control = reset_and_clock_control.control;    // read
            high_speed_stabilization_counter++;
        } while (control.bits.high_speed_external_ready == 0);
    }
    if (use_csi) {
        do {
            control = reset_and_clock_control.control;    // read
            high_speed_stabilization_counter++;
        } while (control.bits.low_power_internal_oscillator_ready == 0);
    }

    if (clkcfg.pll_source == 0U) {
        clock_tree.pll_input = high_speed_internal_oscillator_frequency;
    } else if (clkcfg.pll_source == 1U) {
        clock_tree.pll_input = calibrated_silicon_internal_oscillator_frequency;
    } else {
        clock_tree.pll_input = clkcfg.external_clock_frequency;
    }

    config = reset_and_clock_control.configuration;    // read
    config.bits.real_time_clock_prescaler = clkcfg.rtc_divider;
    config.bits.mco1_prescaler = clkcfg.mcu_clock1_divider;
    config.bits.mco1_selection = clkcfg.use_internal ? mco1_hsi : mco1_hse;
    config.bits.mco2_prescaler = clkcfg.mcu_clock2_divider;
    config.bits.mco2_selection = mco2_system_clock;

    d1cfg = reset_and_clock_control.domain1_clock_configuration;
    d1cfg.bits.domain1_core_prescaler = clkcfg.d1_core_prescaler;
    d1cfg.bits.ahb_prescaler = clkcfg.ahb_divider;
    d1cfg.bits.domain1_peripheral_prescaler = clkcfg.apb3_divider;

    d2cfg = reset_and_clock_control.domain2_clock_configuration;
    d2cfg.bits.domain2_peripheral1_prescaler = clkcfg.apb1_low_speed_divider;
    d2cfg.bits.domain2_peripheral2_prescaler = clkcfg.apb2_high_speed_divider;

    d3cfg = reset_and_clock_control.domain3_clock_configuration;
    d3cfg.bits.domain3_peripheral_prescaler = clkcfg.apb4_divider;

    pll_source = reset_and_clock_control.pll_clock_source_selection;
    pll_source.bits.main_pll_source = clkcfg.pll_source;
    pll_source.bits.pll1_input_divider = clkcfg.pll_m;

    // Set the PLL Configuration
    ResetAndClockControl::PhaseLockLoopConfiguration pll_config;
    pll_config = reset_and_clock_control.pll_configuration;    // read
    pll_config.bits.pll1_input_range =
        (clock_tree.pll_input.value() <= 2'000'000) ? 0b00U : ((clock_tree.pll_input.value() <= 4'000'000) ? 0b01U : 0b10U);
    pll_config.bits.divider_p1_enable = 1U;
    pll_config.bits.divider_q1_enable = 1U;
    pll_config.bits.divider_r1_enable = 1U;
    pll_config.bits.pll1_fractional_enable = clkcfg.use_pll_fracn ? 1U : 0U;

    pll_divider = reset_and_clock_control.pll1_divider_configuration;
    // the clock variables should be preadjusted
    pll_divider.bits.divider_n1 = clkcfg.pll_n;
    pll_divider.bits.divider_p1 = clkcfg.pll_p;
    pll_divider.bits.divider_q1 = clkcfg.pll_q;
    pll_divider.bits.divider_r1 = clkcfg.pll_r;

    pll_fractional = reset_and_clock_control.pll1_fractional_configuration;
    pll_fractional.bits.fractional_n1 = clkcfg.pll_fracn;

    // now write the values back in order
    reset_and_clock_control.pll_clock_source_selection = pll_source;
    reset_and_clock_control.pll_configuration = pll_config;
    reset_and_clock_control.pll1_divider_configuration = pll_divider;
    reset_and_clock_control.pll1_fractional_configuration = pll_fractional;

    reset_and_clock_control.domain1_clock_configuration = d1cfg;
    reset_and_clock_control.domain2_clock_configuration = d2cfg;
    reset_and_clock_control.domain3_clock_configuration = d3cfg;
    reset_and_clock_control.configuration = config;

    control = reset_and_clock_control.control;    // read
    control.bits.pll1_enable = 1U;                // enable PLL1
    reset_and_clock_control.control = control;    // write

    // Wait for PLL Ready
    do {
        control = reset_and_clock_control.control;    // read
        pll_clock_stabilization_counter++;
    } while (control.bits.pll1_ready == 0);

    // Choose PLL1 as the system clock
    config = reset_and_clock_control.configuration;        // read
    config.bits.system_clock_switch = h7xx::ResetAndClockControl::Configuration::SystemClockSwitch::PhaseLockLoopClock;
    reset_and_clock_control.configuration = config;        // write
    do {
        config = reset_and_clock_control.configuration;    // read
        system_clock_switch_counter++;
    } while (config.bits.system_clock_switch_status != h7xx::ResetAndClockControl::Configuration::SystemClockSwitch::PhaseLockLoopClock);

    // Compute the Clock Tree values from what we just set
    clock_tree.low_speed_internal = low_speed_internal_oscillator_frequency;
    clock_tree.low_speed_external = clkcfg.low_speed_external_oscillator_frequency;
    clock_tree.high_speed_internal = high_speed_internal_oscillator_frequency;
    clock_tree.high_speed_external = clkcfg.external_clock_frequency;

    std::uint32_t pllm = clkcfg.pll_m;
    std::uint32_t plln = clkcfg.pll_n + 1U;    // the actual multiplier is N+1
    std::uint32_t pllp = clkcfg.pll_p + 1U;
    std::uint32_t pllq = clkcfg.pll_q + 1U;
    std::uint32_t d1cpre = GetD1CoreDivider(clkcfg.d1_core_prescaler);
    std::uint32_t hpre = GetAHBDivider(clkcfg.ahb_divider);
    // VCO = F_in * (N/M) but if N *F_in is too large (exceeds 32 bits), then we need to divide first
    clock_tree.pll_vco = (clock_tree.pll_input / pllm) * plln;
    clock_tree.pll_output = clock_tree.pll_vco / pllp;
    clock_tree.pll_48ck = clock_tree.pll_vco / pllq;
    // SYSCLK is sourced from PLL1P.
    clock_tree.sysclk = clock_tree.pll_output;
    clock_tree.fclk = clock_tree.sysclk / d1cpre;
    clock_tree.system_timer = clock_tree.fclk / 8U;
    clock_tree.hclk = clock_tree.sysclk / hpre;
    clock_tree.ahb1_peripheral = clock_tree.hclk;    // Assuming AHB1 is directly derived from HCLK
    clock_tree.ahb2_peripheral = clock_tree.hclk;    // Assuming AHB2 is directly derived from HCLK
    clock_tree.ahb3_peripheral = clock_tree.hclk;    // Assuming AHB3 is directly derived from HCLK
    clock_tree.ahb4_peripheral = clock_tree.hclk;    // Assuming AHB4 is directly derived from HCLK
    clock_tree.apb1_peripheral = clock_tree.hclk / GetAPBDivider(clkcfg.apb1_low_speed_divider);
    clock_tree.apb2_peripheral = clock_tree.hclk / GetAPBDivider(clkcfg.apb2_high_speed_divider);
    clock_tree.apb3_peripheral = clock_tree.hclk / GetAPBDivider(clkcfg.apb3_divider);
    clock_tree.apb4_peripheral = clock_tree.hclk / GetAPBDivider(clkcfg.apb4_divider);
    clock_tree.eth_ptp = clock_tree.sysclk;
    clock_tree.rng = clock_tree.apb2_peripheral;
    clock_tree.rtc = clock_tree.high_speed_external / clkcfg.rtc_divider;
    clock_tree.apb1_timer_clk =
        clock_tree.apb1_peripheral * (GetAPBDivider(clkcfg.apb1_low_speed_divider) == 1 ? 1U : 2U);     // APB1 is doubled if the divider is not 1
    clock_tree.apb2_timer_clk =
        clock_tree.apb2_peripheral * (GetAPBDivider(clkcfg.apb2_high_speed_divider) == 1 ? 1U : 2U);    // APB2 is doubled if the divider is not 1
}

}    // namespace initialize
}    // namespace stm32

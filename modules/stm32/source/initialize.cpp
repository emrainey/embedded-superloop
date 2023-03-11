#include "core/core.hpp"
#include "jarnax/Status.hpp"
#include "jarnax/system.hpp"
#include "board.hpp"    // Depends on the build

namespace stm32 {

/// Storage location for the extended vector table.
ATTRIBUTE((used, section(".extended_vectors")))
ExternalInterrupts external_interrupts = {
    jarnax::handlers::dummy,    // 0
    jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy,
    jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy,
    jarnax::handlers::dummy,    // 9
    jarnax::handlers::dummy,    // 10
    jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy,
    jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy,
    jarnax::handlers::dummy,    // 19
    jarnax::handlers::dummy,    // 20
    jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy,
    jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy,
    jarnax::handlers::dummy,    // 29
    jarnax::handlers::dummy,    // 30
    jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy,
    jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy,
    jarnax::handlers::dummy,    // 39
    jarnax::handlers::dummy,    // 40
    jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy,
    jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy,
    jarnax::handlers::dummy,    // 49
    jarnax::handlers::dummy,    // 50
    jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy,
    jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy,
    jarnax::handlers::dummy,    // 59
    jarnax::handlers::dummy,    // 60
    jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy,
    jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy,
    jarnax::handlers::dummy,    // 69
    jarnax::handlers::dummy,    // 70
    jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy,
    jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy, jarnax::handlers::dummy,
    jarnax::handlers::dummy,    // 79
    jarnax::handlers::dummy,    // 80
    jarnax::handlers::dummy,
};

uint32_t GetClockFrequency(void) {
    return stm32::clock_frequency;
}

namespace initialize {

void clocks() {
    clocks(stm32::high_speed_external_oscillator_frequency, stm32::default_clock_configuration);
}

/// Initializes the Clock Tree with a given configuration
void clocks(std::uint32_t input_clock_frequency, ClockConfiguration const& clkcfg) {
    using namespace stm32::registers;
    (void)input_clock_frequency;
    /// Sequence
    /// * Enable and Ready HSE or HSI
    /// *

    ResetAndClockControl::Control control;
    ResetAndClockControl::Configuration config;

    control = reset_and_clock_control.control;    // read
    if (clkcfg.use_internal) {
        control.bits.high_speed_external_bypass = 0;
        control.bits.high_speed_external_enable = 0;
        control.bits.high_speed_internal_enable = 1;
    } else {
        control.bits.high_speed_external_bypass = (clkcfg.use_bypass ? 1 : 0);
        control.bits.high_speed_external_enable = 1;
        control.bits.high_speed_internal_enable = 0;
    }
    reset_and_clock_control.control = control;    // write

    if (clkcfg.use_internal) {
        while (reset_and_clock_control.control.bits.high_speed_internal_ready == 0) {
        }
    } else {
        while (reset_and_clock_control.control.bits.high_speed_external_ready == 0) {
        }
    }

    config.bits.system_clock_switch =
        stm32::registers::ResetAndClockControl::Configuration::SystemClockSwitch::PhaseLockLoop;    // switch to the PLL
    config.bits.ahb_divider = clkcfg.ahb_divider;
    config.bits.apb_low_speed_divider = clkcfg.low_speed_divider;
    config.bits.apb_high_speed_divider = clkcfg.high_speed_divider;
    if (clkcfg.use_internal) {
        config.bits.micro_controller_clock_1_source =
            ResetAndClockControl::Configuration::Clock1Source::HighSpeedInternal;
    } else {
        config.bits.micro_controller_clock_1_source =
            ResetAndClockControl::Configuration::Clock1Source::HighSpeedExternal;
    }
    config.bits.micro_controller_clock_1_divider = clkcfg.mcu_clock1_divider;
    config.bits.micro_controller_clock_2_source = ResetAndClockControl::Configuration::Clock2Source::PhaseLockLoop;
    config.bits.micro_controller_clock_2_divider = clkcfg.mcu_clock2_divider;
    config.bits.rtc_divider = clkcfg.rtc_divider;

    // save value
    reset_and_clock_control.configuration = config;
    reset_and_clock_control.control.bits.main_pll_enable = 1U;    // enable PLL
    while (reset_and_clock_control.control.bits.main_pll_ready == 0U) {
    }
}

}    // namespace initialize
}    // namespace stm32

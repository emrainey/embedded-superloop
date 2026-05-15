#include "core/Status.hpp"
#include "core/core.hpp"
#include "cortex/halt.hpp"
#include "cortex/thumb.hpp"
#include "stm32/Initialize.hpp"
#include "stm32/peripherals.hpp"
#include "stm32/stm32h7xx.hpp"

namespace stm32 {
namespace initialize {

/// @brief Counts how long voltage scaling took to report ready.
std::uint32_t voltage_scaling_ready_counter{0U};

void early_power(void) {
    // Enable Power clocks early
    stm32::h7xx::ResetAndClockControl::APB4ClockEnable apb4_enable;
    apb4_enable = stm32::h7xx::reset_and_clock_control.apb4_clock_enable;    // read
    apb4_enable.bits.vref_enable = 1U;                                       // modify
    stm32::h7xx::reset_and_clock_control.apb4_clock_enable = apb4_enable;    // write
    thumb::nop();                                                            // small delay to ensure write completes before next PWR access

    // @note This has to be correct the first time, as alterations require POWER CYCLES not Reset!
    h7xx::PowerController::Control3 pwr_control3;
    pwr_control3 = h7xx::power_controller.control3;               // read
    pwr_control3.bits.low_dropout_regulator_enable = 1U;          // modify
    pwr_control3.bits.supply_configuration_update_enable = 0U;    // modify
    h7xx::power_controller.control3 = pwr_control3;               // write

    // Configure D3 voltage scaling before clock ramp.
    h7xx::PowerController::Domain3Control pwr_d3_control;
    pwr_d3_control = h7xx::power_controller.domain3_control;
    pwr_d3_control.bits.voltage_scaling_selection = stm32::default_clock_configuration.voltage_scaling;
    h7xx::power_controller.domain3_control = pwr_d3_control;

    // Use CSR1.ACTVOSRDY for readiness: D3CR.VOSRDY may stay low for valid non-bypass supply modes.
    constexpr std::uint32_t max_wait_iterations = 1000000U;
    h7xx::PowerController::ContextSwap1 power_status;
    voltage_scaling_ready_counter = 0U;
    do {
        power_status = h7xx::power_controller.context_swap1;
        voltage_scaling_ready_counter++;
        if (voltage_scaling_ready_counter >= max_wait_iterations) {
            cortex::spinhalt();
        }
    } while (power_status.bits.active_voltage_scaling_ready == 0U);
}

}    // namespace initialize
}    // namespace stm32

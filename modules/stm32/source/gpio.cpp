#include "stm32/stm32.hpp"

namespace stm32 {
namespace initialize {

void gpio(void) {
    using namespace stm32::registers;
    // Enable GPIO Clocks
    ResetAndClockControl::AHB1PeripheralClockEnable ahb1_enable;
    ResetAndClockControl::AHB1PeripheralReset ahb1_reset;

    ahb1_enable = reset_and_clock_control.ahb1_peripheral_clock_enable;    // load
    ahb1_enable.bits.gpioaen = 1U;
    ahb1_enable.bits.gpioben = 1U;
    ahb1_enable.bits.gpiocen = 1U;
    ahb1_enable.bits.gpioden = 1U;
    ahb1_enable.bits.gpioeen = 1U;
    ahb1_enable.bits.gpiofen = 1U;
    ahb1_enable.bits.gpiogen = 1U;
    ahb1_enable.bits.gpiohen = 1U;
    ahb1_enable.bits.gpioien = 1U;
    reset_and_clock_control.ahb1_peripheral_clock_enable = ahb1_enable;    // store
    // Reset GPIO Ports
    ahb1_reset = reset_and_clock_control.ahb1_peripheral_reset;    // load
    ahb1_reset.bits.gpioarst = 1U;
    ahb1_reset.bits.gpiobrst = 1U;
    ahb1_reset.bits.gpiocrst = 1U;
    ahb1_reset.bits.gpiodrst = 1U;
    ahb1_reset.bits.gpioerst = 1U;
    ahb1_reset.bits.gpiofrst = 1U;
    ahb1_reset.bits.gpiogrst = 1U;
    ahb1_reset.bits.gpiohrst = 1U;
    ahb1_reset.bits.gpioirst = 1U;
    reset_and_clock_control.ahb1_peripheral_reset = ahb1_reset;    // store
    // Release GPIO Ports
    ahb1_reset.bits.gpioarst = 0U;
    ahb1_reset.bits.gpiobrst = 0U;
    ahb1_reset.bits.gpiocrst = 0U;
    ahb1_reset.bits.gpiodrst = 0U;
    ahb1_reset.bits.gpioerst = 0U;
    ahb1_reset.bits.gpiofrst = 0U;
    ahb1_reset.bits.gpiogrst = 0U;
    ahb1_reset.bits.gpiohrst = 0U;
    ahb1_reset.bits.gpioirst = 0U;
    reset_and_clock_control.ahb1_peripheral_reset = ahb1_reset;    // store
}

}    // namespace initialize
}    // namespace stm32
#include "board.hpp"
#include "segger/rtt.hpp"
#include "jarnax.hpp"
#include "stm32/RandomNumberGenerator.hpp"
#include "stm32/Timer.hpp"

namespace stm32 {

/// The Clock configuration for this board.
ClockConfiguration const default_clock_configuration = {
    /* .use_internal = */ false,
    /* .use_bypass = */ false,
    /* .external_clock_frequency */ high_speed_external_oscillator_frequency,
    /* .ahb_divider = */ 0b0000,          // /1
    /* .low_speed_divider = */ 0b101,     // /4
    /* .high_speed_divider = */ 0b100,    // /2
    /* .mcu_clock1_divider = */ 2,
    /* .mcu_clock2_divider = */ 2,
    /* .rtc_divider = */ 8,
    /* .pll_m = */ 8,
    /* .pll_n = */ 336,
    /* .pll_p = */ 0b00,    // /2
    /* .pll_q = */ 7
};

}    // namespace stm32

namespace jarnax {
DriverContext::DriverContext()
    : timer_{stm32::registers::timer2}
    , random_number_generator_{}
    , wakeup_pin_{stm32::gpio::Port::A, 0}
    , mc0_pin_{stm32::gpio::Port::A, 8}
    , key0_pin_{stm32::gpio::Port::E, 4}
    , key1_pin_{stm32::gpio::Port::E, 3}
    , error_pin_{stm32::gpio::Port::A, 6}
    , status_pin_{stm32::gpio::Port::A, 7}
    , error_indicator_{error_pin_, stm32::Level::Low}
    , status_indicator_{status_pin_, stm32::Level::Low}
    , wakeup_button_{wakeup_pin_, true}
    , key0_button_{key0_pin_, false}
    , key1_button_{key1_pin_, false}
    , spi1_mosi_{stm32::gpio::Port::B, 5}
    , spi1_miso_{stm32::gpio::Port::B, 4}
    , spi1_sclk_{stm32::gpio::Port::B, 3}
    , flash_cs_{stm32::gpio::Port::B, 0}
    , nrf_cs_{stm32::gpio::Port::B, 7}
    , nrf_ce_{stm32::gpio::Port::B, 6}
    , nrf_irq_{stm32::gpio::Port::B, 8}
    , spi1_driver_{stm32::registers::spi1} {
    // @todo initialize the driver objects
}

core::Status DriverContext::Initialize(void) {
    core::Status status;
    wakeup_pin_.SetMode(stm32::gpio::Mode::Input).SetResistor(stm32::gpio::Resistor::PullDown);
    mc0_pin_.SetOutputSpeed(stm32::gpio::Speed::VeryHigh).SetMode(stm32::gpio::Mode::AlternateFunction).SetAlternative(0);    // Alt 0 is MCO1
    key0_pin_.SetMode(stm32::gpio::Mode::Input).SetResistor(stm32::gpio::Resistor::PullUp);
    key1_pin_.SetMode(stm32::gpio::Mode::Input).SetResistor(stm32::gpio::Resistor::PullUp);
    error_pin_.SetMode(stm32::gpio::Mode::Output)
        .SetOutputSpeed(stm32::gpio::Speed::Low)
        .SetOutputType(stm32::gpio::OutputType::PushPull)
        .SetResistor(stm32::gpio::Resistor::None);
    status_pin_.SetMode(stm32::gpio::Mode::Output)
        .SetOutputSpeed(stm32::gpio::Speed::Low)
        .SetOutputType(stm32::gpio::OutputType::PushPull)
        .SetResistor(stm32::gpio::Resistor::None);
    error_indicator_.Inactive();
    status_indicator_.Inactive();
    spi1_mosi_.SetMode(stm32::gpio::Mode::AlternateFunction).SetOutputSpeed(stm32::gpio::Speed::High).SetAlternative(5);    // Alt 5 is SPI1
    spi1_miso_.SetMode(stm32::gpio::Mode::AlternateFunction).SetOutputSpeed(stm32::gpio::Speed::High).SetAlternative(5);    // Alt 5 is SPI1
    spi1_sclk_.SetMode(stm32::gpio::Mode::AlternateFunction).SetOutputSpeed(stm32::gpio::Speed::High).SetAlternative(5);    // Alt 5 is SPI1
    flash_cs_.SetMode(stm32::gpio::Mode::Output)
        .SetOutputSpeed(stm32::gpio::Speed::High)
        .SetOutputType(stm32::gpio::OutputType::PushPull)
        .SetResistor(stm32::gpio::Resistor::PullUp);
    nrf_cs_.SetMode(stm32::gpio::Mode::Output)
        .SetOutputSpeed(stm32::gpio::Speed::High)
        .SetOutputType(stm32::gpio::OutputType::PushPull)
        .SetResistor(stm32::gpio::Resistor::PullUp);
    nrf_ce_.SetMode(stm32::gpio::Mode::Output)
        .SetOutputSpeed(stm32::gpio::Speed::High)
        .SetOutputType(stm32::gpio::OutputType::PushPull)
        .SetResistor(stm32::gpio::Resistor::PullUp);
    nrf_irq_.SetMode(stm32::gpio::Mode::Input).SetResistor(stm32::gpio::Resistor::PullUp);

    // Enable the RNG in the AHB2 Periperhals
    stm32::registers::ResetAndClockControl::AHB2PeripheralClockEnable ahb2_enable;
    ahb2_enable = stm32::registers::reset_and_clock_control.ahb2_peripheral_clock_enable;    // read
    ahb2_enable.bits.random_number_generator_enable = 1U;
    stm32::registers::reset_and_clock_control.ahb2_peripheral_clock_enable = ahb2_enable;    // write

    // Reset the RNG
    stm32::registers::ResetAndClockControl::AHB2PeripheralReset reset;
    reset = stm32::registers::reset_and_clock_control.ahb2_peripheral_reset;    // read
    reset.bits.random_number_generator_reset = 1U;
    stm32::registers::reset_and_clock_control.ahb2_peripheral_reset = reset;    // write
    reset.bits.random_number_generator_reset = 0U;
    stm32::registers::reset_and_clock_control.ahb2_peripheral_reset = reset;    // write

    // enable clock (from APB1) for Timer2
    stm32::registers::ResetAndClockControl::APB1PeripheralClockEnable config;
    config = stm32::registers::reset_and_clock_control.apb1_peripheral_clock_enable;    // read
    config.bits.tim2en = 1U;
    stm32::registers::reset_and_clock_control.apb1_peripheral_clock_enable = config;    // write

    // enable the SPI peripheral in the Reset and Clock Control register
    stm32::registers::ResetAndClockControl::APB2PeripheralClockEnable apb2_enable;
    apb2_enable = stm32::registers::reset_and_clock_control.apb2_peripheral_clock_enable;    // read
    apb2_enable.bits.spi1en = 1;                                                             // modify
    stm32::registers::reset_and_clock_control.apb2_peripheral_clock_enable = apb2_enable;    // write

    status = random_number_generator_.Initialize();
    status = timer_.Initialize(stm32::GetClockTree().tim_clk);
    jarnax::print("Feature Clock is %lu\r\n", stm32::GetClockTree().fclk.value());
    status = spi1_driver_.Initialize(stm32::GetClockTree().fclk, winbond::spi_clock_frequency);

    return status;
}

jarnax::Timer& DriverContext::GetTimer() {
    return timer_;
}

jarnax::RandomNumberGenerator& DriverContext::GetRandomNumberGenerator() {
    return random_number_generator_;
}

jarnax::Indicator& DriverContext::GetErrorIndicator() {
    return error_indicator_;
}

jarnax::Indicator& DriverContext::GetStatusIndicator() {
    return status_indicator_;
}

jarnax::Button& DriverContext::GetWakeupButton() {
    return wakeup_button_;
}

jarnax::Button& DriverContext::GetButton0() {
    return key0_button_;
}

jarnax::Button& DriverContext::GetButton1() {
    return key1_button_;
}

DriverContext& GetDriverContext() {
    static DriverContext context;
    return context;
}
}    // namespace jarnax

namespace stm32 {
namespace initialize {

bool are_drivers_initialized{false};

void drivers(void) {
    using namespace stm32::registers;
    core::Status status;
    status = jarnax::GetDriverContext().Initialize();
    if (status) {
        are_drivers_initialized = true;
    }
}

}    // namespace initialize
}    // namespace stm32

namespace jarnax {
void banner(void) {
    jarnax::print(
        "                                                                    \r\n"
        "         _/    _/_/    _/_/_/    _/      _/    _/_/    _/      _/   \r\n"
        "        _/  _/    _/  _/    _/  _/_/    _/  _/    _/    _/  _/      \r\n"
        "       _/  _/_/_/_/  _/_/_/    _/  _/  _/  _/_/_/_/      _/         \r\n"
        "_/    _/  _/    _/  _/    _/  _/    _/_/  _/    _/    _/  _/        \r\n"
        " _/_/    _/    _/  _/    _/  _/      _/  _/    _/  _/      _/       \r\n"
        " -- %s\r\n",
        jarnax::VersionString
    );
}
}    // namespace jarnax
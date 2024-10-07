

#include "stm32/RandomNumberGenerator.hpp"
#include "stm32/registers/RandomNumberGenerator.hpp"
#include "stm32/registers/ResetAndClockControl.hpp"

using core::Cause;
using core::Result;
using core::Status;

namespace stm32 {

Status RandomNumberGenerator::Initialize(void) {
    std::size_t counter = kInitializeLimit;

    // Enable the RNG in the AHB2 Periperhals
    stm32::registers::ResetAndClockControl::AHB2PeripheralClockEnable enable;
    enable = stm32::registers::reset_and_clock_control.ahb2_peripheral_clock_enable;    // read
    enable.bits.random_number_generator_enable = 1U;
    stm32::registers::reset_and_clock_control.ahb2_peripheral_clock_enable = enable;    // write

    stm32::registers::ResetAndClockControl::AHB2PeripheralReset reset;
    reset = stm32::registers::reset_and_clock_control.ahb2_peripheral_reset;    // read
    reset.bits.random_number_generator_reset = 1U;
    stm32::registers::reset_and_clock_control.ahb2_peripheral_reset = reset;    // write
    reset.bits.random_number_generator_reset = 0U;
    stm32::registers::reset_and_clock_control.ahb2_peripheral_reset = reset;    // write

    // enable but with no interrupts
    stm32::registers::RandomNumberGenerator::Control ctrl;
    ctrl = stm32::registers::random_number_generator.control;    // read
    ctrl.bits.interrupt_enable = 0U;
    ctrl.bits.enable = 1U;
    stm32::registers::random_number_generator.control = ctrl;    // write
    // wait until first read?
    while (not stm32::registers::random_number_generator.status.bits.data_ready and counter > 0U) {
        counter--;
    }
    m_initialized_ = (counter > 0U);
    // save the first read (even if not initialized)
    m_first_ = uint32_t(stm32::registers::random_number_generator.dr);
    return Status{};
}

std::uint32_t RandomNumberGenerator::GetNextRandom(void) {
    // wait until first read?
    while (not stm32::registers::random_number_generator.status.bits.data_ready) {
    }
    // save the first read
    return stm32::registers::random_number_generator.dr.bits.rndata;
}

}    // namespace stm32
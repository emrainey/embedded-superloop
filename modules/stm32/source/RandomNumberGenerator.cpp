

#include "stm32/RandomNumberGenerator.hpp"
#include "stm32/registers/RandomNumberGenerator.hpp"
#include "stm32/registers/ResetAndClockControl.hpp"

using core::Cause;
using core::Result;
using core::Status;

namespace stm32 {

Status RandomNumberGenerator::Initialize(void) {
    std::size_t counter = kInitializeLimit;

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
    initialized_ = (counter > 0U);
    // save the first read (even if not initialized)
    first_ = uint32_t(stm32::registers::random_number_generator.dr);
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
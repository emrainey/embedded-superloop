#include "stm32/RandomNumberGenerator.hpp"
#include "stm32/peripherals.hpp"

using core::Cause;
using core::Result;
using core::Status;

namespace stm32 {

RandomNumberGenerator::RandomNumberGenerator(stm32::peripherals::RandomNumberGenerator volatile& peripheral)
    : peripheral_{peripheral}
    , first_{0U}
    , initialized_(false) {}

Status RandomNumberGenerator::Initialize(void) {
    std::size_t counter = kInitializeLimit;

    // enable but with no interrupts
    stm32::peripherals::RandomNumberGenerator::Control ctrl;
    ctrl = peripheral_.control;    // read
    ctrl.bits.interrupt_enable = 0U;
    ctrl.bits.random_number_generator_enable = 1U;
    peripheral_.control = ctrl;    // write
    // wait until first read?
    while (not peripheral_.status.bits.data_ready and counter > 0U) {
        counter--;
    }
    initialized_ = (counter > 0U);
    // save the first read (even if not initialized)
    first_ = uint32_t(peripheral_.data);
    return Status{};
}

std::uint32_t RandomNumberGenerator::GetNextRandom(void) {
    // wait until first read?
    auto ready = false;
    do {
        // FIXME this could take several milliseconds, so we should probably have a timeout here, but for now we'll just wait indefinitely
        ready = (peripheral_.status.bits.data_ready == 1U);
    } while (not ready);
    // return the value
    return peripheral_.data.bits.random_number_data;
}

}    // namespace stm32

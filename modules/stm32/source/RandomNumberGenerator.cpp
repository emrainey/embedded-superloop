#include "stm32/RandomNumberGenerator.hpp"
#include "stm32/peripherals.hpp"

using core::Cause;
using core::Result;
using core::Status;

namespace stm32 {

static RandomNumberGenerator *random_number_driver{nullptr};

/// @brief The Random Number ISR
void random_number_isr(void) {
    if (random_number_driver) {
        random_number_driver->HandleInterrupt();
    }
}


RandomNumberGenerator::RandomNumberGenerator(stm32::peripherals::RandomNumberGenerator volatile& peripheral)
    : peripheral_{peripheral}
    , first_{0U}
    , initialized_{false}
    , value_{0U}
    , value_ready_{false}
    , statistics_{} {
        random_number_driver = this;
    }

Status RandomNumberGenerator::Initialize(void) {
    stm32::peripherals::RandomNumberGenerator::Control ctrl;
    ctrl = peripheral_.control;    // read
    ctrl.bits.interrupt_enable = 1U; 
#if defined(STM32H7)
    ctrl.bits.clock_error_detection = 1U;
#endif
    ctrl.bits.random_number_generator_enable = 1U;
    peripheral_.control = ctrl;    // write
    return Status{};
}

void RandomNumberGenerator::HandleInterrupt(void) {
    // clear the interrupt
    stm32::peripherals::RandomNumberGenerator::Status status;
    status = peripheral_.status;    // read
    if (status.bits.data_ready == 1U) {
        statistics_.readings++;
        value_ = peripheral_.data.bits.random_number_data;
        value_ready_ = true;
    }
    if (status.bits.clock_error_current_status or status.bits.seed_error_current_status) {
        statistics_.errors++;
        // write status back to clear either value
        status.whole = 0; 
        peripheral_.status = status;
    }
}

bool RandomNumberGenerator::IsReady(void) const {
    return value_ready_;
}

std::uint32_t RandomNumberGenerator::GetNextRandom(void) {
    value_ready_ = false;
    return value_;
}

}    // namespace stm32

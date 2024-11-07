#ifndef STM32_TIMER_HPP
#define STM32_TIMER_HPP

#include "stm32/registers/Timer2.hpp"
#include "jarnax/Timer.hpp"
#include "core/Status.hpp"
#include "core/Units.hpp"

namespace stm32 {

using MicroSeconds = core::units::MicroSeconds;

class Timer : public jarnax::Timer {
public:
    Timer(stm32::registers::Timer2 volatile& timer);

    core::Status Initialize(core::units::Hertz apb1_frequency);

    //+---[jarnax::Timer]--------------------------------------------+
    core::units::Iota GetIotas(void) const override;
    core::units::MicroSeconds GetMicroseconds(void) const override;

protected:
    stm32::registers::Timer2 volatile& timer_;
};

}    // namespace stm32

#endif    // STM32_TIMER_HPP
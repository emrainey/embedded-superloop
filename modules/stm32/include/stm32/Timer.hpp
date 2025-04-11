#ifndef STM32_TIMER_HPP
#define STM32_TIMER_HPP

#include "stm32/registers/Timer2.hpp"
#include "jarnax/Timer.hpp"
#include "core/Status.hpp"
#include "core/Units.hpp"

namespace stm32 {

/// @brief The copied type within the stm32 namespace.
using MicroSeconds = core::units::MicroSeconds;

/// @brief The timer interface for the STM32
class Timer : public jarnax::Timer {
public:
    /// @brief Parameterized constructor
    /// @param timer The volatile reference to a timer
    Timer(stm32::registers::Timer2 volatile& timer);

    /// @brief The initializer of the abp1 frequency
    /// @param apb1_frequency The frequency of the APB1 bus
    /// @return core::Status
    core::Status Initialize(core::units::Hertz apb1_frequency);

    //+---[jarnax::Timer]--------------------------------------------+
    /// @copydoc jarnax::Timer::GetIotas()
    core::units::Iota GetIotas(void) const override;
    /// @copydoc jarnax::Timer::GetMicroseconds()
    core::units::MicroSeconds GetMicroseconds(void) const override;

protected:
    stm32::registers::Timer2 volatile& timer_;    ///< The reference to the volatile timer
};

}    // namespace stm32

#endif    // STM32_TIMER_HPP
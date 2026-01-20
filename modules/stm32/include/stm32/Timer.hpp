#ifndef STM32_TIMER_HPP
#define STM32_TIMER_HPP

#include "core/Conversions.hpp"
#include "core/Status.hpp"
#include "core/Units.hpp"
#include "jarnax/Timer.hpp"
#include "stm32/peripherals/Timer2.hpp"

namespace stm32 {

/// @brief The copied type within the stm32 namespace.
using MicroSeconds = core::units::MicroSeconds;

/// @brief The timer interface for the STM32
class Timer final : public jarnax::Timer {
public:
    /// @brief Parameterized constructor
    /// @param timer The volatile reference to a timer
    Timer(stm32::peripherals::Timer2 volatile& timer);

    ~Timer() = default;

    /// @brief The initializer of the Timer frequency
    /// @param internal_frequency The frequency of the internal clock
    /// @param desired_timer_frequency The desired frequency of the timer
    /// @return core::Status
    core::Status Initialize(core::units::Hertz internal_frequency, core::units::Hertz desired_timer_frequency);

    /// @brief Check if the timer has been initialized
    /// @return true if initialized, false otherwise
    bool IsInitialized() const { return initialized_; }

    //+---[jarnax::Timer]--------------------------------------------+
    core::units::Iota GetIotas(void) const override;
    core::units::MicroSeconds GetMicroseconds(void) const override;
    core::units::Seconds GetSeconds(void) const override;
    //+---[jarnax::Timer]--------------------------------------------+

protected:
    stm32::peripherals::Timer2 volatile& timer_;    ///< The reference to the volatile timer
    std::uint32_t reload_value_;                    ///< The value to reload the timer with
    bool initialized_;                              ///< A guard against using the hardware before it's been initialized
};

}    // namespace stm32

#endif    // STM32_TIMER_HPP

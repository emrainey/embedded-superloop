#ifndef STM32_INDICATOR_HPP
#define STM32_INDICATOR_HPP

/// @file
/// The Indicator Implementation

#include "jarnax/Indicator.hpp"
#include "stm32/Pin.hpp"

namespace stm32 {

/// @brief Used to indicate the Level of the indicator output
enum class Level : bool {
    Low = false,
    High = true
};

/// @brief The Indicator class is used to represent an indicator on the STM32 microcontroller (LED)
class Indicator : public jarnax::Indicator {
public:
    /// @brief The parameter constructor
    /// @param pin The reference to the pin
    /// @param level The level of the indicator to use as it's "ON" state
    Indicator(stm32::gpio::Pin& pin, Level level);

    /// @brief Activate the indicator
    void Active() override;

    /// @brief Deactivate the indicator
    void Inactive() override;

protected:
    Level level_;              ///< The level of the indicator to use as it's "ON" state
    stm32::gpio::Pin& pin_;    ///< The reference to the pin
};
}    // namespace stm32

#endif    // STM32_INDICATOR_HPP
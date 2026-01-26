#ifndef STM32_BUTTON_HPP
#define STM32_BUTTON_HPP

/// @file
/// The Button Definition

#include "jarnax/Button.hpp"
#include "stm32/gpio/Pin.hpp"

namespace stm32 {

/// @brief STM32-specific button implementation using GPIO pins
/// @details Provides a concrete implementation of the Button interface for STM32 microcontrollers.
/// The button reads its state from a GPIO pin and supports configurable active states (high or low).
class Button : public jarnax::Button {
public:
    /// @brief Constructs a button with a GPIO pin
    /// @param pin The GPIO pin connected to the button
    /// @param pressed_state The logic level when button is pressed (true = high, false = low)
    Button(stm32::gpio::Pin& pin, bool pressed_state = true);

    bool IsPressed() const override;

    /// @brief Default Destructor since no pointers are contained within, this can be copied and moved.
    virtual ~Button() = default;

protected:
    /// @brief Reference to the GPIO pin used by this button
    stm32::gpio::Pin& pin_;
    /// @brief The logic level when the button is pressed
    bool pressed_state_;
};

}    // namespace stm32

#endif    // STM32_BUTTON_HPP

#ifndef STM32_BUTTON_HPP
#define STM32_BUTTON_HPP

/// @file
/// The Button Definition

#include "stm32/gpio/Pin.hpp"
#include "jarnax/Button.hpp"

namespace stm32 {

class Button : public jarnax::Button {
public:
    Button(stm32::gpio::Pin& pin, bool pressed_state = true);

    bool IsPressed() const override;

    /// @brief Default Destructor since no pointers are contained within, this can be copied and moved.
    virtual ~Button() = default;

protected:
    stm32::gpio::Pin& pin_;
    bool pressed_state_;
};

}    // namespace stm32

#endif    // STM32_BUTTON_HPP
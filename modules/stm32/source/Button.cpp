#include "stm32/Button.hpp"

namespace stm32 {

Button::Button(stm32::gpio::Pin& pin, bool pressed_state)
    : pin_{pin}
    , pressed_state_{pressed_state} {
}

bool Button::IsPressed() const {
    if (pressed_state_) {
        return pin_.Read();
    } else {
        return not pin_.Read();
    }
}

}    // namespace stm32
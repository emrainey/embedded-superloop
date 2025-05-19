/// @file
/// The Indicator Implementation

#include "iso.hpp"
#include "stm32/Indicator.hpp"
#include "stm32/Pin.hpp"

namespace stm32 {

Indicator::Indicator(stm32::gpio::Pin& pin, Level level)
    : level_{level}
    , pin_{pin} {
}

void Indicator::Active() {
    state_ = to_underlying(level_);
    pin_.Value(state_);
}

void Indicator::Inactive() {
    state_ = to_underlying(level_);
    pin_.Value(not state_);
}

void Indicator::Toggle() {
    state_ = not state_;
    pin_.Value(state_);
}

}    // namespace stm32

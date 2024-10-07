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
    pin_.Write(to_underlying(level_));
}
void Indicator::Inactive() {
    pin_.Write(not to_underlying(level_));
}

}    // namespace stm32

#ifndef STM32_INDICATOR_HPP
#define STM32_INDICATOR_HPP

/// @file
/// The Indicator Implementation

#include "jarnax/Indicator.hpp"
#include "stm32/Pin.hpp"

namespace stm32 {

enum class Level : bool {
    Low = false,
    High = true
};

class Indicator : public jarnax::Indicator {
public:
    Indicator(stm32::gpio::Pin& pin, Level level);
    void Active() override;
    void Inactive() override;

protected:
    Level level_;
    stm32::gpio::Pin& pin_;
};
}    // namespace stm32

#endif    // STM32_INDICATOR_HPP
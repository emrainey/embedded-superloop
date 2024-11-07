#ifndef JARNAX_GPIO_INPUT_HPP
#define JARNAX_GPIO_INPUT_HPP

#include <cstdint>
#include <cstddef>

namespace jarnax {
namespace gpio {

/// @brief An input is a simple general purpose input line.
/// It can be used to read a digital signal but has no concept of active level.
class Input {
public:
    /// @brief Gets the current value of the pin
    /// @return True is logic high, False is logic low
    virtual bool Value(void) const = 0;
};

}  // namespace gpio
}  // namespace jarnax

#endif // JARNAX_GPIO_INPUT_HPP
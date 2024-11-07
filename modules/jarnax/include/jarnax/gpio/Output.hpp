#ifndef JARNAX_GPIO_OUTPUT_HPP
#define JARNAX_GPIO_OUTPUT_HPP

#include <cstdint>
#include <cstddef>

namespace jarnax {
namespace gpio {

/// @brief An output is a simple general purpose output line.
/// It can be used to write a digital signal but has no concept of active level (see @ref Indicators)
class Output {
public:
    /// @brief Sets the Pin to the value of the parameter
    /// @param value True is logic high, False is logic low
    virtual void Value(bool value) = 0;
};


}  // namespace gpio
}  // namespace jarnax

#endif // JARNAX_GPIO_OUTPUT_HPP
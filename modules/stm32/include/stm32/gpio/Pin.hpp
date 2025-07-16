#ifndef STM32_GPIO_PIN_HPP
#define STM32_GPIO_PIN_HPP

/// @file
/// Auto Generated Structure Definitions for GeneralPurposeInputOutput from the Peripheralyzer.
/// @copyright

#include <cstdint>
#include <cstddef>
#include <type_traits>
#include "jarnax/gpio/Input.hpp"
#include "jarnax/gpio/Output.hpp"

namespace stm32 {
namespace gpio {

/// @brief The GPIO Port Name
enum class Port : uint8_t {
    A = 0,
    B = 1,
    C = 2,
    D = 3,
    E = 4,
    F = 5,
    G = 6,
    H = 7,
    I = 8,
    J = 9,
    K = 10
};

/// @brief The GPIO Pin Mode
enum class Mode : uint8_t {
    Input = 0b00,
    Output = 0b01,
    AlternateFunction = 0b10,
    Analog = 0b11
};

/// @brief The GPIO Output Type
enum class OutputType : uint8_t {
    PushPull = 0b0,
    OpenDrain = 0b1
};

/// @brief The GPIO Output Speed
enum class Speed : uint8_t {
    Low = 0b00,
    Medium = 0b01,
    High = 0b10,
    VeryHigh = 0b11
};

/// @brief The GPIO Resistor Type
enum class Resistor : uint8_t {
    None = 0b00,
    PullUp = 0b01,
    PullDown = 0b10
};

/// @brief The GPIO Pin Index Mask
static constexpr std::uint8_t IndexMask = 0xFU;

/// @brief The Pin class is used to represent a GPIO pin on the STM32 microcontroller which can be either Input or Output.
class Pin : public jarnax::gpio::Input, public jarnax::gpio::Output {
public:
    /// @brief The default constructor is deleted
    Pin() = delete;
    /// @brief The parameterized constructor
    Pin(Port port, uint8_t index);
    // since no pointers are contained within, this can be copied and moved.
    ~Pin() = default;

    /// @return The value of the pin
    bool Value() const override;
    /// Sets the value of the Pin
    /// @param value The value to set the pin to
    void Value(bool value) override;

    /// @brief Sets the mode of the pin
    Pin& SetMode(Mode mode);
    /// @brief Gets the mode of the pin
    Mode GetMode() const;

    /// @brief Sets the output speed of the pin
    Pin& SetOutputSpeed(Speed speed);
    /// @brief Gets the output speed of the pin
    Speed GetOutputSpeed() const;

    /// @brief Sets the output type of the pin
    Pin& SetOutputType(OutputType type);
    /// @brief Gets the output type of the pin
    OutputType GetOutputType() const;

    /// @brief Sets the resistor type of the pin
    Pin& SetResistor(Resistor type);
    /// @brief Gets the resistor type of the pin
    Resistor GetResistor() const;

    /// @brief Sets the alternative function of the pin
    Pin& SetAlternative(uint8_t value);
    /// @brief Gets the alternative function of the pin
    uint8_t GetAlternative() const;

protected:
    Port port_;        ///< The port of the pin
    uint8_t index_;    ///< The index within the port to use
};

}    // namespace gpio

}    // namespace stm32

#endif    // STM32_GPIO_PIN_HPP
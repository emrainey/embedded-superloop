#ifndef STM32_GPIO_PIN_HPP
#define STM32_GPIO_PIN_HPP

/// @file
/// Auto Generated Structure Definitions for GeneralPurposeInputOutput from the Peripheralyzer.
/// @copyright

#include <cstdint>
#include <cstddef>
#include <type_traits>

namespace stm32 {
namespace gpio {

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

enum class Mode : uint8_t {
    Input = 0b00,
    Output = 0b01,
    AlternateFunction = 0b10,
    Analog = 0b11
};

enum class OutputType : uint8_t {
    PushPull = 0b0,
    OpenDrain = 0b1
};

enum class Speed : uint8_t {
    Low = 0b00,
    Medium = 0b01,
    High = 0b10,
    VeryHigh = 0b11
};

enum class Resistor : uint8_t {
    None = 0b00,
    PullUp = 0b01,
    PullDown = 0b10
};

static constexpr std::uint8_t IndexMask = 0xFU;

class Pin {
public:
    Pin() = delete;
    Pin(Port port, uint8_t index);
    // since no pointers are contained within, this can be copied and moved.
    ~Pin() = default;

    Pin& SetMode(Mode mode);
    Mode GetMode() const;

    Pin& SetOutputSpeed(Speed speed);
    Speed GetOutputSpeed() const;

    Pin& SetOutputType(OutputType type);
    OutputType GetOutputType() const;

    Pin& SetResistor(Resistor type);
    Resistor GetResistor() const;

    bool Read() const;
    void Write(bool value);

    Pin& SetAlternative(uint8_t value);
    uint8_t GetAlternative() const;

protected:
    Port port_;
    uint8_t index_;    ///< The index within the port to use
};

}    // namespace gpio

}    // namespace stm32

#endif    // STM32_GPIO_PIN_HPP
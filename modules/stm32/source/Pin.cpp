#include "iso.hpp"
#include "stm32/Pin.hpp"
#include "stm32/registers/GeneralPurposeInputOutput.hpp"

namespace stm32 {
namespace gpio {

using namespace stm32::registers;

Pin::Pin(Port port, uint8_t index)
    : port_{port}
    , index_{static_cast<std::uint8_t>(index & IndexMask)}    // indexes can only be up to 15.
{
}

Pin& Pin::SetMode(Mode mode) {
    auto pin_mode = general_purpose_input_output[to_underlying(port_)].mode;               // read
    pin_mode.whole |= static_cast<std::uint32_t>(to_underlying(mode) << (index_ * 2U));    // modify
    general_purpose_input_output[to_underlying(port_)].mode = pin_mode;                    // write
    return *this;
}

Mode Pin::GetMode() const {
    auto mode = general_purpose_input_output[to_underlying(port_)].mode;    // read
    return static_cast<Mode>((mode.whole >> (index_ * 2)) & 0b11);          // extract
}

Pin& Pin::SetOutputSpeed(Speed speed) {
    auto output_speed = general_purpose_input_output[to_underlying(port_)].output_speed;        // read
    output_speed.whole |= static_cast<std::uint32_t>(to_underlying(speed) << (index_ * 2U));    // modify
    general_purpose_input_output[to_underlying(port_)].output_speed = output_speed;             // write
    return *this;
}

Speed Pin::GetOutputSpeed() const {
    auto output_speed = general_purpose_input_output[to_underlying(port_)].output_speed;    // read
    return static_cast<Speed>((output_speed.whole >> (index_ * 2)) & 0b11);                 // extract
}

Pin& Pin::SetOutputType(OutputType type) {
    auto output_type = general_purpose_input_output[to_underlying(port_)].output_type;    // read
    output_type.whole |= static_cast<std::uint32_t>(to_underlying(type) << index_);       // modify
    general_purpose_input_output[to_underlying(port_)].output_type = output_type;         // write
    return *this;
}

OutputType Pin::GetOutputType() const {
    auto output_type = general_purpose_input_output[to_underlying(port_)].output_type;    // read
    return static_cast<OutputType>((output_type.whole >> index_) & 0b1);                  // extract
}

Pin& Pin::SetResistor(Resistor type) {
    auto pull = general_purpose_input_output[to_underlying(port_)].pullup_pulldown;    // read
    pull.whole |= static_cast<std::uint32_t>(to_underlying(type) << (index_ * 2U));    // modify
    general_purpose_input_output[to_underlying(port_)].pullup_pulldown = pull;         // write
    return *this;
}

Resistor Pin::GetResistor() const {
    auto pull = general_purpose_input_output[to_underlying(port_)].pullup_pulldown;    // read
    return static_cast<Resistor>((pull.whole >> (index_ * 2)) & 0b11);                 // extract
}

bool Pin::Value() const {
    Mode mode = GetMode();
    if (mode == Mode::Input) {
        auto input = general_purpose_input_output[to_underlying(port_)].input_data;    // read
        return ((input.whole >> index_) & 0b1) > 0;                                    // extract
    } else if (mode == Mode::Output) {
        auto output = general_purpose_input_output[to_underlying(port_)].output_data;    // read
        return ((output.whole >> index_) & 0b1) > 0;                                     // extract
    } else {
        return false;
    }
}
void Pin::Value(bool value) {
    Mode mode = GetMode();
    if (mode == Mode::Output) {
        auto output = general_purpose_input_output[to_underlying(port_)].output_data;    // read
        output.whole |= static_cast<std::uint32_t>(value << index_);                     // modify
        general_purpose_input_output[to_underlying(port_)].output_data = output;         // write
    } else {
        // nothing happens
    }
}

Pin& Pin::SetAlternative(uint8_t value) {
    Mode mode = GetMode();
    if (mode == Mode::AlternateFunction) {
        value &= 0xFU;    // only 4 bits are allowed
        if (index_ < 8) {
            auto alt_func_low = general_purpose_input_output[to_underlying(port_)].alt_func_low;    // read
            alt_func_low.whole |= static_cast<std::uint32_t>(value << (index_ * 4U));               // modify
            general_purpose_input_output[to_underlying(port_)].alt_func_low = alt_func_low;         // write
        } else {
            auto alt_func_high = general_purpose_input_output[to_underlying(port_)].alt_func_high;    // read
            alt_func_high.whole |= static_cast<std::uint32_t>(value << ((index_ - 8) * 4U));          // modify
            general_purpose_input_output[to_underlying(port_)].alt_func_high = alt_func_high;         // write
        }
    }
    return *this;
}

uint8_t Pin::GetAlternative() const {
    Mode mode = GetMode();
    if (mode == Mode::AlternateFunction) {
        if (index_ < 8) {
            auto alt_func_low = general_purpose_input_output[to_underlying(port_)].alt_func_low;    // read
            return (alt_func_low.whole >> (index_ * 4U)) & 0xFU;                                    // extract
        } else {
            auto alt_func_high = general_purpose_input_output[to_underlying(port_)].alt_func_high;    // read
            return (alt_func_high.whole >> ((index_ - 8) * 4U)) & 0xFU;                               // extract
        }
    }
    return 0U;    // when not in alternate function mode, return 0 (the hardware default)
}

}    // namespace gpio
}    // namespace stm32
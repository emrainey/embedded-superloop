#ifndef JARNAX_BUTTON_HPP
#define JARNAX_BUTTON_HPP

/// @file
/// The Button Definition

namespace jarnax {

/// @brief The Button Interface
class Button {
public:
    /// @return true if the button is currently pressed, false otherwise
    virtual bool IsPressed() const = 0;

protected:
    ~Button() = default;
};

}    // namespace jarnax

#endif    // JARNAX_BUTTON_HPP

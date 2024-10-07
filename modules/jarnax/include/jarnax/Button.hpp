#ifndef JARNAX_BUTTON_HPP
#define JARNAX_BUTTON_HPP

/// @file
/// The Button Definition

namespace jarnax {

class Button {
public:
    virtual bool IsPressed() const = 0;

protected:
    ~Button() = default;
};

}    // namespace jarnax

#endif    // JARNAX_BUTTON_HPP
#ifndef JARNAX_INDICATOR_HPP
#define JARNAX_INDICATOR_HPP

/// @file
/// The Indicator Definition

namespace jarnax {

/// @brief The Indicator Interface
class Indicator {
public:
    /// @brief Sets the indicator to active state
    virtual void Active() = 0;

    /// @brief Sets the indicator to inactive state
    virtual void Inactive() = 0;

    /// @brief Toggles the indicator state from active to inactive or vice versa
    virtual void Toggle() = 0;

protected:
    ~Indicator() = default;
};
}    // namespace jarnax

#endif    // JARNAX_INDICATOR_HPP

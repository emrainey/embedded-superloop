#ifndef JARNAX_INDICATOR_HPP
#define JARNAX_INDICATOR_HPP

/// @file
/// The Indicator Definition

namespace jarnax {

class Indicator {
public:
    virtual void Active() = 0;
    virtual void Inactive() = 0;

protected:
    ~Indicator() = default;
};
}    // namespace jarnax

#endif    // JARNAX_INDICATOR_HPP
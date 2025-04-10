#ifndef JARNAX_RNG_H
#define JARNAX_RNG_H

/// @file
/// jarnax::RandomNumberGenerator Interface

#include <cstdint>
#include <cstddef>

namespace jarnax {

class RandomNumberGenerator {
public:
    /// Returns a random 32 bit number.
    virtual std::uint32_t GetNextRandom(void) = 0;

protected:
    ~RandomNumberGenerator() = default;
};
}    // namespace jarnax

#endif    // JARNAX_RNG_H
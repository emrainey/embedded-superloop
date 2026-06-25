#ifndef JARNAX_RNG_H
#define JARNAX_RNG_H

/// @file
/// jarnax::RandomNumberGenerator Interface

#include <cstddef>
#include <cstdint>

namespace jarnax {

/// @brief The Random Number Generator Interface
class RandomNumberGenerator {
public:
    /// Returns true if a random number is ready to be read.
    virtual bool IsReady(void) const = 0;
    /// Returns a random 32 bit number, if @ref IsReady() return true. Otherwise, returns the previous number.
    virtual std::uint32_t GetNextRandom(void) = 0;

protected:
    ~RandomNumberGenerator() = default;
};
}    // namespace jarnax

#endif    // JARNAX_RNG_H

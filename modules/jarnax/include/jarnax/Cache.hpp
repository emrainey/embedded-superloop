#ifndef JARNAX_CACHE_HPP_
#define JARNAX_CACHE_HPP_

/// @file
/// A Cache Control Interface for Jarnax

#include <cstdint>

namespace jarnax {
/// The Cache interface manages a Cache, either Instruction or Data.
class DataCache {
public:
    /// Enable the Cache
    virtual void Enable() = 0;

    /// Disable the Cache
    virtual void Disable() = 0;

    /// Invalidate the entire Cache
    /// All lines will be marked as invalid and a subsequent access will fetch from memory.
    /// @warning Any dirty lines will be lost!
    virtual void Invalidate() = 0;

    /// Invalidate a line of the Cache.
    /// The lines will be marked as invalid and a subsequent access will fetch from memory.
    /// @warning Any dirty lines will be lost!
    virtual void Invalidate(std::uintptr_t address, size_t bytes) = 0;

    /// Clean the entire Cache
    /// All dirty lines will be written back to memory.
    virtual void Clean() = 0;

    /// Clean a range within the Cache
    /// The line will be written back to memory and kept in the cache.
    virtual void Clean(std::uintptr_t address, size_t bytes) = 0;

    /// Clean and Invalidate the entire Cache
    /// All dirty lines will be written back to memory and then marked as invalid.
    virtual void Flush() = 0;

    /// Cleans and Invalidates a range within the Cache
    /// The lines will be written back to memory and then marked as invalid.
    virtual void Flush(std::uintptr_t address, size_t bytes) = 0;

protected:
    ~DataCache() = default;
};

/// The Cache interface manages a Cache, either Instruction or Data.
class InstructionCache {
public:
    /// Enable the Cache
    virtual void Enable() = 0;

    /// Disable the Cache
    virtual void Disable() = 0;

    /// Invalidate the entire Cache
    /// All lines will be marked as invalid and a subsequent access will fetch from memory.
    /// @warning Any dirty lines will be lost!
    virtual void Invalidate() = 0;

    /// Invalidate a line of the Cache.
    /// The lines will be marked as invalid and a subsequent access will fetch from memory.
    /// @warning Any dirty lines will be lost!
    virtual void Invalidate(std::uintptr_t address, size_t bytes) = 0;

protected:
    ~InstructionCache() = default;
};

}    // namespace jarnax

#endif    // JARNAX_CACHE_HPP_

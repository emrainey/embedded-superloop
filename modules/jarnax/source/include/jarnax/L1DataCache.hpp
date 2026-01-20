#ifndef JARNAX_L1CACHE_HPP
#define JARNAX_L1CACHE_HPP

/// @file
/// The Jarnax L1 Cache Control Header

#include <cstddef>
#include <cstdint>

#include "jarnax/Cache.hpp"    // DataCache, InstructionCache

namespace jarnax {

/// Contains operations on the L1 Cache subsystems for Jarnax processors
class L1DataCache final : public DataCache {
public:
    // ###########################
    //  Jarnax::Cache Interface //
    // ###########################
    void Enable() override;
    void Disable() override;
    void Invalidate() override;
    void Invalidate(std::uintptr_t address, size_t bytes) override;
    void Clean() override;
    void Clean(std::uintptr_t address, size_t bytes) override;
    void Flush() override;
    void Flush(std::uintptr_t address, size_t bytes) override;
    ~L1DataCache() = default;
};

}    // namespace jarnax

#endif    // JARNAX_L1CACHE_HPP

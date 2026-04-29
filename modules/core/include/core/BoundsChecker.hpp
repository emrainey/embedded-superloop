#ifndef CORE_BOUNDSCHECKER_HPP_
#define CORE_BOUNDSCHECKER_HPP_

/// @file
/// The Cortex Microcontroller Address Header. The contains the definitions of the 32 bit address space of the Cortex Microcontroller processor

#include <cstddef>
#include <cstdint>
#include <polyfill.hpp>
#include "iso.hpp"

#include <core/Intervals.hpp>
#include <core/Span.hpp>

namespace core {

/// Contains the valid memory regions of the system and provides a function to check if an address is valid.
class BoundsChecker {
public:
    BoundsChecker() = delete;

    /// @brief Construct a MemoryChecker with the given memory regions
    BoundsChecker(core::Interval const intervals[], uint32_t count);

    /// @brief Checks if the given address is valid for the processor
    /// @param address The address to check
    /// @return true if the address is valid, false otherwise
    bool IsValidAddress(std::uintptr_t address);

protected:
    core::Span<core::Interval const> memory_regions_;    ///< The memory regions of the processor
};

}    // namespace core

#endif    // CORE_BOUNDSCHECKER_HPP_

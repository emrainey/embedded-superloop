#ifndef SYSTEM_LOOPINFO_HPP_
#define SYSTEM_LOOPINFO_HPP_

/// @file
/// Loop Data Information Structure

#include <cstdint>
#include <cstddef>

namespace jarnax {

/// The Core SuperLoop metadata structure passed to the Executable each loop
struct LoopInfo final {
    std::size_t system_count{0U};         ///< Counts the number of system loops
    std::size_t count{0U};                ///< Counts the number of loops that this Executable has run
    std::size_t cadence{0xFFFF'FFFFU};    ///< The cadence of this Executable.
    std::size_t cadence_mask{0U};         ///< The mask of the current cadence
};

}    // namespace jarnax

#endif    // SYSTEM_LOOPINFO_HPP_
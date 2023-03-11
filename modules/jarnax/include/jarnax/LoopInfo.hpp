#ifndef SYSTEM_LOOPINFO_HPP_
#define SYSTEM_LOOPINFO_HPP_

/// @file
/// Loop Data Information Structure

#include <cstdint>
#include <cstddef>

namespace jarnax {

/// The Core SuperLoop metadata structure
struct LoopInfo final {
    std::size_t system_count{0U};    ///< Counts the number of system loops
    std::size_t count{0U};           ///< Counts the number of loops that this Executable has run
    std::size_t cadence{1U};         ///< The cadence of this Executable.
};

}    // namespace jarnax

#endif    // SYSTEM_LOOPINFO_HPP_
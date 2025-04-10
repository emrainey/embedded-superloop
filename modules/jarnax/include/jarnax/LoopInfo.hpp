#ifndef JARNAX_LOOPINFO_HPP_
#define JARNAX_LOOPINFO_HPP_

/// @file
/// Loop Data Information Structure

#include <cstdint>
#include <cstddef>

namespace jarnax {

/// @brief The ID of the Executable Object
using Id = std::uint32_t;

/// @brief Used to denote if the Executable should run in this loop or not.
using Cadence = std::uint32_t;

/// @brief The number of slots in the Cadency
static constexpr std::size_t SlotsInCadence = sizeof(Cadence) * 8U;

/// @brief The mask for the cadence slot
inline Cadence GetMask(std::size_t slot) {
    slot = ((SlotsInCadence - 1U) & slot);    // mask out any high values
    return (1U << slot);                      // return the mask
}

/// The Core SuperLoop metadata structure available to the Executable each loop
struct LoopInfo final {
    std::size_t system_loop_count{0U};    ///< Counts the number of system loops
    std::size_t cadence_slot{0U};         ///< The current cadence slot. Use @ref GetMask to get the mask for this slot
};

}    // namespace jarnax

#endif    // JARNAX_LOOPINFO_HPP_
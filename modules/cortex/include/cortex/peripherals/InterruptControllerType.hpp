#ifndef CORTEX_PERIPHERALS_INTERRUPT_CONTROLLER_TYPE_HPP_
#define CORTEX_PERIPHERALS_INTERRUPT_CONTROLLER_TYPE_HPP_

/// @file
/// The Cortex Microcontroller Interrupt Controller Type Header

#include "cortex/types.hpp"

namespace cortex {
namespace peripherals {
/// The Interrupt Controller Type Register (ICTR) is outside the SCB.
struct InterruptControllerType final {
    uint32_t group_interrupt_lines_count;    ///< The total number of group of interrupt lines of this implementation.

    /// Returns the upper limit of individual number of interrupt lines
    inline uint32_t get_interrupt_lines_limit(void) { return (32U * (group_interrupt_lines_count + 1U)); }
};
static_assert(sizeof(InterruptControllerType) == sizeof(std::uint32_t), "Must be this exact size");

/// The pointer to the Interrupt Controller Type Register
extern InterruptControllerType volatile interrupt_controller_type;

}    // namespace peripherals
}    // namespace cortex

#endif    // CORTEX_PERIPHERALS_INTERRUPT_CONTROLLER_TYPE_HPP_

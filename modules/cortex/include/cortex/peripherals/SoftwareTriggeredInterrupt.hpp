#ifndef CORTEX_SOFTWARE_INTERRUPT_HPP_
#define CORTEX_SOFTWARE_INTERRUPT_HPP_

/// @file
/// The Cortex Microcontroller Software Interrupt Control Header

#include <cstddef>
#include <cstdint>

namespace cortex {
namespace peripherals {
/// (STIR) The Software Triggered Interrupt Register
struct SoftwareTriggeredInterrupt final {
    /// @brief The bitfield definition of the register
    struct Fields final {
        std::uint32_t interrupt : 9U;
        std::uint32_t           : 23U;
    };
    union {
        Fields bits;
        std::uint32_t whole;
    };
};

/// The pointer to the Software Triggered Interrupt Register
extern SoftwareTriggeredInterrupt volatile software_triggered_interrupt;

}    // namespace peripherals
}    // namespace cortex

#endif    // CORTEX_SOFTWARE_INTERRUPT_HPP_

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
    SoftwareTriggeredInterrupt()
        : whole{0U} {}
    SoftwareTriggeredInterrupt(SoftwareTriggeredInterrupt volatile const& other)
        : whole{other.whole} {}
    SoftwareTriggeredInterrupt(SoftwareTriggeredInterrupt const& other)
        : whole{other.whole} {}
    /// @brief The bitfield definition of the register
    struct Fields final {
        std::uint32_t interrupt : 9U;
        std::uint32_t           : 23U;
    };
    union {
        Fields bits;
        std::uint32_t whole;
    };
    /// Assignment from copy back to registers
    void operator=(SoftwareTriggeredInterrupt const& other) volatile { whole = other.whole; }
    /// Copy from volatile register to local copy
    void operator=(SoftwareTriggeredInterrupt volatile& other) { whole = other.whole; }
};

/// The pointer to the Software Triggered Interrupt Register
extern SoftwareTriggeredInterrupt volatile software_triggered_interrupt;

}    // namespace peripherals
}    // namespace cortex

#endif    // CORTEX_SOFTWARE_INTERRUPT_HPP_

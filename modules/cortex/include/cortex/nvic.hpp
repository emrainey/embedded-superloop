#ifndef CORTEX_M_NVIC_HPP_
#define CORTEX_M_NVIC_HPP_

/// @file
/// The Cortex M System NVIC Header

#include "cortex/core.hpp"
#include "cortex/exceptions.hpp"
#include "cortex/vendor.hpp"

namespace cortex {

namespace nvic {
// The normal shift size for all registers
constexpr static uint32_t shift = 5U;
/// @brief The mask for all registers
constexpr static uint32_t mask = (1U << shift) - 1U;
/// @brief The limit to the number of external interrupts
constexpr static uint32_t limit = 496U;

/// Enables an interrupt in the NVIC
/// @param interrupt The enumerated interrupt value.
void Enable(std::uint32_t interrupt);

/// Determines if the interrupt is enabled in the NVIC
/// @param interrupt The enumerated interrupt value.
bool IsEnabled(std::uint32_t interrupt);

/// Disables the interrupt from firing again
/// @param interrupt The enumerated interrupt value.
void Disable(std::uint32_t interrupt);

/// Clears the pending state on an interrupt
/// @param interrupt The enumerated interrupt value.
void Cancel(std::uint32_t interrupt);

/// Sets the pending state on an interrupt
/// @param interrupt The enumerated interrupt value.
void Pend(std::uint32_t interrupt);

/// Determines if an interrupt is pending
/// @param interrupt The enumerated interrupt value.
bool IsPending(std::uint32_t interrupt);

/// Determines if an interrupt is active
/// @param interrupt The enumerated interrupt value.
bool IsActive(std::uint32_t interrupt);

/// Sets the priority value of an interrupt
/// @param interrupt The enumerated interrupt value.
/// @param value The priority to assign to the interrupt.
void Prioritize(std::uint32_t interrupt, std::uint8_t value);

}    // namespace nvic

/// The Nested Interrupt Vector Peripheral definition
struct NestedInterruptVectorController final {
    std::uint32_t enable[16];                //!< Offset 0x0 to 0x3C inclusive
    std::uint32_t _reserved1[16];            ///< Reserved Fields
    std::uint32_t clear[16];                 //!< Offsets 0x80 to 0xBC inclusive
    std::uint32_t _reserved2[16];            ///< Reserved Fields
    std::uint32_t pending[16];               //!< Offset 0x100 to 0x13C inclusive
    std::uint32_t _reserved3[16];            ///< Reserved Fields
    std::uint32_t cancel[16];                //!< Offset 0x180 to 0x1BC inclusive
    std::uint32_t _reserved4[16];            ///< Reserved Fields
    std::uint32_t /* const */ active[16];    //!< Offset 0x200 to 0x23C inclusive
    std::uint32_t _reserved5[48];            ///< Reserved Fields
    std::uint8_t priority[nvic::limit];      //!< Offset 0x300 to 0x4EC inclusive
    std::uint32_t _reserved6[452];           ///< Reserved Fields
};
static_assert(sizeof(NestedInterruptVectorController) == 0xC00, "Must be this size");

/// The peripheral NVIC as defined in Linker
extern NestedInterruptVectorController volatile nested_interrupt_vector_controller;

}    // namespace cortex

#endif    // CORTEX_M_NVIC_HPP_
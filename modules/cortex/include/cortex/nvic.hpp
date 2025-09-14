#ifndef CORTEX_M_NVIC_HPP_
#define CORTEX_M_NVIC_HPP_

/// @file
/// The Cortex Microcontroller System NVIC API

#include <cstdint>

namespace cortex {
namespace nvic {

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

}    // namespace cortex

#endif    // CORTEX_M_NVIC_HPP_

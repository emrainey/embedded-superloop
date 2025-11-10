#ifndef CORTEX_TRIGGER_HPP_
#define CORTEX_TRIGGER_HPP_

/// @file
/// The Cortex Microcontroller Trigger Header

namespace cortex {
/// The Trigger Namespace which is used to induce various processor states.
namespace trigger {

/// Triggers a Reset to the Processor as if reset externally
[[noreturn]] void external_reset(void);

/// Causes a Non Maskable Interrupt to Fire
void non_maskable_interrupt(void);

/// Causes a processor exception to enter into Pending Supervisor
void pending_supervisor(void);

/// Causes a system tick interrupt to fire.
/// @note This will advance the tick count by one regardless of the current tick state.
/// @warning This may become deprecated in the future due to potential timing issues.
void system_tick(void);

/// Causes a software interrupt to fire for the given interrupt number
/// @param interrupt The interrupt number to trigger
/// @warning This may cause a fault if the allow_unprivileged_software_trigger is false and the call is made from unprivileged mode.
void software_interrupt(uint32_t interrupt);

}    // namespace trigger
}    // namespace cortex

#endif    // CORTEX_TRIGGER_HPP_

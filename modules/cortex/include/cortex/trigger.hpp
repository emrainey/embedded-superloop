#ifndef CORTEX_TRIGGER_HPP_
#define CORTEX_TRIGGER_HPP_

/// @file
/// The Cortex Microcontroller Trigger Header

namespace cortex {

/// Requests a Reset to the External System
[[noreturn]] void request_external_reset(void);

/// Causes a Non Maskable Interrupt to Fire
void trigger_non_maskable_interrupt(void);

/// Causes a processor exception to enter into Pending Supervisor
void trigger_pending_supervisor(void);

/// Causes a system tick interrupt to fire.
void trigger_system_tick(void);

}    // namespace cortex

#endif    // CORTEX_TRIGGER_HPP_

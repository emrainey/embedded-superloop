#include "cortex/m4.hpp"
#include "jarnax/system.hpp"

namespace cortex {

void trigger_non_maskable_interrupt(void) {
    thumb::data_synchronization_barrier();
    auto ics = system_control_block.interrupt_control_state;
    ics.parts.trigger_non_maskable = 1U;
    system_control_block.interrupt_control_state.whole = ics.whole;
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
    // we'll return here once the call is done.
}

void trigger_supervisor_call(void) {
    /// @todo Figure out the parameter sets and then the call into and out of this method...
}

void trigger_system_tick(void) {
    thumb::data_synchronization_barrier();
    auto ics = system_control_block.interrupt_control_state;
    ics.parts.trigger_system_tick = 1U;
    system_control_block.interrupt_control_state.whole = ics.whole;
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
    // we'll return here once the call is done.
}

void trigger_pending_supervisor(void) {
    thumb::data_synchronization_barrier();
    auto ics = system_control_block.interrupt_control_state;
    ics.parts.trigger_pending_supervisor = 1U;
    system_control_block.interrupt_control_state.whole = ics.whole;
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
    // we'll return here once the call is done.
}
}    // namespace cortex

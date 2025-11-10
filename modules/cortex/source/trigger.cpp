#include "cortex/mcu.hpp"

namespace cortex {
namespace trigger {

[[noreturn]] void external_reset(void) {
    thumb::data_synchronization_barrier();
    auto aircr = peripherals::system_control_block.application_interrupt_reset_control;
    aircr.parts.key = cortex::keys::reset_value;
    aircr.parts.system_reset_request = 1U;
    peripherals::system_control_block.application_interrupt_reset_control = aircr;
    thumb::data_synchronization_barrier();
    // >>> reset should happen right here <<<
    cortex::spinhalt();
}

void non_maskable_interrupt(void) {
    thumb::data_synchronization_barrier();
    auto ics = peripherals::system_control_block.interrupt_control_state;
    ics.parts.trigger_non_maskable = 1U;
    peripherals::system_control_block.interrupt_control_state = ics;
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
    // we'll return here once the call is done.
}

void pending_supervisor(void) {
    thumb::data_synchronization_barrier();
    auto ics = peripherals::system_control_block.interrupt_control_state;
    ics.parts.trigger_pending_supervisor = 1U;
    peripherals::system_control_block.interrupt_control_state = ics;
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
    // we'll return here once the call is done.
}

void system_tick(void) {
    thumb::data_synchronization_barrier();
    auto ics = peripherals::system_control_block.interrupt_control_state;
    ics.parts.trigger_system_tick = 1U;
    peripherals::system_control_block.interrupt_control_state = ics;
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
    // we'll return here once the call is done.
}

void software_interrupt(uint32_t interrupt) {
    thumb::data_synchronization_barrier();
    auto stir = peripherals::software_triggered_interrupt;
    stir.bits.interrupt = interrupt & 0x1FFU;    // only lower 9 bits are valid
    peripherals::software_triggered_interrupt = stir;
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
    // we'll return here once the call is done.
}

}    // namespace trigger
}    // namespace cortex

#include "cortex/mcu.hpp"

namespace cortex {
[[noreturn]] void request_external_reset(void) {
    thumb::data_synchronization_barrier();
    auto aircr = peripherals::system_control_block.application_interrupt_reset_control;
    aircr.parts.key = cortex::keys::reset_value;
    aircr.parts.system_reset_request = 1U;
    peripherals::system_control_block.application_interrupt_reset_control = aircr;
    thumb::data_synchronization_barrier();
    // >>> reset should happen right here <<<
    cortex::spinhalt();
}
}    // namespace cortex

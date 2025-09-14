#include "cortex/mcu.hpp"

namespace cortex {

// [[noreturn]] void halt(void) {
//     thumb::data_synchronization_barrier();
//     thumb::instruction_barrier();
//     // Enable the debug system and halt the processor
//     peripherals::DebugSystem::HaltingControl dhc;
//     dhc = peripherals::debug_system.halting_control;
//     dhc.write.debug = 1U;
//     dhc.write.halt = 1U;
//     peripherals::debug_system.halting_control = dhc;
//     thumb::data_synchronization_barrier();
//     thumb::instruction_barrier();
//     __builtin_unreachable();
// }

[[noreturn]] void spinhalt(void) {
    while (true) {
        thumb::breakpoint<0>();    // 0xAB should be use for semihosting
    }
    __builtin_unreachable();
}

}    // namespace cortex

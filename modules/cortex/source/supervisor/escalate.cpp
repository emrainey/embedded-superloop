#include "cortex/mcu.hpp"
namespace cortex {
namespace supervisor {

cortex::modes::Privileged escalate(void) {
    cortex::registers::Control control;
    control.whole = thumb::get_control();
    cortex::modes::Privileged old = control.parts.privilege;
    control.parts.privilege = cortex::modes::Privileged::High;
    thumb::set_control(control.whole);
    thumb::instruction_barrier();
    return old;
}

}    // namespace supervisor

}    // namespace cortex

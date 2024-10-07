#include "cortex/mcu.hpp"
namespace cortex {
namespace supervisor {

void deescalate(void) {
    cortex::Control control;
    control.whole = thumb::get_control();
    control.parts.privilege = cortex::modes::Privileged::Low;
    thumb::set_control(control.whole);
    thumb::instruction_barrier();
}

}    // namespace supervisor

}    // namespace cortex

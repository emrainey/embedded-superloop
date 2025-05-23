#include "cortex/mcu.hpp"
namespace cortex {
namespace supervisor {

void restore(cortex::modes::Privileged old) {
    cortex::Control control;
    control.whole = thumb::get_control();
    control.parts.privilege = old;
    thumb::set_control(control.whole);
    thumb::instruction_barrier();
}

}    // namespace supervisor

}    // namespace cortex

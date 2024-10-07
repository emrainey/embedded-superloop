#include "cortex/mcu.hpp"
namespace cortex {
namespace supervisor {

modes::Privileged query(void) {
    cortex::Control control;
    control.whole = thumb::get_control();
    return control.parts.privilege;
}

}    // namespace supervisor

}    // namespace cortex

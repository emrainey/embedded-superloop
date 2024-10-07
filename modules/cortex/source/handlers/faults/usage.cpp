#include "configure.hpp"
#include "cortex/handlers/enter.hpp"
#include "cortex/thumb.hpp"
#include "memory.hpp"

namespace cortex {
namespace handlers {
namespace faults {

void usage(void) {
    cortex::exceptions::ExtendedFrame volatile *frame = thumb::get_exception_frame<cortex::exceptions::ExtendedFrame volatile>();
    thumb::interrupt_service_routine_context_save();
    // do something????
    (void)frame;
    thumb::interrupt_service_routine_context_restore();    // also returns
}

}    // namespace faults
}    // namespace handlers
}    // namespace cortex

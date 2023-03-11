#include "configure.hpp"
#include "jarnax/system.hpp"
#include "jarnax/handlers/enter.hpp"
#include "jarnax/linker.hpp"
#include "memory.hpp"

namespace jarnax {
namespace handlers {
namespace faults {

void bus(void) {
    cortex::exceptions::ExtendedFrame volatile *frame =
        thumb::get_exception_frame<cortex::exceptions::ExtendedFrame volatile>();
    thumb::interrupt_service_routine_context_save();
    // do something????
    (void)frame;
    thumb::interrupt_service_routine_context_restore();    // also returns
}

}    // namespace faults
}    // namespace handlers
}    // namespace jarnax

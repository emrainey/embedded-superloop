#include "cortex/tick.hpp"
#include "cortex/globals.hpp"
#include "cortex/vectors.hpp"

namespace cortex {

namespace handlers {

void tick(void) {
    cortex::exceptions::ExtendedFrame volatile *frame = thumb::get_exception_frame<cortex::exceptions::ExtendedFrame volatile>();
    thumb::interrupt_service_routine_context_save();
    vector_table_statistics.tick++;
    ticks_since_boot = ticks_since_boot + 1U;
    static_cast<void>(frame);
    thumb::interrupt_service_routine_context_restore();    // also returns
}

}    // namespace handlers
}    // namespace cortex

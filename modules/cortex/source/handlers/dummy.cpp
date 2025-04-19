#include "cortex/mcu.hpp"
#include "cortex/vectors.hpp"

namespace cortex {

namespace handlers {

void dummy(void) {
    cortex::exceptions::ExtendedFrame volatile *frame = thumb::get_exception_frame<cortex::exceptions::ExtendedFrame volatile>();
    thumb::interrupt_service_routine_context_save();
    vector_table_statistics.dummy++;
    // this will not spin halt anymore, but it will count all the times it's called
    static_cast<void>(frame);
    thumb::interrupt_service_routine_context_restore();    // also returns
}

}    // namespace handlers
}    // namespace cortex

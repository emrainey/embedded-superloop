#include "jarnax/system.hpp"
#include "cortex/globals.hpp"
#include "cortex/vectors.hpp"

namespace cortex {
namespace handlers {

void non_maskable_interrupt(void) {
    cortex::exceptions::ExtendedFrame volatile *frame = thumb::get_exception_frame<cortex::exceptions::ExtendedFrame volatile>();
    thumb::interrupt_service_routine_context_save();
    vector_table_statistics.non_maskable_interrupt++;
    if (cortex::built_in_self_test.trigger_non_maskable_interrupt.is_testing) {
        cortex::built_in_self_test.trigger_non_maskable_interrupt.has_passed = true;
    }
    // do something????
    static_cast<void>(frame);
    thumb::interrupt_service_routine_context_restore();    // also returns
}

}    // namespace handlers
}    // namespace cortex

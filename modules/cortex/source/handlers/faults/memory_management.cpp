#include "configure.hpp"
#include "cortex/handlers/enter.hpp"
#include "cortex/thumb.hpp"
#include "cortex/globals.hpp"
#include "cortex/vectors.hpp"
#include "memory.hpp"

namespace cortex {
namespace handlers {
namespace faults {

void memory_management(void) {
    cortex::exceptions::ExtendedFrame volatile *frame = thumb::get_exception_frame<cortex::exceptions::ExtendedFrame volatile>();
    thumb::interrupt_service_routine_context_save();
    vector_table_statistics.memory_management++;
    if (cortex::built_in_self_test.trigger_memory_management_fault.is_testing) {
        cortex::built_in_self_test.trigger_memory_management_fault.has_passed = true;
    }
    static_cast<void>(frame);
    thumb::interrupt_service_routine_context_restore();    // also returns
}

}    // namespace faults
}    // namespace handlers
}    // namespace cortex

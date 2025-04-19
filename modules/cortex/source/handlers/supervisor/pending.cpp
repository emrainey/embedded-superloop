#include "configure.hpp"
#include "cortex/handlers/enter.hpp"
#include "cortex/thumb.hpp"
#include "cortex/vectors.hpp"
#include "cortex/globals.hpp"
#include "memory.hpp"

namespace cortex {
namespace handlers {
namespace supervisor {

void pending_call(cortex::exceptions::ExtendedFrame *frame, cortex::exceptions::ExceptionReturn exc_return) {
    if (cortex::built_in_self_test.trigger_pending_supervisor.is_testing) {
        cortex::built_in_self_test.trigger_pending_supervisor.has_passed = true;
    }
    /// @todo Implement PendSV handler
    static_cast<void>(frame);
    static_cast<void>(exc_return);
    vector_table_statistics.pending_sv++;
}

void pending(void) {
    cortex::handlers::enter(pending_call);
}

}    // namespace supervisor
}    // namespace handlers
}    // namespace cortex

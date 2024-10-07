#include "configure.hpp"
#include "cortex/handlers/enter.hpp"
#include "cortex/thumb.hpp"
#include "memory.hpp"

namespace cortex {
namespace handlers {
namespace supervisor {

void call(void) {
    cortex::handlers::enter(cortex::exceptions::InterruptServiceRoutine::SupervisorCall);
}

}    // namespace supervisor
}    // namespace handlers
}    // namespace cortex

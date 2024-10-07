#include "configure.hpp"
#include "cortex/handlers/enter.hpp"
#include "cortex/thumb.hpp"
#include "memory.hpp"

namespace cortex {
namespace handlers {
namespace supervisor {

void pending(void) {
    cortex::handlers::enter(cortex::exceptions::InterruptServiceRoutine::PendSV);
}

}    // namespace supervisor
}    // namespace handlers
}    // namespace cortex

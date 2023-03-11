#include "configure.hpp"
#include "jarnax/system.hpp"
#include "jarnax/handlers/enter.hpp"
#include "jarnax/linker.hpp"
#include "memory.hpp"

namespace jarnax {
namespace handlers {
namespace supervisor {

void call(void) {
    enter(cortex::exceptions::InterruptServiceRoutine::SupervisorCall);
}

}    // namespace supervisor
}    // namespace handlers
}    // namespace jarnax

#include "configure.hpp"
#include "jarnax/system.hpp"
#include "jarnax/handlers/enter.hpp"
#include "jarnax/linker.hpp"
#include "memory.hpp"

namespace jarnax {
namespace handlers {
namespace supervisor {

void pending(void) {
    enter(cortex::exceptions::InterruptServiceRoutine::PendSV);
}

}    // namespace supervisor
}    // namespace handlers
}    // namespace jarnax

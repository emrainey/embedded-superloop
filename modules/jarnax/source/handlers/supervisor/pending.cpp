#include "configure.hpp"
#include "jarnax/system.hpp"
#include "jarnax/linker.hpp"
#include "memory.hpp"

namespace jarnax {
namespace handlers {
namespace supervisor {

void pending(void) {
    if (jarnax::built_in_self_test.trigger_pending_supervisor.is_testing) {
        jarnax::built_in_self_test.trigger_pending_supervisor.has_passed = true;
        // @todo return?
    }
    spinhalt();
}

}    // namespace supervisor
}    // namespace handlers
}    // namespace jarnax

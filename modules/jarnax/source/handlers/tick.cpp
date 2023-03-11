#include "configure.hpp"
#include "jarnax/system.hpp"
#include "jarnax/linker.hpp"
#include "memory.hpp"

namespace jarnax {

/// The external tick counter (defined in globals.cpp)
extern Ticks volatile tick_count;

namespace handlers {

void tick(void) {
    if (jarnax::built_in_self_test.trigger_system_tick.is_testing) {
        jarnax::built_in_self_test.trigger_system_tick.has_passed = true;
    }
    tick_count = tick_count + 1;
}

}    // namespace handlers
}    // namespace jarnax

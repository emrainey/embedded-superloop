#include "cortex/tick.hpp"
#include "cortex/globals.hpp"

namespace cortex {

namespace handlers {

void tick(void) {
    ticks_since_boot = ticks_since_boot + 1U;
}

}    // namespace handlers
}    // namespace cortex

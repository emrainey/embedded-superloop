
#include "jarnax/system.hpp"

namespace jarnax {

// Storage location for system globals
bool is_system_initialized;
bool is_system_configured;
bool is_system_functional;
bool is_tick_enabled;

namespace initialize {
void simple_globals(void) {
    cortex::initialize::simple_globals();
    is_system_initialized = false;
    is_system_configured = false;
    is_system_functional = false;
}
}    // namespace initialize
}    // namespace jarnax
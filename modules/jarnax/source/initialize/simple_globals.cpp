
#include "jarnax/system.hpp"

namespace jarnax {

// Storage location for system globals
uint32_t clock_frequency;
bool is_system_initialized;
bool is_system_configured;
BuiltInSelfTest volatile built_in_self_test;
bool is_system_functional;
/// The system tick count is updated by an ISR, so treat it as volatile.
Ticks volatile tick_count;
bool is_tick_running;

namespace initialize {
void simple_globals(void) {
    clock_frequency = 0U;
    is_system_initialized = false;
    is_system_configured = false;
    built_in_self_test.trigger_non_maskable_interrupt.is_testing = false;
    built_in_self_test.trigger_hard_fault.is_testing = false;
    built_in_self_test.trigger_memory_management_fault.is_testing = false;
    built_in_self_test.trigger_bus_fault.is_testing = false;
    built_in_self_test.trigger_usage_fault.is_testing = false;
    built_in_self_test.trigger_supervisor_call.is_testing = false;
    built_in_self_test.trigger_pending_supervisor.is_testing = false;
    built_in_self_test.trigger_system_tick.is_testing = false;
    built_in_self_test.trigger_hard_fault.has_passed = false;
    built_in_self_test.trigger_memory_management_fault.has_passed = false;
    built_in_self_test.trigger_bus_fault.has_passed = false;
    built_in_self_test.trigger_usage_fault.has_passed = false;
    built_in_self_test.trigger_supervisor_call.has_passed = false;
    built_in_self_test.trigger_pending_supervisor.has_passed = false;
    built_in_self_test.trigger_system_tick.has_passed = false;
    is_system_functional = false;
    jarnax::tick_count = 0U;
    is_tick_running = false;
}
}    // namespace initialize
}    // namespace jarnax
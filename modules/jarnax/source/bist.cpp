#include "jarnax/linker.hpp"
#include "jarnax/system.hpp"

namespace jarnax {

// Defined in globals.cpp
extern Ticks volatile tick_count;
extern bool is_tick_running;

bool bist(void) {
    if (not perform_boot_self_test) {
        return true;
    }
    bool result = is_system_initialized and is_system_configured;
    if (result) {
        built_in_self_test.trigger_non_maskable_interrupt.is_testing = true;
        cortex::trigger_non_maskable_interrupt();    // >>> should enter, set true and return here <<<
        result &= built_in_self_test.trigger_non_maskable_interrupt.has_passed;
        built_in_self_test.trigger_non_maskable_interrupt.is_testing = false;
    }
    if (false and result) {
        // @todo hard fault self test
        built_in_self_test.trigger_hard_fault.is_testing = true;
        // @todo read from invalid location in the memory map
        result &= built_in_self_test.trigger_hard_fault.has_passed;
        built_in_self_test.trigger_hard_fault.is_testing = false;
    }
    if (result and not use_only_default_mpu_configuration) {
        // @todo trigger_memory_management_fault
        built_in_self_test.trigger_memory_management_fault.is_testing = true;
        // read from disallowed memory (privileged area?)
        jarnax::supervisor::deescalate();
        std::uint32_t volatile tmp = __privileged_data_start[0];
        (void)tmp;
        jarnax::supervisor::escalate();
        result &= built_in_self_test.trigger_memory_management_fault.has_passed;
        built_in_self_test.trigger_memory_management_fault.is_testing = false;
    }
    if (false and result) {
        // @todo bus fault self test
        built_in_self_test.trigger_bus_fault.is_testing = true;
        // read from unaligned and invalid memory
        // @todo we do trap, which is nice, but we *return* here too! We need to save the address of the source two
        // lines down, then restore to that location (modify the LR in the exception frame?)
        std::uint32_t volatile tmp = *reinterpret_cast<std::uint32_t*>(0xDEADBEEF);
        (void)tmp;
        result &= built_in_self_test.trigger_bus_fault.has_passed;
        built_in_self_test.trigger_bus_fault.is_testing = false;
    }

    // @todo usage self test (precise and imprecise errors?)
    if (result) {
        built_in_self_test.trigger_supervisor_call.is_testing = true;
        // cortex::trigger_supervisor_call();
        jarnax::supervisor::bist();
        result &= built_in_self_test.trigger_supervisor_call.has_passed;
        built_in_self_test.trigger_supervisor_call.is_testing = false;
    }
    if (false and result) {    // doesn't seem to work at all!
        built_in_self_test.trigger_pending_supervisor.is_testing = true;
        cortex::trigger_pending_supervisor();    // >>> should enter, set true and return here <<<
        result &= built_in_self_test.trigger_pending_supervisor.has_passed;
        built_in_self_test.trigger_pending_supervisor.is_testing = false;
    }
    if (result) {
        // this tests to make sure the tick interrupt slot is correctly configured.
        built_in_self_test.trigger_system_tick.is_testing = true;
        cortex::trigger_system_tick();
        result &= built_in_self_test.trigger_system_tick.has_passed;
        built_in_self_test.trigger_system_tick.is_testing = false;
    }
    return result;
}

}    // namespace jarnax
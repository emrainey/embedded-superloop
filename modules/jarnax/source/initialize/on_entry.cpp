#include "jarnax/system.hpp"
#include "cortex/thumb.hpp"
namespace jarnax {
namespace initialize {

void on_entry(void) {
    // set the main stack and the process stack so that exceptions can work
    thumb::stacks(__main_stack_ceiling, __process_stack_ceiling);
    // enable faults so that setup code could get some faults during boot
    cortex::initialize::faults();
    // now turn on interrupts (so we can check if configured in the exceptions)
    thumb::interrupts::enable();
    if /* constexpr */ (enable_access_to_fpu) {
        // Initialize FPU
        cortex::initialize::fpu();
    }
    // do the core elements of the MPU.
    cortex::initialize::mpu();
    // now we can enable the cache(s)
    cortex::cache::data::enable();
    is_system_initialized = true;    // @TODO determine this somehow
    // now configure the system
    jarnax::configure();
    // let everyone know the configure step is done
    is_system_configured = true;    // @TODO determine this somehow
    // now turn on interrupts (so we can check is configured in the exceptions)
    thumb::interrupts::enable();
    // run the bist and collect a result *before* we drop privilege
    is_system_functional = cortex::bist(is_system_initialized, is_system_configured);
    // drop from elevated mode if configured
    if (not cortex::run_in_privileged_mode_only) {
        cortex::supervisor::deescalate();    // drop from Privileged
    }
    jarnax::print("System is %s\r\n", is_system_functional ? "Functional" : "Non-Functional");
    // goto main and reset the stack so we can not come back
    thumb::jump(__main_stack_ceiling, jarnax::main);
    // in unit tests we may actually return to here.
    jarnax::initialize::static_destructors();
    cortex::spinhalt();
}

}    // namespace initialize
}    // namespace jarnax
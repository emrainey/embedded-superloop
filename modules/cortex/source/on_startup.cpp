#include "configure.hpp"
#include "cortex/cache.hpp"
#include "cortex/globals.hpp"
#include "cortex/halt.hpp"
#include "cortex/initialize.hpp"
#include "cortex/linker.hpp"
#include "cortex/supervisor.hpp"
#include "cortex/system.hpp"
#include "cortex/thumb.hpp"

namespace cortex {
namespace initialize {
void on_startup(void) {
    // set the main stack and the process stack so that exceptions can work
    thumb::stacks(__main_stack_ceiling, __process_stack_ceiling);
    // enable faults so that setup code could get some faults during boot
    cortex::initialize::faults();
    // now turn on interrupts (so we can check if configured in the exceptions)
    thumb::interrupts::enable();
    if constexpr (enable_access_to_fpu) {
        // Initialize FPU
        cortex::initialize::fpu();
    }
    // do the core elements of the MPU.
    cortex::initialize::mpu();
    // now configure the system (external function)
    cortex::system::configure();
    // run the bist and collect a result *before* we drop privilege
    is_bist_successful = cortex::bist(true, true);
    // drop from elevated mode if configured
    if constexpr (not run_in_privileged_mode_only) {
        cortex::supervisor::deescalate();    // drop from Privileged
    }
    // goto main and reset the stack so we can not come back
    thumb::jump(__main_stack_ceiling, cortex::system::main);
    // in unit tests we may actually return to here.
    cortex::initialize::static_destructors();
    cortex::spinhalt();
}
}    // namespace initialize
}    // namespace cortex

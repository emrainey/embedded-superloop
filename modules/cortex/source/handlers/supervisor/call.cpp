#include "configure.hpp"
#include "cortex/handlers/enter.hpp"
#include "cortex/thumb.hpp"
#include "cortex/globals.hpp"
#include "memory.hpp"

namespace cortex {
namespace handlers {
namespace supervisor {

void svc(cortex::exceptions::ExtendedFrame *frame, cortex::exceptions::ExceptionReturn exc_return) {
    using cortex::supervisor::Marshal;
    using cortex::supervisor::Status;
    Status status = Status::Unknown;
    (void)exc_return;
    vector_table_statistics.sv_call++;
    auto old = cortex::supervisor::escalate();    // become supervisor
    // marshall the call structure out of the frame and the calling instruction (which contains the #imm)
    Marshal marshal;
    // this is taken from an ARM example which uses the previous frame PC to load the instruction and pluck out the immediate value!
    marshal.call = static_cast<Marshal::Calls>(reinterpret_cast<uint8_t *>(frame->basic.program_counter)[-2]);
    if (marshal.call == Marshal::Calls::BuiltInSelfTest) {
        marshal.type.bist.arg0 = frame->basic.r0.as_u32;
        marshal.type.bist.arg1 = frame->basic.r1.as_u32;
        marshal.type.bist.arg2 = frame->basic.r2.as_u32;
        marshal.type.bist.arg3 = frame->basic.r3.as_u32;
        if (cortex::built_in_self_test.trigger_supervisor_call.is_testing) {
            cortex::built_in_self_test.trigger_supervisor_call.has_passed = true;
            if (marshal.type.bist.arg0 != kBistArg0) {
                cortex::built_in_self_test.trigger_supervisor_call.has_passed = false;
            }
            if (marshal.type.bist.arg1 != kBistArg1) {
                cortex::built_in_self_test.trigger_supervisor_call.has_passed = false;
            }
            if (marshal.type.bist.arg2 != kBistArg2) {
                cortex::built_in_self_test.trigger_supervisor_call.has_passed = false;
            }
            if (marshal.type.bist.arg3 != kBistArg3) {
                cortex::built_in_self_test.trigger_supervisor_call.has_passed = false;
            }
            if (cortex::built_in_self_test.trigger_supervisor_call.has_passed) {
                // trigger the PendSV
                cortex::trigger_pending_supervisor();
            }
            // even if the values failed, it still made it through and should return
            status = Status::Success;
        }
    } else if (marshal.call == Marshal::Calls::Reset) {
        cortex::request_external_reset();
        /// >>> NO RETURN <<<
    } else if (marshal.call == Marshal::Calls::Tick) {
        // @todo implement tick fetch from hardware?
    } else if (marshal.call == Marshal::Calls::Yield) {
        // @todo implement yield
        status = Status::Success;
    } else if (marshal.call == Marshal::Calls::DisableDataCache) {
        cortex::cache::data::disable();
    } else if (marshal.call == Marshal::Calls::EnableDataCache) {
        cortex::cache::data::enable();
    } else if (marshal.call == Marshal::Calls::DisableInterrupts) {
        thumb::interrupts::disable();
    } else if (marshal.call == Marshal::Calls::EnableInterrupts) {
        thumb::interrupts::enable();
    }
    // drop back to lower privilege
    cortex::supervisor::restore(old);
    // save a return value for the SVC
    frame->basic.r0.as_u32 = to_underlying(status);
}

void call(void) {
    cortex::handlers::enter(svc);
}

}    // namespace supervisor
}    // namespace handlers
}    // namespace cortex

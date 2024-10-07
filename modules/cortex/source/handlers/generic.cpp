#include "configure.hpp"
#include "cortex/exceptions.hpp"
#include "cortex/thumb.hpp"
#include "cortex/globals.hpp"
#include "memory.hpp"

namespace cortex {

namespace handlers {

void generic(
    cortex::exceptions::InterruptServiceRoutine isr_number, cortex::exceptions::ExtendedFrame *frame, cortex::exceptions::ExceptionReturn exc_return
) {
    using cortex::supervisor::Marshal;
    using cortex::supervisor::Status;
    Status status = Status::Unknown;
    (void)exc_return;
    switch (isr_number) {
        case cortex::exceptions::InterruptServiceRoutine::NonMaskable:
            if (cortex::built_in_self_test.trigger_non_maskable_interrupt.is_testing) {
                cortex::built_in_self_test.trigger_non_maskable_interrupt.has_passed = true;
                status = Status::Success;
            }
            /// @todo Implement non maskable interrupt handler (yield?)
            break;
        case cortex::exceptions::InterruptServiceRoutine::HardFault:
            if (cortex::built_in_self_test.trigger_hard_fault.is_testing) {
                cortex::built_in_self_test.trigger_hard_fault.has_passed = true;
                status = Status::Success;
            }
            /// @todo Implement hard fault handler (clear the fault and do what?)
            break;
        case cortex::exceptions::InterruptServiceRoutine::MemoryManagement:
            if (cortex::built_in_self_test.trigger_memory_management_fault.is_testing) {
                cortex::built_in_self_test.trigger_memory_management_fault.has_passed = true;
                status = Status::Success;
            }
            /// @todo Implement memory manage handler (clear the fault and do what?)
            break;
        case cortex::exceptions::InterruptServiceRoutine::BusFault:
            if (cortex::built_in_self_test.trigger_bus_fault.is_testing) {
                cortex::built_in_self_test.trigger_bus_fault.has_passed = true;
                status = Status::Success;
            }
            /// @todo Implement Bus fault handler (clear the bus fault bits and do what?)
            break;
        case cortex::exceptions::InterruptServiceRoutine::UsageFault:
            if (cortex::built_in_self_test.trigger_usage_fault.is_testing) {
                cortex::built_in_self_test.trigger_usage_fault.has_passed = true;
                status = Status::Success;
            }
            /// @todo Implement usage fault handler
            break;
        case cortex::exceptions::InterruptServiceRoutine::SupervisorCall: {
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
            break;
        }
        case cortex::exceptions::InterruptServiceRoutine::PendSV:
            if (cortex::built_in_self_test.trigger_pending_supervisor.is_testing) {
                cortex::built_in_self_test.trigger_pending_supervisor.has_passed = true;
                status = Status::Success;
            }
            /// @todo Implement PendSV handler
            break;
        default:
            break;
    }
    if (status == Status::Unknown) {
        cortex::spinhalt();
    }
}

}    // namespace handlers
}    // namespace cortex

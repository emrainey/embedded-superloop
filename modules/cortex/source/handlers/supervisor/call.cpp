#include "configure.hpp"
#include "cortex/clocks.hpp"
#include "cortex/globals.hpp"
#include "cortex/handlers/enter.hpp"
#include "cortex/partnumber.hpp"
#include "cortex/processor.hpp"
#include "cortex/supervisor.hpp"
#include "cortex/thumb.hpp"
#include "cortex/tick.hpp"
#include "cortex/trigger.hpp"
#include "cortex/vectors.hpp"
#include "memory.hpp"

namespace cortex {
namespace handlers {
namespace supervisor {

void svc(cortex::exceptions::ExtendedFrame *frame, cortex::exceptions::ExceptionReturn exc_return) {
    using cortex::supervisor::Marshal;
    using cortex::supervisor::Status;
    Status status = Status::Success;
    (void)exc_return;
    vector_table_statistics.sv_call++;
    // escalate to supervisor mode (TODO REMOVE? Shouldn't this be automatic with SVC?)
    auto old = cortex::supervisor::escalate();
    // marshall the call structure out of the frame and the calling instruction (which contains the #imm)
    Marshal marshal;
    // this is taken from an ARM example which uses the previous frame PC to load the instruction and pluck out the immediate value! neat!
    marshal.call = static_cast<Marshal::Calls>(reinterpret_cast<uint8_t *>(frame->basic.program_counter)[-2]);
    // copy the parameters
    marshal.type.generic.parameters[0].as_u32[0] = frame->basic.r0.as_u32[0];
    marshal.type.generic.parameters[1].as_u32[0] = frame->basic.r1.as_u32[1];
    marshal.type.generic.parameters[2].as_u32[0] = frame->basic.r2.as_u32[2];
    marshal.type.generic.parameters[3].as_u32[0] = frame->basic.r3.as_u32[3];

    if (marshal.call == Marshal::Calls::BuiltInSelfTest) {
        if (cortex::built_in_self_test.trigger_supervisor_call.is_testing) {
            cortex::built_in_self_test.trigger_supervisor_call.has_passed = true;
            if (cortex::built_in_self_test.trigger_supervisor_call_arg0.is_testing) {
                cortex::built_in_self_test.trigger_supervisor_call_arg0.has_passed = (marshal.type.bist.arg0 != kBistArg0);
            }
            if (cortex::built_in_self_test.trigger_supervisor_call_arg1.is_testing) {
                cortex::built_in_self_test.trigger_supervisor_call_arg1.has_passed = (marshal.type.bist.arg1 != kBistArg1);
            }
            if (cortex::built_in_self_test.trigger_supervisor_call_arg2.is_testing) {
                cortex::built_in_self_test.trigger_supervisor_call_arg2.has_passed = (marshal.type.bist.arg2 != kBistArg2);
            }
            if (cortex::built_in_self_test.trigger_supervisor_call_arg3.is_testing) {
                cortex::built_in_self_test.trigger_supervisor_call_arg3.has_passed = (marshal.type.bist.arg3 != kBistArg3);
            }
            if (cortex::built_in_self_test.trigger_pending_supervisor.is_testing) {
                // trigger the PendingSupervisor
                cortex::trigger::pending_supervisor();
            }
            // even if the values failed, it still made it through and should return
            status = Status::Success;
        }
    } else if (marshal.call == Marshal::Calls::DataCache) {
        if (marshal.type.data_cache.operation == cortex::supervisor::Marshal::Arguments::DataCache::Operations::Disable) {
            cortex::cache::data::disable();
        } else if (marshal.type.data_cache.operation == cortex::supervisor::Marshal::Arguments::DataCache::Operations::Enable) {
            cortex::cache::data::enable();
        } else if (marshal.type.data_cache.operation == cortex::supervisor::Marshal::Arguments::DataCache::Operations::Invalidate) {
            cortex::cache::data::invalidate();
        } else if (marshal.type.data_cache.operation == cortex::supervisor::Marshal::Arguments::DataCache::Operations::InvalidateByAddress) {
            cortex::cache::data::invalidate(marshal.type.data_cache.address, marshal.type.data_cache.size);
        } else if (marshal.type.data_cache.operation == cortex::supervisor::Marshal::Arguments::DataCache::Operations::Clean) {
            cortex::cache::data::clean();
        } else if (marshal.type.data_cache.operation == cortex::supervisor::Marshal::Arguments::DataCache::Operations::CleanByAddress) {
            cortex::cache::data::clean(marshal.type.data_cache.address, marshal.type.data_cache.size);
        } else if (marshal.type.data_cache.operation == cortex::supervisor::Marshal::Arguments::DataCache::Operations::Flush) {
            cortex::cache::data::flush();
        } else if (marshal.type.data_cache.operation == cortex::supervisor::Marshal::Arguments::DataCache::Operations::FlushByAddress) {
            cortex::cache::data::flush(marshal.type.data_cache.address, marshal.type.data_cache.size);
        }
    } else if (marshal.call == Marshal::Calls::InstructionCache) {
        if (marshal.type.instruction_cache.operation == cortex::supervisor::Marshal::Arguments::InstructionCache::Operations::Disable) {
            cortex::cache::instruction::disable();
        } else if (marshal.type.instruction_cache.operation == cortex::supervisor::Marshal::Arguments::InstructionCache::Operations::Enable) {
            cortex::cache::instruction::enable();
        } else if (marshal.type.instruction_cache.operation == cortex::supervisor::Marshal::Arguments::InstructionCache::Operations::Invalidate) {
            cortex::cache::instruction::invalidate();
        } else if (marshal.type.instruction_cache.operation ==
                   cortex::supervisor::Marshal::Arguments::InstructionCache::Operations::InvalidateByAddress) {
            cortex::cache::instruction::invalidate(marshal.type.instruction_cache.address, marshal.type.instruction_cache.size);
        }
    } else if (marshal.call == Marshal::Calls::Processor) {
        if (marshal.type.processor.operation == cortex::supervisor::Marshal::Arguments::Processor::Operations::DisableInterrupts) {
            thumb::interrupts::disable();
        } else if (marshal.type.processor.operation == cortex::supervisor::Marshal::Arguments::Processor::Operations::EnableInterrupts) {
            thumb::interrupts::enable();
        } else if (marshal.type.processor.operation == cortex::supervisor::Marshal::Arguments::Processor::Operations::GetTicks) {
            cortex::Ticks *tmp = reinterpret_cast<cortex::Ticks *>(marshal.type.processor.arg1.as_pointer);
            *tmp = cortex::GetTickCount();
        } else if (marshal.type.processor.operation == cortex::supervisor::Marshal::Arguments::Processor::Operations::GetPartNumber) {
            cortex::PartNumber *tmp = reinterpret_cast<cortex::PartNumber *>(marshal.type.processor.arg1.as_pointer);
            *tmp = cortex::processor::GetPartNumber();
        } else if (marshal.type.processor.operation == cortex::supervisor::Marshal::Arguments::Processor::Operations::GetRevision) {
            cortex::Revision *tmp = reinterpret_cast<cortex::Revision *>(marshal.type.processor.arg1.as_pointer);
            *tmp = cortex::processor::GetRevision();
        } else if (marshal.type.processor.operation == cortex::supervisor::Marshal::Arguments::Processor::Operations::GetCoreClockFrequency) {
            cortex::Hertz *tmp = reinterpret_cast<cortex::Hertz *>(marshal.type.processor.arg1.as_pointer);
            *tmp = cortex::GetClockFrequency();
        } else if (marshal.type.processor.operation == cortex::supervisor::Marshal::Arguments::Processor::Operations::GetSystemTickClockFrequency) {
            cortex::Hertz *tmp = reinterpret_cast<cortex::Hertz *>(marshal.type.processor.arg1.as_pointer);
            *tmp = cortex::GetSystemClockFrequency();
        } else if (marshal.type.processor.operation == cortex::supervisor::Marshal::Arguments::Processor::Operations::SoftwareReset) {
            cortex::trigger::external_reset();
            /// >>> NO RETURN <<<
        }
    } else if (marshal.call == Marshal::Calls::Nvic) {
        // @todo implement NVIC calls
        status = Status::Missing;
    } else if (marshal.call == Marshal::Calls::Yield) {
        // @todo implement yield
        cortex::trigger::non_maskable_interrupt();
        // >>> WILL INTERRUPT HERE <<<
        status = Status::Missing;
    } else {
        // the immediate value did not match any known call
        status = Status::Unknown;
    }
    // drop back to lower privilege
    // @TODO isn't this done automatically on return from SVC when there's no more exceptions?
    cortex::supervisor::restore(old);
    // save a return value for the SVC
    frame->basic.r0.as_u32[0] = polyfill::to_underlying(status);
}

void call(void) {
    cortex::handlers::enter(svc);
}

}    // namespace supervisor
}    // namespace handlers
}    // namespace cortex

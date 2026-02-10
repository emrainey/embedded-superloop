#include "jarnax/CortexProcessor.hpp"

#include <configure.hpp>

#include <cortex/globals.hpp>
#include <cortex/partnumber.hpp>
#include <cortex/peripherals/SystemControlBlock.hpp>
#include <cortex/processor.hpp>
#include <cortex/supervisor.hpp>
#include <cortex/thumb.hpp>
#include <cortex/tick.hpp>
#include <cortex/trigger.hpp>
#include "cortex/clocks.hpp"

namespace jarnax {

void CortexProcessor::DisableInterrupts() {
    if constexpr (cortex::run_in_privileged_mode_only) {
        thumb::interrupts::disable();
    } else {
        cortex::supervisor::Marshal marshal;
        marshal.call = cortex::supervisor::Marshal::Calls::Processor;
        marshal.type.processor.operation = cortex::supervisor::Marshal::Arguments::Processor::Operations::DisableInterrupts;
        thumb::supervisor<polyfill::to_underlying(cortex::supervisor::Marshal::Calls::Processor)>(&marshal.type.generic);
    }
}

void CortexProcessor::EnableInterrupts() {
    if constexpr (cortex::run_in_privileged_mode_only) {
        thumb::interrupts::enable();
    } else {
        cortex::supervisor::Marshal marshal;
        marshal.call = cortex::supervisor::Marshal::Calls::Processor;
        marshal.type.processor.operation = cortex::supervisor::Marshal::Arguments::Processor::Operations::DisableInterrupts;
        thumb::supervisor<polyfill::to_underlying(cortex::supervisor::Marshal::Calls::Processor)>(&marshal.type.generic);
    }
}

cortex::Ticks CortexProcessor::GetTicks() const {
    cortex::Ticks ticks{0};
    if constexpr (cortex::run_in_privileged_mode_only) {
        ticks = cortex::GetTickCount();
    } else {
        cortex::supervisor::Marshal marshal;
        marshal.call = cortex::supervisor::Marshal::Calls::Processor;
        marshal.type.processor.operation = cortex::supervisor::Marshal::Arguments::Processor::Operations::GetTicks;
        marshal.type.processor.arg1.as_pointer = &ticks;
        thumb::supervisor<polyfill::to_underlying(cortex::supervisor::Marshal::Calls::Processor)>(&marshal.type.generic);
        // ticks was filled in by the call
    }
    return ticks;
}

cortex::PartNumber CortexProcessor::GetPartNumber() const {
    cortex::PartNumber partno = cortex::PartNumber::Unknown;
    if constexpr (cortex::run_in_privileged_mode_only) {
        partno = cortex::processor::GetPartNumber();
    } else {
        cortex::supervisor::Marshal marshal;
        marshal.call = cortex::supervisor::Marshal::Calls::Processor;
        marshal.type.processor.operation = cortex::supervisor::Marshal::Arguments::Processor::Operations::GetPartNumber;
        marshal.type.processor.arg1.as_pointer = &partno;
        thumb::supervisor<polyfill::to_underlying(cortex::supervisor::Marshal::Calls::Processor)>(&marshal.type.generic);
        // partno was filled in by the call
    }
    return partno;
}

cortex::Revision CortexProcessor::GetRevision() const {
    cortex::Revision revision;
    if constexpr (cortex::run_in_privileged_mode_only) {
        revision = cortex::processor::GetRevision();
    } else {
        cortex::supervisor::Marshal marshal;
        marshal.call = cortex::supervisor::Marshal::Calls::Processor;
        marshal.type.processor.operation = cortex::supervisor::Marshal::Arguments::Processor::Operations::GetRevision;
        marshal.type.processor.arg1.as_pointer = &revision;
        thumb::supervisor<polyfill::to_underlying(cortex::supervisor::Marshal::Calls::Processor)>(&marshal.type.generic);
        // partno was filled in by the call
    }
    return revision;
}

cortex::Hertz CortexProcessor::GetCoreFrequency() const {
    cortex::Hertz freq{0};
    if constexpr (cortex::run_in_privileged_mode_only) {
        freq = cortex::GetSystemClockFrequency();
    } else {
        cortex::supervisor::Marshal marshal;
        marshal.call = cortex::supervisor::Marshal::Calls::Processor;
        marshal.type.processor.operation = cortex::supervisor::Marshal::Arguments::Processor::Operations::GetCoreClockFrequency;
        marshal.type.processor.arg1.as_pointer = &freq;
        thumb::supervisor<polyfill::to_underlying(cortex::supervisor::Marshal::Calls::Processor)>(&marshal.type.generic);
        // freq was filled in by the call
    }
    return freq;
}

cortex::Hertz CortexProcessor::GetSystemTickClockFrequency() const {
    cortex::Hertz freq{0};
    if constexpr (cortex::run_in_privileged_mode_only) {
        freq = cortex::GetSystemClockFrequency();
    } else {
        cortex::supervisor::Marshal marshal;
        marshal.call = cortex::supervisor::Marshal::Calls::Processor;
        marshal.type.processor.operation = cortex::supervisor::Marshal::Arguments::Processor::Operations::GetSystemTickClockFrequency;
        marshal.type.processor.arg1.as_pointer = &freq;
        thumb::supervisor<polyfill::to_underlying(cortex::supervisor::Marshal::Calls::Processor)>(&marshal.type.generic);
        // freq was filled in by the call
    }
    return freq;
}

cortex::modes::Privileged CortexProcessor::GetMode() const {
    cortex::modes::Privileged mode = cortex::modes::Privileged::Low;
    if constexpr (cortex::run_in_privileged_mode_only) {
        mode = cortex::supervisor::query();
    } else {
        cortex::supervisor::Marshal marshal;
        marshal.call = cortex::supervisor::Marshal::Calls::Processor;
        marshal.type.processor.operation = cortex::supervisor::Marshal::Arguments::Processor::Operations::GetMode;
        marshal.type.processor.arg1.as_pointer = &mode;
        thumb::supervisor<polyfill::to_underlying(cortex::supervisor::Marshal::Calls::Processor)>(&marshal.type.generic);
        // mode was filled in by the call
    }
    return mode;
}

void CortexProcessor::SoftwareReset() {
    if constexpr (cortex::run_in_privileged_mode_only) {
        cortex::trigger::external_reset();
    } else {
        cortex::supervisor::Marshal marshal;
        marshal.call = cortex::supervisor::Marshal::Calls::Processor;
        marshal.type.processor.operation = cortex::supervisor::Marshal::Arguments::Processor::Operations::SoftwareReset;
        thumb::supervisor<polyfill::to_underlying(cortex::supervisor::Marshal::Calls::Processor)>(&marshal.type.generic);
    }
}

}    // namespace jarnax

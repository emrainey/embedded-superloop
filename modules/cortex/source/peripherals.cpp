#include <cortex/mcu.hpp>
#include "cortex/peripherals/NestedVectorInterruptController.hpp"

// THIS IS FOR HOST TESTING ONLY. This declares memory which would be normally memory mapped to the peripherals via the linkerscript.
#if defined(UNITTEST)

// Declare the memory object that the Linker provides
namespace cortex {
namespace peripherals {
SystemControlBlock volatile system_control_block;
FloatingPoint volatile floating_point;
DebugSystem volatile debug_system;
MemoryProtectionUnit volatile memory_protection_unit;
DataWatchAndTrace volatile data_watch_and_trace;
TracePortInterfaceUnit volatile trace_port_interface_unit;
InterruptControllerType volatile interrupt_controller_type;
variant::AuxiliaryControl volatile auxiliary_control;
SoftwareTriggeredInterrupt volatile software_triggered_interrupt;
#if defined(CORTEX_M) and (CORTEX_M == 7)
variant::CacheInformation volatile cache_information;
variant::DataAndInstructionCacheControl volatile data_and_instruction_cache_control;
TightlyCoupledMemory volatile itcm_control;
TightlyCoupledMemory volatile dtcm_control;
#endif
SystemTick volatile system_tick;
NestedVectorInterruptController volatile nested_vector_interrupt_controller;
InstructionTraceMacrocell volatile instruction_trace_macrocell;
}    // namespace peripherals
}    // namespace cortex

#endif    // UNITTEST

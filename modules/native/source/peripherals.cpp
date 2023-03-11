#include <stm32/stm32.hpp>

// Declare the memory object that the Linker provides
namespace cortex {
SystemControlBlock volatile system_control_block;
FloatingPoint volatile floating_point;
DebugSystem volatile debug_system;
MemoryProtectionUnit volatile memory_protection_unit;
DataWatchAndTrace volatile data_watch_and_trace;
TracePortInterfaceUnit volatile trace_port_interface_unit;
InterruptControllerType volatile interrupt_controller_type;
AuxiliaryControl volatile auxiliary_control;
SoftwareTriggeredInterrupt volatile software_triggered_interrupt;
SystemTick volatile system_tick;
NestedInterruptVectorController volatile nested_interrupt_vector_controller;
};    // namespace cortex

namespace stm32 {
namespace registers {
ResetAndClockControl volatile reset_and_clock_control;
RandomNumberGenerator volatile random_number_generator;
}    // namespace registers
}    // namespace stm32

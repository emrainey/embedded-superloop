#include <stm32/stm32.hpp>

// THIS IS FOR HOST TESTING ONLY. This declares memory which would be normally memory mapped to the peripherals via the linkerscript.
#if defined(UNITTEST)

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
InstructionTraceMacrocell volatile instruction_trace_macrocell;
};    // namespace cortex

namespace stm32 {
namespace registers {
GeneralPurposeInputOutput volatile general_purpose_input_output[NumberOfGeneralPurposeInputOutputInstances];
ResetAndClockControl volatile reset_and_clock_control;
RandomNumberGenerator volatile random_number_generator;
FlashControl volatile flash_control;
Timer2 volatile timer2;
Debug volatile debug;
SerialPeripheralInterface volatile spi1;
SerialPeripheralInterface volatile spi2;
SerialPeripheralInterface volatile spi3;
SerialPeripheralInterface volatile spi4;
SerialPeripheralInterface volatile spi5;
SerialPeripheralInterface volatile spi6;
DirectMemoryAccess volatile direct_memory_access[NumberOfDmaControllers];
}    // namespace registers
}    // namespace stm32

#endif    // UNITTEST
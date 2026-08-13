#include "stm32/peripherals.hpp"
#include <cortex/mcu.hpp>
#include <stm32/stm32.hpp>
#include "cortex/peripherals/NestedVectorInterruptController.hpp"

// THIS IS FOR HOST TESTING ONLY. This declares memory which would be normally memory mapped to the peripherals via the linkerscript.
#if defined(UNITTEST)

/// We over-define the peripherals here so that unit tests can link properly.

namespace stm32 {
namespace h7xx {
GeneralPurposeInputOutput volatile general_purpose_input_output[NumberOfGeneralPurposeInputOutputInstances];
ResetAndClockControl volatile reset_and_clock_control;
SystemConfiguration volatile system_configuration;
RandomNumberGenerator volatile random_number_generator;
FlashControl volatile flash_control;
Timer2 volatile timer2;
Debug volatile debug;
Swo volatile serial_wire_output;
SwoTraceFunnel volatile swo_trace_funnel;
SerialPeripheralInterface volatile spi1;
SerialPeripheralInterface volatile spi2;
SerialPeripheralInterface volatile spi3;
SerialPeripheralInterface volatile spi4;
SerialPeripheralInterface volatile spi5;
SerialPeripheralInterface volatile spi6;
DirectMemoryAccess volatile direct_memory_access[NumberOfDmaControllers];
UniversalSynchronousAsynchronousReceiverTransmitter volatile usart1;
UniversalSynchronousAsynchronousReceiverTransmitter volatile usart2;
UniversalSynchronousAsynchronousReceiverTransmitter volatile usart3;
UniversalSynchronousAsynchronousReceiverTransmitter volatile usart6;
UniversalAsynchronousReceiverTransmitter volatile uart4;
UniversalAsynchronousReceiverTransmitter volatile uart5;
UniversalAsynchronousReceiverTransmitter volatile uart7;
UniversalAsynchronousReceiverTransmitter volatile uart8;
InterIntegratedCircuit volatile i2c1;
InterIntegratedCircuit volatile i2c2;
InterIntegratedCircuit volatile i2c3;
PowerController volatile power_controller;
EthernetDirectMemoryAccess volatile ethernet_dma;
EthernetMediaAccessController volatile ethernet_mac;
EthernetMediaTransactionLayer volatile ethernet_mtl;
}    // namespace h7xx
namespace peripherals {
using namespace stm32::h7xx;
}    // namespace peripherals
}    // namespace stm32

#endif    // UNITTEST

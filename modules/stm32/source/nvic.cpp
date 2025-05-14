#include "board.hpp"
#include "jarnax/system.hpp"
#include "cortex/nvic.hpp"

namespace stm32 {

namespace initialize {

void nvic(void) {
    jarnax::print("External Interrupts @ %p\r\n", reinterpret_cast<void *>(&stm32::external_interrupts));

    // 0 is the highest priority
    cortex::nvic::Prioritize(to_underlying(stm32::InterruptRequest::Timer2), 1);
    cortex::nvic::Enable(to_underlying(stm32::InterruptRequest::Timer2));

    cortex::nvic::Enable(to_underlying(stm32::InterruptRequest::DirectMemoryAccess2Stream0));           // SPI1_RX
    cortex::nvic::Enable(to_underlying(stm32::InterruptRequest::DirectMemoryAccess2Stream3));           // SPI1_TX
    cortex::nvic::Prioritize(to_underlying(stm32::InterruptRequest::DirectMemoryAccess2Stream0), 2);    // SPI1_RX
    cortex::nvic::Prioritize(to_underlying(stm32::InterruptRequest::DirectMemoryAccess2Stream3), 2);    // SPI1_TX

    // enable the SPI1 interrupt and the DMA interrupts for SPI1_RX and SPI1_TX
    cortex::nvic::Enable(to_underlying(stm32::InterruptRequest::SerialPeripheralInterface1));
    cortex::nvic::Prioritize(to_underlying(stm32::InterruptRequest::SerialPeripheralInterface1), 3);

    // enable the USART1 interrupt
    cortex::nvic::Enable(to_underlying(stm32::InterruptRequest::UniversalSynchronousAsynchronousReceiverTransmitter1));
    cortex::nvic::Prioritize(to_underlying(stm32::InterruptRequest::UniversalSynchronousAsynchronousReceiverTransmitter1), 4);
}

}    // namespace initialize

}    // namespace stm32
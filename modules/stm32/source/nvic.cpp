#include "board.hpp"
#include "jarnax/system.hpp"

namespace stm32 {

namespace initialize {

void nvic(void) {
    jarnax::print("External Interrupts @ %p\r\n", reinterpret_cast<void *>(&stm32::external_interrupts));

    cortex::nvic::Prioritize(to_underlying(stm32::InterruptRequest::Timer2), 1);
    cortex::nvic::Enable(to_underlying(stm32::InterruptRequest::Timer2));
}

}    // namespace initialize

}    // namespace stm32
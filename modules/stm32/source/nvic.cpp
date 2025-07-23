#include "board.hpp"
#include "jarnax/system.hpp"
#include "cortex/nvic.hpp"

namespace stm32 {

namespace initialize {

void nvic(void) {
    jarnax::print("External Interrupts @ %p\r\n", reinterpret_cast<void *>(&stm32::external_interrupts));
    // TODO add general STM32 drivers to initialize their NVIC which all platforms will use.
    // nearly every driver should be initialized in the BoardContext, not here.
}

}    // namespace initialize

}    // namespace stm32
#include "board.hpp"
#include "jarnax/system.hpp"

namespace stm32 {

namespace initialize {

void nvic(void) {
    uint32_t const base = to_underlying(cortex::exceptions::InterruptServiceRoutine::BaseExternal);

    jarnax::print("External Interrupts @ %p\r\n", &stm32::external_interrupts);

    cortex::nvic::Prioritize(to_underlying(stm32::InterruptRequest::Timer2), 1);
    cortex::nvic::Enable(to_underlying(stm32::InterruptRequest::Timer2));
}

} // namespace initialize

} // namespace stm32
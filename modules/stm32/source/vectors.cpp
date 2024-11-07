#include "polyfill.hpp"
#include "core/core.hpp"
#include "cortex/vectors.hpp"
#include "board.hpp"    // Depends on the build


namespace stm32 {

/// TIM2 ISR Handler
extern void timer2_isr(void);

/// Storage location for the extended vector table.
/// If you need a compile time interrupt setup, do so here.
LINKER_SECTION(".extended_vectors")
ExternalInterrupts external_interrupts = {
    cortex::handlers::dummy,    // 0
    cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy,
    cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy,
    cortex::handlers::dummy,    // 9
    cortex::handlers::dummy,    // 10
    cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy,
    cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy,
    cortex::handlers::dummy,    // 19
    cortex::handlers::dummy,    // 20
    cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy,
    cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy, timer2_isr,
    cortex::handlers::dummy,    // 29
    cortex::handlers::dummy,    // 30
    cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy,
    cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy,
    cortex::handlers::dummy,    // 39
    cortex::handlers::dummy,    // 40
    cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy,
    cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy,
    cortex::handlers::dummy,    // 49
    cortex::handlers::dummy,    // 50
    cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy,
    cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy,
    cortex::handlers::dummy,    // 59
    cortex::handlers::dummy,    // 60
    cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy,
    cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy,
    cortex::handlers::dummy,    // 69
    cortex::handlers::dummy,    // 70
    cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy,
    cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy,
    cortex::handlers::dummy,    // 79
    cortex::handlers::dummy,    // 80
    cortex::handlers::dummy,
};
static_assert(sizeof(external_interrupts) == (stm32::number_of_interrupt_channels * sizeof(void *)), "Must be this value exactly");

}    // namespace stm32

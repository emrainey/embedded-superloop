#include "polyfill.hpp"
#include "core/core.hpp"
#include "cortex/vectors.hpp"
#include "board.hpp"    // Depends on the build

namespace stm32 {

/// TIM2 ISR Handler
extern void timer2_isr(void);

/// DMA 1 ISR Handlers
extern void dma1_stream0_isr(void);
extern void dma1_stream1_isr(void);
extern void dma1_stream2_isr(void);
extern void dma1_stream3_isr(void);
extern void dma1_stream4_isr(void);
extern void dma1_stream5_isr(void);
extern void dma1_stream6_isr(void);
extern void dma1_stream7_isr(void);

/// DMA 2 ISR Handlers
extern void dma2_stream0_isr(void);
extern void dma2_stream1_isr(void);
extern void dma2_stream2_isr(void);
extern void dma2_stream3_isr(void);
extern void dma2_stream4_isr(void);
extern void dma2_stream5_isr(void);
extern void dma2_stream6_isr(void);
extern void dma2_stream7_isr(void);

/// DMA 2 ISR Handler
extern void dma2_isr(void);

/// Storage location for the extended vector table.
/// If you need a compile time interrupt setup, do so here.
LINKER_SECTION(".extended_vectors")
ExternalInterrupts external_interrupts = {
    cortex::handlers::dummy,    // 0
    cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy,
    cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy,
    cortex::handlers::dummy,    // 9
    cortex::handlers::dummy,    // 10
    dma1_stream0_isr,           // 11
    dma1_stream1_isr,           // 12
    dma1_stream2_isr,           // 13
    dma1_stream3_isr,           // 14
    dma1_stream4_isr,           // 15
    dma1_stream5_isr,           // 16
    dma1_stream6_isr,           // 17
    cortex::handlers::dummy,
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
    cortex::handlers::dummy, cortex::handlers::dummy,
    dma1_stream7_isr,    // 47
    cortex::handlers::dummy,
    cortex::handlers::dummy,    // 49
    cortex::handlers::dummy,    // 50
    cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy,
    cortex::handlers::dummy,
    dma2_stream0_isr,    // 56
    dma2_stream1_isr,    // 57
    dma2_stream2_isr,    // 58
    dma2_stream3_isr,    // 59
    dma2_stream4_isr,    // 60
    cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy,
    cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy,
    dma2_stream5_isr,    // 68
    dma2_stream6_isr,    // 69
    dma2_stream7_isr,    // 70
    cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy,
    cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy, cortex::handlers::dummy,
    cortex::handlers::dummy,    // 79
    cortex::handlers::dummy,    // 80
    cortex::handlers::dummy,
};
static_assert(sizeof(external_interrupts) == (stm32::number_of_interrupt_channels * sizeof(void *)), "Must be this value exactly");

}    // namespace stm32

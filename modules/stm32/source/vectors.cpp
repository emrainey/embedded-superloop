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

/// SPI ISR Handler
extern void spi1_isr(void);
extern void spi2_isr(void);
extern void spi3_isr(void);

/// UART4 ISR Handlers
extern void uart4_isr(void);
/// UART5 ISR Handlers
extern void uart5_isr(void);
/// UART7 ISR Handlers
extern void uart7_isr(void);
/// UART8 ISR Handlers
extern void uart8_isr(void);

/// USART1 ISR Handler
extern void usart1_isr(void);
/// USART2 ISR Handler
extern void usart2_isr(void);
/// USART3 ISR Handler
extern void usart3_isr(void);
/// USART6 ISR Handler
extern void usart6_isr(void);

/// Storage location for the extended vector table.
/// If you need a compile time interrupt setup, do so here.
LINKER_SECTION(".extended_vectors")
ExternalInterrupts external_interrupts = {
    cortex::handlers::dummy,    // 0
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    cortex::handlers::dummy,
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
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    timer2_isr,                 // 28
    cortex::handlers::dummy,    // 29
    cortex::handlers::dummy,    // 30
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    spi1_isr,                   // 35
    spi2_isr,                   // 36
    usart1_isr,                 // 37
    usart2_isr,                 // 38
    usart3_isr,                 // 39
    cortex::handlers::dummy,    // 40
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    dma1_stream7_isr,    // 47
    cortex::handlers::dummy,
    cortex::handlers::dummy,    // 49
    cortex::handlers::dummy,    // 50
    spi3_isr,
    uart4_isr,    // 52
    uart5_isr,    // 53
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    dma2_stream0_isr,    // 56
    dma2_stream1_isr,    // 57
    dma2_stream2_isr,    // 58
    dma2_stream3_isr,    // 59
    dma2_stream4_isr,    // 60
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    dma2_stream5_isr,    // 68
    dma2_stream6_isr,    // 69
    dma2_stream7_isr,    // 70
    usart6_isr,          // 71
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    cortex::handlers::dummy,
    cortex::handlers::dummy,    // 79
    cortex::handlers::dummy,    // 80
    cortex::handlers::dummy,
};
static_assert(sizeof(external_interrupts) == (stm32::number_of_interrupt_channels * sizeof(void *)), "Must be this value exactly");

// local storage for the external interrupt statistics
ExternalInterruptStatistics external_interrupt_statistics;

}    // namespace stm32

#include "stm32/vectors.hpp"    // declares the interrupt service routines
#include "core/core.hpp"
#include "cortex/vectors.hpp"
#include "polyfill.hpp"

/// The dummy ISR used by the linker to fill in unused vectors.
extern "C" NAKED void dummy_isr(void) {
    cortex::handlers::dummy();
    __builtin_unreachable();
}

namespace stm32 {

/// Storage location for the extended vector table.
/// If you need a compile time interrupt setup, do so here.
LINKER_SECTION(".extended_vectors")
cortex::ExtendedVectors const extended_vectors USED = {{
    dummy_isr,           // 0
    dummy_isr,        dummy_isr, dummy_isr, dummy_isr, dummy_isr, dummy_isr, dummy_isr, dummy_isr,
    dummy_isr,           // 9
    dummy_isr,           // 10
    dma1_stream0_isr,    // 11
    dma1_stream1_isr,    // 12
    dma1_stream2_isr,    // 13
    dma1_stream3_isr,    // 14
    dma1_stream4_isr,    // 15
    dma1_stream5_isr,    // 16
    dma1_stream6_isr,    // 17
    dummy_isr,
    dummy_isr,           // 19
    dummy_isr,           // 20
    dummy_isr,        dummy_isr, dummy_isr, dummy_isr, dummy_isr, dummy_isr, dummy_isr,
    timer2_isr,          // 28
    dummy_isr,           // 29
    dummy_isr,           // 30
    i2c1_event_isr,      // 31
    i2c1_error_isr,      // 32
    i2c2_event_isr,      // 33
    i2c2_error_isr,      // 34
    spi1_isr,            // 35
    spi2_isr,            // 36
    usart1_isr,          // 37
    usart2_isr,          // 38
    usart3_isr,          // 39
    dummy_isr,           // 40
    dummy_isr,        dummy_isr, dummy_isr, dummy_isr, dummy_isr, dummy_isr,
    dma1_stream7_isr,    // 47
    dummy_isr,
    dummy_isr,           // 49
    dummy_isr,           // 50
    spi3_isr,
    uart4_isr,           // 52
    uart5_isr,           // 53
    dummy_isr,        dummy_isr,
    dma2_stream0_isr,    // 56
    dma2_stream1_isr,    // 57
    dma2_stream2_isr,    // 58
    dma2_stream3_isr,    // 59
    dma2_stream4_isr,    // 60
    dummy_isr,        dummy_isr, dummy_isr, dummy_isr, dummy_isr, dummy_isr, dummy_isr,
    dma2_stream5_isr,    // 68
    dma2_stream6_isr,    // 69
    dma2_stream7_isr,    // 70
    usart6_isr,          // 71
    i2c3_event_isr,      // 72
    i2c3_error_isr,      // 73
    dummy_isr,        dummy_isr, dummy_isr, dummy_isr, dummy_isr,
    dummy_isr,           // 79
    dummy_isr,           // 80
    dummy_isr,
}};
// static_assert(sizeof(extended_vectors.handlers) == (stm32::number_of_interrupt_channels * sizeof(void *)), "Must be this value exactly");

// local storage for the external interrupt statistics
cortex::ExtendedVectorStatistics extended_vector_statistics;

}    // namespace stm32

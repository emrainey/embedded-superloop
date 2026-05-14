#include "stm32/vectors.hpp"    // declares the interrupt service routines
#include "core/core.hpp"
#include "cortex/vectors.hpp"
#include "polyfill.hpp"

extern "C" void dummy_isr(void) {
    cortex::handlers::dummy();
    __builtin_unreachable();
}

#if defined(__has_attribute)
#if not __has_attribute(alias)
// For compilers which don't support the alias attribute, we need to define the functions here instead of just aliasing them to the dummy_isr
namespace stm32 {

void timer2_isr(void) {
    dummy_isr();
}

void dma1_stream0_isr(void) {
    dummy_isr();
}

void dma1_stream1_isr(void) {
    dummy_isr();
}

void dma1_stream2_isr(void) {
    dummy_isr();
}

void dma1_stream3_isr(void) {
    dummy_isr();
}

void dma1_stream4_isr(void) {
    dummy_isr();
}

void dma1_stream5_isr(void) {
    dummy_isr();
}

void dma1_stream6_isr(void) {
    dummy_isr();
}

void dma1_stream7_isr(void) {
    dummy_isr();
}

void dma2_stream0_isr(void) {
    dummy_isr();
}

void dma2_stream1_isr(void) {
    dummy_isr();
}

void dma2_stream2_isr(void) {
    dummy_isr();
}

void dma2_stream3_isr(void) {
    dummy_isr();
}

void dma2_stream4_isr(void) {
    dummy_isr();
}

void dma2_stream5_isr(void) {
    dummy_isr();
}

void dma2_stream6_isr(void) {
    dummy_isr();
}

void dma2_stream7_isr(void) {
    dummy_isr();
}

void spi1_isr(void) {
    dummy_isr();
}

void spi2_isr(void) {
    dummy_isr();
}

void spi3_isr(void) {
    dummy_isr();
}

void uart4_isr(void) {
    dummy_isr();
}

void uart5_isr(void) {
    dummy_isr();
}

void uart7_isr(void) {
    dummy_isr();
}

void uart8_isr(void) {
    dummy_isr();
}

void usart1_isr(void) {
    dummy_isr();
}

void usart2_isr(void) {
    dummy_isr();
}

void usart3_isr(void) {
    dummy_isr();
}

void usart4_isr(void) {
    dummy_isr();
}

void usart5_isr(void) {
    dummy_isr();
}

void usart6_isr(void) {
    dummy_isr();
}

void usart7_isr(void) {
    dummy_isr();
}

void usart8_isr(void) {
    dummy_isr();
}
void i2c1_event_isr(void) {
    dummy_isr();
}

void i2c1_error_isr(void) {
    dummy_isr();
}

void i2c2_event_isr(void) {
    dummy_isr();
}

void i2c2_error_isr(void) {
    dummy_isr();
}

void i2c3_event_isr(void) {
    dummy_isr();
}

void i2c3_error_isr(void) {
    dummy_isr();
}

}    // namespace stm32
#else
// Compiler supports alias attribute - define aliases in this TU where dummy_isr is defined
namespace stm32 {

ISR void timer2_isr(void) ALIAS(dummy_isr);

ISR void dma1_stream0_isr(void) ALIAS(dummy_isr);
ISR void dma1_stream1_isr(void) ALIAS(dummy_isr);
ISR void dma1_stream2_isr(void) ALIAS(dummy_isr);
ISR void dma1_stream3_isr(void) ALIAS(dummy_isr);
ISR void dma1_stream4_isr(void) ALIAS(dummy_isr);
ISR void dma1_stream5_isr(void) ALIAS(dummy_isr);
ISR void dma1_stream6_isr(void) ALIAS(dummy_isr);
ISR void dma1_stream7_isr(void) ALIAS(dummy_isr);

ISR void dma2_stream0_isr(void) ALIAS(dummy_isr);
ISR void dma2_stream1_isr(void) ALIAS(dummy_isr);
ISR void dma2_stream2_isr(void) ALIAS(dummy_isr);
ISR void dma2_stream3_isr(void) ALIAS(dummy_isr);
ISR void dma2_stream4_isr(void) ALIAS(dummy_isr);
ISR void dma2_stream5_isr(void) ALIAS(dummy_isr);
ISR void dma2_stream6_isr(void) ALIAS(dummy_isr);
ISR void dma2_stream7_isr(void) ALIAS(dummy_isr);

ISR void spi1_isr(void) ALIAS(dummy_isr);
ISR void spi2_isr(void) ALIAS(dummy_isr);
ISR void spi3_isr(void) ALIAS(dummy_isr);

ISR void usart1_isr(void) ALIAS(dummy_isr);
ISR void usart2_isr(void) ALIAS(dummy_isr);
ISR void usart3_isr(void) ALIAS(dummy_isr);
ISR void usart4_isr(void) ALIAS(dummy_isr);
ISR void usart5_isr(void) ALIAS(dummy_isr);
ISR void usart6_isr(void) ALIAS(dummy_isr);
ISR void usart7_isr(void) ALIAS(dummy_isr);
ISR void usart8_isr(void) ALIAS(dummy_isr);

ISR void i2c1_event_isr(void) ALIAS(dummy_isr);
ISR void i2c1_error_isr(void) ALIAS(dummy_isr);
ISR void i2c2_event_isr(void) ALIAS(dummy_isr);
ISR void i2c2_error_isr(void) ALIAS(dummy_isr);
ISR void i2c3_event_isr(void) ALIAS(dummy_isr);
ISR void i2c3_error_isr(void) ALIAS(dummy_isr);

}    // namespace stm32
#endif
#endif

namespace cortex {

/// Storage location for the extended vector table.
/// If you need a compile time interrupt setup, do so here.
LINKER_SECTION(".extended_vectors") USED
ExtendedVectors const extended_vectors = {{
    dummy_isr,          // 0
    dummy_isr,          // 1
    dummy_isr,          // 2
    dummy_isr,          // 3
    dummy_isr,          // 4
    dummy_isr,          // 5
    dummy_isr,          // 6
    dummy_isr,          // 7
    dummy_isr,          // 8
    dummy_isr,          // 9
    dummy_isr,          // 10
    stm32::dma1_stream0_isr,    // 11
    stm32::dma1_stream1_isr,    // 12
    stm32::dma1_stream2_isr,    // 13
    stm32::dma1_stream3_isr,    // 14
    stm32::dma1_stream4_isr,    // 15
    stm32::dma1_stream5_isr,    // 16
    stm32::dma1_stream6_isr,    // 17
    dummy_isr,            // 18
    dummy_isr,           // 19
    dummy_isr,           // 20
    dummy_isr,          // 21
    dummy_isr,          // 22
    dummy_isr,          // 23
    dummy_isr,          // 24
    dummy_isr,          // 25
    dummy_isr,          // 26
    dummy_isr,          // 27
    stm32::timer2_isr,   // 28
    dummy_isr,           // 29
    dummy_isr,           // 30
    stm32::i2c1_event_isr,      // 31
    stm32::i2c1_error_isr,      // 32
    stm32::i2c2_event_isr,      // 33
    stm32::i2c2_error_isr,      // 34
    stm32::spi1_isr,            // 35
    stm32::spi2_isr,            // 36
    stm32::usart1_isr,          // 37
    stm32::usart2_isr,          // 38
    stm32::usart3_isr,          // 39
    dummy_isr,           // 40
    dummy_isr,           // 41
    dummy_isr,           // 42
    dummy_isr,           // 43
    dummy_isr,           // 44
    dummy_isr,           // 45
    dummy_isr,           // 46
    stm32::dma1_stream7_isr,    // 47
    dummy_isr,           // 48
    dummy_isr,           // 49
    dummy_isr,           // 50
    stm32::spi3_isr,            // 51
    stm32::usart4_isr,          // 52
    stm32::usart5_isr,          // 53
    dummy_isr,           // 54
    dummy_isr,           // 55
    stm32::dma2_stream0_isr,    // 56
    stm32::dma2_stream1_isr,    // 57
    stm32::dma2_stream2_isr,    // 58
    stm32::dma2_stream3_isr,    // 59
    stm32::dma2_stream4_isr,    // 60
    dummy_isr,           // 61
    dummy_isr,           // 62
    dummy_isr,           // 63
    dummy_isr,           // 64
    dummy_isr,           // 65
    dummy_isr,           // 66
    dummy_isr,           // 67
    stm32::dma2_stream5_isr,    // 68
    stm32::dma2_stream6_isr,    // 69
    stm32::dma2_stream7_isr,    // 70
    stm32::usart6_isr,          // 71
    stm32::i2c3_event_isr,      // 72
    stm32::i2c3_error_isr,      // 73
    dummy_isr,           // 74 - USB OTG HS EP1 Out
    dummy_isr,           // 75 - USB OTG HS EP1 In
    dummy_isr,           // 76 - USB OTG HS WakeUp
    dummy_isr,           // 77 - USB OTG HS
    dummy_isr,           // 78 - DCMI
    dummy_isr,           // 79 - CRYP / HASH
    dummy_isr,           // 80 - RNG
    dummy_isr,           // 81 - FPU
    stm32::usart7_isr,   // 82 - UART7
    stm32::usart8_isr,   // 83 - UART8
    dummy_isr,           // 84 - SPI4
    dummy_isr,           // 85 - SPI5
    dummy_isr,           // 86 - SPI6
    dummy_isr,           // 87 - SAI1
    dummy_isr,           // 88 - LTDC
    dummy_isr,           // 89 - LTDC Error
    dummy_isr,           // 90 - DMA2D
    dummy_isr,           // 91 - SAI2
    dummy_isr,           // 92 - QUADSPI
    dummy_isr,           // 93 - LPTIM1
    dummy_isr,           // 94 - HDMI CEC
    dummy_isr,           // 95 - I2C4 Event
    dummy_isr,           // 96 - I2C4 Error
    dummy_isr,           // 97 - SPDIFRX
    dummy_isr,           // 98 - USB OTG FS EP1 Out
    dummy_isr,           // 99 - USB OTG FS EP1 In
    dummy_isr,           // 100 - USB OTG FS WakeUp
    dummy_isr,           // 101 - USB OTG FS
    dummy_isr,           // 102 - DMAMUX1 Overrun
    dummy_isr,           // 103 - HRTIM1 Master
    dummy_isr,           // 104 - HRTIM1 Timer A
    dummy_isr,           // 105 - HRTIM1 Timer B
    dummy_isr,           // 106 - HRTIM1 Timer C
    dummy_isr,           // 107 - HRTIM1 Timer D
    dummy_isr,           // 108 - HRTIM1 Timer E
    dummy_isr,           // 109 - HRTIM1 Fault
    dummy_isr,           // 110 - DFSDM0
    dummy_isr,           // 111 - DFSDM1
    dummy_isr,           // 112 - DFSDM2
    dummy_isr,           // 113 - DFSDM3
    dummy_isr,           // 114 - SAI3
    dummy_isr,           // 115 - SWPMI1
    dummy_isr,           // 116 - TIM15
    dummy_isr,           // 117 - TIM16
    dummy_isr,           // 118 - TIM17
    dummy_isr,           // 119 - MDIOS WakeUp
    dummy_isr,           // 120 - MDIOS
    dummy_isr,           // 121 - JPEG
    dummy_isr,           // 122 - MDMA
    dummy_isr,           // 123 - Reserved
    dummy_isr,           // 124 - SDMMC2
    dummy_isr,           // 125 - HSEM1
    dummy_isr,           // 126 - Reserved
    dummy_isr,           // 127 - ADC3
    dummy_isr,           // 128 - Reserved
    dummy_isr,           // 129 - Reserved
    dummy_isr,           // 130 - Reserved
    dummy_isr,           // 131 - Reserved
    dummy_isr,           // 132 - Reserved
    dummy_isr,           // 133 - Reserved
    dummy_isr,           // 134 - Reserved
    dummy_isr,           // 135 - Reserved
    dummy_isr,           // 136 - Reserved
    dummy_isr,           // 137 - Reserved
    dummy_isr,           // 138 - Reserved
    dummy_isr,           // 139 - Reserved
    dummy_isr,           // 140 - Reserved
    dummy_isr,           // 141 - Reserved
    dummy_isr,           // 142 - Reserved
    dummy_isr,           // 143 - Reserved
    dummy_isr,           // 144 - Reserved
    dummy_isr,           // 145 - Reserved
    dummy_isr,           // 146 - Reserved
    dummy_isr,           // 147 - Reserved
    dummy_isr,           // 148 - Reserved
    dummy_isr,           // 149 - Reserved
}};
static_assert(sizeof(extended_vectors.handlers) == (stm32::number_of_interrupt_channels * sizeof(void *)), "Must be this value exactly");

// local storage for the external interrupt statistics
ExtendedVectorStatistics extended_vector_statistics;

}    // namespace cortex

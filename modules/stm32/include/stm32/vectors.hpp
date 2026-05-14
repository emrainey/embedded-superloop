#ifndef STM32_VECTORS_HPP
#define STM32_VECTORS_HPP

/// @file
/// The set of all vector definitions for the STM32 family of microcontrollers.

#include <cortex/vectors.hpp>

/// The dummy ISR used by the linker to fill in unused vectors.
extern "C" ISR void dummy_isr(void);

namespace stm32 {

/// TIM2 ISR Handler
ISR void timer2_isr(void);

/// DMA 1 ISR Handlers
ISR void dma1_stream0_isr(void);
ISR void dma1_stream1_isr(void);
ISR void dma1_stream2_isr(void);
ISR void dma1_stream3_isr(void);
ISR void dma1_stream4_isr(void);
ISR void dma1_stream5_isr(void);
ISR void dma1_stream6_isr(void);
ISR void dma1_stream7_isr(void);

/// DMA 2 ISR Handlers
ISR void dma2_stream0_isr(void);
ISR void dma2_stream1_isr(void);
ISR void dma2_stream2_isr(void);
ISR void dma2_stream3_isr(void);
ISR void dma2_stream4_isr(void);
ISR void dma2_stream5_isr(void);
ISR void dma2_stream6_isr(void);
ISR void dma2_stream7_isr(void);

/// SPI ISR Handler
ISR void spi1_isr(void);
ISR void spi2_isr(void);
ISR void spi3_isr(void);

#if defined(STM32F4)
/// UART4 ISR Handlers
ISR void uart4_isr(void);
/// UART5 ISR Handlers
ISR void uart5_isr(void);
/// UART7 ISR Handlers
ISR void uart7_isr(void);
/// UART8 ISR Handlers
ISR void uart8_isr(void);
#endif

/// USART1 ISR Handler
ISR void usart1_isr(void);
/// USART2 ISR Handler
ISR void usart2_isr(void);
/// USART3 ISR Handler
ISR void usart3_isr(void);
/// USART6 ISR Handler
ISR void usart6_isr(void);

#if defined(STM32H7)
/// USART4 ISR Handlers
ISR void usart4_isr(void);
/// USART5 ISR Handlers
ISR void usart5_isr(void);
/// USART7 ISR Handlers
ISR void usart7_isr(void);
/// USART8 ISR Handlers
ISR void usart8_isr(void);
#endif

/// I2C1 ISR Handler
ISR void i2c1_event_isr(void);
ISR void i2c1_error_isr(void);
/// I2C2 ISR Handler
ISR void i2c2_event_isr(void);
ISR void i2c2_error_isr(void);
/// I2C3 ISR Handler
ISR void i2c3_event_isr(void);
ISR void i2c3_error_isr(void);
}    // namespace stm32
#endif    // STM32_VECTORS_HPP

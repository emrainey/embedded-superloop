#ifndef STM_VECTORS_HPP
#define STM_VECTORS_HPP

namespace stm32 {
/// TIM2 ISR Handler
void timer2_isr(void);

/// DMA 1 ISR Handlers
void dma1_stream0_isr(void);
void dma1_stream1_isr(void);
void dma1_stream2_isr(void);
void dma1_stream3_isr(void);
void dma1_stream4_isr(void);
void dma1_stream5_isr(void);
void dma1_stream6_isr(void);
void dma1_stream7_isr(void);

/// DMA 2 ISR Handlers
void dma2_stream0_isr(void);
void dma2_stream1_isr(void);
void dma2_stream2_isr(void);
void dma2_stream3_isr(void);
void dma2_stream4_isr(void);
void dma2_stream5_isr(void);
void dma2_stream6_isr(void);
void dma2_stream7_isr(void);

/// SPI ISR Handler
void spi1_isr(void);
void spi2_isr(void);
void spi3_isr(void);

/// UART4 ISR Handlers
void uart4_isr(void);
/// UART5 ISR Handlers
void uart5_isr(void);
/// UART7 ISR Handlers
void uart7_isr(void);
/// UART8 ISR Handlers
void uart8_isr(void);

/// USART1 ISR Handler
void usart1_isr(void);
/// USART2 ISR Handler
void usart2_isr(void);
/// USART3 ISR Handler
void usart3_isr(void);
/// USART6 ISR Handler
void usart6_isr(void);

/// I2C1 ISR Handler
void i2c1_event_isr(void);
void i2c1_error_isr(void);
/// I2C2 ISR Handler
void i2c2_event_isr(void);
void i2c2_error_isr(void);
/// I2C3 ISR Handler
void i2c3_event_isr(void);
void i2c3_error_isr(void);
} // namespace stm32
#endif   // STM_VECTORS_HPP
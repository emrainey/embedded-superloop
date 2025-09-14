#ifndef STM32_CONFIGURE_HPP
#define STM32_CONFIGURE_HPP

/// @file
/// @brief Configuration options for STM32 peripheral drivers.

#include <cstdint>

namespace stm32 {
namespace configure {

enum class Mode : std::uint8_t {
    None = 0,
    Polling = 1,
    Interrupt = 2,
    Dma = 3,
};

#ifndef STM32_I2C_MODE
#define STM32_I2C_MODE Interrupt
#endif

#ifndef STM32_SPI_MODE
#define STM32_SPI_MODE Interrupt
#endif

#ifndef STM32_UART_MODE
#define STM32_UART_MODE Interrupt
#endif

#ifndef STM32_USART_MODE
#define STM32_USART_MODE Interrupt
#endif

#ifndef STM32_CAN_MODE
#define STM32_CAN_MODE Interrupt
#endif

#ifndef STM32_ADC_MODE
#define STM32_ADC_MODE Interrupt
#endif

constexpr static Mode use_i2c_as = Mode::STM32_I2C_MODE;
constexpr static Mode use_spi_as = Mode::STM32_SPI_MODE;
constexpr static Mode use_uart_as = Mode::STM32_UART_MODE;
constexpr static Mode use_usart_as = Mode::STM32_USART_MODE;
constexpr static Mode use_can_as = Mode::STM32_CAN_MODE;

}    // namespace configure
}    // namespace stm32

#endif    // STM32_CONFIGURE_HPP

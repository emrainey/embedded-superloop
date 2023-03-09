#ifndef STM32_H_
#define STM32_H_
namespace stm32 {
// @see cortex::m4::IRQn for preceeding numbers
enum class IRQn : int {
	WindowWatchDog = 0,
    // up to 81
};
} // namespace stm32
#endif // STM32_H_
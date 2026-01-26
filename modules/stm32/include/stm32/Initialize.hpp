#ifndef STM32_INITIALIZE_HPP_
#define STM32_INITIALIZE_HPP_

/// @file
/// STM32 Chip Initialization Functions

/// The ST Micro 32 Namespace
namespace stm32 {

/// Used to initialize chip specific drivers which need to be brought up very early.
namespace initialize {

/// @brief The required Clock initialization for all STM32 chips
void clocks(void);

/// @brief The required GPIO initialization
/// @note Implemented in the Board
extern void gpio(void);

/// Initializes the Drivers for the STM32 namespace
/// @note Implemented in the Board
extern bool drivers(void);

/// @brief Vendor specific setup of NVIC for drivers
/// @note Implemented in the Board
extern void nvic(void);

}    // namespace initialize

}    // namespace stm32

#endif    // STM32_INITIALIZE_HPP_

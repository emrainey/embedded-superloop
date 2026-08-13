#ifndef STM32_INITIALIZE_HPP_
#define STM32_INITIALIZE_HPP_

/// @file
/// STM32 Chip Initialization Functions

#include <cstdint>

#include "core/Units.hpp"

/// The ST Micro 32 Namespace
namespace stm32 {

/// Used to initialize chip specific drivers which need to be brought up very early.
namespace initialize {

/// @brief Initializes any Power needed to start the clock tree (e.g. enabling the voltage regulator)
void early_power(void);

/// @brief The required Clock initialization for all STM32 chips
void clocks(void);

/// @brief Enables the DBGMCU trace port clocks (TRACECLKEN/D1DBGCKEN/D3DBGCKEN) so the trace
/// blocks can be clocked.
/// @note On the H7 this also un-gates the D3 domain which contains the SWO/SWTF blocks.
void enable_trace_port_clock(void);

/// @brief Programs the ST Serial Wire Output path (SWO + SWTF) for UART trace on the SWO pin.
/// @param trace_clock The frequency of the trace clock (TRACECK) driving the SWO block.
/// @param baud The desired SWO UART baud rate.
/// @note H7 only: the Cortex-M7 TPIU (0xE0040000) does not drive the SWO pin, the ST SWO block
/// (0x5C003000) does. The F4 implementation is a no-op as it uses the standard TPIU instead.
void enable_serial_wire_output(core::units::Hertz trace_clock, std::uint32_t baud);

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

#ifndef CORTEX_INITIALIZE_HPP_
#define CORTEX_INITIALIZE_HPP_

/// @file
/// The Cortex Microcontroller Initialization Header
#include <cstddef>
#include <cstdint>

#include "cortex/types.hpp"

namespace cortex {

/// @brief Contains the methods to initialize various parts of the MCU.
/// @warning These should ONLY be called by the boot sequence!
namespace initialize {

/// Initializes Simple Cortex Global variables needed to use across other calls.
void simple_globals(void);

/// Initializes Class Cortex Global variables needed to use across other calls.
void class_globals(void);

/// Grants access to the FPU
void fpu(void);

/// Initializes the MPU entries
void mpu(void);

/// Initializes the TPIU, ITM and then SWO output
void swo(std::uint32_t desired_baud, Hertz clock_frequency);

/// Initializes the Standard Faults in the System
void faults(void);

/// Initializes the System Tick
void tick(Hertz ticks_per_second, Hertz reference_clock_frequency);

/// Configures the System Control Block Configuration Register
void configuration();

/// Calls all the static object constructors
void static_constructors(void);

/// Calls all the static object destructors
void static_destructors(void);

/// Zeros the BSS section of memory
void zero_bss(void);

/// Loads the Data section of memory from Flash to RAM
void load_data(void);

/// Fills the stack with a known value to allow later measurement of highest stack usage
void watermark_stack(void);

/// The entry point called at the end of initialization before the system has been
/// fully configured. The Clock tree and other subsystems have not yet been initialized.
/// @note This is defined by the external system, not by cortex
[[noreturn]] void on_startup(void);

}    // namespace initialize

}    // namespace cortex

#endif    // CORTEX_M_INITIALIZE_HPP_

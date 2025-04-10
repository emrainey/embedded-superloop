#ifndef JARNAX_SYSTEM_HPP_
#define JARNAX_SYSTEM_HPP_

/// @file
/// The System Interface
#include "compiler.hpp"
#include "configure.hpp"
#include "cortex/linker.hpp"
#include "cortex/vectors.hpp"
#include "jarnax/print.hpp"
#include "jarnax/SuperLoop.hpp"
#include "jarnax/Ticker.hpp"
#include "jarnax/Timer.hpp"

/// The namespace of the system level functions
namespace jarnax {

/// Indicates if the system was able to initialize correctly
extern bool is_system_initialized;

/// Indicates if the system was able to configure correctly
extern bool is_system_configured;

/// Indicates if the system was able to run BIST correctly.
extern bool is_system_functional;

// enum class Phase  {
//     Reset = 0U,
//     Initializing = 1U,
//     Configuring = 2U,
//     SelfTest = 3U,
//     Main = 4U,
// };

/// A namespace to cover the various types of initialization invoked from @see on_entry
namespace initialize {

/// Does system level (cortex specific) initialization such as FPU/MPU, Faults, etc.
void on_entry(void);

/// Fills the stack with a watermark
void watermark_stack(void);

/// Initializes the BSS Section
void zero_bss(void);

/// Loads the Data Section with Values
void load_data(void);

/// Calls the Static Constructors and Pre-initialized arrays
void static_constructors(void);

/// Calls the Static Destructors
void static_destructors(void);

/// Initializes global data for the system which were simple types
/// @pre zero_bss
/// @pre load_data
void simple_globals(void);

/// Initializes global data which had Class initialization
/// @pre class initializers
void class_globals(void);

}    // namespace initialize

/// Defines a type for generic functions.
using function = void (*)(void);

/// Jumps to the new location, reseting the stack and preventing a return.
[[noreturn]] void jump(void* stack, function func);

/// Configures the system beyond initialization.
/// Does system specific configuration such as
/// * configures clocks
/// * configures timers
/// * configures gpio
/// * configures watchdog
void configure(void);

/// Requests an external reset by emitting a signal from the processor.
[[noreturn]] void request_external_reset(void);

/// @brief Primitive Printing Facility.
/// Supports %s, %d, %i, %u, %x, %b (binary), %f for float ONLY.
/// @param format The format string.
/// @param ... The variadic arguments.
void print(const char* format, ...) ATTRIBUTE((format(printf, 1, 2)));

/// The only normal while(true) loop allowed in the system is in "main"
[[noreturn]] void main(void);

/// Requests a call to the system to yield
void yield(void);

}    // namespace jarnax

/// The one global symbol used by the Linker from the code.
extern "C" NAKED void reset_entry(void);

#endif    // JARNAX_SYSTEM_HPP_

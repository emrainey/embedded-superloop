#ifndef CORTEX_VECTORS_HPP_
#define CORTEX_VECTORS_HPP_

/// @file
/// The Cortex-M Vector Related Definitions

#include "cortex/mcu.hpp"

namespace cortex {

/// Declares the table which handles processor exceptions.
extern exceptions::VectorTable const vector_table;

/// Handlers for the System Vector Table
namespace handlers {

/// Handler invoked by the reset exception (does not need to be naked on processor w/o ECC in Stack)
/// @warning The function is `naked` on targets where the stack is not valid during this function
NAKED [[noreturn]] void entry(void);

/// The handler invoked after the stack has been initialized
/// @note This is the first call in the system when the stack is valid and thus won't be `naked`
[[noreturn]] void entry_after_stack(void);

/// The generic handler for all hardware exceptions
USED void generic(
    cortex::exceptions::InterruptServiceRoutine isr_number, cortex::exceptions::ExtendedFrame* frame, cortex::exceptions::ExceptionReturn exc_return
);

/// Handler invoked by the non maskable interrupt
/// @warning The function is `naked` on targets where the stack is not valid during this exception
NAKED void non_maskable_interrupt(void);

/// The subset of exception handlers which deal with faults of some kind
namespace faults {

/// Handler for Hard Faults
/// @warning The function is `naked` on targets where the stack is not valid during this exception
NAKED void hard(void);

/// Handler for Memory Management Issues
/// @warning The function is `naked` on targets where the stack is not valid during this exception
NAKED void memory_management(void);

/// Handler for Bus related Faults
/// @warning The function is `naked` on targets where the stack is not valid during this exception
NAKED void bus(void);

/// Handler for Instruction Usage Faults
/// @warning The function is `naked` on targets where the stack is not valid during this exception
NAKED void usage(void);
}    // namespace faults
/// Handles calls into Supervisor State
namespace supervisor {

/// Handles SVC instructions
/// @warning The function is `naked` on targets where the stack is not valid during this exception
NAKED void call(void);

/// Handler for PendSV
/// @warning The function is `naked` on targets where the stack is not valid during this exception
NAKED void pending(void);
}    // namespace supervisor

/// Handles updates to the System Tick
/// @warning The function is `naked` on targets where the stack is not valid during this exception
NAKED void tick(void);

/// Empty handler which spins
/// @warning The function is `naked` on targets where the stack is not valid during this exception
NAKED void dummy(void);
}    // namespace handlers

}    // namespace cortex

/// The one global symbol used by the Linker from the code.
/// @warning The function is `naked` on targets where the stack is not valid during this function
extern "C" NAKED [[noreturn]] void reset_entry(void);

#endif    // CORTEX_VECTORS_HPP_
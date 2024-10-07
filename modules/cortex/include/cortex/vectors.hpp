#ifndef CORTEX_VECTORS_HPP_
#define CORTEX_VECTORS_HPP_

#include "cortex/mcu.hpp"

namespace cortex {

/// Declares the table which handles processor exceptions.
extern exceptions::VectorTable const vector_table;

/// Handlers for the System Vector Table
/// @warning These functions are naked as the stack is not correct yet.
namespace handlers {

/// Handler invoked by the reset exception (does not need to be naked on processor w/o ECC in Stack)
NAKED [[noreturn]] void entry(void);

/// The handler invoked after the stack has been initialized
[[noreturn]] void entry_after_stack(void);

/// The generic handler for all hardware exceptions
USED void generic(
    cortex::exceptions::InterruptServiceRoutine isr_number, cortex::exceptions::ExtendedFrame* frame, cortex::exceptions::ExceptionReturn exc_return
);

/// Handler invoked by the non maskable interrupt
NAKED void non_maskable_interrupt(void);

/// The subset of exception handlers which deal with faults of some kind
namespace faults {

/// Handler for Hard Faults
NAKED void hard(void);

/// Handler for Memory Management Issues
NAKED void memory_management(void);

/// Handler for Bus related Faults
NAKED void bus(void);

/// Handler for Instruction Usage Faults
NAKED void usage(void);
}    // namespace faults
/// Handles calls into Supervisor State
namespace supervisor {

/// Handles SVC instructions
NAKED void call(void);

/// Handler for PendSV
NAKED void pending(void);
}    // namespace supervisor

/// Handles updates to the System Tick
NAKED void tick(void);

/// Empty handler which spins
NAKED void dummy(void);
}    // namespace handlers

}    // namespace cortex

/// The one global symbol used by the Linker from the code.
extern "C" NAKED [[noreturn]] void reset_entry(void);

#endif    // SYSTEM_HPP_
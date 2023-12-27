#ifndef VECTORS_HPP_
#define VECTORS_HPP_

#include "cortex/mcu.hpp"

namespace jarnax {

/// Use the Cortex Vector table as the system's vector table
using VectorTable = cortex::exceptions::VectorTable;

/// Declares the table which handles processor exceptions.
extern VectorTable const vector_table;

/// Handlers for the System Vector Table
/// @warning These functions are naked as the stack is not correct yet.
namespace handlers {

/// Handler invoked by the reset exception (does not need to be naked on processor w/o ECC in Stack)
ATTRIBUTE((used, naked)) [[noreturn]] void entry(void);

/// The handler invoked after the stack has been initialized
[[noreturn]] void entry_after_stack(void);

/// The generic handler for all exceptions
ATTRIBUTE((used))
void generic(
    cortex::exceptions::InterruptServiceRoutine isr_number,
    cortex::exceptions::ExtendedFrame* frame,
    cortex::exceptions::ExceptionReturn exc_return
);

/// Handler invoked by the non maskable interrupt
ATTRIBUTE((used, naked)) void non_maskable_interrupt(void);

/// The subset of exception handlers which deal with faults of some kind
namespace faults {

/// Handler for Hard Faults
ATTRIBUTE((used, naked)) void hard(void);

/// Handler for Memory Management Issues
ATTRIBUTE((used, naked)) void memory_management(void);

/// Handler for Bus related Faults
ATTRIBUTE((used, naked)) void bus(void);

/// Handler for Instruction Usage Faults
ATTRIBUTE((used, naked)) void usage(void);
}    // namespace faults
/// Handles calls into Supervisor State
namespace supervisor {

/// Handles SVC instructions
ATTRIBUTE((used, naked)) void call(void);

/// Handler for PendSV
ATTRIBUTE((used, naked)) void pending(void);
}    // namespace supervisor

/// Handles updates to the System Tick
ATTRIBUTE((used, naked)) void tick(void);

/// Empty handler which spins
ATTRIBUTE((used, naked)) void dummy(void);
}    // namespace handlers

}    // namespace jarnax

/// The one global symbol used by the Linker from the code.
extern "C" ATTRIBUTE((used, naked, noreturn)) void reset_entry(void);

#endif    // SYSTEM_HPP_
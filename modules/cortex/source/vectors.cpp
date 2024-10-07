#include "compiler.hpp"
#include "cortex/vectors.hpp"
#include "cortex/linker.hpp"

/// @file
/// Vector Table
/// @see https://interrupt.memfault.com/blog/arm-cortex-m-exceptions-and-nvic

namespace cortex {

/// This is the vector table, placed by the Linker at the start of the image.
/// The processor will boot into the offset at 0x4, the entry handler.
LINKER_SECTION(".vectors")
exceptions::VectorTable const vector_table = {
    __main_stack_top,
    {handlers::entry,
     handlers::non_maskable_interrupt,
     {handlers::faults::hard, handlers::faults::memory_management, handlers::faults::bus, handlers::faults::usage},
     handlers::dummy,
     handlers::dummy,
     handlers::dummy,
     handlers::dummy,
     handlers::supervisor::call,
     handlers::dummy,
     handlers::dummy,
     handlers::supervisor::pending,
     handlers::tick}
};
}    // namespace cortex

// Used by the Linker to declare the entry point
extern "C" NAKED void reset_entry(void) {
    // since this function is also naked, you can call it directly
    cortex::handlers::entry();
}

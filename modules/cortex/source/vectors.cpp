#include "jarnax/system.hpp"
#include "jarnax/linker.hpp"

/// @file
/// Vector Table
/// @see https://interrupt.memfault.com/blog/arm-cortex-m-exceptions-and-nvic

namespace jarnax {

/// This is the vector table, placed by the Linker at the start of the image.
/// The processor will boot into the offset at 0x4, the entry handler.
ATTRIBUTE((used, section(".vectors")))
cortex::exceptions::VectorTable const vector_table = {
    __main_stack_top,
    {jarnax::handlers::entry,
     jarnax::handlers::non_maskable_interrupt,
     {jarnax::handlers::faults::hard,
      jarnax::handlers::faults::memory_management,
      jarnax::handlers::faults::bus,
      jarnax::handlers::faults::usage},
     jarnax::handlers::dummy,
     jarnax::handlers::dummy,
     jarnax::handlers::dummy,
     jarnax::handlers::dummy,
     jarnax::handlers::supervisor::call,
     jarnax::handlers::dummy,
     jarnax::handlers::dummy,
     jarnax::handlers::supervisor::pending,
     jarnax::handlers::tick}};
}    // namespace jarnax

// Used by the Linker to declare the entry point
extern "C" void reset_entry(void) {
    // since this function is also naked, you can call it directly
    jarnax::handlers::entry();
}

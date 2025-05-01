#include "jarnax/system.hpp"
#include "cortex/thumb.hpp"
namespace jarnax {
namespace initialize {

void watermark_stack(void) {
    // stack has been moved down from where it was to accommodate all of this
    // function's automatics. We'll write a pattern from the current stack pointer down to
    // the bottom of stack. If we were to use the Main Stack symbol, we'd destroy our own stack
    // values in caller functions!
    std::uint32_t* current_stack = thumb::get_current_stack_pointer();
    std::uint32_t const* const bottom_stack = __main_stack_bottom;
    while (current_stack >= bottom_stack) {
        *current_stack = cortex::stack_watermark;
        --current_stack;
    }
    std::uint32_t* process_stack_top = __process_stack_top;
    std::uint32_t const* const process_stack_bottom = __process_stack_bottom;
    while (process_stack_top >= process_stack_bottom) {
        *process_stack_top = cortex::stack_watermark;
        --process_stack_top;
    }
}

}    // namespace initialize
}    // namespace jarnax
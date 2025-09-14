#include "cortex/linker.hpp"
#include "cortex/mcu.hpp"

namespace cortex {
namespace initialize {

void static_destructors(void) {
    std::ptrdiff_t index = 0U;
    std::ptrdiff_t count = __fini_array_end - __fini_array_start;    // a difference of two TYPED pointers
    for (index = count; index > 0; index--) {
        __fini_array_start[index - 1]();
    }
}

}    // namespace initialize
}    // namespace cortex

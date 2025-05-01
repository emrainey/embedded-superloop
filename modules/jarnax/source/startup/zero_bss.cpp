#include "jarnax/system.hpp"
#include "cortex/linker.hpp"
#include "cortex/thumb.hpp"
namespace jarnax {
namespace initialize {

#if defined(__GNUC__) and not defined(__clang__)
#pragma GCC push_options
#pragma GCC optimize("O0")    // Disable all optimizations
#endif
void zero_bss(void) {
    // zero initialize the bss from the start (bottom) to the end (top)
    std::uint32_t* tmp = __bss_start;
    std::uint32_t const* const end = __bss_end;
    while (tmp < end) {
        *tmp = 0U;
        ++tmp;
    }
}
#if defined(__GNUC__) and not defined(__clang__)
#pragma GCC pop_options    // Restore the optimization level
#endif
}    // namespace initialize
}    // namespace jarnax
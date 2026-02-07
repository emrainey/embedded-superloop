#include "cortex/linker.hpp"    // for data symbols
#include "cortex/mcu.hpp"

namespace cortex {
namespace initialize {

#if defined(__GNUC__) and not defined(__clang__)
#pragma GCC push_options
#pragma GCC optimize("O0")    // Disable all optimizations
#endif
void load_data(void) {
    // load the read only data from the
    std::uint32_t volatile* dst = __const_static_data_start;
    std::uint32_t volatile* src = __const_static_data_load;
    std::uint32_t volatile const* const end = __const_static_data_limit;
    while (dst < end) {
        *dst = *src;
        ++dst;
        ++src;
    }
}
#if defined(__GNUC__) and not defined(__clang__)
#pragma GCC pop_options    // Restore the optimization level
#endif

}    // namespace initialize
}    // namespace cortex

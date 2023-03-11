#include "jarnax/system.hpp"
#include "jarnax/linker.hpp"
namespace jarnax {
namespace initialize {

#if defined(__GNUC__) and not defined(__clang__)
#pragma GCC push_options
#pragma GCC optimize("O0")    // Disable all optimizations
#endif
void load_data(void) {
    // load the read only data from the
    std::uint32_t volatile* dst = __data_start;
    std::uint32_t volatile* src = __data_load;
    std::uint32_t volatile const* const end = __data_end;
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
}    // namespace jarnax
#include "jarnax/system.hpp"
#include "jarnax/linker.hpp"

namespace jarnax {
namespace initialize {

void static_destructors(void) {
    // register std::uintptr_t end = reinterpret_cast<std::uintptr_t>(__fini_array_end);
    // register std::uintptr_t beg = reinterpret_cast<std::uintptr_t>(__fini_array_start);
    std::ptrdiff_t index = 0U;
    std::ptrdiff_t count = __fini_array_end - __fini_array_start;
    // count /= sizeof(std::uintptr_t);
    for (index = count; index > 0; index--) {
        __fini_array_start[index - 1]();
    }
}

}    // namespace initialize
}    // namespace jarnax

#include "jarnax/system.hpp"
#include "jarnax/linker.hpp"
namespace jarnax {
namespace initialize {

void static_constructors(void) {
    std::ptrdiff_t index = 0U;
    std::ptrdiff_t count = 0U;
    {
        // register std::uintptr_t end = reinterpret_cast<std::uintptr_t>(__preinit_array_end);
        // register std::uintptr_t beg = reinterpret_cast<std::uintptr_t>(__preinit_array_start);
        count = __preinit_array_end - __preinit_array_start;
        // count /= sizeof(std::uintptr_t);
        for (index = 0U; index < count; index++) {
            __preinit_array_start[index]();
        }
    }
    {
        // register std::uintptr_t end = reinterpret_cast<std::uintptr_t>(__init_array_end);
        // register std::uintptr_t beg = reinterpret_cast<std::uintptr_t>(__init_array_start);
        count = __init_array_end - __init_array_start;
        // count /= sizeof(std::uintptr_t);
        for (index = 0U; index < count; index++) {
            __init_array_start[index]();
        }
    }
}

}    // namespace initialize
}    // namespace jarnax
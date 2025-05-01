#include "jarnax/system.hpp"
#include "cortex/thumb.hpp"
namespace jarnax {
namespace initialize {

void static_constructors(void) {
    std::ptrdiff_t index = 0U;
    std::ptrdiff_t count = 0U;
    if constexpr (has_preinitialization) {
        count = __preinit_array_end - __preinit_array_start;
        for (index = 0U; index < count; index++) {
            __preinit_array_start[index]();
        }
    }
    if constexpr (has_static_constructors) {
        count = __init_array_end - __init_array_start;
        for (index = 0U; index < count; index++) {
            __init_array_start[index]();
        }
    }
}

}    // namespace initialize
}    // namespace jarnax
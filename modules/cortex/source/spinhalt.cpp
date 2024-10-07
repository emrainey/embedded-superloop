#include "cortex/mcu.hpp"

namespace cortex {

[[noreturn]] void spinhalt(void) {
    while (true) {
        thumb::breakpoint<0>();    // 0xAB should be use for semihosting
    }
    __builtin_unreachable();
}

}    // namespace cortex

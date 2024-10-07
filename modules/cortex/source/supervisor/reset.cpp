#include "cortex/mcu.hpp"
namespace cortex {
namespace supervisor {

/// Causes a reset
[[noreturn]] void reset(void) {
    thumb::Stacked parameters{{{0U}, {0U}, {0U}, {0U}}};
    thumb::supervisor<to_underlying(Marshal::Calls::Reset)>(&parameters);
    __builtin_unreachable();
}

}    // namespace supervisor

}    // namespace cortex

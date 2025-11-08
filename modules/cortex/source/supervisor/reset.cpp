#include "cortex/mcu.hpp"
namespace cortex {
namespace supervisor {

/// Causes a reset
[[noreturn]] void reset(void) {
    thumb::Stacked args{{{0U}, {0U}, {0U}, {0U}}};
    args.parameters[0].as_u32[0] = to_underlying(Marshal::Arguments::Processor::Operations::SoftwareReset);
    thumb::supervisor<to_underlying(Marshal::Calls::Processor)>(&args);
    __builtin_unreachable();
}

}    // namespace supervisor

}    // namespace cortex

#include "configure.hpp"

#include <cortex/supervisor.hpp>
#include <cortex/thumb.hpp>
#include <cortex/trigger.hpp>

namespace jarnax {

void yield(void) {
    // if we're in supervisor mode, we can trigger a NMI, else we just have to do a SVC
    if constexpr (cortex::run_in_privileged_mode_only) {
        // @TODO should we have a global structure or flag to indicate what we should do in a NMI?
        cortex::trigger::non_maskable_interrupt();
    } else {
        thumb::Stacked parameters{{{0U}, {0U}, {0U}, {0U}}};
        thumb::supervisor<polyfill::to_underlying(cortex::supervisor::Marshal::Calls::Yield)>(&parameters);
    }
}

}    // namespace jarnax

#include "jarnax/system.hpp"
#include "cortex/mcu.hpp"
#include "cortex/thumb.hpp"

namespace jarnax {

void yield(void) {
    // if we're in supervisor mode, we can trigger a NMI, else we just have to do a SVC
    if (cortex::is_privileged()) {
        // @TODO should we have a global structure or flag to indicate what we should do in a NMI?
        cortex::trigger_non_maskable_interrupt();
    } else {
        thumb::Stacked parameters{{{0U}, {0U}, {0U}, {0U}}};
        thumb::supervisor<to_underlying(cortex::supervisor::Marshal::Calls::Yield)>(&parameters);
    }
}

}    // namespace jarnax
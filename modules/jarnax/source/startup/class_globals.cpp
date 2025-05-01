
#include "jarnax/system.hpp"

namespace jarnax {

namespace initialize {

void class_globals(void) {
    // fill in with globals with Classes in the Jarnax system which are not on the Context
    // Such as a Scheduler, or some Kernel specific classes which have to be working before the
    // system is finished initializing.
}
}    // namespace initialize
}    // namespace jarnax
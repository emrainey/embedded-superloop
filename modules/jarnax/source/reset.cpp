#include "jarnax/system.hpp"
#include "cortex/m4.hpp"
namespace jarnax {

[[noreturn]] void request_external_reset(void) {
    cortex::request_external_reset();
}

}    // namespace jarnax

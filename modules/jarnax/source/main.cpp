
#include "jarnax.hpp"
#include "jarnax/Context.hpp"
#include "jarnax/Assertion.hpp"
namespace jarnax {

[[noreturn]] void main(void) {
    banner();
    Context& context = GetContext();
    if (context.Initialize()) {
        SuperLoop& superloop = context.GetSuperLoop();
        superloop.RunForever();
    }
    cortex::spinhalt();
    __builtin_unreachable();
}

}    // namespace jarnax

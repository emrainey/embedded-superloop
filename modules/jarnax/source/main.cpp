#include "jarnax.hpp"
#include "jarnax/Assertion.hpp"
#include "jarnax/Context.hpp"

#include "cmake.hpp"
#include "git.hpp"

namespace jarnax {
void ATTRIBUTE((weak)) banner(void) {
    jarnax::print(
        "                  _/                                                \r\n"
        "         _/    _/_/    _/_/_/    _/      _/    _/_/    _/      _/   \r\n"
        "        _/  _/    _/  _/    _/  _/_/    _/  _/  _/_/    _/  _/      \r\n"
        "       _/  _/_/_/_/  _/_/_/    _/  _/  _/  _/    _/      _/         \r\n"
        "_/    _/  _/    _/  _/    _/  _/    _/_/  _/_/  _/    _/  _/        \r\n"
        " _/_/    _/    _/  _/    _/  _/      _/    _/_/    _/      _/       \r\n"
        " %s -- %u.%u.%u from git commit %s\r\n",
        cmake::project::name_version,
        cmake::project::version.major,
        cmake::project::version.minor,
        cmake::project::version.patch,
        git::short_hash
    );
}
}    // namespace jarnax

namespace cortex {
namespace system {
[[noreturn]] void ATTRIBUTE((used)) main(void) {
    jarnax::banner();
    jarnax::Context& context = jarnax::GetContext();
    if (context.Initialize()) {
        jarnax::SuperLoop& superloop = context.GetSuperLoop();
        superloop.RunForever();
    }
    cortex::spinhalt();
    __builtin_unreachable();
}
}    // namespace system
}    // namespace cortex

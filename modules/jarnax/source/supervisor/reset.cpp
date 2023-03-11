#include "jarnax/system.hpp"

namespace jarnax {
namespace supervisor {

/// Causes a reset
void reset(void) {
    thumb::Stacked parameters{{{0U}, {0U}, {0U}, {0U}}};
    thumb::supervisor<to_underlying(Marshal::Calls::Reset)>(&parameters);
}

}    // namespace supervisor

}    // namespace jarnax

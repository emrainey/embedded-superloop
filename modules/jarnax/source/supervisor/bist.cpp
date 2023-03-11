#include "jarnax/system.hpp"

namespace jarnax {
namespace supervisor {

void bist() {
    thumb::Stacked parameters{{{kBistArg0}, {kBistArg1}, {kBistArg2}, {kBistArg3}}};
    thumb::supervisor<to_underlying(Marshal::Calls::BuiltInSelfTest)>(&parameters);
}

}    // namespace supervisor

}    // namespace jarnax

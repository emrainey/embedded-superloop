#include "cortex/supervisor.hpp"
#include "cortex/bist.hpp"
namespace cortex {
namespace supervisor {

void bist() {
    thumb::Stacked parameters{{{kBistArg0}, {kBistArg1}, {kBistArg2}, {kBistArg3}}};
    thumb::supervisor<to_underlying(Marshal::Calls::BuiltInSelfTest)>(&parameters);
}

}    // namespace supervisor

}    // namespace cortex

#include "cortex/bist.hpp"
#include "cortex/supervisor.hpp"
namespace cortex {
namespace supervisor {

void bist() {
    thumb::Stacked parameters{{{kBistArg0}, {kBistArg1}, {kBistArg2}, {kBistArg3}}};
    thumb::supervisor<polyfill::to_underlying(Marshal::Calls::BuiltInSelfTest)>(&parameters);
}

}    // namespace supervisor

}    // namespace cortex

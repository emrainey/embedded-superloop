#include "jarnax/StopWatch.hpp"

using namespace core::units;

namespace jarnax {

StopWatch::StopWatch(Timer const& timer)
    : timer_{timer}
    , start_{0u}
    , diff_{0u} {
}

void StopWatch::Start() {
    if (start_ == 0_iota) {
        diff_ = 0_iota;
        start_ = timer_.GetIotas();
    }
}

void StopWatch::Stop() {
    if (start_ > 0_iota) {
        diff_ = timer_.GetIotas() - start_;
        start_ = 0_iota;
    }
}

core::units::Iota StopWatch::GetElapsed() const {
    return diff_;
}

}    // namespace jarnax
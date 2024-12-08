#include "jarnax/CountDown.hpp"

namespace jarnax {

using namespace core::units;
using core::units::operator""_iota;

CountDown::CountDown(Timer const& timer, core::units::Iota duration)
    : timer_{timer}
    , duration_{0U}
    , limit_{0U}
    , last_{0U}
    , delta_late_{0U} {
    Restart(duration);
}

bool CountDown::IsExpired() {
    auto now = timer_.GetIotas();
    if (now >= limit_) {
        delta_late_ = now - limit_;
        return true;
    }
    return false;
}

void CountDown::Reset() {
    limit_ = timer_.GetIotas() + duration_ - delta_late_;
    delta_late_ = 0_iota;
}

void CountDown::Restart(core::units::Iota new_duration) {
    duration_ = new_duration;
    limit_ = timer_.GetIotas() + duration_;
    delta_late_ = 0_iota;
}

}  // namespace jarnax

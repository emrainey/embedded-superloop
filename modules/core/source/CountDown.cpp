#include <core/time/CountDown.hpp>
#include <core/Units.hpp>

namespace core {
namespace time {

CountDown::CountDown(MonotonicClock const& clock, MicroSeconds duration)
    : clock_{clock}
    , duration_{0U}
    , limit_{0U}
    , last_{0U}
    , delta_late_{0U} {
    Restart(duration);
}

bool CountDown::IsExpired() const {
    auto now = clock_.Now();
    if (now >= limit_) {
        delta_late_ = now - limit_;
        return true;
    }
    return false;
}

core::time::MicroSeconds CountDown::GetLateness() const {
    return delta_late_;
}

void CountDown::Reset() {
    using namespace core::units;
    limit_ = clock_.Now() + duration_ - delta_late_;
    delta_late_ = 0_usec;
}

void CountDown::Restart(MicroSeconds new_duration) {
    using namespace core::units;
    duration_ = new_duration;
    limit_ = clock_.Now() + duration_;
    delta_late_ = 0_usec;
}

}   // namespace time
}  // namespace core

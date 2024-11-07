#include "core/Units.hpp"
#include "jarnax/SuperLoop.hpp"

namespace jarnax {

using namespace core::units;

SuperLoop::SuperLoop(Ticker& ticker)
    : ticker_{ticker}
    , loop_count_{0U}
    , executables_{}
    , next_id_{1U} {
    for (auto& exec_info : executables_) {
        exec_info.id = 0;
        exec_info.object = nullptr;
        exec_info.cadence = 0xFFFF'FFFFU;
        exec_info.last_tick = 0_ticks;
        exec_info.last_duration = 0_ticks;
        exec_info.count = 0U;
        exec_info.is_active = false;
    }
}

bool SuperLoop::Enlist(Executable& obj, std::uint32_t cadence) {
    if (cadence == 0) {
        return false;
    }
    for (auto& exec_info : executables_) {
        if (exec_info.object == nullptr) {
            exec_info.id = next_id_++;
            exec_info.object = &obj;
            exec_info.cadence = cadence;
            exec_info.last_tick = 0_ticks;
            exec_info.last_duration = 0_ticks;
            exec_info.count = 0U;
            exec_info.is_active = true;
            return exec_info.is_active;
        }
    }
    return false;
}

void SuperLoop::Dismiss(Executable& obj) {
    for (auto& exec_info : executables_) {
        if (exec_info.object == &obj) {
            exec_info.id = 0U;
            exec_info.is_active = false;
            exec_info.object = nullptr;
            exec_info.cadence = 0U;
            exec_info.last_tick = 0_ticks;
            exec_info.last_duration = 0_ticks;
            exec_info.count = 0U;
        }
    }
}

void SuperLoop::RunForever(void) {
    while (true) {
        RunAllOnce();
    }
}

void SuperLoop::RunAllOnce(void) {
    const std::uint32_t count_mask = (SlotsInCadence - 1U);
    const Cadence cadence_mask = (1U << (loop_count_ & count_mask));
    for (auto& exec_info : executables_) {
#if defined(UNITTEST)
            std::cout << std::hex << "exec_info.cadence: " << exec_info.cadence << " mask: " << cadence_mask << std::endl;
#endif
        if (exec_info.is_active and exec_info.object != nullptr and ((exec_info.cadence & cadence_mask) > 0)) {
            ++exec_info.count;    // the task sees the current count, not the last count
            LoopInfo const loopinfo = {
                /* .system_count = */ loop_count_,
                /* .count = */ exec_info.count,
                /* .cadence = */ exec_info.cadence,
                /* .cadence_mask */ cadence_mask,
            };
#if defined(UNITTEST)
                std::cout << std::hex << "id: " << exec_info.id << " exec_info.count: " << exec_info.count << " mask: " << cadence_mask << std::endl;
#endif
            auto start = ticker_.GetTicks();
            exec_info.is_active = exec_info.object->Execute(loopinfo);
            exec_info.last_tick = ticker_.GetTicks();
            exec_info.last_duration = exec_info.last_tick - start;
        }
    }
    ++loop_count_;
}

#if defined(UNITTEST)
std::ostream& operator<<(std::ostream& os, SuperLoop const& loop) {
    os << "SuperLoop{" << std::endl;
    for (auto const& exec_info : loop.executables_) {
        os << "id: " << exec_info.id << " count: " << exec_info.count << " cadence: " << exec_info.cadence << " last_tick: " << exec_info.last_tick
           << " last_duration: " << exec_info.last_duration << " is_active: " << exec_info.is_active << std::endl;
    }
    os << "}";
    return os;
}
#endif

}    // namespace jarnax
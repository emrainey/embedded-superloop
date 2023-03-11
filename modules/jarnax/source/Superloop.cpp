#include "jarnax/SuperLoop.hpp"

namespace jarnax {
SuperLoop::SuperLoop() : loop_count_{0U}, executables_{} {
    for (auto& exec_info : executables_) {
        exec_info.object = nullptr;
        exec_info.cadence = 0U;
        exec_info.count = 0U;
        exec_info.is_active = false;
    }
}

bool SuperLoop::Enlist(Executable& obj, std::size_t cadence) {
    if (cadence == 0) {
        return false;
    }
    for (auto& exec_info : executables_) {
        if (exec_info.object == nullptr) {
            exec_info.object = &obj;
            exec_info.cadence = cadence;
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
            exec_info.is_active = false;
            exec_info.object = nullptr;
            exec_info.cadence = 0U;
            exec_info.count = 0U;
        }
    }
}

void SuperLoop::RunAllOnce(void) {
    for (auto& exec_info : executables_) {
        if (exec_info.is_active and exec_info.object != nullptr) {
            LoopInfo const loopinfo = {
                /* .system_count = */ loop_count_,
                /* .count = */ exec_info.count,
                /* .cadence = */ exec_info.cadence,
            };
            exec_info.is_active = exec_info.object->Execute(loopinfo);
            ++exec_info.count;
        }
    }
    ++loop_count_;
}

}    // namespace jarnax
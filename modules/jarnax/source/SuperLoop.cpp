#include "core/Units.hpp"
#include "jarnax/SuperLoop.hpp"

namespace jarnax {

using namespace core::units;

SuperLoop::SuperLoop(Ticker& ticker)
    : ticker_{ticker}
    , loop_count_{0U}
    , next_id_{1U}
    , head_{nullptr}
    , tail_{nullptr} {
}

bool SuperLoop::Enlist(Executable& obj, std::uint32_t cadence) {
    if (cadence == 0) {
        return false;
    }
    if (not head_ and not tail_) {
        head_ = tail_ = &obj.execute_info_;
    } else {
        tail_->InsertBefore(obj.execute_info_);
        tail_ = &obj.execute_info_;
    }
    // reset the info
    obj.ResetInfo();
    // ensure the pointer is set
    obj.GetInfo().object = &obj;
    // assign the id
    obj.GetInfo().id = next_id_++;
    // assign the cadence
    obj.GetInfo().cadence = cadence;
    return false;
}

void SuperLoop::Dismiss(Executable& obj) {
    obj.execute_info_.Remove();   // remove the node from the list
    obj.ResetInfo();              // reset the info
}

void SuperLoop::RunForever(void) {
    while (true) {
        RunAllOnce();
    }
}

void SuperLoop::RunAllOnce(void) {
    if (head_ == nullptr) {
        return;
    }
    head_->VisitForward([&](core::doublelink::Node<Executable::Info>& node) {
        const std::uint32_t count_mask = (SlotsInCadence - 1U);
        const std::uint32_t cadence_slot = (loop_count_ & count_mask);
        const std::uint32_t cadence_mask = GetMask(cadence_slot);
        Executable::Info& exec_info = node();
#if defined(UNITTEST)
            std::cout << std::hex << "exec_info.cadence: " << exec_info.cadence << " mask: " << cadence_mask << std::endl;
#endif
        if (not exec_info.is_active) {
            return;
        }

        if (exec_info.object == nullptr) {
            // FIXME error?
            return;
        }

        if ((exec_info.cadence & (1U << cadence_slot)) == 0) {
            return;
        }

        ++exec_info.count;    // the task sees the current count, not the last count
        LoopInfo const loopinfo = {
            /* .system_count = */ loop_count_,
            /* .cadence_slot = */ cadence_slot,
        };
#if defined(UNITTEST)
            std::cout << std::hex << "id: " << exec_info.id << " exec_info.count: " << exec_info.count << " mask: " << cadence_mask << std::endl;
#endif
        auto start = ticker_.GetTicks();
        exec_info.is_active = exec_info.object->Execute(loopinfo);
        exec_info.last_tick = ticker_.GetTicks();
        exec_info.last_duration = exec_info.last_tick - start;
    });
    ++loop_count_;
}

#if defined(UNITTEST)
std::ostream& operator<<(std::ostream& os, SuperLoop const& loop) {
    os << "SuperLoop{" << std::endl;
    loop.head_->VisitForward([&](core::doublelink::Node<Executable::Info>& node) {
        Executable::Info const& exec_info = node();
        os << "id: " << exec_info.id << " count: " << exec_info.count << " cadence: " << exec_info.cadence << " last_tick: " << exec_info.last_tick
           << " last_duration: " << exec_info.last_duration << " is_active: " << exec_info.is_active << std::endl << "}";
    });

    return os;
}
#endif

}    // namespace jarnax
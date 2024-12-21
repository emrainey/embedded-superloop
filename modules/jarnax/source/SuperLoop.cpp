#include "core/Units.hpp"
#include "jarnax/print.hpp"
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

bool SuperLoop::Enlist(Loopable& obj, std::uint32_t cadence) {
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
    obj.GetMutableInfo().object = &obj;
    // assign the id
    obj.GetMutableInfo().id = next_id_++;
    // assign the cadence
    obj.GetMutableInfo().cadence = cadence;
    // Enable the executable
    obj.GetMutableInfo().is_active = true;
    return true;
}

void SuperLoop::Dismiss(Loopable& obj) {
    obj.execute_info_.Remove();    // remove the node from the list
    obj.ResetInfo();               // reset the info
}

void SuperLoop::RunForever(void) {
    while (true) {
        RunAllOnce();
    }
}

void SuperLoop::Visit(core::doublelink::Node<Loopable::Info>& node) {
    const std::uint32_t count_mask = (SlotsInCadence - 1U);
    const std::uint32_t cadence_slot = (loop_count_ & count_mask);
    const std::uint32_t cadence_mask = GetMask(cadence_slot);
    Loopable::Info& exec_info = node();
#if defined(UNITTEST)
    std::cout << std::hex << "exec_info.cadence: " << exec_info.cadence << " mask: " << cadence_mask << std::endl;
#endif
    if (not exec_info.is_active) {
        return;
    }

    if (exec_info.object == nullptr) {
        // FIXME assertable error?
        return;
    }

    if ((exec_info.cadence & cadence_mask) == 0) {
        return;
    }

    exec_info.object->GetMutableLoopInfo() = {
        /* .system_count = */ loop_count_,
        /* .cadence_slot = */ cadence_slot,
    };
    ++exec_info.count;    // the task sees the current count, not the last count

#if defined(UNITTEST)
    std::cout << std::hex << "id: " << exec_info.id << " exec_info.count: " << exec_info.count << " mask: " << cadence_mask << std::endl;
#endif
    auto start = ticker_.GetTicks();
    exec_info.is_active = exec_info.object->Execute();
    exec_info.last_tick = ticker_.GetTicks();
    exec_info.last_duration = exec_info.last_tick - start;
}

void SuperLoop::RunAllOnce(void) {
    if (head_ == nullptr) {
        return;
    }
    head_->VisitForward(*this);
    ++loop_count_;
}

void SuperLoop::Visit(core::doublelink::Node<Loopable::Info> const& node) const {
#if defined(UNITTEST)
    Loopable::Info const& exec_info = node();
    std::cout << "id: " << exec_info.id << " count: " << exec_info.count << " cadence: " << exec_info.cadence << " last_tick: " << exec_info.last_tick
              << " last_duration: " << exec_info.last_duration << " is_active: " << exec_info.is_active << std::endl;
#else
    // this visitor method is used for printing the list on target
    jarnax::print("id: %" PRIu32 " count: %" PRIz " cadence: %" PRIx32 "\n", node().id, node().count, node().cadence);
#endif
}

#if defined(UNITTEST)
std::ostream& operator<<(std::ostream& os, SuperLoop const& loop) {
    os << "SuperLoop{" << std::endl;
    loop.head_->VisitForward(loop);
    os << "}" << std::endl;

    return os;
}
#endif

}    // namespace jarnax
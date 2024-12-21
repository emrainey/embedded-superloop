#include "memory.h"
#include "Task.hpp"
#include "board.hpp"

Task::Task()
    : ticker_{jarnax::GetTicker()}
    , timer_{jarnax::GetTimer()}
    , rng_{jarnax::GetDriverContext().GetRandomNumberGenerator()}
    , error_indicator_{jarnax::GetDriverContext().GetErrorIndicator()}
    , status_indicator_{jarnax::GetDriverContext().GetStatusIndicator()}
    , wakeup_button_{jarnax::GetDriverContext().GetWakeupButton()}
    , key0_button_{jarnax::GetDriverContext().GetButton0()}
    , key1_button_{jarnax::GetDriverContext().GetButton1()}
    , copier_{jarnax::GetDriverContext().GetCopier()}
    , buffer_one_{}
    , buffer_two_{} {
}

void Task::DelayForTicks(jarnax::Ticks ticks) {
    jarnax::Ticks start = ticker_.GetTicks();
    jarnax::Ticks now, diff;
    size_t outer_counter{0U};
    do {
        thumb::nop();
        outer_counter++;
        now = ticker_.GetTicks();
        diff = now - start;
    } while (diff < ticks);
    jarnax::print("Counted to %u\r\n", outer_counter);
}

bool Task::Execute() {
    if ((GetLoopInfo().system_loop_count & 1) == 0) {
        // be able to trigger a NMI
        // jarnax::yield();
    }
    jarnax::Ticks ticks = ticker_.GetTicksSinceBoot();
    jarnax::Time time = ticker_.GetTimeSinceBoot();
    uint32_t random = rng_.GetNextRandom();
    std::uint32_t iotas = static_cast<std::uint32_t>(timer_.GetIotas().value());

    memory::fill(buffer_one_, 0x5A, sizeof(buffer_one_));
    memory::fill(buffer_two_, 0x00, sizeof(buffer_two_));
    copier_.Copy(&buffer_one_[0], &buffer_two_[0], sizeof(buffer_one_));
    if (memory::compare(&buffer_one_[0], &buffer_two_[0], sizeof(buffer_one_)) == 0) {
        jarnax::print("Buffers are the same\r\n");
    } else {
        jarnax::print("Buffers are different\r\n");
    }

    jarnax::print("Task::Execute: %lu ticks, %lf sec, 0x%lx Iotas: %lu\r\n", ticks.value(), time.value(), random, iotas);
    DelayForTicks(Ticks{64});
    if (wakeup_button_.IsPressed()) {
        jarnax::print("Wakeup Pressed\r\n");
    }
    if (key0_button_.IsPressed()) {
        jarnax::print("Key0 Pressed\r\n");
        status_indicator_.Active();
    } else {
        status_indicator_.Inactive();
    }
    if (key1_button_.IsPressed()) {
        jarnax::print("Key1 Pressed\r\n");
        error_indicator_.Active();
    } else {
        error_indicator_.Inactive();
    }
    return true;
}

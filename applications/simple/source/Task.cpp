#include "Task.hpp"
#include "board.hpp"

Task::Task()
    : ticker_{jarnax::GetTicker()}
    , rng_{jarnax::GetDriverContext().GetRandomNumberGenerator()}
    , error_indicator_{jarnax::GetDriverContext().GetErrorIndicator()}
    , status_indicator_{jarnax::GetDriverContext().GetStatusIndicator()}
    , wakeup_button_{jarnax::GetDriverContext().GetWakeupButton()}
    , key0_button_{jarnax::GetDriverContext().GetButton0()}
    , key1_button_{jarnax::GetDriverContext().GetButton1()} {
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

bool Task::Execute(LoopInfo const &metadata) {
    if ((metadata.count & 1) == 0) {
        // be able to trigger a NMI
        // jarnax::yield();
    }
    jarnax::Ticks ticks = ticker_.GetTicksSinceBoot();
    jarnax::Time time = ticker_.GetTimeSinceBoot();
    uint32_t random = rng_.GetNextRandom();
    jarnax::print("Task::Execute: %lu ticks, %lf sec, 0x%x\r\n", ticks.value(), time.value(), static_cast<unsigned int>(random));
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

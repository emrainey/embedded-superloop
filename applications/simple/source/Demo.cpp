#include "memory.h"
#include "Demo.hpp"
#include "board.hpp"

Demo::Demo()
    : ticker_{jarnax::GetTicker()}
    , timer_{jarnax::GetTimer()}
    , usart_driver_{jarnax::GetDriverContext().GetDebugDriver()}
    , rng_{jarnax::GetDriverContext().GetRandomNumberGenerator()}
    , error_indicator_{jarnax::GetDriverContext().GetErrorIndicator()}
    , status_indicator_{jarnax::GetDriverContext().GetStatusIndicator()}
    , wakeup_button_{jarnax::GetDriverContext().GetWakeupButton()}
    , key0_button_{jarnax::GetDriverContext().GetButton0()}
    , key1_button_{jarnax::GetDriverContext().GetButton1()}
    , copier_{jarnax::GetDriverContext().GetCopier()}
    , winbond_driver_{jarnax::GetDriverContext().GetWinbondDriver()}
    , countdown_{timer_, core::units::Iota{250'000U}}
    , buffer_one_{}
    , buffer_two_{} {
}

void Demo::DelayForTicks(jarnax::Ticks ticks) {
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

void Demo::KeyLoop() {
    if (wakeup_button_.IsPressed()) {
        jarnax::print("Wakeup Pressed\r\n");
    }
    if (key0_button_.IsPressed()) {
        jarnax::print("Key0 Pressed\r\n");
    }
    if (key1_button_.IsPressed()) {
        jarnax::print("Key1 Pressed\r\n");
    }
}

void Demo::CopierTest() {
    if (not buffer_test_) {
        memory::fill(buffer_one_, 0x5A, sizeof(buffer_one_));
        memory::fill(buffer_two_, 0x00, sizeof(buffer_two_));
        copier_.Copy(&buffer_one_[0], &buffer_two_[0], sizeof(buffer_one_));
        if (memory::compare(&buffer_one_[0], &buffer_two_[0], sizeof(buffer_one_)) == 0) {
            jarnax::print("PASSED: Buffers are the same\r\n");
        } else {
            jarnax::print("FAILED: Buffers are different\r\n");
        }
        buffer_test_ = true;
    }
}

bool Demo::Execute() {
    if (countdown_.IsExpired()) {
        status_indicator_.Active();
        jarnax::Ticks ticks = ticker_.GetTicksSinceBoot();
        jarnax::Time time = ticker_.GetTimeSinceBoot();
        uint32_t random = rng_.GetNextRandom();
        std::uint32_t iotas = static_cast<std::uint32_t>(timer_.GetIotas().value());
        jarnax::print("Demo::Execute: %lu ticks, %lf sec, %lx Iotas: %lu\r\n", ticks.value(), time.value(), random, iotas);
        CopierTest();
        KeyLoop();
        status_indicator_.Inactive();
        error_indicator_.Active();
        DelayForTicks(Ticks{64U});
        error_indicator_.Inactive();
        auto hello = core::SpanFrom("Hello World\r\n");
        usart_driver_.Enqueue(hello);
        countdown_.Reset();
    }
    return true;
}

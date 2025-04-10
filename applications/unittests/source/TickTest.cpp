#include "TickTest.hpp"

static TickTest::TestName tests[] = {
    DEFINE_TEST_NAME(TickTests::kCollect),
    DEFINE_TEST_NAME(TickTests::kCompute),
};

TickTest::TickTest()
    : UnitTest{"TickTest", tests} {
}

TickTest::State TickTest::Test(EnumType test_enum) {
    jarnax::Ticker& ticker = jarnax::GetTicker();
    if (not ticker.IsEnabled()) {
        return State::Skipped;
    }
    if (test_enum == EnumType::kCollect) {
        if (tick_index_ < kLength) {
            jarnax::Ticks tmp = jarnax::GetTicker().GetTicksSinceBoot();
            if (ticks_[tick_index_] != tmp) {
                ticks_[tick_index_] = tmp;
                tick_index_++;
            }
        } else {
            return State::Completed;
        }
    } else if (test_enum == EnumType::kCompute) {
        // determine if all ticks are monotonic...
        bool increased = false;
        for (size_t i = 0; i < kLength - 1U; i++) {
            increased = (ticks_[tick_index_] < ticks_[tick_index_ + 1U]);
            Assert(increased, "Value must increase");
        }
    } else {
        return State::Skipped;
    }
    return State::Completed;
}

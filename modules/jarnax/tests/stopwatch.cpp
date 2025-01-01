#include <catch2/catch_test_macros.hpp>
#include "jarnax/StopWatch.hpp"
#include "JumpTimer.hpp"

using namespace core::units;

TEST_CASE("StopWatch") {
    jarnax::JumpTimer timer;
    jarnax::StopWatch stopwatch(timer);
    timer.Jump(10_iota);
    REQUIRE(timer.GetIotas() == 10_iota);

    SECTION("In Order") {
        stopwatch.Start();
        timer.Jump(20_iota);
        stopwatch.Stop();
        REQUIRE(20_iota == stopwatch.GetElapsed());
    }

    SECTION("Out of Order") {
        REQUIRE(0_iota == stopwatch.GetElapsed());
        stopwatch.Stop();    // ignore
        timer.Jump(10_iota);
        REQUIRE(0_iota == stopwatch.GetElapsed());
        stopwatch.Start();    // starts here
        timer.Jump(10_iota);
        REQUIRE(0_iota == stopwatch.GetElapsed());
        // is measuring now
        stopwatch.Start();    // ignore
        timer.Jump(10_iota);
        REQUIRE(0_iota == stopwatch.GetElapsed());
        stopwatch.Stop();    // ends here
        REQUIRE(20_iota == stopwatch.GetElapsed());
        timer.Jump(10_iota);
        stopwatch.Stop();    // ignored
        REQUIRE(20_iota == stopwatch.GetElapsed());
    }
}
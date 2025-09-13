// #define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "core/time/CountDown.hpp"
#include "gtest/JumpClock.hpp"

#include <core/Units.hpp>
using namespace core::units;

TEST_CASE("CountDown") {
    core::time::JumpClock clock;
    clock.Jump(10_usec);
    REQUIRE(clock.Now() == 10_usec);

    SECTION("Construction") {
        core::time::CountDown countdown{clock, 10_usec};
    }
    SECTION("IsExpired") {
        core::time::CountDown countdown{clock, 10_usec};
        REQUIRE(not countdown.IsExpired());
        clock.Jump(10_usec);
        REQUIRE(countdown.GetLateness() == 0_usec);
        REQUIRE(countdown.IsExpired());
    }
    SECTION("Reset") {
        core::time::CountDown countdown{clock, 10_usec};
        REQUIRE(not countdown.IsExpired());
        clock.Jump(10_usec);
        REQUIRE(countdown.IsExpired());
        countdown.Reset();
        REQUIRE(not countdown.IsExpired());
        clock.Jump(10_usec);
        REQUIRE(countdown.IsExpired());
        REQUIRE(countdown.GetLateness() == 0_usec);
    }
    SECTION("Restart") {
        core::time::CountDown countdown{clock, 10_usec};
        REQUIRE(not countdown.IsExpired());
        clock.Jump(10_usec);
        REQUIRE(countdown.IsExpired());
        countdown.Restart(20_usec);
        REQUIRE(not countdown.IsExpired());
        clock.Jump(10_usec);
        REQUIRE(not countdown.IsExpired());
        clock.Jump(10_usec);
        REQUIRE(countdown.IsExpired());
        REQUIRE(countdown.GetLateness() == 0_usec);
    }
    SECTION("Lateness Accounted Reset") {
        core::time::CountDown countdown{clock, 10_usec};
        REQUIRE(not countdown.IsExpired());
        clock.Jump(15_usec);
        REQUIRE(countdown.IsExpired());
        REQUIRE(countdown.GetLateness() == 5_usec);
        countdown.Reset();
        REQUIRE(not countdown.IsExpired());
        clock.Jump(3_usec);
        REQUIRE(not countdown.IsExpired());
        clock.Jump(2_usec);
        REQUIRE(countdown.IsExpired());
    }
    SECTION("Lateness Not Accounted Restart") {
        core::time::CountDown countdown{clock, 10_usec};
        REQUIRE(not countdown.IsExpired());
        clock.Jump(15_usec);
        REQUIRE(countdown.IsExpired());
        REQUIRE(countdown.GetLateness() == 5_usec);
        countdown.Restart(20_usec);
        REQUIRE(not countdown.IsExpired());
        clock.Jump(15_usec);
        REQUIRE(not countdown.IsExpired());
        clock.Jump(5_usec);
        REQUIRE(countdown.IsExpired());
    }
}

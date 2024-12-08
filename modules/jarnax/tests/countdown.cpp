// #define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "jarnax/CountDown.hpp"
#include "JumpTimer.hpp"

#include <core/Units.hpp>
using namespace core::units;

TEST_CASE("CountDown") {
    jarnax::JumpTimer timer;
    timer.Jump(10_iota);
    REQUIRE(timer.GetIotas() == 10_iota);

    SECTION("Construction") {
        jarnax::CountDown countdown{timer, 10_iota};
    }
    SECTION("IsExpired") {
        jarnax::CountDown countdown{timer, 10_iota};
        REQUIRE(not countdown.IsExpired());
        timer.Jump(10_iota);
        REQUIRE(countdown.GetLateness() == 0_iota);
        REQUIRE(countdown.IsExpired());
    }
    SECTION("Reset") {
        jarnax::CountDown countdown{timer, 10_iota};
        REQUIRE(not countdown.IsExpired());
        timer.Jump(10_iota);
        REQUIRE(countdown.IsExpired());
        countdown.Reset();
        REQUIRE(not countdown.IsExpired());
        timer.Jump(10_iota);
        REQUIRE(countdown.IsExpired());
        REQUIRE(countdown.GetLateness() == 0_iota);
    }
    SECTION("Restart") {
        jarnax::CountDown countdown{timer, 10_iota};
        REQUIRE(not countdown.IsExpired());
        timer.Jump(10_iota);
        REQUIRE(countdown.IsExpired());
        countdown.Restart(20_iota);
        REQUIRE(not countdown.IsExpired());
        timer.Jump(10_iota);
        REQUIRE(not countdown.IsExpired());
        timer.Jump(10_iota);
        REQUIRE(countdown.IsExpired());
        REQUIRE(countdown.GetLateness() == 0_iota);
    }
    SECTION("Lateness Accounted Reset") {
        jarnax::CountDown countdown{timer, 10_iota};
        REQUIRE(not countdown.IsExpired());
        timer.Jump(15_iota);
        REQUIRE(countdown.IsExpired());
        REQUIRE(countdown.GetLateness() == 5_iota);
        countdown.Reset();
        REQUIRE(not countdown.IsExpired());
        timer.Jump(3_iota);
        REQUIRE(not countdown.IsExpired());
        timer.Jump(2_iota);
        REQUIRE(countdown.IsExpired());
    }
    SECTION("Lateness Not Accounted Restart") {
        jarnax::CountDown countdown{timer, 10_iota};
        REQUIRE(not countdown.IsExpired());
        timer.Jump(15_iota);
        REQUIRE(countdown.IsExpired());
        REQUIRE(countdown.GetLateness() == 5_iota);
        countdown.Restart(20_iota);
        REQUIRE(not countdown.IsExpired());
        timer.Jump(15_iota);
        REQUIRE(not countdown.IsExpired());
        timer.Jump(5_iota);
        REQUIRE(countdown.IsExpired());
    }
}

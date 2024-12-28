// #define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "jarnax/Context.hpp"
#include "jarnax/SuperLoop.hpp"
#include "JumpTicker.hpp"
#include "TestContext.hpp"

#include <cstdio>

using namespace core::units;

namespace jarnax {

class DummyTask : public Loopable {
public:
    DummyTask(const char *name)
        : Loopable()
        , name_{name}
        , should_keep_going_{true} {}

    bool Execute() override {
        std::cout << "Running in slot " << GetLoopInfo().cadence_slot << std::endl;
        return should_keep_going_;
    }

    friend std::ostream &operator<<(std::ostream &os, const DummyTask &dummy) {
        os << dummy.name_ << ": " << std::dec << dummy.GetInfo().count;
        return os;
    }

    void Stop() { should_keep_going_ = false; }

protected:
    char const *name_;
    bool should_keep_going_;
};

TEST_CASE("SuperLoop - Two Tasks") {
    JumpTicker ticker{10_ticks};
    SuperLoop loop{ticker};
    DummyTask dummy0{"DummyTask0"};
    DummyTask dummy1{"DummyTask1"};
    loop.Enlist(dummy0);
    loop.Enlist(dummy1);
    SECTION("Single Loop") {
        loop.RunAllOnce();
        std::cout << loop << std::endl;
        REQUIRE(dummy0.GetInfo().count == 1U);
        REQUIRE(dummy1.GetInfo().count == 1U);
    }
    SECTION("All Count but Stop One") {
        dummy0.Stop();
        for (size_t i = 0; i < SlotsInCadence; i++) {
            loop.RunAllOnce();
        }
        std::cout << loop << std::endl;
        REQUIRE(dummy0.GetInfo().count == 1U);    // stopped after the first loop was called
        REQUIRE(dummy1.GetInfo().count == 32U);
    }
}

TEST_CASE("SuperLoop - Cadence Test") {
    JumpTicker ticker{10_ticks};
    SuperLoop loop{ticker};
    DummyTask dummy0{"DummyTask0"};
    DummyTask dummy1{"DummyTask1"};
    DummyTask dummy2{"DummyTask2"};
    DummyTask dummy3{"DummyTask3"};
    // right now these have to be read as RIGHT to LEFT <--
    loop.Enlist(dummy0, 0b1010'1010'1010'1010'1010'1010'1010'1010u);
    loop.Enlist(dummy1, 0b0101'0101'0101'0101'0101'0101'0101'0101u);
    loop.Enlist(dummy2, 0b1111'1111'1111'1111'1111'1111'1111'1111u);
    loop.Enlist(dummy3, 0b1111'0000'1111'0000'1111'0000'1111'0000u);

    SECTION("Single Loop") {
        loop.RunAllOnce();
        std::cout << loop << std::endl;
        REQUIRE(dummy0.GetInfo().count == 0U);
        REQUIRE(dummy1.GetInfo().count == 1U);
        REQUIRE(dummy2.GetInfo().count == 1U);
        REQUIRE(dummy3.GetInfo().count == 0U);
    }
    SECTION("All Count") {
        for (size_t i = 0; i < SlotsInCadence; i++) {
            loop.RunAllOnce();
        }
        std::cout << loop << std::endl;
        REQUIRE(dummy0.GetInfo().count == 16U);
        REQUIRE(dummy1.GetInfo().count == 16U);
        REQUIRE(dummy2.GetInfo().count == 32U);
        REQUIRE(dummy3.GetInfo().count == 16U);
    }
    SECTION("All Count But First Dismissed") {
        loop.Dismiss(dummy0);
        for (size_t i = 0; i < SlotsInCadence; i++) {
            loop.RunAllOnce();
        }
        std::cout << loop << std::endl;
        CHECK(dummy0.GetInfo().count == 0U);
        CHECK(dummy1.GetInfo().count == 16U);
        CHECK(dummy2.GetInfo().count == 32U);
        CHECK(dummy3.GetInfo().count == 16U);
    }
    SECTION("All Count But Last Dismissed") {
        loop.Dismiss(dummy3);
        for (size_t i = 0; i < SlotsInCadence; i++) {
            loop.RunAllOnce();
        }
        std::cout << loop << std::endl;
        CHECK(dummy0.GetInfo().count == 16U);
        CHECK(dummy1.GetInfo().count == 16U);
        CHECK(dummy2.GetInfo().count == 32U);
        CHECK(dummy3.GetInfo().count == 0U);
    }
    SECTION("All Count But Middle Dismissed") {
        loop.Dismiss(dummy1);
        for (size_t i = 0; i < SlotsInCadence; i++) {
            loop.RunAllOnce();
        }
        std::cout << loop << std::endl;
        CHECK(dummy0.GetInfo().count == 16U);
        CHECK(dummy1.GetInfo().count == 0U);
        CHECK(dummy2.GetInfo().count == 32U);
        CHECK(dummy3.GetInfo().count == 16U);
    }
    SECTION("All Count But First and Last Dismissed") {
        loop.Dismiss(dummy0);
        loop.Dismiss(dummy3);
        for (size_t i = 0; i < SlotsInCadence; i++) {
            loop.RunAllOnce();
        }
        std::cout << loop << std::endl;
        CHECK(dummy0.GetInfo().count == 0U);
        CHECK(dummy1.GetInfo().count == 16U);
        CHECK(dummy2.GetInfo().count == 32U);
        CHECK(dummy3.GetInfo().count == 0U);
    }
    SECTION("All Count But Everything Dismissed") {
        loop.Dismiss(dummy0);
        loop.Dismiss(dummy1);
        loop.Dismiss(dummy2);
        loop.Dismiss(dummy3);
        for (size_t i = 0; i < SlotsInCadence; i++) {
            loop.RunAllOnce();
        }
        std::cout << loop << std::endl;
        CHECK(dummy0.GetInfo().count == 0U);
        CHECK(dummy1.GetInfo().count == 0U);
        CHECK(dummy2.GetInfo().count == 0U);
        CHECK(dummy3.GetInfo().count == 0U);
    }
}

}    // namespace jarnax
// #define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "jarnax/Context.hpp"
#include "jarnax/Transactable.hpp"

#include <cstdio>

using namespace core::units;

namespace jarnax {

class FakeTimer : public Timer {
public:
    FakeTimer()
        : current_{0U} {}

    Iota GetIotas(void) const override {
        Iota tmp;
        tmp = current_;
        current_ = current_ + 1_iota;
        return tmp;
    }

    MicroSeconds GetMicroseconds(void) const override {
        return core::units::MicroSeconds{GetIotas().value()};
    }

protected:
    mutable Iota current_{0U};
};

class DummyTransaction : public Transactable<DummyTransaction, 3> {
public:
    DummyTransaction(Timer& timer)
        : Transactable{timer} {}

    void Clear() {
        id_ = 0;
        return;
    }

    void Initialize(std::size_t id) {
        id_ = id;
        Inform(Event::Initialized);
        return;
    }

    std::size_t id_;
};

TEST_CASE("Transactable") {
    FakeTimer timer;
    DummyTransaction dummy{timer};

    SECTION("Default") {
        REQUIRE(not dummy.IsComplete());
        REQUIRE(dummy.GetStatus() == Status{core::Result::NotInitialized, core::Cause::State});
        REQUIRE(dummy.GetAttemptsRemaining() == 3);
        REQUIRE(dummy.GetDuration().value() == 0U);
    }
    SECTION("LifeCycle") {
        dummy.Initialize(1);
        REQUIRE(dummy.IsInitialized());
        dummy.Inform(DummyTransaction::Event::Scheduled);
        REQUIRE(dummy.IsQueued());
        dummy.Inform(DummyTransaction::Event::Start);
        REQUIRE(dummy.IsRunning());
        REQUIRE(dummy.GetStatus() == Status{core::Result::Busy, core::Cause::State});
        dummy.Inform(DummyTransaction::Event::Completed, Status{core::Result::Success, core::Cause::Unknown});
        REQUIRE(dummy.IsComplete());
        REQUIRE(dummy.GetAttemptsRemaining() == 2);
        REQUIRE(dummy.GetDuration().value() == 1U);
        REQUIRE(dummy.GetStatus() == Status{core::Result::Success, core::Cause::Unknown});
        //======================================================================
        REQUIRE(dummy.Reset());
        REQUIRE(not dummy.IsComplete());
        REQUIRE(dummy.GetAttemptsRemaining() == 3);
        REQUIRE(dummy.GetDuration().value() == 0U);
        REQUIRE(dummy.GetStatus() == Status{core::Result::NotInitialized, core::Cause::State});
        //======================================================================
        dummy.Initialize(2);
        REQUIRE(dummy.IsInitialized());
        dummy.Inform(DummyTransaction::Event::Scheduled);
        REQUIRE(dummy.IsQueued());
        dummy.Inform(DummyTransaction::Event::Start);
        REQUIRE(dummy.IsRunning());
        REQUIRE(dummy.GetStatus() == Status{core::Result::Busy, core::Cause::State});
        dummy.Inform(DummyTransaction::Event::Completed, Status{core::Result::Success, core::Cause::Unknown});
        REQUIRE(dummy.IsComplete());
        REQUIRE(dummy.GetAttemptsRemaining() == 2);
        REQUIRE(dummy.GetDuration().value() == 1U);
        REQUIRE(dummy.GetStatus() == Status{core::Result::Success, core::Cause::Unknown});
    }
}

}    // namespace jarnax

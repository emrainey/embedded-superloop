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

static constexpr std::size_t Attempts = 3u;

class DummyTransaction : public Transactable<DummyTransaction, Attempts> {
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
        REQUIRE(dummy.GetAttemptsRemaining() == Attempts);
        REQUIRE(dummy.GetDuration().value() == 0U);
    }
    SECTION("LifeCycle") {
        dummy.Initialize(1);
        REQUIRE(dummy.IsInitialized());
        dummy.Inform(DummyTransaction::Event::Scheduled);
        REQUIRE(dummy.IsQueued());
        REQUIRE(dummy.GetAttemptsRemaining() == Attempts);
        dummy.Inform(DummyTransaction::Event::Start);
        REQUIRE(dummy.IsRunning());
        REQUIRE(dummy.GetStatus() == Status{core::Result::Busy, core::Cause::State});
        dummy.Inform(DummyTransaction::Event::Completed, Status{core::Result::Success, core::Cause::Unknown});
        REQUIRE(dummy.IsComplete());
        REQUIRE(dummy.GetAttemptsRemaining() == Attempts - 1);
        REQUIRE(dummy.GetDuration().value() == 1U);
        REQUIRE(dummy.GetStatus() == Status{core::Result::Success, core::Cause::Unknown});
        //======================================================================
        REQUIRE(dummy.Reset());
        REQUIRE(not dummy.IsComplete());
        REQUIRE(dummy.GetAttemptsRemaining() == Attempts);
        REQUIRE(dummy.GetDuration().value() == 0U);
        REQUIRE(dummy.GetStatus() == Status{core::Result::NotInitialized, core::Cause::State});
        //======================================================================
        dummy.Initialize(2);
        REQUIRE(dummy.IsInitialized());
        dummy.Inform(DummyTransaction::Event::Scheduled);
        REQUIRE(dummy.IsQueued());
        REQUIRE(dummy.GetAttemptsRemaining() == Attempts);
        dummy.Inform(DummyTransaction::Event::Start);
        REQUIRE(dummy.IsRunning());
        REQUIRE(dummy.GetStatus() == Status{core::Result::Busy, core::Cause::State});
        dummy.Inform(DummyTransaction::Event::Completed, Status{core::Result::Success, core::Cause::Unknown});
        REQUIRE(dummy.IsComplete());
        REQUIRE(dummy.GetAttemptsRemaining() == Attempts - 1);
        REQUIRE(dummy.GetDuration().value() == 1U);
        REQUIRE(dummy.GetStatus() == Status{core::Result::Success, core::Cause::Unknown});
    }
    SECTION("Retry") {
        dummy.Initialize(3);
        REQUIRE(dummy.IsInitialized());
        dummy.Inform(DummyTransaction::Event::Scheduled);
        REQUIRE(dummy.IsQueued());
        REQUIRE(dummy.GetAttemptsRemaining() == Attempts);
        dummy.Inform(DummyTransaction::Event::Start);
        REQUIRE(dummy.IsRunning());
        REQUIRE(dummy.GetAttemptsRemaining() == Attempts - 1);
        dummy.Inform(DummyTransaction::Event::Retry);
        REQUIRE(dummy.IsQueued());
        dummy.Inform(DummyTransaction::Event::Start);
        REQUIRE(dummy.IsRunning());
        REQUIRE(dummy.GetAttemptsRemaining() == Attempts - 2);
        dummy.Inform(DummyTransaction::Event::Retry);
        REQUIRE(dummy.IsQueued());
        dummy.Inform(DummyTransaction::Event::Start);
        REQUIRE(dummy.IsRunning());
        REQUIRE(dummy.GetAttemptsRemaining() == Attempts - 3);
        dummy.Inform(DummyTransaction::Event::Retry);
        REQUIRE(dummy.IsComplete());
        REQUIRE(dummy.GetStatus() == Status{core::Result::ExceededLimit, core::Cause::State});
        REQUIRE(dummy.GetAttemptsRemaining() == 0);
    }
}

}    // namespace jarnax

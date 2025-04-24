// #define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "jarnax/Context.hpp"
#include "jarnax/Transactable.hpp"
#include "JumpTimer.hpp"

#include <cstdio>

using namespace core::units;

namespace jarnax {

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
    JumpTimer timer;
    DummyTransaction dummy{timer};

    SECTION("Default") {
        REQUIRE(not dummy.IsComplete());
        REQUIRE(dummy.GetStatus() == core::Status{core::Result::NotInitialized, core::Cause::State});
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
        REQUIRE(dummy.GetStatus() == core::Status{core::Result::Busy, core::Cause::State});
        timer.Jump(7_usec);
        dummy.Inform(DummyTransaction::Event::Completed, core::Status{core::Result::Success, core::Cause::Unknown});
        REQUIRE(dummy.IsComplete());
        REQUIRE(dummy.GetAttemptsRemaining() == Attempts - 1);
        REQUIRE(dummy.GetDuration().value() == 7U);
        REQUIRE(dummy.GetStatus() == core::Status{core::Result::Success, core::Cause::Unknown});
        //======================================================================
        REQUIRE(dummy.Reset());
        REQUIRE(not dummy.IsComplete());
        REQUIRE(dummy.GetAttemptsRemaining() == Attempts);
        REQUIRE(dummy.GetDuration().value() == 0U);
        REQUIRE(dummy.GetStatus() == core::Status{core::Result::NotInitialized, core::Cause::State});
        //======================================================================
        dummy.Initialize(2);
        REQUIRE(dummy.IsInitialized());
        dummy.Inform(DummyTransaction::Event::Scheduled);
        REQUIRE(dummy.IsQueued());
        REQUIRE(dummy.GetAttemptsRemaining() == Attempts);
        dummy.Inform(DummyTransaction::Event::Start);
        REQUIRE(dummy.IsRunning());
        REQUIRE(dummy.GetStatus() == core::Status{core::Result::Busy, core::Cause::State});
        timer.Jump(7_usec);
        dummy.Inform(DummyTransaction::Event::Completed, core::Status{core::Result::Success, core::Cause::Unknown});
        REQUIRE(dummy.IsComplete());
        REQUIRE(dummy.GetAttemptsRemaining() == Attempts - 1);
        REQUIRE(dummy.GetDuration().value() == 7U);
        REQUIRE(dummy.GetStatus() == core::Status{core::Result::Success, core::Cause::Unknown});
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
        REQUIRE(dummy.GetStatus() == core::Status{core::Result::ExceededLimit, core::Cause::State});
        REQUIRE(dummy.GetAttemptsRemaining() == 0);
    }
    SECTION("Deadline") {
        dummy.Initialize(3);
        dummy.SetDeadline(timer.GetMicroseconds() + 100_usec);
        REQUIRE(dummy.IsInitialized());
        dummy.Inform(DummyTransaction::Event::Scheduled);
        REQUIRE(dummy.IsQueued());
        REQUIRE(dummy.GetAttemptsRemaining() == Attempts);
        // time passes (over the amount)
        timer.Jump(timer.GetMicroseconds() + 200_usec);
        dummy.Inform(DummyTransaction::Event::Start);
        REQUIRE(dummy.IsComplete());
        REQUIRE(dummy.GetStatus() == core::Status{core::Result::Timeout, core::Cause::State});
    }
}

}    // namespace jarnax

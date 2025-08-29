#include <catch2/catch_test_macros.hpp>
#include "core/Event.hpp"
#include "core/StateChart.hpp"

enum class State : std::uint32_t {
    Undefined = 0,    ///< [Required Name and Value] The undefined state, must be zero
    Initializing,     ///< The Initial state, goes to Running after 3 cycles
    Running,          ///< The Running state, goes to Completing when event is 2
    Completing,       ///< The Completing state
    Final,            ///< [Required Name] The last state, will exit the state chart when returned.
};

class StateChartFixture : public core::StateChart<State>, private core::StateChart<State>::Callback {
public:
    StateChartFixture()
        : core::StateChart<State>{static_cast<core::StateChart<State>::Callback&>(*this)}
        , results{}
        , event{1}
        , counter{0U} {}

    virtual ~StateChartFixture() = default;

    void OnEnter() override { results.entered = true; }

    void OnEntry(State state) override {
        results.entry = true;
        if (state == State::Initializing) {
            counter = 0U;
        } else if (state == State::Running) {
            event = 0U;
            value = 0U;
        } else if (state == State::Completing) {
            // nothing to do
        }
    }

    void OnCycle(State state) override {
        results.cycled = true;
        if (state == State::Initializing) {
            counter++;
        } else if (state == State::Running) {
            if (event) {
                value = uint32_t(event);
            }
        } else if (state == State::Completing) {
            // nothing
        }
    }

    bool OnGuard(State state) const override {
        results.guard = true;
        if (state == State::Initializing) {
            return counter >= 3U;
        } else if (state == State::Running) {
            return value == 2;
        } else if (state == State::Completing) {
            return true;    // always leave Completing
        }
        return false;       // should not get here
    }

    void OnExit(State state) override {
        static_cast<void>(state);
        results.exit = true;
    }

    State OnTransition(State from) override {
        results.transitioned = true;
        if (from == State::Undefined) {
            return State::Initializing;
        } else if (from == State::Initializing) {
            results.initial_to_running = true;
            return State::Running;
        } else if (from == State::Running) {
            results.running_to_completing = true;
            return State::Completing;
        } else if (from == State::Completing) {
            return State::Final;
        }
        return State::Undefined;
    }

    void OnExit() override { results.exited = true; }

    void ResetFlags() {
        results.entered = false;
        results.entry = false;
        results.cycled = false;
        results.initial_to_running = false;
        results.running_to_completing = false;
        results.transitioned = false;
        results.exit = false;
        results.exited = false;
    }

    struct Results {
        bool entered{false};
        bool entry{false};
        bool guard{false};
        bool cycled{false};
        bool initial_to_running{false};
        bool running_to_completing{false};
        bool transitioned{false};
        bool exit{false};
        bool exited{false};
    };

    void SetEvent(uint32_t v) { event = v; }
    uint32_t GetEvent() { return uint32_t(event); }

    Results& GetResults() { return results; }

private:
    mutable Results results;
    core::events::Single<uint32_t> event;
    uint32_t value;
    std::size_t counter;
};

TEST_CASE("StateChart - Basics") {
    StateChartFixture sm;
    REQUIRE(sm.Is(State::Undefined));
    REQUIRE(sm.IsFinal());
    sm.Enter();
    REQUIRE(sm.GetResults().entered);
    REQUIRE(sm.GetResults().entry);
    REQUIRE(not sm.GetResults().guard);
    REQUIRE(not sm.GetResults().cycled);
    REQUIRE(not sm.GetResults().exit);
    REQUIRE(sm.GetResults().transitioned);
    REQUIRE(not sm.GetResults().exited);
    REQUIRE(not sm.GetResults().initial_to_running);
    REQUIRE(not sm.GetResults().running_to_completing);
    sm.ResetFlags();
    sm.RunOnce();
    REQUIRE(not sm.GetResults().entered);
    REQUIRE(not sm.GetResults().entry);
    REQUIRE(sm.GetResults().guard);
    REQUIRE(sm.GetResults().cycled);
    REQUIRE(not sm.GetResults().exit);
    REQUIRE(not sm.GetResults().transitioned);
    REQUIRE(not sm.GetResults().exited);
    REQUIRE(not sm.GetResults().initial_to_running);
    REQUIRE(not sm.GetResults().running_to_completing);
    REQUIRE(sm.Is(State::Initializing));
    REQUIRE(not sm.IsFinal());
    sm.ResetFlags();
    sm.RunOnce();
    REQUIRE(not sm.GetResults().entered);
    REQUIRE(not sm.GetResults().entry);
    REQUIRE(sm.GetResults().guard);
    REQUIRE(sm.GetResults().cycled);
    REQUIRE(not sm.GetResults().exit);
    REQUIRE(not sm.GetResults().transitioned);
    REQUIRE(not sm.GetResults().exited);
    REQUIRE(not sm.GetResults().initial_to_running);
    REQUIRE(not sm.GetResults().running_to_completing);
    REQUIRE(sm.Is(State::Initializing));
    REQUIRE(not sm.IsFinal());
    sm.ResetFlags();
    sm.RunOnce();
    REQUIRE(not sm.GetResults().entered);
    REQUIRE(not sm.GetResults().entry);
    REQUIRE(sm.GetResults().guard);
    REQUIRE(sm.GetResults().cycled);
    REQUIRE(not sm.GetResults().exit);
    REQUIRE(not sm.GetResults().transitioned);
    REQUIRE(not sm.GetResults().exited);
    REQUIRE(not sm.GetResults().initial_to_running);
    REQUIRE(not sm.GetResults().running_to_completing);
    REQUIRE(sm.Is(State::Initializing));
    REQUIRE(not sm.IsFinal());
    sm.ResetFlags();
    // the counter should cause a transition to Running
    sm.RunOnce();
    REQUIRE(not sm.GetResults().entered);
    REQUIRE(sm.GetResults().guard);
    REQUIRE(not sm.GetResults().cycled);
    REQUIRE(sm.GetResults().exit);     // counter should have hit 3
    REQUIRE(sm.GetResults().transitioned);
    REQUIRE(sm.GetResults().entry);    // entered the next state
    REQUIRE(not sm.GetResults().exited);
    REQUIRE(sm.GetResults().initial_to_running);
    REQUIRE(not sm.GetResults().running_to_completing);
    REQUIRE(sm.Is(State::Running));
    REQUIRE(not sm.IsFinal());
    sm.ResetFlags();
    sm.RunOnce();
    REQUIRE(not sm.GetResults().entered);
    REQUIRE(not sm.GetResults().entry);
    REQUIRE(sm.GetResults().guard);
    REQUIRE(sm.GetResults().cycled);
    REQUIRE(not sm.GetResults().exit);
    REQUIRE(not sm.GetResults().transitioned);
    REQUIRE(not sm.GetResults().exited);
    REQUIRE(not sm.GetResults().initial_to_running);
    REQUIRE(not sm.GetResults().running_to_completing);
    REQUIRE(sm.Is(State::Running));
    REQUIRE(not sm.IsFinal());
    sm.ResetFlags();
    sm.RunOnce();
    REQUIRE(sm.Is(State::Running));
    REQUIRE(not sm.GetResults().entered);
    REQUIRE(not sm.GetResults().entry);
    REQUIRE(sm.GetResults().guard);
    REQUIRE(sm.GetResults().cycled);
    REQUIRE(not sm.GetResults().exit);
    REQUIRE(not sm.GetResults().transitioned);
    REQUIRE(not sm.GetResults().exited);
    REQUIRE(not sm.GetResults().initial_to_running);
    REQUIRE(not sm.GetResults().running_to_completing);
    REQUIRE(not sm.IsFinal());
    sm.ResetFlags();
    sm.RunOnce();
    REQUIRE(sm.Is(State::Running));
    REQUIRE(not sm.GetResults().entered);
    REQUIRE(not sm.GetResults().entry);
    REQUIRE(sm.GetResults().guard);
    REQUIRE(sm.GetResults().cycled);
    REQUIRE(not sm.GetResults().exit);
    REQUIRE(not sm.GetResults().transitioned);
    REQUIRE(not sm.GetResults().exited);
    REQUIRE(not sm.GetResults().initial_to_running);
    REQUIRE(not sm.GetResults().running_to_completing);
    REQUIRE(not sm.IsFinal());
    sm.ResetFlags();
    sm.RunOnce();
    REQUIRE(sm.Is(State::Running));
    REQUIRE(not sm.GetResults().entered);
    REQUIRE(not sm.GetResults().entry);
    REQUIRE(sm.GetResults().guard);
    REQUIRE(sm.GetResults().cycled);
    REQUIRE(not sm.GetResults().exit);
    REQUIRE(not sm.GetResults().transitioned);
    REQUIRE(not sm.GetResults().exited);
    REQUIRE(not sm.GetResults().initial_to_running);
    REQUIRE(not sm.GetResults().running_to_completing);
    REQUIRE(not sm.IsFinal());
    sm.ResetFlags();
    sm.SetEvent(2);    // this should cause a transition to Completing on the next cycle?
    sm.RunOnce();
    REQUIRE(sm.Is(State::Running));
    REQUIRE(not sm.GetResults().entered);
    REQUIRE(not sm.GetResults().entry);
    REQUIRE(sm.GetResults().guard);
    REQUIRE(sm.GetResults().cycled);
    REQUIRE(not sm.GetResults().exit);
    REQUIRE(not sm.GetResults().transitioned);
    REQUIRE(not sm.GetResults().exited);
    REQUIRE(not sm.GetResults().initial_to_running);
    REQUIRE(not sm.GetResults().running_to_completing);
    REQUIRE(not sm.IsFinal());
    sm.ResetFlags();
    sm.RunOnce();
    REQUIRE(sm.Is(State::Completing));
    REQUIRE(not sm.GetResults().entered);
    REQUIRE(sm.GetResults().entry);
    REQUIRE(sm.GetResults().guard);
    REQUIRE(not sm.GetResults().cycled);
    REQUIRE(sm.GetResults().exit);
    REQUIRE(sm.GetResults().transitioned);
    REQUIRE(not sm.GetResults().exited);
    REQUIRE(not sm.GetResults().initial_to_running);
    REQUIRE(sm.GetResults().running_to_completing);
    REQUIRE(not sm.IsFinal());
    sm.ResetFlags();
    // now
    sm.RunOnce();
    REQUIRE(sm.Is(State::Undefined));
    REQUIRE(not sm.GetResults().entered);
    REQUIRE(sm.GetResults().guard);
    REQUIRE(not sm.GetResults().cycled);
    REQUIRE(sm.GetResults().exit);
    REQUIRE(not sm.GetResults().entry);
    REQUIRE(sm.GetResults().transitioned);
    REQUIRE(sm.GetResults().exited);
    REQUIRE(not sm.GetResults().initial_to_running);
    REQUIRE(not sm.GetResults().running_to_completing);
    sm.ResetFlags();
    REQUIRE(sm.IsFinal());

    REQUIRE(sm.GetStatistics().entered == 1U);
    REQUIRE(sm.GetStatistics().entries == 3U);
    REQUIRE(sm.GetStatistics().guards == 11U);
    REQUIRE(sm.GetStatistics().cycles == 8U);
    REQUIRE(sm.GetStatistics().exits == 3U);
    REQUIRE(sm.GetStatistics().exited == 1U);
}

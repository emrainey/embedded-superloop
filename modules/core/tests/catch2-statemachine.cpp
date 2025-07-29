#include <catch2/catch_test_macros.hpp>
#include "core/StateMachine.hpp"
#include "core/Event.hpp"

enum class State : std::uint32_t {
    Undefined = 0,    ///< Required by StateMachine
    Initial,          ///< The initial state, goes to Running after 3 cycles
    Running,          ///< The running state, goes to Done when event is 2
    Done,             ///< The last state, should exit the state machine
};

class StateMachineFixture : public core::StateMachine<State>, private core::StateMachine<State>::Callback {
public:
    StateMachineFixture()
        : StateMachine<State>{*this, State::Initial}
        , results{}
        , statistics{}
        , event{}
        , counter{0U} {}

    void OnEnter() override {
        results.started = true;
        statistics.enter++;
    }

    void OnEntry(State state) override {
        results.entry = true;
        statistics.entries++;
        if (state == State::Initial) {
            counter = 0U;
        } else if (state == State::Running) {
            event = 0U;
        } else if (state == State::Done) {
            // nothing to do
        }
    }

    State OnCycle(State state) override {
        results.cycled = true;
        statistics.cycles++;
        if (state == State::Initial) {
            counter++;
            if (counter == 3U) {
                return State::Running;
            }
        } else if (state == State::Running) {
            if (event) {
                uint32_t value = uint32_t(event);
                if (value == 2) {
                    return State::Done;
                }
            }
        } else if (state == State::Done) {
            state = State::Undefined;    // exit the state machine
        }
        // otherwise stay in the current state
        return state;
    }

    void OnExit(State state) override {
        static_cast<void>(state);
        results.exit = true;
        statistics.exits++;
    }

    void OnTransition(State from, State to) override {
        results.transitioned = true;
        statistics.transitions++;
        if (from == State::Initial and to == State::Running) {
            results.initial_to_running = true;
        } else if (from == State::Running and to == State::Done) {
            results.running_to_done = true;
        }
    }

    void OnExit() override {
        results.stopped = true;
        statistics.exit++;
    }

    void ResetFlags() {
        results.started = false;
        results.entry = false;
        results.cycled = false;
        results.initial_to_running = false;
        results.running_to_done = false;
        results.transitioned = false;
        results.exit = false;
        results.stopped = false;
    }

    struct Results {
        bool started{false};
        bool entry{false};
        bool cycled{false};
        bool initial_to_running{false};
        bool running_to_done{false};
        bool transitioned{false};
        bool exit{false};
        bool stopped{false};
    };
    struct Statistics {
        size_t enter{0U};
        size_t entries{0U};
        size_t cycles{0U};
        size_t exits{0U};
        size_t transitions{0U};
        size_t exit{0U};
    };

    void SetEvent(uint32_t value) { event = value; }
    uint32_t GetEvent() { return uint32_t(event); }

    Results& GetResults() { return results; }
    Statistics& GetStatistics() { return statistics; }

private:
    Results results;
    Statistics statistics;
    core::events::Single<uint32_t> event;
    std::size_t counter;
};

TEST_CASE("StateMachine - Basics") {
    StateMachineFixture sm;
    REQUIRE(not sm.IsMalformed());
    REQUIRE(sm.Is(State::Undefined));
    REQUIRE(sm.IsFinal());
    sm.Enter();
    REQUIRE(sm.GetResults().started);
    REQUIRE(sm.GetResults().entry);
    REQUIRE(not sm.GetResults().cycled);
    REQUIRE(not sm.GetResults().exit);
    REQUIRE(not sm.GetResults().transitioned);
    REQUIRE(not sm.GetResults().stopped);
    REQUIRE(not sm.GetResults().initial_to_running);
    REQUIRE(not sm.GetResults().running_to_done);
    sm.ResetFlags();
    sm.RunOnce();
    REQUIRE(not sm.GetResults().started);
    REQUIRE(not sm.GetResults().entry);
    REQUIRE(sm.GetResults().cycled);
    REQUIRE(not sm.GetResults().exit);
    REQUIRE(not sm.GetResults().transitioned);
    REQUIRE(not sm.GetResults().stopped);
    REQUIRE(not sm.GetResults().initial_to_running);
    REQUIRE(not sm.GetResults().running_to_done);
    REQUIRE(sm.Is(State::Initial));
    REQUIRE(not sm.IsFinal());
    sm.ResetFlags();
    sm.RunOnce();
    REQUIRE(not sm.GetResults().started);
    REQUIRE(not sm.GetResults().entry);
    REQUIRE(sm.GetResults().cycled);
    REQUIRE(not sm.GetResults().exit);
    REQUIRE(not sm.GetResults().transitioned);
    REQUIRE(not sm.GetResults().stopped);
    REQUIRE(not sm.GetResults().initial_to_running);
    REQUIRE(not sm.GetResults().running_to_done);
    REQUIRE(sm.Is(State::Initial));
    REQUIRE(not sm.IsFinal());
    sm.ResetFlags();
    // the counter should cause a transition to Running
    sm.RunOnce();
    REQUIRE(not sm.GetResults().started);
    REQUIRE(sm.GetResults().entry);    // entered the next state
    REQUIRE(sm.GetResults().cycled);
    REQUIRE(sm.GetResults().exit);    // counter should have hit 3
    REQUIRE(sm.GetResults().transitioned);
    REQUIRE(not sm.GetResults().stopped);
    REQUIRE(sm.GetResults().initial_to_running);
    REQUIRE(not sm.GetResults().running_to_done);
    REQUIRE(sm.Is(State::Running));
    REQUIRE(not sm.IsFinal());
    sm.ResetFlags();
    sm.RunOnce();
    REQUIRE(not sm.GetResults().started);
    REQUIRE(not sm.GetResults().entry);
    REQUIRE(sm.GetResults().cycled);
    REQUIRE(not sm.GetResults().exit);
    REQUIRE(not sm.GetResults().transitioned);
    REQUIRE(not sm.GetResults().stopped);
    REQUIRE(not sm.GetResults().initial_to_running);
    REQUIRE(not sm.GetResults().running_to_done);
    REQUIRE(sm.Is(State::Running));
    REQUIRE(not sm.IsFinal());
    sm.ResetFlags();
    sm.RunOnce();
    REQUIRE(sm.Is(State::Running));
    REQUIRE(not sm.GetResults().started);
    REQUIRE(not sm.GetResults().entry);
    REQUIRE(sm.GetResults().cycled);
    REQUIRE(not sm.GetResults().exit);
    REQUIRE(not sm.GetResults().transitioned);
    REQUIRE(not sm.GetResults().stopped);
    REQUIRE(not sm.GetResults().initial_to_running);
    REQUIRE(not sm.GetResults().running_to_done);
    REQUIRE(not sm.IsFinal());
    sm.ResetFlags();
    sm.RunOnce();
    REQUIRE(sm.Is(State::Running));
    REQUIRE(not sm.GetResults().started);
    REQUIRE(not sm.GetResults().entry);
    REQUIRE(sm.GetResults().cycled);
    REQUIRE(not sm.GetResults().exit);
    REQUIRE(not sm.GetResults().transitioned);
    REQUIRE(not sm.GetResults().stopped);
    REQUIRE(not sm.GetResults().initial_to_running);
    REQUIRE(not sm.GetResults().running_to_done);
    REQUIRE(not sm.IsFinal());
    sm.ResetFlags();
    sm.RunOnce();
    REQUIRE(sm.Is(State::Running));
    REQUIRE(not sm.GetResults().started);
    REQUIRE(not sm.GetResults().entry);
    REQUIRE(sm.GetResults().cycled);
    REQUIRE(not sm.GetResults().exit);
    REQUIRE(not sm.GetResults().transitioned);
    REQUIRE(not sm.GetResults().stopped);
    REQUIRE(not sm.GetResults().initial_to_running);
    REQUIRE(not sm.GetResults().running_to_done);
    REQUIRE(not sm.IsFinal());
    sm.ResetFlags();
    sm.SetEvent(2);    // this should cause a transition to Done
    sm.RunOnce();
    REQUIRE(sm.Is(State::Done));
    REQUIRE(not sm.GetResults().started);
    REQUIRE(sm.GetResults().cycled);
    REQUIRE(sm.GetResults().exit);
    REQUIRE(sm.GetResults().entry);
    REQUIRE(sm.GetResults().transitioned);
    REQUIRE(not sm.GetResults().stopped);
    REQUIRE(not sm.GetResults().initial_to_running);
    REQUIRE(sm.GetResults().running_to_done);
    sm.ResetFlags();
    sm.RunOnce();
    REQUIRE(sm.Is(State::Undefined));
    REQUIRE(not sm.GetResults().started);
    REQUIRE(not sm.GetResults().entry);
    REQUIRE(sm.GetResults().cycled);
    REQUIRE(sm.GetResults().exit);
    REQUIRE(sm.GetResults().stopped);
    REQUIRE(sm.IsFinal());

    REQUIRE(sm.GetStatistics().enter == 1U);
    REQUIRE(sm.GetStatistics().entries == 3U);
    REQUIRE(sm.GetStatistics().cycles == 9U);
    REQUIRE(sm.GetStatistics().exits == 3U);
    REQUIRE(sm.GetStatistics().exit == 1U);
}
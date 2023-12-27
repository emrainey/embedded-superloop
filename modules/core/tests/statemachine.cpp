#include <catch2/catch_test_macros.hpp>
#include "core/StateMachine.hpp"
#include "core/Event.hpp"

enum class State : std::uint32_t {
    Undefined = 0,
    Initial,
    Running,
    Final,
};

class StateMachineFixture : public core::StateMachine<State>, private core::StateMachine<State>::Callback {
public:
    StateMachineFixture()
        : StateMachine<State>{*this, State::Initial, State::Final} {}

    void OnEnter() override { results.started = true; }

    void OnEntry(State state) override {
        results.entry = true;
        if (state == State::Initial) {
            counter = 0U;
        } else if (state == State::Running) {
            event = 0U;
        } else {    // if (state == State::Final) {
        }
    }

    State OnCycle(State state) override {
        results.cycled = true;
        if (state == State::Initial) {
            counter++;
            if (counter == 3U) {
                return State::Running;
            }
        } else if (state == State::Running) {
            if (event) {
                uint32_t value = uint32_t(event);
                if (value == 2) {
                    return State::Final;
                }
            }
        }
        // otherwise stay in the current state
        return state;
    }

    void OnExit(State state) override { results.exit = true; }

    void OnTransition(State from, State to) override {
        if (from == State::Initial and to == State::Running) {
            results.initial_to_running = true;
        } else if (from == State::Running and to == State::Final) {
            results.running_to_final = true;
        }
    }

    void OnExit() override { results.stopped = true; }

    void ResetFlags() {
        results.started = false;
        results.entry = false;
        results.cycled = false;
        results.initial_to_running = false;
        results.running_to_final = false;
        results.exit = false;
        results.stopped = false;
    }

    struct Results {
        bool started{false};
        bool entry{false};
        bool cycled{false};
        bool initial_to_running{false};
        bool running_to_final{false};
        bool exit{false};
        bool stopped{false};
    };

    void SetEvent(uint32_t value) { event = value; }
    uint32_t GetEvent() { return uint32_t(event); }

    Results& GetResults() { return results; }

private:
    Results results;
    core::events::Single<uint32_t> event;
    std::size_t counter{0U};
};

TEST_CASE("StateMachine - Basics") {
    StateMachineFixture sm;
    REQUIRE(sm.Is(State::Undefined));
    REQUIRE(sm.IsFinal());
    sm.Enter();
    sm.RunOnce();
    REQUIRE(sm.GetResults().started);
    REQUIRE(sm.GetResults().entry);
    REQUIRE(sm.GetResults().cycled);
    REQUIRE(sm.GetResults().exit == false);
    REQUIRE(sm.GetResults().stopped == false);
    REQUIRE(sm.GetResults().initial_to_running == false);
    REQUIRE(sm.GetResults().running_to_final == false);
    REQUIRE(sm.Is(State::Initial));
    sm.ResetFlags();
    sm.RunOnce();
    REQUIRE(sm.Is(State::Initial));
    REQUIRE(sm.GetResults().started == false);
    REQUIRE(sm.GetResults().entry == false);
    REQUIRE(sm.GetResults().cycled);
    REQUIRE(sm.GetResults().exit == false);
    REQUIRE(sm.GetResults().stopped == false);
    REQUIRE(sm.GetResults().initial_to_running == false);
    REQUIRE(sm.GetResults().running_to_final == false);
    REQUIRE(sm.Is(State::Initial));
    REQUIRE(not sm.IsFinal());
    sm.ResetFlags();
    sm.RunOnce();
    REQUIRE(sm.GetResults().started == false);
    REQUIRE(sm.GetResults().entry == false);
    REQUIRE(sm.GetResults().cycled);
    REQUIRE(sm.GetResults().exit);
    REQUIRE(sm.GetResults().stopped == false);
    REQUIRE(sm.GetResults().initial_to_running);
    REQUIRE(sm.GetResults().running_to_final == false);
    REQUIRE(sm.Was(State::Initial));
    REQUIRE(sm.Is(State::Undefined));
    REQUIRE(not sm.IsFinal());
    sm.ResetFlags();
    sm.RunOnce();
    REQUIRE(sm.GetResults().started == false);
    REQUIRE(sm.GetResults().entry);
    REQUIRE(sm.GetResults().cycled);
    REQUIRE(sm.GetResults().exit == false);
    REQUIRE(sm.GetResults().stopped == false);
    REQUIRE(sm.GetResults().initial_to_running == false);
    REQUIRE(sm.GetResults().running_to_final == false);
    REQUIRE(sm.Is(State::Running));
    REQUIRE(not sm.IsFinal());
    sm.ResetFlags();
    sm.RunOnce();
    REQUIRE(sm.Is(State::Running));
    REQUIRE(sm.GetResults().started == false);
    REQUIRE(sm.GetResults().entry == false);
    REQUIRE(sm.GetResults().cycled);
    REQUIRE(sm.GetResults().exit == false);
    REQUIRE(sm.GetResults().stopped == false);
    REQUIRE(sm.GetResults().initial_to_running == false);
    REQUIRE(sm.GetResults().running_to_final == false);
    REQUIRE(not sm.IsFinal());
    sm.ResetFlags();
    sm.RunOnce();
    REQUIRE(sm.Is(State::Running));
    REQUIRE(sm.GetResults().started == false);
    REQUIRE(sm.GetResults().entry == false);
    REQUIRE(sm.GetResults().cycled);
    REQUIRE(sm.GetResults().exit == false);
    REQUIRE(sm.GetResults().stopped == false);
    REQUIRE(sm.GetResults().initial_to_running == false);
    REQUIRE(sm.GetResults().running_to_final == false);
    REQUIRE(not sm.IsFinal());
    sm.RunOnce();
    REQUIRE(sm.Is(State::Running));
    REQUIRE(sm.GetResults().started == false);
    REQUIRE(sm.GetResults().entry == false);
    REQUIRE(sm.GetResults().cycled);
    REQUIRE(sm.GetResults().exit == false);
    REQUIRE(sm.GetResults().stopped == false);
    REQUIRE(sm.GetResults().initial_to_running == false);
    REQUIRE(sm.GetResults().running_to_final == false);
    REQUIRE(not sm.IsFinal());
    sm.ResetFlags();
    sm.SetEvent(2);
    sm.RunOnce();
    REQUIRE(sm.Was(State::Running));
    REQUIRE(sm.Is(State::Undefined));
    REQUIRE(sm.GetResults().started == false);
    REQUIRE(sm.GetResults().entry == false);
    REQUIRE(sm.GetResults().cycled);
    REQUIRE(sm.GetResults().exit);
    REQUIRE(sm.GetResults().stopped == false);
    REQUIRE(sm.GetResults().initial_to_running == false);
    REQUIRE(sm.GetResults().running_to_final);
    sm.ResetFlags();
    sm.RunOnce();
    REQUIRE(sm.Was(State::Final));
    REQUIRE(sm.Is(State::Undefined));
    REQUIRE(sm.GetResults().started == false);
    REQUIRE(sm.GetResults().entry);
    REQUIRE(sm.GetResults().cycled);
    REQUIRE(sm.GetResults().exit);
    REQUIRE(sm.GetResults().stopped);
    REQUIRE(sm.IsFinal());
}
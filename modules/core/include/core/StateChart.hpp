#ifndef CORE_STATE_MACHINE_HPP
#define CORE_STATE_MACHINE_HPP

/// @file
/// The StateChart Template

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <utility>
#include "core/EnumType.hpp"

namespace core {
/// A State typically represents a specific configuration of the system. A state can be nested in another state.
///
template <typename EnumType, EnumType ParentState = EnumType::Undefined>
class State {
    // State properties and methods
};

/// @brief Implements a State Chart via a callback interface and a given State Enumeration.
/// The order of callbacks is: Enter() -> OnEnter(), OnEntry(initial_state)
/// Then during the RunOnce: OnGuard(current_state) -> OnCycle(current_state) or -> OnExit(last_state) -> next_state = OnTransition(last_state) ->
/// OnEntry(next_state)
/// @tparam ENUM_TPARAM The state enumeration. It must have an `Undefined` value (which can not be the initial state or the final state)
template <typename ENUM_TPARAM>
class StateChart {
public:
    static_assert(std::is_enum<ENUM_TPARAM>::value, "ENUM_TPARAM must be an enumerated type");
    /// @brief The type of the state machine's enum
    using StateType = ENUM_TPARAM;
    static_assert(to_underlying(StateType::Undefined) == 0U, "ENUM_TPARAM must have a Undefined state and it must be zero");

    /// @brief The callback interface for the StateChart
    class Callback {
    public:
        /// Called when the StateChart is entered
        /// @note This is called only one time per lifecycle.
        virtual void OnEnter() = 0;

        /// Called when the StateChart enters a new state
        /// @param state The new state
        virtual void OnEntry(StateType state) = 0;

        /// Called when the StateChart cycles and does not exit a state
        virtual void OnCycle(StateType state) = 0;

        /// Called to decide if a StateChart will leave a given state.
        /// @return True if the StateChart will leave the state, false otherwise
        virtual bool OnGuard(StateType state) const = 0;

        /// Called when the StateChart is exiting a state
        /// @param state The state that is being exited
        virtual void OnExit(StateType state) = 0;

        /// Called upon the transition out of a state into another
        /// @return The new state to go to. To halt the state chart, return StateType::Final.
        virtual StateType OnTransition(StateType from) = 0;

        /// Called then the StateChart is exitted
        /// @note This is called only one time per lifecycle.
        virtual void OnExit() = 0;

    protected:
        ~Callback() = default;
    };

    /// @brief The parameter constructor
    /// @param callback The reference to the callback interface
    /// @param initial_state The initial state of the StateChart
    /// @param final_state The final state of the StateChart
    StateChart(Callback& callback)
        : callback_{callback}
        , state_{StateType::Undefined} {}

    /// @param state The state to query for
    /// @return True if the machine is in the given state
    bool Is(StateType state) const { return state_ == state; }

    /// @return True if the StateChart is final
    bool IsFinal() const { return stopped_; }

    struct Statistics {
        size_t entered{0U};        ///< The number of times OnEnter() was called
        size_t entries{0U};        ///< The number of times OnEntry() was called
        size_t guards{0U};         ///< The number of times OnGuard() was called
        size_t cycles{0U};         ///< The number of times OnCycle() was called
        size_t exits{0U};          ///< The number of times OnExit() was called
        size_t transitions{0U};    ///< The number of times OnTransition() was called
        size_t exited{0U};         ///< The number of times OnExit() was called
    };

    /// @return The statistics of the StateChart
    Statistics const& GetStatistics() const { return statistics_; }

    /// @brief Enters the StateChart if previously Stopped.
    /// Before a State Machine is Entered, it's State is Undefined
    void Enter() {
        if (stopped_) {
            stopped_ = false;
            state_ = StateType::Undefined;
            callback_.OnEnter();
            statistics_.entered++;
            state_ = callback_.OnTransition(state_);
            statistics_.transitions++;
            if (state_ == StateType::Undefined or state_ == StateType::Final) {
                callback_.OnExit();
                statistics_.exited++;
                stopped_ = true;
            } else {
                callback_.OnEntry(state_);
                statistics_.entries++;
            }
        }
    }

    /// @brief Runs the StateChart for one cycle.
    /// This will process the StateChart if it is not stopped or malformed.
    /// If it is stopped or malformed, it will not process the StateChart.
    void RunOnce() {
        if (not stopped_) {
            bool guard_signaled = callback_.OnGuard(state_);
            statistics_.guards++;
            if (guard_signaled) {
                StateType next = StateType::Undefined;
                StateType last = StateType::Undefined;
                callback_.OnExit(state_);
                statistics_.exits++;
                last = state_;
                state_ = StateType::Undefined;
                next = callback_.OnTransition(last);
                statistics_.transitions++;
                if (next == StateType::Final or next == StateType::Undefined) {
                    callback_.OnExit();
                    statistics_.exited++;
                    stopped_ = true;
                } else {
                    callback_.OnEntry(next);
                    statistics_.entries++;
                    state_ = next;
                }
            } else {
                callback_.OnCycle(state_);
                statistics_.cycles++;
            }
        }
    }

protected:
    Callback& callback_;       ///< The reference to the callback interface
    StateType state_;          ///< The current state of the StateChart
    bool stopped_{true};       ///< We start in the final state
    Statistics statistics_;    ///< The statistics of the StateChart
};

}    // namespace core

#endif    // CORE_STATE_MACHINE_HPP

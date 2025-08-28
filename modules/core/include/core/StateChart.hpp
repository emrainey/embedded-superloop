#ifndef CORE_STATE_MACHINE_HPP
#define CORE_STATE_MACHINE_HPP

/// @file
/// The StateMachine Template

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <utility>
#include "core/EnumType.hpp"

namespace core {

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
    /// @param initial_state The initial state of the StateMachine
    /// @param final_state The final state of the StateMachine
    StateChart(Callback& callback, StateType initial_state)
        : callback_{callback}
        , initial_state_{initial_state}
        , current_state_{StateType::Undefined} {
        if (initial_state == StateType::Undefined or initial_state == StateType::Final) {
            malformed_ = true;
        }
    }

    /// @param state The state to query for
    /// @return True if the machine is in the given state
    bool Is(StateType state) const { return current_state_ == state; }

    /// @return True if the StateMachine is final
    bool IsFinal() const { return stopped_; }

    /// @return True if the StateMachine is malformed
    /// @details A malformed state machine is one that has an initial state that is the same as the final state or
    ///          has an initial state or final state that is Undefined. A malformed state machine will not run and will not enter.
    bool IsMalformed() const { return malformed_; }

    /// @brief Enters the StateMachine if previously Stopped.
    /// Before a State Machine is Entered, it's State is Undefined
    void Enter() {
        if (malformed_) {
            return;
        }
        if (stopped_) {
            stopped_ = false;
            current_state_ = StateType::Undefined;
            callback_.OnEnter();
            current_state_ = initial_state_;
            callback_.OnEntry(initial_state_);
        }
    }

    /// @brief Runs the StateMachine for one cycle.
    /// This will process the StateMachine if it is not stopped or malformed.
    /// If it is stopped or malformed, it will not process the StateMachine.
    void RunOnce() {
        if (malformed_) {
            return;
        }
        if (not stopped_) {
            if (callback_.OnGuard(current_state_)) {
                StateType next = StateType::Undefined;
                StateType last = StateType::Undefined;
                callback_.OnExit(current_state_);
                last = current_state_;
                current_state_ = StateType::Undefined;
                next = callback_.OnTransition(last);
                if (next == StateType::Final or next == StateType::Undefined) {
                    callback_.OnExit();
                    stopped_ = true;
                } else {
                    callback_.OnEntry(next);
                    current_state_ = next;
                }
            } else {
                callback_.OnCycle(current_state_);
            }
        }
    }

protected:
    Callback& callback_;               ///< The reference to the callback interface
    StateType const initial_state_;    ///< The initial state of the StateMachine
    StateType current_state_;          ///< The current state of the StateMachine
    bool stopped_{true};               ///< We start in the final state
    bool malformed_{false};            ///< The flag to indicate if the state machine is malformed
};

}    // namespace core

#endif    // CORE_STATE_MACHINE_HPP

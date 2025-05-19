#ifndef CORE_STATE_MACHINE_HPP
#define CORE_STATE_MACHINE_HPP

/// @file
/// The StateMachine Template

#include <cstdint>
#include <cstddef>
#include <type_traits>
#include <utility>
#include "core/EnumType.hpp"

namespace core {

/// @brief Implements a State Machine via a callback interface and a given State Enumeration.
/// The order of callbacks is: Enter() -> OnEnter(), OnEntry(initial_state)
/// Then during the cycle: OnCycle(current_state) -> OnExit(last_state) -> OnTransition(last_state, next_state) -> OnEntry(next_state)
/// @tparam ENUM_TPARAM The state enumeration. It must have an `Undefined` value (which can not be the initial state or the final state)
template <typename ENUM_TPARAM>
class StateMachine {
public:
    static_assert(std::is_enum<ENUM_TPARAM>::value, "ENUM_TPARAM must be an enumerated type");
    /// @brief The type of the state machine's enum
    using StateType = ENUM_TPARAM;
    static_assert(to_underlying(StateType::Undefined) == 0U, "ENUM_TPARAM must have a Undefined state and it must be zero");

    /// @brief The callback interface for the StateMachine
    class Callback {
    public:
        /// Called when the StateMachine is entered
        /// @note This is called only one time per lifecycle.
        virtual void OnEnter() = 0;
        /// Called when the StateMachine is entered in any given state
        /// @param state The state being entered
        virtual void OnEntry(StateType state) = 0;
        /// Called when the StateMachine is cycled in any given state
        /// @param state The current state of the StateMachine
        /// @return The next state of the StateMachine. Return the given state to stay in the same state.
        /// @retval State::Undefined to stop the StateMachine. This will then call OnExit() and stop the StateMachine.
        virtual StateType OnCycle(StateType state) = 0;
        /// Called when the StateMachine is exiting any given state
        /// @param state The state being exited
        virtual void OnExit(StateType state) = 0;
        /// Called when transitioning between two given states.
        /// @warning The StateMachine is not in *any* state when this is called, i.e. it is in StateType::Undefined.
        /// @param from The old state
        /// @param to The new state
        virtual void OnTransition(StateType from, StateType to) = 0;
        /// Called when the StateMachine is exiting the final state.
        /// @note This is called only one time per lifecycle.
        virtual void OnExit() = 0;

    protected:
        /// Do not allow destruction through the interface
        ~Callback() = default;
    };

    /// @brief The parameter constructor
    /// @param callback The reference to the callback interface
    /// @param initial_state The initial state of the StateMachine
    /// @param final_state The final state of the StateMachine
    StateMachine(Callback& callback, StateType initial_state)
        : callback_{callback}
        , initial_state_{initial_state}
        , current_state_{StateType::Undefined}
        , next_state_{StateType::Undefined}
        , last_state_{StateType::Undefined} {
        if (initial_state == StateType::Undefined) {
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
            current_state_ = initial_state_;
            next_state_ = initial_state_;
            last_state_ = initial_state_;
            // unconditionally call the enter function
            callback_.OnEnter();
            // unconditionally call the state entry function
            callback_.OnEntry(initial_state_);
            should_entry_ = false;
            should_cycle_ = true;
            should_exit_ = false;
        }
    }

    /// @brief Runs the StateMachine for one cycle.
    /// This will process the StateMachine if it is not stopped.
    /// If it is stopped, it will not process the StateMachine.
    void RunOnce() {
        if (malformed_) {
            return;
        }
        if (not stopped_) {
            StateType next_desired_state = StateType::Undefined;
            if (should_cycle_) {
                next_desired_state = callback_.OnCycle(current_state_);
                should_cycle_ = false;
            }
            if (next_desired_state == StateType::Undefined) {
                should_exit_ = true;
                stopped_ = true;
            } else if (next_desired_state != current_state_) {
                // going to another state
                should_exit_ = true;
                next_state_ = next_desired_state;
            }
            if (should_exit_) {
                last_state_ = current_state_;
                // if Is, Was or WillBe is called, they should be correct
                callback_.OnExit(last_state_);
                // now change the state
                current_state_ = StateType::Undefined;
                if (not stopped_) {
                    // now we're not in a state, inform the transition
                    callback_.OnTransition(last_state_, next_state_);
                    should_entry_ = true;
                }
                should_exit_ = false;
            }
            if (should_entry_ and not stopped_) {
                current_state_ = next_state_;
                // if Is, Was or WillBe is called, they should be correct
                callback_.OnEntry(next_state_);
                should_entry_ = false;
            }

            if (stopped_) {
                callback_.OnExit();
                // the state machine is now final
            } else {
                should_cycle_ = true;
            }
        }
    }

protected:
    Callback& callback_;               ///< The reference to the callback interface
    StateType const initial_state_;    ///< The initial state of the StateMachine
    StateType current_state_;          ///< The current state of the StateMachine
    StateType next_state_;             ///< The next state of the StateMachine
    StateType last_state_;             ///< The last state of the StateMachine
    bool stopped_{true};               ///< We start in the final state
    bool should_entry_{false};         ///< The flag to indicate if we are in the entry of the state
    bool should_cycle_{false};         ///< The flag to indicate if we are in the cycle of the state
    bool should_exit_{false};          ///< The flag to indicate if we are in the exit of the state
    bool malformed_{false};            ///< The flag to indicate if the state machine is malformed
};

}    // namespace core

#endif    // CORE_STATE_MACHINE_HPP
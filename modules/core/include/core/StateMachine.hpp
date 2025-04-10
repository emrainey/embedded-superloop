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
/// @tparam ENUM_TPARAM The state enumeration. It must have an `Undefined` value.
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
        /// Called when the StateMachine is entered, only one time.
        virtual void OnEnter() = 0;
        /// Called when the StateMachine is entered in any given state
        /// @param state The state being entered
        virtual void OnEntry(StateType state) = 0;
        /// Called when the StateMachine is cycled in any given state
        /// @param state The current state of the StateMachine
        /// @return The next state of the StateMachine. Return the given state to stay in the same state.
        virtual StateType OnCycle(StateType state) = 0;
        /// Called when the StateMachine is exiting any given state
        /// @param state The state being exited
        virtual void OnExit(StateType state) = 0;
        /// Called when transitioning between two given states.
        /// @warning The StateMachine is not in *any* state when this is called.
        /// @param from The old state
        /// @param to The new state
        virtual void OnTransition(StateType from, StateType to) = 0;
        /// Called when the StateMachine is exiting the final state, only one time.
        virtual void OnExit() = 0;

    protected:
        /// Do not allow destruction through the interface
        ~Callback() = default;
    };

    /// @brief The parameter constructor
    /// @param callback The reference to the callback interface
    /// @param initial_state The initial state of the StateMachine
    /// @param final_state The final state of the StateMachine
    StateMachine(Callback& callback, StateType initial_state, StateType final_state)
        : callback_{callback}
        , initial_state_{initial_state}
        , final_state_{final_state}
        , current_state_{StateType::Undefined}
        , next_state_{StateType::Undefined}
        , last_state_{StateType::Undefined} {}

    /// @param state The state to query for
    /// @return True if the machine is in the given state
    bool Is(StateType state) const { return current_state_ == state; }

    /// @param state The state to query for
    /// @return True if the machine was in the given state preceeding the current state
    bool Was(StateType state) const { return last_state_ == state; }

    /// @param state The state to query for
    /// @return True if the machine will be in the given state in the next cycle
    bool WillBe(StateType state) const { return next_state_ == state; }

    /// @return True if the StateMachine is in the final state
    bool IsFinal() const { return stopped_; }

    /// @brief Enters the StateMachine if previously Stopped.
    /// Before a State Machine is Entered, it's State is Undefined
    void Enter() {
        if (stopped_) {
            current_state_ = initial_state_;
            next_state_ = initial_state_;
            last_state_ = initial_state_;
            cycle_ = false;
            exit_ = false;
            stopped_ = false;
            callback_.OnEnter();
            callback_.OnEntry(initial_state_);
            entry_ = false;
        }
    }

    /// @brief Runs the StateMachine for one cycle.
    /// This will process the StateMachine if it is not stopped.
    /// If it is stopped, it will not process the StateMachine.
    void RunOnce() {
        if (not stopped_) {
            cycle_ = true;
            StateType state = callback_.OnCycle(current_state_);
            if (current_state_ != final_state_) {
                if (state != current_state_) {
                    next_state_ = state;
                    exit_ = true;
                }
            } else {
                // we hit the final state
                exit_ = true;
                stopped_ = true;
            }
            cycle_ = false;
            if (exit_) {
                last_state_ = current_state_;
                callback_.OnExit(last_state_);
                // set this after so that any state checks will be ok in OnExit
                current_state_ = StateType::Undefined;
                // now we're not in a state
                callback_.OnTransition(last_state_, next_state_);
                exit_ = false;
                entry_ = true;
            }
            if (entry_ and not stopped_) {
                current_state_ = next_state_;
                callback_.OnEntry(current_state_);
                entry_ = false;
            }

            if (stopped_) {
                callback_.OnExit();
            }
        }
    }

protected:
    Callback& callback_;         ///< The reference to the callback interface
    StateType initial_state_;    ///< The initial state of the StateMachine
    StateType final_state_;      ///< The final state of the StateMachine
    StateType current_state_;    ///< The current state of the StateMachine
    StateType next_state_;       ///< The next state of the StateMachine
    StateType last_state_;       ///< The last state of the StateMachine
    bool stopped_{true};         ///< We start in the final state
    bool entry_{false};          ///< The flag to indicate if we are in the entry of the state
    bool cycle_{false};          ///< The flag to indicate if we are in the cycle of the state
    bool exit_{false};           ///< The flag to indicate if we are in the exit of the state
};

}    // namespace core

#endif    // CORE_STATE_MACHINE_HPP
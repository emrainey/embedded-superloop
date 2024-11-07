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
    using StateType = ENUM_TPARAM;
    static_assert(to_underlying(StateType::Undefined) == 0U, "ENUM_TPARAM must have a Undefined state and it must be zero");

    /// @brief The callback interface for the StateMachine
    class Callback {
    public:
        virtual void OnEnter() = 0;
        virtual void OnEntry(StateType state) = 0;
        virtual StateType OnCycle(StateType state) = 0;
        virtual void OnExit(StateType state) = 0;
        virtual void OnTransition(StateType from, StateType to) = 0;
        virtual void OnExit() = 0;

    protected:
        ~Callback() = default;
    };

    StateMachine(Callback& callback, StateType initial_state, StateType final_state)
        : callback_{callback}
        , initial_state_{initial_state}
        , final_state_{final_state}
        , current_state_{StateType::Undefined}
        , next_state_{StateType::Undefined}
        , last_state_{StateType::Undefined} {}

    bool Is(StateType state) const { return current_state_ == state; }

    bool Was(StateType state) const { return last_state_ == state; }

    bool WillBe(StateType state) const { return next_state_ == state; }

    bool IsFinal() const { return stopped_; }

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
    Callback& callback_;
    StateType initial_state_;
    StateType final_state_;
    StateType current_state_;
    StateType next_state_;
    StateType last_state_;
    bool stopped_{true};    ///< We start in the final state
    bool entry_{false};
    bool cycle_{false};
    bool exit_{false};
};

}    // namespace core

#endif    // CORE_STATE_MACHINE_HPP
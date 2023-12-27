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

    bool Is(StateType state) { return current_state_ == state; }

    bool Was(StateType state) { return last_state_ == state; }

    bool WillBe(StateType state) { return next_state_ == state; }

    bool IsFinal() const { return stopped_; }

    /// Before a State Machine is Entered, it's State is Undefined
    void Enter() {
        if (stopped_) {
            current_state_ = initial_state_;
            next_state_ = initial_state_;
            last_state_ = initial_state_;
            entry_ = true;
            cycle_ = false;
            exit_ = false;
            stopped_ = false;
            callback_.OnEnter();
        }
    }

    void RunOnce() {
        if (not stopped_) {
            if (entry_) {
                current_state_ = next_state_;
                callback_.OnEntry(next_state_);
                entry_ = false;
            }
            cycle_ = true;
            StateType state = callback_.OnCycle(current_state_);
            if (current_state_ != final_state_) {
                if (state != current_state_) {
                    next_state_ = state;
                    exit_ = true;
                }
            } else {
                exit_ = true;
                stopped_ = true;
            }
            cycle_ = false;
            if (exit_) {
                last_state_ = current_state_;
                callback_.OnExit(last_state_);
                current_state_ = StateType::Undefined;
                callback_.OnTransition(last_state_, next_state_);
                exit_ = false;
                entry_ = true;
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
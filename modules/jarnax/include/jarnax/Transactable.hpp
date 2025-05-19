#ifndef JARNAX_TRANSACTABLE_HPP
#define JARNAX_TRANSACTABLE_HPP

/// @file
/// The Transactable Interface

#include <cstdint>
#include <cstddef>
#include <limits>
#include "core/Status.hpp"
#include "core/Units.hpp"
#include "core/StateMachine.hpp"
#include "jarnax/Timer.hpp"
#include "jarnax/print.hpp"

namespace jarnax {

namespace debug {
/// @brief The boolean flag to control debugging States
#if defined(UNITTEST)
static constexpr bool States = true;
static constexpr bool Inform = true;
#else
static constexpr bool States = false;
static constexpr bool Inform = false;
#endif
}    // namespace debug

/// @brief  The state of the transaction
enum class TransactionState {
    Undefined = 0,        ///< The transaction is in an undefined state (required by StateMachine)
    Uninitialized = 1,    ///< The transaction has not been initialized
    Initialized = 2,      ///< The transaction has been initialized, and is ready to be scheduled.
    Queued = 3,           ///< The transaction has been scheduled but has not yet started.
    Running = 4,          ///< The transaction is currently running but has not yet completed.
    Complete = 5,         ///< The transaction has completed. The result is available from @ref Transactable::GetStatus()
};

/// Item objects which are transacted must inherit from this class. The Transactor will inform the Item about it's different changes in state through
/// input events in @ref Transactable::Inform.
/// @tparam DERIVED_CLASS The class which is derived from this class.
/// @tparam ATTEMPT_LIMIT The number of times the transaction can be tried.
template <typename DERIVED_CLASS, std::size_t ATTEMPT_LIMIT>
class Transactable : protected core::StateMachine<TransactionState>, private core::StateMachine<TransactionState>::Callback {
public:
    /// @brief The type of the Derived Class
    using DerivedType = DERIVED_CLASS;

    /// @brief Parameterized constructor
    /// @param timer The reference to the timer
    Transactable(Timer& timer)
        : StateMachine<TransactionState>{*this, TransactionState::Uninitialized}
        , derived_{*static_cast<DERIVED_CLASS*>(this)}
        , timer_{timer}
        , done_{false}
        , status_{core::Result::NotInitialized, core::Cause::State}
        , try_count_{ATTEMPT_LIMIT} {
        Reset();
    }

    /// @brief The envent enumeration for the transaction
    enum class Event {
        None = 0,            ///< No event has occurred (after an event has been processed it will be set back to None)
        Initialized = 10,    ///< The transaction has been initialized and is ready for scheduling
        Scheduled = 11,      ///< The transaction has been scheduled
        Start = 12,          ///< The transaction has been started
        Retry = 13,          ///< The transaction is being retried
        Completed = 14,      ///< The transaction has completed, must be Recycled or Finalized
        Recycle = 15,        ///< The transaction will be recycled, it will go back to the Uninitialized state
        Discard = 16,        ///< The transaction will be discarded (unusable). It will have to be externally @ref Reset to be used again.
    };

    void Print(core::Printer& printer) const {
        printer(
            "Transactable State: %d:%d:%d, Event: %d, Attempts Remaining: %" PRIz ", Duration: %" PRIu64 " us Deadline: %" PRIu64 " \n",
            static_cast<int>(last_state_),
            static_cast<int>(current_state_),
            static_cast<int>(next_state_),
            static_cast<int>(event_),
            try_count_,
            duration_.value(),
            deadline_.value()
        );
    }

    /// @brief Informs the transaction of an event.
    /// If the event is a completion, the status is set to the completion status will be saved and the RunOnce will be run again to close the machine.
    /// @param event The input event
    /// @param status The status to assign to the completion status if the event is Completed
    void Inform(Event event, core::Status status = core::Status{core::Result::NotAvailable, core::Cause::Parameter}) {
        if constexpr (debug::Inform) {
            jarnax::print("Transactable::Inform: %d (Final? %s)\n", static_cast<int>(event), IsFinal() ? "true" : "false");
        }
        if (not IsFinal()) {
            event_ = event;
            if (event_ == Event::Completed) {
                completion_status_ = status;
            }
            RunOnce();
        }
    }

    /// @return True if the transaction is Uninitialized
    bool IsUninitialized() const { return Is(TransactionState::Uninitialized); }
    /// @return True if the transaction is Initialized
    bool IsInitialized() const { return Is(TransactionState::Initialized); }
    /// @return True if the transaction is Queued
    bool IsQueued() const { return Is(TransactionState::Queued); }
    /// @return True if the transaction is Running
    bool IsRunning() const { return Is(TransactionState::Running); }
    /// @return True if the transaction is Complete
    bool IsComplete() const { return Is(TransactionState::Complete); }
    /// @return True if the transaction can be Reset
    bool IsResetable() const { return StateMachine<TransactionState>::IsFinal(); }

    /// Before the transaction is scheduled, the status is not valid,
    /// After the transaction is scheduled, it should return busy.
    /// After the transaction is complete, it should return the result of the transaction.
    core::Status GetStatus() const { return status_; }

    /// The number of times the transaction has been tried. This is reset to zero when the transaction is initialized.
    std::size_t GetAttemptsRemaining() const { return try_count_; }

    /// The duration of the transaction in microseconds. This is only valid after the transaction has completed
    core::units::MicroSeconds GetDuration() const { return duration_; }

    /// Sets the deadline for the transaction to a non-infinite value.
    void SetDeadline(core::units::MicroSeconds deadline) { deadline_ = deadline; }

    /// Resets the machine back to an Entered state if it was already final
    /// @return True if the machine is final, false otherwise
    bool Reset() {
        if (IsFinal()) {
            Enter();
            return true;
        } else {
            // do nothing
            if constexpr (debug::States) {
                jarnax::print("Reset: Not Final\n");
            }
            return false;
        }
    }

protected:
    void InternalInitialize() {
        status_ = core::Status{core::Result::NotInitialized, core::Cause::State};
        try_count_ = ATTEMPT_LIMIT;
        start_ = core::units::MicroSeconds{0U};
        duration_ = core::units::MicroSeconds{0U};
        deadline_ = core::units::MicroSeconds{std::numeric_limits<core::units::MicroSeconds::StorageType>::max()};
        derived_.Clear();
    }

    /// @copydoc core::StateMachine<TransactionState>::Callback::OnEnter
    void OnEnter() override {
        // do nothing
        if constexpr (debug::States) {
            jarnax::print("Transactable::OnEnter\n");
        }
    }

    /// @copydoc core::StateMachine<TransactionState>::Callback::OnEntry(TransactionState)
    void OnEntry(TransactionState state) override {
        if constexpr (debug::States) {
            jarnax::print("Transactable::OnEntry: %d\n", static_cast<int>(state));
        }
        if (state == TransactionState::Uninitialized) {
            InternalInitialize();
        } else if (state == TransactionState::Initialized) {
            status_ = core::Status{core::Result::NotReady, core::Cause::State};
        } else if (state == TransactionState::Running) {
            try_count_--;
            start_ = timer_.GetMicroseconds();
            status_ = core::Status{core::Result::Busy, core::Cause::State};
        } else if (state == TransactionState::Complete) {
            duration_ = timer_.GetMicroseconds() - start_;
        }
    }

    /// @copydoc core::StateMachine<TransactionState>::Callback::OnCycle(TransactionState)
    TransactionState OnCycle(TransactionState state) override {
        if constexpr (debug::States) {
            jarnax::print("Transactable::OnCycle: %d w/ event=%d\n", static_cast<int>(state), static_cast<int>(event_));
            Print(core::GetPrinter());
        }
        if (state == TransactionState::Uninitialized) {
            // wait for the external event which indicates that the class has been externally initialized too
            if (event_ == Event::Initialized) {
                return TransactionState::Initialized;
            }
        } else if (state == TransactionState::Initialized) {
            if (event_ == Event::Scheduled) {
                return TransactionState::Queued;
            }
        } else if (state == TransactionState::Queued) {
            if (event_ == Event::Start) {
                if (timer_.GetMicroseconds() < deadline_) {
                    return TransactionState::Running;
                } else {
                    status_ = core::Status{core::Result::Timeout, core::Cause::State};
                    return TransactionState::Complete;
                }
            } else if (event_ == Event::Completed) {
                // failed to start
                status_ = completion_status_;
                return TransactionState::Complete;
            }
        } else if (state == TransactionState::Running) {
            if (event_ == Event::Retry) {
                if (try_count_ > 0U) {
                    return TransactionState::Queued;
                } else {
                    status_ = core::Status{core::Result::ExceededLimit, core::Cause::State};
                    return TransactionState::Complete;
                }
            } else if (event_ == Event::Completed) {
                // pass or fail!
                status_ = completion_status_;
                return TransactionState::Complete;
            }
        } else if (state == TransactionState::Complete) {
            if (event_ == Event::Recycle) {
                return TransactionState::Uninitialized;
            } else if (event_ == Event::Discard) {
                return TransactionState::Undefined;    // finalize the state machine
            }
        }
        event_ = Event::None;    // reset the event
        return state;            // otherwise stay in this state
    }

    /// @copydoc core::StateMachine<TransactionState>::Callback::OnExit(TransactionState)
    void OnExit(TransactionState state) override {
        // do nothing
        if constexpr (debug::States) {
            jarnax::print("Transactable::OnExit: %d\n", static_cast<int>(state));
        }
    }

    /// @copydoc core::StateMachine<TransactionState>::Callback::OnTransition(TransactionState, TransactionState)
    void OnTransition(TransactionState from, TransactionState to) override {
        if constexpr (debug::States) {
            jarnax::print("Transactable::OnTransition: %d -> %d\n", static_cast<int>(from), static_cast<int>(to));
        }
    }

    /// @copydoc core::StateMachine<TransactionState>::Callback::OnExit()
    void OnExit() override {
        // do nothing
        if constexpr (debug::States) {
            jarnax::print("Transactable::OnExit\n");
        }
    }

    DerivedType& derived_;                  ///< The reference to the derived class
    Timer& timer_;                          ///< The reference to the timer
    bool done_;                             ///< The flag to indicate if the transaction is done (i.e. has onCycled Completed)
    Event event_;                           ///< The current event
    core::Status status_;                   ///< The current status
    core::Status completion_status_;        ///< The completion status
    std::size_t try_count_;                 ///< The number of attempts remaining
    core::units::MicroSeconds start_;       ///< The start time of the transaction
    core::units::MicroSeconds duration_;    ///< The duration of the transaction
    core::units::MicroSeconds deadline_;    ///< The deadline for the transaction
};

}    // namespace jarnax

#endif    // JARNAX_TRANSACTABLE_HPP
#ifndef JARNAX_TRANSACTABLE_HPP
#define JARNAX_TRANSACTABLE_HPP

#include <cstddef>
#include "core/StateMachine.hpp"
#include "jarnax.hpp"
#include "jarnax/Timer.hpp"

namespace jarnax {

namespace debug {
static constexpr bool States =
#if defined(UNITTEST)
    true;
#else
    false;
#endif
}    // namespace debug

/// @brief  The state of the transaction
enum class TransactionState {
    Undefined,      ///< The transaction has not been initialized (required by StateMachine)
    Initialized,    ///< The transaction has been initialized, and is ready to be scheduled.
    Queued,         ///< The transaction has been scheduled but has not yet started.
    Running,        ///< The transaction is currently running but has not yet completed.
    Complete,       ///< The transaction has completed. The result is available from @ref GetStatus.
};

/// Item objects which are transacted must inherit from this class. The Transactor will inform the Item about it's different changes in state through
/// input events in @ref Inform.
/// @tparam DERIVED_CLASS The class which is derived from this class.
/// @tparam ATTEMPT_LIMIT The number of times the transaction can be tried.
template <typename DERIVED_CLASS, std::size_t ATTEMPT_LIMIT>
class Transactable : protected core::StateMachine<TransactionState>, private core::StateMachine<TransactionState>::Callback {
public:
    using DerivedType = DERIVED_CLASS;

    Transactable(Timer& timer)
        : StateMachine<TransactionState>{*this, TransactionState::Undefined, TransactionState::Complete}
        , derived_{*static_cast<DERIVED_CLASS*>(this)}
        , timer_{timer}
        , status_{core::Result::NotInitialized, core::Cause::State}
        , try_count_{ATTEMPT_LIMIT} {
        Reset();
    }

    enum class Event {
        None,           ///< No event has occurred (after an event has been processed it will be set back to None)
        Initialized,    ///< The transaction has been initialized and is ready for scheduling
        Scheduled,      ///< The transaction has been scheduled
        Start,          ///< The transaction has been started
        Retry,          ///< The transaction is being retried
        Completed,      ///< The transaction has completed
    };

    void Inform(Event event, Status status = Status{core::Result::NotAvailable, core::Cause::Parameter}) {
        event_ = event;
        if (event_ == Event::Completed) {
            completion_status_ = status;
        }
        RunOnce();
        // in the case of the final state of Completed, we need to run the
        // state machine twice to get the final state to stop the machine
        if (event_ == Event::Completed) {
            RunOnce();
        }
    }

    bool IsInitialized() const { return Is(TransactionState::Initialized); }
    bool IsQueued() const { return Is(TransactionState::Queued); }
    bool IsRunning() const { return Is(TransactionState::Running); }
    bool IsComplete() const { return Is(TransactionState::Complete) or IsFinal(); }

    /// Before the transaction is scheduled, the status is not valid,
    /// After the transaction is scheduled, it should return busy.
    /// After the transaction is complete, it should return the result of the transaction.
    Status GetStatus() const { return status_; }

    /// The number of times the transaction has been tried. This is reset to zero when the transaction is initialized.
    std::size_t GetAttemptsRemaining() const { return try_count_; }

    /// The duration of the transaction in microseconds. This is only valid after the transaction has completed
    core::units::MicroSeconds GetDuration() const { return duration_; }

    bool Reset() {
        if (IsFinal()) {
            // moves the state back to Uninitialized
            status_ = Status{core::Result::NotInitialized, core::Cause::State};
            try_count_ = ATTEMPT_LIMIT;
            start_ = core::units::MicroSeconds{0U};
            duration_ = core::units::MicroSeconds{0U};
            derived_.Clear();
            Enter();
            return true;
        } else {
            // do nothing
            if constexpr (debug::States) {
                // std::cout << "Reset: Not Final" << std::endl;
            }
            return false;
        }
    }

protected:
    void OnEnter() override {
        // do nothing
        if constexpr (debug::States) {
            // std::cout << "On Enter" << std::endl;
        }
    }

    void OnExit() override {
        // do nothing
        if constexpr (debug::States) {
            // std::cout << "On Exit" << std::endl;
        }
    }

    void OnEntry(TransactionState state) override {
        if constexpr (debug::States) {
            // std::cout << "Entry State: " << static_cast<int>(state) << std::endl;
        }
        if (state == TransactionState::Initialized) {
            status_ = Status{core::Result::NotReady, core::Cause::State};
        } else if (state == TransactionState::Running) {
            try_count_--;
            start_ = timer_.GetMicroseconds();
            status_ = Status{core::Result::Busy, core::Cause::State};
        } else if (state == TransactionState::Complete) {
            duration_ = timer_.GetMicroseconds() - start_;
        }
    }

    void OnExit(TransactionState) override {
        // do nothing
        if constexpr (debug::States) {
            // std::cout << "On Exit " << static_cast<int>(state) << std::endl;
        }
    }

    TransactionState OnCycle(TransactionState state) override {
        if constexpr (debug::States) {
            // std::cout << "State: " << static_cast<int>(state) << " Event: " << static_cast<int>(event_) << std::endl;
        }
        if (state == TransactionState::Undefined) {
            if (event_ == Event::Initialized) {
                return TransactionState::Initialized;
            }
        } else if (state == TransactionState::Initialized) {
            if (event_ == Event::Scheduled) {
                return TransactionState::Queued;
            }
        } else if (state == TransactionState::Queued) {
            if (event_ == Event::Start) {
                return TransactionState::Running;
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
                    status_ = Status{core::Result::ExceededLimit, core::Cause::State};
                    return TransactionState::Complete;
                }
            } else if (event_ == Event::Completed) {
                // pass or fail!
                status_ = completion_status_;
                return TransactionState::Complete;
            }
        } else if (state == TransactionState::Complete) {
            // do nothing, final state
        }
        event_ = Event::None;    // reset the event
        return state;            // otherwise stay in this state
    }

    void OnTransition(TransactionState /*from*/, TransactionState /*to*/) override {
        // do nothing
    }

    DerivedType& derived_;
    Timer& timer_;
    Event event_;
    Status status_;
    Status completion_status_;
    std::size_t try_count_;
    core::units::MicroSeconds start_;
    core::units::MicroSeconds duration_;
};

}    // namespace jarnax

#endif    // JARNAX_TRANSACTABLE_HPP
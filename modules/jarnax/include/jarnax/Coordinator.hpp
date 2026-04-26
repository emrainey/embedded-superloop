#ifndef JARNAX_COORDINATOR_HPP
#define JARNAX_COORDINATOR_HPP

/// @file
/// Transaction Coordinator for Asynchronous Operations

#include <cstddef>
#include "core/Ring.hpp"
#include "core/StateMachine.hpp"
#include "jarnax/Loopable.hpp"
#include "jarnax/Timer.hpp"
#include "jarnax/Transactable.hpp"
#include "jarnax/Transactor.hpp"
#include "jarnax/print.hpp"

namespace jarnax {

/// @brief A transactor is a class that can schedule a transaction
/// @tparam TRANSACTION_TYPE The transaction type
template <typename TRANSACTION_TYPE, std::size_t DEPTH>
class Coordinator : public Loopable {
public:
    /// The transaction type managed by this coordinator
    using TransactionType = TRANSACTION_TYPE;
    // static_assert(std::is_base_of<Transactable<TransactionType>, TransactionType>::value, "TransactionType must be derived from Transactable");

    /// Constructs a coordinator with a reference to the transaction driver
    /// @param driver The transactor driver that executes transactions
    Coordinator(Transactor<TransactionType>& driver)
        : Loopable()
        , transactions_{}
        , active_{nullptr}
        , stats_{}
        , driver_{driver} {
        // do nothing
    }

    virtual ~Coordinator() {
        // mark all the transactions as cancelled
        active_ = nullptr;
    }

    /// @brief Attempts to schedule a transaction
    /// @param transaction The pointer to the transaction.
    /// @return core::Result::InvalidValue, core::Cause::Parameter if the transaction is nullptr
    /// @return core::Result::NotInitialized, core::Cause::Parameter if the transaction is not initialized
    /// @return core::Result::ExceededLimit, core::Cause::Resource if the transaction ring is full
    /// @return core::Result::Success, core::Cause::State if the transaction was successfully scheduled
    /// @return core::Result::Failure, core::Cause::Parameter if the transaction was not successfully scheduled
    core::Status Schedule(TransactionType* transaction) {
        if (transaction == nullptr) {
            stats_.rejected++;
            return core::Status{core::Result::InvalidValue, core::Cause::Parameter};
        }
        if (not transaction->IsInitialized()) {
            stats_.rejected++;
            return core::Status{core::Result::NotInitialized, core::Cause::Parameter};
        }
        // Prevent duplicate enqueue of the same transaction instance
        if (active_ == transaction) {
            // but the that means the active_ is also somehow just initialized and not queued. this is SERIOUS developer state bug!
            stats_.rejected++;
            return core::Status{core::Result::NotExpected, core::Cause::State};
        }
        for (std::size_t i = 0U; i < transactions_.Count(); ++i) {
            if (transactions_[i] == transaction) {
                stats_.rejected++;
                return core::Status{core::Result::NotExpected, core::Cause::State};
            }
        }
        if (transactions_.IsFull()) {
            stats_.rejected++;
            return core::Status{core::Result::ExceededLimit, core::Cause::Resource};
        }
        auto status = driver_.Verify(*transaction);
        if (status) {
            // we've already verified it's not full
            transactions_.Push(transaction);
            // we've already verified it's not nullptr
            transaction->Inform(TransactionType::Event::Scheduled, core::Status{core::Result::Success, core::Cause::State});
            stats_.accepted++;
            return core::Status{core::Result::Success, core::Cause::State};
        } else {
            stats_.rejected++;
            return status;
        }
    }

    bool Execute() override {
        core::Status status;
        while (active_ == nullptr) {
            if (transactions_.IsEmpty()) {
                // no transactions to process, but we need to keep the loop active
                // so we will be called again later
                return true;
            }
            // get the top transaction
            if (not transactions_.Pop(active_)) {    // [[unlikely]]
                // could not pop for some reason (should only be when it's empty)
                active_ = nullptr;
                // but we need to keep the loop active
                return true;
            }
            // If the active_ is not Queued, then it may have already timed out and internally completed
            if (not active_->IsQueued()) {
                stats_.deadline++;
                active_ = nullptr;
                // pull the next off
                continue;
            }
        }

        // check the state of the active_ transaction
        if (active_->IsQueued()) {
            // ask it to Start, this will internally check to see if the dead line has been passed.
            if (active_->Inform(TransactionType::Event::Start, core::Status{core::Result::Success, core::Cause::State})) {
                if (active_->IsRunning()) {
                    status = driver_.Start(*active_);
                    if (status.IsSuccess()) {
                        stats_.started++;
                    } else {
                        stats_.stalled++;
                        stats_.completed++;
                        active_->Inform(TransactionType::Event::Completed, status);
                    }
                } else {
                    // the transaction is not running, like due to a deadline or retry
                    stats_.deadline++;
                    if (active_->IsComplete()) {
                        stats_.completed++;
                        // internally the transaction will be marked as complete due to timeout
                    } else {    // FAULT
                        if (active_->Inform(TransactionType::Event::Completed, core::Status{core::Result::Timeout, core::Cause::State})) {
                            stats_.completed++;
                        }
                    }
                }
            }
        }
        // check the state of the active transaction
        if (active_->IsRunning()) {
            status = driver_.Check(*active_);
            // jarnax::print("Transaction status", status);
            if (status.IsSuccess()) {
                stats_.completed++;
                stats_.passed++;
                active_->Inform(TransactionType::Event::Completed, status);
            } else if (status.IsBusy()) {
                // Keep the transaction state machine progressing so deadline timeouts can occur.
                active_->Inform(TransactionType::Event::None, core::Status{core::Result::Success, core::Cause::State});
                if (active_->IsComplete()) {
                    stats_.completed++;
                    stats_.failed++;
                    stats_.deadline++;
                    (void)driver_.Cancel(*active_);
                }
            } else {
                // some failure occurred
                if (active_->GetAttemptsRemaining() > 0) {
                    // goes back to the "IsQueued" state
                    active_->Inform(TransactionType::Event::Retry);
                    stats_.retried++;
                } else {
                    stats_.completed++;
                    stats_.failed++;
                    active_->Inform(TransactionType::Event::Completed, status);
                    status = driver_.Cancel(*active_);
                    // ignore the status of the cancel
                }
            }
        }
        // if it's completed, forget the active transaction
        if (active_->IsComplete()) {
            // Hand off ownership to the originator when completion is observed.
            // The originator is responsible for reclaim/recycle once notified.
            (void)active_->NotifyCompletionListener();
            stats_.forgotten++;
            active_ = nullptr;
        }
        return true;
    }

    /// @brief Returns true if the transaction is currently owned by this coordinator
    /// either as the active transaction or queued for processing.
    bool IsOwned(TransactionType const* transaction) const {
        if (transaction == nullptr) {
            return false;
        }
        if (active_ == transaction) {
            return true;
        }
        for (std::size_t i = 0U; i < transactions_.Count(); ++i) {
            if (transactions_[i] == transaction) {
                return true;
            }
        }
        return false;
    }

    /// @brief  The Coordinator Statistics
    struct Statistics {
        std::size_t accepted{0U};     ///< The transaction passed verification and placed into the Ring.
        std::size_t rejected{0U};     ///< The transaction was invalid and was not placed into the Ring.
        std::size_t started{0U};      ///< The transaction was started.
        std::size_t stalled{0U};      ///< The transaction was not started due to failure.
        std::size_t deadline{0U};     ///< The transaction was not started due to deadline passing
        std::size_t completed{0U};    ///< The transaction was completed.
        std::size_t forgotten{0U};    ///< The transaction was forgotten (completed, then removed from Coordinators memory).
        std::size_t retried{0U};      ///< The transaction was retried.
        std::size_t passed{0U};       ///< The transaction was successful.
        std::size_t failed{0U};       ///< The transaction was unsuccessful.
    };
    /// @brief Returns a read-only view of the statistics
    Statistics const& GetCoordinatorStatistics() const { return stats_; }

protected:
    /// @brief The ring of transaction pointer which are the work queue
    core::Ring<TransactionType*, DEPTH> transactions_;
    /// @brief Holds the active transaction
    TransactionType* active_;
    /// @brief The statistics of the transactor
    Statistics stats_;
    /// @brief The implementation which knows how to act on the transactions
    Transactor<TransactionType>& driver_;
};

}    // namespace jarnax

#endif    // JARNAX_COORDINATOR_HPP

#ifndef JARNAX_COORDINATOR_HPP
#define JARNAX_COORDINATOR_HPP

#include <cstddef>
#include "core/Ring.hpp"
#include "core/StateMachine.hpp"
#include "jarnax/Loopable.hpp"
#include "jarnax/Timer.hpp"
#include "jarnax/Transactable.hpp"
#include "jarnax/Transactor.hpp"

namespace jarnax {

/// @brief A transactor is a class that can schedule a transaction
/// @tparam TRANSACTION_TYPE The transaction type
template <typename TRANSACTION_TYPE, std::size_t DEPTH>
class Coordinator : public Loopable {
public:
    using TransactionType = TRANSACTION_TYPE;
    // static_assert(std::is_base_of<Transactable<TransactionType>, TransactionType>::value, "TransactionType must be derived from Transactable");

    Coordinator(Transactor<TransactionType>& driver)
        : Loopable()
        , transactions_{}
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
            return core::Status{core::Result::InvalidValue, core::Cause::Parameter};
        }
        if (not transaction->IsInitialized()) {
            return core::Status{core::Result::NotInitialized, core::Cause::Parameter};
        }
        if (transactions_.IsFull()) {
            return core::Status{core::Result::ExceededLimit, core::Cause::Resource};
        }
        auto status = driver_.Verify(*transaction);
        if (status) {
            // we've already verified it's not full
            transactions_.Push(transaction);
            // we've already verified it's not nullptr
            transaction->Inform(TransactionType::Event::Scheduled);
            stats_.accepted++;
            return core::Status{core::Result::Success, core::Cause::State};
        } else {
            stats_.rejected++;
            return status;
        }
    }

    bool Execute() override {
        core::Status status;
        if (active_ == nullptr) {
            if (transactions_.IsEmpty()) {
                // no transactions to process, but we need to keep the loop active
                // so we will be called again later
                return true;
            }
            // get the top transaction
            if (not transactions_.Pop(active_)) {
                // could not pop for some reason
                active_ = nullptr;
                // but we need to keep the loop active
                return true;
            }
        }

        // check the state of the active_ transaction
        if (active_->IsQueued()) {
            // ask it to Start, this will internally check to see if the dead line has been passed.
            active_->Inform(TransactionType::Event::Start);
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
                // the transaction is not running
                stats_.deadline++;
                stats_.completed++;
                // internally the transaction will be marked as complete
            }
        }
        // check the state of the active transaction
        if (active_->IsRunning()) {
            status = driver_.Check(*active_);
            if (status.IsSuccess()) {
                stats_.completed++;
                stats_.passed++;
                active_->Inform(TransactionType::Event::Completed, status);
            } else if (status.IsBusy()) {
                // do nothing
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
                active_->Inform(TransactionType::Event::Retry);
            }
        }
        // if it's completed, forget the active transaction
        if (active_->IsComplete()) {
            active_ = nullptr;
        }
        return true;
    }

    /// @brief  The Coordinator Statistics
    struct Statistics {
        std::size_t accepted{0U};     ///< The transaction passed verification and placed into the Ring.
        std::size_t rejected{0U};     ///< The transaction was invalid and was not placed into the Ring.
        std::size_t started{0U};      ///< The transaction was started.
        std::size_t stalled{0U};      ///< The transaction was not started due to failure.
        std::size_t deadline{0U};     ///< The transaction was not started due to deadline passing
        std::size_t completed{0U};    ///< The transaction was completed.
        std::size_t retried{0U};      ///< The transaction was retried.
        std::size_t passed{0U};       ///< The transaction was successful.
        std::size_t failed{0U};       ///< The transaction was unsuccessful.
    };
    /// @brief Returns a read-only view of the statistics
    Statistics const& GetStatistics() const { return stats_; }

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
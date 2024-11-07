#ifndef JARNAX_TRANSACTOR_HPP
#define JARNAX_TRANSACTOR_HPP

#include <cstddef>
#include "core/StateMachine.hpp"
#include "jarnax.hpp"
#include "jarnax/Timer.hpp"
#include "jarnax/Transactable.hpp"

namespace jarnax {

/// @brief An object which verifies, initiates, and could cancel transactions.
/// @tparam TRANSACTION_TYPE
template <typename TRANSACTION_TYPE>
class Transactor {
public:
    using TransactionType = TRANSACTION_TYPE; ///< Should be the Derived Type of the Transactable

    /// @brief Verifies the transaction for correctness before @ref Start is called on it.
    /// @param transaction The pointer to the transaction
    /// @return
    virtual Status Verify(TransactionType& transaction) = 0;

    /// @brief Starts the transaction
    /// @param transaction The pointer to the transaction
    /// @return
    virtual Status Start(TransactionType& transaction) = 0;

    /// @brief Checks the status of the transaction
    /// @param transaction The pointer to the transaction
    /// @return Result::Success if the transaction is complete, Result::Busy if the transaction is still running
    virtual Status Check(TransactionType& transaction) = 0;

    /// @brief Cancels the transaction
    /// @param transaction The pointer to the transaction
    /// @return
    virtual Status Cancel(TransactionType& transaction) = 0;
protected:
    ~Transactor() = default;
};

}    // namespace jarnax

#endif    // JARNAX_TRANSACTOR_HPP
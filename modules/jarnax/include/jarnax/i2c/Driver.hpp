#ifndef JARNAX_I2C_DRIVER_HPP
#define JARNAX_I2C_DRIVER_HPP

/// @file
/// Abstract I²C Driver Interface

#include <cstdint>
#include "compiler.hpp"
#include "core/Buffer.hpp"
#include "jarnax/Coordinator.hpp"
#include "jarnax/Transactable.hpp"

namespace jarnax {

namespace i2c {

/// @brief The default number of retries
static constexpr std::size_t DefaultRetries{3U};

/// @brief The number of transactions that can be queued
static constexpr std::size_t DefaultQueueDepth{8U};

/// @brief The Default data unit size of the I2C Driver
using DataUnit = uint8_t;

/// @brief The I2C Address structure
union Address {
    /// Default Constructor
    constexpr Address()
        : whole{0U} {}
    /// Small address format constructor
    constexpr Address(std::uint8_t addr)
        : whole{addr} {
        small.read = 0U;                // Default to write
        small.address = addr & 0x7F;    // Mask to 7 bits
        small.is_large = 0U;            // Default to small address
    }
    /// Large address format constructor
    constexpr Address(std::uint16_t addr)
        : whole{addr} {
        large.read = 0U;                 // Default to write
        large.address = addr & 0x3FF;    // Mask to 10 bits
        large.is_large = 1U;             // Default to large address
    }
    /// Small address format
    struct small {
        std::uint8_t read     : 1;    ///< Indicates if the transaction is a read (1) or write (0)
        std::uint8_t address  : 7;    ///< The 7-bit I2C address of the device to communicate with
        std::uint8_t          : 7;    ///< Reserved and unused
        std::uint8_t is_large : 1;    ///< Indicates if the address is large (1) or small (0)
    } small;                          ///< 7-bit I2C address format
    /// Large address format
    struct large {
        std::uint16_t read     : 1;     ///< Indicates if the transaction is a read (1) or write (0)
        std::uint16_t address  : 10;    ///< The 10-bit I2C address of the device to communicate with
        std::uint16_t          : 4;     ///< Reserved and unused
        std::uint16_t is_large : 1;     ///< Indicates if the address is large (1) or small (0)
    } large;                            ///< 10-bit I2C address format
    std::uint8_t parts[2];              ///< The address as an array of 2 bytes
    std::uint16_t whole;                ///< The whole address as an 8-bit value
};

/// @brief Defines a CRTP Transactable object for I2C transactions
class Transaction : public jarnax::Transactable<Transaction, DefaultRetries> {
public:
    /// Constructs an I2C transaction with a timer reference
    /// @param timer Timer for tracking transaction timeouts and durations
    Transaction(jarnax::Timer const& timer)
        : jarnax::Transactable<Transaction, DefaultRetries>{timer}
        , address{}
        , buffer{}
        , desired_count{0U}
        , actual_count{0U} {}

    /// The I2C Address of the device to communicate with
    Address address;
    /// Use Move Sematics on the Buffer to shift ownership/access to the transacton so that the Driver can use it
    /// The format of the data buffer and the expected send + response size must total the buffer size.
    core::Buffer<DataUnit> buffer;
    /// The desired number of bytes to send or receive (not including the address byte)
    std::size_t desired_count;
    /// The number of bytes that have actually been sent or received (not including the address byte).
    std::size_t actual_count;

    /// @brief Indicates if the transaction is empty
    /// @return True if the transaction buffer is empty
    bool IsEmpty() const { return buffer.IsEmpty(); }

    /// @brief Moves the buffer into the transaction
    /// @param buf The buffer to move into the transaction
    void Assign(core::Buffer<DataUnit>&& buf) { buffer = std::move(buf); }

    /// @brief Removes the buffer from the transaction and returns it to the caller
    /// @return A container of the buffer
    /// @post Release must be called to release the transaction buffer
    core::Buffer<DataUnit> Relinquish(void) { return std::move(buffer); }

    /// @return True if the transaction seems valid, false otherwise
    bool IsValid() const {
        if (address.whole == 0U) {
            return false;    // address must be set
        }
        if (buffer.IsEmpty()) {
            return false;    // buffer must not be empty
        }
        if (desired_count == 0U) {
            return false;    // desired count must be set
        }
        if (actual_count > desired_count) {
            return false;    // actual count must not exceed desired count
        }
        return true;         // all checks passed, transaction seems valid
    }

    /// Clears the transaction state to defaults
    void Clear() {
        address.whole = 0U;
        buffer.Release();    // if the memory has not been moved, this will free it
        desired_count = 0U;
        actual_count = 0U;
    }
};

/// Type alias for I2C transaction handler
using Transactor = jarnax::Transactor<i2c::Transaction>;
/// Type alias for I2C transaction queue coordinator
using Coordinator = jarnax::Coordinator<i2c::Transaction, DefaultQueueDepth>;

/// The I2C Driver Interface has a Transactor of I2C Transactions and is a Coordinator of the I2C Transactions
class Driver : public Coordinator, public UnCopyMoveable {
public:
    Driver() = delete;

    /// @brief Constructs a new I2C Driver
    /// @param tr The Transactor to use for I2C transactions
    explicit Driver(jarnax::i2c::Transactor& tr);

protected:
    ~Driver() = default;
};
}    // namespace i2c
}    // namespace jarnax
#endif    // JARNAX_I2C_DRIVER_HPP

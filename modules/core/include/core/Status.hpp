#ifndef CORE_STATUS_HPP_
#define CORE_STATUS_HPP_

#include <cstdint>

/// @file
/// core::Status Interface

namespace core {
/// The enumeration of Results in the system
enum class Result : std::int8_t {
    Success = 0,            ///< Correct, all is as expected
    Failure = 1,            ///< Unknown or generic failure
    Busy = 2,               ///< An operation is ongoing
    InvalidValue = 3,       ///< Not a correct value, not in a set of values
    OutOfRange = 4,         ///< Not in the correct range
    NotReady = 5,           ///< The cause was not ready at this time,
    NotEnough = 6,          ///< Not enough of something
    NotSupported = 7,       ///< Not supported
    NotExpected = 8,        ///< Not expected
    NotInitialized = 9,     ///< Not initialized
    NotAvailable = 10,      ///< Not available
    Timeout = 11,           ///< A timeout occurred
    ExceededLimit = 12,     ///< A counted limit has been exceeded (not a timeout)
    NotImplemented = 13,    ///< The feature is not implemented
};

/// The enumeration of Causes in the system
enum class Cause : std::uint8_t {
    Unknown = 0U,          ///< Unstated cause, usually paired with Success
    Parameter = 1U,        ///< A parameter was the cause
    Resource = 2U,         ///< Such as a software construct
    Peripheral = 3U,       ///< Such as a peripheral
    Configuration = 4U,    ///< Such as the system configuration
    Hardware = 5U,         ///< External Hardware (i2C Chips, SPI chips)
    State = 6U,            ///< Some Finite State Machine or StateChart or process
};

/// Locations are captured as addresses but are masked to be sub-ranges of the Flash Address Space
using Location = std::uintptr_t;

/// The Status object contains results and causes for any return value.
class Status final {
public:
    /// Default Construct
    Status();

    /// Parameterized Contructor
    Status(Result result, Cause cause);

    /// Returns true when the result was success. Does not consider cause.
    bool IsSuccess(void) const;

    /// Returns true when the result was failure (anything other than success)
    bool IsBusy(void) const;

    /// Returns true if the result is Success and any cause if present.
    explicit operator bool(void) const;

    /// Equality operator
    /// @param rhs The other Status to compare to
    /// @return true if all fields are equal
    bool operator==(const Status& rhs) const;

    /// Inequality operator
    bool operator!=(const Status& rhs) const;

    /// @brief Returns the location of the Status
    Location GetLocation(void) const;

    /// @brief Returns the Result
    Result GetResult(void) const;

    /// @brief Returns the Cause
    Cause GetCause(void) const;

protected:
    Result result_{Result::Success};    ///< The result of the operation
    Cause cause_{Cause::Unknown};       ///< The cause of the result (if any)
    Location location_{0};              ///< The location of the result
};

}    // namespace core

#endif    // CORE_STATUS_HPP_
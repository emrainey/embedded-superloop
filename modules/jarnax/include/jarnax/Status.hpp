#ifndef SYSTEM_STATUS_HPP_
#define SYSTEM_STATUS_HPP_

#include <cstdint>

/// @file
/// jarnax::Status Interface

namespace jarnax {
/// The enumeration of Results in the system
enum class Result : std::int8_t {
    Success = 0,           ///< Correct, all is as expected
    Failure = 1,           ///< Unknown or generic failure
    Busy = 2,              ///< An operation is ongoing
    InvalidValue = 3,      ///< Not a correct value, not in a set of values
    OutOfRange = 4,        ///< Not in the correct range
    NotReady = 5,          ///< The cause was not ready at this time,
    NotEnough = 6,         ///< Not enough of something
    NotSupported = 7,      ///< Not supported
    NotExpected = 8,       ///< Not expected
    NotInitialized = 9,    ///< Not initialized
    NotAvailable = 10,     ///< Not available
};

/// The enumeration of Causes in the system
enum class Cause : std::uint8_t {
    Unknown = 0U,          ///< Unstated cause, usually paired with Success
    Parameter = 1U,        ///<
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
    Status() = default;

    /// Parameterized Contructor
    Status(Result result, Cause cause);

    /// Returns true when the result was success. Does not consider cause.
    inline bool IsSuccess(void) const { return (m_result_ == Result::Success); }

    /// Returns true when the result was failure (anything other than success)
    inline bool IsBusy(void) const { return (m_result_ == Result::Busy); }

    /// Returns true if the result is Success and any cause if present.
    inline explicit operator bool(void) const { return IsSuccess(); }

    /// Equality operator
    /// @param rhs The other Status to compare to
    /// @return true if all fields are equal
    inline bool operator==(const Status& rhs) const {
        return (m_result_ == rhs.m_result_) and (m_cause_ == rhs.m_cause_) and (m_location_ == rhs.m_location_);
    }

    /// Inequality operator
    inline bool operator!=(const Status& rhs) const { return not(*this == rhs); }

    /// @brief Returns the location of the Status
    inline Location GetLocation(void) const { return m_location_; }

protected:
#if defined(__arm__)
    Result m_result_     : 4 {Result::Success};
    Cause m_cause_       : 4 {Cause::Unknown};
    Location m_location_ : 24 {0};
#else
    Result m_result_{Result::Success};
    Cause m_cause_{Cause::Unknown};
    Location m_location_{0};
#endif
};

#if defined(__arm__)
static_assert(sizeof(Status) == sizeof(std::uint32_t), "Must be this size");
#endif

}    // namespace jarnax

#endif    // SYSTEM_STATUS_HPP_
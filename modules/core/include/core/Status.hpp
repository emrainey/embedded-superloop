#ifndef CORE_STATUS_HPP_
#define CORE_STATUS_HPP_

/// @file
/// core::Status Interface

#include <cstddef>
#include <cstdint>

#include "core/Ring.hpp"

/// The core namespace for fundamental system constructs
namespace core {
/// The enumeration of Results in the system
/// @note Be sure to add a field to the Statistics struct in core::Status for each new Result
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
    NotConfigured = 14,     ///< The feature is not configured
    // Add new results above this line
    _max = 16U,
};

/// @return The name of the Result as a string
constexpr char const* GetResultName(Result r) {
#define CASE_STR(x) \
    case x:         \
        return #x
    switch (r) {
        CASE_STR(Result::Success);
        CASE_STR(Result::Failure);
        CASE_STR(Result::Busy);
        CASE_STR(Result::InvalidValue);
        CASE_STR(Result::OutOfRange);
        CASE_STR(Result::NotReady);
        CASE_STR(Result::NotEnough);
        CASE_STR(Result::NotSupported);
        CASE_STR(Result::NotExpected);
        CASE_STR(Result::NotInitialized);
        CASE_STR(Result::NotAvailable);
        CASE_STR(Result::Timeout);
        CASE_STR(Result::ExceededLimit);
        CASE_STR(Result::NotImplemented);
        CASE_STR(Result::NotConfigured);
        default:
            return "<?>";
    }
#undef CASE_STR
}

/// The enumeration of Causes in the system
/// @note Be sure to add a field to the Statistics struct in core::Status for each new Cause
enum class Cause : std::uint8_t {
    Unknown = 0U,          ///< Unstated cause, usually paired with Success
    Parameter = 1U,        ///< A parameter was the cause
    Resource = 2U,         ///< Such as a software construct
    Peripheral = 3U,       ///< Such as a peripheral
    Configuration = 4U,    ///< Such as the system configuration
    Hardware = 5U,         ///< External Hardware (i2C Chips, SPI chips)
    State = 6U,            ///< Some Finite State Machine or StateChart or process
    /// Add new causes above this line
    _max = 8U,
};

/// @return The name of the Cause as a string
constexpr char const* GetCauseName(Cause c) {
#define CASE_STR(x) \
    case x:         \
        return #x
    switch (c) {
        CASE_STR(Cause::Unknown);
        CASE_STR(Cause::Parameter);
        CASE_STR(Cause::Resource);
        CASE_STR(Cause::Peripheral);
        CASE_STR(Cause::Configuration);
        CASE_STR(Cause::Hardware);
        CASE_STR(Cause::State);
        default:
            return "<?>";
    }
#undef CASE_STR
}

/// Locations are captured as addresses but are masked to be sub-ranges of the Flash Address Space
using Location = std::uintptr_t;

/// The Status object contains results and causes for any return value.
class Status final {
public:
    // === Constexpr static members ===
    constexpr static size_t LogCount = 128U;    ///< The number of items of the log buffer
    /// The type of the log buffer
    using Log = Ring<Status, LogCount>;

    /// Default Construct
    Status();

    /// Parameterized Contructor
    Status(Result result, Cause cause);

    /// @return true when the result was success. Does not consider cause.
    bool IsSuccess(void) const;

    /// @return true when the result was busy specifically.
    bool IsBusy(void) const;

    /// @return true when the Status is not Success and not Busy.
    bool IsFailure(void) const;

    /// Returns true if the result is Success and any cause if present.
    explicit operator bool(void) const;

    /// Equality operator
    /// @param rhs The other Status to compare to
    /// @return true if all fields are equal
    bool operator==(const Status& rhs) const;

    /// Inequality operator
    bool operator!=(const Status& rhs) const;

    /// @brief Equality operator for Result
    /// @param rhs The other Result to compare to
    /// @return true if the Result is equal
    bool operator==(Result rhs) const;

    /// @brief Inequality operator for Result
    /// @param rhs The other Result to compare to
    /// @return true if the Result is not equal
    bool operator!=(Result rhs) const;

    /// @brief Equality operator for Cause
    /// @param rhs The other Cause to compare to
    /// @return true if the Cause is equal
    bool operator==(Cause rhs) const;

    /// @brief Inequality operator for Cause
    /// @param rhs The other Cause to compare to
    /// @return true if the Cause is not equal
    bool operator!=(Cause rhs) const;

    /// @brief Returns the location of the Status
    Location GetLocation(void) const;

    /// @brief Returns the Result
    Result GetResult(void) const;

    /// @brief Returns the Cause
    Cause GetCause(void) const;

    /// @brief Statistics about Status objects.
    /// Tracks the total status objects created and the counts for each Result and Cause.
    struct Statistics {
        size_t total{0U};    ///< The total number of Status objects created
        /// The union of the Result counts and the raw array
        union ResultCounts {
            struct {    // anonymous struct for each Result field
                size_t success{0U};
                size_t failure{0U};
                size_t busy{0U};
                size_t invalid_value{0U};
                size_t out_of_range{0U};
                size_t not_ready{0U};
                size_t not_enough{0U};
                size_t not_supported{0U};
                size_t not_expected{0U};
                size_t not_initialized{0U};
                size_t not_available{0U};
                size_t timeout{0U};
                size_t exceeded_limit{0U};
                size_t not_implemented{0U};
                size_t not_configured{0U};
            } fields;
            size_t array[static_cast<size_t>(Result::_max)]{0U};
        } result_counts;
        /// The union of the Cause counts and the raw array
        union CauseCounts {
            struct {    // anonymous struct for each Cause field
                size_t unknown{0U};
                size_t parameter{0U};
                size_t resource{0U};
                size_t peripheral{0U};
                size_t configuration{0U};
                size_t hardware{0U};
                size_t state{0U};
            } fields;
            size_t array[static_cast<size_t>(Cause::_max)]{0U};
        } cause_counts;
    };

    /// @return The statistics for Status objects
    static inline Statistics const& GetStatistics(void) { return statistics_; }

    /// @return The log of recent Status objects, mutable so that items can be popped off.
    static inline Log& GetLog(void) { return log_; }

protected:
    // === Static Members ===
    static Statistics statistics_;    ///< The statistics for Status objects (shared between all objects)
    static Log log_;                  ///< The log of recent Status objects
    // === Instance Members ===
    Result result_{Result::Success};    ///< The result of the operation
    Cause cause_{Cause::Unknown};       ///< The cause of the result (if any)
    Location location_{0};              ///< The location of the result
};

}    // namespace core

#endif    // CORE_STATUS_HPP_

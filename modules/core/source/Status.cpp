#include "core/Status.hpp"
#include "core/Split.hpp"

namespace core {

Status::Status()
    : Status(Result::Success, Cause::Unknown) {
}

Status::Status(Result result, Cause cause)
    : m_result_{result}
    , m_cause_{cause}
    , m_location_{0} {
    core::Split<std::uintptr_t, 24> split;
    split.whole = reinterpret_cast<std::uintptr_t>(__builtin_extract_return_addr(__builtin_return_address(0)));
    m_location_ = split.parts.lower;
}

/// Returns true when the result was success. Does not consider cause.
bool Status::IsSuccess(void) const {
    return (m_result_ == Result::Success);
}

/// Returns true when the result was failure (anything other than success)
bool Status::IsBusy(void) const {
    return (m_result_ == Result::Busy);
}

/// Returns true if the result is Success and any cause if present.
Status::operator bool(void) const {
    return IsSuccess();
}

/// Equality operator
/// @param rhs The other Status to compare to
/// @return true if all fields are equal
bool Status::operator==(const Status& rhs) const {
    return (m_result_ == rhs.m_result_) and (m_cause_ == rhs.m_cause_) and (m_location_ == rhs.m_location_);
}

/// Inequality operator
bool Status::operator!=(const Status& rhs) const {
    return not(*this == rhs);
}

/// @brief Returns the location of the Status
Location Status::GetLocation(void) const {
    return m_location_;
}

}    // namespace core
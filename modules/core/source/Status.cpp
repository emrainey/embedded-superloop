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
    m_location_ = reinterpret_cast<std::uintptr_t>(__builtin_extract_return_addr(__builtin_return_address(0)));
}

bool Status::IsSuccess(void) const {
    return (m_result_ == Result::Success);
}

bool Status::IsBusy(void) const {
    return (m_result_ == Result::Busy);
}

Status::operator bool(void) const {
    return IsSuccess();
}

bool Status::operator==(const Status& rhs) const {
    return (m_result_ == rhs.m_result_) and (m_cause_ == rhs.m_cause_) and (m_location_ == rhs.m_location_);
}

bool Status::operator!=(const Status& rhs) const {
    return not(*this == rhs);
}

Location Status::GetLocation(void) const {
    return m_location_;
}

Result Status::GetResult(void) const {
    return m_result_;
}

Cause Status::GetCause(void) const {
    return m_cause_;
}

}    // namespace core
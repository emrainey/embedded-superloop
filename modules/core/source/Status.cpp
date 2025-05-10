#include "core/Status.hpp"
#include "core/Split.hpp"

namespace core {

Status::Status()
    : Status(Result::Success, Cause::Unknown) {
}

Status::Status(Result result, Cause cause)
    : result_{result}
    , cause_{cause}
    , location_{0} {
    location_ = reinterpret_cast<std::uintptr_t>(__builtin_extract_return_addr(__builtin_return_address(0)));
}

bool Status::IsSuccess(void) const {
    return (result_ == Result::Success);
}

bool Status::IsBusy(void) const {
    return (result_ == Result::Busy);
}

Status::operator bool(void) const {
    return IsSuccess();
}

bool Status::operator==(const Status& rhs) const {
    return (result_ == rhs.result_) and (cause_ == rhs.cause_);
}

bool Status::operator!=(const Status& rhs) const {
    return not(*this == rhs);
}

Location Status::GetLocation(void) const {
    return location_;
}

Result Status::GetResult(void) const {
    return result_;
}

Cause Status::GetCause(void) const {
    return cause_;
}

}    // namespace core
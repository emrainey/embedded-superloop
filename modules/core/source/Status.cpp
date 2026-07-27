#include "core/Status.hpp"
#include "core/Split.hpp"

namespace core {

// === Static Storage ===
Status::Statistics Status::statistics_ = {};
Status::Log Status::log_ = {};

Status::Status()
    : Status(Result::Success, Cause::Unknown) {}

Status::Status(Result result, Cause cause)
    : result_{result}
    , cause_{cause}
    , location_{0} {
    location_ = reinterpret_cast<std::uintptr_t>(__builtin_extract_return_addr(__builtin_return_address(0)));
    // Update statistics
    statistics_.total++;
    statistics_.result_counts.array[static_cast<size_t>(result_)]++;
    statistics_.cause_counts.array[static_cast<size_t>(cause_)]++;
    // Filter items which will do into the Log, Success will never be logged and "busy" should not be either as it would overwhelm the log.
    if (result_ != Result::Success and result_ != Result::Busy) {
        log_.Push(*this);    // will call the Copy Assign or Copy Constructor
    }
}

bool Status::Is(Result result, Cause cause) const {
    return (result_ == result) and (cause_ == cause);
}

bool Status::IsSuccess(void) const {
    return (result_ == Result::Success);
}

bool Status::IsBusy(void) const {
    return (result_ == Result::Busy);
}

bool Status::IsFailure(void) const {
    return not(IsSuccess() or IsBusy());
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

bool Status::operator==(Result rhs) const {
    return (result_ == rhs);
}

bool Status::operator!=(Result rhs) const {
    return not(*this == rhs);
}

bool Status::operator==(Cause rhs) const {
    return (cause_ == rhs);
}

bool Status::operator!=(Cause rhs) const {
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

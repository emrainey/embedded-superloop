#include "jarnax/Status.hpp"
#include "core/Split.hpp"

namespace jarnax {

Status::Status(Result result, Cause cause) : m_result_{result}, m_cause_{cause}, m_location_{0} {
    core::Split<std::uintptr_t, 24> split;
    split.whole = reinterpret_cast<std::uintptr_t>(__builtin_extract_return_addr(__builtin_return_address(0)));
    m_location_ = split.parts.lower;
}

}    // namespace jarnax
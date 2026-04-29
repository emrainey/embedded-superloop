#include "core/BoundsChecker.hpp"

namespace core {

BoundsChecker::BoundsChecker(core::Interval const intervals[], uint32_t count)
    : memory_regions_{intervals, count} {}

bool BoundsChecker::IsValidAddress(std::uintptr_t address) {
    return core::Contains(memory_regions_.data(), memory_regions_.count(), address);
}

}    // namespace core

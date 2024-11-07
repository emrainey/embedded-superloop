#include "cortex/mcu.hpp"

namespace cortex {

bool IsValidAddress(std::uintptr_t address) {
    return core::Contains(sorted_memory_regions, address);
}

}    // namespace cortex
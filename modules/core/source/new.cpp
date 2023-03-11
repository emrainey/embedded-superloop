#include "core/core.hpp"

void *operator new(std::size_t bytes, void *pointer) {
    (void)bytes;
    // @todo check for valid ranges
    return pointer;
}

void *operator new(std::size_t bytes, uintptr_t address) {
    (void)bytes;
    // @todo check for valid ranges
    return reinterpret_cast<void *>(address);
}

namespace core {

/// @todo add core library implementations

}    // namespace core
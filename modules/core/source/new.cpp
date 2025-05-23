#include "core/std.hpp"

void *operator new(std::size_t bytes, void *pointer) noexcept {
    (void)bytes;
    // @todo check for valid ranges
    return pointer;
}

void *operator new(std::size_t bytes, uintptr_t address) noexcept {
    (void)bytes;
    // @todo check for valid ranges
    return reinterpret_cast<void *>(address);
}

void operator delete(void *) noexcept {
    // do nothing
}

void operator delete(void *, unsigned int) noexcept {
    // do nothing
}

namespace core {

/// @todo add core library implementations

}    // namespace core
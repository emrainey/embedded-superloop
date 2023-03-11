#include "memory.hpp"

namespace memory {

void copy(void *_dst, void *const _src, std::size_t bytes) {
    std::uint8_t *dst = reinterpret_cast<uint8_t *>(_dst);
    std::uint8_t const *src = reinterpret_cast<uint8_t const *>(_src);
    memory::copy(dst, src, bytes);
}

}    // namespace memory
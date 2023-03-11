#include "memory.hpp"

namespace memory {

void fill(void *_dst, std::uint8_t value, std::size_t bytes) {
    std::uint8_t *dst = reinterpret_cast<uint8_t *>(_dst);
    memory::fill(dst, value, bytes);
}

}    // namespace memory
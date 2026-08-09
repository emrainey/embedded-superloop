#include "memory.hpp"

namespace memory {

void move(void *_dst, void const *_src, std::size_t bytes) {
    std::uint8_t *dst = static_cast<uint8_t *>(_dst);
    std::uint8_t const *src = static_cast<uint8_t const *>(_src);
    memory::move(dst, src, bytes);
}

}    // namespace memory

extern void *memmove(void *_dst, void const *_src, std::size_t bytes) {
    memory::move(_dst, _src, bytes);
    return _dst;
}
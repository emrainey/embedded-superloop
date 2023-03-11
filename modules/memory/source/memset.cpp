#include "memory.hpp"

extern "C" void *memset(void *_dst, int value, std::size_t bytes) {
    std::uint8_t *dst = reinterpret_cast<uint8_t *>(_dst);
    std::uint8_t v = std::uint8_t(value & 0xFF);    // can't use narrowing here
    memory::fill(dst, v, bytes);
    return _dst;
}
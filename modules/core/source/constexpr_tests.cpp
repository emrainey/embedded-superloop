#include <core/Ring.hpp>

namespace {

core::Ring<uint8_t, 3> dummy;
static_assert(dummy.Capacity() == 3U, "Must be this exact size");
}    // namespace
#include "O1HeapPool.hpp"

namespace nucleo {
namespace cyphal {

namespace {
alignas(O1HEAP_ALIGNMENT) static std::uint8_t arena[O1HeapPool::ArenaSize];
}

O1HeapInstance& O1HeapPool::Instance() {
    static O1HeapInstance* const instance = o1heapInit(arena, sizeof(arena));
    return *instance;
}

}    // namespace cyphal
}    // namespace nucleo

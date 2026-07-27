#ifndef APP_O1HEAP_POOL_HPP
#define APP_O1HEAP_POOL_HPP

#include <cstddef>
#include <cstdint>

extern "C" {
#include "o1heap.h"
}

namespace nucleo {
namespace cyphal {

class O1HeapPool {
public:
    static O1HeapInstance& Instance();

    static constexpr std::size_t ArenaSize = 65536U;

private:
    O1HeapPool() = delete;
};

}    // namespace cyphal
}    // namespace nucleo

#endif    // APP_O1HEAP_POOL_HPP

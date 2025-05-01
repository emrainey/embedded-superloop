#include "jarnax/system.hpp"

namespace jarnax {
void jump(void* stack, function func) {
    thumb::jump(stack, func);
}
}    // namespace jarnax
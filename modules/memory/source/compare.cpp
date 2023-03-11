#include "memory.hpp"

namespace memory {

int compare(void const *lhs, void const *rhs, std::size_t count) {
    uint8_t const *tmp_lhs = reinterpret_cast<uint8_t const *>(lhs);
    uint8_t const *tmp_rhs = reinterpret_cast<uint8_t const *>(rhs);
    for (std::size_t i = 0; i < count; ++i) {
        if (tmp_lhs[i] < tmp_rhs[i]) {
            return -1;
        } else if (tmp_lhs[i] > tmp_rhs[i]) {
            return 1;
        }
    }
    return 0;
}

}    // namespace memory
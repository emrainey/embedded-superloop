#include "jarnax/system.hpp"

namespace stm32 {
/// The hidden Backup Ram Context
ATTRIBUTE((used, section(".bkpsram"))) std::uint32_t backup_sram[1024U]{};

uint32_t get_value(std::uint32_t index) {
    return backup_sram[index & 0x3FF];
}

void set_value(std::uint32_t index, std::uint32_t value) {
    backup_sram[index & 0x3FF] = value;
}

}    // namespace stm32
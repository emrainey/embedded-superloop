#include "stm32/stm32f407ve.hpp"

namespace stm32 {
/// The hidden Backup Ram Context
LINKER_SECTION(".bkpsram") std::uint32_t backup_sram[stm32::sizes::backup_sram / sizeof(uint32_t)]{};

uint32_t get_value(std::uint32_t index) {
    return backup_sram[index & 0x3FF];
}

void set_value(std::uint32_t index, std::uint32_t value) {
    backup_sram[index & 0x3FF] = value;
}

}    // namespace stm32
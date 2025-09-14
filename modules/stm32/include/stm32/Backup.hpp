#ifndef STM32_BACKUP_HPP_
#define STM32_BACKUP_HPP_

/// @file
/// STM32 Backup RAM access
#include <cstdint>

namespace stm32 {

/// Gets a value from the backup ram at an index
std::uint32_t get_value(std::uint32_t index);

/// Sets a value to an index in the backup ram.
void set_value(std::uint32_t index, std::uint32_t value);

}    // namespace stm32

#endif    // STM32_BACKUP_HPP_

#ifndef STM32F407VE_HPP_
#define STM32F407VE_HPP_

#define STM32_HAS_FSMC 1
#define STM32_HAS_ETHERNET 1
#define STM32_HAS_CAMERA 1

#include "stm32/stm32f40xxx.hpp"

/// The ST Micro 32 Namespace
namespace stm32 {

/// Contains the defined address for the chip
/// @TODO Eliminate the need for this namespace. ONLY the linker should know these values.
/// The primary reason they are know is due to the MPU and the need to have large address
/// ranges defined as constexprs for compile time use.
namespace address {
/// The Base Address of Flash
constexpr std::uintptr_t flash = 0x08'00'00'00UL;
/// The Base Address of CCM
constexpr std::uintptr_t ccm = 0x10'00'00'00UL;
/// The Base Address of SRAM
constexpr std::uintptr_t sram = cortex::m4::address::sram;
/// The Base Address of Backup RAM
constexpr std::uintptr_t backup_sram = 0x40'02'40'00UL;
}    // namespace address

/// @brief The sizes of the Ranges of the Processor
namespace sizes {
/// The Size in Bytes of Flash
constexpr std::uint32_t flash = 512U * iso::prefix::kibi;
/// The Size in Bytes of CCM
constexpr std::uint32_t ccm = 64U * iso::prefix::kibi;
/// The Size in Bytes of SRAM
constexpr std::uint32_t sram = (112U + 16U) * iso::prefix::kibi;
/// The Size in Bytes of Backup SRAM
constexpr std::uint32_t backup_sram = 4U * iso::prefix::kibi;
/// @brief The sizes represented as powers of 2
namespace power2 {
/// The Power of 2 of the Flash Size
constexpr std::uint8_t flash = polyfill::log2(stm32::sizes::flash);
/// The Power of 2 of the CCM Size
constexpr std::uint8_t ccm = polyfill::log2(stm32::sizes::ccm);
/// The Power of 2 of the SRAM Size
constexpr std::uint8_t sram = polyfill::log2(stm32::sizes::sram);
/// The Power of 2 of the Backup SRAM Size
constexpr std::uint32_t backup_sram = polyfill::log2(stm32::sizes::backup_sram);
}    // namespace power2
}    // namespace sizes

/// The number of GPIOs on this part
constexpr static size_t number_of_gpios = 82U;

}    // namespace stm32

#endif    // STM32F407VE_HPP_

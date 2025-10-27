#ifndef STM32H753ZI_HPP_
#define STM32H753ZI_HPP_

#include "iso.hpp"
#define STM32_HAS_FSMC 1
#define STM32_HAS_ETHERNET 1
#define STM32_HAS_CAMERA 1

#include "stm32/stm32h7xxxx.hpp"

/// The ST Micro 32 Namespace
namespace stm32 {

/// Contains the defined address for the chip
/// @TODO Eliminate the need for this namespace. ONLY the linker should know these values.
/// The primary reason they are know is due to the MPU and the need to have large address
/// ranges defined as constexprs for compile time use.
namespace address {
/// The Base Address of Flash
constexpr std::uintptr_t flash = 0x08'00'00'00UL;
/// The Base Address of ITCM
constexpr std::uintptr_t itcm = 0x00'00'00'00UL;
/// The Base Address of DTCM
constexpr std::uintptr_t dtcm = 0x20'00'00'00UL;
/// The Base Address of SRAM
constexpr std::uintptr_t sram = cortex::m7::address::sram;
/// The Base Address of Backup RAM
constexpr std::uintptr_t backup_sram = 0x40'02'40'00UL;
}    // namespace address

/// @brief The sizes of the Ranges of the Processor
namespace sizes {
/// The Size in Bytes of Flash
constexpr std::uint32_t flash = 2U * iso::prefix::mebi;
/// The Size in Bytes of itcm
constexpr std::uint32_t itcm = 64U * iso::prefix::kibi;
/// The Size in Bytes of dtcm
constexpr std::uint32_t dtcm = 128U * iso::prefix::kibi;
/// The Size in Bytes of SRAM
constexpr std::uint32_t sram = (512U + 288U + 64U) * iso::prefix::kibi;
/// The Size in Bytes of Backup SRAM
constexpr std::uint32_t backup_sram = 4U * iso::prefix::kibi;
/// @brief The sizes represented as powers of 2
namespace power2 {
/// The Power of 2 of the Flash Size
constexpr std::uint8_t flash = polyfill::log2(stm32::sizes::flash);
/// The Power of 2 of the ITCM Size
constexpr std::uint8_t itcm = polyfill::log2(stm32::sizes::itcm);
/// The Power of 2 of the DTCM Size
constexpr std::uint8_t dtcm = polyfill::log2(stm32::sizes::dtcm);
/// The Power of 2 of the SRAM Size
constexpr std::uint8_t sram = polyfill::log2(stm32::sizes::sram);
/// The Power of 2 of the Backup SRAM Size
constexpr std::uint32_t backup_sram = polyfill::log2(stm32::sizes::backup_sram);
}    // namespace power2
}    // namespace sizes

// The package determines the number of GPIOs available
#if defined(STM32H743ZILQFP100) and (STM32H743ZILQFP100 == 1)
/// The number of GPIOs on this part
constexpr static size_t number_of_gpios = 114U;
#endif

}    // namespace stm32

#endif    // STM32H753ZI_HPP_

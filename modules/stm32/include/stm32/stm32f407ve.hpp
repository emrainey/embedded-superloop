#ifndef STM32F407VE_HPP_
#define STM32F407VE_HPP_

#include "core/Units.hpp"
#include "stm32/stm32.hpp"

#define HAS_FLASH 1
#undef HAS_ITCM
#undef HAS_DTCM
#define HAS_CCM 1
#define HAS_SRAM 1

/// The ST Micro 32 Namespace
namespace stm32 {

namespace configuration {
constexpr bool has_flash{true};
constexpr bool has_ccm{true};
constexpr bool has_itcm{false};
constexpr bool has_dtcm{false};
constexpr bool has_sram{true};
}    // namespace configuration

/// Contains the defined address for the chip
namespace address {
/// The Base Address of Flash
constexpr uintptr_t flash = 0x08'00'00'00UL;
/// The Base Address of CCM
constexpr uintptr_t ccm = 0x10'00'00'00UL;
/// The Base Address of SRAM
constexpr uintptr_t sram = cortex::address::sram;
/// The Base Address of Backup RAM
constexpr uintptr_t backup_sram = 0x40'02'40'00UL;
/// The Base Address of the Reset and Clock Control Peripheral
constexpr uintptr_t rcc = 0x40'02'38'00;
/// The Base Address of RNG
constexpr uintptr_t random_number_generator = 0x50'06'08'00UL;
}    // namespace address

namespace sizes {
/// The Size in Bytes of Flash
constexpr std::uint32_t flash = 1U * iso::prefix::mebi;
/// The Size in Bytes of CCM
constexpr std::uint32_t ccm = 64U * iso::prefix::kibi;
/// The Size in Bytes of SRAM
constexpr std::uint32_t sram = (112U + 16U) * iso::prefix::kibi;
/// The Size in Bytes of Backup SRAM
constexpr std::uint32_t backup_sram = 4U * iso::prefix::kibi;
namespace power2 {
/// The Power of 2 of the CCM Size
constexpr std::uint8_t flash = polyfill::log2(stm32::sizes::flash);
/// The Power of 2 of the CCM Size
constexpr std::uint8_t ccm = polyfill::log2(stm32::sizes::ccm);
/// The Power of 2 of the SRAM Size
constexpr std::uint8_t sram = polyfill::log2(stm32::sizes::sram);
/// The Power of 2 of the Backup SRAM Size
constexpr std::uint32_t backup_sram = polyfill::log2(stm32::sizes::backup_sram);
}    // namespace power2
}    // namespace sizes

using namespace core::units;

/// @brief The speed of the HSI oscillator on most STM32 parts
constexpr Hertz high_speed_internal_oscillator_frequency = 16_MHz;

/// The clock speed of the STM32F407VE
constexpr Hertz top_clock_frequency = 168_MHz;

/// The number of extended interrupt vectors supported on this processor
constexpr std::uint32_t number_of_interrupt_channels = 82U;

/// The layout of the vendor portion of the extended vector table
struct ExternalInterrupts final {
    /// The external interrupt handlers
    cortex::exceptions::HandlerFunction handlers[number_of_interrupt_channels];
};

/// The chip specific external interrupts table
extern ExternalInterrupts external_interrupts;

/// @see cortex::m4::InterruptRequest for preceding numbers
enum class InterruptRequest : int {
    WindowWatchDog = 0,
    /// @todo fill in up to 81
};

/// Gets a value from the backup ram at an index
std::uint32_t get_value(std::uint32_t index);

/// Sets a value to an index in the backup ram.
void set_value(std::uint32_t index, std::uint32_t value);

}    // namespace stm32
#endif    // STM32F407VE_HPP_
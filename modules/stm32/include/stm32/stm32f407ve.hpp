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
/// @TODO Eliminate the need for this namespace. ONLY the linker should know these values.
/// The primary reason they are know is due to the MPU and the need to have large address
/// ranges defined as constexprs for compile time use.
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

/// @brief The sizes of the Ranges of the Processor
namespace sizes {
/// The Size in Bytes of Flash
constexpr std::uint32_t flash = 1U * iso::prefix::mebi;
/// The Size in Bytes of CCM
constexpr std::uint32_t ccm = 64U * iso::prefix::kibi;
/// The Size in Bytes of SRAM
constexpr std::uint32_t sram = (112U + 16U) * iso::prefix::kibi;
/// The Size in Bytes of Backup SRAM
constexpr std::uint32_t backup_sram = 4U * iso::prefix::kibi;
/// @brief The sizes represented as powers of 2
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

/// Counts the number of times each interrupt has been called
/// @note This is used to track the number of times each vector table entry has been called
struct ExternalInterruptStatistics final {
    std::size_t count[number_of_interrupt_channels]{0U};    ///< Incremented by the interrupt handler per interrupt
};

/// @brief Each Driver interrupt increments their own count
extern ExternalInterruptStatistics external_interrupt_statistics;

/// @see cortex::m4::InterruptRequest for preceding numbers
enum class InterruptRequest : int {
    WindowWatchDog = 0U,
    PowerSupervisior = 1U,    ///< PVD
    TamperAndTimeStamp = 2U,
    RealTimeClockWakeUp = 3U,
    Flash = 4U,
    ResetAndClockControl = 5U,
    ExternalInterrupt0 = 6U,
    ExternalInterrupt1 = 7U,
    ExternalInterrupt2 = 8U,
    ExternalInterrupt3 = 9U,
    ExternalInterrupt4 = 10U,
    DirectMemoryAccess1Stream0 = 11U,
    DirectMemoryAccess1Stream1 = 12U,
    DirectMemoryAccess1Stream2 = 13U,
    DirectMemoryAccess1Stream3 = 14U,
    DirectMemoryAccess1Stream4 = 15U,
    DirectMemoryAccess1Stream5 = 16U,
    DirectMemoryAccess1Stream6 = 17U,
    AnalogToDigitalConverters = 18U,    // ADC1, 2, and 3
    ControllerAreaNetwork1_TX = 19U,
    ControllerAreaNetwork1_RX0 = 20U,
    ControllerAreaNetwork1_RX1 = 21U,
    ControllerAreaNetwork1_SCE = 22U,
    ExternalLine5 = 23U,
    ExternalLine6 = 23U,
    ExternalLine7 = 23U,
    ExternalLine8 = 23U,
    ExternalLine9 = 23U,
    Timer1_Break = 24U,
    Timer9 = 24U,
    Timer1_Update = 25U,
    Timer10 = 25U,
    Timer1_Trigger = 26U,
    Timer11 = 26U,
    Timer1_CaptureCompare = 27U,
    Timer2 = 28U,
    Timer3 = 29U,
    Timer4 = 30U,
    InterIntegratedCircuit1_Event = 31U,
    InterIntegratedCircuit1_Error = 32U,
    InterIntegratedCircuit2_Event = 33U,
    InterIntegratedCircuit2_Error = 34U,
    SerialPeripheralInterface1 = 35U,
    SerialPeripheralInterface2 = 36U,
    UniversalSynchronousAsynchronousReceiverTransmitter1 = 37U,
    UniversalSynchronousAsynchronousReceiverTransmitter2 = 38U,
    UniversalSynchronousAsynchronousReceiverTransmitter3 = 39U,
    ExternalLine10 = 40U,
    ExternalLine11 = 40U,
    ExternalLine12 = 40U,
    ExternalLine13 = 40U,
    ExternalLine14 = 40U,
    ExternalLine15 = 40U,
    RealTimeClock_Alarm = 41U,
    UniversalSerialBusOnTheGoFullSpeedWakeUp = 42U,    ///< USB OTG FS Wakeup
    Timer8_Break = 43U,
    Timer12 = 43U,
    Timer8_Update = 44U,
    Timer13 = 44U,
    Timer8_Trigger = 45U,
    Timer14 = 45U,
    Timer8_CaptureCompare = 46U,
    DirectMemoryAccess1Stream7 = 47U,
    FlexibleStaticMemoryController = 48U,    ///< FSMC
    SerialDataInputOutput = 49U,             ///< SDIO
    Timer5 = 50U,
    SerialPeripheralInterface3 = 51U,
    UniversalAsynchronousReceiverTransmitter4 = 52U,    ///< UART4
    UniversalAsynchronousReceiverTransmitter5 = 53U,    ///< UART5
    Timer6 = 54U,
    DigitalToAnalogConverter1 = 54U,
    DigitalToAnalogConverter2 = 54U,
    Timer7 = 55U,
    DirectMemoryAccess2Stream0 = 56U,
    DirectMemoryAccess2Stream1 = 57U,
    DirectMemoryAccess2Stream2 = 58U,
    DirectMemoryAccess2Stream3 = 59U,
    DirectMemoryAccess2Stream4 = 60U,
    Ethernet = 61U,
    EthernetWakeUp = 62U,
    ControllerAreaNetwork2_TX = 63U,
    ControllerAreaNetwork2_RX0 = 64U,
    ControllerAreaNetwork2_RX1 = 65U,
    ControllerAreaNetwork2_SCE = 66U,
    UniversalSerialBusOnTheGoFullSpeed = 67U,    ///< USB OTG FS
    DirectMemoryAccess2Stream5 = 68U,
    DirectMemoryAccess2Stream6 = 69U,
    DirectMemoryAccess2Stream7 = 70U,
    UniversalSynchronousAsynchronousReceiverTransmitter6 = 71U,    ///< USART6
    InterIntegratedCircuit3_Event = 72U,
    InterIntegratedCircuit3_Error = 73U,
    UniversalSerialBusOnTheGoHighSpeedEndPoint1Out = 74U,    ///< USB OTG HS EP1 Out
    UniversalSerialBusOnTheGoHighSpeedEndPoint1In = 75U,     ///< USB OTG HS EP1 In
    UniversalSerialBusOnTheGoHighSpeedWakeUp = 76U,          ///< USB OTG HS WKUP
    UniversalSerialBusOnTheGoHighSpeed = 77U,                ///< USB OTG HS
    DigitalCameraInterface = 78U,                            ///< DCMI
    // ??? = 79U,
    // ??? = 80U,
    FloatingPointUnit = 81U,    ///< FPU
    _count = 82U,
};
static_assert(static_cast<std::size_t>(InterruptRequest::_count) == number_of_interrupt_channels, "The number of interrupts is incorrect");

/// Gets a value from the backup ram at an index
std::uint32_t get_value(std::uint32_t index);

/// Sets a value to an index in the backup ram.
void set_value(std::uint32_t index, std::uint32_t value);

}    // namespace stm32
#endif    // STM32F407VE_HPP_
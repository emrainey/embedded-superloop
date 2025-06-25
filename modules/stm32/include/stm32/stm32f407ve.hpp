#ifndef STM32F407VE_HPP_
#define STM32F407VE_HPP_

#include "core/Units.hpp"
#include "stm32/stm32.hpp"
#include "jarnax/Peripheral.hpp"

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
enum class InterruptRequest : jarnax::InterruptRequestType {
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

using Peripheral = jarnax::Peripheral;

constexpr static Peripheral _ = jarnax::_;

constexpr static Peripheral ADC1 = Peripheral{Peripheral::Type::ADC, 1, Peripheral::Sub::None};
constexpr static Peripheral ADC2 = Peripheral{Peripheral::Type::ADC, 2, Peripheral::Sub::None};
constexpr static Peripheral ADC3 = Peripheral{Peripheral::Type::ADC, 3, Peripheral::Sub::None};
constexpr static Peripheral DAC1 = Peripheral{Peripheral::Type::DAC, 1, Peripheral::Sub::None};
constexpr static Peripheral DAC2 = Peripheral{Peripheral::Type::DAC, 2, Peripheral::Sub::None};
constexpr static Peripheral DCMI = Peripheral{Peripheral::Type::DCMI, 1, Peripheral::Sub::None};
constexpr static Peripheral CRYPTO_IN = Peripheral{Peripheral::Type::CRYPTO, 0, Peripheral::Sub::IN};
constexpr static Peripheral CRYPTO_OUT = Peripheral{Peripheral::Type::CRYPTO, 0, Peripheral::Sub::OUT};

constexpr static Peripheral HASH_IN = Peripheral{Peripheral::Type::HASH, 0, Peripheral::Sub::IN};
constexpr static Peripheral HASH_OUT = Peripheral{Peripheral::Type::HASH, 0, Peripheral::Sub::OUT};

constexpr static Peripheral I2C1_RX = Peripheral{Peripheral::Type::I2C, 1, Peripheral::Sub::RX};
constexpr static Peripheral I2C1_TX = Peripheral{Peripheral::Type::I2C, 1, Peripheral::Sub::TX};
constexpr static Peripheral I2C2_RX = Peripheral{Peripheral::Type::I2C, 2, Peripheral::Sub::RX};
constexpr static Peripheral I2C2_TX = Peripheral{Peripheral::Type::I2C, 2, Peripheral::Sub::TX};
constexpr static Peripheral I2C3_RX = Peripheral{Peripheral::Type::I2C, 3, Peripheral::Sub::RX};
constexpr static Peripheral I2C3_TX = Peripheral{Peripheral::Type::I2C, 3, Peripheral::Sub::TX};

constexpr static Peripheral I2S0_EXT_RX = Peripheral{Peripheral::Type::I2S_EXT, 0, Peripheral::Sub::RX};
constexpr static Peripheral I2S0_EXT_TX = Peripheral{Peripheral::Type::I2S_EXT, 0, Peripheral::Sub::TX};
constexpr static Peripheral I2S1_EXT_RX = Peripheral{Peripheral::Type::I2S_EXT, 1, Peripheral::Sub::RX};
constexpr static Peripheral I2S1_EXT_TX = Peripheral{Peripheral::Type::I2S_EXT, 1, Peripheral::Sub::TX};
constexpr static Peripheral I2S2_EXT_RX = Peripheral{Peripheral::Type::I2S_EXT, 2, Peripheral::Sub::RX};
constexpr static Peripheral I2S2_EXT_TX = Peripheral{Peripheral::Type::I2S_EXT, 2, Peripheral::Sub::TX};
constexpr static Peripheral I2S3_EXT_RX = Peripheral{Peripheral::Type::I2S_EXT, 3, Peripheral::Sub::RX};
constexpr static Peripheral I2S3_EXT_TX = Peripheral{Peripheral::Type::I2S_EXT, 3, Peripheral::Sub::TX};

constexpr static Peripheral SAI1_A = Peripheral{Peripheral::Type::SAI, 1, Peripheral::Sub::A};
constexpr static Peripheral SAI1_B = Peripheral{Peripheral::Type::SAI, 1, Peripheral::Sub::B};

constexpr static Peripheral SDIO = Peripheral{Peripheral::Type::SDIO, 0, Peripheral::Sub::None};

constexpr static Peripheral SPI1_RX = Peripheral{Peripheral::Type::SPI, 1, Peripheral::Sub::RX};
constexpr static Peripheral SPI1_TX = Peripheral{Peripheral::Type::SPI, 1, Peripheral::Sub::TX};
constexpr static Peripheral SPI2_RX = Peripheral{Peripheral::Type::SPI, 2, Peripheral::Sub::RX};
constexpr static Peripheral SPI2_TX = Peripheral{Peripheral::Type::SPI, 2, Peripheral::Sub::TX};
constexpr static Peripheral SPI3_RX = Peripheral{Peripheral::Type::SPI, 3, Peripheral::Sub::RX};
constexpr static Peripheral SPI3_TX = Peripheral{Peripheral::Type::SPI, 3, Peripheral::Sub::TX};
constexpr static Peripheral SPI4_RX = Peripheral{Peripheral::Type::SPI, 4, Peripheral::Sub::RX};
constexpr static Peripheral SPI4_TX = Peripheral{Peripheral::Type::SPI, 4, Peripheral::Sub::TX};
constexpr static Peripheral SPI5_RX = Peripheral{Peripheral::Type::SPI, 5, Peripheral::Sub::RX};
constexpr static Peripheral SPI5_TX = Peripheral{Peripheral::Type::SPI, 5, Peripheral::Sub::TX};
constexpr static Peripheral SPI6_RX = Peripheral{Peripheral::Type::SPI, 6, Peripheral::Sub::RX};
constexpr static Peripheral SPI6_TX = Peripheral{Peripheral::Type::SPI, 6, Peripheral::Sub::TX};

constexpr static Peripheral TIM1_CH1 = Peripheral{Peripheral::Type::TIMER, 1, Peripheral::Sub::CH1};
constexpr static Peripheral TIM1_CH2 = Peripheral{Peripheral::Type::TIMER, 1, Peripheral::Sub::CH2};
constexpr static Peripheral TIM1_CH3 = Peripheral{Peripheral::Type::TIMER, 1, Peripheral::Sub::CH3};
constexpr static Peripheral TIM1_CH4 = Peripheral{Peripheral::Type::TIMER, 1, Peripheral::Sub::CH4};
constexpr static Peripheral TIM1_TRIG = Peripheral{Peripheral::Type::TIMER, 1, Peripheral::Sub::TRIG};
constexpr static Peripheral TIM1_COM = Peripheral{Peripheral::Type::TIMER, 1, Peripheral::Sub::COM};
constexpr static Peripheral TIM1_UP = Peripheral{Peripheral::Type::TIMER, 1, Peripheral::Sub::UP};

constexpr static Peripheral TIM2_CH1 = Peripheral{Peripheral::Type::TIMER, 2, Peripheral::Sub::CH1};
constexpr static Peripheral TIM2_CH2 = Peripheral{Peripheral::Type::TIMER, 2, Peripheral::Sub::CH2};
constexpr static Peripheral TIM2_CH3 = Peripheral{Peripheral::Type::TIMER, 2, Peripheral::Sub::CH3};
constexpr static Peripheral TIM2_CH4 = Peripheral{Peripheral::Type::TIMER, 2, Peripheral::Sub::CH4};
constexpr static Peripheral TIM2_TRIG = Peripheral{Peripheral::Type::TIMER, 2, Peripheral::Sub::TRIG};
constexpr static Peripheral TIM2_COM = Peripheral{Peripheral::Type::TIMER, 2, Peripheral::Sub::COM};
constexpr static Peripheral TIM2_UP = Peripheral{Peripheral::Type::TIMER, 2, Peripheral::Sub::UP};

constexpr static Peripheral TIM3_CH1 = Peripheral{Peripheral::Type::TIMER, 3, Peripheral::Sub::CH1};
constexpr static Peripheral TIM3_CH2 = Peripheral{Peripheral::Type::TIMER, 3, Peripheral::Sub::CH2};
constexpr static Peripheral TIM3_CH3 = Peripheral{Peripheral::Type::TIMER, 3, Peripheral::Sub::CH3};
constexpr static Peripheral TIM3_CH4 = Peripheral{Peripheral::Type::TIMER, 3, Peripheral::Sub::CH4};
constexpr static Peripheral TIM3_TRIG = Peripheral{Peripheral::Type::TIMER, 3, Peripheral::Sub::TRIG};
constexpr static Peripheral TIM3_COM = Peripheral{Peripheral::Type::TIMER, 3, Peripheral::Sub::COM};
constexpr static Peripheral TIM3_UP = Peripheral{Peripheral::Type::TIMER, 3, Peripheral::Sub::UP};

constexpr static Peripheral TIM4_CH1 = Peripheral{Peripheral::Type::TIMER, 4, Peripheral::Sub::CH1};
constexpr static Peripheral TIM4_CH2 = Peripheral{Peripheral::Type::TIMER, 4, Peripheral::Sub::CH2};
constexpr static Peripheral TIM4_CH3 = Peripheral{Peripheral::Type::TIMER, 4, Peripheral::Sub::CH3};
constexpr static Peripheral TIM4_CH4 = Peripheral{Peripheral::Type::TIMER, 4, Peripheral::Sub::CH4};
constexpr static Peripheral TIM4_TRIG = Peripheral{Peripheral::Type::TIMER, 4, Peripheral::Sub::TRIG};
constexpr static Peripheral TIM4_COM = Peripheral{Peripheral::Type::TIMER, 4, Peripheral::Sub::COM};
constexpr static Peripheral TIM4_UP = Peripheral{Peripheral::Type::TIMER, 4, Peripheral::Sub::UP};

constexpr static Peripheral TIM5_CH1 = Peripheral{Peripheral::Type::TIMER, 5, Peripheral::Sub::CH1};
constexpr static Peripheral TIM5_CH2 = Peripheral{Peripheral::Type::TIMER, 5, Peripheral::Sub::CH2};
constexpr static Peripheral TIM5_CH3 = Peripheral{Peripheral::Type::TIMER, 5, Peripheral::Sub::CH3};
constexpr static Peripheral TIM5_CH4 = Peripheral{Peripheral::Type::TIMER, 5, Peripheral::Sub::CH4};
constexpr static Peripheral TIM5_TRIG = Peripheral{Peripheral::Type::TIMER, 5, Peripheral::Sub::TRIG};
constexpr static Peripheral TIM5_COM = Peripheral{Peripheral::Type::TIMER, 5, Peripheral::Sub::COM};
constexpr static Peripheral TIM5_UP = Peripheral{Peripheral::Type::TIMER, 5, Peripheral::Sub::UP};

constexpr static Peripheral TIM6_UP = Peripheral{Peripheral::Type::TIMER, 6, Peripheral::Sub::UP};

constexpr static Peripheral TIM7_UP = Peripheral{Peripheral::Type::TIMER, 7, Peripheral::Sub::UP};

constexpr static Peripheral TIM8_CH1 = Peripheral{Peripheral::Type::TIMER, 8, Peripheral::Sub::CH1};
constexpr static Peripheral TIM8_CH2 = Peripheral{Peripheral::Type::TIMER, 8, Peripheral::Sub::CH2};
constexpr static Peripheral TIM8_CH3 = Peripheral{Peripheral::Type::TIMER, 8, Peripheral::Sub::CH3};
constexpr static Peripheral TIM8_CH4 = Peripheral{Peripheral::Type::TIMER, 8, Peripheral::Sub::CH4};
constexpr static Peripheral TIM8_TRIG = Peripheral{Peripheral::Type::TIMER, 8, Peripheral::Sub::TRIG};
constexpr static Peripheral TIM8_COM = Peripheral{Peripheral::Type::TIMER, 8, Peripheral::Sub::COM};
constexpr static Peripheral TIM8_UP = Peripheral{Peripheral::Type::TIMER, 8, Peripheral::Sub::UP};

constexpr static Peripheral USART1_RX = Peripheral{Peripheral::Type::USART, 1, Peripheral::Sub::RX};
constexpr static Peripheral USART1_TX = Peripheral{Peripheral::Type::USART, 1, Peripheral::Sub::TX};
constexpr static Peripheral USART2_RX = Peripheral{Peripheral::Type::USART, 2, Peripheral::Sub::RX};
constexpr static Peripheral USART2_TX = Peripheral{Peripheral::Type::USART, 2, Peripheral::Sub::TX};
constexpr static Peripheral USART3_RX = Peripheral{Peripheral::Type::USART, 3, Peripheral::Sub::RX};
constexpr static Peripheral USART3_TX = Peripheral{Peripheral::Type::USART, 3, Peripheral::Sub::TX};
constexpr static Peripheral USART6_RX = Peripheral{Peripheral::Type::USART, 6, Peripheral::Sub::RX};
constexpr static Peripheral USART6_TX = Peripheral{Peripheral::Type::USART, 6, Peripheral::Sub::TX};

constexpr static Peripheral UART4_RX = Peripheral{Peripheral::Type::UART, 4, Peripheral::Sub::RX};
constexpr static Peripheral UART4_TX = Peripheral{Peripheral::Type::UART, 4, Peripheral::Sub::TX};
constexpr static Peripheral UART5_RX = Peripheral{Peripheral::Type::UART, 5, Peripheral::Sub::RX};
constexpr static Peripheral UART5_TX = Peripheral{Peripheral::Type::UART, 5, Peripheral::Sub::TX};
constexpr static Peripheral UART6_RX = Peripheral{Peripheral::Type::UART, 6, Peripheral::Sub::RX};
constexpr static Peripheral UART6_TX = Peripheral{Peripheral::Type::UART, 6, Peripheral::Sub::TX};
constexpr static Peripheral UART7_RX = Peripheral{Peripheral::Type::UART, 7, Peripheral::Sub::RX};
constexpr static Peripheral UART7_TX = Peripheral{Peripheral::Type::UART, 7, Peripheral::Sub::TX};
constexpr static Peripheral UART8_RX = Peripheral{Peripheral::Type::UART, 8, Peripheral::Sub::RX};
constexpr static Peripheral UART8_TX = Peripheral{Peripheral::Type::UART, 8, Peripheral::Sub::TX};

static_assert(ADC1 == ADC1, "Must be this value exactly");
static_assert((TIM8_CH1 | TIM8_CH2) == TIM8_CH1, "Must be this value exactly");
static_assert((TIM8_CH1 | TIM8_CH2 | TIM8_CH3) == TIM8_CH1, "Must be this value exactly");

/// Gets a value from the backup ram at an index
std::uint32_t get_value(std::uint32_t index);

/// Sets a value to an index in the backup ram.
void set_value(std::uint32_t index, std::uint32_t value);

}    // namespace stm32
#endif    // STM32F407VE_HPP_
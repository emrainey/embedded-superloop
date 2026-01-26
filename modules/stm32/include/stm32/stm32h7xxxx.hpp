#ifndef STM32H7xXXX_HPP_
#define STM32H7xXXX_HPP_

/// @file
/// STM32H7 Series Peripheral Definitions

#include "stm32/stm32.hpp"
///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#include "stm32/peripherals/Debug.hpp"
#include "stm32/peripherals/DirectMemoryAccess.hpp"
#include "stm32/peripherals/FlashControl.hpp"
#include "stm32/peripherals/GeneralPurposeInputOutput.hpp"
#include "stm32/peripherals/InterIntegratedCircuit.hpp"
#include "stm32/peripherals/RandomNumberGenerator.hpp"
#include "stm32/peripherals/ResetAndClockControl.hpp"
#include "stm32/peripherals/SerialPeripheralInterface.hpp"
#include "stm32/peripherals/Timer2.hpp"
#include "stm32/peripherals/UniversalAsynchronousReceiverTransmitter.hpp"
#include "stm32/peripherals/UniversalSynchronousAsynchronousReceiverTransmitter.hpp"

namespace stm32 {

using Hertz = core::units::Hertz;
using core::units::operator""_Hz;
using core::units::operator""_KHz;
using core::units::operator""_MHz;

/// @brief The speed of the HSI oscillator on most STM32 parts
constexpr Hertz high_speed_internal_oscillator_frequency = 64_MHz;

/// @brief The speed of the HSE oscillator on most STM32 parts
constexpr Hertz low_speed_internal_oscillator_frequency = 32_KHz;

/// The clock speed of the STM32H7xxxx
constexpr Hertz top_clock_frequency = 480_MHz;

/// The number of extended interrupt vectors supported on this processor
constexpr std::uint32_t number_of_interrupt_channels = 150U;

/// @see cortex::m7::InterruptRequest for preceding numbers
enum class InterruptRequest : cortex::InterruptRequestType {
    WindowWatchDog = 0U,
    PowerSupervisor = 1U,    ///< PVD
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
    AnalogToDigitalConverters = 18U,    // ADC1, 2
    ControllerAreaNetworkFlexibleDataRate1Int0 = 19U,
    ControllerAreaNetworkFlexibleDataRate2Int0 = 20U,
    ControllerAreaNetworkFlexibleDataRate1Int1 = 21U,
    ControllerAreaNetworkFlexibleDataRate2Int1 = 22U,
    ExternalLine5 = 23U,
    ExternalLine6 = 23U,
    ExternalLine7 = 23U,
    ExternalLine8 = 23U,
    ExternalLine9 = 23U,
    Timer1_Break = 24U,
    Timer1_Update = 25U,
    Timer1_Trigger = 26U,
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
    // Reserved = 42U,
    Timer8_Break = 43U,
    Timer12 = 43U,
    Timer8_Update = 44U,
    Timer13 = 44U,
    Timer8_Trigger = 45U,
    Timer14 = 45U,
    Timer8_CaptureCompare = 46U,
    DirectMemoryAccess1Stream7 = 47U,
#if defined(STM32_HAS_FSMC) && (STM32_HAS_FSMC == 1)
    FlexibleStaticMemoryController = 48U,    ///< FSMC
#endif
    SerialDataMultimediaCard1 = 49U,         ///< SDMMC1
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
#if defined(STM32_HAS_ETHERNET) && (STM32_HAS_ETHERNET == 1)
    Ethernet = 61U,
    EthernetWakeUp = 62U,
#endif
    ControllerAreaNetworkFlexibleDataRateCalibration = 63U,
    CortexM7SendEven = 64U,
    // Reserved = 65U,
    // Reserved = 66U,
    // Reserved = 67U,
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
#if defined(STM32_HAS_CAMERA) && (STM32_HAS_CAMERA == 1)
    DigitalCameraInterface = 78U,                            ///< DCMI
#endif
    Cryptography = 79U,                                      ///< CRYP and HASH
    RandomNumberGenerator = 80U,                             ///< RNG
    FloatingPointUnit = 81U,                                 ///< FPU
    UniversalAsynchronousReceiverTransmitter7 = 82U,         ///< UART7
    UniversalAsynchronousReceiverTransmitter8 = 83U,         ///< UART8
    SerialPeripheralInterface4 = 84U,                        ///< SPI4
    SerialPeripheralInterface5 = 85U,                        ///< SPI5
    SerialPeripheralInterface6 = 86U,                        ///< SPI6
    SerialAudioInterface1 = 87U,                             ///< SAI1
    LiquidCrystalDisplayTFT = 88U,                           ///< LTDC
    LiquidCrystalDisplayTFTError = 89U,                      ///< LTDC ERR
    DirectMemoryAccess2D = 90U,                              ///< DMA2D
    SerialAudioInterface2 = 91U,                             ///< SAI2
    QuadSPI = 92U,                                           ///< QUADSPI
    LowPowerTimer1 = 93U,                                    ///< LPTIM1
    HDMIConsumerElectronicsControl = 94U,                    ///< HDMI CEC
    InterIntegratedCircuit4_Event = 95U,                     ///< I2C4 Event
    InterIntegratedCircuit4_Error = 96U,                     ///< I2C4 Error
    SonyPhilipsDigitalInterfaceReceive = 97U,                ///< SPDIFRX
    UniversalSerialBusOnTheGoFullSpeedEndPoint1Out = 98U,    ///< USB OTG FS EP1 Out
    UniversalSerialBusOnTheGoFullSpeedEndPoint1In = 99U,     ///< USB OTG FS EP1 In
    UniversalSerialBusOnTheGoFullSpeedWakeUp = 100U,         ///< USB OTG FS WKUP
    UniversalSerialBusOnTheGoFullSpeed = 101U,               ///< USB OTG FS
    DirectMemoryAccessMultiplexerOverrun = 102U,             ///< DMAMUX1 Overrun
    HighResolutionTimer1Master = 103U,                       ///< HRTIM1 Master
    HighResolutionTimer1TimerA = 104U,                       ///< HRTIM1 Timer A
    HighResolutionTimer1TimerB = 105U,                       ///< HRTIM1 Timer
    HighResolutionTimer1TimerC = 106U,                       ///< HRTIM1 Timer C
    HighResolutionTimer1TimerD = 107U,                       ///< HRTIM1 Timer
    HighResolutionTimer1TimerE = 108U,                       ///< HRTIM1 Timer E
    HighResolutionTimer1Fault = 109U,                        ///< HRTIM1 Fault
    DigitalFilterForSigmaDeltaModulators0 = 110U,            ///< DFSDM0
    DigitalFilterForSigmaDeltaModulators1 = 111U,            ///< DFSDM1
    DigitalFilterForSigmaDeltaModulators2 = 112U,            ///< DFSDM2
    DigitalFilterForSigmaDeltaModulators3 = 113U,            ///< DFSDM3
    SerialAudioInterface3 = 114U,                            ///< SAI3
    SingleWireProtocolMasterInterface = 115U,                ///< SWPMI1
    Timer15 = 116U,                                          ///< Timer 15
    Timer16 = 117U,                                          ///< Timer 16
    Timer17 = 118U,                                          ///< Timer 17
    ManagementInputOutputWakeup = 119U,                      ///< MDIOS WKUP
    ManagementInputOutput = 120U,                            ///< MDIOS
    JointPhotographicExpertsGroupInterface = 121U,           ///< JPEG
    MasterDirectMemoryAccessController = 122U,               ///< MDMA
    // Reserved = 123U,
    SerialDataMultimediaCard2 = 124U,    ///< SDMMC2
    HardwareSemaphore1 = 125U,           ///< HSEM1
    // Reserved = 126U,
    AnalogToDigitalConverter3 = 127U,    ///< ADC3
    // TODO Add more interrupts here
    _count = 150U,
};
static_assert(static_cast<std::size_t>(InterruptRequest::_count) == number_of_interrupt_channels, "The number of interrupts is incorrect");

using Peripheral = cortex::Peripheral;

constexpr static Peripheral _ = cortex::_;

constexpr static Peripheral ADC1 = Peripheral{Peripheral::Type::ADC, 1, Peripheral::Sub::None};
constexpr static Peripheral ADC2 = Peripheral{Peripheral::Type::ADC, 2, Peripheral::Sub::None};
constexpr static Peripheral ADC3 = Peripheral{Peripheral::Type::ADC, 3, Peripheral::Sub::None};
constexpr static Peripheral DAC1 = Peripheral{Peripheral::Type::DAC, 1, Peripheral::Sub::None};
constexpr static Peripheral DAC2 = Peripheral{Peripheral::Type::DAC, 2, Peripheral::Sub::None};
#if defined(STM32_HAS_CAMERA) && (STM32_HAS_CAMERA == 1)
constexpr static Peripheral DCMI = Peripheral{Peripheral::Type::DCMI, 1, Peripheral::Sub::None};
#endif
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

using Hertz = core::units::Hertz;

// The STM32F40xx Clock Tree frequencies
struct ClockTree {
    Hertz low_speed_internal;
    Hertz low_speed_external;
    Hertz high_speed_internal;
    Hertz high_speed_external;
    Hertz pll_input;          ///< The frequency of the input to the PLL
    Hertz pll_vco;            ///< The frequency of the VCO
    Hertz pll_output;         ///< The frequency of the PLL output
    Hertz sysclk;             ///< the clock before the AHB/APB divider
    Hertz eth_ptp;            ///< The frequency of the Ethernet PTP clock
    Hertz fclk;               ///< The frequency of the cortex free running clock
    Hertz hclk;               ///< The frequency of the AHB bus, DMA and Core Memory (HCLK)
    Hertz system_timer;       ///< The frequency of the Cortex SYSTICK
    Hertz apb1_peripheral;    ///< The frequency of the APB1 bus (low speed)
    Hertz apb2_peripheral;    ///< The frequency of the APB2 bus (high speed)
    Hertz pll_i2s;
    Hertz pll_48ck;
    Hertz rtc;
    Hertz rng;
    Hertz usbotg;
    Hertz apb1_timer_clk;    ///< The frequency of the TIMx clocks  (TIMxCLK)
    Hertz apb2_timer_clk;    ///< The frequency of the TIMx clocks  (TIMxCLK)
};

/// @brief The STM32H7xxx clock configuration.
/// @note This does NOT map to hardware but it does have register values which will so we limit
/// their possible value ranges.
struct ClockConfiguration {
    bool use_internal;
    bool use_bypass;
    Hertz external_clock_frequency;
    Hertz low_speed_external_oscillator_frequency;
    //---
    std::uint32_t ahb_divider             : 4;
    std::uint32_t                         : 28;
    std::uint32_t apb1_low_speed_divider  : 3;
    std::uint32_t                         : 29;
    std::uint32_t apb2_high_speed_divider : 3;
    std::uint32_t                         : 29;
    std::uint32_t mcu_clock1_divider      : 3;
    std::uint32_t                         : 29;
    std::uint32_t mcu_clock2_divider      : 3;
    std::uint32_t                         : 29;
    std::uint32_t rtc_divider             : 5;
    std::uint32_t                         : 27;
    //---
    std::uint32_t pll_m                   : 6;
    std::uint32_t                         : 32 - 6;
    std::uint32_t pll_n                   : 9;
    std::uint32_t                         : 32 - 9;
    std::uint32_t pll_p                   : 2;
    std::uint32_t                         : 32 - 2;
    std::uint32_t pll_q                   : 4;
    std::uint32_t                         : 32 - 4;
};

// Vendor Chips declare this structure
extern ClockConfiguration const default_clock_configuration;

/// Returns what the vendor considers the frequency of the system.
/// @note Interface
ClockTree const& GetClockTree();

/// @brief Gets the clock frequency for the MCU
/// @return
Hertz& GetClockFrequency();

/// @brief Gets the system tick feeder clock frequency
Hertz& GetSystemClockFrequency();

namespace initialize {

/// Initializes the Clock Tree, but with a family specific definition of the Clock Configuration
/// @param external_input_clock_frequency The clock frequency of the external clock (if present)
/// @param clkcfg The configuration of the clock for the system
void clocks(ClockConfiguration const& clkcfg);

}    // namespace initialize

}    // namespace stm32

#endif    // STM32H7XXXX_HPP_

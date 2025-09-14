#ifndef CORTEX_PERIPHERAL_HPP
#define CORTEX_PERIPHERAL_HPP

/// @file
/// @brief Contains the definition of the Peripheral class which is used to represent a hardware peripheral and it's related information.

#include <cstddef>
#include <cstdint>
#include "polyfill.hpp"

namespace cortex {

// @TODO should this be defined in Cortex Microcontroller headers?
using InterruptRequestType = std::int16_t;     ///< The type of the interrupt request number enumeration, typically a short signed integer
using InterruptPriorityType = std::uint8_t;    ///< The type of the interrupt priority, typically a small unsigned integer
using PeripheralType = std::uint8_t;           ///< The type of the peripheral enumeration, typically a small unsigned integer

/// @brief For the purposes of DMA we create a peripheral which enumerates it's type, instance and some sub-component information.
struct Peripheral {
    /// @brief The enumeration of the peripheral types on a Microcontroller.
    /// @TODO should Cortex Microcontroller peripherals be included here?
    enum class Type : PeripheralType {
        None,
        ADC,                    ///< Analog to Digital Converter
        CAN,                    ///< Controller Area Network
        CRYPTO,                 ///< Cryptographic Accelerator
        DAC,                    ///< Digital to Analog Converter
        DMA,                    ///< Direct Memory Access Controller
        DCMI,                   ///< Digital Camera Memory Interface
        EMAC,                   ///< Ethernet Media Access Controller
        FLASH,                  ///< Flash Memory
        FPU,                    ///< (Cortex) Floating Point Unit
        GMAC,                   ///< Gigabit Media Access Controller
        GPIO,                   ///< General Purpose Input Output
        HASH,                   ///< Hash Accelerator
        HSMCI,                  ///< High Speed Multimedia Card Interface
        ICI,                    ///< Image-Controller Interface
        ICM,                    ///< Integrity Check Module
        I2C,                    ///< Inter-Integrated Circuit
        I2S_EXT,                ///< External I2S Interface
        LIN,                    ///< Local Interconnect Network
        MDIO,                   ///< Media Data Input/Output
        PIT,                    ///< Periodic Interval Timer
        PWM,                    ///< Pulse Width Modulation
        QSPI,                   ///< Quad Serial Peripheral Interface
        RTC,                    ///< Real-Time Clock
        SAI,                    ///< Serial Audio Interface
        SDIO,                   ///< Secure Digital Input Output
        SDRAM,                  ///< Synchronous Dynamic Random Access Memory
        SPI,                    ///< Serial Peripheral Interface
        TICK,                   ///< (Cortex) Tick Timer (usually a system timer)
        TIMER,                  ///< Timer
        TPIU,                   ///< (Cortex) Trace Port Interface Unit
        TRNG,                   ///< True Random Number Generator
        UART,                   ///< Universal Asynchronous Receiver Transmitter
        USART,                  ///< Universal Synchronous Asynchronous Receiver Transmitter
        USB,                    ///< Universal Serial Bus (Full Speed)
        USB_HS,                 ///< Universal Serial Bus High Speed
        USB_OTG,                ///< Universal Serial Bus On-The-Go (Full Speed)
        USB_OTG_HS,             ///< Universal Serial Bus On-The-Go High Speed
        W1,                     ///< One-Wire Interface
        WDT,                    ///< Watchdog Timer
        _max,                   ///< The maximum value of the enumeration, used for bounds checking

        VENDOR_BASE = 0x80U,    ///< Vendor specific peripherals start here
    };
    static_assert(static_cast<std::uint8_t>(Type::VENDOR_BASE) > static_cast<std::uint8_t>(Type::_max), "Vendor base must be greater than _max");
    /// @brief The enumeration of the sub-types of the various peripherals
    enum class Sub : std::uint32_t {
        None = 0U,
        RX = (1U << 0U),
        TX = (1U << 1U),
        IN = (1U << 2U),
        OUT = (1U << 3U),
        CH1 = (1U << 4U),
        CH2 = (1U << 5U),
        CH3 = (1U << 6U),
        CH4 = (1U << 7U),
        TRIG = (1U << 8U),
        COM = (1U << 9U),
        UP = (1U << 10U),
        A = (1U << 11U),
        B = (1U << 12U),
        C = (1U << 13U),
        D = (1U << 14U),
        E = (1U << 15U),
        F = (1U << 16U),
        G = (1U << 17U),
        H = (1U << 18U),
        I = (1U << 19U),
        J = (1U << 20U),
        K = (1U << 21U),
    };
    Type type;
    uint8_t instance;
    Sub sub;    // a field of flags
};

/// @brief A special Peripheral that represents no peripheral.
constexpr static Peripheral _ = Peripheral{Peripheral::Type::None, 0, Peripheral::Sub::None};

/// @brief Determine if the two peripherals are the same or if they are contained within each other.
/// @param lhs
/// @param rhs
/// @return
constexpr bool operator==(Peripheral const& lhs, Peripheral const& rhs) {
    // the type and instance must match, but the sub can be a subset or superset
    bool type_match = (lhs.type == rhs.type);
    bool instance_match = (lhs.instance == rhs.instance);
    bool sub_match = ((to_underlying(lhs.sub) & to_underlying(rhs.sub)) > 0U) or (to_underlying(lhs.sub) == 0U and to_underlying(rhs.sub) == 0U);
    return type_match and instance_match and sub_match;
}

constexpr Peripheral operator|(Peripheral const& lhs, Peripheral const& rhs) {
    return Peripheral{lhs.type, lhs.instance, static_cast<Peripheral::Sub>(to_underlying(lhs.sub) | to_underlying(rhs.sub))};
}

}    // namespace cortex

#endif    // CORTEX_PERIPHERAL_HPP

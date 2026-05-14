
#ifndef STM32_H7XX_DEBUG__HPP_
#define STM32_H7XX_DEBUG__HPP_

/// @file
/// Auto Generated Structure Definitions for Debug from the Peripheralyzer.
/// @copyright

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace stm32 {
namespace h7xx {

/// Microcontroller Debug Unit (DBGMCU)
struct Debug final {
    /// DBGMCU Identity Code Register (IDC)
    struct Identity final {
        /// Default Constructor
        Identity()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Identity(Identity volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Identity(Identity const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Identity(Identity&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Identity(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Identity(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Identity() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Device ID (DEV_ID)
            uint32_t device_id   : 12;    // bits 0:11
            /// (reserved)
            uint32_t             : 4;    // bits 12:15
            /// Revision (REV_ID)
            uint32_t revision_id : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Identity& operator=(Identity&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Identity volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Identity const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint32_t.
        inline explicit operator uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint32_t
        inline explicit operator uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<Identity>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Identity) == 4UL, "Must be this exact size");
    /// DBGMCU Configuration Register (CR)
    struct Control final {
        /// Default Constructor
        Control()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Control(Control volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Control(Control const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Control(Control&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Control(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Control(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Control() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Allow D1 domain debug in Sleep mode (DBGSLEEP_D1)
            uint32_t debug_sleep_d1                 : 1;    // bit 0
            /// Allow D1 domain debug in Stop mode (DBGSTOP_D1)
            uint32_t debug_stop_d1                  : 1;    // bit 1
            /// Allow D1 domain debug in Standby mode (DBGSTBY_D1)
            uint32_t debug_standby_d1               : 1;    // bit 2
            /// Allow D2 domain debug in Sleep mode (DBGSLEEP_D2)
            uint32_t debug_sleep_d2                 : 1;    // bit 3
            /// Allow D2 domain debug in Stop mode (DBGSTOP_D2)
            uint32_t debug_stop_d2                  : 1;    // bit 4
            /// Allow D2 domain debug in Standby mode (DBGSTBY_D2)
            uint32_t debug_standby_d2               : 1;    // bit 5
            /// (reserved)
            uint32_t                                : 1;    // bit 6
            /// Allow debug in D3 Stop mode (DBGSTOP_D3)
            uint32_t debug_stop_d3                  : 1;    // bit 7
            /// Allow debug in D3 Standby mode (DBGSTBY_D3)
            uint32_t debug_standby_d3               : 1;    // bit 8
            /// (reserved)
            uint32_t                                : 11;    // bits 9:19
            /// Trace port clock enable (TRACECLKEN)
            uint32_t trace_clock_enable             : 1;    // bit 20
            /// D1 debug clock enable (D1DBGCKEN)
            uint32_t domain1_debug_clock_enable     : 1;    // bit 21
            /// D3 debug clock enable (D3DBGCKEN)
            uint32_t domain3_debug_clock_enable     : 1;    // bit 22
            /// (reserved)
            uint32_t                                : 5;    // bits 23:27
            /// External trigger output enable (TRGOEN)
            uint32_t external_trigger_output_enable : 1;    // bit 28
            /// (reserved)
            uint32_t                                : 3;    // bits 29:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Control& operator=(Control&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Control volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Control const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint32_t.
        inline explicit operator uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint32_t
        inline explicit operator uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<Control>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Control) == 4UL, "Must be this exact size");
    /// DBGMCU APB3 peripheral freeze register (APB3FZ1)
    struct APB3Freeze1 final {
        /// Default Constructor
        APB3Freeze1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        APB3Freeze1(APB3Freeze1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        APB3Freeze1(APB3Freeze1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        APB3Freeze1(APB3Freeze1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit APB3Freeze1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit APB3Freeze1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~APB3Freeze1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                  : 6;    // bits 0:5
            /// WWDG1 stop in debug (WWDG1)
            uint32_t window_watchdog1 : 1;    // bit 6
            /// (reserved)
            uint32_t                  : 25;    // bits 7:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        APB3Freeze1& operator=(APB3Freeze1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(APB3Freeze1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(APB3Freeze1 const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint32_t.
        inline explicit operator uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint32_t
        inline explicit operator uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<APB3Freeze1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(APB3Freeze1) == 4UL, "Must be this exact size");
    /// DBGMCU APB1L peripheral freeze register (APB1LFZ1)
    struct APB1LowFreeze1 final {
        /// Default Constructor
        APB1LowFreeze1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        APB1LowFreeze1(APB1LowFreeze1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        APB1LowFreeze1(APB1LowFreeze1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        APB1LowFreeze1(APB1LowFreeze1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit APB1LowFreeze1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit APB1LowFreeze1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~APB1LowFreeze1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TIM2 stop in debug (DBG_TIM2)
            uint32_t timer2_stop_in_debug   : 1;    // bit 0
            /// TIM3 stop in debug (DBG_TIM3)
            uint32_t timer3_stop_in_debug   : 1;    // bit 1
            /// TIM4 stop in debug (DBG_TIM4)
            uint32_t timer4_stop_in_debug   : 1;    // bit 2
            /// TIM5 stop in debug (DBG_TIM5)
            uint32_t timer5_stop_in_debug   : 1;    // bit 3
            /// TIM6 stop in debug (DBG_TIM6)
            uint32_t timer6_stop_in_debug   : 1;    // bit 4
            /// TIM7 stop in debug (DBG_TIM7)
            uint32_t timer7_stop_in_debug   : 1;    // bit 5
            /// TIM12 stop in debug (DBG_TIM12)
            uint32_t timer12_stop_in_debug  : 1;    // bit 6
            /// TIM13 stop in debug (DBG_TIM13)
            uint32_t timer13_stop_in_debug  : 1;    // bit 7
            /// TIM14 stop in debug (DBG_TIM14)
            uint32_t timer14_stop_in_debug  : 1;    // bit 8
            /// LPTIM1 stop in debug (DBG_LPTIM1)
            uint32_t lptimer1_stop_in_debug : 1;    // bit 9
            /// (reserved)
            uint32_t                        : 11;    // bits 10:20
            /// I2C1 SMBUS timeout stop in debug (DBG_I2C1)
            uint32_t i2c1_stop_in_debug     : 1;    // bit 21
            /// I2C2 SMBUS timeout stop in debug (DBG_I2C2)
            uint32_t i2c2_stop_in_debug     : 1;    // bit 22
            /// I2C3 SMBUS timeout stop in debug (DBG_I2C3)
            uint32_t i2c3_stop_in_debug     : 1;    // bit 23
            /// (reserved)
            uint32_t                        : 8;    // bits 24:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        APB1LowFreeze1& operator=(APB1LowFreeze1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(APB1LowFreeze1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(APB1LowFreeze1 const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint32_t.
        inline explicit operator uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint32_t
        inline explicit operator uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<APB1LowFreeze1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(APB1LowFreeze1) == 4UL, "Must be this exact size");
    /// DBGMCU APB2 peripheral freeze register (APB2FZ1)
    struct APB2Freeze1 final {
        /// Default Constructor
        APB2Freeze1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        APB2Freeze1(APB2Freeze1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        APB2Freeze1(APB2Freeze1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        APB2Freeze1(APB2Freeze1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit APB2Freeze1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit APB2Freeze1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~APB2Freeze1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TIM1 stop in debug (DBG_TIM1)
            uint32_t timer1_stop_in_debug  : 1;    // bit 0
            /// TIM8 stop in debug (DBG_TIM8)
            uint32_t timer8_stop_in_debug  : 1;    // bit 1
            /// (reserved)
            uint32_t                       : 14;    // bits 2:15
            /// TIM15 stop in debug (DBG_TIM15)
            uint32_t timer15_stop_in_debug : 1;    // bit 16
            /// TIM16 stop in debug (DBG_TIM16)
            uint32_t timer16_stop_in_debug : 1;    // bit 17
            /// TIM17 stop in debug (DBG_TIM17)
            uint32_t timer17_stop_in_debug : 1;    // bit 18
            /// (reserved)
            uint32_t                       : 10;    // bits 19:28
            /// HRTIM stop in debug (DBG_HRTIM)
            uint32_t hrtim_stop_in_debug   : 1;    // bit 29
            /// (reserved)
            uint32_t                       : 2;    // bits 30:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        APB2Freeze1& operator=(APB2Freeze1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(APB2Freeze1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(APB2Freeze1 const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint32_t.
        inline explicit operator uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint32_t
        inline explicit operator uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<APB2Freeze1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(APB2Freeze1) == 4UL, "Must be this exact size");
    /// DBGMCU APB4 peripheral freeze register (APB4FZ1)
    struct APB4Freeze1 final {
        /// Default Constructor
        APB4Freeze1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        APB4Freeze1(APB4Freeze1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        APB4Freeze1(APB4Freeze1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        APB4Freeze1(APB4Freeze1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit APB4Freeze1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit APB4Freeze1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~APB4Freeze1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                        : 7;    // bits 0:6
            /// I2C4 SMBUS timeout stop in debug (DBG_I2C4)
            uint32_t i2c4_stop_in_debug     : 1;    // bit 7
            /// (reserved)
            uint32_t                        : 1;    // bit 8
            /// LPTIM2 stop in debug (DBG_LPTIM2)
            uint32_t lptimer2_stop_in_debug : 1;    // bit 9
            /// LPTIM2 stop in debug (DBG_LPTIM3)
            uint32_t lptimer3_stop_in_debug : 1;    // bit 10
            /// LPTIM4 stop in debug (DBG_LPTIM4)
            uint32_t lptimer4_stop_in_debug : 1;    // bit 11
            /// LPTIM5 stop in debug (DBG_LPTIM5)
            uint32_t lptimer5_stop_in_debug : 1;    // bit 12
            /// (reserved)
            uint32_t                        : 3;    // bits 13:15
            /// RTC stop in debug (DBG_RTC)
            uint32_t rtc_stop_in_debug      : 1;    // bit 16
            /// (reserved)
            uint32_t                        : 1;    // bit 17
            /// Independent watchdog for D1 stop in debug (DBG_WDGLSD1)
            uint32_t wdglsd1_stop_in_debug  : 1;    // bit 18
            /// (reserved)
            uint32_t                        : 13;    // bits 19:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        APB4Freeze1& operator=(APB4Freeze1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(APB4Freeze1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(APB4Freeze1 const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint32_t.
        inline explicit operator uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint32_t
        inline explicit operator uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<APB4Freeze1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(APB4Freeze1) == 4UL, "Must be this exact size");

    //+=MEMORY======================================+
    /// DBGMCU Identity Code Register (IDC)
    Identity identity;    // offset 0x0UL
    /// DBGMCU Configuration Register (CR)
    Control control;    // offset 0x4UL
    uint32_t : 32;      // offset 0x8UL
    uint32_t : 32;      // offset 0xcUL
    uint32_t : 32;      // offset 0x10UL
    uint32_t : 32;      // offset 0x14UL
    uint32_t : 32;      // offset 0x18UL
    uint32_t : 32;      // offset 0x1cUL
    uint32_t : 32;      // offset 0x20UL
    uint32_t : 32;      // offset 0x24UL
    uint32_t : 32;      // offset 0x28UL
    uint32_t : 32;      // offset 0x2cUL
    uint32_t : 32;      // offset 0x30UL
    /// DBGMCU APB3 peripheral freeze register (APB3FZ1)
    APB3Freeze1 apb3_freeze1;    // offset 0x34UL
    uint32_t : 32;               // offset 0x38UL
    /// DBGMCU APB1L peripheral freeze register (APB1LFZ1)
    APB1LowFreeze1 apb1_low_freeze1;    // offset 0x3cUL
    uint32_t : 32;                      // offset 0x40UL
    uint32_t : 32;                      // offset 0x44UL
    uint32_t : 32;                      // offset 0x48UL
    /// DBGMCU APB2 peripheral freeze register (APB2FZ1)
    APB2Freeze1 apb2_freeze1;    // offset 0x4cUL
    uint32_t : 32;               // offset 0x50UL
    /// DBGMCU APB4 peripheral freeze register (APB4FZ1)
    APB4Freeze1 apb4_freeze1;    // offset 0x54UL
    uint32_t : 32;               // offset 0x58UL
    uint32_t : 32;               // offset 0x5cUL
    uint32_t : 32;               // offset 0x60UL
    uint32_t : 32;               // offset 0x64UL
    uint32_t : 32;               // offset 0x68UL
    uint32_t : 32;               // offset 0x6cUL
    uint32_t : 32;               // offset 0x70UL
    uint32_t : 32;               // offset 0x74UL
    uint32_t : 32;               // offset 0x78UL
    uint32_t : 32;               // offset 0x7cUL
    uint32_t : 32;               // offset 0x80UL
    uint32_t : 32;               // offset 0x84UL
    uint32_t : 32;               // offset 0x88UL
    uint32_t : 32;               // offset 0x8cUL
    uint32_t : 32;               // offset 0x90UL
    uint32_t : 32;               // offset 0x94UL
    uint32_t : 32;               // offset 0x98UL
    uint32_t : 32;               // offset 0x9cUL
    uint32_t : 32;               // offset 0xa0UL
    uint32_t : 32;               // offset 0xa4UL
    uint32_t : 32;               // offset 0xa8UL
    uint32_t : 32;               // offset 0xacUL
    uint32_t : 32;               // offset 0xb0UL
    uint32_t : 32;               // offset 0xb4UL
    uint32_t : 32;               // offset 0xb8UL
    uint32_t : 32;               // offset 0xbcUL
    uint32_t : 32;               // offset 0xc0UL
    uint32_t : 32;               // offset 0xc4UL
    uint32_t : 32;               // offset 0xc8UL
    uint32_t : 32;               // offset 0xccUL
    uint32_t : 32;               // offset 0xd0UL
    uint32_t : 32;               // offset 0xd4UL
    uint32_t : 32;               // offset 0xd8UL
    uint32_t : 32;               // offset 0xdcUL
    uint32_t : 32;               // offset 0xe0UL
    uint32_t : 32;               // offset 0xe4UL
    uint32_t : 32;               // offset 0xe8UL
    uint32_t : 32;               // offset 0xecUL
    uint32_t : 32;               // offset 0xf0UL
    uint32_t : 32;               // offset 0xf4UL
    uint32_t : 32;               // offset 0xf8UL
    uint32_t : 32;               // offset 0xfcUL
    uint32_t : 32;               // offset 0x100UL
    uint32_t : 32;               // offset 0x104UL
    uint32_t : 32;               // offset 0x108UL
    uint32_t : 32;               // offset 0x10cUL
    uint32_t : 32;               // offset 0x110UL
    uint32_t : 32;               // offset 0x114UL
    uint32_t : 32;               // offset 0x118UL
    uint32_t : 32;               // offset 0x11cUL
    uint32_t : 32;               // offset 0x120UL
    uint32_t : 32;               // offset 0x124UL
    uint32_t : 32;               // offset 0x128UL
    uint32_t : 32;               // offset 0x12cUL
    uint32_t : 32;               // offset 0x130UL
    uint32_t : 32;               // offset 0x134UL
    uint32_t : 32;               // offset 0x138UL
    uint32_t : 32;               // offset 0x13cUL
    uint32_t : 32;               // offset 0x140UL
    uint32_t : 32;               // offset 0x144UL
    uint32_t : 32;               // offset 0x148UL
    uint32_t : 32;               // offset 0x14cUL
    uint32_t : 32;               // offset 0x150UL
    uint32_t : 32;               // offset 0x154UL
    uint32_t : 32;               // offset 0x158UL
    uint32_t : 32;               // offset 0x15cUL
    uint32_t : 32;               // offset 0x160UL
    uint32_t : 32;               // offset 0x164UL
    uint32_t : 32;               // offset 0x168UL
    uint32_t : 32;               // offset 0x16cUL
    uint32_t : 32;               // offset 0x170UL
    uint32_t : 32;               // offset 0x174UL
    uint32_t : 32;               // offset 0x178UL
    uint32_t : 32;               // offset 0x17cUL
    uint32_t : 32;               // offset 0x180UL
    uint32_t : 32;               // offset 0x184UL
    uint32_t : 32;               // offset 0x188UL
    uint32_t : 32;               // offset 0x18cUL
    uint32_t : 32;               // offset 0x190UL
    uint32_t : 32;               // offset 0x194UL
    uint32_t : 32;               // offset 0x198UL
    uint32_t : 32;               // offset 0x19cUL
    uint32_t : 32;               // offset 0x1a0UL
    uint32_t : 32;               // offset 0x1a4UL
    uint32_t : 32;               // offset 0x1a8UL
    uint32_t : 32;               // offset 0x1acUL
    uint32_t : 32;               // offset 0x1b0UL
    uint32_t : 32;               // offset 0x1b4UL
    uint32_t : 32;               // offset 0x1b8UL
    uint32_t : 32;               // offset 0x1bcUL
    uint32_t : 32;               // offset 0x1c0UL
    uint32_t : 32;               // offset 0x1c4UL
    uint32_t : 32;               // offset 0x1c8UL
    uint32_t : 32;               // offset 0x1ccUL
    uint32_t : 32;               // offset 0x1d0UL
    uint32_t : 32;               // offset 0x1d4UL
    uint32_t : 32;               // offset 0x1d8UL
    uint32_t : 32;               // offset 0x1dcUL
    uint32_t : 32;               // offset 0x1e0UL
    uint32_t : 32;               // offset 0x1e4UL
    uint32_t : 32;               // offset 0x1e8UL
    uint32_t : 32;               // offset 0x1ecUL
    uint32_t : 32;               // offset 0x1f0UL
    uint32_t : 32;               // offset 0x1f4UL
    uint32_t : 32;               // offset 0x1f8UL
    uint32_t : 32;               // offset 0x1fcUL
    uint32_t : 32;               // offset 0x200UL
    uint32_t : 32;               // offset 0x204UL
    uint32_t : 32;               // offset 0x208UL
    uint32_t : 32;               // offset 0x20cUL
    uint32_t : 32;               // offset 0x210UL
    uint32_t : 32;               // offset 0x214UL
    uint32_t : 32;               // offset 0x218UL
    uint32_t : 32;               // offset 0x21cUL
    uint32_t : 32;               // offset 0x220UL
    uint32_t : 32;               // offset 0x224UL
    uint32_t : 32;               // offset 0x228UL
    uint32_t : 32;               // offset 0x22cUL
    uint32_t : 32;               // offset 0x230UL
    uint32_t : 32;               // offset 0x234UL
    uint32_t : 32;               // offset 0x238UL
    uint32_t : 32;               // offset 0x23cUL
    uint32_t : 32;               // offset 0x240UL
    uint32_t : 32;               // offset 0x244UL
    uint32_t : 32;               // offset 0x248UL
    uint32_t : 32;               // offset 0x24cUL
    uint32_t : 32;               // offset 0x250UL
    uint32_t : 32;               // offset 0x254UL
    uint32_t : 32;               // offset 0x258UL
    uint32_t : 32;               // offset 0x25cUL
    uint32_t : 32;               // offset 0x260UL
    uint32_t : 32;               // offset 0x264UL
    uint32_t : 32;               // offset 0x268UL
    uint32_t : 32;               // offset 0x26cUL
    uint32_t : 32;               // offset 0x270UL
    uint32_t : 32;               // offset 0x274UL
    uint32_t : 32;               // offset 0x278UL
    uint32_t : 32;               // offset 0x27cUL
    uint32_t : 32;               // offset 0x280UL
    uint32_t : 32;               // offset 0x284UL
    uint32_t : 32;               // offset 0x288UL
    uint32_t : 32;               // offset 0x28cUL
    uint32_t : 32;               // offset 0x290UL
    uint32_t : 32;               // offset 0x294UL
    uint32_t : 32;               // offset 0x298UL
    uint32_t : 32;               // offset 0x29cUL
    uint32_t : 32;               // offset 0x2a0UL
    uint32_t : 32;               // offset 0x2a4UL
    uint32_t : 32;               // offset 0x2a8UL
    uint32_t : 32;               // offset 0x2acUL
    uint32_t : 32;               // offset 0x2b0UL
    uint32_t : 32;               // offset 0x2b4UL
    uint32_t : 32;               // offset 0x2b8UL
    uint32_t : 32;               // offset 0x2bcUL
    uint32_t : 32;               // offset 0x2c0UL
    uint32_t : 32;               // offset 0x2c4UL
    uint32_t : 32;               // offset 0x2c8UL
    uint32_t : 32;               // offset 0x2ccUL
    uint32_t : 32;               // offset 0x2d0UL
    uint32_t : 32;               // offset 0x2d4UL
    uint32_t : 32;               // offset 0x2d8UL
    uint32_t : 32;               // offset 0x2dcUL
    uint32_t : 32;               // offset 0x2e0UL
    uint32_t : 32;               // offset 0x2e4UL
    uint32_t : 32;               // offset 0x2e8UL
    uint32_t : 32;               // offset 0x2ecUL
    uint32_t : 32;               // offset 0x2f0UL
    uint32_t : 32;               // offset 0x2f4UL
    uint32_t : 32;               // offset 0x2f8UL
    uint32_t : 32;               // offset 0x2fcUL
    uint32_t : 32;               // offset 0x300UL
    uint32_t : 32;               // offset 0x304UL
    uint32_t : 32;               // offset 0x308UL
    uint32_t : 32;               // offset 0x30cUL
    uint32_t : 32;               // offset 0x310UL
    uint32_t : 32;               // offset 0x314UL
    uint32_t : 32;               // offset 0x318UL
    uint32_t : 32;               // offset 0x31cUL
    uint32_t : 32;               // offset 0x320UL
    uint32_t : 32;               // offset 0x324UL
    uint32_t : 32;               // offset 0x328UL
    uint32_t : 32;               // offset 0x32cUL
    uint32_t : 32;               // offset 0x330UL
    uint32_t : 32;               // offset 0x334UL
    uint32_t : 32;               // offset 0x338UL
    uint32_t : 32;               // offset 0x33cUL
    uint32_t : 32;               // offset 0x340UL
    uint32_t : 32;               // offset 0x344UL
    uint32_t : 32;               // offset 0x348UL
    uint32_t : 32;               // offset 0x34cUL
    uint32_t : 32;               // offset 0x350UL
    uint32_t : 32;               // offset 0x354UL
    uint32_t : 32;               // offset 0x358UL
    uint32_t : 32;               // offset 0x35cUL
    uint32_t : 32;               // offset 0x360UL
    uint32_t : 32;               // offset 0x364UL
    uint32_t : 32;               // offset 0x368UL
    uint32_t : 32;               // offset 0x36cUL
    uint32_t : 32;               // offset 0x370UL
    uint32_t : 32;               // offset 0x374UL
    uint32_t : 32;               // offset 0x378UL
    uint32_t : 32;               // offset 0x37cUL
    uint32_t : 32;               // offset 0x380UL
    uint32_t : 32;               // offset 0x384UL
    uint32_t : 32;               // offset 0x388UL
    uint32_t : 32;               // offset 0x38cUL
    uint32_t : 32;               // offset 0x390UL
    uint32_t : 32;               // offset 0x394UL
    uint32_t : 32;               // offset 0x398UL
    uint32_t : 32;               // offset 0x39cUL
    uint32_t : 32;               // offset 0x3a0UL
    uint32_t : 32;               // offset 0x3a4UL
    uint32_t : 32;               // offset 0x3a8UL
    uint32_t : 32;               // offset 0x3acUL
    uint32_t : 32;               // offset 0x3b0UL
    uint32_t : 32;               // offset 0x3b4UL
    uint32_t : 32;               // offset 0x3b8UL
    uint32_t : 32;               // offset 0x3bcUL
    uint32_t : 32;               // offset 0x3c0UL
    uint32_t : 32;               // offset 0x3c4UL
    uint32_t : 32;               // offset 0x3c8UL
    uint32_t : 32;               // offset 0x3ccUL
    uint32_t : 32;               // offset 0x3d0UL
    uint32_t : 32;               // offset 0x3d4UL
    uint32_t : 32;               // offset 0x3d8UL
    uint32_t : 32;               // offset 0x3dcUL
    uint32_t : 32;               // offset 0x3e0UL
    uint32_t : 32;               // offset 0x3e4UL
    uint32_t : 32;               // offset 0x3e8UL
    uint32_t : 32;               // offset 0x3ecUL
    uint32_t : 32;               // offset 0x3f0UL
    uint32_t : 32;               // offset 0x3f4UL
    uint32_t : 32;               // offset 0x3f8UL
    uint32_t : 32;               // offset 0x3fcUL
    //+=MEMORY======================================+
};
// Ensure the structure is in standard layout format
static_assert(std::is_standard_layout<Debug>::value, "Must be standard layout");
// Ensure the offsets are all correct
static_assert(offsetof(Debug, identity) == 0x0UL, "Must be located at this offset");
static_assert(offsetof(Debug, control) == 0x4UL, "Must be located at this offset");
static_assert(offsetof(Debug, apb3_freeze1) == 0x34UL, "Must be located at this offset");
static_assert(offsetof(Debug, apb1_low_freeze1) == 0x3cUL, "Must be located at this offset");
static_assert(offsetof(Debug, apb2_freeze1) == 0x4cUL, "Must be located at this offset");
static_assert(offsetof(Debug, apb4_freeze1) == 0x54UL, "Must be located at this offset");

// Ensure the sizeof the entire structure is correct.
static_assert(sizeof(Debug) == 0x400UL, "Must be this exact size");

/// The external volatile debug which is a memory mapped register or peripheral.
/// @note The address of the peripheral is set either by the linkerscript or by a unit test.
extern Debug volatile debug;
}    // namespace h7xx
}    // namespace stm32
#endif    // STM32_H7XX_DEBUG__HPP_


#ifndef STM32_REGISTERS_RESETANDCLOCKCONTROL_HPP_
#define STM32_REGISTERS_RESETANDCLOCKCONTROL_HPP_

/// @file
/// Auto Generated Structure Definitions for ResetAndClockControl from the Peripheralyzer.
/// @copyright

#include <cstdint>
#include <cstddef>
#include <type_traits>

namespace stm32 {
namespace registers {

/// Reset and clock control (RCC)
struct ResetAndClockControl final {
    /// clock control register (CR)
    struct Control final {
        /// Default Constructor
        Control() : whole{0u} {}
        /// Parameterized Constructor
        Control(std::uint32_t const& value) : whole{value} {}
        /// The internal bitfield for the register
        struct Fields final {
            /// Internal high-speed clock enable (HSION)
            std::uint32_t high_speed_internal_enable   : 1;    // bit 0
            /// Internal high-speed clock ready flag (HSIRDY)
            std::uint32_t high_speed_internal_ready    : 1;    // bit 1
            /// (reserved)
            std::uint32_t                              : 1;    // bit 2
            /// Internal high-speed clock trimming (HSITRIM)
            std::uint32_t high_speed_internal_trim     : 5;    // bits 3:7
            /// Internal high-speed clock calibration (HSICAL)
            std::uint32_t high_speed_internal_calib    : 8;    // bits 8:15
            /// HSE clock enable (HSEON)
            std::uint32_t high_speed_external_enable   : 1;    // bit 16
            /// HSE clock ready flag (HSERDY)
            std::uint32_t high_speed_external_ready    : 1;    // bit 17
            /// HSE clock bypass (HSEBYP)
            std::uint32_t high_speed_external_bypass   : 1;    // bit 18
            /// Clock security system enable (CSSON)
            std::uint32_t clock_security_system_enable : 1;    // bit 19
            /// (reserved)
            std::uint32_t                              : 4;    // bits 20:23
            /// Main PLL (PLL) enable (PLLON)
            std::uint32_t main_pll_enable              : 1;    // bit 24
            /// Main PLL (PLL) clock ready flag (PLLRDY)
            std::uint32_t main_pll_ready               : 1;    // bit 25
            /// PLLI2S enable (PLLI2SON)
            std::uint32_t i2s_pll_enable               : 1;    // bit 26
            /// PLLI2S clock ready flag (PLLI2SRDY)
            std::uint32_t i2s_pll_ready                : 1;    // bit 27
            /// (reserved)
            std::uint32_t                              : 4;    // bits 28:31
        };
        //==MEMORY==========================
        union {
            Fields bits;
            std::uint32_t whole;
        };
        //==================================
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Control volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Control const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type std::uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(std::uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an std::uint32_t.
        inline explicit operator std::uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an std::uint32_t
        inline explicit operator std::uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular
        /// instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<Control>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Control) == 4UL, "Must be this exact size");    /// PLL configuration register (PLLCFGR)
    struct PhaseLockLoopConfiguration final {
        /// Main PLL(PLL) and audio PLL (PLLI2S) entry clock source (PLLSRC)
        enum class MainPLLSource : std::uint32_t {
            HighSpeedInternal = 0,    ///<  (HSI_CLOCK)
            HighSpeedExternal = 1,    ///<  (HSE_CLOCK)
        };
        /// Default Constructor
        PhaseLockLoopConfiguration() : whole{0u} {}
        /// Parameterized Constructor
        PhaseLockLoopConfiguration(std::uint32_t const& value) : whole{value} {}
        /// The internal bitfield for the register
        struct Fields final {
            /// Division factor for the main PLL (PLL) and audio PLL (PLLI2S) input clock (PLLM)
            std::uint32_t main_pll_input_divisor : 6;    // bits 0:5
            /// Main PLL (PLL) multiplication factor for VCO (PLLN)
            std::uint32_t main_pll_vco_scalar    : 9;    // bits 6:14
            /// (reserved)
            std::uint32_t                        : 1;    // bit 15
            /// Main PLL (PLL) division factor for main system clock (PLLP)
            std::uint32_t main_pll_divider       : 2;    // bits 16:17
            /// (reserved)
            std::uint32_t                        : 4;    // bits 18:21
            /// Main PLL(PLL) and audio PLL (PLLI2S) entry clock source (PLLSRC)
            MainPLLSource main_pll_source        : 1;    // bit 22
            /// (reserved)
            std::uint32_t                        : 1;    // bit 23
            /// Main PLL (PLL) division factor for USB OTG FS, SDIO and random number generator clocks (PLLQ)
            std::uint32_t main_pll_divider2      : 4;    // bits 24:27
            /// (reserved)
            std::uint32_t                        : 4;    // bits 28:31
        };
        //==MEMORY==========================
        union {
            Fields bits;
            std::uint32_t whole;
        };
        //==================================
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PhaseLockLoopConfiguration volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PhaseLockLoopConfiguration const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type std::uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(std::uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an std::uint32_t.
        inline explicit operator std::uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an std::uint32_t
        inline explicit operator std::uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular
        /// instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<PhaseLockLoopConfiguration>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(
        sizeof(PhaseLockLoopConfiguration) == 4UL, "Must be this exact size"
    );    /// clock configuration register (CFGR)
    struct Configuration final {
        /// Microcontroller clock output 2 (MCO2)
        enum class Clock2Source : std::uint32_t {
            SystemClock = 0,          ///<  (SYS_CLOCK)
            PhaseLockLoopI2S = 1,     ///<  (PLL_I2S_CLOCK)
            HighSpeedExternal = 2,    ///<  (HSE_CLOCK)
            PhaseLockLoop = 3,        ///<  (PLL_CLOCK)
        };
        /// Microcontroller clock output 1 (MCO1)
        enum class Clock1Source : std::uint32_t {
            HighSpeedInternal = 0,    ///<  (HSI_CLOCK)
            LSE_CLOCK = 1,            ///<  (LSE_CLOCK)
            HighSpeedExternal = 2,    ///<  (HSE_CLOCK)
            PhaseLockLoop = 3,        ///<  (PLL_CLOCK)
        };
        /// System clock switch (SW)
        enum class SystemClockSwitch : std::uint32_t {
            HighSpeedInternal = 0,    ///<  (HSI_CLOCK)
            HighSpeedExternal = 1,    ///<  (HSE_CLOCK)
            PhaseLockLoop = 2,        ///<  (PLL_CLOCK)
        };
        /// Default Constructor
        Configuration() : whole{0u} {}
        /// Parameterized Constructor
        Configuration(std::uint32_t const& value) : whole{value} {}
        /// The internal bitfield for the register
        struct Fields final {
            /// System clock switch (SW)
            SystemClockSwitch system_clock_switch          : 2;    // bits 0:1
            /// System clock switch status (SWS)
            std::uint32_t system_clock_switch_status       : 2;    // bits 2:3
            /// AHB prescaler (HPRE)
            std::uint32_t ahb_divider                      : 4;    // bits 4:7
            /// (reserved)
            std::uint32_t                                  : 2;    // bits 8:9
            /// APB Low speed prescaler (APB1) (PPRE1)
            std::uint32_t apb_low_speed_divider            : 3;    // bits 10:12
            /// APB high-speed prescaler (APB2) (PPRE2)
            std::uint32_t apb_high_speed_divider           : 3;    // bits 13:15
            /// HSE division factor for RTC clock (RTCPRE)
            std::uint32_t rtc_divider                      : 5;    // bits 16:20
            /// Microcontroller clock output 1 (MCO1)
            Clock1Source micro_controller_clock_1_source   : 2;    // bits 21:22
            /// I2S clock selection (I2SSRC)
            std::uint32_t i2ssrc                           : 1;    // bit 23
            /// MCO1 prescaler (MCO1PRE)
            std::uint32_t micro_controller_clock_1_divider : 3;    // bits 24:26
            /// MCO2 prescaler (MCO2PRE)
            std::uint32_t micro_controller_clock_2_divider : 3;    // bits 27:29
            /// Microcontroller clock output 2 (MCO2)
            Clock2Source micro_controller_clock_2_source   : 2;    // bits 30:31
        };
        //==MEMORY==========================
        union {
            Fields bits;
            std::uint32_t whole;
        };
        //==================================
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Configuration volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Configuration const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type std::uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(std::uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an std::uint32_t.
        inline explicit operator std::uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an std::uint32_t
        inline explicit operator std::uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular
        /// instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<Configuration>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Configuration) == 4UL, "Must be this exact size");    /// clock interrupt register (CIR)
    struct ClockInterrupt final {
        /// Default Constructor
        ClockInterrupt() : whole{0u} {}
        /// Parameterized Constructor
        ClockInterrupt(std::uint32_t const& value) : whole{value} {}
        /// The internal bitfield for the register
        struct Fields final {
            /// LSI ready interrupt flag (LSIRDYF)
            std::uint32_t lsirdyf     : 1;    // bit 0
            /// LSE ready interrupt flag (LSERDYF)
            std::uint32_t lserdyf     : 1;    // bit 1
            /// HSI ready interrupt flag (HSIRDYF)
            std::uint32_t hsirdyf     : 1;    // bit 2
            /// HSE ready interrupt flag (HSERDYF)
            std::uint32_t hserdyf     : 1;    // bit 3
            /// Main PLL (PLL) ready interrupt flag (PLLRDYF)
            std::uint32_t pllrdyf     : 1;    // bit 4
            /// PLLI2S ready interrupt flag (PLLI2SRDYF)
            std::uint32_t plli2srdyf  : 1;    // bit 5
            /// (reserved)
            std::uint32_t             : 1;    // bit 6
            /// Clock security system interrupt flag (CSSF)
            std::uint32_t cssf        : 1;    // bit 7
            /// LSI ready interrupt enable (LSIRDYIE)
            std::uint32_t lsirdyie    : 1;    // bit 8
            /// LSE ready interrupt enable (LSERDYIE)
            std::uint32_t lserdyie    : 1;    // bit 9
            /// HSI ready interrupt enable (HSIRDYIE)
            std::uint32_t hsirdyie    : 1;    // bit 10
            /// HSE ready interrupt enable (HSERDYIE)
            std::uint32_t hserdyie    : 1;    // bit 11
            /// Main PLL (PLL) ready interrupt enable (PLLRDYIE)
            std::uint32_t pllrdyie    : 1;    // bit 12
            /// PLLI2S ready interrupt enable (PLLI2SRDYIE)
            std::uint32_t plli2srdyie : 1;    // bit 13
            /// (reserved)
            std::uint32_t             : 2;    // bits 14:15
            /// LSI ready interrupt clear (LSIRDYC)
            std::uint32_t lsirdyc     : 1;    // bit 16
            /// LSE ready interrupt clear (LSERDYC)
            std::uint32_t lserdyc     : 1;    // bit 17
            /// HSI ready interrupt clear (HSIRDYC)
            std::uint32_t hsirdyc     : 1;    // bit 18
            /// HSE ready interrupt clear (HSERDYC)
            std::uint32_t hserdyc     : 1;    // bit 19
            /// Main PLL(PLL) ready interrupt clear (PLLRDYC)
            std::uint32_t pllrdyc     : 1;    // bit 20
            /// PLLI2S ready interrupt clear (PLLI2SRDYC)
            std::uint32_t plli2srdyc  : 1;    // bit 21
            /// (reserved)
            std::uint32_t             : 1;    // bit 22
            /// Clock security system interrupt clear (CSSC)
            std::uint32_t cssc        : 1;    // bit 23
            /// (reserved)
            std::uint32_t             : 8;    // bits 24:31
        };
        //==MEMORY==========================
        union {
            Fields bits;
            std::uint32_t whole;
        };
        //==================================
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ClockInterrupt volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ClockInterrupt const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type std::uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(std::uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an std::uint32_t.
        inline explicit operator std::uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an std::uint32_t
        inline explicit operator std::uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular
        /// instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<ClockInterrupt>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(
        sizeof(ClockInterrupt) == 4UL, "Must be this exact size"
    );    /// AHB1 peripheral reset register (AHB1RSTR)
    struct AHB1PeripheralReset final {
        /// Default Constructor
        AHB1PeripheralReset() : whole{0u} {}
        /// Parameterized Constructor
        AHB1PeripheralReset(std::uint32_t const& value) : whole{value} {}
        /// The internal bitfield for the register
        struct Fields final {
            /// IO port A reset (GPIOARST)
            std::uint32_t gpioarst  : 1;    // bit 0
            /// IO port B reset (GPIOBRST)
            std::uint32_t gpiobrst  : 1;    // bit 1
            /// IO port C reset (GPIOCRST)
            std::uint32_t gpiocrst  : 1;    // bit 2
            /// IO port D reset (GPIODRST)
            std::uint32_t gpiodrst  : 1;    // bit 3
            /// IO port E reset (GPIOERST)
            std::uint32_t gpioerst  : 1;    // bit 4
            /// IO port F reset (GPIOFRST)
            std::uint32_t gpiofrst  : 1;    // bit 5
            /// IO port G reset (GPIOGRST)
            std::uint32_t gpiogrst  : 1;    // bit 6
            /// IO port H reset (GPIOHRST)
            std::uint32_t gpiohrst  : 1;    // bit 7
            /// IO port I reset (GPIOIRST)
            std::uint32_t gpioirst  : 1;    // bit 8
            /// (reserved)
            std::uint32_t           : 3;    // bits 9:11
            /// CRC reset (CRCRST)
            std::uint32_t crcrst    : 1;    // bit 12
            /// (reserved)
            std::uint32_t           : 8;    // bits 13:20
            /// DMA2 reset (DMA1RST)
            std::uint32_t dma1rst   : 1;    // bit 21
            /// DMA2 reset (DMA2RST)
            std::uint32_t dma2rst   : 1;    // bit 22
            /// (reserved)
            std::uint32_t           : 2;    // bits 23:24
            /// Ethernet MAC reset (ETHMACRST)
            std::uint32_t ethmacrst : 1;    // bit 25
            /// (reserved)
            std::uint32_t           : 3;    // bits 26:28
            /// USB OTG HS module reset (OTGHSRST)
            std::uint32_t otghsrst  : 1;    // bit 29
            /// (reserved)
            std::uint32_t           : 2;    // bits 30:31
        };
        //==MEMORY==========================
        union {
            Fields bits;
            std::uint32_t whole;
        };
        //==================================
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(AHB1PeripheralReset volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(AHB1PeripheralReset const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type std::uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(std::uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an std::uint32_t.
        inline explicit operator std::uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an std::uint32_t
        inline explicit operator std::uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular
        /// instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<AHB1PeripheralReset>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(
        sizeof(AHB1PeripheralReset) == 4UL, "Must be this exact size"
    );    /// AHB2 peripheral reset register (AHB2RSTR)
    struct AHB2PeripheralReset final {
        /// Default Constructor
        AHB2PeripheralReset() : whole{0u} {}
        /// Parameterized Constructor
        AHB2PeripheralReset(std::uint32_t const& value) : whole{value} {}
        /// The internal bitfield for the register
        struct Fields final {
            /// Camera interface reset (DCMIRST)
            std::uint32_t dcmirst  : 1;    // bit 0
            /// (reserved)
            std::uint32_t          : 5;    // bits 1:5
            /// Random number generator module reset (RNGRST)
            std::uint32_t rngrst   : 1;    // bit 6
            /// USB OTG FS module reset (OTGFSRST)
            std::uint32_t otgfsrst : 1;    // bit 7
            /// (reserved)
            std::uint32_t          : 24;    // bits 8:31
        };
        //==MEMORY==========================
        union {
            Fields bits;
            std::uint32_t whole;
        };
        //==================================
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(AHB2PeripheralReset volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(AHB2PeripheralReset const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type std::uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(std::uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an std::uint32_t.
        inline explicit operator std::uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an std::uint32_t
        inline explicit operator std::uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular
        /// instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<AHB2PeripheralReset>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(
        sizeof(AHB2PeripheralReset) == 4UL, "Must be this exact size"
    );    /// AHB3 peripheral reset register (AHB3RSTR)
    struct AHB3PeripheralReset final {
        /// Default Constructor
        AHB3PeripheralReset() : whole{0u} {}
        /// Parameterized Constructor
        AHB3PeripheralReset(std::uint32_t const& value) : whole{value} {}
        /// The internal bitfield for the register
        struct Fields final {
            /// Flexible static memory controller module reset (FSMCRST)
            std::uint32_t fsmcrst : 1;    // bit 0
            /// (reserved)
            std::uint32_t         : 31;    // bits 1:31
        };
        //==MEMORY==========================
        union {
            Fields bits;
            std::uint32_t whole;
        };
        //==================================
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(AHB3PeripheralReset volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(AHB3PeripheralReset const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type std::uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(std::uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an std::uint32_t.
        inline explicit operator std::uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an std::uint32_t
        inline explicit operator std::uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular
        /// instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<AHB3PeripheralReset>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(
        sizeof(AHB3PeripheralReset) == 4UL, "Must be this exact size"
    );    /// APB1 peripheral reset register (APB1RSTR)
    struct APB1PeripheralReset final {
        /// Default Constructor
        APB1PeripheralReset() : whole{0u} {}
        /// Parameterized Constructor
        APB1PeripheralReset(std::uint32_t const& value) : whole{value} {}
        /// The internal bitfield for the register
        struct Fields final {
            /// TIM2 reset (TIM2RST)
            std::uint32_t tim2rst    : 1;    // bit 0
            /// TIM3 reset (TIM3RST)
            std::uint32_t tim3rst    : 1;    // bit 1
            /// TIM4 reset (TIM4RST)
            std::uint32_t tim4rst    : 1;    // bit 2
            /// TIM5 reset (TIM5RST)
            std::uint32_t tim5rst    : 1;    // bit 3
            /// TIM6 reset (TIM6RST)
            std::uint32_t tim6rst    : 1;    // bit 4
            /// TIM7 reset (TIM7RST)
            std::uint32_t tim7rst    : 1;    // bit 5
            /// TIM12 reset (TIM12RST)
            std::uint32_t tim12rst   : 1;    // bit 6
            /// TIM13 reset (TIM13RST)
            std::uint32_t tim13rst   : 1;    // bit 7
            /// TIM14 reset (TIM14RST)
            std::uint32_t tim14rst   : 1;    // bit 8
            /// (reserved)
            std::uint32_t            : 2;    // bits 9:10
            /// Window watchdog reset (WWDGRST)
            std::uint32_t wwdgrst    : 1;    // bit 11
            /// (reserved)
            std::uint32_t            : 2;    // bits 12:13
            /// SPI 2 reset (SPI2RST)
            std::uint32_t spi2rst    : 1;    // bit 14
            /// SPI 3 reset (SPI3RST)
            std::uint32_t spi3_reset : 1;    // bit 15
            /// (reserved)
            std::uint32_t            : 1;    // bit 16
            /// USART 2 reset (UART2RST)
            std::uint32_t uart2rst   : 1;    // bit 17
            /// USART 3 reset (UART3RST)
            std::uint32_t uart3rst   : 1;    // bit 18
            /// USART 4 reset (UART4RST)
            std::uint32_t uart4rst   : 1;    // bit 19
            /// USART 5 reset (UART5RST)
            std::uint32_t uart5rst   : 1;    // bit 20
            /// I2C 1 reset (I2C1RST)
            std::uint32_t i2c1rst    : 1;    // bit 21
            /// I2C 2 reset (I2C2RST)
            std::uint32_t i2c2rst    : 1;    // bit 22
            /// I2C3 reset (I2C3RST)
            std::uint32_t i2c3rst    : 1;    // bit 23
            /// (reserved)
            std::uint32_t            : 1;    // bit 24
            /// CAN1 reset (CAN1RST)
            std::uint32_t can1rst    : 1;    // bit 25
            /// CAN2 reset (CAN2RST)
            std::uint32_t can2rst    : 1;    // bit 26
            /// (reserved)
            std::uint32_t            : 1;    // bit 27
            /// Power interface reset (PWRRST)
            std::uint32_t pwrrst     : 1;    // bit 28
            /// DAC reset (DACRST)
            std::uint32_t dacrst     : 1;    // bit 29
            /// (reserved)
            std::uint32_t            : 2;    // bits 30:31
        };
        //==MEMORY==========================
        union {
            Fields bits;
            std::uint32_t whole;
        };
        //==================================
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(APB1PeripheralReset volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(APB1PeripheralReset const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type std::uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(std::uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an std::uint32_t.
        inline explicit operator std::uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an std::uint32_t
        inline explicit operator std::uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular
        /// instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<APB1PeripheralReset>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(
        sizeof(APB1PeripheralReset) == 4UL, "Must be this exact size"
    );    /// APB2 peripheral reset register (APB2RSTR)
    struct APB2PeripheralReset final {
        /// Default Constructor
        APB2PeripheralReset() : whole{0u} {}
        /// Parameterized Constructor
        APB2PeripheralReset(std::uint32_t const& value) : whole{value} {}
        /// The internal bitfield for the register
        struct Fields final {
            /// TIM1 reset (TIM1RST)
            std::uint32_t tim1rst   : 1;    // bit 0
            /// TIM8 reset (TIM8RST)
            std::uint32_t tim8rst   : 1;    // bit 1
            /// (reserved)
            std::uint32_t           : 2;    // bits 2:3
            /// USART1 reset (USART1RST)
            std::uint32_t usart1rst : 1;    // bit 4
            /// USART6 reset (USART6RST)
            std::uint32_t usart6rst : 1;    // bit 5
            /// (reserved)
            std::uint32_t           : 2;    // bits 6:7
            /// ADC interface reset (common to all ADCs) (ADCRST)
            std::uint32_t adcrst    : 1;    // bit 8
            /// (reserved)
            std::uint32_t           : 2;    // bits 9:10
            /// SDIO reset (SDIORST)
            std::uint32_t sdiorst   : 1;    // bit 11
            /// SPI 1 reset (SPI1RST)
            std::uint32_t spi1rst   : 1;    // bit 12
            /// (reserved)
            std::uint32_t           : 1;    // bit 13
            /// System configuration controller reset (SYSCFGRST)
            std::uint32_t syscfgrst : 1;    // bit 14
            /// (reserved)
            std::uint32_t           : 1;    // bit 15
            /// TIM9 reset (TIM9RST)
            std::uint32_t tim9rst   : 1;    // bit 16
            /// TIM10 reset (TIM10RST)
            std::uint32_t tim10rst  : 1;    // bit 17
            /// TIM11 reset (TIM11RST)
            std::uint32_t tim11rst  : 1;    // bit 18
            /// (reserved)
            std::uint32_t           : 13;    // bits 19:31
        };
        //==MEMORY==========================
        union {
            Fields bits;
            std::uint32_t whole;
        };
        //==================================
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(APB2PeripheralReset volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(APB2PeripheralReset const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type std::uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(std::uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an std::uint32_t.
        inline explicit operator std::uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an std::uint32_t
        inline explicit operator std::uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular
        /// instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<APB2PeripheralReset>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(
        sizeof(APB2PeripheralReset) == 4UL, "Must be this exact size"
    );    /// AHB1 peripheral clock register (AHB1ENR)
    struct AHB1PeripheralClockEnable final {
        /// Default Constructor
        AHB1PeripheralClockEnable() : whole{0u} {}
        /// Parameterized Constructor
        AHB1PeripheralClockEnable(std::uint32_t const& value) : whole{value} {}
        /// The internal bitfield for the register
        struct Fields final {
            /// IO port A clock enable (GPIOAEN)
            std::uint32_t gpioaen     : 1;    // bit 0
            /// IO port B clock enable (GPIOBEN)
            std::uint32_t gpioben     : 1;    // bit 1
            /// IO port C clock enable (GPIOCEN)
            std::uint32_t gpiocen     : 1;    // bit 2
            /// IO port D clock enable (GPIODEN)
            std::uint32_t gpioden     : 1;    // bit 3
            /// IO port E clock enable (GPIOEEN)
            std::uint32_t gpioeen     : 1;    // bit 4
            /// IO port F clock enable (GPIOFEN)
            std::uint32_t gpiofen     : 1;    // bit 5
            /// IO port G clock enable (GPIOGEN)
            std::uint32_t gpiogen     : 1;    // bit 6
            /// IO port H clock enable (GPIOHEN)
            std::uint32_t gpiohen     : 1;    // bit 7
            /// IO port I clock enable (GPIOIEN)
            std::uint32_t gpioien     : 1;    // bit 8
            /// (reserved)
            std::uint32_t             : 3;    // bits 9:11
            /// CRC clock enable (CRCEN)
            std::uint32_t crcen       : 1;    // bit 12
            /// (reserved)
            std::uint32_t             : 5;    // bits 13:17
            /// Backup SRAM interface clock enable (BKPSRAMEN)
            std::uint32_t bkpsramen   : 1;    // bit 18
            /// (reserved)
            std::uint32_t             : 2;    // bits 19:20
            /// DMA1 clock enable (DMA1EN)
            std::uint32_t dma1en      : 1;    // bit 21
            /// DMA2 clock enable (DMA2EN)
            std::uint32_t dma2en      : 1;    // bit 22
            /// (reserved)
            std::uint32_t             : 2;    // bits 23:24
            /// Ethernet MAC clock enable (ETHMACEN)
            std::uint32_t ethmacen    : 1;    // bit 25
            /// Ethernet Transmission clock enable (ETHMACTXEN)
            std::uint32_t ethmactxen  : 1;    // bit 26
            /// Ethernet Reception clock enable (ETHMACRXEN)
            std::uint32_t ethmacrxen  : 1;    // bit 27
            /// Ethernet PTP clock enable (ETHMACPTPEN)
            std::uint32_t ethmacptpen : 1;    // bit 28
            /// USB OTG HS clock enable (OTGHSEN)
            std::uint32_t otghsen     : 1;    // bit 29
            /// USB OTG HSULPI clock enable (OTGHSULPIEN)
            std::uint32_t otghsulpien : 1;    // bit 30
            /// (reserved)
            std::uint32_t             : 1;    // bit 31
        };
        //==MEMORY==========================
        union {
            Fields bits;
            std::uint32_t whole;
        };
        //==================================
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(AHB1PeripheralClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(AHB1PeripheralClockEnable const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type std::uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(std::uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an std::uint32_t.
        inline explicit operator std::uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an std::uint32_t
        inline explicit operator std::uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular
        /// instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<AHB1PeripheralClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(
        sizeof(AHB1PeripheralClockEnable) == 4UL, "Must be this exact size"
    );    /// AHB2 peripheral clock enable register (AHB2ENR)
    struct AHB2PeripheralClockEnable final {
        /// Default Constructor
        AHB2PeripheralClockEnable() : whole{0u} {}
        /// Parameterized Constructor
        AHB2PeripheralClockEnable(std::uint32_t const& value) : whole{value} {}
        /// The internal bitfield for the register
        struct Fields final {
            /// Camera interface enable (DCMIEN)
            std::uint32_t dcmien  : 1;    // bit 0
            /// (reserved)
            std::uint32_t         : 5;    // bits 1:5
            /// Random number generator clock enable (RNGEN)
            std::uint32_t enable  : 1;    // bit 6
            /// USB OTG FS clock enable (OTGFSEN)
            std::uint32_t otgfsen : 1;    // bit 7
            /// (reserved)
            std::uint32_t         : 24;    // bits 8:31
        };
        //==MEMORY==========================
        union {
            Fields bits;
            std::uint32_t whole;
        };
        //==================================
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(AHB2PeripheralClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(AHB2PeripheralClockEnable const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type std::uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(std::uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an std::uint32_t.
        inline explicit operator std::uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an std::uint32_t
        inline explicit operator std::uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular
        /// instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<AHB2PeripheralClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(
        sizeof(AHB2PeripheralClockEnable) == 4UL, "Must be this exact size"
    );    /// AHB3 peripheral clock enable register (AHB3ENR)
    struct AHB3PeripheralClockEnable final {
        /// Default Constructor
        AHB3PeripheralClockEnable() : whole{0u} {}
        /// Parameterized Constructor
        AHB3PeripheralClockEnable(std::uint32_t const& value) : whole{value} {}
        /// The internal bitfield for the register
        struct Fields final {
            /// Flexible static memory controller module clock enable (FSMCEN)
            std::uint32_t fsmcen : 1;    // bit 0
            /// (reserved)
            std::uint32_t        : 31;    // bits 1:31
        };
        //==MEMORY==========================
        union {
            Fields bits;
            std::uint32_t whole;
        };
        //==================================
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(AHB3PeripheralClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(AHB3PeripheralClockEnable const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type std::uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(std::uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an std::uint32_t.
        inline explicit operator std::uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an std::uint32_t
        inline explicit operator std::uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular
        /// instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<AHB3PeripheralClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(
        sizeof(AHB3PeripheralClockEnable) == 4UL, "Must be this exact size"
    );    /// APB1 peripheral clock enable register (APB1ENR)
    struct APB1PeripheralClockEnable final {
        /// Default Constructor
        APB1PeripheralClockEnable() : whole{0u} {}
        /// Parameterized Constructor
        APB1PeripheralClockEnable(std::uint32_t const& value) : whole{value} {}
        /// The internal bitfield for the register
        struct Fields final {
            /// TIM2 clock enable (TIM2EN)
            std::uint32_t tim2en      : 1;    // bit 0
            /// TIM3 clock enable (TIM3EN)
            std::uint32_t tim3en      : 1;    // bit 1
            /// TIM4 clock enable (TIM4EN)
            std::uint32_t tim4en      : 1;    // bit 2
            /// TIM5 clock enable (TIM5EN)
            std::uint32_t tim5en      : 1;    // bit 3
            /// TIM6 clock enable (TIM6EN)
            std::uint32_t tim6en      : 1;    // bit 4
            /// TIM7 clock enable (TIM7EN)
            std::uint32_t tim7en      : 1;    // bit 5
            /// TIM12 clock enable (TIM12EN)
            std::uint32_t tim12en     : 1;    // bit 6
            /// TIM13 clock enable (TIM13EN)
            std::uint32_t tim13en     : 1;    // bit 7
            /// TIM14 clock enable (TIM14EN)
            std::uint32_t tim14en     : 1;    // bit 8
            /// (reserved)
            std::uint32_t             : 2;    // bits 9:10
            /// Window watchdog clock enable (WWDGEN)
            std::uint32_t wwdgen      : 1;    // bit 11
            /// (reserved)
            std::uint32_t             : 2;    // bits 12:13
            /// SPI2 clock enable (SPI2EN)
            std::uint32_t spi2en      : 1;    // bit 14
            /// SPI3 clock enable (SPI3EN)
            std::uint32_t spi3_enable : 1;    // bit 15
            /// (reserved)
            std::uint32_t             : 1;    // bit 16
            /// USART 2 clock enable (USART2EN)
            std::uint32_t usart2en    : 1;    // bit 17
            /// USART3 clock enable (USART3EN)
            std::uint32_t usart3en    : 1;    // bit 18
            /// UART4 clock enable (UART4EN)
            std::uint32_t uart4en     : 1;    // bit 19
            /// UART5 clock enable (UART5EN)
            std::uint32_t uart5en     : 1;    // bit 20
            /// I2C1 clock enable (I2C1EN)
            std::uint32_t i2c1en      : 1;    // bit 21
            /// I2C2 clock enable (I2C2EN)
            std::uint32_t i2c2en      : 1;    // bit 22
            /// I2C3 clock enable (I2C3EN)
            std::uint32_t i2c3en      : 1;    // bit 23
            /// (reserved)
            std::uint32_t             : 1;    // bit 24
            /// CAN 1 clock enable (CAN1EN)
            std::uint32_t can1en      : 1;    // bit 25
            /// CAN 2 clock enable (CAN2EN)
            std::uint32_t can2en      : 1;    // bit 26
            /// (reserved)
            std::uint32_t             : 1;    // bit 27
            /// Power interface clock enable (PWREN)
            std::uint32_t pwren       : 1;    // bit 28
            /// DAC interface clock enable (DACEN)
            std::uint32_t dacen       : 1;    // bit 29
            /// (reserved)
            std::uint32_t             : 2;    // bits 30:31
        };
        //==MEMORY==========================
        union {
            Fields bits;
            std::uint32_t whole;
        };
        //==================================
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(APB1PeripheralClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(APB1PeripheralClockEnable const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type std::uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(std::uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an std::uint32_t.
        inline explicit operator std::uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an std::uint32_t
        inline explicit operator std::uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular
        /// instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<APB1PeripheralClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(
        sizeof(APB1PeripheralClockEnable) == 4UL, "Must be this exact size"
    );    /// APB2 peripheral clock enable register (APB2ENR)
    struct APB2PeripheralClockEnable final {
        /// Default Constructor
        APB2PeripheralClockEnable() : whole{0u} {}
        /// Parameterized Constructor
        APB2PeripheralClockEnable(std::uint32_t const& value) : whole{value} {}
        /// The internal bitfield for the register
        struct Fields final {
            /// TIM1 clock enable (TIM1EN)
            std::uint32_t tim1en   : 1;    // bit 0
            /// TIM8 clock enable (TIM8EN)
            std::uint32_t tim8en   : 1;    // bit 1
            /// (reserved)
            std::uint32_t          : 2;    // bits 2:3
            /// USART1 clock enable (USART1EN)
            std::uint32_t usart1en : 1;    // bit 4
            /// USART6 clock enable (USART6EN)
            std::uint32_t usart6en : 1;    // bit 5
            /// (reserved)
            std::uint32_t          : 2;    // bits 6:7
            /// ADC1 clock enable (ADC1EN)
            std::uint32_t adc1en   : 1;    // bit 8
            /// ADC2 clock enable (ADC2EN)
            std::uint32_t adc2en   : 1;    // bit 9
            /// ADC3 clock enable (ADC3EN)
            std::uint32_t adc3en   : 1;    // bit 10
            /// SDIO clock enable (SDIOEN)
            std::uint32_t sdioen   : 1;    // bit 11
            /// SPI1 clock enable (SPI1EN)
            std::uint32_t spi1en   : 1;    // bit 12
            /// (reserved)
            std::uint32_t          : 1;    // bit 13
            /// System configuration controller clock enable (SYSCFGEN)
            std::uint32_t syscfgen : 1;    // bit 14
            /// (reserved)
            std::uint32_t          : 1;    // bit 15
            /// TIM9 clock enable (TIM9EN)
            std::uint32_t tim9en   : 1;    // bit 16
            /// TIM10 clock enable (TIM10EN)
            std::uint32_t tim10en  : 1;    // bit 17
            /// TIM11 clock enable (TIM11EN)
            std::uint32_t tim11en  : 1;    // bit 18
            /// (reserved)
            std::uint32_t          : 13;    // bits 19:31
        };
        //==MEMORY==========================
        union {
            Fields bits;
            std::uint32_t whole;
        };
        //==================================
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(APB2PeripheralClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(APB2PeripheralClockEnable const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type std::uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(std::uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an std::uint32_t.
        inline explicit operator std::uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an std::uint32_t
        inline explicit operator std::uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular
        /// instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<APB2PeripheralClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(
        sizeof(APB2PeripheralClockEnable) == 4UL, "Must be this exact size"
    );    /// AHB1 peripheral clock enable in low power mode register (AHB1LPENR)
    struct AHB1PeripheralLowPowerEnable final {
        /// Default Constructor
        AHB1PeripheralLowPowerEnable() : whole{0u} {}
        /// Parameterized Constructor
        AHB1PeripheralLowPowerEnable(std::uint32_t const& value) : whole{value} {}
        /// The internal bitfield for the register
        struct Fields final {
            /// IO port A clock enable during sleep mode (GPIOALPEN)
            std::uint32_t gpioalpen     : 1;    // bit 0
            /// IO port B clock enable during Sleep mode (GPIOBLPEN)
            std::uint32_t gpioblpen     : 1;    // bit 1
            /// IO port C clock enable during Sleep mode (GPIOCLPEN)
            std::uint32_t gpioclpen     : 1;    // bit 2
            /// IO port D clock enable during Sleep mode (GPIODLPEN)
            std::uint32_t gpiodlpen     : 1;    // bit 3
            /// IO port E clock enable during Sleep mode (GPIOELPEN)
            std::uint32_t gpioelpen     : 1;    // bit 4
            /// IO port F clock enable during Sleep mode (GPIOFLPEN)
            std::uint32_t gpioflpen     : 1;    // bit 5
            /// IO port G clock enable during Sleep mode (GPIOGLPEN)
            std::uint32_t gpioglpen     : 1;    // bit 6
            /// IO port H clock enable during Sleep mode (GPIOHLPEN)
            std::uint32_t gpiohlpen     : 1;    // bit 7
            /// IO port I clock enable during Sleep mode (GPIOILPEN)
            std::uint32_t gpioilpen     : 1;    // bit 8
            /// (reserved)
            std::uint32_t               : 3;    // bits 9:11
            /// CRC clock enable during Sleep mode (CRCLPEN)
            std::uint32_t crclpen       : 1;    // bit 12
            /// (reserved)
            std::uint32_t               : 2;    // bits 13:14
            /// Flash interface clock enable during Sleep mode (FLITFLPEN)
            std::uint32_t flitflpen     : 1;    // bit 15
            /// SRAM 1interface clock enable during Sleep mode (SRAM1LPEN)
            std::uint32_t sram1lpen     : 1;    // bit 16
            /// SRAM 2 interface clock enable during Sleep mode (SRAM2LPEN)
            std::uint32_t sram2lpen     : 1;    // bit 17
            /// Backup SRAM interface clock enable during Sleep mode (BKPSRAMLPEN)
            std::uint32_t bkpsramlpen   : 1;    // bit 18
            /// (reserved)
            std::uint32_t               : 2;    // bits 19:20
            /// DMA1 clock enable during Sleep mode (DMA1LPEN)
            std::uint32_t dma1lpen      : 1;    // bit 21
            /// DMA2 clock enable during Sleep mode (DMA2LPEN)
            std::uint32_t dma2lpen      : 1;    // bit 22
            /// (reserved)
            std::uint32_t               : 2;    // bits 23:24
            /// Ethernet MAC clock enable during Sleep mode (ETHMACLPEN)
            std::uint32_t ethmaclpen    : 1;    // bit 25
            /// Ethernet transmission clock enable during Sleep mode (ETHMACTXLPEN)
            std::uint32_t ethmactxlpen  : 1;    // bit 26
            /// Ethernet reception clock enable during Sleep mode (ETHMACRXLPEN)
            std::uint32_t ethmacrxlpen  : 1;    // bit 27
            /// Ethernet PTP clock enable during Sleep mode (ETHMACPTPLPEN)
            std::uint32_t ethmacptplpen : 1;    // bit 28
            /// USB OTG HS clock enable during Sleep mode (OTGHSLPEN)
            std::uint32_t otghslpen     : 1;    // bit 29
            /// USB OTG HS ULPI clock enable during Sleep mode (OTGHSULPILPEN)
            std::uint32_t otghsulpilpen : 1;    // bit 30
            /// (reserved)
            std::uint32_t               : 1;    // bit 31
        };
        //==MEMORY==========================
        union {
            Fields bits;
            std::uint32_t whole;
        };
        //==================================
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(AHB1PeripheralLowPowerEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(AHB1PeripheralLowPowerEnable const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type std::uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(std::uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an std::uint32_t.
        inline explicit operator std::uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an std::uint32_t
        inline explicit operator std::uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular
        /// instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<AHB1PeripheralLowPowerEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(
        sizeof(AHB1PeripheralLowPowerEnable) == 4UL, "Must be this exact size"
    );    /// AHB2 peripheral clock enable in low power mode register (AHB2LPENR)
    struct AHB2PeripheralLowPowerEnable final {
        /// Default Constructor
        AHB2PeripheralLowPowerEnable() : whole{0u} {}
        /// Parameterized Constructor
        AHB2PeripheralLowPowerEnable(std::uint32_t const& value) : whole{value} {}
        /// The internal bitfield for the register
        struct Fields final {
            /// Camera interface enable during Sleep mode (DCMILPEN)
            std::uint32_t dcmilpen  : 1;    // bit 0
            /// (reserved)
            std::uint32_t           : 5;    // bits 1:5
            /// Random number generator clock enable during Sleep mode (RNGLPEN)
            std::uint32_t rnglpen   : 1;    // bit 6
            /// USB OTG FS clock enable during Sleep mode (OTGFSLPEN)
            std::uint32_t otgfslpen : 1;    // bit 7
            /// (reserved)
            std::uint32_t           : 24;    // bits 8:31
        };
        //==MEMORY==========================
        union {
            Fields bits;
            std::uint32_t whole;
        };
        //==================================
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(AHB2PeripheralLowPowerEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(AHB2PeripheralLowPowerEnable const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type std::uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(std::uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an std::uint32_t.
        inline explicit operator std::uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an std::uint32_t
        inline explicit operator std::uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular
        /// instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<AHB2PeripheralLowPowerEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(
        sizeof(AHB2PeripheralLowPowerEnable) == 4UL, "Must be this exact size"
    );    /// AHB3 peripheral clock enable in low power mode register (AHB3LPENR)
    struct AHB3PeripheralLowPowerEnable final {
        /// Default Constructor
        AHB3PeripheralLowPowerEnable() : whole{0u} {}
        /// Parameterized Constructor
        AHB3PeripheralLowPowerEnable(std::uint32_t const& value) : whole{value} {}
        /// The internal bitfield for the register
        struct Fields final {
            /// Flexible static memory controller module clock enable during Sleep mode (FSMCLPEN)
            std::uint32_t fsmclpen : 1;    // bit 0
            /// (reserved)
            std::uint32_t          : 31;    // bits 1:31
        };
        //==MEMORY==========================
        union {
            Fields bits;
            std::uint32_t whole;
        };
        //==================================
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(AHB3PeripheralLowPowerEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(AHB3PeripheralLowPowerEnable const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type std::uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(std::uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an std::uint32_t.
        inline explicit operator std::uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an std::uint32_t
        inline explicit operator std::uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular
        /// instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<AHB3PeripheralLowPowerEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(
        sizeof(AHB3PeripheralLowPowerEnable) == 4UL, "Must be this exact size"
    );    /// APB1 peripheral clock enable in low power mode register (APB1LPENR)
    struct APB1PeripheralLowPowerEnable final {
        /// Default Constructor
        APB1PeripheralLowPowerEnable() : whole{0u} {}
        /// Parameterized Constructor
        APB1PeripheralLowPowerEnable(std::uint32_t const& value) : whole{value} {}
        /// The internal bitfield for the register
        struct Fields final {
            /// TIM2 clock enable during Sleep mode (TIM2LPEN)
            std::uint32_t tim2lpen             : 1;    // bit 0
            /// TIM3 clock enable during Sleep mode (TIM3LPEN)
            std::uint32_t tim3lpen             : 1;    // bit 1
            /// TIM4 clock enable during Sleep mode (TIM4LPEN)
            std::uint32_t tim4lpen             : 1;    // bit 2
            /// TIM5 clock enable during Sleep mode (TIM5LPEN)
            std::uint32_t tim5lpen             : 1;    // bit 3
            /// TIM6 clock enable during Sleep mode (TIM6LPEN)
            std::uint32_t tim6lpen             : 1;    // bit 4
            /// TIM7 clock enable during Sleep mode (TIM7LPEN)
            std::uint32_t tim7lpen             : 1;    // bit 5
            /// TIM12 clock enable during Sleep mode (TIM12LPEN)
            std::uint32_t tim12lpen            : 1;    // bit 6
            /// TIM13 clock enable during Sleep mode (TIM13LPEN)
            std::uint32_t tim13lpen            : 1;    // bit 7
            /// TIM14 clock enable during Sleep mode (TIM14LPEN)
            std::uint32_t tim14lpen            : 1;    // bit 8
            /// (reserved)
            std::uint32_t                      : 2;    // bits 9:10
            /// Window watchdog clock enable during Sleep mode (WWDGLPEN)
            std::uint32_t wwdglpen             : 1;    // bit 11
            /// (reserved)
            std::uint32_t                      : 2;    // bits 12:13
            /// SPI2 clock enable during Sleep mode (SPI2LPEN)
            std::uint32_t spi2lpen             : 1;    // bit 14
            /// SPI3 clock enable during Sleep mode (SPI3LPEN)
            std::uint32_t spi3_lowpower_enable : 1;    // bit 15
            /// (reserved)
            std::uint32_t                      : 1;    // bit 16
            /// USART2 clock enable during Sleep mode (USART2LPEN)
            std::uint32_t usart2lpen           : 1;    // bit 17
            /// USART3 clock enable during Sleep mode (USART3LPEN)
            std::uint32_t usart3lpen           : 1;    // bit 18
            /// UART4 clock enable during Sleep mode (UART4LPEN)
            std::uint32_t uart4lpen            : 1;    // bit 19
            /// UART5 clock enable during Sleep mode (UART5LPEN)
            std::uint32_t uart5lpen            : 1;    // bit 20
            /// I2C1 clock enable during Sleep mode (I2C1LPEN)
            std::uint32_t i2c1lpen             : 1;    // bit 21
            /// I2C2 clock enable during Sleep mode (I2C2LPEN)
            std::uint32_t i2c2lpen             : 1;    // bit 22
            /// I2C3 clock enable during Sleep mode (I2C3LPEN)
            std::uint32_t i2c3lpen             : 1;    // bit 23
            /// (reserved)
            std::uint32_t                      : 1;    // bit 24
            /// CAN 1 clock enable during Sleep mode (CAN1LPEN)
            std::uint32_t can1lpen             : 1;    // bit 25
            /// CAN 2 clock enable during Sleep mode (CAN2LPEN)
            std::uint32_t can2lpen             : 1;    // bit 26
            /// (reserved)
            std::uint32_t                      : 1;    // bit 27
            /// Power interface clock enable during Sleep mode (PWRLPEN)
            std::uint32_t pwrlpen              : 1;    // bit 28
            /// DAC interface clock enable during Sleep mode (DACLPEN)
            std::uint32_t daclpen              : 1;    // bit 29
            /// (reserved)
            std::uint32_t                      : 2;    // bits 30:31
        };
        //==MEMORY==========================
        union {
            Fields bits;
            std::uint32_t whole;
        };
        //==================================
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(APB1PeripheralLowPowerEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(APB1PeripheralLowPowerEnable const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type std::uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(std::uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an std::uint32_t.
        inline explicit operator std::uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an std::uint32_t
        inline explicit operator std::uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular
        /// instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<APB1PeripheralLowPowerEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(
        sizeof(APB1PeripheralLowPowerEnable) == 4UL, "Must be this exact size"
    );    /// APB2 peripheral clock enabled in low power mode register (APB2LPENR)
    struct APB2PeripheralLowPowerEnable final {
        /// Default Constructor
        APB2PeripheralLowPowerEnable() : whole{0u} {}
        /// Parameterized Constructor
        APB2PeripheralLowPowerEnable(std::uint32_t const& value) : whole{value} {}
        /// The internal bitfield for the register
        struct Fields final {
            /// TIM1 clock enable during Sleep mode (TIM1LPEN)
            std::uint32_t tim1lpen   : 1;    // bit 0
            /// TIM8 clock enable during Sleep mode (TIM8LPEN)
            std::uint32_t tim8lpen   : 1;    // bit 1
            /// (reserved)
            std::uint32_t            : 2;    // bits 2:3
            /// USART1 clock enable during Sleep mode (USART1LPEN)
            std::uint32_t usart1lpen : 1;    // bit 4
            /// USART6 clock enable during Sleep mode (USART6LPEN)
            std::uint32_t usart6lpen : 1;    // bit 5
            /// (reserved)
            std::uint32_t            : 2;    // bits 6:7
            /// ADC1 clock enable during Sleep mode (ADC1LPEN)
            std::uint32_t adc1lpen   : 1;    // bit 8
            /// ADC2 clock enable during Sleep mode (ADC2LPEN)
            std::uint32_t adc2lpen   : 1;    // bit 9
            /// ADC 3 clock enable during Sleep mode (ADC3LPEN)
            std::uint32_t adc3lpen   : 1;    // bit 10
            /// SDIO clock enable during Sleep mode (SDIOLPEN)
            std::uint32_t sdiolpen   : 1;    // bit 11
            /// SPI 1 clock enable during Sleep mode (SPI1LPEN)
            std::uint32_t spi1lpen   : 1;    // bit 12
            /// (reserved)
            std::uint32_t            : 1;    // bit 13
            /// System configuration controller clock enable during Sleep mode (SYSCFGLPEN)
            std::uint32_t syscfglpen : 1;    // bit 14
            /// (reserved)
            std::uint32_t            : 1;    // bit 15
            /// TIM9 clock enable during sleep mode (TIM9LPEN)
            std::uint32_t tim9lpen   : 1;    // bit 16
            /// TIM10 clock enable during Sleep mode (TIM10LPEN)
            std::uint32_t tim10lpen  : 1;    // bit 17
            /// TIM11 clock enable during Sleep mode (TIM11LPEN)
            std::uint32_t tim11lpen  : 1;    // bit 18
            /// (reserved)
            std::uint32_t            : 13;    // bits 19:31
        };
        //==MEMORY==========================
        union {
            Fields bits;
            std::uint32_t whole;
        };
        //==================================
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(APB2PeripheralLowPowerEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(APB2PeripheralLowPowerEnable const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type std::uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(std::uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an std::uint32_t.
        inline explicit operator std::uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an std::uint32_t
        inline explicit operator std::uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular
        /// instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<APB2PeripheralLowPowerEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(
        sizeof(APB2PeripheralLowPowerEnable) == 4UL, "Must be this exact size"
    );    /// Backup domain control register (BDCR)
    struct BackupDomainControl final {
        /// Default Constructor
        BackupDomainControl() : whole{0u} {}
        /// Parameterized Constructor
        BackupDomainControl(std::uint32_t const& value) : whole{value} {}
        /// The internal bitfield for the register
        struct Fields final {
            /// External low-speed oscillator enable (LSEON)
            std::uint32_t lseon   : 1;    // bit 0
            /// External low-speed oscillator ready (LSERDY)
            std::uint32_t lserdy  : 1;    // bit 1
            /// External low-speed oscillator bypass (LSEBYP)
            std::uint32_t lsebyp  : 1;    // bit 2
            /// (reserved)
            std::uint32_t         : 5;    // bits 3:7
            /// RTC clock source selection (RTCSEL0)
            std::uint32_t rtcsel0 : 1;    // bit 8
            /// RTC clock source selection (RTCSEL1)
            std::uint32_t rtcsel1 : 1;    // bit 9
            /// (reserved)
            std::uint32_t         : 5;    // bits 10:14
            /// RTC clock enable (RTCEN)
            std::uint32_t rtcen   : 1;    // bit 15
            /// Backup domain software reset (BDRST)
            std::uint32_t bdrst   : 1;    // bit 16
            /// (reserved)
            std::uint32_t         : 15;    // bits 17:31
        };
        //==MEMORY==========================
        union {
            Fields bits;
            std::uint32_t whole;
        };
        //==================================
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(BackupDomainControl volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(BackupDomainControl const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type std::uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(std::uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an std::uint32_t.
        inline explicit operator std::uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an std::uint32_t
        inline explicit operator std::uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular
        /// instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<BackupDomainControl>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(
        sizeof(BackupDomainControl) == 4UL, "Must be this exact size"
    );    /// clock control & status register (CSR)
    struct Status final {
        /// Default Constructor
        Status() : whole{0u} {}
        /// Parameterized Constructor
        Status(std::uint32_t const& value) : whole{value} {}
        /// The internal bitfield for the register
        struct Fields final {
            /// Internal low-speed oscillator enable (LSION)
            std::uint32_t lsion    : 1;    // bit 0
            /// Internal low-speed oscillator ready (LSIRDY)
            std::uint32_t lsirdy   : 1;    // bit 1
            /// (reserved)
            std::uint32_t          : 22;    // bits 2:23
            /// Remove reset flag (RMVF)
            std::uint32_t rmvf     : 1;    // bit 24
            /// BOR reset flag (BORRSTF)
            std::uint32_t borrstf  : 1;    // bit 25
            /// PIN reset flag (PADRSTF)
            std::uint32_t padrstf  : 1;    // bit 26
            /// POR/PDR reset flag (PORRSTF)
            std::uint32_t porrstf  : 1;    // bit 27
            /// Software reset flag (SFTRSTF)
            std::uint32_t sftrstf  : 1;    // bit 28
            /// Independent watchdog reset flag (WDGRSTF)
            std::uint32_t wdgrstf  : 1;    // bit 29
            /// Window watchdog reset flag (WWDGRSTF)
            std::uint32_t wwdgrstf : 1;    // bit 30
            /// Low-power reset flag (LPWRRSTF)
            std::uint32_t lpwrrstf : 1;    // bit 31
        };
        //==MEMORY==========================
        union {
            Fields bits;
            std::uint32_t whole;
        };
        //==================================
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Status volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Status const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type std::uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(std::uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an std::uint32_t.
        inline explicit operator std::uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an std::uint32_t
        inline explicit operator std::uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular
        /// instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<Status>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(
        sizeof(Status) == 4UL, "Must be this exact size"
    );    /// spread spectrum clock generation register (SSCGR)
    struct SpreadSpectrumClockGeneration final {
        /// Default Constructor
        SpreadSpectrumClockGeneration() : whole{0u} {}
        /// Parameterized Constructor
        SpreadSpectrumClockGeneration(std::uint32_t const& value) : whole{value} {}
        /// The internal bitfield for the register
        struct Fields final {
            /// Modulation period (MODPER)
            std::uint32_t modper    : 13;    // bits 0:12
            /// Incrementation step (INCSTEP)
            std::uint32_t incstep   : 15;    // bits 13:27
            /// (reserved)
            std::uint32_t           : 2;    // bits 28:29
            /// Spread Select (SPREADSEL)
            std::uint32_t spreadsel : 1;    // bit 30
            /// Spread spectrum modulation enable (SSCGEN)
            std::uint32_t sscgen    : 1;    // bit 31
        };
        //==MEMORY==========================
        union {
            Fields bits;
            std::uint32_t whole;
        };
        //==================================
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(SpreadSpectrumClockGeneration volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(SpreadSpectrumClockGeneration const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type std::uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(std::uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an std::uint32_t.
        inline explicit operator std::uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an std::uint32_t
        inline explicit operator std::uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular
        /// instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<SpreadSpectrumClockGeneration>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(
        sizeof(SpreadSpectrumClockGeneration) == 4UL, "Must be this exact size"
    );    /// PLLI2S configuration register (PLLI2SCFGR)
    struct PhaseLockLoopI2SConfiguration final {
        /// Default Constructor
        PhaseLockLoopI2SConfiguration() : whole{0u} {}
        /// Parameterized Constructor
        PhaseLockLoopI2SConfiguration(std::uint32_t const& value) : whole{value} {}
        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            std::uint32_t          : 6;    // bits 0:5
            /// PLLI2S multiplication factor for VCO (PLLI2SNx)
            std::uint32_t plli2snx : 9;    // bits 6:14
            /// (reserved)
            std::uint32_t          : 13;    // bits 15:27
            /// PLLI2S division factor for I2S clocks (PLLI2SRx)
            std::uint32_t plli2srx : 3;    // bits 28:30
            /// (reserved)
            std::uint32_t          : 1;    // bit 31
        };
        //==MEMORY==========================
        union {
            Fields bits;
            std::uint32_t whole;
        };
        //==================================
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PhaseLockLoopI2SConfiguration volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PhaseLockLoopI2SConfiguration const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type std::uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(std::uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an std::uint32_t.
        inline explicit operator std::uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an std::uint32_t
        inline explicit operator std::uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular
        /// instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<PhaseLockLoopI2SConfiguration>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(PhaseLockLoopI2SConfiguration) == 4UL, "Must be this exact size");

    /// clock control register (CR)
    Control control;    // offset 0x0UL
    /// PLL configuration register (PLLCFGR)
    PhaseLockLoopConfiguration pll_configuration;    // offset 0x4UL
    /// clock configuration register (CFGR)
    Configuration configuration;    // offset 0x8UL
    /// clock interrupt register (CIR)
    ClockInterrupt clock_interrupt;    // offset 0xcUL
    /// AHB1 peripheral reset register (AHB1RSTR)
    AHB1PeripheralReset ahb1_peripheral_reset;    // offset 0x10UL
    /// AHB2 peripheral reset register (AHB2RSTR)
    AHB2PeripheralReset ahb2_peripheral_reset;    // offset 0x14UL
    /// AHB3 peripheral reset register (AHB3RSTR)
    AHB3PeripheralReset ahb3_peripheral_reset;    // offset 0x18UL
    std::uint32_t : 32;                           // offset 0x1cUL
    /// APB1 peripheral reset register (APB1RSTR)
    APB1PeripheralReset apb1_peripheral_reset;    // offset 0x20UL
    /// APB2 peripheral reset register (APB2RSTR)
    APB2PeripheralReset apb2_peripheral_reset;    // offset 0x24UL
    std::uint32_t : 32;                           // offset 0x28UL
    std::uint32_t : 32;                           // offset 0x2cUL
    /// AHB1 peripheral clock register (AHB1ENR)
    AHB1PeripheralClockEnable ahb1_peripheral_clock_enable;    // offset 0x30UL
    /// AHB2 peripheral clock enable register (AHB2ENR)
    AHB2PeripheralClockEnable ahb2_peripheral_clock_enable;    // offset 0x34UL
    /// AHB3 peripheral clock enable register (AHB3ENR)
    AHB3PeripheralClockEnable ahb3_peripheral_clock_enable;    // offset 0x38UL
    std::uint32_t : 32;                                        // offset 0x3cUL
    /// APB1 peripheral clock enable register (APB1ENR)
    APB1PeripheralClockEnable apb1_peripheral_clock_enable;    // offset 0x40UL
    /// APB2 peripheral clock enable register (APB2ENR)
    APB2PeripheralClockEnable apb2_peripheral_clock_enable;    // offset 0x44UL
    std::uint32_t : 32;                                        // offset 0x48UL
    std::uint32_t : 32;                                        // offset 0x4cUL
    /// AHB1 peripheral clock enable in low power mode register (AHB1LPENR)
    AHB1PeripheralLowPowerEnable ahb1_peripheral_low_power_enable;    // offset 0x50UL
    /// AHB2 peripheral clock enable in low power mode register (AHB2LPENR)
    AHB2PeripheralLowPowerEnable ahb2_peripheral_low_power_enable;    // offset 0x54UL
    /// AHB3 peripheral clock enable in low power mode register (AHB3LPENR)
    AHB3PeripheralLowPowerEnable ahb3_peripheral_low_power_enable;    // offset 0x58UL
    std::uint32_t : 32;                                               // offset 0x5cUL
    /// APB1 peripheral clock enable in low power mode register (APB1LPENR)
    APB1PeripheralLowPowerEnable apb1_peripheral_low_power_enable;    // offset 0x60UL
    /// APB2 peripheral clock enabled in low power mode register (APB2LPENR)
    APB2PeripheralLowPowerEnable apb2_peripheral_low_power_enable;    // offset 0x64UL
    std::uint32_t : 32;                                               // offset 0x68UL
    std::uint32_t : 32;                                               // offset 0x6cUL
    /// Backup domain control register (BDCR)
    BackupDomainControl backup_domain_control;    // offset 0x70UL
    /// clock control & status register (CSR)
    Status status;         // offset 0x74UL
    std::uint32_t : 32;    // offset 0x78UL
    std::uint32_t : 32;    // offset 0x7cUL
    /// spread spectrum clock generation register (SSCGR)
    SpreadSpectrumClockGeneration spread_spectrum_clock_generation;    // offset 0x80UL
    /// PLLI2S configuration register (PLLI2SCFGR)
    PhaseLockLoopI2SConfiguration pll_i2s_configuration;    // offset 0x84UL
    std::uint32_t : 32;                                     // offset 0x88UL
    std::uint32_t : 32;                                     // offset 0x8cUL
    std::uint32_t : 32;                                     // offset 0x90UL
    std::uint32_t : 32;                                     // offset 0x94UL
    std::uint32_t : 32;                                     // offset 0x98UL
    std::uint32_t : 32;                                     // offset 0x9cUL
    std::uint32_t : 32;                                     // offset 0xa0UL
    std::uint32_t : 32;                                     // offset 0xa4UL
    std::uint32_t : 32;                                     // offset 0xa8UL
    std::uint32_t : 32;                                     // offset 0xacUL
    std::uint32_t : 32;                                     // offset 0xb0UL
    std::uint32_t : 32;                                     // offset 0xb4UL
    std::uint32_t : 32;                                     // offset 0xb8UL
    std::uint32_t : 32;                                     // offset 0xbcUL
    std::uint32_t : 32;                                     // offset 0xc0UL
    std::uint32_t : 32;                                     // offset 0xc4UL
    std::uint32_t : 32;                                     // offset 0xc8UL
    std::uint32_t : 32;                                     // offset 0xccUL
    std::uint32_t : 32;                                     // offset 0xd0UL
    std::uint32_t : 32;                                     // offset 0xd4UL
    std::uint32_t : 32;                                     // offset 0xd8UL
    std::uint32_t : 32;                                     // offset 0xdcUL
    std::uint32_t : 32;                                     // offset 0xe0UL
    std::uint32_t : 32;                                     // offset 0xe4UL
    std::uint32_t : 32;                                     // offset 0xe8UL
    std::uint32_t : 32;                                     // offset 0xecUL
    std::uint32_t : 32;                                     // offset 0xf0UL
    std::uint32_t : 32;                                     // offset 0xf4UL
    std::uint32_t : 32;                                     // offset 0xf8UL
    std::uint32_t : 32;                                     // offset 0xfcUL
    std::uint32_t : 32;                                     // offset 0x100UL
    std::uint32_t : 32;                                     // offset 0x104UL
    std::uint32_t : 32;                                     // offset 0x108UL
    std::uint32_t : 32;                                     // offset 0x10cUL
    std::uint32_t : 32;                                     // offset 0x110UL
    std::uint32_t : 32;                                     // offset 0x114UL
    std::uint32_t : 32;                                     // offset 0x118UL
    std::uint32_t : 32;                                     // offset 0x11cUL
    std::uint32_t : 32;                                     // offset 0x120UL
    std::uint32_t : 32;                                     // offset 0x124UL
    std::uint32_t : 32;                                     // offset 0x128UL
    std::uint32_t : 32;                                     // offset 0x12cUL
    std::uint32_t : 32;                                     // offset 0x130UL
    std::uint32_t : 32;                                     // offset 0x134UL
    std::uint32_t : 32;                                     // offset 0x138UL
    std::uint32_t : 32;                                     // offset 0x13cUL
    std::uint32_t : 32;                                     // offset 0x140UL
    std::uint32_t : 32;                                     // offset 0x144UL
    std::uint32_t : 32;                                     // offset 0x148UL
    std::uint32_t : 32;                                     // offset 0x14cUL
    std::uint32_t : 32;                                     // offset 0x150UL
    std::uint32_t : 32;                                     // offset 0x154UL
    std::uint32_t : 32;                                     // offset 0x158UL
    std::uint32_t : 32;                                     // offset 0x15cUL
    std::uint32_t : 32;                                     // offset 0x160UL
    std::uint32_t : 32;                                     // offset 0x164UL
    std::uint32_t : 32;                                     // offset 0x168UL
    std::uint32_t : 32;                                     // offset 0x16cUL
    std::uint32_t : 32;                                     // offset 0x170UL
    std::uint32_t : 32;                                     // offset 0x174UL
    std::uint32_t : 32;                                     // offset 0x178UL
    std::uint32_t : 32;                                     // offset 0x17cUL
    std::uint32_t : 32;                                     // offset 0x180UL
    std::uint32_t : 32;                                     // offset 0x184UL
    std::uint32_t : 32;                                     // offset 0x188UL
    std::uint32_t : 32;                                     // offset 0x18cUL
    std::uint32_t : 32;                                     // offset 0x190UL
    std::uint32_t : 32;                                     // offset 0x194UL
    std::uint32_t : 32;                                     // offset 0x198UL
    std::uint32_t : 32;                                     // offset 0x19cUL
    std::uint32_t : 32;                                     // offset 0x1a0UL
    std::uint32_t : 32;                                     // offset 0x1a4UL
    std::uint32_t : 32;                                     // offset 0x1a8UL
    std::uint32_t : 32;                                     // offset 0x1acUL
    std::uint32_t : 32;                                     // offset 0x1b0UL
    std::uint32_t : 32;                                     // offset 0x1b4UL
    std::uint32_t : 32;                                     // offset 0x1b8UL
    std::uint32_t : 32;                                     // offset 0x1bcUL
    std::uint32_t : 32;                                     // offset 0x1c0UL
    std::uint32_t : 32;                                     // offset 0x1c4UL
    std::uint32_t : 32;                                     // offset 0x1c8UL
    std::uint32_t : 32;                                     // offset 0x1ccUL
    std::uint32_t : 32;                                     // offset 0x1d0UL
    std::uint32_t : 32;                                     // offset 0x1d4UL
    std::uint32_t : 32;                                     // offset 0x1d8UL
    std::uint32_t : 32;                                     // offset 0x1dcUL
    std::uint32_t : 32;                                     // offset 0x1e0UL
    std::uint32_t : 32;                                     // offset 0x1e4UL
    std::uint32_t : 32;                                     // offset 0x1e8UL
    std::uint32_t : 32;                                     // offset 0x1ecUL
    std::uint32_t : 32;                                     // offset 0x1f0UL
    std::uint32_t : 32;                                     // offset 0x1f4UL
    std::uint32_t : 32;                                     // offset 0x1f8UL
    std::uint32_t : 32;                                     // offset 0x1fcUL
    std::uint32_t : 32;                                     // offset 0x200UL
    std::uint32_t : 32;                                     // offset 0x204UL
    std::uint32_t : 32;                                     // offset 0x208UL
    std::uint32_t : 32;                                     // offset 0x20cUL
    std::uint32_t : 32;                                     // offset 0x210UL
    std::uint32_t : 32;                                     // offset 0x214UL
    std::uint32_t : 32;                                     // offset 0x218UL
    std::uint32_t : 32;                                     // offset 0x21cUL
    std::uint32_t : 32;                                     // offset 0x220UL
    std::uint32_t : 32;                                     // offset 0x224UL
    std::uint32_t : 32;                                     // offset 0x228UL
    std::uint32_t : 32;                                     // offset 0x22cUL
    std::uint32_t : 32;                                     // offset 0x230UL
    std::uint32_t : 32;                                     // offset 0x234UL
    std::uint32_t : 32;                                     // offset 0x238UL
    std::uint32_t : 32;                                     // offset 0x23cUL
    std::uint32_t : 32;                                     // offset 0x240UL
    std::uint32_t : 32;                                     // offset 0x244UL
    std::uint32_t : 32;                                     // offset 0x248UL
    std::uint32_t : 32;                                     // offset 0x24cUL
    std::uint32_t : 32;                                     // offset 0x250UL
    std::uint32_t : 32;                                     // offset 0x254UL
    std::uint32_t : 32;                                     // offset 0x258UL
    std::uint32_t : 32;                                     // offset 0x25cUL
    std::uint32_t : 32;                                     // offset 0x260UL
    std::uint32_t : 32;                                     // offset 0x264UL
    std::uint32_t : 32;                                     // offset 0x268UL
    std::uint32_t : 32;                                     // offset 0x26cUL
    std::uint32_t : 32;                                     // offset 0x270UL
    std::uint32_t : 32;                                     // offset 0x274UL
    std::uint32_t : 32;                                     // offset 0x278UL
    std::uint32_t : 32;                                     // offset 0x27cUL
    std::uint32_t : 32;                                     // offset 0x280UL
    std::uint32_t : 32;                                     // offset 0x284UL
    std::uint32_t : 32;                                     // offset 0x288UL
    std::uint32_t : 32;                                     // offset 0x28cUL
    std::uint32_t : 32;                                     // offset 0x290UL
    std::uint32_t : 32;                                     // offset 0x294UL
    std::uint32_t : 32;                                     // offset 0x298UL
    std::uint32_t : 32;                                     // offset 0x29cUL
    std::uint32_t : 32;                                     // offset 0x2a0UL
    std::uint32_t : 32;                                     // offset 0x2a4UL
    std::uint32_t : 32;                                     // offset 0x2a8UL
    std::uint32_t : 32;                                     // offset 0x2acUL
    std::uint32_t : 32;                                     // offset 0x2b0UL
    std::uint32_t : 32;                                     // offset 0x2b4UL
    std::uint32_t : 32;                                     // offset 0x2b8UL
    std::uint32_t : 32;                                     // offset 0x2bcUL
    std::uint32_t : 32;                                     // offset 0x2c0UL
    std::uint32_t : 32;                                     // offset 0x2c4UL
    std::uint32_t : 32;                                     // offset 0x2c8UL
    std::uint32_t : 32;                                     // offset 0x2ccUL
    std::uint32_t : 32;                                     // offset 0x2d0UL
    std::uint32_t : 32;                                     // offset 0x2d4UL
    std::uint32_t : 32;                                     // offset 0x2d8UL
    std::uint32_t : 32;                                     // offset 0x2dcUL
    std::uint32_t : 32;                                     // offset 0x2e0UL
    std::uint32_t : 32;                                     // offset 0x2e4UL
    std::uint32_t : 32;                                     // offset 0x2e8UL
    std::uint32_t : 32;                                     // offset 0x2ecUL
    std::uint32_t : 32;                                     // offset 0x2f0UL
    std::uint32_t : 32;                                     // offset 0x2f4UL
    std::uint32_t : 32;                                     // offset 0x2f8UL
    std::uint32_t : 32;                                     // offset 0x2fcUL
    std::uint32_t : 32;                                     // offset 0x300UL
    std::uint32_t : 32;                                     // offset 0x304UL
    std::uint32_t : 32;                                     // offset 0x308UL
    std::uint32_t : 32;                                     // offset 0x30cUL
    std::uint32_t : 32;                                     // offset 0x310UL
    std::uint32_t : 32;                                     // offset 0x314UL
    std::uint32_t : 32;                                     // offset 0x318UL
    std::uint32_t : 32;                                     // offset 0x31cUL
    std::uint32_t : 32;                                     // offset 0x320UL
    std::uint32_t : 32;                                     // offset 0x324UL
    std::uint32_t : 32;                                     // offset 0x328UL
    std::uint32_t : 32;                                     // offset 0x32cUL
    std::uint32_t : 32;                                     // offset 0x330UL
    std::uint32_t : 32;                                     // offset 0x334UL
    std::uint32_t : 32;                                     // offset 0x338UL
    std::uint32_t : 32;                                     // offset 0x33cUL
    std::uint32_t : 32;                                     // offset 0x340UL
    std::uint32_t : 32;                                     // offset 0x344UL
    std::uint32_t : 32;                                     // offset 0x348UL
    std::uint32_t : 32;                                     // offset 0x34cUL
    std::uint32_t : 32;                                     // offset 0x350UL
    std::uint32_t : 32;                                     // offset 0x354UL
    std::uint32_t : 32;                                     // offset 0x358UL
    std::uint32_t : 32;                                     // offset 0x35cUL
    std::uint32_t : 32;                                     // offset 0x360UL
    std::uint32_t : 32;                                     // offset 0x364UL
    std::uint32_t : 32;                                     // offset 0x368UL
    std::uint32_t : 32;                                     // offset 0x36cUL
    std::uint32_t : 32;                                     // offset 0x370UL
    std::uint32_t : 32;                                     // offset 0x374UL
    std::uint32_t : 32;                                     // offset 0x378UL
    std::uint32_t : 32;                                     // offset 0x37cUL
    std::uint32_t : 32;                                     // offset 0x380UL
    std::uint32_t : 32;                                     // offset 0x384UL
    std::uint32_t : 32;                                     // offset 0x388UL
    std::uint32_t : 32;                                     // offset 0x38cUL
    std::uint32_t : 32;                                     // offset 0x390UL
    std::uint32_t : 32;                                     // offset 0x394UL
    std::uint32_t : 32;                                     // offset 0x398UL
    std::uint32_t : 32;                                     // offset 0x39cUL
    std::uint32_t : 32;                                     // offset 0x3a0UL
    std::uint32_t : 32;                                     // offset 0x3a4UL
    std::uint32_t : 32;                                     // offset 0x3a8UL
    std::uint32_t : 32;                                     // offset 0x3acUL
    std::uint32_t : 32;                                     // offset 0x3b0UL
    std::uint32_t : 32;                                     // offset 0x3b4UL
    std::uint32_t : 32;                                     // offset 0x3b8UL
    std::uint32_t : 32;                                     // offset 0x3bcUL
    std::uint32_t : 32;                                     // offset 0x3c0UL
    std::uint32_t : 32;                                     // offset 0x3c4UL
    std::uint32_t : 32;                                     // offset 0x3c8UL
    std::uint32_t : 32;                                     // offset 0x3ccUL
    std::uint32_t : 32;                                     // offset 0x3d0UL
    std::uint32_t : 32;                                     // offset 0x3d4UL
    std::uint32_t : 32;                                     // offset 0x3d8UL
    std::uint32_t : 32;                                     // offset 0x3dcUL
    std::uint32_t : 32;                                     // offset 0x3e0UL
    std::uint32_t : 32;                                     // offset 0x3e4UL
    std::uint32_t : 32;                                     // offset 0x3e8UL
    std::uint32_t : 32;                                     // offset 0x3ecUL
    std::uint32_t : 32;                                     // offset 0x3f0UL
    std::uint32_t : 32;                                     // offset 0x3f4UL
    std::uint32_t : 32;                                     // offset 0x3f8UL
    std::uint32_t : 32;                                     // offset 0x3fcUL
};
// Ensure the structure is in standard layout format
static_assert(std::is_standard_layout<ResetAndClockControl>::value, "Must be standard layout");
// Ensure the offsets are all correct
static_assert(offsetof(ResetAndClockControl, control) == 0x0UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, pll_configuration) == 0x4UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, configuration) == 0x8UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, clock_interrupt) == 0xcUL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, ahb1_peripheral_reset) == 0x10UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, ahb2_peripheral_reset) == 0x14UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, ahb3_peripheral_reset) == 0x18UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, apb1_peripheral_reset) == 0x20UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, apb2_peripheral_reset) == 0x24UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, ahb1_peripheral_clock_enable) == 0x30UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, ahb2_peripheral_clock_enable) == 0x34UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, ahb3_peripheral_clock_enable) == 0x38UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, apb1_peripheral_clock_enable) == 0x40UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, apb2_peripheral_clock_enable) == 0x44UL, "Must be located at this offset");
static_assert(
    offsetof(ResetAndClockControl, ahb1_peripheral_low_power_enable) == 0x50UL, "Must be located at this offset"
);
static_assert(
    offsetof(ResetAndClockControl, ahb2_peripheral_low_power_enable) == 0x54UL, "Must be located at this offset"
);
static_assert(
    offsetof(ResetAndClockControl, ahb3_peripheral_low_power_enable) == 0x58UL, "Must be located at this offset"
);
static_assert(
    offsetof(ResetAndClockControl, apb1_peripheral_low_power_enable) == 0x60UL, "Must be located at this offset"
);
static_assert(
    offsetof(ResetAndClockControl, apb2_peripheral_low_power_enable) == 0x64UL, "Must be located at this offset"
);
static_assert(offsetof(ResetAndClockControl, backup_domain_control) == 0x70UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, status) == 0x74UL, "Must be located at this offset");
static_assert(
    offsetof(ResetAndClockControl, spread_spectrum_clock_generation) == 0x80UL, "Must be located at this offset"
);
static_assert(offsetof(ResetAndClockControl, pll_i2s_configuration) == 0x84UL, "Must be located at this offset");

// Ensure the sizeof the entire structure is correct.
static_assert(sizeof(ResetAndClockControl) == 0x400UL, "Must be this exact size");

/// The external volatile reset_and_clock_control which is a memory mapped register or peripheral.
/// @note The address of the peripheral is set either by the linkerscript or by a unit test.
extern ResetAndClockControl volatile reset_and_clock_control;
}    // namespace registers
}    // namespace stm32
#endif    // STM32_REGISTERS_RESETANDCLOCKCONTROL_HPP_
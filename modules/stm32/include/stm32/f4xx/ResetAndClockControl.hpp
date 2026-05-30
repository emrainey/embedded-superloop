
#ifndef STM32_F4XX_RESETANDCLOCKCONTROL__HPP_
#define STM32_F4XX_RESETANDCLOCKCONTROL__HPP_

/// @file
/// Auto Generated Structure Definitions for ResetAndClockControl from the Peripheralyzer.
/// @copyright

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace stm32 {
namespace f4xx {

/// Reset and clock control (RCC)
struct ResetAndClockControl final {
    /// clock control register (CR)
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
            /// Internal high-speed clock enable (HSION)
            uint32_t high_speed_internal_enable      : 1;    // bit 0
            /// Internal high-speed clock ready flag (HSIRDY)
            uint32_t high_speed_internal_ready       : 1;    // bit 1
            /// (reserved)
            uint32_t                                 : 1;    // bit 2
            /// Internal high-speed clock trimming (HSITRIM)
            uint32_t high_speed_internal_trim        : 5;    // bits 3:7
            /// Internal high-speed clock calibration (HSICAL)
            uint32_t high_speed_internal_calibration : 8;    // bits 8:15
            /// HSE clock enable (HSEON)
            uint32_t high_speed_external_enable      : 1;    // bit 16
            /// HSE clock ready flag (HSERDY)
            uint32_t high_speed_external_ready       : 1;    // bit 17
            /// HSE clock bypass (HSEBYP)
            uint32_t high_speed_external_bypass      : 1;    // bit 18
            /// Clock security system enable (CSSON)
            uint32_t clock_security_system_enable    : 1;    // bit 19
            /// (reserved)
            uint32_t                                 : 4;    // bits 20:23
            /// Main PLL (PLL) enable (PLLON)
            uint32_t main_pll_enable                 : 1;    // bit 24
            /// Main PLL (PLL) clock ready flag (PLLRDY)
            uint32_t main_pll_ready                  : 1;    // bit 25
            /// PLLI2S enable (PLLI2SON)
            uint32_t i2s_pll_enable                  : 1;    // bit 26
            /// PLLI2S clock ready flag (PLLI2SRDY)
            uint32_t i2s_pll_ready                   : 1;    // bit 27
            /// (reserved)
            uint32_t                                 : 4;    // bits 28:31
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
    /// PLL configuration register (PLLCFGR)
    struct PhaseLockLoopConfiguration final {
        /// Main PLL(PLL) and audio PLL (PLLI2S) entry clock source (PLLSRC)
        enum class MainPLLSource : uint32_t {
            HighSpeedInternalClock = 0,    ///<  (HSI_CLOCK)
            HighSpeedExternalClock = 1,    ///<  (HSE_CLOCK)
        };
        /// Default Constructor
        PhaseLockLoopConfiguration()
            : whole{0u} {}
        /// Copy Constructor from volatile
        PhaseLockLoopConfiguration(PhaseLockLoopConfiguration volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        PhaseLockLoopConfiguration(PhaseLockLoopConfiguration const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        PhaseLockLoopConfiguration(PhaseLockLoopConfiguration&&) = delete;
        /// Parameterized Constructor for constant references
        explicit PhaseLockLoopConfiguration(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit PhaseLockLoopConfiguration(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~PhaseLockLoopConfiguration() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Division factor for the main PLL (PLL) and audio PLL (PLLI2S) input clock (PLLM)
            uint32_t main_pll_input_divisor : 6;    // bits 0:5
            /// Main PLL (PLL) multiplication factor for VCO (PLLN)
            uint32_t main_pll_vco_scalar    : 9;    // bits 6:14
            /// (reserved)
            uint32_t                        : 1;    // bit 15
            /// Main PLL (PLL) division factor for main system clock (PLLP)
            uint32_t main_pll_divider       : 2;    // bits 16:17
            /// (reserved)
            uint32_t                        : 4;    // bits 18:21
            /// Main PLL(PLL) and audio PLL (PLLI2S) entry clock source (PLLSRC)
            MainPLLSource main_pll_source   : 1;    // bit 22
            /// (reserved)
            uint32_t                        : 1;    // bit 23
            /// Main PLL (PLL) division factor for USB OTG FS, SDIO and random number generator clocks (PLLQ)
            uint32_t main_pll_divider2      : 4;    // bits 24:27
            /// (reserved)
            uint32_t                        : 4;    // bits 28:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        PhaseLockLoopConfiguration& operator=(PhaseLockLoopConfiguration&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PhaseLockLoopConfiguration volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PhaseLockLoopConfiguration const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<PhaseLockLoopConfiguration>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(PhaseLockLoopConfiguration) == 4UL, "Must be this exact size");
    /// clock configuration register (CFGR)
    struct Configuration final {
        /// Microcontroller clock output 2 (MCO2)
        enum class Clock2Source : uint32_t {
            SystemClock = 0,                                ///<  (SYS_CLOCK)
            PhaseLockLoopInterIntergratedSoundClock = 1,    ///<  (PLL_I2S_CLOCK)
            HighSpeedExternalClock = 2,                     ///<  (HSE_CLOCK)
            PhaseLockLoopClock = 3,                         ///<  (PLL_CLOCK)
        };
        /// Microcontroller clock output 1 (MCO1)
        enum class Clock1Source : uint32_t {
            HighSpeedInternalClock = 0,    ///<  (HSI_CLOCK)
            LowSpeedExternalClock = 1,     ///<  (LSE_CLOCK)
            HighSpeedExternalClock = 2,    ///<  (HSE_CLOCK)
            PhaseLockLoopClock = 3,        ///<  (PLL_CLOCK)
        };
        /// System clock switch (SW)
        enum class SystemClockSwitch : uint32_t {
            HighSpeedInternalClock = 0,    ///<  (HSI_CLOCK)
            HighSpeedExternalClock = 1,    ///<  (HSE_CLOCK)
            PhaseLockLoopClock = 2,        ///<  (PLL_CLOCK)
        };
        /// Default Constructor
        Configuration()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Configuration(Configuration volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Configuration(Configuration const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Configuration(Configuration&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Configuration(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Configuration(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Configuration() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// System clock switch (SW)
            SystemClockSwitch system_clock_switch        : 2;    // bits 0:1
            /// System clock switch status (SWS)
            SystemClockSwitch system_clock_switch_status : 2;    // bits 2:3
            /// AHB prescaler (HPRE)
            uint32_t ahb_prescaler                       : 4;    // bits 4:7
            /// (reserved)
            uint32_t                                     : 2;    // bits 8:9
            /// APB Low speed prescaler (APB1) (PPRE1)
            uint32_t apb1_prescaler                      : 3;    // bits 10:12
            /// APB high-speed prescaler (APB2) (PPRE2)
            uint32_t apb2_prescaler                      : 3;    // bits 13:15
            /// HSE division factor for RTC clock (RTCPRE)
            uint32_t real_time_clock_prescaler           : 5;    // bits 16:20
            /// Microcontroller clock output 1 (MCO1)
            Clock1Source clock1_source                   : 2;    // bits 21:22
            /// I2S clock selection (I2SSRC)
            uint32_t i2s_clock_source                    : 1;    // bit 23
            /// MCO1 prescaler (MCO1PRE)
            uint32_t mco1_prescaler                      : 3;    // bits 24:26
            /// MCO2 prescaler (MCO2PRE)
            uint32_t mco2_prescaler                      : 3;    // bits 27:29
            /// Microcontroller clock output 2 (MCO2)
            Clock2Source clock2_source                   : 2;    // bits 30:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Configuration& operator=(Configuration&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Configuration volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Configuration const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Configuration>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Configuration) == 4UL, "Must be this exact size");
    /// clock interrupt register (CIR)
    struct ClockInterrupt final {
        /// Default Constructor
        ClockInterrupt()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ClockInterrupt(ClockInterrupt volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ClockInterrupt(ClockInterrupt const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ClockInterrupt(ClockInterrupt&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ClockInterrupt(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ClockInterrupt(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ClockInterrupt() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// LSI ready interrupt flag (LSIRDYF)
            uint32_t low_speed_internal_ready_flag              : 1;    // bit 0
            /// LSE ready interrupt flag (LSERDYF)
            uint32_t low_speed_external_ready_flag              : 1;    // bit 1
            /// HSI ready interrupt flag (HSIRDYF)
            uint32_t high_speed_internal_ready_flag             : 1;    // bit 2
            /// HSE ready interrupt flag (HSERDYF)
            uint32_t high_speed_external_ready_flag             : 1;    // bit 3
            /// Main PLL (PLL) ready interrupt flag (PLLRDYF)
            uint32_t main_pll_interrupt_flag                    : 1;    // bit 4
            /// PLLI2S ready interrupt flag (PLLI2SRDYF)
            uint32_t i2s_pll_ready_flag                         : 1;    // bit 5
            /// (reserved)
            uint32_t                                            : 1;    // bit 6
            /// Clock security system interrupt flag (CSSF)
            uint32_t clock_security_system_flag                 : 1;    // bit 7
            /// LSI ready interrupt enable (LSIRDYIE)
            uint32_t low_speed_internal_ready_interrupt_enable  : 1;    // bit 8
            /// LSE ready interrupt enable (LSERDYIE)
            uint32_t low_speed_external_ready_interrupt_enable  : 1;    // bit 9
            /// HSI ready interrupt enable (HSIRDYIE)
            uint32_t high_speed_internal_ready_interrupt_enable : 1;    // bit 10
            /// HSE ready interrupt enable (HSERDYIE)
            uint32_t high_speed_external_ready_interrupt_enable : 1;    // bit 11
            /// Main PLL (PLL) ready interrupt enable (PLLRDYIE)
            uint32_t main_pll_interrupt_enable                  : 1;    // bit 12
            /// PLLI2S ready interrupt enable (PLLI2SRDYIE)
            uint32_t i2s_pll_ready_interrupt_enable             : 1;    // bit 13
            /// (reserved)
            uint32_t                                            : 2;    // bits 14:15
            /// LSI ready interrupt clear (LSIRDYC)
            uint32_t low_speed_internal_ready_interrupt_clear   : 1;    // bit 16
            /// LSE ready interrupt clear (LSERDYC)
            uint32_t low_speed_external_ready_interrupt_clear   : 1;    // bit 17
            /// HSI ready interrupt clear (HSIRDYC)
            uint32_t high_speed_internal_ready_clear            : 1;    // bit 18
            /// HSE ready interrupt clear (HSERDYC)
            uint32_t high_speed_external_ready_interrupt_clear  : 1;    // bit 19
            /// Main PLL(PLL) ready interrupt clear (PLLRDYC)
            uint32_t main_pll_ready_interrupt_clear             : 1;    // bit 20
            /// PLLI2S ready interrupt clear (PLLI2SRDYC)
            uint32_t i2s_pll_ready_interrupt_clear              : 1;    // bit 21
            /// (reserved)
            uint32_t                                            : 1;    // bit 22
            /// Clock security system interrupt clear (CSSC)
            uint32_t clock_security_system_clear                : 1;    // bit 23
            /// (reserved)
            uint32_t                                            : 8;    // bits 24:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ClockInterrupt& operator=(ClockInterrupt&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ClockInterrupt volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ClockInterrupt const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ClockInterrupt>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ClockInterrupt) == 4UL, "Must be this exact size");
    /// AHB1 peripheral reset register (AHB1RSTR)
    struct AHB1PeripheralReset final {
        /// Default Constructor
        AHB1PeripheralReset()
            : whole{0u} {}
        /// Copy Constructor from volatile
        AHB1PeripheralReset(AHB1PeripheralReset volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        AHB1PeripheralReset(AHB1PeripheralReset const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        AHB1PeripheralReset(AHB1PeripheralReset&&) = delete;
        /// Parameterized Constructor for constant references
        explicit AHB1PeripheralReset(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit AHB1PeripheralReset(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~AHB1PeripheralReset() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// IO port A reset (GPIOARST)
            uint32_t gpioa_reset  : 1;    // bit 0
            /// IO port B reset (GPIOBRST)
            uint32_t gpiob_reset  : 1;    // bit 1
            /// IO port C reset (GPIOCRST)
            uint32_t gpioc_reset  : 1;    // bit 2
            /// IO port D reset (GPIODRST)
            uint32_t gpiod_reset  : 1;    // bit 3
            /// IO port E reset (GPIOERST)
            uint32_t gpioe_reset  : 1;    // bit 4
            /// IO port F reset (GPIOFRST)
            uint32_t gpiof_reset  : 1;    // bit 5
            /// IO port G reset (GPIOGRST)
            uint32_t gpiog_reset  : 1;    // bit 6
            /// IO port H reset (GPIOHRST)
            uint32_t gpioh_reset  : 1;    // bit 7
            /// IO port I reset (GPIOIRST)
            uint32_t gpioi_reset  : 1;    // bit 8
            /// (reserved)
            uint32_t              : 3;    // bits 9:11
            /// CRC reset (CRCRST)
            uint32_t crc_reset    : 1;    // bit 12
            /// (reserved)
            uint32_t              : 8;    // bits 13:20
            /// DMA2 reset (DMA1RST)
            uint32_t dma1_reset   : 1;    // bit 21
            /// DMA2 reset (DMA2RST)
            uint32_t dma2_reset   : 1;    // bit 22
            /// (reserved)
            uint32_t              : 2;    // bits 23:24
            /// Ethernet MAC reset (ETHMACRST)
            uint32_t ethmac_reset : 1;    // bit 25
            /// (reserved)
            uint32_t              : 3;    // bits 26:28
            /// USB OTG HS module reset (OTGHSRST)
            uint32_t otghs_reset  : 1;    // bit 29
            /// (reserved)
            uint32_t              : 2;    // bits 30:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        AHB1PeripheralReset& operator=(AHB1PeripheralReset&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(AHB1PeripheralReset volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(AHB1PeripheralReset const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<AHB1PeripheralReset>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(AHB1PeripheralReset) == 4UL, "Must be this exact size");
    /// AHB2 peripheral reset register (AHB2RSTR)
    struct AHB2PeripheralReset final {
        /// Default Constructor
        AHB2PeripheralReset()
            : whole{0u} {}
        /// Copy Constructor from volatile
        AHB2PeripheralReset(AHB2PeripheralReset volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        AHB2PeripheralReset(AHB2PeripheralReset const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        AHB2PeripheralReset(AHB2PeripheralReset&&) = delete;
        /// Parameterized Constructor for constant references
        explicit AHB2PeripheralReset(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit AHB2PeripheralReset(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~AHB2PeripheralReset() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Camera interface reset (DCMIRST)
            uint32_t dcmi_reset                    : 1;    // bit 0
            /// (reserved)
            uint32_t                               : 5;    // bits 1:5
            /// Random number generator module reset (RNGRST)
            uint32_t random_number_generator_reset : 1;    // bit 6
            /// USB OTG FS module reset (OTGFSRST)
            uint32_t otgfs_reset                   : 1;    // bit 7
            /// (reserved)
            uint32_t                               : 24;    // bits 8:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        AHB2PeripheralReset& operator=(AHB2PeripheralReset&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(AHB2PeripheralReset volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(AHB2PeripheralReset const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<AHB2PeripheralReset>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(AHB2PeripheralReset) == 4UL, "Must be this exact size");
    /// AHB3 peripheral reset register (AHB3RSTR)
    struct AHB3PeripheralReset final {
        /// Default Constructor
        AHB3PeripheralReset()
            : whole{0u} {}
        /// Copy Constructor from volatile
        AHB3PeripheralReset(AHB3PeripheralReset volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        AHB3PeripheralReset(AHB3PeripheralReset const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        AHB3PeripheralReset(AHB3PeripheralReset&&) = delete;
        /// Parameterized Constructor for constant references
        explicit AHB3PeripheralReset(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit AHB3PeripheralReset(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~AHB3PeripheralReset() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Flexible static memory controller module reset (FSMCRST)
            uint32_t fsmc_reset : 1;    // bit 0
            /// (reserved)
            uint32_t            : 31;    // bits 1:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        AHB3PeripheralReset& operator=(AHB3PeripheralReset&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(AHB3PeripheralReset volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(AHB3PeripheralReset const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<AHB3PeripheralReset>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(AHB3PeripheralReset) == 4UL, "Must be this exact size");
    /// APB1 peripheral reset register (APB1RSTR)
    struct APB1PeripheralReset final {
        /// Default Constructor
        APB1PeripheralReset()
            : whole{0u} {}
        /// Copy Constructor from volatile
        APB1PeripheralReset(APB1PeripheralReset volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        APB1PeripheralReset(APB1PeripheralReset const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        APB1PeripheralReset(APB1PeripheralReset&&) = delete;
        /// Parameterized Constructor for constant references
        explicit APB1PeripheralReset(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit APB1PeripheralReset(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~APB1PeripheralReset() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TIM2 reset (TIM2RST)
            uint32_t timer2_reset          : 1;    // bit 0
            /// TIM3 reset (TIM3RST)
            uint32_t timer3_reset          : 1;    // bit 1
            /// TIM4 reset (TIM4RST)
            uint32_t timer4_reset          : 1;    // bit 2
            /// TIM5 reset (TIM5RST)
            uint32_t timer5_reset          : 1;    // bit 3
            /// TIM6 reset (TIM6RST)
            uint32_t timer6_reset          : 1;    // bit 4
            /// TIM7 reset (TIM7RST)
            uint32_t timer7_reset          : 1;    // bit 5
            /// TIM12 reset (TIM12RST)
            uint32_t timer12_reset         : 1;    // bit 6
            /// TIM13 reset (TIM13RST)
            uint32_t timer13_reset         : 1;    // bit 7
            /// TIM14 reset (TIM14RST)
            uint32_t timer14_reset         : 1;    // bit 8
            /// (reserved)
            uint32_t                       : 2;    // bits 9:10
            /// Window watchdog reset (WWDGRST)
            uint32_t window_watchdog_reset : 1;    // bit 11
            /// (reserved)
            uint32_t                       : 2;    // bits 12:13
            /// SPI 2 reset (SPI2RST)
            uint32_t spi2_reset            : 1;    // bit 14
            /// SPI 3 reset (SPI3RST)
            uint32_t spi3_reset            : 1;    // bit 15
            /// (reserved)
            uint32_t                       : 1;    // bit 16
            /// USART 2 reset (UART2RST)
            uint32_t uart2_reset           : 1;    // bit 17
            /// USART 3 reset (UART3RST)
            uint32_t uart3_reset           : 1;    // bit 18
            /// USART 4 reset (UART4RST)
            uint32_t uart4_reset           : 1;    // bit 19
            /// USART 5 reset (UART5RST)
            uint32_t uart5_reset           : 1;    // bit 20
            /// I2C 1 reset (I2C1RST)
            uint32_t i2c1_reset            : 1;    // bit 21
            /// I2C 2 reset (I2C2RST)
            uint32_t i2c2_reset            : 1;    // bit 22
            /// I2C3 reset (I2C3RST)
            uint32_t i2c3_reset            : 1;    // bit 23
            /// (reserved)
            uint32_t                       : 1;    // bit 24
            /// CAN1 reset (CAN1RST)
            uint32_t can1_reset            : 1;    // bit 25
            /// CAN2 reset (CAN2RST)
            uint32_t can2_reset            : 1;    // bit 26
            /// (reserved)
            uint32_t                       : 1;    // bit 27
            /// Power interface reset (PWRRST)
            uint32_t pwr_reset             : 1;    // bit 28
            /// DAC reset (DACRST)
            uint32_t dac_reset             : 1;    // bit 29
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
        APB1PeripheralReset& operator=(APB1PeripheralReset&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(APB1PeripheralReset volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(APB1PeripheralReset const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<APB1PeripheralReset>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(APB1PeripheralReset) == 4UL, "Must be this exact size");
    /// APB2 peripheral reset register (APB2RSTR)
    struct APB2PeripheralReset final {
        /// Default Constructor
        APB2PeripheralReset()
            : whole{0u} {}
        /// Copy Constructor from volatile
        APB2PeripheralReset(APB2PeripheralReset volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        APB2PeripheralReset(APB2PeripheralReset const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        APB2PeripheralReset(APB2PeripheralReset&&) = delete;
        /// Parameterized Constructor for constant references
        explicit APB2PeripheralReset(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit APB2PeripheralReset(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~APB2PeripheralReset() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TIM1 reset (TIM1RST)
            uint32_t timer1_reset  : 1;    // bit 0
            /// TIM8 reset (TIM8RST)
            uint32_t timer8_reset  : 1;    // bit 1
            /// (reserved)
            uint32_t               : 2;    // bits 2:3
            /// USART1 reset (USART1RST)
            uint32_t usart1_reset  : 1;    // bit 4
            /// USART6 reset (USART6RST)
            uint32_t usart6_reset  : 1;    // bit 5
            /// (reserved)
            uint32_t               : 2;    // bits 6:7
            /// ADC interface reset (common to all ADCs) (ADCRST)
            uint32_t adc_reset     : 1;    // bit 8
            /// (reserved)
            uint32_t               : 2;    // bits 9:10
            /// SDIO reset (SDIORST)
            uint32_t sdio_reset    : 1;    // bit 11
            /// SPI 1 reset (SPI1RST)
            uint32_t spi1_reset    : 1;    // bit 12
            /// (reserved)
            uint32_t               : 1;    // bit 13
            /// System configuration controller reset (SYSCFGRST)
            uint32_t syscfg_reset  : 1;    // bit 14
            /// (reserved)
            uint32_t               : 1;    // bit 15
            /// TIM9 reset (TIM9RST)
            uint32_t timer9_reset  : 1;    // bit 16
            /// TIM10 reset (TIM10RST)
            uint32_t timer10_reset : 1;    // bit 17
            /// TIM11 reset (TIM11RST)
            uint32_t timer11_reset : 1;    // bit 18
            /// (reserved)
            uint32_t               : 13;    // bits 19:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        APB2PeripheralReset& operator=(APB2PeripheralReset&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(APB2PeripheralReset volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(APB2PeripheralReset const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<APB2PeripheralReset>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(APB2PeripheralReset) == 4UL, "Must be this exact size");
    /// AHB1 peripheral clock register (AHB1ENR)
    struct AHB1PeripheralClockEnable final {
        /// Default Constructor
        AHB1PeripheralClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        AHB1PeripheralClockEnable(AHB1PeripheralClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        AHB1PeripheralClockEnable(AHB1PeripheralClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        AHB1PeripheralClockEnable(AHB1PeripheralClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit AHB1PeripheralClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit AHB1PeripheralClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~AHB1PeripheralClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// IO port A clock enable (GPIOAEN)
            uint32_t gpioa_enable                   : 1;    // bit 0
            /// IO port B clock enable (GPIOBEN)
            uint32_t gpiob_enable                   : 1;    // bit 1
            /// IO port C clock enable (GPIOCEN)
            uint32_t gpioc_enable                   : 1;    // bit 2
            /// IO port D clock enable (GPIODEN)
            uint32_t gpiod_enable                   : 1;    // bit 3
            /// IO port E clock enable (GPIOEEN)
            uint32_t gpioe_enable                   : 1;    // bit 4
            /// IO port F clock enable (GPIOFEN)
            uint32_t gpiof_enable                   : 1;    // bit 5
            /// IO port G clock enable (GPIOGEN)
            uint32_t gpiog_enable                   : 1;    // bit 6
            /// IO port H clock enable (GPIOHEN)
            uint32_t gpioh_enable                   : 1;    // bit 7
            /// IO port I clock enable (GPIOIEN)
            uint32_t gpioi_enable                   : 1;    // bit 8
            /// (reserved)
            uint32_t                                : 3;    // bits 9:11
            /// CRC clock enable (CRCEN)
            uint32_t cyclic_redundancy_check_enable : 1;    // bit 12
            /// (reserved)
            uint32_t                                : 5;    // bits 13:17
            /// Backup SRAM interface clock enable (BKPSRAMEN)
            uint32_t bkpsram_enable                 : 1;    // bit 18
            /// (reserved)
            uint32_t                                : 2;    // bits 19:20
            /// DMA1 clock enable (DMA1EN)
            uint32_t dma1_enable                    : 1;    // bit 21
            /// DMA2 clock enable (DMA2EN)
            uint32_t dma2_enable                    : 1;    // bit 22
            /// (reserved)
            uint32_t                                : 2;    // bits 23:24
            /// Ethernet MAC clock enable (ETHMACEN)
            uint32_t ethmac_enable                  : 1;    // bit 25
            /// Ethernet Transmission clock enable (ETHMACTXEN)
            uint32_t ethmactx_enable                : 1;    // bit 26
            /// Ethernet Reception clock enable (ETHMACRXEN)
            uint32_t ethmacrx_enable                : 1;    // bit 27
            /// Ethernet PTP clock enable (ETHMACPTPEN)
            uint32_t ethmacptp_enable               : 1;    // bit 28
            /// USB OTG HS clock enable (OTGHSEN)
            uint32_t otghs_enable                   : 1;    // bit 29
            /// USB OTG HSULPI clock enable (OTGHSULPIEN)
            uint32_t otghsulpi_enable               : 1;    // bit 30
            /// (reserved)
            uint32_t                                : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        AHB1PeripheralClockEnable& operator=(AHB1PeripheralClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(AHB1PeripheralClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(AHB1PeripheralClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<AHB1PeripheralClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(AHB1PeripheralClockEnable) == 4UL, "Must be this exact size");
    /// AHB2 peripheral clock enable register (AHB2ENR)
    struct AHB2PeripheralClockEnable final {
        /// Default Constructor
        AHB2PeripheralClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        AHB2PeripheralClockEnable(AHB2PeripheralClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        AHB2PeripheralClockEnable(AHB2PeripheralClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        AHB2PeripheralClockEnable(AHB2PeripheralClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit AHB2PeripheralClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit AHB2PeripheralClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~AHB2PeripheralClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Camera interface enable (DCMIEN)
            uint32_t dcmi_enable                    : 1;    // bit 0
            /// (reserved)
            uint32_t                                : 5;    // bits 1:5
            /// Random number generator clock enable (RNGEN)
            uint32_t random_number_generator_enable : 1;    // bit 6
            /// USB OTG FS clock enable (OTGFSEN)
            uint32_t otgfs_enable                   : 1;    // bit 7
            /// (reserved)
            uint32_t                                : 24;    // bits 8:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        AHB2PeripheralClockEnable& operator=(AHB2PeripheralClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(AHB2PeripheralClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(AHB2PeripheralClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<AHB2PeripheralClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(AHB2PeripheralClockEnable) == 4UL, "Must be this exact size");
    /// AHB3 peripheral clock enable register (AHB3ENR)
    struct AHB3PeripheralClockEnable final {
        /// Default Constructor
        AHB3PeripheralClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        AHB3PeripheralClockEnable(AHB3PeripheralClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        AHB3PeripheralClockEnable(AHB3PeripheralClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        AHB3PeripheralClockEnable(AHB3PeripheralClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit AHB3PeripheralClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit AHB3PeripheralClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~AHB3PeripheralClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Flexible static memory controller module clock enable (FSMCEN)
            uint32_t fsmc_enable : 1;    // bit 0
            /// (reserved)
            uint32_t             : 31;    // bits 1:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        AHB3PeripheralClockEnable& operator=(AHB3PeripheralClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(AHB3PeripheralClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(AHB3PeripheralClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<AHB3PeripheralClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(AHB3PeripheralClockEnable) == 4UL, "Must be this exact size");
    /// APB1 peripheral clock enable register (APB1ENR)
    struct APB1PeripheralClockEnable final {
        /// Default Constructor
        APB1PeripheralClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        APB1PeripheralClockEnable(APB1PeripheralClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        APB1PeripheralClockEnable(APB1PeripheralClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        APB1PeripheralClockEnable(APB1PeripheralClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit APB1PeripheralClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit APB1PeripheralClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~APB1PeripheralClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TIM2 clock enable (TIM2EN)
            uint32_t timer2_enable          : 1;    // bit 0
            /// TIM3 clock enable (TIM3EN)
            uint32_t timer3_enable          : 1;    // bit 1
            /// TIM4 clock enable (TIM4EN)
            uint32_t timer4_enable          : 1;    // bit 2
            /// TIM5 clock enable (TIM5EN)
            uint32_t timer5_enable          : 1;    // bit 3
            /// TIM6 clock enable (TIM6EN)
            uint32_t timer6_enable          : 1;    // bit 4
            /// TIM7 clock enable (TIM7EN)
            uint32_t timer7_enable          : 1;    // bit 5
            /// TIM12 clock enable (TIM12EN)
            uint32_t timer12_enable         : 1;    // bit 6
            /// TIM13 clock enable (TIM13EN)
            uint32_t timer13_enable         : 1;    // bit 7
            /// TIM14 clock enable (TIM14EN)
            uint32_t timer14_enable         : 1;    // bit 8
            /// (reserved)
            uint32_t                        : 2;    // bits 9:10
            /// Window watchdog clock enable (WWDGEN)
            uint32_t window_watchdog_enable : 1;    // bit 11
            /// (reserved)
            uint32_t                        : 2;    // bits 12:13
            /// SPI2 clock enable (SPI2EN)
            uint32_t spi2_enable            : 1;    // bit 14
            /// SPI3 clock enable (SPI3EN)
            uint32_t spi3_enable            : 1;    // bit 15
            /// (reserved)
            uint32_t                        : 1;    // bit 16
            /// USART 2 clock enable (USART2EN)
            uint32_t usart2_enable          : 1;    // bit 17
            /// USART3 clock enable (USART3EN)
            uint32_t usart3_enable          : 1;    // bit 18
            /// UART4 clock enable (UART4EN)
            uint32_t uart4_enable           : 1;    // bit 19
            /// UART5 clock enable (UART5EN)
            uint32_t uart5_enable           : 1;    // bit 20
            /// I2C1 clock enable (I2C1EN)
            uint32_t i2c1_enable            : 1;    // bit 21
            /// I2C2 clock enable (I2C2EN)
            uint32_t i2c2_enable            : 1;    // bit 22
            /// I2C3 clock enable (I2C3EN)
            uint32_t i2c3_enable            : 1;    // bit 23
            /// (reserved)
            uint32_t                        : 1;    // bit 24
            /// CAN 1 clock enable (CAN1EN)
            uint32_t can1_enable            : 1;    // bit 25
            /// CAN 2 clock enable (CAN2EN)
            uint32_t can2_enable            : 1;    // bit 26
            /// (reserved)
            uint32_t                        : 1;    // bit 27
            /// Power interface clock enable (PWREN)
            uint32_t pwr_enable             : 1;    // bit 28
            /// DAC interface clock enable (DACEN)
            uint32_t dac_enable             : 1;    // bit 29
            /// (reserved)
            uint32_t                        : 2;    // bits 30:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        APB1PeripheralClockEnable& operator=(APB1PeripheralClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(APB1PeripheralClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(APB1PeripheralClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<APB1PeripheralClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(APB1PeripheralClockEnable) == 4UL, "Must be this exact size");
    /// APB2 peripheral clock enable register (APB2ENR)
    struct APB2PeripheralClockEnable final {
        /// Default Constructor
        APB2PeripheralClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        APB2PeripheralClockEnable(APB2PeripheralClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        APB2PeripheralClockEnable(APB2PeripheralClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        APB2PeripheralClockEnable(APB2PeripheralClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit APB2PeripheralClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit APB2PeripheralClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~APB2PeripheralClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TIM1 clock enable (TIM1EN)
            uint32_t timer1_enable  : 1;    // bit 0
            /// TIM8 clock enable (TIM8EN)
            uint32_t timer8_enable  : 1;    // bit 1
            /// (reserved)
            uint32_t                : 2;    // bits 2:3
            /// USART1 clock enable (USART1EN)
            uint32_t usart1_enable  : 1;    // bit 4
            /// USART6 clock enable (USART6EN)
            uint32_t usart6_enable  : 1;    // bit 5
            /// (reserved)
            uint32_t                : 2;    // bits 6:7
            /// ADC1 clock enable (ADC1EN)
            uint32_t adc1_enable    : 1;    // bit 8
            /// ADC2 clock enable (ADC2EN)
            uint32_t adc2_enable    : 1;    // bit 9
            /// ADC3 clock enable (ADC3EN)
            uint32_t adc3_enable    : 1;    // bit 10
            /// SDIO clock enable (SDIOEN)
            uint32_t sdio_enable    : 1;    // bit 11
            /// SPI1 clock enable (SPI1EN)
            uint32_t spi1_enable    : 1;    // bit 12
            /// (reserved)
            uint32_t                : 1;    // bit 13
            /// System configuration controller clock enable (SYSCFGEN)
            uint32_t syscfg_enable  : 1;    // bit 14
            /// (reserved)
            uint32_t                : 1;    // bit 15
            /// TIM9 clock enable (TIM9EN)
            uint32_t timer9_enable  : 1;    // bit 16
            /// TIM10 clock enable (TIM10EN)
            uint32_t timer10_enable : 1;    // bit 17
            /// TIM11 clock enable (TIM11EN)
            uint32_t timer11_enable : 1;    // bit 18
            /// (reserved)
            uint32_t                : 13;    // bits 19:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        APB2PeripheralClockEnable& operator=(APB2PeripheralClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(APB2PeripheralClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(APB2PeripheralClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<APB2PeripheralClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(APB2PeripheralClockEnable) == 4UL, "Must be this exact size");
    /// AHB1 peripheral clock enable in low power mode register (AHB1LPENR)
    struct AHB1PeripheralLowPowerEnable final {
        /// Default Constructor
        AHB1PeripheralLowPowerEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        AHB1PeripheralLowPowerEnable(AHB1PeripheralLowPowerEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        AHB1PeripheralLowPowerEnable(AHB1PeripheralLowPowerEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        AHB1PeripheralLowPowerEnable(AHB1PeripheralLowPowerEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit AHB1PeripheralLowPowerEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit AHB1PeripheralLowPowerEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~AHB1PeripheralLowPowerEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// IO port A clock enable during sleep mode (GPIOALPEN)
            uint32_t gpioa_low_power_enable     : 1;    // bit 0
            /// IO port B clock enable during Sleep mode (GPIOBLPEN)
            uint32_t gpiob_low_power_enable     : 1;    // bit 1
            /// IO port C clock enable during Sleep mode (GPIOCLPEN)
            uint32_t gpioc_low_power_enable     : 1;    // bit 2
            /// IO port D clock enable during Sleep mode (GPIODLPEN)
            uint32_t gpiod_low_power_enable     : 1;    // bit 3
            /// IO port E clock enable during Sleep mode (GPIOELPEN)
            uint32_t gpioe_low_power_enable     : 1;    // bit 4
            /// IO port F clock enable during Sleep mode (GPIOFLPEN)
            uint32_t gpiof_low_power_enable     : 1;    // bit 5
            /// IO port G clock enable during Sleep mode (GPIOGLPEN)
            uint32_t gpiog_low_power_enable     : 1;    // bit 6
            /// IO port H clock enable during Sleep mode (GPIOHLPEN)
            uint32_t gpioh_low_power_enable     : 1;    // bit 7
            /// IO port I clock enable during Sleep mode (GPIOILPEN)
            uint32_t gpioi_low_power_enable     : 1;    // bit 8
            /// (reserved)
            uint32_t                            : 3;    // bits 9:11
            /// CRC clock enable during Sleep mode (CRCLPEN)
            uint32_t crc_low_power_enable       : 1;    // bit 12
            /// (reserved)
            uint32_t                            : 2;    // bits 13:14
            /// Flash interface clock enable during Sleep mode (FLITFLPEN)
            uint32_t flitf_low_power_enable     : 1;    // bit 15
            /// SRAM 1interface clock enable during Sleep mode (SRAM1LPEN)
            uint32_t sram1_low_power_enable     : 1;    // bit 16
            /// SRAM 2 interface clock enable during Sleep mode (SRAM2LPEN)
            uint32_t sram2_low_power_enable     : 1;    // bit 17
            /// Backup SRAM interface clock enable during Sleep mode (BKPSRAMLPEN)
            uint32_t bkpsram_low_power_enable   : 1;    // bit 18
            /// (reserved)
            uint32_t                            : 2;    // bits 19:20
            /// DMA1 clock enable during Sleep mode (DMA1LPEN)
            uint32_t dma1_low_power_enable      : 1;    // bit 21
            /// DMA2 clock enable during Sleep mode (DMA2LPEN)
            uint32_t dma2_low_power_enable      : 1;    // bit 22
            /// (reserved)
            uint32_t                            : 2;    // bits 23:24
            /// Ethernet MAC clock enable during Sleep mode (ETHMACLPEN)
            uint32_t ethmac_low_power_enable    : 1;    // bit 25
            /// Ethernet transmission clock enable during Sleep mode (ETHMACTXLPEN)
            uint32_t ethmactx_low_power_enable  : 1;    // bit 26
            /// Ethernet reception clock enable during Sleep mode (ETHMACRXLPEN)
            uint32_t ethmacrx_low_power_enable  : 1;    // bit 27
            /// Ethernet PTP clock enable during Sleep mode (ETHMACPTPLPEN)
            uint32_t ethmacptp_low_power_enable : 1;    // bit 28
            /// USB OTG HS clock enable during Sleep mode (OTGHSLPEN)
            uint32_t otghs_low_power_enable     : 1;    // bit 29
            /// USB OTG HS ULPI clock enable during Sleep mode (OTGHSULPILPEN)
            uint32_t otghsulpi_low_power_enable : 1;    // bit 30
            /// (reserved)
            uint32_t                            : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        AHB1PeripheralLowPowerEnable& operator=(AHB1PeripheralLowPowerEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(AHB1PeripheralLowPowerEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(AHB1PeripheralLowPowerEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<AHB1PeripheralLowPowerEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(AHB1PeripheralLowPowerEnable) == 4UL, "Must be this exact size");
    /// AHB2 peripheral clock enable in low power mode register (AHB2LPENR)
    struct AHB2PeripheralLowPowerEnable final {
        /// Default Constructor
        AHB2PeripheralLowPowerEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        AHB2PeripheralLowPowerEnable(AHB2PeripheralLowPowerEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        AHB2PeripheralLowPowerEnable(AHB2PeripheralLowPowerEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        AHB2PeripheralLowPowerEnable(AHB2PeripheralLowPowerEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit AHB2PeripheralLowPowerEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit AHB2PeripheralLowPowerEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~AHB2PeripheralLowPowerEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Camera interface enable during Sleep mode (DCMILPEN)
            uint32_t dcmi_low_power_enable  : 1;    // bit 0
            /// (reserved)
            uint32_t                        : 5;    // bits 1:5
            /// Random number generator clock enable during Sleep mode (RNGLPEN)
            uint32_t low_power_enable       : 1;    // bit 6
            /// USB OTG FS clock enable during Sleep mode (OTGFSLPEN)
            uint32_t otgfs_low_power_enable : 1;    // bit 7
            /// (reserved)
            uint32_t                        : 24;    // bits 8:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        AHB2PeripheralLowPowerEnable& operator=(AHB2PeripheralLowPowerEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(AHB2PeripheralLowPowerEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(AHB2PeripheralLowPowerEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<AHB2PeripheralLowPowerEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(AHB2PeripheralLowPowerEnable) == 4UL, "Must be this exact size");
    /// AHB3 peripheral clock enable in low power mode register (AHB3LPENR)
    struct AHB3PeripheralLowPowerEnable final {
        /// Default Constructor
        AHB3PeripheralLowPowerEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        AHB3PeripheralLowPowerEnable(AHB3PeripheralLowPowerEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        AHB3PeripheralLowPowerEnable(AHB3PeripheralLowPowerEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        AHB3PeripheralLowPowerEnable(AHB3PeripheralLowPowerEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit AHB3PeripheralLowPowerEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit AHB3PeripheralLowPowerEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~AHB3PeripheralLowPowerEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Flexible static memory controller module clock enable during Sleep mode (FSMCLPEN)
            uint32_t fsmc_low_power_enable : 1;    // bit 0
            /// (reserved)
            uint32_t                       : 31;    // bits 1:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        AHB3PeripheralLowPowerEnable& operator=(AHB3PeripheralLowPowerEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(AHB3PeripheralLowPowerEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(AHB3PeripheralLowPowerEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<AHB3PeripheralLowPowerEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(AHB3PeripheralLowPowerEnable) == 4UL, "Must be this exact size");
    /// APB1 peripheral clock enable in low power mode register (APB1LPENR)
    struct APB1LowPowerEnable final {
        /// Default Constructor
        APB1LowPowerEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        APB1LowPowerEnable(APB1LowPowerEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        APB1LowPowerEnable(APB1LowPowerEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        APB1LowPowerEnable(APB1LowPowerEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit APB1LowPowerEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit APB1LowPowerEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~APB1LowPowerEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TIM2 clock enable during Sleep mode (TIM2LPEN)
            uint32_t timer2_low_power_enable          : 1;    // bit 0
            /// TIM3 clock enable during Sleep mode (TIM3LPEN)
            uint32_t timer3_low_power_enable          : 1;    // bit 1
            /// TIM4 clock enable during Sleep mode (TIM4LPEN)
            uint32_t timer4_low_power_enable          : 1;    // bit 2
            /// TIM5 clock enable during Sleep mode (TIM5LPEN)
            uint32_t timer5_low_power_enable          : 1;    // bit 3
            /// TIM6 clock enable during Sleep mode (TIM6LPEN)
            uint32_t timer6_low_power_enable          : 1;    // bit 4
            /// TIM7 clock enable during Sleep mode (TIM7LPEN)
            uint32_t timer7_low_power_enable          : 1;    // bit 5
            /// TIM12 clock enable during Sleep mode (TIM12LPEN)
            uint32_t timer12_low_power_enable         : 1;    // bit 6
            /// TIM13 clock enable during Sleep mode (TIM13LPEN)
            uint32_t timer13_low_power_enable         : 1;    // bit 7
            /// TIM14 clock enable during Sleep mode (TIM14LPEN)
            uint32_t timer14_low_power_enable         : 1;    // bit 8
            /// (reserved)
            uint32_t                                  : 2;    // bits 9:10
            /// Window watchdog clock enable during Sleep mode (WWDGLPEN)
            uint32_t window_watchdog_low_power_enable : 1;    // bit 11
            /// (reserved)
            uint32_t                                  : 2;    // bits 12:13
            /// SPI2 clock enable during Sleep mode (SPI2LPEN)
            uint32_t spi2_low_power_enable            : 1;    // bit 14
            /// SPI3 clock enable during Sleep mode (SPI3LPEN)
            uint32_t spi3_low_power_enable            : 1;    // bit 15
            /// (reserved)
            uint32_t                                  : 1;    // bit 16
            /// USART2 clock enable during Sleep mode (USART2LPEN)
            uint32_t usart2_low_power_enable          : 1;    // bit 17
            /// USART3 clock enable during Sleep mode (USART3LPEN)
            uint32_t usart3_low_power_enable          : 1;    // bit 18
            /// UART4 clock enable during Sleep mode (UART4LPEN)
            uint32_t uart4_low_power_enable           : 1;    // bit 19
            /// UART5 clock enable during Sleep mode (UART5LPEN)
            uint32_t uart5_low_power_enable           : 1;    // bit 20
            /// I2C1 clock enable during Sleep mode (I2C1LPEN)
            uint32_t i2c1_low_power_enable            : 1;    // bit 21
            /// I2C2 clock enable during Sleep mode (I2C2LPEN)
            uint32_t i2c2_low_power_enable            : 1;    // bit 22
            /// I2C3 clock enable during Sleep mode (I2C3LPEN)
            uint32_t i2c3_low_power_enable            : 1;    // bit 23
            /// (reserved)
            uint32_t                                  : 1;    // bit 24
            /// CAN 1 clock enable during Sleep mode (CAN1LPEN)
            uint32_t can1_low_power_enable            : 1;    // bit 25
            /// CAN 2 clock enable during Sleep mode (CAN2LPEN)
            uint32_t can2_low_power_enable            : 1;    // bit 26
            /// (reserved)
            uint32_t                                  : 1;    // bit 27
            /// Power interface clock enable during Sleep mode (PWRLPEN)
            uint32_t pwr_low_power_enable             : 1;    // bit 28
            /// DAC interface clock enable during Sleep mode (DACLPEN)
            uint32_t dac_low_power_enable             : 1;    // bit 29
            /// (reserved)
            uint32_t                                  : 2;    // bits 30:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        APB1LowPowerEnable& operator=(APB1LowPowerEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(APB1LowPowerEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(APB1LowPowerEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<APB1LowPowerEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(APB1LowPowerEnable) == 4UL, "Must be this exact size");
    /// APB2 peripheral clock enabled in low power mode register (APB2LPENR)
    struct APB2PeripheralLowPowerEnable final {
        /// Default Constructor
        APB2PeripheralLowPowerEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        APB2PeripheralLowPowerEnable(APB2PeripheralLowPowerEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        APB2PeripheralLowPowerEnable(APB2PeripheralLowPowerEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        APB2PeripheralLowPowerEnable(APB2PeripheralLowPowerEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit APB2PeripheralLowPowerEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit APB2PeripheralLowPowerEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~APB2PeripheralLowPowerEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TIM1 clock enable during Sleep mode (TIM1LPEN)
            uint32_t timer1_low_power_enable  : 1;    // bit 0
            /// TIM8 clock enable during Sleep mode (TIM8LPEN)
            uint32_t timer8_low_power_enable  : 1;    // bit 1
            /// (reserved)
            uint32_t                          : 2;    // bits 2:3
            /// USART1 clock enable during Sleep mode (USART1LPEN)
            uint32_t usart1_low_power_enable  : 1;    // bit 4
            /// USART6 clock enable during Sleep mode (USART6LPEN)
            uint32_t usart6_low_power_enable  : 1;    // bit 5
            /// (reserved)
            uint32_t                          : 2;    // bits 6:7
            /// ADC1 clock enable during Sleep mode (ADC1LPEN)
            uint32_t adc1_low_power_enable    : 1;    // bit 8
            /// ADC2 clock enable during Sleep mode (ADC2LPEN)
            uint32_t adc2_low_power_enable    : 1;    // bit 9
            /// ADC 3 clock enable during Sleep mode (ADC3LPEN)
            uint32_t adc3_low_power_enable    : 1;    // bit 10
            /// SDIO clock enable during Sleep mode (SDIOLPEN)
            uint32_t sdio_low_power_enable    : 1;    // bit 11
            /// SPI 1 clock enable during Sleep mode (SPI1LPEN)
            uint32_t spi1_low_power_enable    : 1;    // bit 12
            /// (reserved)
            uint32_t                          : 1;    // bit 13
            /// System configuration controller clock enable during Sleep mode (SYSCFGLPEN)
            uint32_t syscfg_low_power_enable  : 1;    // bit 14
            /// (reserved)
            uint32_t                          : 1;    // bit 15
            /// TIM9 clock enable during sleep mode (TIM9LPEN)
            uint32_t timer9_low_power_enable  : 1;    // bit 16
            /// TIM10 clock enable during Sleep mode (TIM10LPEN)
            uint32_t timer10_low_power_enable : 1;    // bit 17
            /// TIM11 clock enable during Sleep mode (TIM11LPEN)
            uint32_t timer11_low_power_enable : 1;    // bit 18
            /// (reserved)
            uint32_t                          : 13;    // bits 19:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        APB2PeripheralLowPowerEnable& operator=(APB2PeripheralLowPowerEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(APB2PeripheralLowPowerEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(APB2PeripheralLowPowerEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<APB2PeripheralLowPowerEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(APB2PeripheralLowPowerEnable) == 4UL, "Must be this exact size");
    /// Backup domain control register (BDCR)
    struct BackupDomainControl final {
        /// Default Constructor
        BackupDomainControl()
            : whole{0u} {}
        /// Copy Constructor from volatile
        BackupDomainControl(BackupDomainControl volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        BackupDomainControl(BackupDomainControl const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        BackupDomainControl(BackupDomainControl&&) = delete;
        /// Parameterized Constructor for constant references
        explicit BackupDomainControl(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit BackupDomainControl(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~BackupDomainControl() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// External low-speed oscillator enable (LSEON)
            uint32_t low_speed_external_enable          : 1;    // bit 0
            /// External low-speed oscillator ready (LSERDY)
            uint32_t low_speed_external_ready           : 1;    // bit 1
            /// External low-speed oscillator bypass (LSEBYP)
            uint32_t low_speed_external_bypass          : 1;    // bit 2
            /// (reserved)
            uint32_t                                    : 5;    // bits 3:7
            /// RTC clock source selection (RTCSEL0)
            uint32_t real_time_clock_source_select_bit0 : 1;    // bit 8
            /// RTC clock source selection (RTCSEL1)
            uint32_t real_time_clock_source_select_bit1 : 1;    // bit 9
            /// (reserved)
            uint32_t                                    : 5;    // bits 10:14
            /// RTC clock enable (RTCEN)
            uint32_t real_time_clock_enable             : 1;    // bit 15
            /// Backup domain software reset (BDRST)
            uint32_t backup_domain_reset                : 1;    // bit 16
            /// (reserved)
            uint32_t                                    : 15;    // bits 17:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        BackupDomainControl& operator=(BackupDomainControl&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(BackupDomainControl volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(BackupDomainControl const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<BackupDomainControl>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(BackupDomainControl) == 4UL, "Must be this exact size");
    /// clock control & status register (CSR)
    struct ClockControlStatus final {
        /// Default Constructor
        ClockControlStatus()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ClockControlStatus(ClockControlStatus volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ClockControlStatus(ClockControlStatus const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ClockControlStatus(ClockControlStatus&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ClockControlStatus(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ClockControlStatus(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ClockControlStatus() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Internal low-speed oscillator enable (LSION)
            uint32_t low_speed_internal_enable       : 1;    // bit 0
            /// Internal low-speed oscillator ready (LSIRDY)
            uint32_t low_speed_internal_ready        : 1;    // bit 1
            /// (reserved)
            uint32_t                                 : 22;    // bits 2:23
            /// Remove reset flag (RMVF)
            uint32_t reset_flags_clear               : 1;    // bit 24
            /// BOR reset flag (BORRSTF)
            uint32_t brown_out_reset_flag            : 1;    // bit 25
            /// PIN reset flag (PADRSTF)
            uint32_t pin_reset_flag                  : 1;    // bit 26
            /// POR/PDR reset flag (PORRSTF)
            uint32_t power_on_reset_flag             : 1;    // bit 27
            /// Software reset flag (SFTRSTF)
            uint32_t software_reset_flag             : 1;    // bit 28
            /// Independent watchdog reset flag (WDGRSTF)
            uint32_t independent_watchdog_reset_flag : 1;    // bit 29
            /// Window watchdog reset flag (WWDGRSTF)
            uint32_t window_watchdog_reset_flag      : 1;    // bit 30
            /// Low-power reset flag (LPWRRSTF)
            uint32_t low_power_reset_flag            : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ClockControlStatus& operator=(ClockControlStatus&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ClockControlStatus volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ClockControlStatus const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ClockControlStatus>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ClockControlStatus) == 4UL, "Must be this exact size");
    /// spread spectrum clock generation register (SSCGR)
    struct SpreadSpectrumClockGeneration final {
        /// Default Constructor
        SpreadSpectrumClockGeneration()
            : whole{0u} {}
        /// Copy Constructor from volatile
        SpreadSpectrumClockGeneration(SpreadSpectrumClockGeneration volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        SpreadSpectrumClockGeneration(SpreadSpectrumClockGeneration const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        SpreadSpectrumClockGeneration(SpreadSpectrumClockGeneration&&) = delete;
        /// Parameterized Constructor for constant references
        explicit SpreadSpectrumClockGeneration(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit SpreadSpectrumClockGeneration(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~SpreadSpectrumClockGeneration() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Modulation period (MODPER)
            uint32_t modulation_period                       : 13;    // bits 0:12
            /// Incrementation step (INCSTEP)
            uint32_t increment_step                          : 15;    // bits 13:27
            /// (reserved)
            uint32_t                                         : 2;    // bits 28:29
            /// Spread Select (SPREADSEL)
            uint32_t spread_selection                        : 1;    // bit 30
            /// Spread spectrum modulation enable (SSCGEN)
            uint32_t spread_spectrum_clock_generation_enable : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        SpreadSpectrumClockGeneration& operator=(SpreadSpectrumClockGeneration&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(SpreadSpectrumClockGeneration volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(SpreadSpectrumClockGeneration const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<SpreadSpectrumClockGeneration>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(SpreadSpectrumClockGeneration) == 4UL, "Must be this exact size");
    /// PLLI2S configuration register (PLLI2SCFGR)
    struct PhaseLockLoopInterIntegratedCircuitSoundConfiguration final {
        /// Default Constructor
        PhaseLockLoopInterIntegratedCircuitSoundConfiguration()
            : whole{0u} {}
        /// Copy Constructor from volatile
        PhaseLockLoopInterIntegratedCircuitSoundConfiguration(PhaseLockLoopInterIntegratedCircuitSoundConfiguration volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        PhaseLockLoopInterIntegratedCircuitSoundConfiguration(PhaseLockLoopInterIntegratedCircuitSoundConfiguration const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        PhaseLockLoopInterIntegratedCircuitSoundConfiguration(PhaseLockLoopInterIntegratedCircuitSoundConfiguration&&) = delete;
        /// Parameterized Constructor for constant references
        explicit PhaseLockLoopInterIntegratedCircuitSoundConfiguration(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit PhaseLockLoopInterIntegratedCircuitSoundConfiguration(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~PhaseLockLoopInterIntegratedCircuitSoundConfiguration() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                   : 6;    // bits 0:5
            /// PLLI2S multiplication factor for VCO (PLLI2SNx)
            uint32_t i2s_pll_n_factor  : 9;    // bits 6:14
            /// (reserved)
            uint32_t                   : 13;    // bits 15:27
            /// PLLI2S division factor for I2S clocks (PLLI2SRx)
            uint32_t i2s_pll_r_divider : 3;    // bits 28:30
            /// (reserved)
            uint32_t                   : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        PhaseLockLoopInterIntegratedCircuitSoundConfiguration& operator=(PhaseLockLoopInterIntegratedCircuitSoundConfiguration&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PhaseLockLoopInterIntegratedCircuitSoundConfiguration volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PhaseLockLoopInterIntegratedCircuitSoundConfiguration const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<PhaseLockLoopInterIntegratedCircuitSoundConfiguration>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(PhaseLockLoopInterIntegratedCircuitSoundConfiguration) == 4UL, "Must be this exact size");

    //+=MEMORY======================================+
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
    uint32_t : 32;                                // offset 0x1cUL
    /// APB1 peripheral reset register (APB1RSTR)
    APB1PeripheralReset apb1_peripheral_reset;    // offset 0x20UL
    /// APB2 peripheral reset register (APB2RSTR)
    APB2PeripheralReset apb2_peripheral_reset;    // offset 0x24UL
    uint32_t : 32;                                // offset 0x28UL
    uint32_t : 32;                                // offset 0x2cUL
    /// AHB1 peripheral clock register (AHB1ENR)
    AHB1PeripheralClockEnable ahb1_peripheral_clock_enable;    // offset 0x30UL
    /// AHB2 peripheral clock enable register (AHB2ENR)
    AHB2PeripheralClockEnable ahb2_peripheral_clock_enable;    // offset 0x34UL
    /// AHB3 peripheral clock enable register (AHB3ENR)
    AHB3PeripheralClockEnable ahb3_peripheral_clock_enable;    // offset 0x38UL
    uint32_t : 32;                                             // offset 0x3cUL
    /// APB1 peripheral clock enable register (APB1ENR)
    APB1PeripheralClockEnable apb1_peripheral_clock_enable;    // offset 0x40UL
    /// APB2 peripheral clock enable register (APB2ENR)
    APB2PeripheralClockEnable apb2_peripheral_clock_enable;    // offset 0x44UL
    uint32_t : 32;                                             // offset 0x48UL
    uint32_t : 32;                                             // offset 0x4cUL
    /// AHB1 peripheral clock enable in low power mode register (AHB1LPENR)
    AHB1PeripheralLowPowerEnable ahb1_peripheral_low_power_enable;    // offset 0x50UL
    /// AHB2 peripheral clock enable in low power mode register (AHB2LPENR)
    AHB2PeripheralLowPowerEnable ahb2_peripheral_low_power_enable;    // offset 0x54UL
    /// AHB3 peripheral clock enable in low power mode register (AHB3LPENR)
    AHB3PeripheralLowPowerEnable ahb3_peripheral_low_power_enable;    // offset 0x58UL
    uint32_t : 32;                                                    // offset 0x5cUL
    /// APB1 peripheral clock enable in low power mode register (APB1LPENR)
    APB1LowPowerEnable apb1_low_power_enable;    // offset 0x60UL
    /// APB2 peripheral clock enabled in low power mode register (APB2LPENR)
    APB2PeripheralLowPowerEnable apb2_peripheral_low_power_enable;    // offset 0x64UL
    uint32_t : 32;                                                    // offset 0x68UL
    uint32_t : 32;                                                    // offset 0x6cUL
    /// Backup domain control register (BDCR)
    BackupDomainControl backup_domain_control;    // offset 0x70UL
    /// clock control & status register (CSR)
    ClockControlStatus clock_control_status;    // offset 0x74UL
    uint32_t : 32;                              // offset 0x78UL
    uint32_t : 32;                              // offset 0x7cUL
    /// spread spectrum clock generation register (SSCGR)
    SpreadSpectrumClockGeneration spread_spectrum_clock_generation;    // offset 0x80UL
    /// PLLI2S configuration register (PLLI2SCFGR)
    PhaseLockLoopInterIntegratedCircuitSoundConfiguration pll_i2s_configuration;    // offset 0x84UL
    uint32_t : 32;                                                                  // offset 0x88UL
    uint32_t : 32;                                                                  // offset 0x8cUL
    uint32_t : 32;                                                                  // offset 0x90UL
    uint32_t : 32;                                                                  // offset 0x94UL
    uint32_t : 32;                                                                  // offset 0x98UL
    uint32_t : 32;                                                                  // offset 0x9cUL
    uint32_t : 32;                                                                  // offset 0xa0UL
    uint32_t : 32;                                                                  // offset 0xa4UL
    uint32_t : 32;                                                                  // offset 0xa8UL
    uint32_t : 32;                                                                  // offset 0xacUL
    uint32_t : 32;                                                                  // offset 0xb0UL
    uint32_t : 32;                                                                  // offset 0xb4UL
    uint32_t : 32;                                                                  // offset 0xb8UL
    uint32_t : 32;                                                                  // offset 0xbcUL
    uint32_t : 32;                                                                  // offset 0xc0UL
    uint32_t : 32;                                                                  // offset 0xc4UL
    uint32_t : 32;                                                                  // offset 0xc8UL
    uint32_t : 32;                                                                  // offset 0xccUL
    uint32_t : 32;                                                                  // offset 0xd0UL
    uint32_t : 32;                                                                  // offset 0xd4UL
    uint32_t : 32;                                                                  // offset 0xd8UL
    uint32_t : 32;                                                                  // offset 0xdcUL
    uint32_t : 32;                                                                  // offset 0xe0UL
    uint32_t : 32;                                                                  // offset 0xe4UL
    uint32_t : 32;                                                                  // offset 0xe8UL
    uint32_t : 32;                                                                  // offset 0xecUL
    uint32_t : 32;                                                                  // offset 0xf0UL
    uint32_t : 32;                                                                  // offset 0xf4UL
    uint32_t : 32;                                                                  // offset 0xf8UL
    uint32_t : 32;                                                                  // offset 0xfcUL
    uint32_t : 32;                                                                  // offset 0x100UL
    uint32_t : 32;                                                                  // offset 0x104UL
    uint32_t : 32;                                                                  // offset 0x108UL
    uint32_t : 32;                                                                  // offset 0x10cUL
    uint32_t : 32;                                                                  // offset 0x110UL
    uint32_t : 32;                                                                  // offset 0x114UL
    uint32_t : 32;                                                                  // offset 0x118UL
    uint32_t : 32;                                                                  // offset 0x11cUL
    uint32_t : 32;                                                                  // offset 0x120UL
    uint32_t : 32;                                                                  // offset 0x124UL
    uint32_t : 32;                                                                  // offset 0x128UL
    uint32_t : 32;                                                                  // offset 0x12cUL
    uint32_t : 32;                                                                  // offset 0x130UL
    uint32_t : 32;                                                                  // offset 0x134UL
    uint32_t : 32;                                                                  // offset 0x138UL
    uint32_t : 32;                                                                  // offset 0x13cUL
    uint32_t : 32;                                                                  // offset 0x140UL
    uint32_t : 32;                                                                  // offset 0x144UL
    uint32_t : 32;                                                                  // offset 0x148UL
    uint32_t : 32;                                                                  // offset 0x14cUL
    uint32_t : 32;                                                                  // offset 0x150UL
    uint32_t : 32;                                                                  // offset 0x154UL
    uint32_t : 32;                                                                  // offset 0x158UL
    uint32_t : 32;                                                                  // offset 0x15cUL
    uint32_t : 32;                                                                  // offset 0x160UL
    uint32_t : 32;                                                                  // offset 0x164UL
    uint32_t : 32;                                                                  // offset 0x168UL
    uint32_t : 32;                                                                  // offset 0x16cUL
    uint32_t : 32;                                                                  // offset 0x170UL
    uint32_t : 32;                                                                  // offset 0x174UL
    uint32_t : 32;                                                                  // offset 0x178UL
    uint32_t : 32;                                                                  // offset 0x17cUL
    uint32_t : 32;                                                                  // offset 0x180UL
    uint32_t : 32;                                                                  // offset 0x184UL
    uint32_t : 32;                                                                  // offset 0x188UL
    uint32_t : 32;                                                                  // offset 0x18cUL
    uint32_t : 32;                                                                  // offset 0x190UL
    uint32_t : 32;                                                                  // offset 0x194UL
    uint32_t : 32;                                                                  // offset 0x198UL
    uint32_t : 32;                                                                  // offset 0x19cUL
    uint32_t : 32;                                                                  // offset 0x1a0UL
    uint32_t : 32;                                                                  // offset 0x1a4UL
    uint32_t : 32;                                                                  // offset 0x1a8UL
    uint32_t : 32;                                                                  // offset 0x1acUL
    uint32_t : 32;                                                                  // offset 0x1b0UL
    uint32_t : 32;                                                                  // offset 0x1b4UL
    uint32_t : 32;                                                                  // offset 0x1b8UL
    uint32_t : 32;                                                                  // offset 0x1bcUL
    uint32_t : 32;                                                                  // offset 0x1c0UL
    uint32_t : 32;                                                                  // offset 0x1c4UL
    uint32_t : 32;                                                                  // offset 0x1c8UL
    uint32_t : 32;                                                                  // offset 0x1ccUL
    uint32_t : 32;                                                                  // offset 0x1d0UL
    uint32_t : 32;                                                                  // offset 0x1d4UL
    uint32_t : 32;                                                                  // offset 0x1d8UL
    uint32_t : 32;                                                                  // offset 0x1dcUL
    uint32_t : 32;                                                                  // offset 0x1e0UL
    uint32_t : 32;                                                                  // offset 0x1e4UL
    uint32_t : 32;                                                                  // offset 0x1e8UL
    uint32_t : 32;                                                                  // offset 0x1ecUL
    uint32_t : 32;                                                                  // offset 0x1f0UL
    uint32_t : 32;                                                                  // offset 0x1f4UL
    uint32_t : 32;                                                                  // offset 0x1f8UL
    uint32_t : 32;                                                                  // offset 0x1fcUL
    uint32_t : 32;                                                                  // offset 0x200UL
    uint32_t : 32;                                                                  // offset 0x204UL
    uint32_t : 32;                                                                  // offset 0x208UL
    uint32_t : 32;                                                                  // offset 0x20cUL
    uint32_t : 32;                                                                  // offset 0x210UL
    uint32_t : 32;                                                                  // offset 0x214UL
    uint32_t : 32;                                                                  // offset 0x218UL
    uint32_t : 32;                                                                  // offset 0x21cUL
    uint32_t : 32;                                                                  // offset 0x220UL
    uint32_t : 32;                                                                  // offset 0x224UL
    uint32_t : 32;                                                                  // offset 0x228UL
    uint32_t : 32;                                                                  // offset 0x22cUL
    uint32_t : 32;                                                                  // offset 0x230UL
    uint32_t : 32;                                                                  // offset 0x234UL
    uint32_t : 32;                                                                  // offset 0x238UL
    uint32_t : 32;                                                                  // offset 0x23cUL
    uint32_t : 32;                                                                  // offset 0x240UL
    uint32_t : 32;                                                                  // offset 0x244UL
    uint32_t : 32;                                                                  // offset 0x248UL
    uint32_t : 32;                                                                  // offset 0x24cUL
    uint32_t : 32;                                                                  // offset 0x250UL
    uint32_t : 32;                                                                  // offset 0x254UL
    uint32_t : 32;                                                                  // offset 0x258UL
    uint32_t : 32;                                                                  // offset 0x25cUL
    uint32_t : 32;                                                                  // offset 0x260UL
    uint32_t : 32;                                                                  // offset 0x264UL
    uint32_t : 32;                                                                  // offset 0x268UL
    uint32_t : 32;                                                                  // offset 0x26cUL
    uint32_t : 32;                                                                  // offset 0x270UL
    uint32_t : 32;                                                                  // offset 0x274UL
    uint32_t : 32;                                                                  // offset 0x278UL
    uint32_t : 32;                                                                  // offset 0x27cUL
    uint32_t : 32;                                                                  // offset 0x280UL
    uint32_t : 32;                                                                  // offset 0x284UL
    uint32_t : 32;                                                                  // offset 0x288UL
    uint32_t : 32;                                                                  // offset 0x28cUL
    uint32_t : 32;                                                                  // offset 0x290UL
    uint32_t : 32;                                                                  // offset 0x294UL
    uint32_t : 32;                                                                  // offset 0x298UL
    uint32_t : 32;                                                                  // offset 0x29cUL
    uint32_t : 32;                                                                  // offset 0x2a0UL
    uint32_t : 32;                                                                  // offset 0x2a4UL
    uint32_t : 32;                                                                  // offset 0x2a8UL
    uint32_t : 32;                                                                  // offset 0x2acUL
    uint32_t : 32;                                                                  // offset 0x2b0UL
    uint32_t : 32;                                                                  // offset 0x2b4UL
    uint32_t : 32;                                                                  // offset 0x2b8UL
    uint32_t : 32;                                                                  // offset 0x2bcUL
    uint32_t : 32;                                                                  // offset 0x2c0UL
    uint32_t : 32;                                                                  // offset 0x2c4UL
    uint32_t : 32;                                                                  // offset 0x2c8UL
    uint32_t : 32;                                                                  // offset 0x2ccUL
    uint32_t : 32;                                                                  // offset 0x2d0UL
    uint32_t : 32;                                                                  // offset 0x2d4UL
    uint32_t : 32;                                                                  // offset 0x2d8UL
    uint32_t : 32;                                                                  // offset 0x2dcUL
    uint32_t : 32;                                                                  // offset 0x2e0UL
    uint32_t : 32;                                                                  // offset 0x2e4UL
    uint32_t : 32;                                                                  // offset 0x2e8UL
    uint32_t : 32;                                                                  // offset 0x2ecUL
    uint32_t : 32;                                                                  // offset 0x2f0UL
    uint32_t : 32;                                                                  // offset 0x2f4UL
    uint32_t : 32;                                                                  // offset 0x2f8UL
    uint32_t : 32;                                                                  // offset 0x2fcUL
    uint32_t : 32;                                                                  // offset 0x300UL
    uint32_t : 32;                                                                  // offset 0x304UL
    uint32_t : 32;                                                                  // offset 0x308UL
    uint32_t : 32;                                                                  // offset 0x30cUL
    uint32_t : 32;                                                                  // offset 0x310UL
    uint32_t : 32;                                                                  // offset 0x314UL
    uint32_t : 32;                                                                  // offset 0x318UL
    uint32_t : 32;                                                                  // offset 0x31cUL
    uint32_t : 32;                                                                  // offset 0x320UL
    uint32_t : 32;                                                                  // offset 0x324UL
    uint32_t : 32;                                                                  // offset 0x328UL
    uint32_t : 32;                                                                  // offset 0x32cUL
    uint32_t : 32;                                                                  // offset 0x330UL
    uint32_t : 32;                                                                  // offset 0x334UL
    uint32_t : 32;                                                                  // offset 0x338UL
    uint32_t : 32;                                                                  // offset 0x33cUL
    uint32_t : 32;                                                                  // offset 0x340UL
    uint32_t : 32;                                                                  // offset 0x344UL
    uint32_t : 32;                                                                  // offset 0x348UL
    uint32_t : 32;                                                                  // offset 0x34cUL
    uint32_t : 32;                                                                  // offset 0x350UL
    uint32_t : 32;                                                                  // offset 0x354UL
    uint32_t : 32;                                                                  // offset 0x358UL
    uint32_t : 32;                                                                  // offset 0x35cUL
    uint32_t : 32;                                                                  // offset 0x360UL
    uint32_t : 32;                                                                  // offset 0x364UL
    uint32_t : 32;                                                                  // offset 0x368UL
    uint32_t : 32;                                                                  // offset 0x36cUL
    uint32_t : 32;                                                                  // offset 0x370UL
    uint32_t : 32;                                                                  // offset 0x374UL
    uint32_t : 32;                                                                  // offset 0x378UL
    uint32_t : 32;                                                                  // offset 0x37cUL
    uint32_t : 32;                                                                  // offset 0x380UL
    uint32_t : 32;                                                                  // offset 0x384UL
    uint32_t : 32;                                                                  // offset 0x388UL
    uint32_t : 32;                                                                  // offset 0x38cUL
    uint32_t : 32;                                                                  // offset 0x390UL
    uint32_t : 32;                                                                  // offset 0x394UL
    uint32_t : 32;                                                                  // offset 0x398UL
    uint32_t : 32;                                                                  // offset 0x39cUL
    uint32_t : 32;                                                                  // offset 0x3a0UL
    uint32_t : 32;                                                                  // offset 0x3a4UL
    uint32_t : 32;                                                                  // offset 0x3a8UL
    uint32_t : 32;                                                                  // offset 0x3acUL
    uint32_t : 32;                                                                  // offset 0x3b0UL
    uint32_t : 32;                                                                  // offset 0x3b4UL
    uint32_t : 32;                                                                  // offset 0x3b8UL
    uint32_t : 32;                                                                  // offset 0x3bcUL
    uint32_t : 32;                                                                  // offset 0x3c0UL
    uint32_t : 32;                                                                  // offset 0x3c4UL
    uint32_t : 32;                                                                  // offset 0x3c8UL
    uint32_t : 32;                                                                  // offset 0x3ccUL
    uint32_t : 32;                                                                  // offset 0x3d0UL
    uint32_t : 32;                                                                  // offset 0x3d4UL
    uint32_t : 32;                                                                  // offset 0x3d8UL
    uint32_t : 32;                                                                  // offset 0x3dcUL
    uint32_t : 32;                                                                  // offset 0x3e0UL
    uint32_t : 32;                                                                  // offset 0x3e4UL
    uint32_t : 32;                                                                  // offset 0x3e8UL
    uint32_t : 32;                                                                  // offset 0x3ecUL
    uint32_t : 32;                                                                  // offset 0x3f0UL
    uint32_t : 32;                                                                  // offset 0x3f4UL
    uint32_t : 32;                                                                  // offset 0x3f8UL
    uint32_t : 32;                                                                  // offset 0x3fcUL
    //+=MEMORY======================================+
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
static_assert(offsetof(ResetAndClockControl, ahb1_peripheral_low_power_enable) == 0x50UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, ahb2_peripheral_low_power_enable) == 0x54UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, ahb3_peripheral_low_power_enable) == 0x58UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, apb1_low_power_enable) == 0x60UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, apb2_peripheral_low_power_enable) == 0x64UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, backup_domain_control) == 0x70UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, clock_control_status) == 0x74UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, spread_spectrum_clock_generation) == 0x80UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, pll_i2s_configuration) == 0x84UL, "Must be located at this offset");

// Ensure the sizeof the entire structure is correct.
static_assert(sizeof(ResetAndClockControl) == 0x400UL, "Must be this exact size");

}    // namespace f4xx
}    // namespace stm32
#endif    // STM32_F4XX_RESETANDCLOCKCONTROL__HPP_

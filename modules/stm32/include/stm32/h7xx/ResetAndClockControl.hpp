
#ifndef STM32_H7XX_RESETANDCLOCKCONTROL__HPP_
#define STM32_H7XX_RESETANDCLOCKCONTROL__HPP_

/// @file
/// Auto Generated Structure Definitions for ResetAndClockControl from the Peripheralyzer.
/// @copyright

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace stm32 {
namespace h7xx {

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
            uint32_t high_speed_internal_enable                         : 1;    // bit 0
            /// High Speed Internal clock enable in Stop mode (HSIKERON)
            uint32_t high_speed_internal_oscillator_kernel_clock_enable : 1;    // bit 1
            /// HSI clock ready flag (HSIRDY)
            uint32_t high_speed_internal_ready                          : 1;    // bit 2
            /// HSI clock divider (HSIDIV)
            uint32_t high_speed_internal_oscillator_divider             : 2;    // bits 3:4
            /// HSI divider flag (HSIDIVF)
            uint32_t high_speed_internal_oscillator_divider_flag        : 1;    // bit 5
            /// (reserved)
            uint32_t                                                    : 1;    // bit 6
            /// CSI clock enable (CSION)
            uint32_t low_power_internal_oscillator_enable               : 1;    // bit 7
            /// CSI clock ready flag (CSIRDY)
            uint32_t low_power_internal_oscillator_ready                : 1;    // bit 8
            /// CSI clock enable in Stop mode (CSIKERON)
            uint32_t low_power_internal_oscillator_kernel_clock_enable  : 1;    // bit 9
            /// (reserved)
            uint32_t                                                    : 2;    // bits 10:11
            /// RC48 clock enable (RC48ON)
            uint32_t rc48_enable                                        : 1;    // bit 12
            /// RC48 clock ready flag (RC48RDY)
            uint32_t rc48_ready                                         : 1;    // bit 13
            /// D1 domain clocks ready flag (D1CKRDY)
            uint32_t domain1_clock_ready                                : 1;    // bit 14
            /// D2 domain clocks ready flag (D2CKRDY)
            uint32_t domain2_clock_ready                                : 1;    // bit 15
            /// HSE clock enable (HSEON)
            uint32_t high_speed_external_enable                         : 1;    // bit 16
            /// HSE clock ready flag (HSERDY)
            uint32_t high_speed_external_ready                          : 1;    // bit 17
            /// HSE clock bypass (HSEBYP)
            uint32_t high_speed_external_bypass                         : 1;    // bit 18
            /// HSE Clock Security System enable (HSECSSON)
            uint32_t high_speed_external_clock_security_system_enable   : 1;    // bit 19
            /// (reserved)
            uint32_t                                                    : 4;    // bits 20:23
            /// PLL1 enable (PLL1ON)
            uint32_t pll1_enable                                        : 1;    // bit 24
            /// PLL1 clock ready flag (PLL1RDY)
            uint32_t pll1_ready                                         : 1;    // bit 25
            /// PLL2 enable (PLL2ON)
            uint32_t pll2_enable                                        : 1;    // bit 26
            /// PLL2 clock ready flag (PLL2RDY)
            uint32_t pll2_ready                                         : 1;    // bit 27
            /// PLL3 enable (PLL3ON)
            uint32_t pll3_enable                                        : 1;    // bit 28
            /// PLL3 clock ready flag (PLL3RDY)
            uint32_t pll3_ready                                         : 1;    // bit 29
            /// (reserved)
            uint32_t                                                    : 2;    // bits 30:31
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
    /// RCC Internal Clock Source Calibration Register (ICSCR)
    struct InternalClockSourcesCalibration final {
        /// Default Constructor
        InternalClockSourcesCalibration()
            : whole{0u} {}
        /// Copy Constructor from volatile
        InternalClockSourcesCalibration(InternalClockSourcesCalibration volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        InternalClockSourcesCalibration(InternalClockSourcesCalibration const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        InternalClockSourcesCalibration(InternalClockSourcesCalibration&&) = delete;
        /// Parameterized Constructor for constant references
        explicit InternalClockSourcesCalibration(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit InternalClockSourcesCalibration(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~InternalClockSourcesCalibration() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// HSI clock calibration (HSICAL)
            uint32_t high_speed_internal_calibration           : 12;    // bits 0:11
            /// HSI clock trimming (HSITRIM)
            uint32_t high_speed_internal_trim                  : 6;    // bits 12:17
            /// CSI clock calibration (CSICAL)
            uint32_t low_power_internal_oscillator_calibration : 8;    // bits 18:25
            /// CSI clock trimming (CSITRIM)
            uint32_t low_power_internal_oscillator_trim        : 5;    // bits 26:30
            /// (reserved)
            uint32_t                                           : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        InternalClockSourcesCalibration& operator=(InternalClockSourcesCalibration&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(InternalClockSourcesCalibration volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(InternalClockSourcesCalibration const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<InternalClockSourcesCalibration>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(InternalClockSourcesCalibration) == 4UL, "Must be this exact size");
    /// RCC HSI configuration register (HSICFGR)
    struct HighSpeedInternalConfiguration final {
        /// Default Constructor
        HighSpeedInternalConfiguration()
            : whole{0u} {}
        /// Copy Constructor from volatile
        HighSpeedInternalConfiguration(HighSpeedInternalConfiguration volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        HighSpeedInternalConfiguration(HighSpeedInternalConfiguration const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        HighSpeedInternalConfiguration(HighSpeedInternalConfiguration&&) = delete;
        /// Parameterized Constructor for constant references
        explicit HighSpeedInternalConfiguration(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit HighSpeedInternalConfiguration(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~HighSpeedInternalConfiguration() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// HSI clock calibration (HSICAL)
            uint32_t high_speed_internal_calibration : 12;    // bits 0:11
            /// (reserved)
            uint32_t                                 : 12;    // bits 12:23
            /// HSI clock trimming (HSITRIM)
            uint32_t high_speed_internal_trim        : 7;    // bits 24:30
            /// (reserved)
            uint32_t                                 : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        HighSpeedInternalConfiguration& operator=(HighSpeedInternalConfiguration&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(HighSpeedInternalConfiguration volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(HighSpeedInternalConfiguration const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<HighSpeedInternalConfiguration>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(HighSpeedInternalConfiguration) == 4UL, "Must be this exact size");
    /// RCC Clock Recovery RC Register (CRRCR)
    struct ClockRecoveryCalibrationControl final {
        /// Default Constructor
        ClockRecoveryCalibrationControl()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ClockRecoveryCalibrationControl(ClockRecoveryCalibrationControl volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ClockRecoveryCalibrationControl(ClockRecoveryCalibrationControl const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ClockRecoveryCalibrationControl(ClockRecoveryCalibrationControl&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ClockRecoveryCalibrationControl(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ClockRecoveryCalibrationControl(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ClockRecoveryCalibrationControl() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Internal RC 48 MHz clock calibration (RC48CAL)
            uint32_t rc48_calibration : 10;    // bits 0:9
            /// (reserved)
            uint32_t                  : 22;    // bits 10:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ClockRecoveryCalibrationControl& operator=(ClockRecoveryCalibrationControl&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ClockRecoveryCalibrationControl volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ClockRecoveryCalibrationControl const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ClockRecoveryCalibrationControl>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ClockRecoveryCalibrationControl) == 4UL, "Must be this exact size");
    /// RCC Clock Configuration Register (CFGR)
    struct Configuration final {
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
            uint32_t system_clock_switch          : 3;    // bits 0:2
            /// System clock switch status (SWS)
            uint32_t system_clock_switch_status   : 3;    // bits 3:5
            /// System clock selection after a wake up from system Stop (STOPWUCK)
            uint32_t stop_wakeup_clock            : 1;    // bit 6
            /// Kernel clock selection after a wake up from system Stop (STOPKERWUCK)
            uint32_t stop_kernel_wakeup_clock     : 1;    // bit 7
            /// HSE division factor for RTC clock (RTCPRE)
            uint32_t real_time_clock_prescaler    : 6;    // bits 8:13
            /// High Resolution Timer clock prescaler selection (HRTIMSEL)
            uint32_t high_resolution_timer_select : 1;    // bit 14
            /// Timers clocks prescaler selection (TIMPRE)
            uint32_t timers_clock_prescaler       : 1;    // bit 15
            /// (reserved)
            uint32_t                              : 2;    // bits 16:17
            /// MCO1 prescaler (MCO1PRE)
            uint32_t mco1_prescaler               : 4;    // bits 18:21
            /// Micro-controller clock output 1 (MCO1SEL)
            uint32_t mco1_selection               : 3;    // bits 22:24
            /// MCO2 prescaler (MCO2PRE)
            uint32_t mco2_prescaler               : 4;    // bits 25:28
            /// Micro-controller clock output 2 (MCO2SEL)
            uint32_t mco2_selection               : 3;    // bits 29:31
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
    /// RCC Domain 1 Clock Configuration Register (D1CFGR)
    struct Domain1ClockConfiguration final {
        /// Default Constructor
        Domain1ClockConfiguration()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Domain1ClockConfiguration(Domain1ClockConfiguration volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Domain1ClockConfiguration(Domain1ClockConfiguration const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Domain1ClockConfiguration(Domain1ClockConfiguration&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Domain1ClockConfiguration(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Domain1ClockConfiguration(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Domain1ClockConfiguration() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// D1 domain AHB prescaler (HPRE)
            uint32_t ahb_prescaler                : 4;    // bits 0:3
            /// D1 domain APB3 prescaler (D1PPRE)
            uint32_t domain1_peripheral_prescaler : 3;    // bits 4:6
            /// (reserved)
            uint32_t                              : 1;    // bit 7
            /// D1 domain Core prescaler (D1CPRE)
            uint32_t domain1_core_prescaler       : 4;    // bits 8:11
            /// (reserved)
            uint32_t                              : 20;    // bits 12:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Domain1ClockConfiguration& operator=(Domain1ClockConfiguration&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Domain1ClockConfiguration volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Domain1ClockConfiguration const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Domain1ClockConfiguration>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Domain1ClockConfiguration) == 4UL, "Must be this exact size");
    /// RCC Domain 2 Clock Configuration Register (D2CFGR)
    struct Domain2ClockConfiguration final {
        /// Default Constructor
        Domain2ClockConfiguration()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Domain2ClockConfiguration(Domain2ClockConfiguration volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Domain2ClockConfiguration(Domain2ClockConfiguration const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Domain2ClockConfiguration(Domain2ClockConfiguration&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Domain2ClockConfiguration(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Domain2ClockConfiguration(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Domain2ClockConfiguration() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                               : 4;    // bits 0:3
            /// D2 domain APB1 prescaler (D2PPRE1)
            uint32_t domain2_peripheral1_prescaler : 3;    // bits 4:6
            /// (reserved)
            uint32_t                               : 1;    // bit 7
            /// D2 domain APB2 prescaler (D2PPRE2)
            uint32_t domain2_peripheral2_prescaler : 3;    // bits 8:10
            /// (reserved)
            uint32_t                               : 21;    // bits 11:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Domain2ClockConfiguration& operator=(Domain2ClockConfiguration&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Domain2ClockConfiguration volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Domain2ClockConfiguration const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Domain2ClockConfiguration>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Domain2ClockConfiguration) == 4UL, "Must be this exact size");
    /// RCC Domain 3 Clock Configuration Register (D3CFGR)
    struct Domain3ClockConfiguration final {
        /// Default Constructor
        Domain3ClockConfiguration()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Domain3ClockConfiguration(Domain3ClockConfiguration volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Domain3ClockConfiguration(Domain3ClockConfiguration const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Domain3ClockConfiguration(Domain3ClockConfiguration&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Domain3ClockConfiguration(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Domain3ClockConfiguration(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Domain3ClockConfiguration() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                              : 4;    // bits 0:3
            /// D3 domain APB4 prescaler (D3PPRE)
            uint32_t domain3_peripheral_prescaler : 3;    // bits 4:6
            /// (reserved)
            uint32_t                              : 25;    // bits 7:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Domain3ClockConfiguration& operator=(Domain3ClockConfiguration&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Domain3ClockConfiguration volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Domain3ClockConfiguration const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Domain3ClockConfiguration>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Domain3ClockConfiguration) == 4UL, "Must be this exact size");
    /// RCC PLLs Clock Source Selection Register (PLLCKSELR)
    struct PllClockSourceSelection final {
        /// Default Constructor
        PllClockSourceSelection()
            : whole{0u} {}
        /// Copy Constructor from volatile
        PllClockSourceSelection(PllClockSourceSelection volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        PllClockSourceSelection(PllClockSourceSelection const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        PllClockSourceSelection(PllClockSourceSelection&&) = delete;
        /// Parameterized Constructor for constant references
        explicit PllClockSourceSelection(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit PllClockSourceSelection(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~PllClockSourceSelection() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// DIVMx and PLLs clock source selection (PLLSRC)
            uint32_t main_pll_source    : 2;    // bits 0:1
            /// (reserved)
            uint32_t                    : 2;    // bits 2:3
            /// Prescaler for PLL1 (DIVM1)
            uint32_t pll1_input_divider : 6;    // bits 4:9
            /// (reserved)
            uint32_t                    : 2;    // bits 10:11
            /// Prescaler for PLL2 (DIVM2)
            uint32_t pll2_input_divider : 6;    // bits 12:17
            /// (reserved)
            uint32_t                    : 2;    // bits 18:19
            /// Prescaler for PLL3 (DIVM3)
            uint32_t pll3_input_divider : 6;    // bits 20:25
            /// (reserved)
            uint32_t                    : 6;    // bits 26:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        PllClockSourceSelection& operator=(PllClockSourceSelection&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PllClockSourceSelection volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PllClockSourceSelection const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<PllClockSourceSelection>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(PllClockSourceSelection) == 4UL, "Must be this exact size");
    /// RCC PLLs Configuration Register (PLLCFGR)
    struct PhaseLockLoopConfiguration final {
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
            /// PLL1 fractional latch enable (PLL1FRACEN)
            uint32_t pll1_fractional_enable : 1;    // bit 0
            /// PLL1 VCO selection (PLL1VCOSEL)
            uint32_t pll1_vco_selection     : 1;    // bit 1
            /// PLL1 input frequency range (PLL1RGE)
            uint32_t pll1_input_range       : 2;    // bits 2:3
            /// PLL2 fractional latch enable (PLL2FRACEN)
            uint32_t pll2_fractional_enable : 1;    // bit 4
            /// PLL2 VCO selection (PLL2VCOSEL)
            uint32_t pll2_vco_selection     : 1;    // bit 5
            /// PLL2 input frequency range (PLL2RGE)
            uint32_t pll2_input_range       : 2;    // bits 6:7
            /// PLL3 fractional latch enable (PLL3FRACEN)
            uint32_t pll3_fractional_enable : 1;    // bit 8
            /// PLL3 VCO selection (PLL3VCOSEL)
            uint32_t pll3_vco_selection     : 1;    // bit 9
            /// PLL3 input frequency range (PLL3RGE)
            uint32_t pll3_input_range       : 2;    // bits 10:11
            /// (reserved)
            uint32_t                        : 4;    // bits 12:15
            /// PLL1 DIVP divider output enable (DIVP1EN)
            uint32_t divider_p1_enable      : 1;    // bit 16
            /// PLL1 DIVQ divider output enable (DIVQ1EN)
            uint32_t divider_q1_enable      : 1;    // bit 17
            /// PLL1 DIVR divider output enable (DIVR1EN)
            uint32_t divider_r1_enable      : 1;    // bit 18
            /// PLL2 DIVP divider output enable (DIVP2EN)
            uint32_t divider_p2_enable      : 1;    // bit 19
            /// PLL2 DIVQ divider output enable (DIVQ2EN)
            uint32_t divider_q2_enable      : 1;    // bit 20
            /// PLL2 DIVR divider output enable (DIVR2EN)
            uint32_t divider_r2_enable      : 1;    // bit 21
            /// PLL3 DIVP divider output enable (DIVP3EN)
            uint32_t divider_p3_enable      : 1;    // bit 22
            /// PLL3 DIVQ divider output enable (DIVQ3EN)
            uint32_t divider_q3_enable      : 1;    // bit 23
            /// PLL3 DIVR divider output enable (DIVR3EN)
            uint32_t divider_r3_enable      : 1;    // bit 24
            /// (reserved)
            uint32_t                        : 7;    // bits 25:31
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
    /// RCC PLL1 Dividers Configuration Register (PLL1DIVR)
    struct Pll1DividerConfiguration final {
        /// Default Constructor
        Pll1DividerConfiguration()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Pll1DividerConfiguration(Pll1DividerConfiguration volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Pll1DividerConfiguration(Pll1DividerConfiguration const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Pll1DividerConfiguration(Pll1DividerConfiguration&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Pll1DividerConfiguration(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Pll1DividerConfiguration(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Pll1DividerConfiguration() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Multiplication factor for PLL1 VCO (DIVN1)
            uint32_t divider_n1 : 9;    // bits 0:8
            /// PLL1 DIVP division factor (DIVP1)
            uint32_t divider_p1 : 7;    // bits 9:15
            /// PLL1 DIVQ division factor (DIVQ1)
            uint32_t divider_q1 : 7;    // bits 16:22
            /// (reserved)
            uint32_t            : 1;    // bit 23
            /// PLL1 DIVR division factor (DIVR1)
            uint32_t divider_r1 : 7;    // bits 24:30
            /// (reserved)
            uint32_t            : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Pll1DividerConfiguration& operator=(Pll1DividerConfiguration&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Pll1DividerConfiguration volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Pll1DividerConfiguration const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Pll1DividerConfiguration>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Pll1DividerConfiguration) == 4UL, "Must be this exact size");
    /// RCC PLL1 Fractional Divider Register (PLL1FRACR)
    struct Pll1FractionalConfiguration final {
        /// Default Constructor
        Pll1FractionalConfiguration()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Pll1FractionalConfiguration(Pll1FractionalConfiguration volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Pll1FractionalConfiguration(Pll1FractionalConfiguration const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Pll1FractionalConfiguration(Pll1FractionalConfiguration&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Pll1FractionalConfiguration(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Pll1FractionalConfiguration(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Pll1FractionalConfiguration() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t               : 3;    // bits 0:2
            /// Fractional part of the multiplication factor for PLL1 VCO (FRACN1)
            uint32_t fractional_n1 : 13;    // bits 3:15
            /// (reserved)
            uint32_t               : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Pll1FractionalConfiguration& operator=(Pll1FractionalConfiguration&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Pll1FractionalConfiguration volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Pll1FractionalConfiguration const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Pll1FractionalConfiguration>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Pll1FractionalConfiguration) == 4UL, "Must be this exact size");
    /// RCC PLL2 Dividers Configuration Register (PLL2DIVR)
    struct Pll2DividerConfiguration final {
        /// Default Constructor
        Pll2DividerConfiguration()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Pll2DividerConfiguration(Pll2DividerConfiguration volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Pll2DividerConfiguration(Pll2DividerConfiguration const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Pll2DividerConfiguration(Pll2DividerConfiguration&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Pll2DividerConfiguration(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Pll2DividerConfiguration(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Pll2DividerConfiguration() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Multiplication factor for PLL1 VCO (DIVN2)
            uint32_t divider_n2 : 9;    // bits 0:8
            /// PLL1 DIVP division factor (DIVP2)
            uint32_t divider_p2 : 7;    // bits 9:15
            /// PLL1 DIVQ division factor (DIVQ2)
            uint32_t divider_q2 : 7;    // bits 16:22
            /// (reserved)
            uint32_t            : 1;    // bit 23
            /// PLL1 DIVR division factor (DIVR2)
            uint32_t divider_r2 : 7;    // bits 24:30
            /// (reserved)
            uint32_t            : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Pll2DividerConfiguration& operator=(Pll2DividerConfiguration&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Pll2DividerConfiguration volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Pll2DividerConfiguration const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Pll2DividerConfiguration>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Pll2DividerConfiguration) == 4UL, "Must be this exact size");
    /// RCC PLL2 Fractional Divider Register (PLL2FRACR)
    struct Pll2FractionalConfiguration final {
        /// Default Constructor
        Pll2FractionalConfiguration()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Pll2FractionalConfiguration(Pll2FractionalConfiguration volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Pll2FractionalConfiguration(Pll2FractionalConfiguration const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Pll2FractionalConfiguration(Pll2FractionalConfiguration&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Pll2FractionalConfiguration(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Pll2FractionalConfiguration(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Pll2FractionalConfiguration() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t               : 3;    // bits 0:2
            /// Fractional part of the multiplication factor for PLL VCO (FRACN2)
            uint32_t fractional_n2 : 13;    // bits 3:15
            /// (reserved)
            uint32_t               : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Pll2FractionalConfiguration& operator=(Pll2FractionalConfiguration&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Pll2FractionalConfiguration volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Pll2FractionalConfiguration const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Pll2FractionalConfiguration>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Pll2FractionalConfiguration) == 4UL, "Must be this exact size");
    /// RCC PLL3 Dividers Configuration Register (PLL3DIVR)
    struct Pll3DividerConfiguration final {
        /// Default Constructor
        Pll3DividerConfiguration()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Pll3DividerConfiguration(Pll3DividerConfiguration volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Pll3DividerConfiguration(Pll3DividerConfiguration const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Pll3DividerConfiguration(Pll3DividerConfiguration&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Pll3DividerConfiguration(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Pll3DividerConfiguration(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Pll3DividerConfiguration() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Multiplication factor for PLL1 VCO (DIVN3)
            uint32_t divider_n3 : 9;    // bits 0:8
            /// PLL DIVP division factor (DIVP3)
            uint32_t divider_p3 : 7;    // bits 9:15
            /// PLL DIVQ division factor (DIVQ3)
            uint32_t divider_q3 : 7;    // bits 16:22
            /// (reserved)
            uint32_t            : 1;    // bit 23
            /// PLL DIVR division factor (DIVR3)
            uint32_t divider_r3 : 7;    // bits 24:30
            /// (reserved)
            uint32_t            : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Pll3DividerConfiguration& operator=(Pll3DividerConfiguration&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Pll3DividerConfiguration volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Pll3DividerConfiguration const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Pll3DividerConfiguration>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Pll3DividerConfiguration) == 4UL, "Must be this exact size");
    /// RCC PLL3 Fractional Divider Register (PLL3FRACR)
    struct Pll3FractionalConfiguration final {
        /// Default Constructor
        Pll3FractionalConfiguration()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Pll3FractionalConfiguration(Pll3FractionalConfiguration volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Pll3FractionalConfiguration(Pll3FractionalConfiguration const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Pll3FractionalConfiguration(Pll3FractionalConfiguration&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Pll3FractionalConfiguration(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Pll3FractionalConfiguration(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Pll3FractionalConfiguration() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t               : 3;    // bits 0:2
            /// Fractional part of the multiplication factor for PLL3 VCO (FRACN3)
            uint32_t fractional_n3 : 13;    // bits 3:15
            /// (reserved)
            uint32_t               : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Pll3FractionalConfiguration& operator=(Pll3FractionalConfiguration&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Pll3FractionalConfiguration volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Pll3FractionalConfiguration const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Pll3FractionalConfiguration>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Pll3FractionalConfiguration) == 4UL, "Must be this exact size");
    /// RCC Domain 1 Kernel Clock Configuration Register (D1CCIPR)
    struct Domain1PeripheralClockSelection final {
        /// Default Constructor
        Domain1PeripheralClockSelection()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Domain1PeripheralClockSelection(Domain1PeripheralClockSelection volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Domain1PeripheralClockSelection(Domain1PeripheralClockSelection const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Domain1PeripheralClockSelection(Domain1PeripheralClockSelection&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Domain1PeripheralClockSelection(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Domain1PeripheralClockSelection(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Domain1PeripheralClockSelection() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// FMC kernel clock source selection (FMCSEL)
            uint32_t fmc_clock_selection   : 2;    // bits 0:1
            /// (reserved)
            uint32_t                       : 2;    // bits 2:3
            /// QUADSPI kernel clock source selection (QSPISEL)
            uint32_t qspi_clock_selection  : 2;    // bits 4:5
            /// (reserved)
            uint32_t                       : 10;    // bits 6:15
            /// SDMMC kernel clock source selection (SDMMCSEL)
            uint32_t sdmmc_clock_selection : 1;    // bit 16
            /// (reserved)
            uint32_t                       : 11;    // bits 17:27
            /// per_ck clock source selection (CKPERSEL)
            uint32_t ckper_clock_selection : 2;    // bits 28:29
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
        Domain1PeripheralClockSelection& operator=(Domain1PeripheralClockSelection&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Domain1PeripheralClockSelection volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Domain1PeripheralClockSelection const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Domain1PeripheralClockSelection>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Domain1PeripheralClockSelection) == 4UL, "Must be this exact size");
    /// RCC Domain 2 Kernel Clock Configuration Register (D2CCIP1R)
    struct Domain2PeripheralClockSelection1 final {
        /// Default Constructor
        Domain2PeripheralClockSelection1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Domain2PeripheralClockSelection1(Domain2PeripheralClockSelection1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Domain2PeripheralClockSelection1(Domain2PeripheralClockSelection1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Domain2PeripheralClockSelection1(Domain2PeripheralClockSelection1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Domain2PeripheralClockSelection1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Domain2PeripheralClockSelection1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Domain2PeripheralClockSelection1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// SAI1 and DFSDM1 kernel Aclk clock source selection (SAI1SEL)
            uint32_t sai1_clock_selection   : 3;    // bits 0:2
            /// (reserved)
            uint32_t                        : 3;    // bits 3:5
            /// SAI2 and SAI3 kernel clock source selection (SAI23SEL)
            uint32_t sai23_clock_selection  : 3;    // bits 6:8
            /// (reserved)
            uint32_t                        : 3;    // bits 9:11
            /// SPI/I2S1,2 and 3 kernel clock source selection (SPI123SEL)
            uint32_t spi123_clock_selection : 3;    // bits 12:14
            /// (reserved)
            uint32_t                        : 1;    // bit 15
            /// SPI4 and 5 kernel clock source selection (SPI45SEL)
            uint32_t spi45_clock_selection  : 3;    // bits 16:18
            /// (reserved)
            uint32_t                        : 1;    // bit 19
            /// SPDIFRX kernel clock source selection (SPDIFSEL)
            uint32_t spdif_clock_selection  : 2;    // bits 20:21
            /// (reserved)
            uint32_t                        : 2;    // bits 22:23
            /// DFSDM1 kernel Clk clock source selection (DFSDM1SEL)
            uint32_t dfsdm1_clock_selection : 1;    // bit 24
            /// (reserved)
            uint32_t                        : 3;    // bits 25:27
            /// FDCAN kernel clock source selection (FDCANSEL)
            uint32_t fdcan_clock_selection  : 2;    // bits 28:29
            /// (reserved)
            uint32_t                        : 1;    // bit 30
            /// SWPMI kernel clock source selection (SWPSEL)
            uint32_t swp_clock_selection    : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Domain2PeripheralClockSelection1& operator=(Domain2PeripheralClockSelection1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Domain2PeripheralClockSelection1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Domain2PeripheralClockSelection1 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Domain2PeripheralClockSelection1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Domain2PeripheralClockSelection1) == 4UL, "Must be this exact size");
    /// RCC Domain 2 Kernel Clock Configuration Register (D2CCIP2R)
    struct Domain2PeripheralClockSelection2 final {
        /// Default Constructor
        Domain2PeripheralClockSelection2()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Domain2PeripheralClockSelection2(Domain2PeripheralClockSelection2 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Domain2PeripheralClockSelection2(Domain2PeripheralClockSelection2 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Domain2PeripheralClockSelection2(Domain2PeripheralClockSelection2&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Domain2PeripheralClockSelection2(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Domain2PeripheralClockSelection2(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Domain2PeripheralClockSelection2() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// USART2/3, UART4,5, 7/8 (APB1) kernel clock source selection (USART234578SEL)
            uint32_t usart234578_clock_selection : 3;    // bits 0:2
            /// USART1 and 6 kernel clock source selection (USART16SEL)
            uint32_t usart16_clock_selection     : 3;    // bits 3:5
            /// (reserved)
            uint32_t                             : 2;    // bits 6:7
            /// RNG kernel clock source selection (RNGSEL)
            uint32_t clock_selection             : 2;    // bits 8:9
            /// (reserved)
            uint32_t                             : 2;    // bits 10:11
            /// I2C1,2,3 kernel clock source selection (I2C123SEL)
            uint32_t i2c123_clock_selection      : 2;    // bits 12:13
            /// (reserved)
            uint32_t                             : 6;    // bits 14:19
            /// USBOTG 1 and 2 kernel clock source selection (USBSEL)
            uint32_t usb_clock_selection         : 2;    // bits 20:21
            /// HDMI-CEC kernel clock source selection (CECSEL)
            uint32_t cec_clock_selection         : 2;    // bits 22:23
            /// (reserved)
            uint32_t                             : 4;    // bits 24:27
            /// LPTIM1 kernel clock source selection (LPTIM1SEL)
            uint32_t lptimer1_clock_selection    : 3;    // bits 28:30
            /// (reserved)
            uint32_t                             : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Domain2PeripheralClockSelection2& operator=(Domain2PeripheralClockSelection2&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Domain2PeripheralClockSelection2 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Domain2PeripheralClockSelection2 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Domain2PeripheralClockSelection2>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Domain2PeripheralClockSelection2) == 4UL, "Must be this exact size");
    /// RCC Domain 3 Kernel Clock Configuration Register (D3CCIPR)
    struct Domain3PeripheralClockSelection final {
        /// Default Constructor
        Domain3PeripheralClockSelection()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Domain3PeripheralClockSelection(Domain3PeripheralClockSelection volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Domain3PeripheralClockSelection(Domain3PeripheralClockSelection const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Domain3PeripheralClockSelection(Domain3PeripheralClockSelection&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Domain3PeripheralClockSelection(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Domain3PeripheralClockSelection(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Domain3PeripheralClockSelection() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// LPUART1 kernel clock source selection (LPUART1SEL)
            uint32_t lpuart1_clock_selection    : 3;    // bits 0:2
            /// (reserved)
            uint32_t                            : 5;    // bits 3:7
            /// I2C4 kernel clock source selection (I2C4SEL)
            uint32_t i2c4_clock_selection       : 2;    // bits 8:9
            /// LPTIM2 kernel clock source selection (LPTIM2SEL)
            uint32_t lptimer2_clock_selection   : 3;    // bits 10:12
            /// LPTIM3,4,5 kernel clock source selection (LPTIM345SEL)
            uint32_t lptimer345_clock_selection : 3;    // bits 13:15
            /// SAR ADC kernel clock source selection (ADCSEL)
            uint32_t adc_clock_selection        : 2;    // bits 16:17
            /// (reserved)
            uint32_t                            : 3;    // bits 18:20
            /// Sub-Block A of SAI4 kernel clock source selection (SAI4ASEL)
            uint32_t sai4a_clock_selection      : 3;    // bits 21:23
            /// Sub-Block B of SAI4 kernel clock source selection (SAI4BSEL)
            uint32_t sai4b_clock_selection      : 3;    // bits 24:26
            /// (reserved)
            uint32_t                            : 1;    // bit 27
            /// SPI6 kernel clock source selection (SPI6SEL)
            uint32_t spi6_clock_selection       : 3;    // bits 28:30
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
        Domain3PeripheralClockSelection& operator=(Domain3PeripheralClockSelection&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Domain3PeripheralClockSelection volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Domain3PeripheralClockSelection const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Domain3PeripheralClockSelection>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Domain3PeripheralClockSelection) == 4UL, "Must be this exact size");
    /// RCC Clock Source Interrupt Enable Register (CIER)
    struct ClockInterruptEnable final {
        /// Default Constructor
        ClockInterruptEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ClockInterruptEnable(ClockInterruptEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ClockInterruptEnable(ClockInterruptEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ClockInterruptEnable(ClockInterruptEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ClockInterruptEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ClockInterruptEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ClockInterruptEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// LSI ready Interrupt Enable (LSIRDYIE)
            uint32_t low_speed_internal_ready_interrupt_enable                 : 1;    // bit 0
            /// LSE ready Interrupt Enable (LSERDYIE)
            uint32_t low_speed_external_ready_interrupt_enable                 : 1;    // bit 1
            /// HSI ready Interrupt Enable (HSIRDYIE)
            uint32_t high_speed_internal_ready_interrupt_enable                : 1;    // bit 2
            /// HSE ready Interrupt Enable (HSERDYIE)
            uint32_t high_speed_external_ready_interrupt_enable                : 1;    // bit 3
            /// CSI ready Interrupt Enable (CSIRDYIE)
            uint32_t low_power_internal_oscillator_ready_interrupt_enable      : 1;    // bit 4
            /// RC48 ready Interrupt Enable (RC48RDYIE)
            uint32_t rc48_ready_interrupt_enable                               : 1;    // bit 5
            /// PLL1 ready Interrupt Enable (PLL1RDYIE)
            uint32_t pll1_ready_interrupt_enable                               : 1;    // bit 6
            /// PLL2 ready Interrupt Enable (PLL2RDYIE)
            uint32_t pll2_ready_interrupt_enable                               : 1;    // bit 7
            /// PLL3 ready Interrupt Enable (PLL3RDYIE)
            uint32_t pll3_ready_interrupt_enable                               : 1;    // bit 8
            /// LSE clock security system Interrupt Enable (LSECSSIE)
            uint32_t low_speed_external_clock_security_system_interrupt_enable : 1;    // bit 9
            /// (reserved)
            uint32_t                                                           : 22;    // bits 10:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ClockInterruptEnable& operator=(ClockInterruptEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ClockInterruptEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ClockInterruptEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ClockInterruptEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ClockInterruptEnable) == 4UL, "Must be this exact size");
    /// RCC Clock Source Interrupt Flag Register (CIFR)
    struct ClockInterruptFlags final {
        /// Default Constructor
        ClockInterruptFlags()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ClockInterruptFlags(ClockInterruptFlags volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ClockInterruptFlags(ClockInterruptFlags const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ClockInterruptFlags(ClockInterruptFlags&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ClockInterruptFlags(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ClockInterruptFlags(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ClockInterruptFlags() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// LSI ready Interrupt Flag (LSIRDYF)
            uint32_t low_speed_internal_ready_flag                  : 1;    // bit 0
            /// LSE ready Interrupt Flag (LSERDYF)
            uint32_t low_speed_external_ready_flag                  : 1;    // bit 1
            /// HSI ready Interrupt Flag (HSIRDYF)
            uint32_t high_speed_internal_ready_flag                 : 1;    // bit 2
            /// HSE ready Interrupt Flag (HSERDYF)
            uint32_t high_speed_external_ready_flag                 : 1;    // bit 3
            /// CSI ready Interrupt Flag (CSIRDY)
            uint32_t low_power_internal_oscillator_ready            : 1;    // bit 4
            /// RC48 ready Interrupt Flag (RC48RDYF)
            uint32_t rc48_ready_flag                                : 1;    // bit 5
            /// PLL1 ready Interrupt Flag (PLL1RDYF)
            uint32_t pll1_ready_flag                                : 1;    // bit 6
            /// PLL2 ready Interrupt Flag (PLL2RDYF)
            uint32_t pll2_ready_flag                                : 1;    // bit 7
            /// PLL3 ready Interrupt Flag (PLL3RDYF)
            uint32_t pll3_ready_flag                                : 1;    // bit 8
            /// LSE clock security system Interrupt Flag (LSECSSF)
            uint32_t low_speed_external_clock_security_system_flag  : 1;    // bit 9
            /// HSE clock security system Interrupt Flag (HSECSSF)
            uint32_t high_speed_external_clock_security_system_flag : 1;    // bit 10
            /// (reserved)
            uint32_t                                                : 21;    // bits 11:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ClockInterruptFlags& operator=(ClockInterruptFlags&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ClockInterruptFlags volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ClockInterruptFlags const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ClockInterruptFlags>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ClockInterruptFlags) == 4UL, "Must be this exact size");
    /// RCC Clock Source Interrupt Clear Register (CICR)
    struct ClockInterruptClear final {
        /// Default Constructor
        ClockInterruptClear()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ClockInterruptClear(ClockInterruptClear volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ClockInterruptClear(ClockInterruptClear const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ClockInterruptClear(ClockInterruptClear&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ClockInterruptClear(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ClockInterruptClear(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ClockInterruptClear() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// LSI ready Interrupt Clear (LSIRDYC)
            uint32_t low_speed_internal_ready_interrupt_clear            : 1;    // bit 0
            /// LSE ready Interrupt Clear (LSERDYC)
            uint32_t low_speed_external_ready_interrupt_clear            : 1;    // bit 1
            /// HSI ready Interrupt Clear (HSIRDYC)
            uint32_t high_speed_internal_ready_clear                     : 1;    // bit 2
            /// HSE ready Interrupt Clear (HSERDYC)
            uint32_t high_speed_external_ready_interrupt_clear           : 1;    // bit 3
            /// CSI ready Interrupt Clear (CSIRDYC)
            uint32_t low_power_internal_oscillator_ready_interrupt_clear : 1;    // bit 4
            /// RC48 ready Interrupt Clear (RC48RDYC)
            uint32_t rc48_ready_clear                                    : 1;    // bit 5
            /// PLL1 ready Interrupt Clear (PLL1RDYC)
            uint32_t pll1_ready_clear                                    : 1;    // bit 6
            /// PLL2 ready Interrupt Clear (PLL2RDYC)
            uint32_t pll2_ready_clear                                    : 1;    // bit 7
            /// PLL3 ready Interrupt Clear (PLL3RDYC)
            uint32_t pll3_ready_clear                                    : 1;    // bit 8
            /// LSE clock security system Interrupt Clear (LSECSSC)
            uint32_t low_speed_external_clock_security_system_clear      : 1;    // bit 9
            /// HSE clock security system Interrupt Clear (HSECSSC)
            uint32_t high_speed_external_clock_security_system_clear     : 1;    // bit 10
            /// (reserved)
            uint32_t                                                     : 21;    // bits 11:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ClockInterruptClear& operator=(ClockInterruptClear&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ClockInterruptClear volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ClockInterruptClear const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ClockInterruptClear>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ClockInterruptClear) == 4UL, "Must be this exact size");
    /// RCC Backup Domain Control Register (BDCR)
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
            /// LSE oscillator enabled (LSEON)
            uint32_t low_speed_external_enable                         : 1;    // bit 0
            /// LSE oscillator ready (LSERDY)
            uint32_t low_speed_external_ready                          : 1;    // bit 1
            /// LSE oscillator bypass (LSEBYP)
            uint32_t low_speed_external_bypass                         : 1;    // bit 2
            /// LSE oscillator driving capability (LSEDRV)
            uint32_t low_speed_external_drive_strength                 : 2;    // bits 3:4
            /// LSE clock security system enable (LSECSSON)
            uint32_t low_speed_external_clock_security_system_enable   : 1;    // bit 5
            /// LSE clock security system failure detection (LSECSSD)
            uint32_t low_speed_external_clock_security_system_detected : 1;    // bit 6
            /// (reserved)
            uint32_t                                                   : 1;    // bit 7
            /// RTC clock source selection (RTCSRC)
            uint32_t real_time_clock_source                            : 2;    // bits 8:9
            /// (reserved)
            uint32_t                                                   : 5;    // bits 10:14
            /// RTC clock enable (RTCEN)
            uint32_t real_time_clock_enable                            : 1;    // bit 15
            /// VSwitch domain software reset (VSWRST)
            uint32_t vsw_reset                                         : 1;    // bit 16
            /// (reserved)
            uint32_t                                                   : 15;    // bits 17:31
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
    /// RCC Clock Control and Status Register (CSR)
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
            /// LSI oscillator enable (LSION)
            uint32_t low_speed_internal_enable : 1;    // bit 0
            /// LSI oscillator ready (LSIRDY)
            uint32_t low_speed_internal_ready  : 1;    // bit 1
            /// (reserved)
            uint32_t                           : 30;    // bits 2:31
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
    /// RCC AHB3 Reset Register (AHB3RSTR)
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
            /// MDMA block reset (MDMARST)
            uint32_t mdma_reset   : 1;    // bit 0
            /// (reserved)
            uint32_t              : 3;    // bits 1:3
            /// DMA2D block reset (DMA2DRST)
            uint32_t dma2d_reset  : 1;    // bit 4
            /// JPGDEC block reset (JPGDECRST)
            uint32_t jpgdec_reset : 1;    // bit 5
            /// (reserved)
            uint32_t              : 6;    // bits 6:11
            /// FMC block reset (FMCRST)
            uint32_t fmc_reset    : 1;    // bit 12
            /// (reserved)
            uint32_t              : 1;    // bit 13
            /// QUADSPI and QUADSPI delay block reset (QSPIRST)
            uint32_t qspi_reset   : 1;    // bit 14
            /// (reserved)
            uint32_t              : 1;    // bit 15
            /// SDMMC1 and SDMMC1 delay block reset (SDMMC1RST)
            uint32_t sdmmc1_reset : 1;    // bit 16
            /// (reserved)
            uint32_t              : 14;    // bits 17:30
            /// CPU reset (CPURST)
            uint32_t cpu_reset    : 1;    // bit 31
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
    /// RCC AHB1 Peripheral Reset Register (AHB1RSTR)
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
            /// DMA1 block reset (DMA1RST)
            uint32_t dma1_reset          : 1;    // bit 0
            /// DMA2 block reset (DMA2RST)
            uint32_t dma2_reset          : 1;    // bit 1
            /// (reserved)
            uint32_t                     : 3;    // bits 2:4
            /// ADC1&2 block reset (ADC12RST)
            uint32_t adc12_reset         : 1;    // bit 5
            /// (reserved)
            uint32_t                     : 9;    // bits 6:14
            /// ETH1MAC block reset (ETH1MACRST)
            uint32_t ethernet1_mac_reset : 1;    // bit 15
            /// (reserved)
            uint32_t                     : 9;    // bits 16:24
            /// USB1OTG block reset (USB1OTGRST)
            uint32_t usb1_otg_reset      : 1;    // bit 25
            /// (reserved)
            uint32_t                     : 1;    // bit 26
            /// USB2OTG block reset (USB2OTGRST)
            uint32_t usb2_otg_reset      : 1;    // bit 27
            /// (reserved)
            uint32_t                     : 4;    // bits 28:31
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
    /// RCC AHB2 Peripheral Reset Register (AHB2RSTR)
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
            /// CAMITF block reset (CAMITFRST)
            uint32_t camera_interface_reset        : 1;    // bit 0
            /// (reserved)
            uint32_t                               : 3;    // bits 1:3
            /// Cryptography block reset (CRYPTRST)
            uint32_t crypto_reset                  : 1;    // bit 4
            /// Hash block reset (HASHRST)
            uint32_t hash_reset                    : 1;    // bit 5
            /// Random Number Generator block reset (RNGRST)
            uint32_t random_number_generator_reset : 1;    // bit 6
            /// (reserved)
            uint32_t                               : 2;    // bits 7:8
            /// SDMMC2 and SDMMC2 Delay block reset (SDMMC2RST)
            uint32_t sdmmc2_reset                  : 1;    // bit 9
            /// (reserved)
            uint32_t                               : 22;    // bits 10:31
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
    /// RCC AHB4 Peripheral Reset Register (AHB4RSTR)
    struct AHB4Reset final {
        /// Default Constructor
        AHB4Reset()
            : whole{0u} {}
        /// Copy Constructor from volatile
        AHB4Reset(AHB4Reset volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        AHB4Reset(AHB4Reset const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        AHB4Reset(AHB4Reset&&) = delete;
        /// Parameterized Constructor for constant references
        explicit AHB4Reset(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit AHB4Reset(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~AHB4Reset() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// GPIO block reset (GPIOARST)
            uint32_t gpioa_reset                        : 1;    // bit 0
            /// GPIO block reset (GPIOBRST)
            uint32_t gpiob_reset                        : 1;    // bit 1
            /// GPIO block reset (GPIOCRST)
            uint32_t gpioc_reset                        : 1;    // bit 2
            /// GPIO block reset (GPIODRST)
            uint32_t gpiod_reset                        : 1;    // bit 3
            /// GPIO block reset (GPIOERST)
            uint32_t gpioe_reset                        : 1;    // bit 4
            /// GPIO block reset (GPIOFRST)
            uint32_t gpiof_reset                        : 1;    // bit 5
            /// GPIO block reset (GPIOGRST)
            uint32_t gpiog_reset                        : 1;    // bit 6
            /// GPIO block reset (GPIOHRST)
            uint32_t gpioh_reset                        : 1;    // bit 7
            /// GPIO block reset (GPIOIRST)
            uint32_t gpioi_reset                        : 1;    // bit 8
            /// GPIO block reset (GPIOJRST)
            uint32_t gpioj_reset                        : 1;    // bit 9
            /// GPIO block reset (GPIOKRST)
            uint32_t gpiok_reset                        : 1;    // bit 10
            /// (reserved)
            uint32_t                                    : 8;    // bits 11:18
            /// CRC block reset (CRCRST)
            uint32_t crc_reset                          : 1;    // bit 19
            /// (reserved)
            uint32_t                                    : 1;    // bit 20
            /// BDMA block reset (BDMARST)
            uint32_t bdma_reset                         : 1;    // bit 21
            /// (reserved)
            uint32_t                                    : 2;    // bits 22:23
            /// ADC3 block reset (ADC3RST)
            uint32_t analog_to_digital_converter3_reset : 1;    // bit 24
            /// HSEM block reset (HSEMRST)
            uint32_t hsemrst                            : 1;    // bit 25
            /// (reserved)
            uint32_t                                    : 6;    // bits 26:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        AHB4Reset& operator=(AHB4Reset&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(AHB4Reset volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(AHB4Reset const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<AHB4Reset>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(AHB4Reset) == 4UL, "Must be this exact size");
    /// RCC APB3 Peripheral Reset Register (APB3RSTR)
    struct APB3Reset final {
        /// Default Constructor
        APB3Reset()
            : whole{0u} {}
        /// Copy Constructor from volatile
        APB3Reset(APB3Reset volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        APB3Reset(APB3Reset const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        APB3Reset(APB3Reset&&) = delete;
        /// Parameterized Constructor for constant references
        explicit APB3Reset(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit APB3Reset(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~APB3Reset() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t            : 3;    // bits 0:2
            /// LTDC block reset (LTDCRST)
            uint32_t ltdc_reset : 1;    // bit 3
            /// (reserved)
            uint32_t            : 28;    // bits 4:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        APB3Reset& operator=(APB3Reset&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(APB3Reset volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(APB3Reset const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<APB3Reset>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(APB3Reset) == 4UL, "Must be this exact size");
    /// RCC APB1 Peripheral Reset Register (APB1LRSTR)
    struct APB1LowReset final {
        /// Default Constructor
        APB1LowReset()
            : whole{0u} {}
        /// Copy Constructor from volatile
        APB1LowReset(APB1LowReset volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        APB1LowReset(APB1LowReset const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        APB1LowReset(APB1LowReset&&) = delete;
        /// Parameterized Constructor for constant references
        explicit APB1LowReset(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit APB1LowReset(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~APB1LowReset() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TIM block reset (TIM2RST)
            uint32_t timer2_reset   : 1;    // bit 0
            /// TIM block reset (TIM3RST)
            uint32_t timer3_reset   : 1;    // bit 1
            /// TIM block reset (TIM4RST)
            uint32_t timer4_reset   : 1;    // bit 2
            /// TIM block reset (TIM5RST)
            uint32_t timer5_reset   : 1;    // bit 3
            /// TIM block reset (TIM6RST)
            uint32_t timer6_reset   : 1;    // bit 4
            /// TIM block reset (TIM7RST)
            uint32_t timer7_reset   : 1;    // bit 5
            /// TIM block reset (TIM12RST)
            uint32_t timer12_reset  : 1;    // bit 6
            /// TIM block reset (TIM13RST)
            uint32_t timer13_reset  : 1;    // bit 7
            /// TIM block reset (TIM14RST)
            uint32_t timer14_reset  : 1;    // bit 8
            /// TIM block reset (LPTIM1RST)
            uint32_t lptimer1_reset : 1;    // bit 9
            /// (reserved)
            uint32_t                : 4;    // bits 10:13
            /// SPI2 block reset (SPI2RST)
            uint32_t spi2_reset     : 1;    // bit 14
            /// SPI3 block reset (SPI3RST)
            uint32_t spi3_reset     : 1;    // bit 15
            /// SPDIFRX block reset (SPDIFRXRST)
            uint32_t spdifrx_reset  : 1;    // bit 16
            /// USART2 block reset (USART2RST)
            uint32_t usart2_reset   : 1;    // bit 17
            /// USART3 block reset (USART3RST)
            uint32_t usart3_reset   : 1;    // bit 18
            /// UART4 block reset (UART4RST)
            uint32_t uart4_reset    : 1;    // bit 19
            /// UART5 block reset (UART5RST)
            uint32_t uart5_reset    : 1;    // bit 20
            /// I2C1 block reset (I2C1RST)
            uint32_t i2c1_reset     : 1;    // bit 21
            /// I2C2 block reset (I2C2RST)
            uint32_t i2c2_reset     : 1;    // bit 22
            /// I2C3 block reset (I2C3RST)
            uint32_t i2c3_reset     : 1;    // bit 23
            /// (reserved)
            uint32_t                : 3;    // bits 24:26
            /// HDMI-CEC block reset (CECRST)
            uint32_t cec_reset      : 1;    // bit 27
            /// (reserved)
            uint32_t                : 1;    // bit 28
            /// DAC1 and 2 Blocks Reset (DAC12RST)
            uint32_t dac12_reset    : 1;    // bit 29
            /// USART7 block reset (USART7RST)
            uint32_t usart7_reset   : 1;    // bit 30
            /// USART8 block reset (USART8RST)
            uint32_t usart8_reset   : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        APB1LowReset& operator=(APB1LowReset&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(APB1LowReset volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(APB1LowReset const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<APB1LowReset>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(APB1LowReset) == 4UL, "Must be this exact size");
    /// RCC APB1 Peripheral Reset Register (APB1HRSTR)
    struct APB1HighReset final {
        /// Default Constructor
        APB1HighReset()
            : whole{0u} {}
        /// Copy Constructor from volatile
        APB1HighReset(APB1HighReset volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        APB1HighReset(APB1HighReset const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        APB1HighReset(APB1HighReset&&) = delete;
        /// Parameterized Constructor for constant references
        explicit APB1HighReset(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit APB1HighReset(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~APB1HighReset() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                                             : 1;    // bit 0
            /// Clock Recovery System reset (CRSRST)
            uint32_t clock_recovery_system_reset                 : 1;    // bit 1
            /// SWPMI block reset (SWPRST)
            uint32_t single_wire_protocol_leader_interface_reset : 1;    // bit 2
            /// (reserved)
            uint32_t                                             : 1;    // bit 3
            /// OPAMP block reset (OPAMPRST)
            uint32_t operational_amplifier_reset                 : 1;    // bit 4
            /// MDIOS block reset (MDIOSRST)
            uint32_t mdios_reset                                 : 1;    // bit 5
            /// (reserved)
            uint32_t                                             : 2;    // bits 6:7
            /// FDCAN block reset (FDCANRST)
            uint32_t fdcan_reset                                 : 1;    // bit 8
            /// (reserved)
            uint32_t                                             : 23;    // bits 9:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        APB1HighReset& operator=(APB1HighReset&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(APB1HighReset volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(APB1HighReset const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<APB1HighReset>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(APB1HighReset) == 4UL, "Must be this exact size");
    /// RCC APB2 Peripheral Reset Register (APB2RSTR)
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
            /// TIM1 block reset (TIM1RST)
            uint32_t timer1_reset                : 1;    // bit 0
            /// TIM8 block reset (TIM8RST)
            uint32_t timer8_reset                : 1;    // bit 1
            /// (reserved)
            uint32_t                             : 2;    // bits 2:3
            /// USART1 block reset (USART1RST)
            uint32_t usart1_reset                : 1;    // bit 4
            /// USART6 block reset (USART6RST)
            uint32_t usart6_reset                : 1;    // bit 5
            /// (reserved)
            uint32_t                             : 6;    // bits 6:11
            /// SPI1 block reset (SPI1RST)
            uint32_t spi1_reset                  : 1;    // bit 12
            /// SPI4 block reset (SPI4RST)
            uint32_t spi4_reset                  : 1;    // bit 13
            /// (reserved)
            uint32_t                             : 2;    // bits 14:15
            /// TIM15 block reset (TIM15RST)
            uint32_t timer15_reset               : 1;    // bit 16
            /// TIM16 block reset (TIM16RST)
            uint32_t timer16_reset               : 1;    // bit 17
            /// TIM17 block reset (TIM17RST)
            uint32_t timer17_reset               : 1;    // bit 18
            /// (reserved)
            uint32_t                             : 1;    // bit 19
            /// SPI5 block reset (SPI5RST)
            uint32_t spi5_reset                  : 1;    // bit 20
            /// (reserved)
            uint32_t                             : 1;    // bit 21
            /// SAI1 block reset (SAI1RST)
            uint32_t sai1_reset                  : 1;    // bit 22
            /// SAI2 block reset (SAI2RST)
            uint32_t sai2_reset                  : 1;    // bit 23
            /// SAI3 block reset (SAI3RST)
            uint32_t sai3_reset                  : 1;    // bit 24
            /// (reserved)
            uint32_t                             : 3;    // bits 25:27
            /// DFSDM1 block reset (DFSDM1RST)
            uint32_t dfsdm1_reset                : 1;    // bit 28
            /// HRTIM block reset (HRTIMRST)
            uint32_t high_resolution_timer_reset : 1;    // bit 29
            /// (reserved)
            uint32_t                             : 2;    // bits 30:31
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
    /// RCC APB4 Peripheral Reset Register (APB4RSTR)
    struct APB4Reset final {
        /// Default Constructor
        APB4Reset()
            : whole{0u} {}
        /// Copy Constructor from volatile
        APB4Reset(APB4Reset volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        APB4Reset(APB4Reset const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        APB4Reset(APB4Reset&&) = delete;
        /// Parameterized Constructor for constant references
        explicit APB4Reset(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit APB4Reset(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~APB4Reset() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                : 1;    // bit 0
            /// SYSCFG block reset (SYSCFGRST)
            uint32_t syscfg_reset   : 1;    // bit 1
            /// (reserved)
            uint32_t                : 1;    // bit 2
            /// LPUART1 block reset (LPUART1RST)
            uint32_t lpuart1_reset  : 1;    // bit 3
            /// (reserved)
            uint32_t                : 1;    // bit 4
            /// SPI6 block reset (SPI6RST)
            uint32_t spi6_reset     : 1;    // bit 5
            /// (reserved)
            uint32_t                : 1;    // bit 6
            /// I2C4 block reset (I2C4RST)
            uint32_t i2c4_reset     : 1;    // bit 7
            /// (reserved)
            uint32_t                : 1;    // bit 8
            /// LPTIM2 block reset (LPTIM2RST)
            uint32_t lptimer2_reset : 1;    // bit 9
            /// LPTIM3 block reset (LPTIM3RST)
            uint32_t lptimer3_reset : 1;    // bit 10
            /// LPTIM4 block reset (LPTIM4RST)
            uint32_t lptimer4_reset : 1;    // bit 11
            /// LPTIM5 block reset (LPTIM5RST)
            uint32_t lptimer5_reset : 1;    // bit 12
            /// (reserved)
            uint32_t                : 1;    // bit 13
            /// COMP12 Blocks Reset (COMP12RST)
            uint32_t comp12_reset   : 1;    // bit 14
            /// VREF block reset (VREFRST)
            uint32_t vref_reset     : 1;    // bit 15
            /// (reserved)
            uint32_t                : 5;    // bits 16:20
            /// SAI4 block reset (SAI4RST)
            uint32_t sai4_reset     : 1;    // bit 21
            /// (reserved)
            uint32_t                : 10;    // bits 22:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        APB4Reset& operator=(APB4Reset&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(APB4Reset volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(APB4Reset const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<APB4Reset>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(APB4Reset) == 4UL, "Must be this exact size");
    /// RCC Global Control Register (GCR)
    struct GlobalControl final {
        /// Default Constructor
        GlobalControl()
            : whole{0u} {}
        /// Copy Constructor from volatile
        GlobalControl(GlobalControl volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        GlobalControl(GlobalControl const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        GlobalControl(GlobalControl&&) = delete;
        /// Parameterized Constructor for constant references
        explicit GlobalControl(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit GlobalControl(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~GlobalControl() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// WWDG1 reset scope control (WW1RSC)
            uint32_t window_watchdog1_reset_scope_control : 1;    // bit 0
            /// (reserved)
            uint32_t                                      : 31;    // bits 1:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        GlobalControl& operator=(GlobalControl&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(GlobalControl volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(GlobalControl const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<GlobalControl>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(GlobalControl) == 4UL, "Must be this exact size");
    /// RCC D3 Autonomous mode Register (D3AMR)
    struct Domain3AutonomousMode final {
        /// Default Constructor
        Domain3AutonomousMode()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Domain3AutonomousMode(Domain3AutonomousMode volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Domain3AutonomousMode(Domain3AutonomousMode const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Domain3AutonomousMode(Domain3AutonomousMode&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Domain3AutonomousMode(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Domain3AutonomousMode(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Domain3AutonomousMode() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// BDMA and DMAMUX Autonomous mode enable (BDMAAMEN)
            uint32_t bdma_autonomous_mode       : 1;    // bit 0
            /// (reserved)
            uint32_t                            : 2;    // bits 1:2
            /// LPUART1 Autonomous mode enable (LPUART1AMEN)
            uint32_t lpuart1_autonomous_mode    : 1;    // bit 3
            /// (reserved)
            uint32_t                            : 1;    // bit 4
            /// SPI6 Autonomous mode enable (SPI6AMEN)
            uint32_t spi6_autonomous_mode       : 1;    // bit 5
            /// (reserved)
            uint32_t                            : 1;    // bit 6
            /// I2C4 Autonomous mode enable (I2C4AMEN)
            uint32_t i2c4_autonomous_mode       : 1;    // bit 7
            /// (reserved)
            uint32_t                            : 1;    // bit 8
            /// LPTIM2 Autonomous mode enable (LPTIM2AMEN)
            uint32_t lptimer2_autonomous_mode   : 1;    // bit 9
            /// LPTIM3 Autonomous mode enable (LPTIM3AMEN)
            uint32_t lptimer3_autonomous_mode   : 1;    // bit 10
            /// LPTIM4 Autonomous mode enable (LPTIM4AMEN)
            uint32_t lptimer4_autonomous_mode   : 1;    // bit 11
            /// LPTIM5 Autonomous mode enable (LPTIM5AMEN)
            uint32_t lptimer5_autonomous_mode   : 1;    // bit 12
            /// (reserved)
            uint32_t                            : 1;    // bit 13
            /// COMP12 Autonomous mode enable (COMP12AMEN)
            uint32_t comp12_autonomous_mode     : 1;    // bit 14
            /// VREF Autonomous mode enable (VREFAMEN)
            uint32_t vref_autonomous_mode       : 1;    // bit 15
            /// RTC Autonomous mode enable (RTCAMEN)
            uint32_t rtc_autonomous_mode        : 1;    // bit 16
            /// (reserved)
            uint32_t                            : 2;    // bits 17:18
            /// CRC Autonomous mode enable (CRCAMEN)
            uint32_t crc_autonomous_mode        : 1;    // bit 19
            /// (reserved)
            uint32_t                            : 1;    // bit 20
            /// SAI4 Autonomous mode enable (SAI4AMEN)
            uint32_t sai4_autonomous_mode       : 1;    // bit 21
            /// (reserved)
            uint32_t                            : 2;    // bits 22:23
            /// ADC3 Autonomous mode enable (ADC3AMEN)
            uint32_t adc3_autonomous_mode       : 1;    // bit 24
            /// (reserved)
            uint32_t                            : 3;    // bits 25:27
            /// Backup RAM Autonomous mode enable (BKPRAMAMEN)
            uint32_t backup_ram_autonomous_mode : 1;    // bit 28
            /// SRAM4 Autonomous mode enable (SRAM4AMEN)
            uint32_t sram4_autonomous_mode      : 1;    // bit 29
            /// (reserved)
            uint32_t                            : 2;    // bits 30:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Domain3AutonomousMode& operator=(Domain3AutonomousMode&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Domain3AutonomousMode volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Domain3AutonomousMode const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Domain3AutonomousMode>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Domain3AutonomousMode) == 4UL, "Must be this exact size");
    /// RCC Reset Status Register (RSR)
    struct ResetStatus final {
        /// Default Constructor
        ResetStatus()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ResetStatus(ResetStatus volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ResetStatus(ResetStatus const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ResetStatus(ResetStatus&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ResetStatus(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ResetStatus(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ResetStatus() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                      : 16;    // bits 0:15
            /// Remove reset flag (RMVF)
            uint32_t reset_flags_clear    : 1;    // bit 16
            /// CPU reset flag (CPURSTF)
            uint32_t cpu_reset_flag       : 1;    // bit 17
            /// (reserved)
            uint32_t                      : 1;    // bit 18
            /// D1 domain power switch reset flag (D1RSTF)
            uint32_t domain1_reset_flag   : 1;    // bit 19
            /// D2 domain power switch reset flag (D2RSTF)
            uint32_t domain2_reset_flag   : 1;    // bit 20
            /// BOR reset flag (BORRSTF)
            uint32_t brown_out_reset_flag : 1;    // bit 21
            /// Pin reset flag (NRST) (PINRSTF)
            uint32_t pin_reset_flag       : 1;    // bit 22
            /// POR/PDR reset flag (PORRSTF)
            uint32_t power_on_reset_flag  : 1;    // bit 23
            /// System reset from CPU reset flag (SFTRSTF)
            uint32_t software_reset_flag  : 1;    // bit 24
            /// (reserved)
            uint32_t                      : 1;    // bit 25
            /// Independent Watchdog reset flag (IWDG1RSTF)
            uint32_t iwdg1_reset_flag     : 1;    // bit 26
            /// (reserved)
            uint32_t                      : 1;    // bit 27
            /// Window Watchdog reset flag (WWDG1RSTF)
            uint32_t wwdg1_reset_flag     : 1;    // bit 28
            /// (reserved)
            uint32_t                      : 1;    // bit 29
            /// Reset due to illegal D1 DStandby or CPU CStop flag (LPWRRSTF)
            uint32_t low_power_reset_flag : 1;    // bit 30
            /// (reserved)
            uint32_t                      : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ResetStatus& operator=(ResetStatus&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ResetStatus volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ResetStatus const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ResetStatus>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ResetStatus) == 4UL, "Must be this exact size");
    /// RCC Reset Status Register (C1_RSR)
    struct Processor1ResetStatus final {
        /// Default Constructor
        Processor1ResetStatus()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Processor1ResetStatus(Processor1ResetStatus volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Processor1ResetStatus(Processor1ResetStatus const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Processor1ResetStatus(Processor1ResetStatus&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Processor1ResetStatus(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Processor1ResetStatus(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Processor1ResetStatus() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                      : 16;    // bits 0:15
            /// Remove reset flag (RMVF)
            uint32_t reset_flags_clear    : 1;    // bit 16
            /// CPU reset flag (CPURSTF)
            uint32_t cpu_reset_flag       : 1;    // bit 17
            /// (reserved)
            uint32_t                      : 1;    // bit 18
            /// D1 domain power switch reset flag (D1RSTF)
            uint32_t domain1_reset_flag   : 1;    // bit 19
            /// D2 domain power switch reset flag (D2RSTF)
            uint32_t domain2_reset_flag   : 1;    // bit 20
            /// BOR reset flag (BORRSTF)
            uint32_t brown_out_reset_flag : 1;    // bit 21
            /// Pin reset flag (NRST) (PINRSTF)
            uint32_t pin_reset_flag       : 1;    // bit 22
            /// POR/PDR reset flag (PORRSTF)
            uint32_t power_on_reset_flag  : 1;    // bit 23
            /// System reset from CPU reset flag (SFTRSTF)
            uint32_t software_reset_flag  : 1;    // bit 24
            /// (reserved)
            uint32_t                      : 1;    // bit 25
            /// Independent Watchdog reset flag (IWDG1RSTF)
            uint32_t iwdg1_reset_flag     : 1;    // bit 26
            /// (reserved)
            uint32_t                      : 1;    // bit 27
            /// Window Watchdog reset flag (WWDG1RSTF)
            uint32_t wwdg1_reset_flag     : 1;    // bit 28
            /// (reserved)
            uint32_t                      : 1;    // bit 29
            /// Reset due to illegal D1 DStandby or CPU CStop flag (LPWRRSTF)
            uint32_t low_power_reset_flag : 1;    // bit 30
            /// (reserved)
            uint32_t                      : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Processor1ResetStatus& operator=(Processor1ResetStatus&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Processor1ResetStatus volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Processor1ResetStatus const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Processor1ResetStatus>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Processor1ResetStatus) == 4UL, "Must be this exact size");
    /// RCC AHB3 Clock Register (C1_AHB3ENR)
    struct Processor1AHB3ClockEnable final {
        /// Default Constructor
        Processor1AHB3ClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Processor1AHB3ClockEnable(Processor1AHB3ClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Processor1AHB3ClockEnable(Processor1AHB3ClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Processor1AHB3ClockEnable(Processor1AHB3ClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Processor1AHB3ClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Processor1AHB3ClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Processor1AHB3ClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// MDMA Peripheral Clock Enable (MDMAEN)
            uint32_t mdma_enable   : 1;    // bit 0
            /// (reserved)
            uint32_t               : 3;    // bits 1:3
            /// DMA2D Peripheral Clock Enable (DMA2DEN)
            uint32_t dma2d_enable  : 1;    // bit 4
            /// JPGDEC Peripheral Clock Enable (JPGDECEN)
            uint32_t jpgdec_enable : 1;    // bit 5
            /// (reserved)
            uint32_t               : 6;    // bits 6:11
            /// FMC Peripheral Clocks Enable (FMCEN)
            uint32_t fmc_enable    : 1;    // bit 12
            /// (reserved)
            uint32_t               : 1;    // bit 13
            /// QUADSPI and QUADSPI Delay Clock Enable (QSPIEN)
            uint32_t qspi_enable   : 1;    // bit 14
            /// (reserved)
            uint32_t               : 1;    // bit 15
            /// SDMMC1 and SDMMC1 Delay Clock Enable (SDMMC1EN)
            uint32_t sdmmc1_enable : 1;    // bit 16
            /// (reserved)
            uint32_t               : 15;    // bits 17:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Processor1AHB3ClockEnable& operator=(Processor1AHB3ClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Processor1AHB3ClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Processor1AHB3ClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Processor1AHB3ClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Processor1AHB3ClockEnable) == 4UL, "Must be this exact size");
    /// RCC AHB3 Clock Register (AHB3ENR)
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
            /// MDMA Peripheral Clock Enable (MDMAEN)
            uint32_t mdma_enable   : 1;    // bit 0
            /// (reserved)
            uint32_t               : 3;    // bits 1:3
            /// DMA2D Peripheral Clock Enable (DMA2DEN)
            uint32_t dma2d_enable  : 1;    // bit 4
            /// JPGDEC Peripheral Clock Enable (JPGDECEN)
            uint32_t jpgdec_enable : 1;    // bit 5
            /// (reserved)
            uint32_t               : 6;    // bits 6:11
            /// FMC Peripheral Clocks Enable (FMCEN)
            uint32_t fmc_enable    : 1;    // bit 12
            /// (reserved)
            uint32_t               : 1;    // bit 13
            /// QUADSPI and QUADSPI Delay Clock Enable (QSPIEN)
            uint32_t qspi_enable   : 1;    // bit 14
            /// (reserved)
            uint32_t               : 1;    // bit 15
            /// SDMMC1 and SDMMC1 Delay Clock Enable (SDMMC1EN)
            uint32_t sdmmc1_enable : 1;    // bit 16
            /// (reserved)
            uint32_t               : 15;    // bits 17:31
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
    /// RCC AHB1 Clock Register (AHB1ENR)
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
            /// DMA1 Clock Enable (DMA1EN)
            uint32_t dma1_enable                           : 1;    // bit 0
            /// DMA2 Clock Enable (DMA2EN)
            uint32_t dma2_enable                           : 1;    // bit 1
            /// (reserved)
            uint32_t                                       : 3;    // bits 2:4
            /// ADC1/2 Peripheral Clocks Enable (ADC12EN)
            uint32_t adc12_enable                          : 1;    // bit 5
            /// (reserved)
            uint32_t                                       : 9;    // bits 6:14
            /// Ethernet MAC bus interface Clock Enable (ETH1MACEN)
            uint32_t ethernet1_mac_enable                  : 1;    // bit 15
            /// Ethernet Transmission Clock Enable (ETH1TXEN)
            uint32_t ethernet1_transmit_clock_enable       : 1;    // bit 16
            /// Ethernet Reception Clock Enable (ETH1RXEN)
            uint32_t ethernet1_receive_clock_enable        : 1;    // bit 17
            /// (reserved)
            uint32_t                                       : 7;    // bits 18:24
            /// USB1OTG (OTG_HS1) Peripheral Clocks Enable (USB1OTGHSEN)
            uint32_t usb1_otg_high_speed_enable            : 1;    // bit 25
            /// USB_PHY1 Clocks Enable (USB1OTGHSULPIEN)
            uint32_t usb1_otg_high_speed_phy1_clock_enable : 1;    // bit 26
            /// USB2OTG Peripheral Clocks Enable (USB2OTGHSEN)
            uint32_t usb2_otg_high_speed_enable            : 1;    // bit 27
            /// USB_PHY2 Clocks Enable (USB2OTGHSULPIEN)
            uint32_t usb2_otg_high_speed_ulpi_clock_enable : 1;    // bit 28
            /// (reserved)
            uint32_t                                       : 3;    // bits 29:31
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
    /// RCC AHB1 Clock Register (C1_AHB1ENR)
    struct Processor1AHB1ClockEnable final {
        /// Default Constructor
        Processor1AHB1ClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Processor1AHB1ClockEnable(Processor1AHB1ClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Processor1AHB1ClockEnable(Processor1AHB1ClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Processor1AHB1ClockEnable(Processor1AHB1ClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Processor1AHB1ClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Processor1AHB1ClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Processor1AHB1ClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// DMA1 Clock Enable (DMA1EN)
            uint32_t dma1_enable                           : 1;    // bit 0
            /// DMA2 Clock Enable (DMA2EN)
            uint32_t dma2_enable                           : 1;    // bit 1
            /// (reserved)
            uint32_t                                       : 3;    // bits 2:4
            /// ADC1/2 Peripheral Clocks Enable (ADC12EN)
            uint32_t adc12_enable                          : 1;    // bit 5
            /// (reserved)
            uint32_t                                       : 9;    // bits 6:14
            /// Ethernet MAC bus interface Clock Enable (ETH1MACEN)
            uint32_t ethernet1_mac_enable                  : 1;    // bit 15
            /// Ethernet Transmission Clock Enable (ETH1TXEN)
            uint32_t ethernet1_transmit_clock_enable       : 1;    // bit 16
            /// Ethernet Reception Clock Enable (ETH1RXEN)
            uint32_t ethernet1_receive_clock_enable        : 1;    // bit 17
            /// (reserved)
            uint32_t                                       : 7;    // bits 18:24
            /// USB1OTG (OTG_HS1) Peripheral Clocks Enable (USB1OTGHSEN)
            uint32_t usb1_otg_high_speed_enable            : 1;    // bit 25
            /// USB_PHY1 Clocks Enable (USB1OTGHSULPIEN)
            uint32_t usb1_otg_high_speed_phy1_clock_enable : 1;    // bit 26
            /// USB2OTG Peripheral Clocks Enable (USB2OTGHSEN)
            uint32_t usb2_otg_high_speed_enable            : 1;    // bit 27
            /// USB_PHY2 Clocks Enable (USB2OTGHSULPIEN)
            uint32_t usb2_otg_high_speed_ulpi_clock_enable : 1;    // bit 28
            /// (reserved)
            uint32_t                                       : 3;    // bits 29:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Processor1AHB1ClockEnable& operator=(Processor1AHB1ClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Processor1AHB1ClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Processor1AHB1ClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Processor1AHB1ClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Processor1AHB1ClockEnable) == 4UL, "Must be this exact size");
    /// RCC AHB2 Clock Register (C1_AHB2ENR)
    struct Processor1AHB2ClockEnable final {
        /// Default Constructor
        Processor1AHB2ClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Processor1AHB2ClockEnable(Processor1AHB2ClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Processor1AHB2ClockEnable(Processor1AHB2ClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Processor1AHB2ClockEnable(Processor1AHB2ClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Processor1AHB2ClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Processor1AHB2ClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Processor1AHB2ClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// DCMI peripheral clock enable (DCMIEN)
            uint32_t dcmi_enable                    : 1;    // bit 0
            /// (reserved)
            uint32_t                                : 3;    // bits 1:3
            /// CRYPT peripheral clock enable (CRYPTEN)
            uint32_t crypto_enable                  : 1;    // bit 4
            /// HASH peripheral clock enable (HASHEN)
            uint32_t hash_enable                    : 1;    // bit 5
            /// RNG peripheral clocks enable (RNGEN)
            uint32_t random_number_generator_enable : 1;    // bit 6
            /// (reserved)
            uint32_t                                : 2;    // bits 7:8
            /// SDMMC2 and SDMMC2 delay clock enable (SDMMC2EN)
            uint32_t sdmmc2_enable                  : 1;    // bit 9
            /// (reserved)
            uint32_t                                : 19;    // bits 10:28
            /// SRAM1 block enable (SRAM1EN)
            uint32_t sram1_enable                   : 1;    // bit 29
            /// SRAM2 block enable (SRAM2EN)
            uint32_t sram2_enable                   : 1;    // bit 30
            /// SRAM3 block enable (SRAM3EN)
            uint32_t sram3_enable                   : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Processor1AHB2ClockEnable& operator=(Processor1AHB2ClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Processor1AHB2ClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Processor1AHB2ClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Processor1AHB2ClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Processor1AHB2ClockEnable) == 4UL, "Must be this exact size");
    /// RCC AHB2 Clock Register (AHB2ENR)
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
            /// DCMI peripheral clock enable (DCMIEN)
            uint32_t dcmi_enable                    : 1;    // bit 0
            /// (reserved)
            uint32_t                                : 3;    // bits 1:3
            /// CRYPT peripheral clock enable (CRYPTEN)
            uint32_t crypto_enable                  : 1;    // bit 4
            /// HASH peripheral clock enable (HASHEN)
            uint32_t hash_enable                    : 1;    // bit 5
            /// RNG peripheral clocks enable (RNGEN)
            uint32_t random_number_generator_enable : 1;    // bit 6
            /// (reserved)
            uint32_t                                : 2;    // bits 7:8
            /// SDMMC2 and SDMMC2 delay clock enable (SDMMC2EN)
            uint32_t sdmmc2_enable                  : 1;    // bit 9
            /// (reserved)
            uint32_t                                : 19;    // bits 10:28
            /// SRAM1 block enable (SRAM1EN)
            uint32_t sram1_enable                   : 1;    // bit 29
            /// SRAM2 block enable (SRAM2EN)
            uint32_t sram2_enable                   : 1;    // bit 30
            /// SRAM3 block enable (SRAM3EN)
            uint32_t sram3_enable                   : 1;    // bit 31
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
    /// RCC AHB4 Clock Register (AHB4ENR)
    struct AHB4ClockEnable final {
        /// Default Constructor
        AHB4ClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        AHB4ClockEnable(AHB4ClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        AHB4ClockEnable(AHB4ClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        AHB4ClockEnable(AHB4ClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit AHB4ClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit AHB4ClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~AHB4ClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// 0GPIO peripheral clock enable (GPIOAEN)
            uint32_t gpioa_enable                   : 1;    // bit 0
            /// 0GPIO peripheral clock enable (GPIOBEN)
            uint32_t gpiob_enable                   : 1;    // bit 1
            /// 0GPIO peripheral clock enable (GPIOCEN)
            uint32_t gpioc_enable                   : 1;    // bit 2
            /// 0GPIO peripheral clock enable (GPIODEN)
            uint32_t gpiod_enable                   : 1;    // bit 3
            /// 0GPIO peripheral clock enable (GPIOEEN)
            uint32_t gpioe_enable                   : 1;    // bit 4
            /// 0GPIO peripheral clock enable (GPIOFEN)
            uint32_t gpiof_enable                   : 1;    // bit 5
            /// 0GPIO peripheral clock enable (GPIOGEN)
            uint32_t gpiog_enable                   : 1;    // bit 6
            /// 0GPIO peripheral clock enable (GPIOHEN)
            uint32_t gpioh_enable                   : 1;    // bit 7
            /// 0GPIO peripheral clock enable (GPIOIEN)
            uint32_t gpioi_enable                   : 1;    // bit 8
            /// 0GPIO peripheral clock enable (GPIOJEN)
            uint32_t gpioj_enable                   : 1;    // bit 9
            /// 0GPIO peripheral clock enable (GPIOKEN)
            uint32_t gpiok_enable                   : 1;    // bit 10
            /// (reserved)
            uint32_t                                : 8;    // bits 11:18
            /// CRC peripheral clock enable (CRCEN)
            uint32_t cyclic_redundancy_check_enable : 1;    // bit 19
            /// (reserved)
            uint32_t                                : 1;    // bit 20
            /// BDMA and DMAMUX2 Clock Enable (BDMAEN)
            uint32_t bdma_enable                    : 1;    // bit 21
            /// (reserved)
            uint32_t                                : 2;    // bits 22:23
            /// ADC3 Peripheral Clocks Enable (ADC3EN)
            uint32_t adc3_enable                    : 1;    // bit 24
            /// HSEM peripheral clock enable (HSEMEN)
            uint32_t hardware_semaphore_enable      : 1;    // bit 25
            /// (reserved)
            uint32_t                                : 2;    // bits 26:27
            /// Backup RAM Clock Enable (BKPRAMEN)
            uint32_t backup_ram_enable              : 1;    // bit 28
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
        AHB4ClockEnable& operator=(AHB4ClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(AHB4ClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(AHB4ClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<AHB4ClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(AHB4ClockEnable) == 4UL, "Must be this exact size");
    /// RCC AHB4 Clock Register (C1_AHB4ENR)
    struct Processor1AHB4ClockEnable final {
        /// Default Constructor
        Processor1AHB4ClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Processor1AHB4ClockEnable(Processor1AHB4ClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Processor1AHB4ClockEnable(Processor1AHB4ClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Processor1AHB4ClockEnable(Processor1AHB4ClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Processor1AHB4ClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Processor1AHB4ClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Processor1AHB4ClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// 0GPIO peripheral clock enable (GPIOAEN)
            uint32_t gpioa_enable                   : 1;    // bit 0
            /// 0GPIO peripheral clock enable (GPIOBEN)
            uint32_t gpiob_enable                   : 1;    // bit 1
            /// 0GPIO peripheral clock enable (GPIOCEN)
            uint32_t gpioc_enable                   : 1;    // bit 2
            /// 0GPIO peripheral clock enable (GPIODEN)
            uint32_t gpiod_enable                   : 1;    // bit 3
            /// 0GPIO peripheral clock enable (GPIOEEN)
            uint32_t gpioe_enable                   : 1;    // bit 4
            /// 0GPIO peripheral clock enable (GPIOFEN)
            uint32_t gpiof_enable                   : 1;    // bit 5
            /// 0GPIO peripheral clock enable (GPIOGEN)
            uint32_t gpiog_enable                   : 1;    // bit 6
            /// 0GPIO peripheral clock enable (GPIOHEN)
            uint32_t gpioh_enable                   : 1;    // bit 7
            /// 0GPIO peripheral clock enable (GPIOIEN)
            uint32_t gpioi_enable                   : 1;    // bit 8
            /// 0GPIO peripheral clock enable (GPIOJEN)
            uint32_t gpioj_enable                   : 1;    // bit 9
            /// 0GPIO peripheral clock enable (GPIOKEN)
            uint32_t gpiok_enable                   : 1;    // bit 10
            /// (reserved)
            uint32_t                                : 8;    // bits 11:18
            /// CRC peripheral clock enable (CRCEN)
            uint32_t cyclic_redundancy_check_enable : 1;    // bit 19
            /// (reserved)
            uint32_t                                : 1;    // bit 20
            /// BDMA and DMAMUX2 Clock Enable (BDMAEN)
            uint32_t bdma_enable                    : 1;    // bit 21
            /// (reserved)
            uint32_t                                : 2;    // bits 22:23
            /// ADC3 Peripheral Clocks Enable (ADC3EN)
            uint32_t adc3_enable                    : 1;    // bit 24
            /// HSEM peripheral clock enable (HSEMEN)
            uint32_t hardware_semaphore_enable      : 1;    // bit 25
            /// (reserved)
            uint32_t                                : 2;    // bits 26:27
            /// Backup RAM Clock Enable (BKPRAMEN)
            uint32_t backup_ram_enable              : 1;    // bit 28
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
        Processor1AHB4ClockEnable& operator=(Processor1AHB4ClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Processor1AHB4ClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Processor1AHB4ClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Processor1AHB4ClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Processor1AHB4ClockEnable) == 4UL, "Must be this exact size");
    /// RCC APB3 Clock Register (C1_APB3ENR)
    struct Processor1APB3ClockEnable final {
        /// Default Constructor
        Processor1APB3ClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Processor1APB3ClockEnable(Processor1APB3ClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Processor1APB3ClockEnable(Processor1APB3ClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Processor1APB3ClockEnable(Processor1APB3ClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Processor1APB3ClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Processor1APB3ClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Processor1APB3ClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t              : 3;    // bits 0:2
            /// LTDC peripheral clock enable (LTDCEN)
            uint32_t ltdc_enable  : 1;    // bit 3
            /// (reserved)
            uint32_t              : 2;    // bits 4:5
            /// WWDG1 Clock Enable (WWDG1EN)
            uint32_t wwdg1_enable : 1;    // bit 6
            /// (reserved)
            uint32_t              : 25;    // bits 7:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Processor1APB3ClockEnable& operator=(Processor1APB3ClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Processor1APB3ClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Processor1APB3ClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Processor1APB3ClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Processor1APB3ClockEnable) == 4UL, "Must be this exact size");
    /// RCC APB3 Clock Register (APB3ENR)
    struct APB3ClockEnable final {
        /// Default Constructor
        APB3ClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        APB3ClockEnable(APB3ClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        APB3ClockEnable(APB3ClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        APB3ClockEnable(APB3ClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit APB3ClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit APB3ClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~APB3ClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t              : 3;    // bits 0:2
            /// LTDC peripheral clock enable (LTDCEN)
            uint32_t ltdc_enable  : 1;    // bit 3
            /// (reserved)
            uint32_t              : 2;    // bits 4:5
            /// WWDG1 Clock Enable (WWDG1EN)
            uint32_t wwdg1_enable : 1;    // bit 6
            /// (reserved)
            uint32_t              : 25;    // bits 7:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        APB3ClockEnable& operator=(APB3ClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(APB3ClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(APB3ClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<APB3ClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(APB3ClockEnable) == 4UL, "Must be this exact size");
    /// RCC APB1 Clock Register (APB1LENR)
    struct APB1LowClockEnable final {
        /// Default Constructor
        APB1LowClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        APB1LowClockEnable(APB1LowClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        APB1LowClockEnable(APB1LowClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        APB1LowClockEnable(APB1LowClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit APB1LowClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit APB1LowClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~APB1LowClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TIM peripheral clock enable (TIM2EN)
            uint32_t timer2_enable   : 1;    // bit 0
            /// TIM peripheral clock enable (TIM3EN)
            uint32_t timer3_enable   : 1;    // bit 1
            /// TIM peripheral clock enable (TIM4EN)
            uint32_t timer4_enable   : 1;    // bit 2
            /// TIM peripheral clock enable (TIM5EN)
            uint32_t timer5_enable   : 1;    // bit 3
            /// TIM peripheral clock enable (TIM6EN)
            uint32_t timer6_enable   : 1;    // bit 4
            /// TIM peripheral clock enable (TIM7EN)
            uint32_t timer7_enable   : 1;    // bit 5
            /// TIM peripheral clock enable (TIM12EN)
            uint32_t timer12_enable  : 1;    // bit 6
            /// TIM peripheral clock enable (TIM13EN)
            uint32_t timer13_enable  : 1;    // bit 7
            /// TIM peripheral clock enable (TIM14EN)
            uint32_t timer14_enable  : 1;    // bit 8
            /// LPTIM1 Peripheral Clocks Enable (LPTIM1EN)
            uint32_t lptimer1_enable : 1;    // bit 9
            /// (reserved)
            uint32_t                 : 4;    // bits 10:13
            /// SPI2 Peripheral Clocks Enable (SPI2EN)
            uint32_t spi2_enable     : 1;    // bit 14
            /// SPI3 Peripheral Clocks Enable (SPI3EN)
            uint32_t spi3_enable     : 1;    // bit 15
            /// SPDIFRX Peripheral Clocks Enable (SPDIFRXEN)
            uint32_t spdifrx_enable  : 1;    // bit 16
            /// USART2 Peripheral Clocks Enable (USART2EN)
            uint32_t usart2_enable   : 1;    // bit 17
            /// USART3 Peripheral Clocks Enable (USART3EN)
            uint32_t usart3_enable   : 1;    // bit 18
            /// UART4 Peripheral Clocks Enable (UART4EN)
            uint32_t uart4_enable    : 1;    // bit 19
            /// UART5 Peripheral Clocks Enable (UART5EN)
            uint32_t uart5_enable    : 1;    // bit 20
            /// I2C1 Peripheral Clocks Enable (I2C1EN)
            uint32_t i2c1_enable     : 1;    // bit 21
            /// I2C2 Peripheral Clocks Enable (I2C2EN)
            uint32_t i2c2_enable     : 1;    // bit 22
            /// I2C3 Peripheral Clocks Enable (I2C3EN)
            uint32_t i2c3_enable     : 1;    // bit 23
            /// (reserved)
            uint32_t                 : 3;    // bits 24:26
            /// HDMI-CEC peripheral clock enable (CECEN)
            uint32_t cec_enable      : 1;    // bit 27
            /// (reserved)
            uint32_t                 : 1;    // bit 28
            /// DAC1&2 peripheral clock enable (DAC12EN)
            uint32_t dac12_enable    : 1;    // bit 29
            /// USART7 Peripheral Clocks Enable (USART7EN)
            uint32_t usart7_enable   : 1;    // bit 30
            /// USART8 Peripheral Clocks Enable (USART8EN)
            uint32_t usart8_enable   : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        APB1LowClockEnable& operator=(APB1LowClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(APB1LowClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(APB1LowClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<APB1LowClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(APB1LowClockEnable) == 4UL, "Must be this exact size");
    /// RCC APB1 Clock Register (C1_APB1LENR)
    struct Processor1APB1LowClockEnable final {
        /// Default Constructor
        Processor1APB1LowClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Processor1APB1LowClockEnable(Processor1APB1LowClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Processor1APB1LowClockEnable(Processor1APB1LowClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Processor1APB1LowClockEnable(Processor1APB1LowClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Processor1APB1LowClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Processor1APB1LowClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Processor1APB1LowClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TIM peripheral clock enable (TIM2EN)
            uint32_t timer2_enable   : 1;    // bit 0
            /// TIM peripheral clock enable (TIM3EN)
            uint32_t timer3_enable   : 1;    // bit 1
            /// TIM peripheral clock enable (TIM4EN)
            uint32_t timer4_enable   : 1;    // bit 2
            /// TIM peripheral clock enable (TIM5EN)
            uint32_t timer5_enable   : 1;    // bit 3
            /// TIM peripheral clock enable (TIM6EN)
            uint32_t timer6_enable   : 1;    // bit 4
            /// TIM peripheral clock enable (TIM7EN)
            uint32_t timer7_enable   : 1;    // bit 5
            /// TIM peripheral clock enable (TIM12EN)
            uint32_t timer12_enable  : 1;    // bit 6
            /// TIM peripheral clock enable (TIM13EN)
            uint32_t timer13_enable  : 1;    // bit 7
            /// TIM peripheral clock enable (TIM14EN)
            uint32_t timer14_enable  : 1;    // bit 8
            /// LPTIM1 Peripheral Clocks Enable (LPTIM1EN)
            uint32_t lptimer1_enable : 1;    // bit 9
            /// (reserved)
            uint32_t                 : 4;    // bits 10:13
            /// SPI2 Peripheral Clocks Enable (SPI2EN)
            uint32_t spi2_enable     : 1;    // bit 14
            /// SPI3 Peripheral Clocks Enable (SPI3EN)
            uint32_t spi3_enable     : 1;    // bit 15
            /// SPDIFRX Peripheral Clocks Enable (SPDIFRXEN)
            uint32_t spdifrx_enable  : 1;    // bit 16
            /// USART2 Peripheral Clocks Enable (USART2EN)
            uint32_t usart2_enable   : 1;    // bit 17
            /// USART3 Peripheral Clocks Enable (USART3EN)
            uint32_t usart3_enable   : 1;    // bit 18
            /// UART4 Peripheral Clocks Enable (UART4EN)
            uint32_t uart4_enable    : 1;    // bit 19
            /// UART5 Peripheral Clocks Enable (UART5EN)
            uint32_t uart5_enable    : 1;    // bit 20
            /// I2C1 Peripheral Clocks Enable (I2C1EN)
            uint32_t i2c1_enable     : 1;    // bit 21
            /// I2C2 Peripheral Clocks Enable (I2C2EN)
            uint32_t i2c2_enable     : 1;    // bit 22
            /// I2C3 Peripheral Clocks Enable (I2C3EN)
            uint32_t i2c3_enable     : 1;    // bit 23
            /// (reserved)
            uint32_t                 : 3;    // bits 24:26
            /// HDMI-CEC peripheral clock enable (HDMICECEN)
            uint32_t hdmicec_enable  : 1;    // bit 27
            /// (reserved)
            uint32_t                 : 1;    // bit 28
            /// DAC1&2 peripheral clock enable (DAC12EN)
            uint32_t dac12_enable    : 1;    // bit 29
            /// USART7 Peripheral Clocks Enable (USART7EN)
            uint32_t usart7_enable   : 1;    // bit 30
            /// USART8 Peripheral Clocks Enable (USART8EN)
            uint32_t usart8_enable   : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Processor1APB1LowClockEnable& operator=(Processor1APB1LowClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Processor1APB1LowClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Processor1APB1LowClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Processor1APB1LowClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Processor1APB1LowClockEnable) == 4UL, "Must be this exact size");
    /// RCC APB1 Clock Register (APB1HENR)
    struct APB1HighClockEnable final {
        /// Default Constructor
        APB1HighClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        APB1HighClockEnable(APB1HighClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        APB1HighClockEnable(APB1HighClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        APB1HighClockEnable(APB1HighClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit APB1HighClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit APB1HighClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~APB1HighClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                                    : 1;    // bit 0
            /// Clock Recovery System peripheral clock enable (CRSEN)
            uint32_t clock_recovery_system_enable       : 1;    // bit 1
            /// SWPMI Peripheral Clocks Enable (SWPEN)
            uint32_t single_wire_protocol_leader_enable : 1;    // bit 2
            /// (reserved)
            uint32_t                                    : 1;    // bit 3
            /// OPAMP peripheral clock enable (OPAMPEN)
            uint32_t operational_amplifier_enable       : 1;    // bit 4
            /// MDIOS peripheral clock enable (MDIOSEN)
            uint32_t mdios_enable                       : 1;    // bit 5
            /// (reserved)
            uint32_t                                    : 2;    // bits 6:7
            /// FDCAN Peripheral Clocks Enable (FDCANEN)
            uint32_t fdcan_enable                       : 1;    // bit 8
            /// (reserved)
            uint32_t                                    : 23;    // bits 9:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        APB1HighClockEnable& operator=(APB1HighClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(APB1HighClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(APB1HighClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<APB1HighClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(APB1HighClockEnable) == 4UL, "Must be this exact size");
    /// RCC APB1 Clock Register (C1_APB1HENR)
    struct Processor1APB1HighClockEnable final {
        /// Default Constructor
        Processor1APB1HighClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Processor1APB1HighClockEnable(Processor1APB1HighClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Processor1APB1HighClockEnable(Processor1APB1HighClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Processor1APB1HighClockEnable(Processor1APB1HighClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Processor1APB1HighClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Processor1APB1HighClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Processor1APB1HighClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                                    : 1;    // bit 0
            /// Clock Recovery System peripheral clock enable (CRSEN)
            uint32_t clock_recovery_system_enable       : 1;    // bit 1
            /// SWPMI Peripheral Clocks Enable (SWPEN)
            uint32_t single_wire_protocol_leader_enable : 1;    // bit 2
            /// (reserved)
            uint32_t                                    : 1;    // bit 3
            /// OPAMP peripheral clock enable (OPAMPEN)
            uint32_t operational_amplifier_enable       : 1;    // bit 4
            /// MDIOS peripheral clock enable (MDIOSEN)
            uint32_t mdios_enable                       : 1;    // bit 5
            /// (reserved)
            uint32_t                                    : 2;    // bits 6:7
            /// FDCAN Peripheral Clocks Enable (FDCANEN)
            uint32_t fdcan_enable                       : 1;    // bit 8
            /// (reserved)
            uint32_t                                    : 23;    // bits 9:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Processor1APB1HighClockEnable& operator=(Processor1APB1HighClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Processor1APB1HighClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Processor1APB1HighClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Processor1APB1HighClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Processor1APB1HighClockEnable) == 4UL, "Must be this exact size");
    /// RCC APB2 Clock Register (C1_APB2ENR)
    struct Processor1APB2ClockEnable final {
        /// Default Constructor
        Processor1APB2ClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Processor1APB2ClockEnable(Processor1APB2ClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Processor1APB2ClockEnable(Processor1APB2ClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Processor1APB2ClockEnable(Processor1APB2ClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Processor1APB2ClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Processor1APB2ClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Processor1APB2ClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TIM1 peripheral clock enable (TIM1EN)
            uint32_t timer1_enable                : 1;    // bit 0
            /// TIM8 peripheral clock enable (TIM8EN)
            uint32_t timer8_enable                : 1;    // bit 1
            /// (reserved)
            uint32_t                              : 2;    // bits 2:3
            /// USART1 Peripheral Clocks Enable (USART1EN)
            uint32_t usart1_enable                : 1;    // bit 4
            /// USART6 Peripheral Clocks Enable (USART6EN)
            uint32_t usart6_enable                : 1;    // bit 5
            /// (reserved)
            uint32_t                              : 6;    // bits 6:11
            /// SPI1 Peripheral Clocks Enable (SPI1EN)
            uint32_t spi1_enable                  : 1;    // bit 12
            /// SPI4 Peripheral Clocks Enable (SPI4EN)
            uint32_t spi4_enable                  : 1;    // bit 13
            /// (reserved)
            uint32_t                              : 2;    // bits 14:15
            /// TIM15 peripheral clock enable (TIM15EN)
            uint32_t timer15_enable               : 1;    // bit 16
            /// TIM16 peripheral clock enable (TIM16EN)
            uint32_t timer16_enable               : 1;    // bit 17
            /// TIM17 peripheral clock enable (TIM17EN)
            uint32_t timer17_enable               : 1;    // bit 18
            /// (reserved)
            uint32_t                              : 1;    // bit 19
            /// SPI5 Peripheral Clocks Enable (SPI5EN)
            uint32_t spi5_enable                  : 1;    // bit 20
            /// (reserved)
            uint32_t                              : 1;    // bit 21
            /// SAI1 Peripheral Clocks Enable (SAI1EN)
            uint32_t sai1_enable                  : 1;    // bit 22
            /// SAI2 Peripheral Clocks Enable (SAI2EN)
            uint32_t sai2_enable                  : 1;    // bit 23
            /// SAI3 Peripheral Clocks Enable (SAI3EN)
            uint32_t sai3_enable                  : 1;    // bit 24
            /// (reserved)
            uint32_t                              : 3;    // bits 25:27
            /// DFSDM1 Peripheral Clocks Enable (DFSDM1EN)
            uint32_t dfsdm1_enable                : 1;    // bit 28
            /// HRTIM peripheral clock enable (HRTIMEN)
            uint32_t high_resolution_timer_enable : 1;    // bit 29
            /// (reserved)
            uint32_t                              : 2;    // bits 30:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Processor1APB2ClockEnable& operator=(Processor1APB2ClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Processor1APB2ClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Processor1APB2ClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Processor1APB2ClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Processor1APB2ClockEnable) == 4UL, "Must be this exact size");
    /// RCC APB2 Clock Register (APB2ENR)
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
            /// TIM1 peripheral clock enable (TIM1EN)
            uint32_t timer1_enable                : 1;    // bit 0
            /// TIM8 peripheral clock enable (TIM8EN)
            uint32_t timer8_enable                : 1;    // bit 1
            /// (reserved)
            uint32_t                              : 2;    // bits 2:3
            /// USART1 Peripheral Clocks Enable (USART1EN)
            uint32_t usart1_enable                : 1;    // bit 4
            /// USART6 Peripheral Clocks Enable (USART6EN)
            uint32_t usart6_enable                : 1;    // bit 5
            /// (reserved)
            uint32_t                              : 6;    // bits 6:11
            /// SPI1 Peripheral Clocks Enable (SPI1EN)
            uint32_t spi1_enable                  : 1;    // bit 12
            /// SPI4 Peripheral Clocks Enable (SPI4EN)
            uint32_t spi4_enable                  : 1;    // bit 13
            /// (reserved)
            uint32_t                              : 2;    // bits 14:15
            /// TIM15 peripheral clock enable (TIM15EN)
            uint32_t timer15_enable               : 1;    // bit 16
            /// TIM16 peripheral clock enable (TIM16EN)
            uint32_t timer16_enable               : 1;    // bit 17
            /// TIM17 peripheral clock enable (TIM17EN)
            uint32_t timer17_enable               : 1;    // bit 18
            /// (reserved)
            uint32_t                              : 1;    // bit 19
            /// SPI5 Peripheral Clocks Enable (SPI5EN)
            uint32_t spi5_enable                  : 1;    // bit 20
            /// (reserved)
            uint32_t                              : 1;    // bit 21
            /// SAI1 Peripheral Clocks Enable (SAI1EN)
            uint32_t sai1_enable                  : 1;    // bit 22
            /// SAI2 Peripheral Clocks Enable (SAI2EN)
            uint32_t sai2_enable                  : 1;    // bit 23
            /// SAI3 Peripheral Clocks Enable (SAI3EN)
            uint32_t sai3_enable                  : 1;    // bit 24
            /// (reserved)
            uint32_t                              : 3;    // bits 25:27
            /// DFSDM1 Peripheral Clocks Enable (DFSDM1EN)
            uint32_t dfsdm1_enable                : 1;    // bit 28
            /// HRTIM peripheral clock enable (HRTIMEN)
            uint32_t high_resolution_timer_enable : 1;    // bit 29
            /// (reserved)
            uint32_t                              : 2;    // bits 30:31
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
    /// RCC APB4 Clock Register (APB4ENR)
    struct APB4ClockEnable final {
        /// Default Constructor
        APB4ClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        APB4ClockEnable(APB4ClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        APB4ClockEnable(APB4ClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        APB4ClockEnable(APB4ClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit APB4ClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit APB4ClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~APB4ClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                      : 1;    // bit 0
            /// SYSCFG peripheral clock enable (SYSCFGEN)
            uint32_t syscfg_enable        : 1;    // bit 1
            /// (reserved)
            uint32_t                      : 1;    // bit 2
            /// LPUART1 Peripheral Clocks Enable (LPUART1EN)
            uint32_t lpuart1_enable       : 1;    // bit 3
            /// (reserved)
            uint32_t                      : 1;    // bit 4
            /// SPI6 Peripheral Clocks Enable (SPI6EN)
            uint32_t spi6_enable          : 1;    // bit 5
            /// (reserved)
            uint32_t                      : 1;    // bit 6
            /// I2C4 Peripheral Clocks Enable (I2C4EN)
            uint32_t i2c4_eanble          : 1;    // bit 7
            /// (reserved)
            uint32_t                      : 1;    // bit 8
            /// LPTIM2 Peripheral Clocks Enable (LPTIM2EN)
            uint32_t lptimer2_enable      : 1;    // bit 9
            /// LPTIM3 Peripheral Clocks Enable (LPTIM3EN)
            uint32_t lptimer3_enable      : 1;    // bit 10
            /// LPTIM4 Peripheral Clocks Enable (LPTIM4EN)
            uint32_t lptimer4_enable      : 1;    // bit 11
            /// LPTIM5 Peripheral Clocks Enable (LPTIM5EN)
            uint32_t lptimer5_enable      : 1;    // bit 12
            /// (reserved)
            uint32_t                      : 1;    // bit 13
            /// COMP1/2 peripheral clock enable (COMP12EN)
            uint32_t comp12_enable        : 1;    // bit 14
            /// VREF peripheral clock enable (VREFEN)
            uint32_t vref_enable          : 1;    // bit 15
            /// RTC APB Clock Enable (RTCAPBEN)
            uint32_t rtc_apb_clock_enable : 1;    // bit 16
            /// (reserved)
            uint32_t                      : 4;    // bits 17:20
            /// SAI4 Peripheral Clocks Enable (SAI4EN)
            uint32_t sai4_enable          : 1;    // bit 21
            /// (reserved)
            uint32_t                      : 10;    // bits 22:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        APB4ClockEnable& operator=(APB4ClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(APB4ClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(APB4ClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<APB4ClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(APB4ClockEnable) == 4UL, "Must be this exact size");
    /// RCC APB4 Clock Register (C1_APB4ENR)
    struct Processor1APB4ClockEnable final {
        /// Default Constructor
        Processor1APB4ClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Processor1APB4ClockEnable(Processor1APB4ClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Processor1APB4ClockEnable(Processor1APB4ClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Processor1APB4ClockEnable(Processor1APB4ClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Processor1APB4ClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Processor1APB4ClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Processor1APB4ClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                      : 1;    // bit 0
            /// SYSCFG peripheral clock enable (SYSCFGEN)
            uint32_t syscfg_enable        : 1;    // bit 1
            /// (reserved)
            uint32_t                      : 1;    // bit 2
            /// LPUART1 Peripheral Clocks Enable (LPUART1EN)
            uint32_t lpuart1_enable       : 1;    // bit 3
            /// (reserved)
            uint32_t                      : 1;    // bit 4
            /// SPI6 Peripheral Clocks Enable (SPI6EN)
            uint32_t spi6_enable          : 1;    // bit 5
            /// (reserved)
            uint32_t                      : 1;    // bit 6
            /// I2C4 Peripheral Clocks Enable (I2C4EN)
            uint32_t i2c4_eanble          : 1;    // bit 7
            /// (reserved)
            uint32_t                      : 1;    // bit 8
            /// LPTIM2 Peripheral Clocks Enable (LPTIM2EN)
            uint32_t lptimer2_enable      : 1;    // bit 9
            /// LPTIM3 Peripheral Clocks Enable (LPTIM3EN)
            uint32_t lptimer3_enable      : 1;    // bit 10
            /// LPTIM4 Peripheral Clocks Enable (LPTIM4EN)
            uint32_t lptimer4_enable      : 1;    // bit 11
            /// LPTIM5 Peripheral Clocks Enable (LPTIM5EN)
            uint32_t lptimer5_enable      : 1;    // bit 12
            /// (reserved)
            uint32_t                      : 1;    // bit 13
            /// COMP1/2 peripheral clock enable (COMP12EN)
            uint32_t comp12_enable        : 1;    // bit 14
            /// VREF peripheral clock enable (VREFEN)
            uint32_t vref_enable          : 1;    // bit 15
            /// RTC APB Clock Enable (RTCAPBEN)
            uint32_t rtc_apb_clock_enable : 1;    // bit 16
            /// (reserved)
            uint32_t                      : 4;    // bits 17:20
            /// SAI4 Peripheral Clocks Enable (SAI4EN)
            uint32_t sai4_enable          : 1;    // bit 21
            /// (reserved)
            uint32_t                      : 10;    // bits 22:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Processor1APB4ClockEnable& operator=(Processor1APB4ClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Processor1APB4ClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Processor1APB4ClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Processor1APB4ClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Processor1APB4ClockEnable) == 4UL, "Must be this exact size");
    /// RCC AHB3 Sleep Clock Register (C1_AHB3LPENR)
    struct Processor1AHB3LowPowerClockEnable final {
        /// Default Constructor
        Processor1AHB3LowPowerClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Processor1AHB3LowPowerClockEnable(Processor1AHB3LowPowerClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Processor1AHB3LowPowerClockEnable(Processor1AHB3LowPowerClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Processor1AHB3LowPowerClockEnable(Processor1AHB3LowPowerClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Processor1AHB3LowPowerClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Processor1AHB3LowPowerClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Processor1AHB3LowPowerClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// MDMA Clock Enable During CSleep Mode (MDMALPEN)
            uint32_t mdma_low_power_enable    : 1;    // bit 0
            /// (reserved)
            uint32_t                          : 3;    // bits 1:3
            /// DMA2D Clock Enable During CSleep Mode (DMA2DLPEN)
            uint32_t dma2d_low_power_enable   : 1;    // bit 4
            /// JPGDEC Clock Enable During CSleep Mode (JPGDECLPEN)
            uint32_t jpgdec_low_power_enable  : 1;    // bit 5
            /// (reserved)
            uint32_t                          : 2;    // bits 6:7
            /// FLITF Clock Enable During CSleep Mode (FLITFLPEN)
            uint32_t flitf_low_power_enable   : 1;    // bit 8
            /// (reserved)
            uint32_t                          : 3;    // bits 9:11
            /// FMC Peripheral Clocks Enable During CSleep Mode (FMCLPEN)
            uint32_t fmc_low_power_enable     : 1;    // bit 12
            /// (reserved)
            uint32_t                          : 1;    // bit 13
            /// QUADSPI and QUADSPI Delay Clock Enable During CSleep Mode (QSPILPEN)
            uint32_t qspi_low_power_enable    : 1;    // bit 14
            /// (reserved)
            uint32_t                          : 1;    // bit 15
            /// SDMMC1 and SDMMC1 Delay Clock Enable During CSleep Mode (SDMMC1LPEN)
            uint32_t sdmmc1_low_power_enable  : 1;    // bit 16
            /// (reserved)
            uint32_t                          : 11;    // bits 17:27
            /// D1DTCM1 Block Clock Enable During CSleep mode (D1DTCM1LPEN)
            uint32_t d1dtcm1_low_power_enable : 1;    // bit 28
            /// D1 DTCM2 Block Clock Enable During CSleep mode (DTCM2LPEN)
            uint32_t dtcm2_low_power_enable   : 1;    // bit 29
            /// D1ITCM Block Clock Enable During CSleep mode (ITCMLPEN)
            uint32_t itcm_low_power_enable    : 1;    // bit 30
            /// AXISRAM Block Clock Enable During CSleep mode (AXISRAMLPEN)
            uint32_t axisram_low_power_enable : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Processor1AHB3LowPowerClockEnable& operator=(Processor1AHB3LowPowerClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Processor1AHB3LowPowerClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Processor1AHB3LowPowerClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Processor1AHB3LowPowerClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Processor1AHB3LowPowerClockEnable) == 4UL, "Must be this exact size");
    /// RCC AHB3 Sleep Clock Register (AHB3LPENR)
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
            /// MDMA Clock Enable During CSleep Mode (MDMALPEN)
            uint32_t mdma_low_power_enable    : 1;    // bit 0
            /// (reserved)
            uint32_t                          : 3;    // bits 1:3
            /// DMA2D Clock Enable During CSleep Mode (DMA2DLPEN)
            uint32_t dma2d_low_power_enable   : 1;    // bit 4
            /// JPGDEC Clock Enable During CSleep Mode (JPGDECLPEN)
            uint32_t jpgdec_low_power_enable  : 1;    // bit 5
            /// (reserved)
            uint32_t                          : 2;    // bits 6:7
            /// FLITF Clock Enable During CSleep Mode (FLASHLPEN)
            uint32_t flash_low_power_enable   : 1;    // bit 8
            /// (reserved)
            uint32_t                          : 3;    // bits 9:11
            /// FMC Peripheral Clocks Enable During CSleep Mode (FMCLPEN)
            uint32_t fmc_low_power_enable     : 1;    // bit 12
            /// (reserved)
            uint32_t                          : 1;    // bit 13
            /// QUADSPI and QUADSPI Delay Clock Enable During CSleep Mode (QSPILPEN)
            uint32_t qspi_low_power_enable    : 1;    // bit 14
            /// (reserved)
            uint32_t                          : 1;    // bit 15
            /// SDMMC1 and SDMMC1 Delay Clock Enable During CSleep Mode (SDMMC1LPEN)
            uint32_t sdmmc1_low_power_enable  : 1;    // bit 16
            /// (reserved)
            uint32_t                          : 11;    // bits 17:27
            /// D1DTCM1 Block Clock Enable During CSleep mode (D1DTCM1LPEN)
            uint32_t d1dtcm1_low_power_enable : 1;    // bit 28
            /// D1 DTCM2 Block Clock Enable During CSleep mode (DTCM2LPEN)
            uint32_t dtcm2_low_power_enable   : 1;    // bit 29
            /// D1ITCM Block Clock Enable During CSleep mode (ITCMLPEN)
            uint32_t itcm_low_power_enable    : 1;    // bit 30
            /// AXISRAM Block Clock Enable During CSleep mode (AXISRAMLPEN)
            uint32_t axisram_low_power_enable : 1;    // bit 31
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
    /// RCC AHB1 Sleep Clock Register (AHB1LPENR)
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
            /// DMA1 Clock Enable During CSleep Mode (DMA1LPEN)
            uint32_t dma1_low_power_enable                     : 1;    // bit 0
            /// DMA2 Clock Enable During CSleep Mode (DMA2LPEN)
            uint32_t dma2_low_power_enable                     : 1;    // bit 1
            /// (reserved)
            uint32_t                                           : 3;    // bits 2:4
            /// ADC1/2 Peripheral Clocks Enable During CSleep Mode (ADC12LPEN)
            uint32_t adc12_low_power_enable                    : 1;    // bit 5
            /// (reserved)
            uint32_t                                           : 9;    // bits 6:14
            /// Ethernet MAC bus interface Clock Enable During CSleep Mode (ETH1MACLPEN)
            uint32_t ethernet1_mac_low_power_enable            : 1;    // bit 15
            /// Ethernet Transmission Clock Enable During CSleep Mode (ETH1TXLPEN)
            uint32_t ethernet1_transmit_low_power_enable       : 1;    // bit 16
            /// Ethernet Reception Clock Enable During CSleep Mode (ETH1RXLPEN)
            uint32_t ethernet1_receive_low_power_enable        : 1;    // bit 17
            /// (reserved)
            uint32_t                                           : 7;    // bits 18:24
            /// USB1OTG peripheral clock enable during CSleep mode (USB1OTGHSLPEN)
            uint32_t usb1_otg_high_speed_low_power_enable      : 1;    // bit 25
            /// USB_PHY1 clock enable during CSleep mode (USB1OTGHSULPILPEN)
            uint32_t usb1_otg_high_speed_ulpi_low_power_enable : 1;    // bit 26
            /// USB2OTG peripheral clock enable during CSleep mode (USB2OTGHSLPEN)
            uint32_t usb2_otg_high_speed_low_power_enable      : 1;    // bit 27
            /// USB_PHY2 clocks enable during CSleep mode (USB2OTGHSULPILPEN)
            uint32_t usb2_otg_high_speed_ulpi_low_power_enable : 1;    // bit 28
            /// (reserved)
            uint32_t                                           : 3;    // bits 29:31
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
    /// RCC AHB1 Sleep Clock Register (C1_AHB1LPENR)
    struct Processor1AHB1LowPowerClockEnable final {
        /// Default Constructor
        Processor1AHB1LowPowerClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Processor1AHB1LowPowerClockEnable(Processor1AHB1LowPowerClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Processor1AHB1LowPowerClockEnable(Processor1AHB1LowPowerClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Processor1AHB1LowPowerClockEnable(Processor1AHB1LowPowerClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Processor1AHB1LowPowerClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Processor1AHB1LowPowerClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Processor1AHB1LowPowerClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// DMA1 Clock Enable During CSleep Mode (DMA1LPEN)
            uint32_t dma1_low_power_enable               : 1;    // bit 0
            /// DMA2 Clock Enable During CSleep Mode (DMA2LPEN)
            uint32_t dma2_low_power_enable               : 1;    // bit 1
            /// (reserved)
            uint32_t                                     : 3;    // bits 2:4
            /// ADC1/2 Peripheral Clocks Enable During CSleep Mode (ADC12LPEN)
            uint32_t adc12_low_power_enable              : 1;    // bit 5
            /// (reserved)
            uint32_t                                     : 9;    // bits 6:14
            /// Ethernet MAC bus interface Clock Enable During CSleep Mode (ETH1MACLPEN)
            uint32_t ethernet1_mac_low_power_enable      : 1;    // bit 15
            /// Ethernet Transmission Clock Enable During CSleep Mode (ETH1TXLPEN)
            uint32_t ethernet1_transmit_low_power_enable : 1;    // bit 16
            /// Ethernet Reception Clock Enable During CSleep Mode (ETH1RXLPEN)
            uint32_t ethernet1_receive_low_power_enable  : 1;    // bit 17
            /// (reserved)
            uint32_t                                     : 7;    // bits 18:24
            /// USB1OTG peripheral clock enable during CSleep mode (USB1OTGLPEN)
            uint32_t usb1_otg_low_power_enable           : 1;    // bit 25
            /// USB_PHY1 clock enable during CSleep mode (USB1ULPILPEN)
            uint32_t usb1_ulpi_low_power_enable          : 1;    // bit 26
            /// USB2OTG peripheral clock enable during CSleep mode (USB2OTGLPEN)
            uint32_t usb2_otg_low_power_enable           : 1;    // bit 27
            /// USB_PHY2 clocks enable during CSleep mode (USB2ULPILPEN)
            uint32_t usb2_ulpi_low_power_enable          : 1;    // bit 28
            /// (reserved)
            uint32_t                                     : 3;    // bits 29:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Processor1AHB1LowPowerClockEnable& operator=(Processor1AHB1LowPowerClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Processor1AHB1LowPowerClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Processor1AHB1LowPowerClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Processor1AHB1LowPowerClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Processor1AHB1LowPowerClockEnable) == 4UL, "Must be this exact size");
    /// RCC AHB2 Sleep Clock Register (C1_AHB2LPENR)
    struct Processor1AHB2LowPowerClockEnable final {
        /// Default Constructor
        Processor1AHB2LowPowerClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Processor1AHB2LowPowerClockEnable(Processor1AHB2LowPowerClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Processor1AHB2LowPowerClockEnable(Processor1AHB2LowPowerClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Processor1AHB2LowPowerClockEnable(Processor1AHB2LowPowerClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Processor1AHB2LowPowerClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Processor1AHB2LowPowerClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Processor1AHB2LowPowerClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CAMITF peripheral clock enable during CSleep mode (CAMITFLPEN)
            uint32_t camitf_low_power_enable : 1;    // bit 0
            /// (reserved)
            uint32_t                         : 3;    // bits 1:3
            /// CRYPT peripheral clock enable during CSleep mode (CRYPTLPEN)
            uint32_t crypto_low_power_enable : 1;    // bit 4
            /// HASH peripheral clock enable during CSleep mode (HASHLPEN)
            uint32_t hash_low_power_enable   : 1;    // bit 5
            /// RNG peripheral clock enable during CSleep mode (RNGLPEN)
            uint32_t low_power_enable        : 1;    // bit 6
            /// (reserved)
            uint32_t                         : 2;    // bits 7:8
            /// SDMMC2 and SDMMC2 Delay Clock Enable During CSleep Mode (SDMMC2LPEN)
            uint32_t sdmmc2_low_power_enable : 1;    // bit 9
            /// (reserved)
            uint32_t                         : 19;    // bits 10:28
            /// SRAM1 Clock Enable During CSleep Mode (SRAM1LPEN)
            uint32_t sram1_low_power_enable  : 1;    // bit 29
            /// SRAM2 Clock Enable During CSleep Mode (SRAM2LPEN)
            uint32_t sram2_low_power_enable  : 1;    // bit 30
            /// SRAM3 Clock Enable During CSleep Mode (SRAM3LPEN)
            uint32_t sram3_low_power_enable  : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Processor1AHB2LowPowerClockEnable& operator=(Processor1AHB2LowPowerClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Processor1AHB2LowPowerClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Processor1AHB2LowPowerClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Processor1AHB2LowPowerClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Processor1AHB2LowPowerClockEnable) == 4UL, "Must be this exact size");
    /// RCC AHB2 Sleep Clock Register (AHB2LPENR)
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
            /// CAMITF peripheral clock enable during CSleep mode (CAMITFLPEN)
            uint32_t camitf_low_power_enable : 1;    // bit 0
            /// (reserved)
            uint32_t                         : 3;    // bits 1:3
            /// CRYPT peripheral clock enable during CSleep mode (CRYPTLPEN)
            uint32_t crypto_low_power_enable : 1;    // bit 4
            /// HASH peripheral clock enable during CSleep mode (HASHLPEN)
            uint32_t hash_low_power_enable   : 1;    // bit 5
            /// RNG peripheral clock enable during CSleep mode (RNGLPEN)
            uint32_t low_power_enable        : 1;    // bit 6
            /// (reserved)
            uint32_t                         : 2;    // bits 7:8
            /// SDMMC2 and SDMMC2 Delay Clock Enable During CSleep Mode (SDMMC2LPEN)
            uint32_t sdmmc2_low_power_enable : 1;    // bit 9
            /// (reserved)
            uint32_t                         : 19;    // bits 10:28
            /// SRAM1 Clock Enable During CSleep Mode (SRAM1LPEN)
            uint32_t sram1_low_power_enable  : 1;    // bit 29
            /// SRAM2 Clock Enable During CSleep Mode (SRAM2LPEN)
            uint32_t sram2_low_power_enable  : 1;    // bit 30
            /// SRAM3 Clock Enable During CSleep Mode (SRAM3LPEN)
            uint32_t sram3_low_power_enable  : 1;    // bit 31
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
    /// RCC AHB4 Sleep Clock Register (AHB4LPENR)
    struct AHB4LowPowerClockEnable final {
        /// Default Constructor
        AHB4LowPowerClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        AHB4LowPowerClockEnable(AHB4LowPowerClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        AHB4LowPowerClockEnable(AHB4LowPowerClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        AHB4LowPowerClockEnable(AHB4LowPowerClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit AHB4LowPowerClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit AHB4LowPowerClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~AHB4LowPowerClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// GPIO peripheral clock enable during CSleep mode (GPIOALPEN)
            uint32_t gpioa_low_power_enable      : 1;    // bit 0
            /// GPIO peripheral clock enable during CSleep mode (GPIOBLPEN)
            uint32_t gpiob_low_power_enable      : 1;    // bit 1
            /// GPIO peripheral clock enable during CSleep mode (GPIOCLPEN)
            uint32_t gpioc_low_power_enable      : 1;    // bit 2
            /// GPIO peripheral clock enable during CSleep mode (GPIODLPEN)
            uint32_t gpiod_low_power_enable      : 1;    // bit 3
            /// GPIO peripheral clock enable during CSleep mode (GPIOELPEN)
            uint32_t gpioe_low_power_enable      : 1;    // bit 4
            /// GPIO peripheral clock enable during CSleep mode (GPIOFLPEN)
            uint32_t gpiof_low_power_enable      : 1;    // bit 5
            /// GPIO peripheral clock enable during CSleep mode (GPIOGLPEN)
            uint32_t gpiog_low_power_enable      : 1;    // bit 6
            /// GPIO peripheral clock enable during CSleep mode (GPIOHLPEN)
            uint32_t gpioh_low_power_enable      : 1;    // bit 7
            /// GPIO peripheral clock enable during CSleep mode (GPIOILPEN)
            uint32_t gpioi_low_power_enable      : 1;    // bit 8
            /// GPIO peripheral clock enable during CSleep mode (GPIOJLPEN)
            uint32_t gpioj_low_power_enable      : 1;    // bit 9
            /// GPIO peripheral clock enable during CSleep mode (GPIOKLPEN)
            uint32_t gpiok_low_power_enable      : 1;    // bit 10
            /// (reserved)
            uint32_t                             : 8;    // bits 11:18
            /// CRC peripheral clock enable during CSleep mode (CRCLPEN)
            uint32_t crc_low_power_enable        : 1;    // bit 19
            /// (reserved)
            uint32_t                             : 1;    // bit 20
            /// BDMA Clock Enable During CSleep Mode (BDMALPEN)
            uint32_t bdma_low_power_enable       : 1;    // bit 21
            /// (reserved)
            uint32_t                             : 2;    // bits 22:23
            /// ADC3 Peripheral Clocks Enable During CSleep Mode (ADC3LPEN)
            uint32_t adc3_low_power_enable       : 1;    // bit 24
            /// (reserved)
            uint32_t                             : 3;    // bits 25:27
            /// Backup RAM Clock Enable During CSleep Mode (BKPRAMLPEN)
            uint32_t backup_ram_low_power_enable : 1;    // bit 28
            /// SRAM4 Clock Enable During CSleep Mode (SRAM4LPEN)
            uint32_t sram4_low_power_enable      : 1;    // bit 29
            /// (reserved)
            uint32_t                             : 2;    // bits 30:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        AHB4LowPowerClockEnable& operator=(AHB4LowPowerClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(AHB4LowPowerClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(AHB4LowPowerClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<AHB4LowPowerClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(AHB4LowPowerClockEnable) == 4UL, "Must be this exact size");
    /// RCC AHB4 Sleep Clock Register (C1_AHB4LPENR)
    struct Processor1AHB4LowPowerClockEnable final {
        /// Default Constructor
        Processor1AHB4LowPowerClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Processor1AHB4LowPowerClockEnable(Processor1AHB4LowPowerClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Processor1AHB4LowPowerClockEnable(Processor1AHB4LowPowerClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Processor1AHB4LowPowerClockEnable(Processor1AHB4LowPowerClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Processor1AHB4LowPowerClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Processor1AHB4LowPowerClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Processor1AHB4LowPowerClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// GPIO peripheral clock enable during CSleep mode (GPIOALPEN)
            uint32_t gpioa_low_power_enable      : 1;    // bit 0
            /// GPIO peripheral clock enable during CSleep mode (GPIOBLPEN)
            uint32_t gpiob_low_power_enable      : 1;    // bit 1
            /// GPIO peripheral clock enable during CSleep mode (GPIOCLPEN)
            uint32_t gpioc_low_power_enable      : 1;    // bit 2
            /// GPIO peripheral clock enable during CSleep mode (GPIODLPEN)
            uint32_t gpiod_low_power_enable      : 1;    // bit 3
            /// GPIO peripheral clock enable during CSleep mode (GPIOELPEN)
            uint32_t gpioe_low_power_enable      : 1;    // bit 4
            /// GPIO peripheral clock enable during CSleep mode (GPIOFLPEN)
            uint32_t gpiof_low_power_enable      : 1;    // bit 5
            /// GPIO peripheral clock enable during CSleep mode (GPIOGLPEN)
            uint32_t gpiog_low_power_enable      : 1;    // bit 6
            /// GPIO peripheral clock enable during CSleep mode (GPIOHLPEN)
            uint32_t gpioh_low_power_enable      : 1;    // bit 7
            /// GPIO peripheral clock enable during CSleep mode (GPIOILPEN)
            uint32_t gpioi_low_power_enable      : 1;    // bit 8
            /// GPIO peripheral clock enable during CSleep mode (GPIOJLPEN)
            uint32_t gpioj_low_power_enable      : 1;    // bit 9
            /// GPIO peripheral clock enable during CSleep mode (GPIOKLPEN)
            uint32_t gpiok_low_power_enable      : 1;    // bit 10
            /// (reserved)
            uint32_t                             : 8;    // bits 11:18
            /// CRC peripheral clock enable during CSleep mode (CRCLPEN)
            uint32_t crc_low_power_enable        : 1;    // bit 19
            /// (reserved)
            uint32_t                             : 1;    // bit 20
            /// BDMA Clock Enable During CSleep Mode (BDMALPEN)
            uint32_t bdma_low_power_enable       : 1;    // bit 21
            /// (reserved)
            uint32_t                             : 2;    // bits 22:23
            /// ADC3 Peripheral Clocks Enable During CSleep Mode (ADC3LPEN)
            uint32_t adc3_low_power_enable       : 1;    // bit 24
            /// (reserved)
            uint32_t                             : 3;    // bits 25:27
            /// Backup RAM Clock Enable During CSleep Mode (BKPRAMLPEN)
            uint32_t backup_ram_low_power_enable : 1;    // bit 28
            /// SRAM4 Clock Enable During CSleep Mode (SRAM4LPEN)
            uint32_t sram4_low_power_enable      : 1;    // bit 29
            /// (reserved)
            uint32_t                             : 2;    // bits 30:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Processor1AHB4LowPowerClockEnable& operator=(Processor1AHB4LowPowerClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Processor1AHB4LowPowerClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Processor1AHB4LowPowerClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Processor1AHB4LowPowerClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Processor1AHB4LowPowerClockEnable) == 4UL, "Must be this exact size");
    /// RCC APB3 Sleep Clock Register (C1_APB3LPENR)
    struct Processor1APB3LowPowerClockEnable final {
        /// Default Constructor
        Processor1APB3LowPowerClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Processor1APB3LowPowerClockEnable(Processor1APB3LowPowerClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Processor1APB3LowPowerClockEnable(Processor1APB3LowPowerClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Processor1APB3LowPowerClockEnable(Processor1APB3LowPowerClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Processor1APB3LowPowerClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Processor1APB3LowPowerClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Processor1APB3LowPowerClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                        : 3;    // bits 0:2
            /// LTDC peripheral clock enable during CSleep mode (LTDCLPEN)
            uint32_t ltdc_low_power_enable  : 1;    // bit 3
            /// (reserved)
            uint32_t                        : 2;    // bits 4:5
            /// WWDG1 Clock Enable During CSleep Mode (WWDG1LPEN)
            uint32_t wwdg1_low_power_enable : 1;    // bit 6
            /// (reserved)
            uint32_t                        : 25;    // bits 7:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Processor1APB3LowPowerClockEnable& operator=(Processor1APB3LowPowerClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Processor1APB3LowPowerClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Processor1APB3LowPowerClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Processor1APB3LowPowerClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Processor1APB3LowPowerClockEnable) == 4UL, "Must be this exact size");
    /// RCC APB3 Sleep Clock Register (APB3LPENR)
    struct APB3LowPowerClockEnable final {
        /// Default Constructor
        APB3LowPowerClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        APB3LowPowerClockEnable(APB3LowPowerClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        APB3LowPowerClockEnable(APB3LowPowerClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        APB3LowPowerClockEnable(APB3LowPowerClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit APB3LowPowerClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit APB3LowPowerClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~APB3LowPowerClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                        : 3;    // bits 0:2
            /// LTDC peripheral clock enable during CSleep mode (LTDCLPEN)
            uint32_t ltdc_low_power_enable  : 1;    // bit 3
            /// (reserved)
            uint32_t                        : 2;    // bits 4:5
            /// WWDG1 Clock Enable During CSleep Mode (WWDG1LPEN)
            uint32_t wwdg1_low_power_enable : 1;    // bit 6
            /// (reserved)
            uint32_t                        : 25;    // bits 7:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        APB3LowPowerClockEnable& operator=(APB3LowPowerClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(APB3LowPowerClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(APB3LowPowerClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<APB3LowPowerClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(APB3LowPowerClockEnable) == 4UL, "Must be this exact size");
    /// RCC APB1 Low Sleep Clock Register (APB1LLPENR)
    struct APB1LowLowPowerClockEnable final {
        /// Default Constructor
        APB1LowLowPowerClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        APB1LowLowPowerClockEnable(APB1LowLowPowerClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        APB1LowLowPowerClockEnable(APB1LowLowPowerClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        APB1LowLowPowerClockEnable(APB1LowLowPowerClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit APB1LowLowPowerClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit APB1LowLowPowerClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~APB1LowLowPowerClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TIM2 peripheral clock enable during CSleep mode (TIM2LPEN)
            uint32_t timer2_low_power_enable   : 1;    // bit 0
            /// TIM3 peripheral clock enable during CSleep mode (TIM3LPEN)
            uint32_t timer3_low_power_enable   : 1;    // bit 1
            /// TIM4 peripheral clock enable during CSleep mode (TIM4LPEN)
            uint32_t timer4_low_power_enable   : 1;    // bit 2
            /// TIM5 peripheral clock enable during CSleep mode (TIM5LPEN)
            uint32_t timer5_low_power_enable   : 1;    // bit 3
            /// TIM6 peripheral clock enable during CSleep mode (TIM6LPEN)
            uint32_t timer6_low_power_enable   : 1;    // bit 4
            /// TIM7 peripheral clock enable during CSleep mode (TIM7LPEN)
            uint32_t timer7_low_power_enable   : 1;    // bit 5
            /// TIM12 peripheral clock enable during CSleep mode (TIM12LPEN)
            uint32_t timer12_low_power_enable  : 1;    // bit 6
            /// TIM13 peripheral clock enable during CSleep mode (TIM13LPEN)
            uint32_t timer13_low_power_enable  : 1;    // bit 7
            /// TIM14 peripheral clock enable during CSleep mode (TIM14LPEN)
            uint32_t timer14_low_power_enable  : 1;    // bit 8
            /// LPTIM1 Peripheral Clocks Enable During CSleep Mode (LPTIM1LPEN)
            uint32_t lptimer1_low_power_enable : 1;    // bit 9
            /// (reserved)
            uint32_t                           : 4;    // bits 10:13
            /// SPI2 Peripheral Clocks Enable During CSleep Mode (SPI2LPEN)
            uint32_t spi2_low_power_enable     : 1;    // bit 14
            /// SPI3 Peripheral Clocks Enable During CSleep Mode (SPI3LPEN)
            uint32_t spi3_low_power_enable     : 1;    // bit 15
            /// SPDIFRX Peripheral Clocks Enable During CSleep Mode (SPDIFRXLPEN)
            uint32_t spdifrx_low_power_enable  : 1;    // bit 16
            /// USART2 Peripheral Clocks Enable During CSleep Mode (USART2LPEN)
            uint32_t usart2_low_power_enable   : 1;    // bit 17
            /// USART3 Peripheral Clocks Enable During CSleep Mode (USART3LPEN)
            uint32_t usart3_low_power_enable   : 1;    // bit 18
            /// UART4 Peripheral Clocks Enable During CSleep Mode (UART4LPEN)
            uint32_t uart4_low_power_enable    : 1;    // bit 19
            /// UART5 Peripheral Clocks Enable During CSleep Mode (UART5LPEN)
            uint32_t uart5_low_power_enable    : 1;    // bit 20
            /// I2C1 Peripheral Clocks Enable During CSleep Mode (I2C1LPEN)
            uint32_t i2c1_low_power_enable     : 1;    // bit 21
            /// I2C2 Peripheral Clocks Enable During CSleep Mode (I2C2LPEN)
            uint32_t i2c2_low_power_enable     : 1;    // bit 22
            /// I2C3 Peripheral Clocks Enable During CSleep Mode (I2C3LPEN)
            uint32_t i2c3_low_power_enable     : 1;    // bit 23
            /// (reserved)
            uint32_t                           : 3;    // bits 24:26
            /// HDMI-CEC Peripheral Clocks Enable During CSleep Mode (HDMICECLPEN)
            uint32_t hdmicec_low_power_enable  : 1;    // bit 27
            /// (reserved)
            uint32_t                           : 1;    // bit 28
            /// DAC1/2 peripheral clock enable during CSleep mode (DAC12LPEN)
            uint32_t dac12_low_power_enable    : 1;    // bit 29
            /// USART7 Peripheral Clocks Enable During CSleep Mode (USART7LPEN)
            uint32_t usart7_low_power_enable   : 1;    // bit 30
            /// USART8 Peripheral Clocks Enable During CSleep Mode (USART8LPEN)
            uint32_t usart8_low_power_enable   : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        APB1LowLowPowerClockEnable& operator=(APB1LowLowPowerClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(APB1LowLowPowerClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(APB1LowLowPowerClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<APB1LowLowPowerClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(APB1LowLowPowerClockEnable) == 4UL, "Must be this exact size");
    /// RCC APB1 Low Sleep Clock Register (C1_APB1LLPENR)
    struct Processor1APB1LowLowPowerClockEnable final {
        /// Default Constructor
        Processor1APB1LowLowPowerClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Processor1APB1LowLowPowerClockEnable(Processor1APB1LowLowPowerClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Processor1APB1LowLowPowerClockEnable(Processor1APB1LowLowPowerClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Processor1APB1LowLowPowerClockEnable(Processor1APB1LowLowPowerClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Processor1APB1LowLowPowerClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Processor1APB1LowLowPowerClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Processor1APB1LowLowPowerClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TIM2 peripheral clock enable during CSleep mode (TIM2LPEN)
            uint32_t timer2_low_power_enable   : 1;    // bit 0
            /// TIM3 peripheral clock enable during CSleep mode (TIM3LPEN)
            uint32_t timer3_low_power_enable   : 1;    // bit 1
            /// TIM4 peripheral clock enable during CSleep mode (TIM4LPEN)
            uint32_t timer4_low_power_enable   : 1;    // bit 2
            /// TIM5 peripheral clock enable during CSleep mode (TIM5LPEN)
            uint32_t timer5_low_power_enable   : 1;    // bit 3
            /// TIM6 peripheral clock enable during CSleep mode (TIM6LPEN)
            uint32_t timer6_low_power_enable   : 1;    // bit 4
            /// TIM7 peripheral clock enable during CSleep mode (TIM7LPEN)
            uint32_t timer7_low_power_enable   : 1;    // bit 5
            /// TIM12 peripheral clock enable during CSleep mode (TIM12LPEN)
            uint32_t timer12_low_power_enable  : 1;    // bit 6
            /// TIM13 peripheral clock enable during CSleep mode (TIM13LPEN)
            uint32_t timer13_low_power_enable  : 1;    // bit 7
            /// TIM14 peripheral clock enable during CSleep mode (TIM14LPEN)
            uint32_t timer14_low_power_enable  : 1;    // bit 8
            /// LPTIM1 Peripheral Clocks Enable During CSleep Mode (LPTIM1LPEN)
            uint32_t lptimer1_low_power_enable : 1;    // bit 9
            /// (reserved)
            uint32_t                           : 4;    // bits 10:13
            /// SPI2 Peripheral Clocks Enable During CSleep Mode (SPI2LPEN)
            uint32_t spi2_low_power_enable     : 1;    // bit 14
            /// SPI3 Peripheral Clocks Enable During CSleep Mode (SPI3LPEN)
            uint32_t spi3_low_power_enable     : 1;    // bit 15
            /// SPDIFRX Peripheral Clocks Enable During CSleep Mode (SPDIFRXLPEN)
            uint32_t spdifrx_low_power_enable  : 1;    // bit 16
            /// USART2 Peripheral Clocks Enable During CSleep Mode (USART2LPEN)
            uint32_t usart2_low_power_enable   : 1;    // bit 17
            /// USART3 Peripheral Clocks Enable During CSleep Mode (USART3LPEN)
            uint32_t usart3_low_power_enable   : 1;    // bit 18
            /// UART4 Peripheral Clocks Enable During CSleep Mode (UART4LPEN)
            uint32_t uart4_low_power_enable    : 1;    // bit 19
            /// UART5 Peripheral Clocks Enable During CSleep Mode (UART5LPEN)
            uint32_t uart5_low_power_enable    : 1;    // bit 20
            /// I2C1 Peripheral Clocks Enable During CSleep Mode (I2C1LPEN)
            uint32_t i2c1_low_power_enable     : 1;    // bit 21
            /// I2C2 Peripheral Clocks Enable During CSleep Mode (I2C2LPEN)
            uint32_t i2c2_low_power_enable     : 1;    // bit 22
            /// I2C3 Peripheral Clocks Enable During CSleep Mode (I2C3LPEN)
            uint32_t i2c3_low_power_enable     : 1;    // bit 23
            /// (reserved)
            uint32_t                           : 3;    // bits 24:26
            /// HDMI-CEC Peripheral Clocks Enable During CSleep Mode (HDMICECLPEN)
            uint32_t hdmicec_low_power_enable  : 1;    // bit 27
            /// (reserved)
            uint32_t                           : 1;    // bit 28
            /// DAC1/2 peripheral clock enable during CSleep mode (DAC12LPEN)
            uint32_t dac12_low_power_enable    : 1;    // bit 29
            /// USART7 Peripheral Clocks Enable During CSleep Mode (USART7LPEN)
            uint32_t usart7_low_power_enable   : 1;    // bit 30
            /// USART8 Peripheral Clocks Enable During CSleep Mode (USART8LPEN)
            uint32_t usart8_low_power_enable   : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Processor1APB1LowLowPowerClockEnable& operator=(Processor1APB1LowLowPowerClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Processor1APB1LowLowPowerClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Processor1APB1LowLowPowerClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Processor1APB1LowLowPowerClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Processor1APB1LowLowPowerClockEnable) == 4UL, "Must be this exact size");
    /// RCC APB1 High Sleep Clock Register (C1_APB1HLPENR)
    struct Processor1APB1HighLowPowerClockEnable final {
        /// Default Constructor
        Processor1APB1HighLowPowerClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Processor1APB1HighLowPowerClockEnable(Processor1APB1HighLowPowerClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Processor1APB1HighLowPowerClockEnable(Processor1APB1HighLowPowerClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Processor1APB1HighLowPowerClockEnable(Processor1APB1HighLowPowerClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Processor1APB1HighLowPowerClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Processor1APB1HighLowPowerClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Processor1APB1HighLowPowerClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                                        : 1;    // bit 0
            /// Clock Recovery System peripheral clock enable during CSleep mode (CRSLPEN)
            uint32_t clock_recovery_system_low_power_enable : 1;    // bit 1
            /// SWPMI Peripheral Clocks Enable During CSleep Mode (SWPLPEN)
            uint32_t single_wire_protocol_low_power_enable  : 1;    // bit 2
            /// (reserved)
            uint32_t                                        : 1;    // bit 3
            /// OPAMP peripheral clock enable during CSleep mode (OPAMPLPEN)
            uint32_t operational_amplifier_low_power_enable : 1;    // bit 4
            /// MDIOS peripheral clock enable during CSleep mode (MDIOSLPEN)
            uint32_t mdios_low_power_enable                 : 1;    // bit 5
            /// (reserved)
            uint32_t                                        : 2;    // bits 6:7
            /// FDCAN Peripheral Clocks Enable During CSleep Mode (FDCANLPEN)
            uint32_t fdcan_low_power_enable                 : 1;    // bit 8
            /// (reserved)
            uint32_t                                        : 23;    // bits 9:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Processor1APB1HighLowPowerClockEnable& operator=(Processor1APB1HighLowPowerClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Processor1APB1HighLowPowerClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Processor1APB1HighLowPowerClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Processor1APB1HighLowPowerClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Processor1APB1HighLowPowerClockEnable) == 4UL, "Must be this exact size");
    /// RCC APB1 High Sleep Clock Register (APB1HLPENR)
    struct APB1HighLowPowerClockEnable final {
        /// Default Constructor
        APB1HighLowPowerClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        APB1HighLowPowerClockEnable(APB1HighLowPowerClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        APB1HighLowPowerClockEnable(APB1HighLowPowerClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        APB1HighLowPowerClockEnable(APB1HighLowPowerClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit APB1HighLowPowerClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit APB1HighLowPowerClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~APB1HighLowPowerClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                                        : 1;    // bit 0
            /// Clock Recovery System peripheral clock enable during CSleep mode (CRSLPEN)
            uint32_t clock_recovery_system_low_power_enable : 1;    // bit 1
            /// SWPMI Peripheral Clocks Enable During CSleep Mode (SWPLPEN)
            uint32_t single_wire_protocol_low_power_enable  : 1;    // bit 2
            /// (reserved)
            uint32_t                                        : 1;    // bit 3
            /// OPAMP peripheral clock enable during CSleep mode (OPAMPLPEN)
            uint32_t operational_amplifier_low_power_enable : 1;    // bit 4
            /// MDIOS peripheral clock enable during CSleep mode (MDIOSLPEN)
            uint32_t mdios_low_power_enable                 : 1;    // bit 5
            /// (reserved)
            uint32_t                                        : 2;    // bits 6:7
            /// FDCAN Peripheral Clocks Enable During CSleep Mode (FDCANLPEN)
            uint32_t fdcan_low_power_enable                 : 1;    // bit 8
            /// (reserved)
            uint32_t                                        : 23;    // bits 9:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        APB1HighLowPowerClockEnable& operator=(APB1HighLowPowerClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(APB1HighLowPowerClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(APB1HighLowPowerClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<APB1HighLowPowerClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(APB1HighLowPowerClockEnable) == 4UL, "Must be this exact size");
    /// RCC APB2 Sleep Clock Register (APB2LPENR)
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
            /// TIM1 peripheral clock enable during CSleep mode (TIM1LPEN)
            uint32_t timer1_low_power_enable                : 1;    // bit 0
            /// TIM8 peripheral clock enable during CSleep mode (TIM8LPEN)
            uint32_t timer8_low_power_enable                : 1;    // bit 1
            /// (reserved)
            uint32_t                                        : 2;    // bits 2:3
            /// USART1 Peripheral Clocks Enable During CSleep Mode (USART1LPEN)
            uint32_t usart1_low_power_enable                : 1;    // bit 4
            /// USART6 Peripheral Clocks Enable During CSleep Mode (USART6LPEN)
            uint32_t usart6_low_power_enable                : 1;    // bit 5
            /// (reserved)
            uint32_t                                        : 6;    // bits 6:11
            /// SPI1 Peripheral Clocks Enable During CSleep Mode (SPI1LPEN)
            uint32_t spi1_low_power_enable                  : 1;    // bit 12
            /// SPI4 Peripheral Clocks Enable During CSleep Mode (SPI4LPEN)
            uint32_t spi4_low_power_enable                  : 1;    // bit 13
            /// (reserved)
            uint32_t                                        : 2;    // bits 14:15
            /// TIM15 peripheral clock enable during CSleep mode (TIM15LPEN)
            uint32_t timer15_low_power_enable               : 1;    // bit 16
            /// TIM16 peripheral clock enable during CSleep mode (TIM16LPEN)
            uint32_t timer16_low_power_enable               : 1;    // bit 17
            /// TIM17 peripheral clock enable during CSleep mode (TIM17LPEN)
            uint32_t timer17_low_power_enable               : 1;    // bit 18
            /// (reserved)
            uint32_t                                        : 1;    // bit 19
            /// SPI5 Peripheral Clocks Enable During CSleep Mode (SPI5LPEN)
            uint32_t spi5_low_power_enable                  : 1;    // bit 20
            /// (reserved)
            uint32_t                                        : 1;    // bit 21
            /// SAI1 Peripheral Clocks Enable During CSleep Mode (SAI1LPEN)
            uint32_t sai1_low_power_enable                  : 1;    // bit 22
            /// SAI2 Peripheral Clocks Enable During CSleep Mode (SAI2LPEN)
            uint32_t sai2_low_power_enable                  : 1;    // bit 23
            /// SAI3 Peripheral Clocks Enable During CSleep Mode (SAI3LPEN)
            uint32_t sai3_low_power_enable                  : 1;    // bit 24
            /// (reserved)
            uint32_t                                        : 3;    // bits 25:27
            /// DFSDM1 Peripheral Clocks Enable During CSleep Mode (DFSDM1LPEN)
            uint32_t dfsdm1_low_power_enable                : 1;    // bit 28
            /// HRTIM peripheral clock enable during CSleep mode (HRTIMLPEN)
            uint32_t high_resolution_timer_low_power_enable : 1;    // bit 29
            /// (reserved)
            uint32_t                                        : 2;    // bits 30:31
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
    /// RCC APB2 Sleep Clock Register (C1_APB2LPENR)
    struct Processor1APB2LowPowerClockEnable final {
        /// Default Constructor
        Processor1APB2LowPowerClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Processor1APB2LowPowerClockEnable(Processor1APB2LowPowerClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Processor1APB2LowPowerClockEnable(Processor1APB2LowPowerClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Processor1APB2LowPowerClockEnable(Processor1APB2LowPowerClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Processor1APB2LowPowerClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Processor1APB2LowPowerClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Processor1APB2LowPowerClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TIM1 peripheral clock enable during CSleep mode (TIM1LPEN)
            uint32_t timer1_low_power_enable                : 1;    // bit 0
            /// TIM8 peripheral clock enable during CSleep mode (TIM8LPEN)
            uint32_t timer8_low_power_enable                : 1;    // bit 1
            /// (reserved)
            uint32_t                                        : 2;    // bits 2:3
            /// USART1 Peripheral Clocks Enable During CSleep Mode (USART1LPEN)
            uint32_t usart1_low_power_enable                : 1;    // bit 4
            /// USART6 Peripheral Clocks Enable During CSleep Mode (USART6LPEN)
            uint32_t usart6_low_power_enable                : 1;    // bit 5
            /// (reserved)
            uint32_t                                        : 6;    // bits 6:11
            /// SPI1 Peripheral Clocks Enable During CSleep Mode (SPI1LPEN)
            uint32_t spi1_low_power_enable                  : 1;    // bit 12
            /// SPI4 Peripheral Clocks Enable During CSleep Mode (SPI4LPEN)
            uint32_t spi4_low_power_enable                  : 1;    // bit 13
            /// (reserved)
            uint32_t                                        : 2;    // bits 14:15
            /// TIM15 peripheral clock enable during CSleep mode (TIM15LPEN)
            uint32_t timer15_low_power_enable               : 1;    // bit 16
            /// TIM16 peripheral clock enable during CSleep mode (TIM16LPEN)
            uint32_t timer16_low_power_enable               : 1;    // bit 17
            /// TIM17 peripheral clock enable during CSleep mode (TIM17LPEN)
            uint32_t timer17_low_power_enable               : 1;    // bit 18
            /// (reserved)
            uint32_t                                        : 1;    // bit 19
            /// SPI5 Peripheral Clocks Enable During CSleep Mode (SPI5LPEN)
            uint32_t spi5_low_power_enable                  : 1;    // bit 20
            /// (reserved)
            uint32_t                                        : 1;    // bit 21
            /// SAI1 Peripheral Clocks Enable During CSleep Mode (SAI1LPEN)
            uint32_t sai1_low_power_enable                  : 1;    // bit 22
            /// SAI2 Peripheral Clocks Enable During CSleep Mode (SAI2LPEN)
            uint32_t sai2_low_power_enable                  : 1;    // bit 23
            /// SAI3 Peripheral Clocks Enable During CSleep Mode (SAI3LPEN)
            uint32_t sai3_low_power_enable                  : 1;    // bit 24
            /// (reserved)
            uint32_t                                        : 3;    // bits 25:27
            /// DFSDM1 Peripheral Clocks Enable During CSleep Mode (DFSDM1LPEN)
            uint32_t dfsdm1_low_power_enable                : 1;    // bit 28
            /// HRTIM peripheral clock enable during CSleep mode (HRTIMLPEN)
            uint32_t high_resolution_timer_low_power_enable : 1;    // bit 29
            /// (reserved)
            uint32_t                                        : 2;    // bits 30:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Processor1APB2LowPowerClockEnable& operator=(Processor1APB2LowPowerClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Processor1APB2LowPowerClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Processor1APB2LowPowerClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Processor1APB2LowPowerClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Processor1APB2LowPowerClockEnable) == 4UL, "Must be this exact size");
    /// RCC APB4 Sleep Clock Register (C1_APB4LPENR)
    struct Processor1APB4LowPowerClockEnable final {
        /// Default Constructor
        Processor1APB4LowPowerClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Processor1APB4LowPowerClockEnable(Processor1APB4LowPowerClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Processor1APB4LowPowerClockEnable(Processor1APB4LowPowerClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Processor1APB4LowPowerClockEnable(Processor1APB4LowPowerClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Processor1APB4LowPowerClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Processor1APB4LowPowerClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Processor1APB4LowPowerClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                           : 1;    // bit 0
            /// SYSCFG peripheral clock enable during CSleep mode (SYSCFGLPEN)
            uint32_t syscfg_low_power_enable   : 1;    // bit 1
            /// (reserved)
            uint32_t                           : 1;    // bit 2
            /// LPUART1 Peripheral Clocks Enable During CSleep Mode (LPUART1LPEN)
            uint32_t lpuart1_low_power_enable  : 1;    // bit 3
            /// (reserved)
            uint32_t                           : 1;    // bit 4
            /// SPI6 Peripheral Clocks Enable During CSleep Mode (SPI6LPEN)
            uint32_t spi6_low_power_enable     : 1;    // bit 5
            /// (reserved)
            uint32_t                           : 1;    // bit 6
            /// I2C4 Peripheral Clocks Enable During CSleep Mode (I2C4LPEN)
            uint32_t i2c4_low_power_enable     : 1;    // bit 7
            /// (reserved)
            uint32_t                           : 1;    // bit 8
            /// LPTIM2 Peripheral Clocks Enable During CSleep Mode (LPTIM2LPEN)
            uint32_t lptimer2_low_power_enable : 1;    // bit 9
            /// LPTIM3 Peripheral Clocks Enable During CSleep Mode (LPTIM3LPEN)
            uint32_t lptimer3_low_power_enable : 1;    // bit 10
            /// LPTIM4 Peripheral Clocks Enable During CSleep Mode (LPTIM4LPEN)
            uint32_t lptimer4_low_power_enable : 1;    // bit 11
            /// LPTIM5 Peripheral Clocks Enable During CSleep Mode (LPTIM5LPEN)
            uint32_t lptimer5_low_power_enable : 1;    // bit 12
            /// (reserved)
            uint32_t                           : 1;    // bit 13
            /// COMP1/2 peripheral clock enable during CSleep mode (COMP12LPEN)
            uint32_t comp12_low_power_enable   : 1;    // bit 14
            /// VREF peripheral clock enable during CSleep mode (VREFLPEN)
            uint32_t vref_low_power_enable     : 1;    // bit 15
            /// RTC APB Clock Enable During CSleep Mode (RTCAPBLPEN)
            uint32_t rtc_apb_low_power_enable  : 1;    // bit 16
            /// (reserved)
            uint32_t                           : 4;    // bits 17:20
            /// SAI4 Peripheral Clocks Enable During CSleep Mode (SAI4LPEN)
            uint32_t sai4_low_power_enable     : 1;    // bit 21
            /// (reserved)
            uint32_t                           : 10;    // bits 22:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Processor1APB4LowPowerClockEnable& operator=(Processor1APB4LowPowerClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Processor1APB4LowPowerClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Processor1APB4LowPowerClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Processor1APB4LowPowerClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Processor1APB4LowPowerClockEnable) == 4UL, "Must be this exact size");
    /// RCC APB4 Sleep Clock Register (APB4LPENR)
    struct APB4LowPowerClockEnable final {
        /// Default Constructor
        APB4LowPowerClockEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        APB4LowPowerClockEnable(APB4LowPowerClockEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        APB4LowPowerClockEnable(APB4LowPowerClockEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        APB4LowPowerClockEnable(APB4LowPowerClockEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit APB4LowPowerClockEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit APB4LowPowerClockEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~APB4LowPowerClockEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                           : 1;    // bit 0
            /// SYSCFG peripheral clock enable during CSleep mode (SYSCFGLPEN)
            uint32_t syscfg_low_power_enable   : 1;    // bit 1
            /// (reserved)
            uint32_t                           : 1;    // bit 2
            /// LPUART1 Peripheral Clocks Enable During CSleep Mode (LPUART1LPEN)
            uint32_t lpuart1_low_power_enable  : 1;    // bit 3
            /// (reserved)
            uint32_t                           : 1;    // bit 4
            /// SPI6 Peripheral Clocks Enable During CSleep Mode (SPI6LPEN)
            uint32_t spi6_low_power_enable     : 1;    // bit 5
            /// (reserved)
            uint32_t                           : 1;    // bit 6
            /// I2C4 Peripheral Clocks Enable During CSleep Mode (I2C4LPEN)
            uint32_t i2c4_low_power_enable     : 1;    // bit 7
            /// (reserved)
            uint32_t                           : 1;    // bit 8
            /// LPTIM2 Peripheral Clocks Enable During CSleep Mode (LPTIM2LPEN)
            uint32_t lptimer2_low_power_enable : 1;    // bit 9
            /// LPTIM3 Peripheral Clocks Enable During CSleep Mode (LPTIM3LPEN)
            uint32_t lptimer3_low_power_enable : 1;    // bit 10
            /// LPTIM4 Peripheral Clocks Enable During CSleep Mode (LPTIM4LPEN)
            uint32_t lptimer4_low_power_enable : 1;    // bit 11
            /// LPTIM5 Peripheral Clocks Enable During CSleep Mode (LPTIM5LPEN)
            uint32_t lptimer5_low_power_enable : 1;    // bit 12
            /// (reserved)
            uint32_t                           : 1;    // bit 13
            /// COMP1/2 peripheral clock enable during CSleep mode (COMP12LPEN)
            uint32_t comp12_low_power_enable   : 1;    // bit 14
            /// VREF peripheral clock enable during CSleep mode (VREFLPEN)
            uint32_t vref_low_power_enable     : 1;    // bit 15
            /// RTC APB Clock Enable During CSleep Mode (RTCAPBLPEN)
            uint32_t rtc_apb_low_power_enable  : 1;    // bit 16
            /// (reserved)
            uint32_t                           : 4;    // bits 17:20
            /// SAI4 Peripheral Clocks Enable During CSleep Mode (SAI4LPEN)
            uint32_t sai4_low_power_enable     : 1;    // bit 21
            /// (reserved)
            uint32_t                           : 10;    // bits 22:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        APB4LowPowerClockEnable& operator=(APB4LowPowerClockEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(APB4LowPowerClockEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(APB4LowPowerClockEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<APB4LowPowerClockEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(APB4LowPowerClockEnable) == 4UL, "Must be this exact size");

    //+=MEMORY======================================+
    /// clock control register (CR)
    Control control;                                                    // offset 0x0UL
#if defined(STM32H7_REV_Y)
    InternalClockSourcesCalibration internalclocksourcescalibration;    // offset 0x4UL
#elif defined(STM32H7_REV_V)
    HighSpeedInternalConfiguration highspeedinternalconfiguration;    // offset 0x4UL
#endif
    /// RCC Clock Recovery RC Register (CRRCR)
    ClockRecoveryCalibrationControl clock_recovery_calibration_control;    // offset 0x8UL
    uint32_t : 32;                                                         // offset 0xcUL
    /// RCC Clock Configuration Register (CFGR)
    Configuration configuration;    // offset 0x10UL
    uint32_t : 32;                  // offset 0x14UL
    /// RCC Domain 1 Clock Configuration Register (D1CFGR)
    Domain1ClockConfiguration domain1_clock_configuration;    // offset 0x18UL
    /// RCC Domain 2 Clock Configuration Register (D2CFGR)
    Domain2ClockConfiguration domain2_clock_configuration;    // offset 0x1cUL
    /// RCC Domain 3 Clock Configuration Register (D3CFGR)
    Domain3ClockConfiguration domain3_clock_configuration;    // offset 0x20UL
    uint32_t : 32;                                            // offset 0x24UL
    /// RCC PLLs Clock Source Selection Register (PLLCKSELR)
    PllClockSourceSelection pll_clock_source_selection;    // offset 0x28UL
    /// RCC PLLs Configuration Register (PLLCFGR)
    PhaseLockLoopConfiguration pll_configuration;    // offset 0x2cUL
    /// RCC PLL1 Dividers Configuration Register (PLL1DIVR)
    Pll1DividerConfiguration pll1_divider_configuration;    // offset 0x30UL
    /// RCC PLL1 Fractional Divider Register (PLL1FRACR)
    Pll1FractionalConfiguration pll1_fractional_configuration;    // offset 0x34UL
    /// RCC PLL2 Dividers Configuration Register (PLL2DIVR)
    Pll2DividerConfiguration pll2_divider_configuration;    // offset 0x38UL
    /// RCC PLL2 Fractional Divider Register (PLL2FRACR)
    Pll2FractionalConfiguration pll2_fractional_configuration;    // offset 0x3cUL
    /// RCC PLL3 Dividers Configuration Register (PLL3DIVR)
    Pll3DividerConfiguration pll3_divider_configuration;    // offset 0x40UL
    /// RCC PLL3 Fractional Divider Register (PLL3FRACR)
    Pll3FractionalConfiguration pll3_fractional_configuration;    // offset 0x44UL
    uint32_t : 32;                                                // offset 0x48UL
    /// RCC Domain 1 Kernel Clock Configuration Register (D1CCIPR)
    Domain1PeripheralClockSelection domain1_peripheral_clock_selection;    // offset 0x4cUL
    /// RCC Domain 2 Kernel Clock Configuration Register (D2CCIP1R)
    Domain2PeripheralClockSelection1 domain2_peripheral_clock_selection1;    // offset 0x50UL
    /// RCC Domain 2 Kernel Clock Configuration Register (D2CCIP2R)
    Domain2PeripheralClockSelection2 domain2_peripheral_clock_selection2;    // offset 0x54UL
    /// RCC Domain 3 Kernel Clock Configuration Register (D3CCIPR)
    Domain3PeripheralClockSelection domain3_peripheral_clock_selection;    // offset 0x58UL
    uint32_t : 32;                                                         // offset 0x5cUL
    /// RCC Clock Source Interrupt Enable Register (CIER)
    ClockInterruptEnable clockinterruptenable;    // offset 0x60UL
    /// RCC Clock Source Interrupt Flag Register (CIFR)
    ClockInterruptFlags clockinterruptflags;    // offset 0x64UL
    /// RCC Clock Source Interrupt Clear Register (CICR)
    ClockInterruptClear clockinterruptclear;    // offset 0x68UL
    uint32_t : 32;                              // offset 0x6cUL
    /// RCC Backup Domain Control Register (BDCR)
    BackupDomainControl backup_domain_control;    // offset 0x70UL
    /// RCC Clock Control and Status Register (CSR)
    ClockControlStatus clock_control_status;    // offset 0x74UL
    uint32_t : 32;                              // offset 0x78UL
    /// RCC AHB3 Reset Register (AHB3RSTR)
    AHB3PeripheralReset ahb3_peripheral_reset;    // offset 0x7cUL
    /// RCC AHB1 Peripheral Reset Register (AHB1RSTR)
    AHB1PeripheralReset ahb1_peripheral_reset;    // offset 0x80UL
    /// RCC AHB2 Peripheral Reset Register (AHB2RSTR)
    AHB2PeripheralReset ahb2_peripheral_reset;    // offset 0x84UL
    /// RCC AHB4 Peripheral Reset Register (AHB4RSTR)
    AHB4Reset ahb4_reset;    // offset 0x88UL
    /// RCC APB3 Peripheral Reset Register (APB3RSTR)
    APB3Reset apb3_reset;    // offset 0x8cUL
    /// RCC APB1 Peripheral Reset Register (APB1LRSTR)
    APB1LowReset apb1_low_reset;    // offset 0x90UL
    /// RCC APB1 Peripheral Reset Register (APB1HRSTR)
    APB1HighReset apb1_high_reset;    // offset 0x94UL
    /// RCC APB2 Peripheral Reset Register (APB2RSTR)
    APB2PeripheralReset apb2_peripheral_reset;    // offset 0x98UL
    /// RCC APB4 Peripheral Reset Register (APB4RSTR)
    APB4Reset apb4_reset;    // offset 0x9cUL
    /// RCC Global Control Register (GCR)
    GlobalControl globalcontrol;    // offset 0xa0UL
    uint32_t : 32;                  // offset 0xa4UL
    /// RCC D3 Autonomous mode Register (D3AMR)
    Domain3AutonomousMode domain3_autonomous_mode;    // offset 0xa8UL
    uint32_t : 32;                                    // offset 0xacUL
    uint32_t : 32;                                    // offset 0xb0UL
    uint32_t : 32;                                    // offset 0xb4UL
    uint32_t : 32;                                    // offset 0xb8UL
    uint32_t : 32;                                    // offset 0xbcUL
    uint32_t : 32;                                    // offset 0xc0UL
    uint32_t : 32;                                    // offset 0xc4UL
    uint32_t : 32;                                    // offset 0xc8UL
    uint32_t : 32;                                    // offset 0xccUL
    /// RCC Reset Status Register (RSR)
    ResetStatus reset_status;    // offset 0xd0UL
    /// RCC AHB3 Clock Register (AHB3ENR)
    AHB3PeripheralClockEnable ahb3_peripheral_clock_enable;    // offset 0xd4UL
    /// RCC AHB1 Clock Register (AHB1ENR)
    AHB1PeripheralClockEnable ahb1_peripheral_clock_enable;    // offset 0xd8UL
    /// RCC AHB2 Clock Register (AHB2ENR)
    AHB2PeripheralClockEnable ahb2_peripheral_clock_enable;    // offset 0xdcUL
    /// RCC AHB4 Clock Register (AHB4ENR)
    AHB4ClockEnable ahb4_clock_enable;    // offset 0xe0UL
    /// RCC APB3 Clock Register (APB3ENR)
    APB3ClockEnable apb3_clock_enable;    // offset 0xe4UL
    /// RCC APB1 Clock Register (APB1LENR)
    APB1LowClockEnable apb1_low_clock_enable;    // offset 0xe8UL
    /// RCC APB1 Clock Register (APB1HENR)
    APB1HighClockEnable apb1_high_clock_enable;    // offset 0xecUL
    /// RCC APB2 Clock Register (APB2ENR)
    APB2PeripheralClockEnable apb2_peripheral_clock_enable;    // offset 0xf0UL
    /// RCC APB4 Clock Register (APB4ENR)
    APB4ClockEnable apb4_clock_enable;    // offset 0xf4UL
    uint32_t : 32;                        // offset 0xf8UL
    /// RCC AHB3 Sleep Clock Register (AHB3LPENR)
    AHB3PeripheralLowPowerEnable ahb3_peripheral_low_power_enable;    // offset 0xfcUL
    /// RCC AHB1 Sleep Clock Register (AHB1LPENR)
    AHB1PeripheralLowPowerEnable ahb1_peripheral_low_power_enable;    // offset 0x100UL
    /// RCC AHB2 Sleep Clock Register (AHB2LPENR)
    AHB2PeripheralLowPowerEnable ahb2_peripheral_low_power_enable;    // offset 0x104UL
    /// RCC AHB4 Sleep Clock Register (AHB4LPENR)
    AHB4LowPowerClockEnable ahb4_low_power_clock_enable;    // offset 0x108UL
    /// RCC APB3 Sleep Clock Register (APB3LPENR)
    APB3LowPowerClockEnable apb3_low_power_clock_enable;    // offset 0x10cUL
    /// RCC APB1 Low Sleep Clock Register (APB1LLPENR)
    APB1LowLowPowerClockEnable apb1_low_low_power_clock_enable;    // offset 0x110UL
    /// RCC APB1 High Sleep Clock Register (APB1HLPENR)
    APB1HighLowPowerClockEnable apb1_high_low_power_clock_enable;    // offset 0x114UL
    /// RCC APB2 Sleep Clock Register (APB2LPENR)
    APB2PeripheralLowPowerEnable apb2_peripheral_low_power_enable;    // offset 0x118UL
    /// RCC APB4 Sleep Clock Register (APB4LPENR)
    APB4LowPowerClockEnable apb4_low_power_clock_enable;    // offset 0x11cUL
    uint32_t : 32;                                          // offset 0x120UL
    uint32_t : 32;                                          // offset 0x124UL
    uint32_t : 32;                                          // offset 0x128UL
    uint32_t : 32;                                          // offset 0x12cUL
    /// RCC Reset Status Register (C1_RSR)
    Processor1ResetStatus processor1_reset_status;    // offset 0x130UL
    /// RCC AHB3 Clock Register (C1_AHB3ENR)
    Processor1AHB3ClockEnable processor1_ahb3_clock_enable;    // offset 0x134UL
    /// RCC AHB1 Clock Register (C1_AHB1ENR)
    Processor1AHB1ClockEnable processor1_ahb1_clock_enable;    // offset 0x138UL
    /// RCC AHB2 Clock Register (C1_AHB2ENR)
    Processor1AHB2ClockEnable processor1_ahb2_clock_enable;    // offset 0x13cUL
    /// RCC AHB4 Clock Register (C1_AHB4ENR)
    Processor1AHB4ClockEnable processor1_ahb4_clock_enable;    // offset 0x140UL
    /// RCC APB3 Clock Register (C1_APB3ENR)
    Processor1APB3ClockEnable processor1_apb3_clock_enable;    // offset 0x144UL
    /// RCC APB1 Clock Register (C1_APB1LENR)
    Processor1APB1LowClockEnable processor1_apb1_low_clock_enable;    // offset 0x148UL
    /// RCC APB1 Clock Register (C1_APB1HENR)
    Processor1APB1HighClockEnable processor1_apb1_high_clock_enable;    // offset 0x14cUL
    /// RCC APB2 Clock Register (C1_APB2ENR)
    Processor1APB2ClockEnable processor1_apb2_clock_enable;    // offset 0x150UL
    /// RCC APB4 Clock Register (C1_APB4ENR)
    Processor1APB4ClockEnable processor1_apb4_clock_enable;    // offset 0x154UL
    uint32_t : 32;                                             // offset 0x158UL
    /// RCC AHB3 Sleep Clock Register (C1_AHB3LPENR)
    Processor1AHB3LowPowerClockEnable processor1_ahb3_low_power_clock_enable;    // offset 0x15cUL
    /// RCC AHB1 Sleep Clock Register (C1_AHB1LPENR)
    Processor1AHB1LowPowerClockEnable processor1_ahb1_low_power_clock_enable;    // offset 0x160UL
    /// RCC AHB2 Sleep Clock Register (C1_AHB2LPENR)
    Processor1AHB2LowPowerClockEnable processor1_ahb2_low_power_clock_enable;    // offset 0x164UL
    /// RCC AHB4 Sleep Clock Register (C1_AHB4LPENR)
    Processor1AHB4LowPowerClockEnable processor1_ahb4_low_power_clock_enable;    // offset 0x168UL
    /// RCC APB3 Sleep Clock Register (C1_APB3LPENR)
    Processor1APB3LowPowerClockEnable processor1_apb3_low_power_clock_enable;    // offset 0x16cUL
    /// RCC APB1 Low Sleep Clock Register (C1_APB1LLPENR)
    Processor1APB1LowLowPowerClockEnable processor1_apb1_low_low_power_clock_enable;    // offset 0x170UL
    /// RCC APB1 High Sleep Clock Register (C1_APB1HLPENR)
    Processor1APB1HighLowPowerClockEnable processor1_apb1_high_low_power_clock_enable;    // offset 0x174UL
    /// RCC APB2 Sleep Clock Register (C1_APB2LPENR)
    Processor1APB2LowPowerClockEnable processor1_apb2_low_power_clock_enable;    // offset 0x178UL
    /// RCC APB4 Sleep Clock Register (C1_APB4LPENR)
    Processor1APB4LowPowerClockEnable processor1_apb4_low_power_clock_enable;    // offset 0x17cUL
    uint32_t : 32;                                                               // offset 0x180UL
    uint32_t : 32;                                                               // offset 0x184UL
    uint32_t : 32;                                                               // offset 0x188UL
    uint32_t : 32;                                                               // offset 0x18cUL
    uint32_t : 32;                                                               // offset 0x190UL
    uint32_t : 32;                                                               // offset 0x194UL
    uint32_t : 32;                                                               // offset 0x198UL
    uint32_t : 32;                                                               // offset 0x19cUL
    uint32_t : 32;                                                               // offset 0x1a0UL
    uint32_t : 32;                                                               // offset 0x1a4UL
    uint32_t : 32;                                                               // offset 0x1a8UL
    uint32_t : 32;                                                               // offset 0x1acUL
    uint32_t : 32;                                                               // offset 0x1b0UL
    uint32_t : 32;                                                               // offset 0x1b4UL
    uint32_t : 32;                                                               // offset 0x1b8UL
    uint32_t : 32;                                                               // offset 0x1bcUL
    uint32_t : 32;                                                               // offset 0x1c0UL
    uint32_t : 32;                                                               // offset 0x1c4UL
    uint32_t : 32;                                                               // offset 0x1c8UL
    uint32_t : 32;                                                               // offset 0x1ccUL
    uint32_t : 32;                                                               // offset 0x1d0UL
    uint32_t : 32;                                                               // offset 0x1d4UL
    uint32_t : 32;                                                               // offset 0x1d8UL
    uint32_t : 32;                                                               // offset 0x1dcUL
    uint32_t : 32;                                                               // offset 0x1e0UL
    uint32_t : 32;                                                               // offset 0x1e4UL
    uint32_t : 32;                                                               // offset 0x1e8UL
    uint32_t : 32;                                                               // offset 0x1ecUL
    uint32_t : 32;                                                               // offset 0x1f0UL
    uint32_t : 32;                                                               // offset 0x1f4UL
    uint32_t : 32;                                                               // offset 0x1f8UL
    uint32_t : 32;                                                               // offset 0x1fcUL
    uint32_t : 32;                                                               // offset 0x200UL
    uint32_t : 32;                                                               // offset 0x204UL
    uint32_t : 32;                                                               // offset 0x208UL
    uint32_t : 32;                                                               // offset 0x20cUL
    uint32_t : 32;                                                               // offset 0x210UL
    uint32_t : 32;                                                               // offset 0x214UL
    uint32_t : 32;                                                               // offset 0x218UL
    uint32_t : 32;                                                               // offset 0x21cUL
    uint32_t : 32;                                                               // offset 0x220UL
    uint32_t : 32;                                                               // offset 0x224UL
    uint32_t : 32;                                                               // offset 0x228UL
    uint32_t : 32;                                                               // offset 0x22cUL
    uint32_t : 32;                                                               // offset 0x230UL
    uint32_t : 32;                                                               // offset 0x234UL
    uint32_t : 32;                                                               // offset 0x238UL
    uint32_t : 32;                                                               // offset 0x23cUL
    uint32_t : 32;                                                               // offset 0x240UL
    uint32_t : 32;                                                               // offset 0x244UL
    uint32_t : 32;                                                               // offset 0x248UL
    uint32_t : 32;                                                               // offset 0x24cUL
    uint32_t : 32;                                                               // offset 0x250UL
    uint32_t : 32;                                                               // offset 0x254UL
    uint32_t : 32;                                                               // offset 0x258UL
    uint32_t : 32;                                                               // offset 0x25cUL
    uint32_t : 32;                                                               // offset 0x260UL
    uint32_t : 32;                                                               // offset 0x264UL
    uint32_t : 32;                                                               // offset 0x268UL
    uint32_t : 32;                                                               // offset 0x26cUL
    uint32_t : 32;                                                               // offset 0x270UL
    uint32_t : 32;                                                               // offset 0x274UL
    uint32_t : 32;                                                               // offset 0x278UL
    uint32_t : 32;                                                               // offset 0x27cUL
    uint32_t : 32;                                                               // offset 0x280UL
    uint32_t : 32;                                                               // offset 0x284UL
    uint32_t : 32;                                                               // offset 0x288UL
    uint32_t : 32;                                                               // offset 0x28cUL
    uint32_t : 32;                                                               // offset 0x290UL
    uint32_t : 32;                                                               // offset 0x294UL
    uint32_t : 32;                                                               // offset 0x298UL
    uint32_t : 32;                                                               // offset 0x29cUL
    uint32_t : 32;                                                               // offset 0x2a0UL
    uint32_t : 32;                                                               // offset 0x2a4UL
    uint32_t : 32;                                                               // offset 0x2a8UL
    uint32_t : 32;                                                               // offset 0x2acUL
    uint32_t : 32;                                                               // offset 0x2b0UL
    uint32_t : 32;                                                               // offset 0x2b4UL
    uint32_t : 32;                                                               // offset 0x2b8UL
    uint32_t : 32;                                                               // offset 0x2bcUL
    uint32_t : 32;                                                               // offset 0x2c0UL
    uint32_t : 32;                                                               // offset 0x2c4UL
    uint32_t : 32;                                                               // offset 0x2c8UL
    uint32_t : 32;                                                               // offset 0x2ccUL
    uint32_t : 32;                                                               // offset 0x2d0UL
    uint32_t : 32;                                                               // offset 0x2d4UL
    uint32_t : 32;                                                               // offset 0x2d8UL
    uint32_t : 32;                                                               // offset 0x2dcUL
    uint32_t : 32;                                                               // offset 0x2e0UL
    uint32_t : 32;                                                               // offset 0x2e4UL
    uint32_t : 32;                                                               // offset 0x2e8UL
    uint32_t : 32;                                                               // offset 0x2ecUL
    uint32_t : 32;                                                               // offset 0x2f0UL
    uint32_t : 32;                                                               // offset 0x2f4UL
    uint32_t : 32;                                                               // offset 0x2f8UL
    uint32_t : 32;                                                               // offset 0x2fcUL
    uint32_t : 32;                                                               // offset 0x300UL
    uint32_t : 32;                                                               // offset 0x304UL
    uint32_t : 32;                                                               // offset 0x308UL
    uint32_t : 32;                                                               // offset 0x30cUL
    uint32_t : 32;                                                               // offset 0x310UL
    uint32_t : 32;                                                               // offset 0x314UL
    uint32_t : 32;                                                               // offset 0x318UL
    uint32_t : 32;                                                               // offset 0x31cUL
    uint32_t : 32;                                                               // offset 0x320UL
    uint32_t : 32;                                                               // offset 0x324UL
    uint32_t : 32;                                                               // offset 0x328UL
    uint32_t : 32;                                                               // offset 0x32cUL
    uint32_t : 32;                                                               // offset 0x330UL
    uint32_t : 32;                                                               // offset 0x334UL
    uint32_t : 32;                                                               // offset 0x338UL
    uint32_t : 32;                                                               // offset 0x33cUL
    uint32_t : 32;                                                               // offset 0x340UL
    uint32_t : 32;                                                               // offset 0x344UL
    uint32_t : 32;                                                               // offset 0x348UL
    uint32_t : 32;                                                               // offset 0x34cUL
    uint32_t : 32;                                                               // offset 0x350UL
    uint32_t : 32;                                                               // offset 0x354UL
    uint32_t : 32;                                                               // offset 0x358UL
    uint32_t : 32;                                                               // offset 0x35cUL
    uint32_t : 32;                                                               // offset 0x360UL
    uint32_t : 32;                                                               // offset 0x364UL
    uint32_t : 32;                                                               // offset 0x368UL
    uint32_t : 32;                                                               // offset 0x36cUL
    uint32_t : 32;                                                               // offset 0x370UL
    uint32_t : 32;                                                               // offset 0x374UL
    uint32_t : 32;                                                               // offset 0x378UL
    uint32_t : 32;                                                               // offset 0x37cUL
    uint32_t : 32;                                                               // offset 0x380UL
    uint32_t : 32;                                                               // offset 0x384UL
    uint32_t : 32;                                                               // offset 0x388UL
    uint32_t : 32;                                                               // offset 0x38cUL
    uint32_t : 32;                                                               // offset 0x390UL
    uint32_t : 32;                                                               // offset 0x394UL
    uint32_t : 32;                                                               // offset 0x398UL
    uint32_t : 32;                                                               // offset 0x39cUL
    uint32_t : 32;                                                               // offset 0x3a0UL
    uint32_t : 32;                                                               // offset 0x3a4UL
    uint32_t : 32;                                                               // offset 0x3a8UL
    uint32_t : 32;                                                               // offset 0x3acUL
    uint32_t : 32;                                                               // offset 0x3b0UL
    uint32_t : 32;                                                               // offset 0x3b4UL
    uint32_t : 32;                                                               // offset 0x3b8UL
    uint32_t : 32;                                                               // offset 0x3bcUL
    uint32_t : 32;                                                               // offset 0x3c0UL
    uint32_t : 32;                                                               // offset 0x3c4UL
    uint32_t : 32;                                                               // offset 0x3c8UL
    uint32_t : 32;                                                               // offset 0x3ccUL
    uint32_t : 32;                                                               // offset 0x3d0UL
    uint32_t : 32;                                                               // offset 0x3d4UL
    uint32_t : 32;                                                               // offset 0x3d8UL
    uint32_t : 32;                                                               // offset 0x3dcUL
    uint32_t : 32;                                                               // offset 0x3e0UL
    uint32_t : 32;                                                               // offset 0x3e4UL
    uint32_t : 32;                                                               // offset 0x3e8UL
    uint32_t : 32;                                                               // offset 0x3ecUL
    uint32_t : 32;                                                               // offset 0x3f0UL
    uint32_t : 32;                                                               // offset 0x3f4UL
    uint32_t : 32;                                                               // offset 0x3f8UL
    uint32_t : 32;                                                               // offset 0x3fcUL
    //+=MEMORY======================================+
};
// Ensure the structure is in standard layout format
static_assert(std::is_standard_layout<ResetAndClockControl>::value, "Must be standard layout");
// Ensure the offsets are all correct
static_assert(offsetof(ResetAndClockControl, control) == 0x0UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, clock_recovery_calibration_control) == 0x8UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, configuration) == 0x10UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, domain1_clock_configuration) == 0x18UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, domain2_clock_configuration) == 0x1cUL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, domain3_clock_configuration) == 0x20UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, pll_clock_source_selection) == 0x28UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, pll_configuration) == 0x2cUL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, pll1_divider_configuration) == 0x30UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, pll1_fractional_configuration) == 0x34UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, pll2_divider_configuration) == 0x38UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, pll2_fractional_configuration) == 0x3cUL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, pll3_divider_configuration) == 0x40UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, pll3_fractional_configuration) == 0x44UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, domain1_peripheral_clock_selection) == 0x4cUL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, domain2_peripheral_clock_selection1) == 0x50UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, domain2_peripheral_clock_selection2) == 0x54UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, domain3_peripheral_clock_selection) == 0x58UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, clockinterruptenable) == 0x60UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, clockinterruptflags) == 0x64UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, clockinterruptclear) == 0x68UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, backup_domain_control) == 0x70UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, clock_control_status) == 0x74UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, ahb3_peripheral_reset) == 0x7cUL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, ahb1_peripheral_reset) == 0x80UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, ahb2_peripheral_reset) == 0x84UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, ahb4_reset) == 0x88UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, apb3_reset) == 0x8cUL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, apb1_low_reset) == 0x90UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, apb1_high_reset) == 0x94UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, apb2_peripheral_reset) == 0x98UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, apb4_reset) == 0x9cUL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, globalcontrol) == 0xa0UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, domain3_autonomous_mode) == 0xa8UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, reset_status) == 0xd0UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, ahb3_peripheral_clock_enable) == 0xd4UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, ahb1_peripheral_clock_enable) == 0xd8UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, ahb2_peripheral_clock_enable) == 0xdcUL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, ahb4_clock_enable) == 0xe0UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, apb3_clock_enable) == 0xe4UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, apb1_low_clock_enable) == 0xe8UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, apb1_high_clock_enable) == 0xecUL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, apb2_peripheral_clock_enable) == 0xf0UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, apb4_clock_enable) == 0xf4UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, ahb3_peripheral_low_power_enable) == 0xfcUL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, ahb1_peripheral_low_power_enable) == 0x100UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, ahb2_peripheral_low_power_enable) == 0x104UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, ahb4_low_power_clock_enable) == 0x108UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, apb3_low_power_clock_enable) == 0x10cUL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, apb1_low_low_power_clock_enable) == 0x110UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, apb1_high_low_power_clock_enable) == 0x114UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, apb2_peripheral_low_power_enable) == 0x118UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, apb4_low_power_clock_enable) == 0x11cUL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, processor1_reset_status) == 0x130UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, processor1_ahb3_clock_enable) == 0x134UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, processor1_ahb1_clock_enable) == 0x138UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, processor1_ahb2_clock_enable) == 0x13cUL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, processor1_ahb4_clock_enable) == 0x140UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, processor1_apb3_clock_enable) == 0x144UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, processor1_apb1_low_clock_enable) == 0x148UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, processor1_apb1_high_clock_enable) == 0x14cUL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, processor1_apb2_clock_enable) == 0x150UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, processor1_apb4_clock_enable) == 0x154UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, processor1_ahb3_low_power_clock_enable) == 0x15cUL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, processor1_ahb1_low_power_clock_enable) == 0x160UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, processor1_ahb2_low_power_clock_enable) == 0x164UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, processor1_ahb4_low_power_clock_enable) == 0x168UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, processor1_apb3_low_power_clock_enable) == 0x16cUL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, processor1_apb1_low_low_power_clock_enable) == 0x170UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, processor1_apb1_high_low_power_clock_enable) == 0x174UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, processor1_apb2_low_power_clock_enable) == 0x178UL, "Must be located at this offset");
static_assert(offsetof(ResetAndClockControl, processor1_apb4_low_power_clock_enable) == 0x17cUL, "Must be located at this offset");

// Ensure the sizeof the entire structure is correct.
static_assert(sizeof(ResetAndClockControl) == 0x400UL, "Must be this exact size");

/// The external volatile reset_and_clock_control which is a memory mapped register or peripheral.
/// @note The address of the peripheral is set either by the linkerscript or by a unit test.
extern ResetAndClockControl volatile reset_and_clock_control;
}    // namespace h7xx
}    // namespace stm32
#endif    // STM32_H7XX_RESETANDCLOCKCONTROL__HPP_

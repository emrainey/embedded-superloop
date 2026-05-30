
#ifndef STM32_H7XX_POWERCONTROLLER__HPP_
#define STM32_H7XX_POWERCONTROLLER__HPP_

/// @file
/// Auto Generated Structure Definitions for PowerController from the Peripheralyzer.
/// @copyright

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace stm32 {
namespace h7xx {

/// PWR (PWR)
struct PowerController final {
    /// PWR control register 1 (CR1)
    struct Control1 final {
        /// Default Constructor
        Control1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Control1(Control1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Control1(Control1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Control1(Control1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Control1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Control1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Control1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Low-power Deepsleep with SVOS3 (SVOS4 and SVOS5 always use low-power, regardless of the setting of this bit) (LPDS)
            uint32_t low_power_deep_sleep                    : 1;    // bit 0
            /// (reserved)
            uint32_t                                         : 3;    // bits 1:3
            /// Programmable voltage detector enable (PVDE)
            uint32_t power_voltage_detector_enable           : 1;    // bit 4
            /// Programmable voltage detector level selection These bits select the voltage threshold detected by the PVD. Note: Refer to Section
            /// Electrical characteristics of the product datasheet for more details. (PLS)
            uint32_t pvd_level_select                        : 3;    // bits 5:7
            /// Disable backup domain write protection In reset state, the RCC_BDCR register, the RTC registers (including the backup registers), BREN
            /// and MOEN bits in PWR_CR2 register, are protected against parasitic write access. This bit must be set to enable write access to these
            /// registers. (DBP)
            uint32_t disable_backup_write_protection         : 1;    // bit 8
            /// Flash low-power mode in DStop mode This bit allows to obtain the best trade-off between low-power consumption and restart time when
            /// exiting from DStop mode. When it is set, the Flash memory enters low-power mode when D1 domain is in DStop mode. (FLPS)
            uint32_t flash_low_power_selection               : 1;    // bit 9
            /// (reserved)
            uint32_t                                         : 4;    // bits 10:13
            /// System Stop mode voltage scaling selection These bits control the VCORE voltage level in system Stop mode, to obtain the best
            /// trade-off between power consumption and performance. (SVOS)
            uint32_t system_voltage_scaling_selection        : 2;    // bits 14:15
            /// Peripheral voltage monitor on VDDA enable (AVDEN)
            uint32_t analog_voltage_detector_enable          : 1;    // bit 16
            /// Analog voltage detector level selection These bits select the voltage threshold detected by the AVD. (ALS)
            uint32_t analog_voltage_detector_level_selection : 2;    // bits 17:18
            /// (reserved)
            uint32_t                                         : 13;    // bits 19:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Control1& operator=(Control1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Control1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Control1 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Control1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Control1) == 4UL, "Must be this exact size");
    /// PWR control status register 1 (CSR1)
    struct ContextSwap1 final {
        /// Default Constructor
        ContextSwap1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ContextSwap1(ContextSwap1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ContextSwap1(ContextSwap1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ContextSwap1(ContextSwap1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ContextSwap1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ContextSwap1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ContextSwap1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                                : 4;    // bits 0:3
            /// Programmable voltage detect output This bit is set and cleared by hardware. It is valid only if the PVD has been enabled by the PVDE
            /// bit. Note: since the PVD is disabled in Standby mode, this bit is equal to 0 after Standby or reset until the PVDE bit is set. (PVDO)
            uint32_t power_voltage_detector_output  : 1;    // bit 4
            /// (reserved)
            uint32_t                                : 8;    // bits 5:12
            /// Voltage levels ready bit for currently used VOS and SDLEVEL This bit is set to 1 by hardware when the voltage regulator and the SD
            /// converter are both disabled and Bypass mode is selected in PWR control register 3 (PWR_CR3). (ACTVOSRDY)
            uint32_t active_voltage_scaling_ready   : 1;    // bit 13
            /// VOS currently applied for VCORE voltage scaling selection. These bits reflect the last VOS value applied to the PMU. (ACTVOS)
            uint32_t active_voltage_scaling         : 2;    // bits 14:15
            /// Analog voltage detector output on VDDA This bit is set and cleared by hardware. It is valid only if AVD on VDDA is enabled by the
            /// AVDEN bit. Note: Since the AVD is disabled in Standby mode, this bit is equal to 0 after Standby or reset until the AVDEN bit is set.
            /// (AVDO)
            uint32_t analog_voltage_detector_output : 1;    // bit 16
            /// (reserved)
            uint32_t                                : 15;    // bits 17:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ContextSwap1& operator=(ContextSwap1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ContextSwap1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ContextSwap1 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ContextSwap1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ContextSwap1) == 4UL, "Must be this exact size");
    /// This register is not reset by wakeup from Standby mode, RESET signal and VDD POR. It is only reset by VSW POR and VSWRST reset. This register
    /// shall not be accessed when VSWRST bit in RCC_BDCR register resets the VSW domain.After reset, PWR_CR2 register is write-protected. Prior to
    /// modifying its content, the DBP bit in PWR_CR1 register must be set to disable the write protection. (CR2)
    struct Control2 final {
        /// Default Constructor
        Control2()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Control2(Control2 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Control2(Control2 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Control2(Control2&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Control2(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Control2(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Control2() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Backup regulator enable When set, the Backup regulator (used to maintain the backup RAM content in Standby and VBAT modes) is enabled.
            /// If BREN is reset, the backup regulator is switched off. The backup RAM can still be used in Run and Stop modes. However, its content
            /// will be lost in Standby and VBAT modes. If BREN is set, the application must wait till the Backup Regulator Ready flag (BRRDY) is set
            /// to indicate that the data written into the SRAM will be maintained in Standby and VBAT modes. (BREN)
            uint32_t backup_regulator_enable    : 1;    // bit 0
            /// (reserved)
            uint32_t                            : 3;    // bits 1:3
            /// VBAT and temperature monitoring enable When set, the VBAT supply and temperature monitoring is enabled. (MONEN)
            uint32_t monitoring_enable          : 1;    // bit 4
            /// (reserved)
            uint32_t                            : 11;    // bits 5:15
            /// Backup regulator ready This bit is set by hardware to indicate that the Backup regulator is ready. (BRRDY)
            uint32_t backup_regulator_ready     : 1;    // bit 16
            /// (reserved)
            uint32_t                            : 3;    // bits 17:19
            /// VBAT level monitoring versus low threshold (VBATL)
            uint32_t vbat_low_threshold         : 1;    // bit 20
            /// VBAT level monitoring versus high threshold (VBATH)
            uint32_t vbat_high_threshold        : 1;    // bit 21
            /// Temperature level monitoring versus low threshold (TEMPL)
            uint32_t temperature_low_threshold  : 1;    // bit 22
            /// Temperature level monitoring versus high threshold (TEMPH)
            uint32_t temperature_high_threshold : 1;    // bit 23
            /// (reserved)
            uint32_t                            : 8;    // bits 24:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Control2& operator=(Control2&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Control2 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Control2 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Control2>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Control2) == 4UL, "Must be this exact size");
    /// Reset only by POR only, not reset by wakeup from Standby mode and RESET pad. The lower byte of this register is written once after POR and
    /// shall be written before changing VOS level or ck_sys clock frequency. No limitation applies to the upper bytes.Programming data corresponding
    /// to an invalid combination of SDLEVEL, SDEXTHP, SDEN, LDOEN and BYPASS bits (see Table9) will be ignored: data will not be written, the
    /// written-once mechanism will lock the register and any further write access will be ignored. The default supply configuration will be kept and
    /// the ACTVOSRDY bit in PWR control status register 1 (PWR_CSR1) will go on indicating invalid voltage levels. The system shall be power cycled
    /// before writing a new value. (CR3)
    struct Control3 final {
        /// Default Constructor
        Control3()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Control3(Control3 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Control3(Control3 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Control3(Control3&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Control3(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Control3(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Control3() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Power management unit bypass (BYPASS)
            uint32_t supply_bypass_mode                 : 1;    // bit 0
            /// Low drop-out regulator enable (LDOEN)
            uint32_t low_dropout_regulator_enable       : 1;    // bit 1
            /// SD converter Enable (SCUEN)
            uint32_t supply_configuration_update_enable : 1;    // bit 2
            /// (reserved)
            uint32_t                                    : 5;    // bits 3:7
            /// VBAT charging enable (VBE)
            uint32_t vbat_charging_enable               : 1;    // bit 8
            /// VBAT charging resistor selection (VBRS)
            uint32_t vbat_charging_resistor_selection   : 1;    // bit 9
            /// (reserved)
            uint32_t                                    : 14;    // bits 10:23
            /// VDD33USB voltage level detector enable. (USB33DEN)
            uint32_t usb33_detector_enable              : 1;    // bit 24
            /// USB regulator enable. (USBREGEN)
            uint32_t usb_regulator_enable               : 1;    // bit 25
            /// USB supply ready. (USB33RDY)
            uint32_t usb33_ready                        : 1;    // bit 26
            /// (reserved)
            uint32_t                                    : 5;    // bits 27:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Control3& operator=(Control3&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Control3 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Control3 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Control3>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Control3) == 4UL, "Must be this exact size");
    /// This register allows controlling CPU1 power. (CPUCR)
    struct ProcessorControl final {
        /// Default Constructor
        ProcessorControl()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ProcessorControl(ProcessorControl volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ProcessorControl(ProcessorControl const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ProcessorControl(ProcessorControl&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ProcessorControl(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ProcessorControl(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ProcessorControl() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// D1 domain Power Down Deepsleep selection. This bit allows CPU1 to define the Deepsleep mode for D1 domain. (PDDS_D1)
            uint32_t power_down_deep_sleep_domain1 : 1;    // bit 0
            /// D2 domain Power Down Deepsleep. This bit allows CPU1 to define the Deepsleep mode for D2 domain. (PDDS_D2)
            uint32_t power_down_deep_sleep_domain2 : 1;    // bit 1
            /// System D3 domain Power Down Deepsleep. This bit allows CPU1 to define the Deepsleep mode for System D3 domain. (PDDS_D3)
            uint32_t power_down_deep_sleep_domain3 : 1;    // bit 2
            /// (reserved)
            uint32_t                               : 2;    // bits 3:4
            /// STOP flag This bit is set by hardware and cleared only by any reset or by setting the CPU1 CSSF bit. (STOPF)
            uint32_t stop_detection                : 1;    // bit 5
            /// System Standby flag This bit is set by hardware and cleared only by a POR (Power-on Reset) or by setting the CPU1 CSSF bit (SBF)
            uint32_t standby_flag                  : 1;    // bit 6
            /// D1 domain DStandby flag This bit is set by hardware and cleared by any system reset or by setting the CPU1 CSSF bit. Once set, this
            /// bit can be cleared only when the D1 domain is no longer in DStandby mode. (SBF_D1)
            uint32_t standby_flag_domain1          : 1;    // bit 7
            /// D2 domain DStandby flag This bit is set by hardware and cleared by any system reset or by setting the CPU1 CSSF bit. Once set, this
            /// bit can be cleared only when the D2 domain is no longer in DStandby mode. (SBF_D2)
            uint32_t standby_flag_domain2          : 1;    // bit 8
            /// Clear D1 domain CPU1 Standby, Stop and HOLD flags (always read as 0) This bit is cleared to 0 by hardware. (CSSF)
            uint32_t clock_security_system_flag    : 1;    // bit 9
            /// (reserved)
            uint32_t                               : 1;    // bit 10
            /// Keep system D3 domain in Run mode regardless of the CPU sub-systems modes (RUN_D3)
            uint32_t run_domain3                   : 1;    // bit 11
            /// (reserved)
            uint32_t                               : 20;    // bits 12:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ProcessorControl& operator=(ProcessorControl&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ProcessorControl volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ProcessorControl const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ProcessorControl>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ProcessorControl) == 4UL, "Must be this exact size");
    /// This register allows controlling D3 domain power.Following reset VOSRDY will be read 1 by software (D3CR)
    struct Domain3Control final {
        /// Default Constructor
        Domain3Control()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Domain3Control(Domain3Control volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Domain3Control(Domain3Control const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Domain3Control(Domain3Control&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Domain3Control(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Domain3Control(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Domain3Control() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                              : 13;    // bits 0:12
            /// VOS Ready bit for VCORE voltage scaling output selection. This bit is set to 1 by hardware when Bypass mode is selected in PWR control
            /// register 3 (PWR_CR3). (VOSRDY)
            uint32_t voltage_scaling_output_ready : 1;    // bit 13
            /// Voltage scaling selection according to performance These bits control the VCORE voltage level and allow to obtains the best trade-off
            /// between power consumption and performance: When increasing the performance, the voltage scaling shall be changed before increasing the
            /// system frequency. When decreasing performance, the system frequency shall first be decreased before changing the voltage scaling.
            /// (VOS)
            uint32_t voltage_scaling_selection    : 2;    // bits 14:15
            /// (reserved)
            uint32_t                              : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Domain3Control& operator=(Domain3Control&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Domain3Control volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Domain3Control const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Domain3Control>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Domain3Control) == 4UL, "Must be this exact size");
    /// reset only by system reset, not reset by wakeup from Standby mode5 wait states are required when writing this register (when clearing a WKUPF
    /// bit in PWR_WKUPFR, the AHB write access will complete after the WKUPF has been cleared). (WKUPCR)
    struct WakeupClearRegister final {
        /// Default Constructor
        WakeupClearRegister()
            : whole{0u} {}
        /// Copy Constructor from volatile
        WakeupClearRegister(WakeupClearRegister volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        WakeupClearRegister(WakeupClearRegister const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        WakeupClearRegister(WakeupClearRegister&&) = delete;
        /// Parameterized Constructor for constant references
        explicit WakeupClearRegister(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit WakeupClearRegister(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~WakeupClearRegister() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Clear Wakeup pin flag for WKUP. These bits are always read as 0. (WKUPC)
            uint32_t wakeup_clear : 6;    // bits 0:5
            /// (reserved)
            uint32_t              : 26;    // bits 6:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        WakeupClearRegister& operator=(WakeupClearRegister&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(WakeupClearRegister volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(WakeupClearRegister const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<WakeupClearRegister>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(WakeupClearRegister) == 4UL, "Must be this exact size");
    /// reset only by system reset, not reset by wakeup from Standby mode (WKUPFR)
    struct WakeupFlagRegister final {
        /// Default Constructor
        WakeupFlagRegister()
            : whole{0u} {}
        /// Copy Constructor from volatile
        WakeupFlagRegister(WakeupFlagRegister volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        WakeupFlagRegister(WakeupFlagRegister const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        WakeupFlagRegister(WakeupFlagRegister&&) = delete;
        /// Parameterized Constructor for constant references
        explicit WakeupFlagRegister(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit WakeupFlagRegister(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~WakeupFlagRegister() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Wakeup pin WKUPF flag. This bit is set by hardware and cleared only by a Reset pin or by setting the WKUPCn+1 bit in the PWR wakeup
            /// clear register (PWR_WKUPCR). (WKUPF1)
            uint32_t wakeup_pin1_flag : 1;    // bit 0
            /// Wakeup pin WKUPF flag. This bit is set by hardware and cleared only by a Reset pin or by setting the WKUPCn+1 bit in the PWR wakeup
            /// clear register (PWR_WKUPCR). (WKUPF2)
            uint32_t wakeup_pin2_flag : 1;    // bit 1
            /// Wakeup pin WKUPF flag. This bit is set by hardware and cleared only by a Reset pin or by setting the WKUPCn+1 bit in the PWR wakeup
            /// clear register (PWR_WKUPCR). (WKUPF3)
            uint32_t wakeup_pin3_flag : 1;    // bit 2
            /// Wakeup pin WKUPF flag. This bit is set by hardware and cleared only by a Reset pin or by setting the WKUPCn+1 bit in the PWR wakeup
            /// clear register (PWR_WKUPCR). (WKUPF4)
            uint32_t wakeup_pin4_flag : 1;    // bit 3
            /// Wakeup pin WKUPF flag. This bit is set by hardware and cleared only by a Reset pin or by setting the WKUPCn+1 bit in the PWR wakeup
            /// clear register (PWR_WKUPCR). (WKUPF5)
            uint32_t wakeup_pin5_flag : 1;    // bit 4
            /// Wakeup pin WKUPF flag. This bit is set by hardware and cleared only by a Reset pin or by setting the WKUPCn+1 bit in the PWR wakeup
            /// clear register (PWR_WKUPCR). (WKUPF6)
            uint32_t wakeup_pin6_flag : 1;    // bit 5
            /// (reserved)
            uint32_t                  : 26;    // bits 6:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        WakeupFlagRegister& operator=(WakeupFlagRegister&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(WakeupFlagRegister volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(WakeupFlagRegister const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<WakeupFlagRegister>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(WakeupFlagRegister) == 4UL, "Must be this exact size");
    /// Reset only by system reset, not reset by wakeup from Standby mode (WKUPEPR)
    struct WakeupEnablePolarityRegister final {
        /// Default Constructor
        WakeupEnablePolarityRegister()
            : whole{0u} {}
        /// Copy Constructor from volatile
        WakeupEnablePolarityRegister(WakeupEnablePolarityRegister volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        WakeupEnablePolarityRegister(WakeupEnablePolarityRegister const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        WakeupEnablePolarityRegister(WakeupEnablePolarityRegister&&) = delete;
        /// Parameterized Constructor for constant references
        explicit WakeupEnablePolarityRegister(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit WakeupEnablePolarityRegister(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~WakeupEnablePolarityRegister() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Enable Wakeup Pin WKUPn+1 Each bit is set and cleared by software. Note: An additional wakeup event is detected if WKUPn+1 pin is
            /// enabled (by setting the WKUPENn+1 bit) when WKUPn+1 pin level is already high when WKUPPn+1 selects rising edge, or low when WKUPPn+1
            /// selects falling edge. (WKUPEN1)
            uint32_t wakeup_pin1_enable             : 1;    // bit 0
            /// Enable Wakeup Pin WKUPn+1 Each bit is set and cleared by software. Note: An additional wakeup event is detected if WKUPn+1 pin is
            /// enabled (by setting the WKUPENn+1 bit) when WKUPn+1 pin level is already high when WKUPPn+1 selects rising edge, or low when WKUPPn+1
            /// selects falling edge. (WKUPEN2)
            uint32_t wakeup_pin2_enable             : 1;    // bit 1
            /// Enable Wakeup Pin WKUPn+1 Each bit is set and cleared by software. Note: An additional wakeup event is detected if WKUPn+1 pin is
            /// enabled (by setting the WKUPENn+1 bit) when WKUPn+1 pin level is already high when WKUPPn+1 selects rising edge, or low when WKUPPn+1
            /// selects falling edge. (WKUPEN3)
            uint32_t wakeup_pin3_enable             : 1;    // bit 2
            /// Enable Wakeup Pin WKUPn+1 Each bit is set and cleared by software. Note: An additional wakeup event is detected if WKUPn+1 pin is
            /// enabled (by setting the WKUPENn+1 bit) when WKUPn+1 pin level is already high when WKUPPn+1 selects rising edge, or low when WKUPPn+1
            /// selects falling edge. (WKUPEN4)
            uint32_t wakeup_pin4_enable             : 1;    // bit 3
            /// Enable Wakeup Pin WKUPn+1 Each bit is set and cleared by software. Note: An additional wakeup event is detected if WKUPn+1 pin is
            /// enabled (by setting the WKUPENn+1 bit) when WKUPn+1 pin level is already high when WKUPPn+1 selects rising edge, or low when WKUPPn+1
            /// selects falling edge. (WKUPEN5)
            uint32_t wakeup_pin5_enable             : 1;    // bit 4
            /// Enable Wakeup Pin WKUPn+1 Each bit is set and cleared by software. Note: An additional wakeup event is detected if WKUPn+1 pin is
            /// enabled (by setting the WKUPENn+1 bit) when WKUPn+1 pin level is already high when WKUPPn+1 selects rising edge, or low when WKUPPn+1
            /// selects falling edge. (WKUPEN6)
            uint32_t wakeup_pin6_enable             : 1;    // bit 5
            /// (reserved)
            uint32_t                                : 2;    // bits 6:7
            /// Wakeup pin polarity bit for WKUPn-7 These bits define the polarity used for event detection on WKUPn-7 external wakeup pin. (WKUPP1)
            uint32_t wakeup_pin1_polarity           : 1;    // bit 8
            /// Wakeup pin polarity bit for WKUPn-7 These bits define the polarity used for event detection on WKUPn-7 external wakeup pin. (WKUPP2)
            uint32_t wakeup_pin2_polarity           : 1;    // bit 9
            /// Wakeup pin polarity bit for WKUPn-7 These bits define the polarity used for event detection on WKUPn-7 external wakeup pin. (WKUPP3)
            uint32_t wakeup_pin3_polarity           : 1;    // bit 10
            /// Wakeup pin polarity bit for WKUPn-7 These bits define the polarity used for event detection on WKUPn-7 external wakeup pin. (WKUPP4)
            uint32_t wakeup_pin4_polarity           : 1;    // bit 11
            /// Wakeup pin polarity bit for WKUPn-7 These bits define the polarity used for event detection on WKUPn-7 external wakeup pin. (WKUPP5)
            uint32_t wakeup_pin5_polarity           : 1;    // bit 12
            /// Wakeup pin polarity bit for WKUPn-7 These bits define the polarity used for event detection on WKUPn-7 external wakeup pin. (WKUPP6)
            uint32_t wakeup_pin6_polarity           : 1;    // bit 13
            /// (reserved)
            uint32_t                                : 2;    // bits 14:15
            /// Wakeup pin pull configuration (WKUPPUPD1)
            uint32_t wakeup_pin1_pull_configuration : 2;    // bits 16:17
            /// Wakeup pin pull configuration (WKUPPUPD2)
            uint32_t wakeup_pin2_pull_configuration : 2;    // bits 18:19
            /// Wakeup pin pull configuration (WKUPPUPD3)
            uint32_t wakeup_pin3_pull_configuration : 2;    // bits 20:21
            /// Wakeup pin pull configuration (WKUPPUPD4)
            uint32_t wakeup_pin4_pull_configuration : 2;    // bits 22:23
            /// Wakeup pin pull configuration (WKUPPUPD5)
            uint32_t wakeup_pin5_pull_configuration : 2;    // bits 24:25
            /// Wakeup pin pull configuration for WKUP(truncate(n/2)-7) These bits define the I/O pad pull configuration used when
            /// WKUPEN(truncate(n/2)-7) = 1. The associated GPIO port pull configuration shall be set to the same value or to 00. The Wakeup pin pull
            /// configuration is kept in Standby mode. (WKUPPUPD6)
            uint32_t wakeup_pin6_pull_configuration : 2;    // bits 26:27
            /// (reserved)
            uint32_t                                : 4;    // bits 28:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        WakeupEnablePolarityRegister& operator=(WakeupEnablePolarityRegister&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(WakeupEnablePolarityRegister volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(WakeupEnablePolarityRegister const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<WakeupEnablePolarityRegister>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(WakeupEnablePolarityRegister) == 4UL, "Must be this exact size");

    //+=MEMORY======================================+
    /// PWR control register 1 (CR1)
    Control1 control1;    // offset 0x0UL
    /// PWR control status register 1 (CSR1)
    ContextSwap1 context_swap1;    // offset 0x4UL
    /// This register is not reset by wakeup from Standby mode, RESET signal and VDD POR. It is only reset by VSW POR and VSWRST reset. This register
    /// shall not be accessed when VSWRST bit in RCC_BDCR register resets the VSW domain.After reset, PWR_CR2 register is write-protected. Prior to
    /// modifying its content, the DBP bit in PWR_CR1 register must be set to disable the write protection. (CR2)
    Control2 control2;    // offset 0x8UL
    /// Reset only by POR only, not reset by wakeup from Standby mode and RESET pad. The lower byte of this register is written once after POR and
    /// shall be written before changing VOS level or ck_sys clock frequency. No limitation applies to the upper bytes.Programming data corresponding
    /// to an invalid combination of SDLEVEL, SDEXTHP, SDEN, LDOEN and BYPASS bits (see Table9) will be ignored: data will not be written, the
    /// written-once mechanism will lock the register and any further write access will be ignored. The default supply configuration will be kept and
    /// the ACTVOSRDY bit in PWR control status register 1 (PWR_CSR1) will go on indicating invalid voltage levels. The system shall be power cycled
    /// before writing a new value. (CR3)
    Control3 control3;    // offset 0xcUL
    /// This register allows controlling CPU1 power. (CPUCR)
    ProcessorControl processor_control;    // offset 0x10UL
    uint32_t : 32;                         // offset 0x14UL
    /// This register allows controlling D3 domain power.Following reset VOSRDY will be read 1 by software (D3CR)
    Domain3Control domain3_control;    // offset 0x18UL
    uint32_t : 32;                     // offset 0x1cUL
    /// reset only by system reset, not reset by wakeup from Standby mode5 wait states are required when writing this register (when clearing a WKUPF
    /// bit in PWR_WKUPFR, the AHB write access will complete after the WKUPF has been cleared). (WKUPCR)
    WakeupClearRegister wakeup_clear_register;    // offset 0x20UL
    /// reset only by system reset, not reset by wakeup from Standby mode (WKUPFR)
    WakeupFlagRegister wakeup_flag_register;    // offset 0x24UL
    /// Reset only by system reset, not reset by wakeup from Standby mode (WKUPEPR)
    WakeupEnablePolarityRegister wakeup_enable_polarity_register;    // offset 0x28UL
    uint32_t : 32;                                                   // offset 0x2cUL
    uint32_t : 32;                                                   // offset 0x30UL
    uint32_t : 32;                                                   // offset 0x34UL
    uint32_t : 32;                                                   // offset 0x38UL
    uint32_t : 32;                                                   // offset 0x3cUL
    uint32_t : 32;                                                   // offset 0x40UL
    uint32_t : 32;                                                   // offset 0x44UL
    uint32_t : 32;                                                   // offset 0x48UL
    uint32_t : 32;                                                   // offset 0x4cUL
    uint32_t : 32;                                                   // offset 0x50UL
    uint32_t : 32;                                                   // offset 0x54UL
    uint32_t : 32;                                                   // offset 0x58UL
    uint32_t : 32;                                                   // offset 0x5cUL
    uint32_t : 32;                                                   // offset 0x60UL
    uint32_t : 32;                                                   // offset 0x64UL
    uint32_t : 32;                                                   // offset 0x68UL
    uint32_t : 32;                                                   // offset 0x6cUL
    uint32_t : 32;                                                   // offset 0x70UL
    uint32_t : 32;                                                   // offset 0x74UL
    uint32_t : 32;                                                   // offset 0x78UL
    uint32_t : 32;                                                   // offset 0x7cUL
    uint32_t : 32;                                                   // offset 0x80UL
    uint32_t : 32;                                                   // offset 0x84UL
    uint32_t : 32;                                                   // offset 0x88UL
    uint32_t : 32;                                                   // offset 0x8cUL
    uint32_t : 32;                                                   // offset 0x90UL
    uint32_t : 32;                                                   // offset 0x94UL
    uint32_t : 32;                                                   // offset 0x98UL
    uint32_t : 32;                                                   // offset 0x9cUL
    uint32_t : 32;                                                   // offset 0xa0UL
    uint32_t : 32;                                                   // offset 0xa4UL
    uint32_t : 32;                                                   // offset 0xa8UL
    uint32_t : 32;                                                   // offset 0xacUL
    uint32_t : 32;                                                   // offset 0xb0UL
    uint32_t : 32;                                                   // offset 0xb4UL
    uint32_t : 32;                                                   // offset 0xb8UL
    uint32_t : 32;                                                   // offset 0xbcUL
    uint32_t : 32;                                                   // offset 0xc0UL
    uint32_t : 32;                                                   // offset 0xc4UL
    uint32_t : 32;                                                   // offset 0xc8UL
    uint32_t : 32;                                                   // offset 0xccUL
    uint32_t : 32;                                                   // offset 0xd0UL
    uint32_t : 32;                                                   // offset 0xd4UL
    uint32_t : 32;                                                   // offset 0xd8UL
    uint32_t : 32;                                                   // offset 0xdcUL
    uint32_t : 32;                                                   // offset 0xe0UL
    uint32_t : 32;                                                   // offset 0xe4UL
    uint32_t : 32;                                                   // offset 0xe8UL
    uint32_t : 32;                                                   // offset 0xecUL
    uint32_t : 32;                                                   // offset 0xf0UL
    uint32_t : 32;                                                   // offset 0xf4UL
    uint32_t : 32;                                                   // offset 0xf8UL
    uint32_t : 32;                                                   // offset 0xfcUL
    uint32_t : 32;                                                   // offset 0x100UL
    uint32_t : 32;                                                   // offset 0x104UL
    uint32_t : 32;                                                   // offset 0x108UL
    uint32_t : 32;                                                   // offset 0x10cUL
    uint32_t : 32;                                                   // offset 0x110UL
    uint32_t : 32;                                                   // offset 0x114UL
    uint32_t : 32;                                                   // offset 0x118UL
    uint32_t : 32;                                                   // offset 0x11cUL
    uint32_t : 32;                                                   // offset 0x120UL
    uint32_t : 32;                                                   // offset 0x124UL
    uint32_t : 32;                                                   // offset 0x128UL
    uint32_t : 32;                                                   // offset 0x12cUL
    uint32_t : 32;                                                   // offset 0x130UL
    uint32_t : 32;                                                   // offset 0x134UL
    uint32_t : 32;                                                   // offset 0x138UL
    uint32_t : 32;                                                   // offset 0x13cUL
    uint32_t : 32;                                                   // offset 0x140UL
    uint32_t : 32;                                                   // offset 0x144UL
    uint32_t : 32;                                                   // offset 0x148UL
    uint32_t : 32;                                                   // offset 0x14cUL
    uint32_t : 32;                                                   // offset 0x150UL
    uint32_t : 32;                                                   // offset 0x154UL
    uint32_t : 32;                                                   // offset 0x158UL
    uint32_t : 32;                                                   // offset 0x15cUL
    uint32_t : 32;                                                   // offset 0x160UL
    uint32_t : 32;                                                   // offset 0x164UL
    uint32_t : 32;                                                   // offset 0x168UL
    uint32_t : 32;                                                   // offset 0x16cUL
    uint32_t : 32;                                                   // offset 0x170UL
    uint32_t : 32;                                                   // offset 0x174UL
    uint32_t : 32;                                                   // offset 0x178UL
    uint32_t : 32;                                                   // offset 0x17cUL
    uint32_t : 32;                                                   // offset 0x180UL
    uint32_t : 32;                                                   // offset 0x184UL
    uint32_t : 32;                                                   // offset 0x188UL
    uint32_t : 32;                                                   // offset 0x18cUL
    uint32_t : 32;                                                   // offset 0x190UL
    uint32_t : 32;                                                   // offset 0x194UL
    uint32_t : 32;                                                   // offset 0x198UL
    uint32_t : 32;                                                   // offset 0x19cUL
    uint32_t : 32;                                                   // offset 0x1a0UL
    uint32_t : 32;                                                   // offset 0x1a4UL
    uint32_t : 32;                                                   // offset 0x1a8UL
    uint32_t : 32;                                                   // offset 0x1acUL
    uint32_t : 32;                                                   // offset 0x1b0UL
    uint32_t : 32;                                                   // offset 0x1b4UL
    uint32_t : 32;                                                   // offset 0x1b8UL
    uint32_t : 32;                                                   // offset 0x1bcUL
    uint32_t : 32;                                                   // offset 0x1c0UL
    uint32_t : 32;                                                   // offset 0x1c4UL
    uint32_t : 32;                                                   // offset 0x1c8UL
    uint32_t : 32;                                                   // offset 0x1ccUL
    uint32_t : 32;                                                   // offset 0x1d0UL
    uint32_t : 32;                                                   // offset 0x1d4UL
    uint32_t : 32;                                                   // offset 0x1d8UL
    uint32_t : 32;                                                   // offset 0x1dcUL
    uint32_t : 32;                                                   // offset 0x1e0UL
    uint32_t : 32;                                                   // offset 0x1e4UL
    uint32_t : 32;                                                   // offset 0x1e8UL
    uint32_t : 32;                                                   // offset 0x1ecUL
    uint32_t : 32;                                                   // offset 0x1f0UL
    uint32_t : 32;                                                   // offset 0x1f4UL
    uint32_t : 32;                                                   // offset 0x1f8UL
    uint32_t : 32;                                                   // offset 0x1fcUL
    uint32_t : 32;                                                   // offset 0x200UL
    uint32_t : 32;                                                   // offset 0x204UL
    uint32_t : 32;                                                   // offset 0x208UL
    uint32_t : 32;                                                   // offset 0x20cUL
    uint32_t : 32;                                                   // offset 0x210UL
    uint32_t : 32;                                                   // offset 0x214UL
    uint32_t : 32;                                                   // offset 0x218UL
    uint32_t : 32;                                                   // offset 0x21cUL
    uint32_t : 32;                                                   // offset 0x220UL
    uint32_t : 32;                                                   // offset 0x224UL
    uint32_t : 32;                                                   // offset 0x228UL
    uint32_t : 32;                                                   // offset 0x22cUL
    uint32_t : 32;                                                   // offset 0x230UL
    uint32_t : 32;                                                   // offset 0x234UL
    uint32_t : 32;                                                   // offset 0x238UL
    uint32_t : 32;                                                   // offset 0x23cUL
    uint32_t : 32;                                                   // offset 0x240UL
    uint32_t : 32;                                                   // offset 0x244UL
    uint32_t : 32;                                                   // offset 0x248UL
    uint32_t : 32;                                                   // offset 0x24cUL
    uint32_t : 32;                                                   // offset 0x250UL
    uint32_t : 32;                                                   // offset 0x254UL
    uint32_t : 32;                                                   // offset 0x258UL
    uint32_t : 32;                                                   // offset 0x25cUL
    uint32_t : 32;                                                   // offset 0x260UL
    uint32_t : 32;                                                   // offset 0x264UL
    uint32_t : 32;                                                   // offset 0x268UL
    uint32_t : 32;                                                   // offset 0x26cUL
    uint32_t : 32;                                                   // offset 0x270UL
    uint32_t : 32;                                                   // offset 0x274UL
    uint32_t : 32;                                                   // offset 0x278UL
    uint32_t : 32;                                                   // offset 0x27cUL
    uint32_t : 32;                                                   // offset 0x280UL
    uint32_t : 32;                                                   // offset 0x284UL
    uint32_t : 32;                                                   // offset 0x288UL
    uint32_t : 32;                                                   // offset 0x28cUL
    uint32_t : 32;                                                   // offset 0x290UL
    uint32_t : 32;                                                   // offset 0x294UL
    uint32_t : 32;                                                   // offset 0x298UL
    uint32_t : 32;                                                   // offset 0x29cUL
    uint32_t : 32;                                                   // offset 0x2a0UL
    uint32_t : 32;                                                   // offset 0x2a4UL
    uint32_t : 32;                                                   // offset 0x2a8UL
    uint32_t : 32;                                                   // offset 0x2acUL
    uint32_t : 32;                                                   // offset 0x2b0UL
    uint32_t : 32;                                                   // offset 0x2b4UL
    uint32_t : 32;                                                   // offset 0x2b8UL
    uint32_t : 32;                                                   // offset 0x2bcUL
    uint32_t : 32;                                                   // offset 0x2c0UL
    uint32_t : 32;                                                   // offset 0x2c4UL
    uint32_t : 32;                                                   // offset 0x2c8UL
    uint32_t : 32;                                                   // offset 0x2ccUL
    uint32_t : 32;                                                   // offset 0x2d0UL
    uint32_t : 32;                                                   // offset 0x2d4UL
    uint32_t : 32;                                                   // offset 0x2d8UL
    uint32_t : 32;                                                   // offset 0x2dcUL
    uint32_t : 32;                                                   // offset 0x2e0UL
    uint32_t : 32;                                                   // offset 0x2e4UL
    uint32_t : 32;                                                   // offset 0x2e8UL
    uint32_t : 32;                                                   // offset 0x2ecUL
    uint32_t : 32;                                                   // offset 0x2f0UL
    uint32_t : 32;                                                   // offset 0x2f4UL
    uint32_t : 32;                                                   // offset 0x2f8UL
    uint32_t : 32;                                                   // offset 0x2fcUL
    uint32_t : 32;                                                   // offset 0x300UL
    uint32_t : 32;                                                   // offset 0x304UL
    uint32_t : 32;                                                   // offset 0x308UL
    uint32_t : 32;                                                   // offset 0x30cUL
    uint32_t : 32;                                                   // offset 0x310UL
    uint32_t : 32;                                                   // offset 0x314UL
    uint32_t : 32;                                                   // offset 0x318UL
    uint32_t : 32;                                                   // offset 0x31cUL
    uint32_t : 32;                                                   // offset 0x320UL
    uint32_t : 32;                                                   // offset 0x324UL
    uint32_t : 32;                                                   // offset 0x328UL
    uint32_t : 32;                                                   // offset 0x32cUL
    uint32_t : 32;                                                   // offset 0x330UL
    uint32_t : 32;                                                   // offset 0x334UL
    uint32_t : 32;                                                   // offset 0x338UL
    uint32_t : 32;                                                   // offset 0x33cUL
    uint32_t : 32;                                                   // offset 0x340UL
    uint32_t : 32;                                                   // offset 0x344UL
    uint32_t : 32;                                                   // offset 0x348UL
    uint32_t : 32;                                                   // offset 0x34cUL
    uint32_t : 32;                                                   // offset 0x350UL
    uint32_t : 32;                                                   // offset 0x354UL
    uint32_t : 32;                                                   // offset 0x358UL
    uint32_t : 32;                                                   // offset 0x35cUL
    uint32_t : 32;                                                   // offset 0x360UL
    uint32_t : 32;                                                   // offset 0x364UL
    uint32_t : 32;                                                   // offset 0x368UL
    uint32_t : 32;                                                   // offset 0x36cUL
    uint32_t : 32;                                                   // offset 0x370UL
    uint32_t : 32;                                                   // offset 0x374UL
    uint32_t : 32;                                                   // offset 0x378UL
    uint32_t : 32;                                                   // offset 0x37cUL
    uint32_t : 32;                                                   // offset 0x380UL
    uint32_t : 32;                                                   // offset 0x384UL
    uint32_t : 32;                                                   // offset 0x388UL
    uint32_t : 32;                                                   // offset 0x38cUL
    uint32_t : 32;                                                   // offset 0x390UL
    uint32_t : 32;                                                   // offset 0x394UL
    uint32_t : 32;                                                   // offset 0x398UL
    uint32_t : 32;                                                   // offset 0x39cUL
    uint32_t : 32;                                                   // offset 0x3a0UL
    uint32_t : 32;                                                   // offset 0x3a4UL
    uint32_t : 32;                                                   // offset 0x3a8UL
    uint32_t : 32;                                                   // offset 0x3acUL
    uint32_t : 32;                                                   // offset 0x3b0UL
    uint32_t : 32;                                                   // offset 0x3b4UL
    uint32_t : 32;                                                   // offset 0x3b8UL
    uint32_t : 32;                                                   // offset 0x3bcUL
    uint32_t : 32;                                                   // offset 0x3c0UL
    uint32_t : 32;                                                   // offset 0x3c4UL
    uint32_t : 32;                                                   // offset 0x3c8UL
    uint32_t : 32;                                                   // offset 0x3ccUL
    uint32_t : 32;                                                   // offset 0x3d0UL
    uint32_t : 32;                                                   // offset 0x3d4UL
    uint32_t : 32;                                                   // offset 0x3d8UL
    uint32_t : 32;                                                   // offset 0x3dcUL
    uint32_t : 32;                                                   // offset 0x3e0UL
    uint32_t : 32;                                                   // offset 0x3e4UL
    uint32_t : 32;                                                   // offset 0x3e8UL
    uint32_t : 32;                                                   // offset 0x3ecUL
    uint32_t : 32;                                                   // offset 0x3f0UL
    uint32_t : 32;                                                   // offset 0x3f4UL
    uint32_t : 32;                                                   // offset 0x3f8UL
    uint32_t : 32;                                                   // offset 0x3fcUL
    //+=MEMORY======================================+
};
// Ensure the structure is in standard layout format
static_assert(std::is_standard_layout<PowerController>::value, "Must be standard layout");
// Ensure the offsets are all correct
static_assert(offsetof(PowerController, control1) == 0x0UL, "Must be located at this offset");
static_assert(offsetof(PowerController, context_swap1) == 0x4UL, "Must be located at this offset");
static_assert(offsetof(PowerController, control2) == 0x8UL, "Must be located at this offset");
static_assert(offsetof(PowerController, control3) == 0xcUL, "Must be located at this offset");
static_assert(offsetof(PowerController, processor_control) == 0x10UL, "Must be located at this offset");
static_assert(offsetof(PowerController, domain3_control) == 0x18UL, "Must be located at this offset");
static_assert(offsetof(PowerController, wakeup_clear_register) == 0x20UL, "Must be located at this offset");
static_assert(offsetof(PowerController, wakeup_flag_register) == 0x24UL, "Must be located at this offset");
static_assert(offsetof(PowerController, wakeup_enable_polarity_register) == 0x28UL, "Must be located at this offset");

// Ensure the sizeof the entire structure is correct.
static_assert(sizeof(PowerController) == 0x400UL, "Must be this exact size");

}    // namespace h7xx
}    // namespace stm32
#endif    // STM32_H7XX_POWERCONTROLLER__HPP_


#ifndef STM32_H7XX_SYSTEMCONFIGURATION__HPP_
#define STM32_H7XX_SYSTEMCONFIGURATION__HPP_

/// @file
/// Auto Generated Structure Definitions for SystemConfiguration from the Peripheralyzer.
/// @copyright

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace stm32 {
namespace h7xx {

/// System configuration controller (SYSCFG)
struct SystemConfiguration final {
    /// peripheral mode configuration register (PMCR)
    struct PeripheralModeControl final {
        /// Default Constructor
        PeripheralModeControl()
            : whole{0u} {}
        /// Copy Constructor from volatile
        PeripheralModeControl(PeripheralModeControl volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        PeripheralModeControl(PeripheralModeControl const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        PeripheralModeControl(PeripheralModeControl&&) = delete;
        /// Parameterized Constructor for constant references
        explicit PeripheralModeControl(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit PeripheralModeControl(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~PeripheralModeControl() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// I2C1 Fm+ (I2C1FMP)
            uint32_t i2c1_fast_mode_plus                    : 1;    // bit 0
            /// I2C2 Fm+ (I2C2FMP)
            uint32_t i2c2_fast_mode_plus                    : 1;    // bit 1
            /// I2C3 Fm+ (I2C3FMP)
            uint32_t i2c3_fast_mode_plus                    : 1;    // bit 2
            /// I2C4 Fm+ (I2C4FMP)
            uint32_t i2c4_fast_mode_plus                    : 1;    // bit 3
            /// PB(6) Fm+ (PB6FMP)
            uint32_t pb6_fast_mode_plus                     : 1;    // bit 4
            /// PB(7) Fast Mode Plus (PB7FMP)
            uint32_t pb7_fast_mode_plus                     : 1;    // bit 5
            /// PB(8) Fast Mode Plus (PB8FMP)
            uint32_t pb8_fast_mode_plus                     : 1;    // bit 6
            /// PB(9) Fm+ (PB9FMP)
            uint32_t pb9_fast_mode_plus                     : 1;    // bit 7
            /// Booster Enable (BOOSTE)
            uint32_t booster_enable                         : 1;    // bit 8
            /// Analog switch supply voltage selection (BOOSTVDDSEL)
            uint32_t analog_switch_supply_voltage_selection : 1;    // bit 9
            /// (reserved)
            uint32_t                                        : 11;    // bits 10:20
            /// Ethernet PHY Interface Selection (EPIS)
            uint32_t ethernet_physical_interface_selection  : 3;    // bits 21:23
            /// PA0 Switch Open (PA0SO)
            uint32_t pa0_switch_open                        : 1;    // bit 24
            /// PA1 Switch Open (PA1SO)
            uint32_t pa1_switch_open                        : 1;    // bit 25
            /// PC2 Switch Open (PC2SO)
            uint32_t pc2_switch_open                        : 1;    // bit 26
            /// PC3 Switch Open (PC3SO)
            uint32_t pc3_switch_open                        : 1;    // bit 27
            /// (reserved)
            uint32_t                                        : 4;    // bits 28:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        PeripheralModeControl& operator=(PeripheralModeControl&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PeripheralModeControl volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PeripheralModeControl const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<PeripheralModeControl>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(PeripheralModeControl) == 4UL, "Must be this exact size");
    /// external interrupt configuration register 1 (EXTICR1)
    struct ExternalInterruptConfiguration1 final {
        /// Default Constructor
        ExternalInterruptConfiguration1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ExternalInterruptConfiguration1(ExternalInterruptConfiguration1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ExternalInterruptConfiguration1(ExternalInterruptConfiguration1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ExternalInterruptConfiguration1(ExternalInterruptConfiguration1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ExternalInterruptConfiguration1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ExternalInterruptConfiguration1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ExternalInterruptConfiguration1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// EXTI x configuration (x = 0 to 3) (EXTI0)
            uint32_t exti0 : 4;    // bits 0:3
            /// EXTI x configuration (x = 0 to 3) (EXTI1)
            uint32_t exti1 : 4;    // bits 4:7
            /// EXTI x configuration (x = 0 to 3) (EXTI2)
            uint32_t exti2 : 4;    // bits 8:11
            /// EXTI x configuration (x = 0 to 3) (EXTI3)
            uint32_t exti3 : 4;    // bits 12:15
            /// (reserved)
            uint32_t       : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ExternalInterruptConfiguration1& operator=(ExternalInterruptConfiguration1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ExternalInterruptConfiguration1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ExternalInterruptConfiguration1 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ExternalInterruptConfiguration1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ExternalInterruptConfiguration1) == 4UL, "Must be this exact size");
    /// external interrupt configuration register 2 (EXTICR2)
    struct ExternalInterruptConfiguration2 final {
        /// Default Constructor
        ExternalInterruptConfiguration2()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ExternalInterruptConfiguration2(ExternalInterruptConfiguration2 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ExternalInterruptConfiguration2(ExternalInterruptConfiguration2 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ExternalInterruptConfiguration2(ExternalInterruptConfiguration2&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ExternalInterruptConfiguration2(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ExternalInterruptConfiguration2(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ExternalInterruptConfiguration2() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// EXTI x configuration (x = 4 to 7) (EXTI4)
            uint32_t exti4 : 4;    // bits 0:3
            /// EXTI x configuration (x = 4 to 7) (EXTI5)
            uint32_t exti5 : 4;    // bits 4:7
            /// EXTI x configuration (x = 4 to 7) (EXTI6)
            uint32_t exti6 : 4;    // bits 8:11
            /// EXTI x configuration (x = 4 to 7) (EXTI7)
            uint32_t exti7 : 4;    // bits 12:15
            /// (reserved)
            uint32_t       : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ExternalInterruptConfiguration2& operator=(ExternalInterruptConfiguration2&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ExternalInterruptConfiguration2 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ExternalInterruptConfiguration2 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ExternalInterruptConfiguration2>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ExternalInterruptConfiguration2) == 4UL, "Must be this exact size");
    /// external interrupt configuration register 3 (EXTICR3)
    struct ExternalInterruptConfiguration3 final {
        /// Default Constructor
        ExternalInterruptConfiguration3()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ExternalInterruptConfiguration3(ExternalInterruptConfiguration3 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ExternalInterruptConfiguration3(ExternalInterruptConfiguration3 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ExternalInterruptConfiguration3(ExternalInterruptConfiguration3&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ExternalInterruptConfiguration3(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ExternalInterruptConfiguration3(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ExternalInterruptConfiguration3() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// EXTI x configuration (x = 8 to 11) (EXTI8)
            uint32_t exti8  : 4;    // bits 0:3
            /// EXTI x configuration (x = 8 to 11) (EXTI9)
            uint32_t exti9  : 4;    // bits 4:7
            /// EXTI10 (EXTI10)
            uint32_t exti10 : 4;    // bits 8:11
            /// EXTI x configuration (x = 8 to 11) (EXTI11)
            uint32_t exti11 : 4;    // bits 12:15
            /// (reserved)
            uint32_t        : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ExternalInterruptConfiguration3& operator=(ExternalInterruptConfiguration3&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ExternalInterruptConfiguration3 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ExternalInterruptConfiguration3 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ExternalInterruptConfiguration3>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ExternalInterruptConfiguration3) == 4UL, "Must be this exact size");
    /// external interrupt configuration register 4 (EXTICR4)
    struct ExternalInterruptConfiguration4 final {
        /// Default Constructor
        ExternalInterruptConfiguration4()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ExternalInterruptConfiguration4(ExternalInterruptConfiguration4 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ExternalInterruptConfiguration4(ExternalInterruptConfiguration4 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ExternalInterruptConfiguration4(ExternalInterruptConfiguration4&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ExternalInterruptConfiguration4(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ExternalInterruptConfiguration4(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ExternalInterruptConfiguration4() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// EXTI x configuration (x = 12 to 15) (EXTI12)
            uint32_t exti12 : 4;    // bits 0:3
            /// EXTI x configuration (x = 12 to 15) (EXTI13)
            uint32_t exti13 : 4;    // bits 4:7
            /// EXTI x configuration (x = 12 to 15) (EXTI14)
            uint32_t exti14 : 4;    // bits 8:11
            /// EXTI x configuration (x = 12 to 15) (EXTI15)
            uint32_t exti15 : 4;    // bits 12:15
            /// (reserved)
            uint32_t        : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ExternalInterruptConfiguration4& operator=(ExternalInterruptConfiguration4&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ExternalInterruptConfiguration4 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ExternalInterruptConfiguration4 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ExternalInterruptConfiguration4>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ExternalInterruptConfiguration4) == 4UL, "Must be this exact size");
    /// compensation cell control/status register (CCCSR)
    struct CompensationCellCodeSelection final {
        /// Default Constructor
        CompensationCellCodeSelection()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CompensationCellCodeSelection(CompensationCellCodeSelection volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CompensationCellCodeSelection(CompensationCellCodeSelection const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CompensationCellCodeSelection(CompensationCellCodeSelection&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CompensationCellCodeSelection(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CompensationCellCodeSelection(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CompensationCellCodeSelection() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// enable (EN)
            uint32_t compensation_cell_enable    : 1;    // bit 0
            /// Code selection (CS)
            uint32_t compensation_code_selection : 1;    // bit 1
            /// (reserved)
            uint32_t                             : 6;    // bits 2:7
            /// Compensation cell ready flag (READY)
            uint32_t compensation_cell_ready     : 1;    // bit 8
            /// (reserved)
            uint32_t                             : 7;    // bits 9:15
            /// High-speed at low-voltage (HSLV)
            uint32_t high_speed_low_voltage      : 1;    // bit 16
            /// (reserved)
            uint32_t                             : 15;    // bits 17:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CompensationCellCodeSelection& operator=(CompensationCellCodeSelection&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CompensationCellCodeSelection volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CompensationCellCodeSelection const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CompensationCellCodeSelection>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CompensationCellCodeSelection) == 4UL, "Must be this exact size");
    /// SYSCFG compensation cell value register (CCVR)
    struct CompensationCellValue final {
        /// Default Constructor
        CompensationCellValue()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CompensationCellValue(CompensationCellValue volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CompensationCellValue(CompensationCellValue const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CompensationCellValue(CompensationCellValue&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CompensationCellValue(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CompensationCellValue(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CompensationCellValue() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// NMOS compensation value (NCV)
            uint32_t nmos_compensation_value : 4;    // bits 0:3
            /// PMOS compensation value (PCV)
            uint32_t pmos_compensation_value : 4;    // bits 4:7
            /// (reserved)
            uint32_t                         : 24;    // bits 8:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CompensationCellValue& operator=(CompensationCellValue&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CompensationCellValue volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CompensationCellValue const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CompensationCellValue>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CompensationCellValue) == 4UL, "Must be this exact size");
    /// SYSCFG compensation cell code register (CCCR)
    struct CompensationCellControl final {
        /// Default Constructor
        CompensationCellControl()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CompensationCellControl(CompensationCellControl volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CompensationCellControl(CompensationCellControl const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CompensationCellControl(CompensationCellControl&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CompensationCellControl(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CompensationCellControl(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CompensationCellControl() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// NMOS compensation code (NCC)
            uint32_t nmos_compensation_code : 4;    // bits 0:3
            /// PMOS compensation code (PCC)
            uint32_t pmos_compensation_code : 4;    // bits 4:7
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
        CompensationCellControl& operator=(CompensationCellControl&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CompensationCellControl volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CompensationCellControl const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CompensationCellControl>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CompensationCellControl) == 4UL, "Must be this exact size");
    /// SYSCFG power control register (PWRCR)
    struct PowerControl final {
        /// Default Constructor
        PowerControl()
            : whole{0u} {}
        /// Copy Constructor from volatile
        PowerControl(PowerControl volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        PowerControl(PowerControl const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        PowerControl(PowerControl&&) = delete;
        /// Parameterized Constructor for constant references
        explicit PowerControl(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit PowerControl(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~PowerControl() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Overdrive enable (ODEN)
            uint32_t overdrive_enable : 4;    // bits 0:3
            /// (reserved)
            uint32_t                  : 28;    // bits 4:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        PowerControl& operator=(PowerControl&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PowerControl volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PowerControl const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<PowerControl>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(PowerControl) == 4UL, "Must be this exact size");
    /// SYSCFG package register (PKGR)
    struct Package final {
        /// Default Constructor
        Package()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Package(Package volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Package(Package const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Package(Package&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Package(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Package(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Package() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Package (PKG)
            uint32_t package_type : 4;    // bits 0:3
            /// (reserved)
            uint32_t              : 28;    // bits 4:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Package& operator=(Package&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Package volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Package const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Package>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Package) == 4UL, "Must be this exact size");
    /// SYSCFG user register 0 (UR0)
    struct User0 final {
        /// Default Constructor
        User0()
            : whole{0u} {}
        /// Copy Constructor from volatile
        User0(User0 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        User0(User0 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        User0(User0&&) = delete;
        /// Parameterized Constructor for constant references
        explicit User0(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit User0(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~User0() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Bank Swap (BKS)
            uint32_t bank_swap : 1;    // bit 0
            /// (reserved)
            uint32_t           : 15;    // bits 1:15
            /// Readout protection (RDP)
            uint32_t rdp       : 8;    // bits 16:23
            /// (reserved)
            uint32_t           : 8;    // bits 24:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        User0& operator=(User0&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(User0 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(User0 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<User0>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(User0) == 4UL, "Must be this exact size");
    /// SYSCFG user register 2 (UR2)
    struct User2 final {
        /// Default Constructor
        User2()
            : whole{0u} {}
        /// Copy Constructor from volatile
        User2(User2 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        User2(User2 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        User2(User2&&) = delete;
        /// Parameterized Constructor for constant references
        explicit User2(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit User2(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~User2() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// BOR_LVL Brownout Reset Threshold Level (BORH)
            uint32_t brownout_reset_level : 2;    // bits 0:1
            /// (reserved)
            uint32_t                      : 14;    // bits 2:15
            /// Boot Address 0 (BOOT_ADD0)
            uint32_t boot_address0        : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        User2& operator=(User2&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(User2 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(User2 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<User2>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(User2) == 4UL, "Must be this exact size");
    /// SYSCFG user register 3 (UR3)
    struct User3 final {
        /// Default Constructor
        User3()
            : whole{0u} {}
        /// Copy Constructor from volatile
        User3(User3 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        User3(User3 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        User3(User3&&) = delete;
        /// Parameterized Constructor for constant references
        explicit User3(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit User3(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~User3() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t               : 16;    // bits 0:15
            /// Boot Address 1 (BOOT_ADD1)
            uint32_t boot_address1 : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        User3& operator=(User3&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(User3 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(User3 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<User3>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(User3) == 4UL, "Must be this exact size");
    /// SYSCFG user register 4 (UR4)
    struct User4 final {
        /// Default Constructor
        User4()
            : whole{0u} {}
        /// Copy Constructor from volatile
        User4(User4 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        User4(User4 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        User4(User4&&) = delete;
        /// Parameterized Constructor for constant references
        explicit User4(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit User4(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~User4() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                                          : 16;    // bits 0:15
            /// Mass Erase Protected Area Disabled for bank 1 (MEPAD_1)
            uint32_t mass_erase_protected_area_disabled_bank1 : 1;    // bit 16
            /// (reserved)
            uint32_t                                          : 15;    // bits 17:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        User4& operator=(User4&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(User4 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(User4 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<User4>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(User4) == 4UL, "Must be this exact size");
    /// SYSCFG user register 5 (UR5)
    struct User5 final {
        /// Default Constructor
        User5()
            : whole{0u} {}
        /// Copy Constructor from volatile
        User5(User5 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        User5(User5 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        User5(User5&&) = delete;
        /// Parameterized Constructor for constant references
        explicit User5(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit User5(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~User5() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Mass erase secured area disabled for bank 1 (MESAD_1)
            uint32_t mass_erase_secured_area_disabled_bank1 : 1;    // bit 0
            /// (reserved)
            uint32_t                                        : 15;    // bits 1:15
            /// Write protection for flash bank 1 (WRPN_1)
            uint32_t write_protection_bank1                 : 8;    // bits 16:23
            /// (reserved)
            uint32_t                                        : 8;    // bits 24:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        User5& operator=(User5&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(User5 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(User5 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<User5>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(User5) == 4UL, "Must be this exact size");
    /// SYSCFG user register 6 (UR6)
    struct User6 final {
        /// Default Constructor
        User6()
            : whole{0u} {}
        /// Copy Constructor from volatile
        User6(User6 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        User6(User6 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        User6(User6&&) = delete;
        /// Parameterized Constructor for constant references
        explicit User6(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit User6(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~User6() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Protected area start address for bank 1 (PA_BEG_1)
            uint32_t protected_area_start_bank1 : 12;    // bits 0:11
            /// (reserved)
            uint32_t                            : 4;    // bits 12:15
            /// Protected area end address for bank 1 (PA_END_1)
            uint32_t protected_area_end_bank1   : 12;    // bits 16:27
            /// (reserved)
            uint32_t                            : 4;    // bits 28:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        User6& operator=(User6&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(User6 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(User6 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<User6>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(User6) == 4UL, "Must be this exact size");
    /// SYSCFG user register 7 (UR7)
    struct User7 final {
        /// Default Constructor
        User7()
            : whole{0u} {}
        /// Copy Constructor from volatile
        User7(User7 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        User7(User7 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        User7(User7&&) = delete;
        /// Parameterized Constructor for constant references
        explicit User7(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit User7(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~User7() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Secured area start address for bank 1 (SA_BEG_1)
            uint32_t secured_area_start_bank1 : 12;    // bits 0:11
            /// (reserved)
            uint32_t                          : 4;    // bits 12:15
            /// Secured area end address for bank 1 (SA_END_1)
            uint32_t secured_area_end_bank1   : 12;    // bits 16:27
            /// (reserved)
            uint32_t                          : 4;    // bits 28:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        User7& operator=(User7&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(User7 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(User7 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<User7>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(User7) == 4UL, "Must be this exact size");
    /// SYSCFG user register 8 (UR8)
    struct User8 final {
        /// Default Constructor
        User8()
            : whole{0u} {}
        /// Copy Constructor from volatile
        User8(User8 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        User8(User8 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        User8(User8&&) = delete;
        /// Parameterized Constructor for constant references
        explicit User8(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit User8(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~User8() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Mass erase protected area disabled for bank 2 (MEPAD_2)
            uint32_t mass_erase_protected_area_disabled_bank2 : 1;    // bit 0
            /// (reserved)
            uint32_t                                          : 15;    // bits 1:15
            /// Mass erase secured area disabled for bank 2 (MESAD_2)
            uint32_t mass_erase_secured_area_disabled_bank2   : 1;    // bit 16
            /// (reserved)
            uint32_t                                          : 15;    // bits 17:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        User8& operator=(User8&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(User8 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(User8 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<User8>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(User8) == 4UL, "Must be this exact size");
    /// SYSCFG user register 9 (UR9)
    struct User9 final {
        /// Default Constructor
        User9()
            : whole{0u} {}
        /// Copy Constructor from volatile
        User9(User9 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        User9(User9 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        User9(User9&&) = delete;
        /// Parameterized Constructor for constant references
        explicit User9(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit User9(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~User9() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Write protection for flash bank 2 (WRPN_2)
            uint32_t write_protection_bank2     : 8;    // bits 0:7
            /// (reserved)
            uint32_t                            : 8;    // bits 8:15
            /// Protected area start address for bank 2 (PA_BEG_2)
            uint32_t protected_area_start_bank2 : 12;    // bits 16:27
            /// (reserved)
            uint32_t                            : 4;    // bits 28:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        User9& operator=(User9&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(User9 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(User9 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<User9>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(User9) == 4UL, "Must be this exact size");
    /// SYSCFG user register 10 (UR10)
    struct User10 final {
        /// Default Constructor
        User10()
            : whole{0u} {}
        /// Copy Constructor from volatile
        User10(User10 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        User10(User10 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        User10(User10&&) = delete;
        /// Parameterized Constructor for constant references
        explicit User10(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit User10(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~User10() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Protected area end address for bank 2 (PA_END_2)
            uint32_t protected_area_end_bank2 : 12;    // bits 0:11
            /// (reserved)
            uint32_t                          : 4;    // bits 12:15
            /// Secured area start address for bank 2 (SA_BEG_2)
            uint32_t secured_area_start_bank2 : 12;    // bits 16:27
            /// (reserved)
            uint32_t                          : 4;    // bits 28:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        User10& operator=(User10&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(User10 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(User10 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<User10>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(User10) == 4UL, "Must be this exact size");
    /// SYSCFG user register 11 (UR11)
    struct User11 final {
        /// Default Constructor
        User11()
            : whole{0u} {}
        /// Copy Constructor from volatile
        User11(User11 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        User11(User11 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        User11(User11&&) = delete;
        /// Parameterized Constructor for constant references
        explicit User11(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit User11(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~User11() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Secured area end address for bank 2 (SA_END_2)
            uint32_t secured_area_end_bank2     : 12;    // bits 0:11
            /// (reserved)
            uint32_t                            : 4;    // bits 12:15
            /// Independent Watchdog 1 mode (IWDG1M)
            uint32_t independent_watchdog1_mode : 1;    // bit 16
            /// (reserved)
            uint32_t                            : 15;    // bits 17:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        User11& operator=(User11&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(User11 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(User11 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<User11>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(User11) == 4UL, "Must be this exact size");
    /// SYSCFG user register 12 (UR12)
    struct User12 final {
        /// Default Constructor
        User12()
            : whole{0u} {}
        /// Copy Constructor from volatile
        User12(User12 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        User12(User12 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        User12(User12&&) = delete;
        /// Parameterized Constructor for constant references
        explicit User12(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit User12(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~User12() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t             : 16;    // bits 0:15
            /// Secure mode (SECURE)
            uint32_t secure_mode : 1;    // bit 16
            /// (reserved)
            uint32_t             : 15;    // bits 17:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        User12& operator=(User12&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(User12 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(User12 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<User12>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(User12) == 4UL, "Must be this exact size");
    /// SYSCFG user register 13 (UR13)
    struct User13 final {
        /// Default Constructor
        User13()
            : whole{0u} {}
        /// Copy Constructor from volatile
        User13(User13 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        User13(User13 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        User13(User13&&) = delete;
        /// Parameterized Constructor for constant references
        explicit User13(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit User13(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~User13() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Secured DTCM RAM Size (SDRS)
            uint32_t secured_dtcm_ram_size : 2;    // bits 0:1
            /// (reserved)
            uint32_t                       : 14;    // bits 2:15
            /// D1 Standby reset (D1SBRST)
            uint32_t domain1_standby_reset : 1;    // bit 16
            /// (reserved)
            uint32_t                       : 15;    // bits 17:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        User13& operator=(User13&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(User13 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(User13 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<User13>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(User13) == 4UL, "Must be this exact size");
    /// SYSCFG user register 14 (UR14)
    struct User14 final {
        /// Default Constructor
        User14()
            : whole{0u} {}
        /// Copy Constructor from volatile
        User14(User14 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        User14(User14 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        User14(User14&&) = delete;
        /// Parameterized Constructor for constant references
        explicit User14(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit User14(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~User14() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// D1 Stop Reset (D1STPRST)
            uint32_t domain1_stop_reset : 1;    // bit 0
            /// (reserved)
            uint32_t                    : 31;    // bits 1:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        User14& operator=(User14&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(User14 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(User14 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<User14>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(User14) == 4UL, "Must be this exact size");
    /// SYSCFG user register 15 (UR15)
    struct User15 final {
        /// Default Constructor
        User15()
            : whole{0u} {}
        /// Copy Constructor from volatile
        User15(User15 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        User15(User15 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        User15(User15&&) = delete;
        /// Parameterized Constructor for constant references
        explicit User15(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit User15(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~User15() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                                        : 16;    // bits 0:15
            /// Freeze independent watchdog in Standby mode (FZIWDGSTB)
            uint32_t freeze_independent_watchdog_in_standby : 1;    // bit 16
            /// (reserved)
            uint32_t                                        : 15;    // bits 17:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        User15& operator=(User15&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(User15 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(User15 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<User15>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(User15) == 4UL, "Must be this exact size");
    /// SYSCFG user register 16 (UR16)
    struct User16 final {
        /// Default Constructor
        User16()
            : whole{0u} {}
        /// Copy Constructor from volatile
        User16(User16 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        User16(User16 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        User16(User16&&) = delete;
        /// Parameterized Constructor for constant references
        explicit User16(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit User16(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~User16() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Freeze independent watchdog in Stop mode (FZIWDGSTP)
            uint32_t freeze_independent_watchdog_in_stop : 1;    // bit 0
            /// (reserved)
            uint32_t                                     : 15;    // bits 1:15
            /// Private key programmed (PKP)
            uint32_t private_key_programmed              : 1;    // bit 16
            /// (reserved)
            uint32_t                                     : 15;    // bits 17:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        User16& operator=(User16&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(User16 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(User16 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<User16>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(User16) == 4UL, "Must be this exact size");
    /// SYSCFG user register 17 (UR17)
    struct User17 final {
        /// Default Constructor
        User17()
            : whole{0u} {}
        /// Copy Constructor from volatile
        User17(User17 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        User17(User17 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        User17(User17&&) = delete;
        /// Parameterized Constructor for constant references
        explicit User17(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit User17(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~User17() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// I/O high speed / low voltage (IO_HSLV)
            uint32_t io_high_speed_low_voltage : 1;    // bit 0
            /// (reserved)
            uint32_t                           : 31;    // bits 1:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        User17& operator=(User17&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(User17 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(User17 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<User17>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(User17) == 4UL, "Must be this exact size");

    //+=MEMORY======================================+
    uint32_t : 32;    // offset 0x0UL
    /// peripheral mode configuration register (PMCR)
    PeripheralModeControl peripheral_mode_control;    // offset 0x4UL
    /// external interrupt configuration register 1 (EXTICR1)
    ExternalInterruptConfiguration1 external_interrupt_configuration1;    // offset 0x8UL
    /// external interrupt configuration register 2 (EXTICR2)
    ExternalInterruptConfiguration2 external_interrupt_configuration2;    // offset 0xcUL
    /// external interrupt configuration register 3 (EXTICR3)
    ExternalInterruptConfiguration3 external_interrupt_configuration3;    // offset 0x10UL
    /// external interrupt configuration register 4 (EXTICR4)
    ExternalInterruptConfiguration4 external_interrupt_configuration4;    // offset 0x14UL
    uint32_t : 32;                                                        // offset 0x18UL
    uint32_t : 32;                                                        // offset 0x1cUL
    /// compensation cell control/status register (CCCSR)
    CompensationCellCodeSelection compensation_cell_code_selection;    // offset 0x20UL
    /// SYSCFG compensation cell value register (CCVR)
    CompensationCellValue compensation_cell_value;    // offset 0x24UL
    /// SYSCFG compensation cell code register (CCCR)
    CompensationCellControl compensation_cell_control;    // offset 0x28UL
    /// SYSCFG power control register (PWRCR)
    PowerControl power_control;    // offset 0x2cUL
    uint32_t : 32;                 // offset 0x30UL
    uint32_t : 32;                 // offset 0x34UL
    uint32_t : 32;                 // offset 0x38UL
    uint32_t : 32;                 // offset 0x3cUL
    uint32_t : 32;                 // offset 0x40UL
    uint32_t : 32;                 // offset 0x44UL
    uint32_t : 32;                 // offset 0x48UL
    uint32_t : 32;                 // offset 0x4cUL
    uint32_t : 32;                 // offset 0x50UL
    uint32_t : 32;                 // offset 0x54UL
    uint32_t : 32;                 // offset 0x58UL
    uint32_t : 32;                 // offset 0x5cUL
    uint32_t : 32;                 // offset 0x60UL
    uint32_t : 32;                 // offset 0x64UL
    uint32_t : 32;                 // offset 0x68UL
    uint32_t : 32;                 // offset 0x6cUL
    uint32_t : 32;                 // offset 0x70UL
    uint32_t : 32;                 // offset 0x74UL
    uint32_t : 32;                 // offset 0x78UL
    uint32_t : 32;                 // offset 0x7cUL
    uint32_t : 32;                 // offset 0x80UL
    uint32_t : 32;                 // offset 0x84UL
    uint32_t : 32;                 // offset 0x88UL
    uint32_t : 32;                 // offset 0x8cUL
    uint32_t : 32;                 // offset 0x90UL
    uint32_t : 32;                 // offset 0x94UL
    uint32_t : 32;                 // offset 0x98UL
    uint32_t : 32;                 // offset 0x9cUL
    uint32_t : 32;                 // offset 0xa0UL
    uint32_t : 32;                 // offset 0xa4UL
    uint32_t : 32;                 // offset 0xa8UL
    uint32_t : 32;                 // offset 0xacUL
    uint32_t : 32;                 // offset 0xb0UL
    uint32_t : 32;                 // offset 0xb4UL
    uint32_t : 32;                 // offset 0xb8UL
    uint32_t : 32;                 // offset 0xbcUL
    uint32_t : 32;                 // offset 0xc0UL
    uint32_t : 32;                 // offset 0xc4UL
    uint32_t : 32;                 // offset 0xc8UL
    uint32_t : 32;                 // offset 0xccUL
    uint32_t : 32;                 // offset 0xd0UL
    uint32_t : 32;                 // offset 0xd4UL
    uint32_t : 32;                 // offset 0xd8UL
    uint32_t : 32;                 // offset 0xdcUL
    uint32_t : 32;                 // offset 0xe0UL
    uint32_t : 32;                 // offset 0xe4UL
    uint32_t : 32;                 // offset 0xe8UL
    uint32_t : 32;                 // offset 0xecUL
    uint32_t : 32;                 // offset 0xf0UL
    uint32_t : 32;                 // offset 0xf4UL
    uint32_t : 32;                 // offset 0xf8UL
    uint32_t : 32;                 // offset 0xfcUL
    uint32_t : 32;                 // offset 0x100UL
    uint32_t : 32;                 // offset 0x104UL
    uint32_t : 32;                 // offset 0x108UL
    uint32_t : 32;                 // offset 0x10cUL
    uint32_t : 32;                 // offset 0x110UL
    uint32_t : 32;                 // offset 0x114UL
    uint32_t : 32;                 // offset 0x118UL
    uint32_t : 32;                 // offset 0x11cUL
    uint32_t : 32;                 // offset 0x120UL
    /// SYSCFG package register (PKGR)
    Package package;    // offset 0x124UL
    uint32_t : 32;      // offset 0x128UL
    uint32_t : 32;      // offset 0x12cUL
    uint32_t : 32;      // offset 0x130UL
    uint32_t : 32;      // offset 0x134UL
    uint32_t : 32;      // offset 0x138UL
    uint32_t : 32;      // offset 0x13cUL
    uint32_t : 32;      // offset 0x140UL
    uint32_t : 32;      // offset 0x144UL
    uint32_t : 32;      // offset 0x148UL
    uint32_t : 32;      // offset 0x14cUL
    uint32_t : 32;      // offset 0x150UL
    uint32_t : 32;      // offset 0x154UL
    uint32_t : 32;      // offset 0x158UL
    uint32_t : 32;      // offset 0x15cUL
    uint32_t : 32;      // offset 0x160UL
    uint32_t : 32;      // offset 0x164UL
    uint32_t : 32;      // offset 0x168UL
    uint32_t : 32;      // offset 0x16cUL
    uint32_t : 32;      // offset 0x170UL
    uint32_t : 32;      // offset 0x174UL
    uint32_t : 32;      // offset 0x178UL
    uint32_t : 32;      // offset 0x17cUL
    uint32_t : 32;      // offset 0x180UL
    uint32_t : 32;      // offset 0x184UL
    uint32_t : 32;      // offset 0x188UL
    uint32_t : 32;      // offset 0x18cUL
    uint32_t : 32;      // offset 0x190UL
    uint32_t : 32;      // offset 0x194UL
    uint32_t : 32;      // offset 0x198UL
    uint32_t : 32;      // offset 0x19cUL
    uint32_t : 32;      // offset 0x1a0UL
    uint32_t : 32;      // offset 0x1a4UL
    uint32_t : 32;      // offset 0x1a8UL
    uint32_t : 32;      // offset 0x1acUL
    uint32_t : 32;      // offset 0x1b0UL
    uint32_t : 32;      // offset 0x1b4UL
    uint32_t : 32;      // offset 0x1b8UL
    uint32_t : 32;      // offset 0x1bcUL
    uint32_t : 32;      // offset 0x1c0UL
    uint32_t : 32;      // offset 0x1c4UL
    uint32_t : 32;      // offset 0x1c8UL
    uint32_t : 32;      // offset 0x1ccUL
    uint32_t : 32;      // offset 0x1d0UL
    uint32_t : 32;      // offset 0x1d4UL
    uint32_t : 32;      // offset 0x1d8UL
    uint32_t : 32;      // offset 0x1dcUL
    uint32_t : 32;      // offset 0x1e0UL
    uint32_t : 32;      // offset 0x1e4UL
    uint32_t : 32;      // offset 0x1e8UL
    uint32_t : 32;      // offset 0x1ecUL
    uint32_t : 32;      // offset 0x1f0UL
    uint32_t : 32;      // offset 0x1f4UL
    uint32_t : 32;      // offset 0x1f8UL
    uint32_t : 32;      // offset 0x1fcUL
    uint32_t : 32;      // offset 0x200UL
    uint32_t : 32;      // offset 0x204UL
    uint32_t : 32;      // offset 0x208UL
    uint32_t : 32;      // offset 0x20cUL
    uint32_t : 32;      // offset 0x210UL
    uint32_t : 32;      // offset 0x214UL
    uint32_t : 32;      // offset 0x218UL
    uint32_t : 32;      // offset 0x21cUL
    uint32_t : 32;      // offset 0x220UL
    uint32_t : 32;      // offset 0x224UL
    uint32_t : 32;      // offset 0x228UL
    uint32_t : 32;      // offset 0x22cUL
    uint32_t : 32;      // offset 0x230UL
    uint32_t : 32;      // offset 0x234UL
    uint32_t : 32;      // offset 0x238UL
    uint32_t : 32;      // offset 0x23cUL
    uint32_t : 32;      // offset 0x240UL
    uint32_t : 32;      // offset 0x244UL
    uint32_t : 32;      // offset 0x248UL
    uint32_t : 32;      // offset 0x24cUL
    uint32_t : 32;      // offset 0x250UL
    uint32_t : 32;      // offset 0x254UL
    uint32_t : 32;      // offset 0x258UL
    uint32_t : 32;      // offset 0x25cUL
    uint32_t : 32;      // offset 0x260UL
    uint32_t : 32;      // offset 0x264UL
    uint32_t : 32;      // offset 0x268UL
    uint32_t : 32;      // offset 0x26cUL
    uint32_t : 32;      // offset 0x270UL
    uint32_t : 32;      // offset 0x274UL
    uint32_t : 32;      // offset 0x278UL
    uint32_t : 32;      // offset 0x27cUL
    uint32_t : 32;      // offset 0x280UL
    uint32_t : 32;      // offset 0x284UL
    uint32_t : 32;      // offset 0x288UL
    uint32_t : 32;      // offset 0x28cUL
    uint32_t : 32;      // offset 0x290UL
    uint32_t : 32;      // offset 0x294UL
    uint32_t : 32;      // offset 0x298UL
    uint32_t : 32;      // offset 0x29cUL
    uint32_t : 32;      // offset 0x2a0UL
    uint32_t : 32;      // offset 0x2a4UL
    uint32_t : 32;      // offset 0x2a8UL
    uint32_t : 32;      // offset 0x2acUL
    uint32_t : 32;      // offset 0x2b0UL
    uint32_t : 32;      // offset 0x2b4UL
    uint32_t : 32;      // offset 0x2b8UL
    uint32_t : 32;      // offset 0x2bcUL
    uint32_t : 32;      // offset 0x2c0UL
    uint32_t : 32;      // offset 0x2c4UL
    uint32_t : 32;      // offset 0x2c8UL
    uint32_t : 32;      // offset 0x2ccUL
    uint32_t : 32;      // offset 0x2d0UL
    uint32_t : 32;      // offset 0x2d4UL
    uint32_t : 32;      // offset 0x2d8UL
    uint32_t : 32;      // offset 0x2dcUL
    uint32_t : 32;      // offset 0x2e0UL
    uint32_t : 32;      // offset 0x2e4UL
    uint32_t : 32;      // offset 0x2e8UL
    uint32_t : 32;      // offset 0x2ecUL
    uint32_t : 32;      // offset 0x2f0UL
    uint32_t : 32;      // offset 0x2f4UL
    uint32_t : 32;      // offset 0x2f8UL
    uint32_t : 32;      // offset 0x2fcUL
    /// SYSCFG user register 0 (UR0)
    User0 user0;      // offset 0x300UL
    uint32_t : 32;    // offset 0x304UL
    /// SYSCFG user register 2 (UR2)
    User2 user2;    // offset 0x308UL
    /// SYSCFG user register 3 (UR3)
    User3 user3;    // offset 0x30cUL
    /// SYSCFG user register 4 (UR4)
    User4 user4;    // offset 0x310UL
    /// SYSCFG user register 5 (UR5)
    User5 user5;    // offset 0x314UL
    /// SYSCFG user register 6 (UR6)
    User6 user6;    // offset 0x318UL
    /// SYSCFG user register 7 (UR7)
    User7 user7;    // offset 0x31cUL
    /// SYSCFG user register 8 (UR8)
    User8 user8;    // offset 0x320UL
    /// SYSCFG user register 9 (UR9)
    User9 user9;    // offset 0x324UL
    /// SYSCFG user register 10 (UR10)
    User10 user10;    // offset 0x328UL
    /// SYSCFG user register 11 (UR11)
    User11 user11;    // offset 0x32cUL
    /// SYSCFG user register 12 (UR12)
    User12 user12;    // offset 0x330UL
    /// SYSCFG user register 13 (UR13)
    User13 user13;    // offset 0x334UL
    /// SYSCFG user register 14 (UR14)
    User14 user14;    // offset 0x338UL
    /// SYSCFG user register 15 (UR15)
    User15 user15;    // offset 0x33cUL
    /// SYSCFG user register 16 (UR16)
    User16 user16;    // offset 0x340UL
    /// SYSCFG user register 17 (UR17)
    User17 user17;    // offset 0x344UL
    uint32_t : 32;    // offset 0x348UL
    uint32_t : 32;    // offset 0x34cUL
    uint32_t : 32;    // offset 0x350UL
    uint32_t : 32;    // offset 0x354UL
    uint32_t : 32;    // offset 0x358UL
    uint32_t : 32;    // offset 0x35cUL
    uint32_t : 32;    // offset 0x360UL
    uint32_t : 32;    // offset 0x364UL
    uint32_t : 32;    // offset 0x368UL
    uint32_t : 32;    // offset 0x36cUL
    uint32_t : 32;    // offset 0x370UL
    uint32_t : 32;    // offset 0x374UL
    uint32_t : 32;    // offset 0x378UL
    uint32_t : 32;    // offset 0x37cUL
    uint32_t : 32;    // offset 0x380UL
    uint32_t : 32;    // offset 0x384UL
    uint32_t : 32;    // offset 0x388UL
    uint32_t : 32;    // offset 0x38cUL
    uint32_t : 32;    // offset 0x390UL
    uint32_t : 32;    // offset 0x394UL
    uint32_t : 32;    // offset 0x398UL
    uint32_t : 32;    // offset 0x39cUL
    uint32_t : 32;    // offset 0x3a0UL
    uint32_t : 32;    // offset 0x3a4UL
    uint32_t : 32;    // offset 0x3a8UL
    uint32_t : 32;    // offset 0x3acUL
    uint32_t : 32;    // offset 0x3b0UL
    uint32_t : 32;    // offset 0x3b4UL
    uint32_t : 32;    // offset 0x3b8UL
    uint32_t : 32;    // offset 0x3bcUL
    uint32_t : 32;    // offset 0x3c0UL
    uint32_t : 32;    // offset 0x3c4UL
    uint32_t : 32;    // offset 0x3c8UL
    uint32_t : 32;    // offset 0x3ccUL
    uint32_t : 32;    // offset 0x3d0UL
    uint32_t : 32;    // offset 0x3d4UL
    uint32_t : 32;    // offset 0x3d8UL
    uint32_t : 32;    // offset 0x3dcUL
    uint32_t : 32;    // offset 0x3e0UL
    uint32_t : 32;    // offset 0x3e4UL
    uint32_t : 32;    // offset 0x3e8UL
    uint32_t : 32;    // offset 0x3ecUL
    uint32_t : 32;    // offset 0x3f0UL
    uint32_t : 32;    // offset 0x3f4UL
    uint32_t : 32;    // offset 0x3f8UL
    uint32_t : 32;    // offset 0x3fcUL
    //+=MEMORY======================================+
};
// Ensure the structure is in standard layout format
static_assert(std::is_standard_layout<SystemConfiguration>::value, "Must be standard layout");
// Ensure the offsets are all correct
static_assert(offsetof(SystemConfiguration, peripheral_mode_control) == 0x4UL, "Must be located at this offset");
static_assert(offsetof(SystemConfiguration, external_interrupt_configuration1) == 0x8UL, "Must be located at this offset");
static_assert(offsetof(SystemConfiguration, external_interrupt_configuration2) == 0xcUL, "Must be located at this offset");
static_assert(offsetof(SystemConfiguration, external_interrupt_configuration3) == 0x10UL, "Must be located at this offset");
static_assert(offsetof(SystemConfiguration, external_interrupt_configuration4) == 0x14UL, "Must be located at this offset");
static_assert(offsetof(SystemConfiguration, compensation_cell_code_selection) == 0x20UL, "Must be located at this offset");
static_assert(offsetof(SystemConfiguration, compensation_cell_value) == 0x24UL, "Must be located at this offset");
static_assert(offsetof(SystemConfiguration, compensation_cell_control) == 0x28UL, "Must be located at this offset");
static_assert(offsetof(SystemConfiguration, power_control) == 0x2cUL, "Must be located at this offset");
static_assert(offsetof(SystemConfiguration, package) == 0x124UL, "Must be located at this offset");
static_assert(offsetof(SystemConfiguration, user0) == 0x300UL, "Must be located at this offset");
static_assert(offsetof(SystemConfiguration, user2) == 0x308UL, "Must be located at this offset");
static_assert(offsetof(SystemConfiguration, user3) == 0x30cUL, "Must be located at this offset");
static_assert(offsetof(SystemConfiguration, user4) == 0x310UL, "Must be located at this offset");
static_assert(offsetof(SystemConfiguration, user5) == 0x314UL, "Must be located at this offset");
static_assert(offsetof(SystemConfiguration, user6) == 0x318UL, "Must be located at this offset");
static_assert(offsetof(SystemConfiguration, user7) == 0x31cUL, "Must be located at this offset");
static_assert(offsetof(SystemConfiguration, user8) == 0x320UL, "Must be located at this offset");
static_assert(offsetof(SystemConfiguration, user9) == 0x324UL, "Must be located at this offset");
static_assert(offsetof(SystemConfiguration, user10) == 0x328UL, "Must be located at this offset");
static_assert(offsetof(SystemConfiguration, user11) == 0x32cUL, "Must be located at this offset");
static_assert(offsetof(SystemConfiguration, user12) == 0x330UL, "Must be located at this offset");
static_assert(offsetof(SystemConfiguration, user13) == 0x334UL, "Must be located at this offset");
static_assert(offsetof(SystemConfiguration, user14) == 0x338UL, "Must be located at this offset");
static_assert(offsetof(SystemConfiguration, user15) == 0x33cUL, "Must be located at this offset");
static_assert(offsetof(SystemConfiguration, user16) == 0x340UL, "Must be located at this offset");
static_assert(offsetof(SystemConfiguration, user17) == 0x344UL, "Must be located at this offset");

// Ensure the sizeof the entire structure is correct.
static_assert(sizeof(SystemConfiguration) == 0x400UL, "Must be this exact size");

/// The external volatile system_configuration which is a memory mapped register or peripheral.
/// @note The address of the peripheral is set either by the linkerscript or by a unit test.
extern SystemConfiguration volatile system_configuration;
}    // namespace h7xx
}    // namespace stm32
#endif    // STM32_H7XX_SYSTEMCONFIGURATION__HPP_

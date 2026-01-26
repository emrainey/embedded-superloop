#ifndef LPS35HW_HPP_
#define LPS35HW_HPP_

/// @file
/// LPS35HW Pressure Sensor Register Definitions

#include <core/Split.hpp>
#include <core/Units.hpp>
#include "core/units/MilliSeconds.hpp"

namespace lps35hw {
using core::units::operator""_C;
using core::units::operator""_hPa;
constexpr static core::units::Temperature MinimumTemperature = 0.0_C;     ///< The minimum temperature the LPS35HW can measure
constexpr static core::units::Temperature MaximumTemperature = 65.0_C;    ///< The maximum temperature the LPS35HW can measure
constexpr static core::units::Pressure MinimumPressure = 260.0_hPa;       ///< The minimum pressure the LPS35HW can measure
constexpr static core::units::Pressure MaximumPressure = 1260.0_hPa;      ///< The maximum pressure the LPS35HW can measure
using RawPressure = std::int32_t;                                         ///< The raw pressure value returned by the LPS35HW
using RawTemperature = std::uint16_t;                                     ///< The raw temperature value returned by the LPS35HW
constexpr static std::uint8_t WhoAmI = 0xB1;                              ///< The value of the WHO_AM_I register for the LPS35HW

union Address final {
    Address()
        : whole{0u} {}    ///< Default constructor initializes the address to 0
    Address(std::uint8_t v)
        : whole{v} {}     ///< Constructor to initialize the address from a uint8_t value
    //+=MEMORY======================================+
    struct Fields {
        std::uint8_t address : 7;    ///< The 7-bit address of the LPS35HW
        std::uint8_t read    : 1;    ///< The read/write bit (1 for read, 0 for write)
    } bits;                          ///< The bitfields for the address
    std::uint8_t whole;              ///< The whole address byte
    //+=MEMORY======================================+
};
static_assert(sizeof(Address) == 1UL, "Address must be 1 byte in size");

constexpr static core::units::MilliSeconds DefaultPollingInterval{50U};    ///< The default polling interval for the LPS35HW
/// The largest transaction size for the LPS35HW over SPI (1 address byte + 1U spacer + 4 data bytes)
constexpr static size_t LargestTransactionSize{16U};

/// Convert the raw pressure value to a Pressure object in Pascals (not hPa)
constexpr core::units::Pressure Convert(RawPressure raw_pressure) {
    return core::units::Pressure{static_cast<float>(raw_pressure) * 100.0f / 4096.0f};    // convert to from hPa to Pa
}

/// Convert the raw temperature value to a Temperature object
constexpr core::units::Temperature Convert(RawTemperature raw_temperature) {
    return core::units::Temperature{static_cast<float>(raw_temperature) / 100.0f};
}
/// LPS35HW pressure sensor
struct RegisterSet final {
    /// Interrupt configuration register (INTERRUPT_CFG)
    struct InterruptConfig final {
        /// Default Constructor
        InterruptConfig()
            : whole{0u} {}
        /// Copy Constructor from volatile
        InterruptConfig(InterruptConfig volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        InterruptConfig(InterruptConfig const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        InterruptConfig(InterruptConfig&&) = delete;
        /// Parameterized Constructor for constant references
        explicit InterruptConfig(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit InterruptConfig(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~InterruptConfig() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Pressure High Threshold Enable (PHE)
            uint8_t pressure_high_threshold_enable : 1;    // bit 0
            /// Pressure Low Threshold Enable (PLE)
            uint8_t pressure_low_threshold_enable  : 1;    // bit 1
            /// Latch Interrupt Enable (LIR)
            uint8_t latch_interrupt_enable         : 1;    // bit 2
            /// Interrupt Generation Enable (DIFF_EN)
            uint8_t diff_enable                    : 1;    // bit 3
            /// Reset Auto Zero Function (RESET_AZ)
            uint8_t reset_auto_zero                : 1;    // bit 4
            /// Auto Zero Enable (AUTOZERO)
            uint8_t auto_zero                      : 1;    // bit 5
            /// Reset AutoPifP function (RESET_ARP)
            uint8_t reset_auto_rifp                : 1;    // bit 6
            /// AutoRifP Enable (AUTORIFP)
            uint8_t auto_rifp                      : 1;    // bit 7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        InterruptConfig& operator=(InterruptConfig&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(InterruptConfig volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(InterruptConfig const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint8_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint8_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint8_t.
        inline explicit operator uint8_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint8_t
        inline explicit operator uint8_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<InterruptConfig>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(InterruptConfig) == 1UL, "Must be this exact size");
    /// Pressure Low threshold register (THS_P_L)
    struct PressureLowThreshold final {
        /// Default Constructor
        PressureLowThreshold()
            : whole{0u} {}
        /// Copy Constructor from volatile
        PressureLowThreshold(PressureLowThreshold volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        PressureLowThreshold(PressureLowThreshold const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        PressureLowThreshold(PressureLowThreshold&&) = delete;
        /// Parameterized Constructor for constant references
        explicit PressureLowThreshold(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit PressureLowThreshold(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~PressureLowThreshold() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Low threshold pressure (PTL)
            uint8_t threshold : 8;    // bits 0:7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        PressureLowThreshold& operator=(PressureLowThreshold&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PressureLowThreshold volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PressureLowThreshold const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint8_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint8_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint8_t.
        inline explicit operator uint8_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint8_t
        inline explicit operator uint8_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<PressureLowThreshold>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(PressureLowThreshold) == 1UL, "Must be this exact size");
    /// Pressure high threshold register (THS_P_H)
    struct PressureHighThreshold final {
        /// Default Constructor
        PressureHighThreshold()
            : whole{0u} {}
        /// Copy Constructor from volatile
        PressureHighThreshold(PressureHighThreshold volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        PressureHighThreshold(PressureHighThreshold const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        PressureHighThreshold(PressureHighThreshold&&) = delete;
        /// Parameterized Constructor for constant references
        explicit PressureHighThreshold(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit PressureHighThreshold(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~PressureHighThreshold() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// High threshold pressure (PTH)
            uint8_t threshold : 8;    // bits 0:7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        PressureHighThreshold& operator=(PressureHighThreshold&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PressureHighThreshold volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PressureHighThreshold const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint8_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint8_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint8_t.
        inline explicit operator uint8_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint8_t
        inline explicit operator uint8_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<PressureHighThreshold>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(PressureHighThreshold) == 1UL, "Must be this exact size");
    /// Identification register (WHO_AM_I)
    struct WhoAmI final {
        /// Default Constructor
        WhoAmI()
            : whole{0u} {}
        /// Copy Constructor from volatile
        WhoAmI(WhoAmI volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        WhoAmI(WhoAmI const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        WhoAmI(WhoAmI&&) = delete;
        /// Parameterized Constructor for constant references
        explicit WhoAmI(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit WhoAmI(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~WhoAmI() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Identification (ID)
            uint8_t id : 8;    // bits 0:7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        WhoAmI& operator=(WhoAmI&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(WhoAmI volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(WhoAmI const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint8_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint8_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint8_t.
        inline explicit operator uint8_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint8_t
        inline explicit operator uint8_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<WhoAmI>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(WhoAmI) == 1UL, "Must be this exact size");
    /// Control register 1 (CTRL_REG1)
    struct ControlReg1 final {
        /// Default Constructor
        ControlReg1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ControlReg1(ControlReg1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ControlReg1(ControlReg1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ControlReg1(ControlReg1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ControlReg1(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ControlReg1(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ControlReg1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Serial Interface Mode (SIM)
            uint8_t serial_interface_mode  : 1;    // bit 0
            /// Block Data Update (BDU)
            uint8_t block_data_update      : 1;    // bit 1
            /// Low Pass Configuration (LPF_CFG)
            uint8_t low_pass_configuration : 2;    // bits 2:3
            /// Enable Low Pass Filter (EN_LPF)
            uint8_t enable_low_pass_filter : 1;    // bit 4
            /// Output Data Rate (ODR)
            uint8_t output_data_rate       : 3;    // bits 5:7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ControlReg1& operator=(ControlReg1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ControlReg1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ControlReg1 const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint8_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint8_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint8_t.
        inline explicit operator uint8_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint8_t
        inline explicit operator uint8_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<ControlReg1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ControlReg1) == 1UL, "Must be this exact size");
    /// Control register 2 (CTRL_REG2)
    struct ControlReg2 final {
        /// Default Constructor
        ControlReg2()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ControlReg2(ControlReg2 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ControlReg2(ControlReg2 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ControlReg2(ControlReg2&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ControlReg2(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ControlReg2(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ControlReg2() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// One Shot Mode (ONE_SHOT)
            uint8_t one_shot_enable        : 1;    // bit 0
            /// (reserved)
            uint8_t                        : 1;    // bit 1
            /// Software Reset (SW_RESET)
            uint8_t software_reset         : 1;    // bit 2
            /// I2C Disable (I2C_DISABLE)
            uint8_t i2c_disable            : 1;    // bits 3:4
            /// Auto Increment (IF_ADD_INC)
            uint8_t auto_increment         : 1;    // bit 4
            /// Stop on Fifo Threshold
            uint8_t stop_on_fifo_threshold : 1;    // bit 5
            /// FIFO Enable (FIFO_EN)
            uint8_t fifo_enable            : 1;    // bit 6
            /// Reboot Memory Content (BOOT)
            uint8_t reboot_memory_content  : 1;    // bit 7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ControlReg2& operator=(ControlReg2&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ControlReg2 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ControlReg2 const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint8_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint8_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint8_t.
        inline explicit operator uint8_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint8_t
        inline explicit operator uint8_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<ControlReg2>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ControlReg2) == 1UL, "Must be this exact size");
    /// Control register 2 (CTRL_REG2)
    struct ControlReg3 final {
        /// Default Constructor
        ControlReg3()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ControlReg3(ControlReg3 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ControlReg3(ControlReg3 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ControlReg3(ControlReg3&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ControlReg3(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ControlReg3(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ControlReg3() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Interrupt Data Ready Setting (INT_S[2])
            uint8_t interrupt_data_ready_setting : 2;    // bits 0:1
            /// Data Ready (DRDY)
            uint8_t data_ready                   : 1;    // bit 2
            /// FIFO Overrun (FIFO_OVR)
            uint8_t fifo_overrun                 : 1;    // bit 3
            /// FIFO Threshold (FIFO_THS)
            uint8_t fifo_threshold               : 1;    // bit 4
            /// FIFO Full (FIFO_FULL)
            uint8_t fifo_full                    : 1;    // bit 5
            /// PushPullPad (PP_OD)
            uint8_t push_pull_pad                : 1;    // bit 6
            /// Interrupt Active High/Low (INT_H_L)
            uint8_t interrupt_level              : 1;    // bit 7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ControlReg3& operator=(ControlReg3&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ControlReg3 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ControlReg3 const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint8_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint8_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint8_t.
        inline explicit operator uint8_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint8_t
        inline explicit operator uint8_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<ControlReg3>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ControlReg3) == 1UL, "Must be this exact size");
    /// Fifo Control register (FIFO_CTRL)
    struct FifoControl final {
        /// Default Constructor
        FifoControl()
            : whole{0u} {}
        /// Copy Constructor from volatile
        FifoControl(FifoControl volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        FifoControl(FifoControl const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        FifoControl(FifoControl&&) = delete;
        /// Parameterized Constructor for constant references
        explicit FifoControl(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit FifoControl(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~FifoControl() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Fifo Watermark Level (WTM)
            uint8_t fifo_watermark_level : 5;    // bits 0:4
            /// Fifo Mode (F_MODE)
            uint8_t fifo_mode            : 3;    // bits 5:7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        FifoControl& operator=(FifoControl&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(FifoControl volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(FifoControl const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint8_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint8_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint8_t.
        inline explicit operator uint8_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint8_t
        inline explicit operator uint8_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<FifoControl>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(FifoControl) == 1UL, "Must be this exact size");
    /// Reference Pressure Extended Low register (REF_P_XL)
    struct ReferencePressureExtendedLow final {
        /// Default Constructor
        ReferencePressureExtendedLow()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ReferencePressureExtendedLow(ReferencePressureExtendedLow volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ReferencePressureExtendedLow(ReferencePressureExtendedLow const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ReferencePressureExtendedLow(ReferencePressureExtendedLow&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ReferencePressureExtendedLow(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ReferencePressureExtendedLow(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ReferencePressureExtendedLow() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Lowest Order Byte of Reference Pressure (REF_P_XL)
            uint8_t reference_extended_low : 8;    // bits 0:7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ReferencePressureExtendedLow& operator=(ReferencePressureExtendedLow&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ReferencePressureExtendedLow volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ReferencePressureExtendedLow const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint8_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint8_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint8_t.
        inline explicit operator uint8_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint8_t
        inline explicit operator uint8_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<ReferencePressureExtendedLow>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ReferencePressureExtendedLow) == 1UL, "Must be this exact size");
    /// Reference Pressure Low register (REF_P_L)
    struct ReferencePressureLow final {
        /// Default Constructor
        ReferencePressureLow()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ReferencePressureLow(ReferencePressureLow volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ReferencePressureLow(ReferencePressureLow const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ReferencePressureLow(ReferencePressureLow&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ReferencePressureLow(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ReferencePressureLow(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ReferencePressureLow() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Lowest Order Byte of Reference Pressure (REF_P_L)
            uint8_t reference_low : 8;    // bits 0:7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ReferencePressureLow& operator=(ReferencePressureLow&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ReferencePressureLow volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ReferencePressureLow const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint8_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint8_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint8_t.
        inline explicit operator uint8_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint8_t
        inline explicit operator uint8_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<ReferencePressureLow>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ReferencePressureLow) == 1UL, "Must be this exact size");
    /// Reference Pressure High register (REF_P_H)
    struct ReferencePressureHigh final {
        /// Default Constructor
        ReferencePressureHigh()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ReferencePressureHigh(ReferencePressureHigh volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ReferencePressureHigh(ReferencePressureHigh const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ReferencePressureHigh(ReferencePressureHigh&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ReferencePressureHigh(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ReferencePressureHigh(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ReferencePressureHigh() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Lowest Order Byte of Reference Pressure (REF_P_H)
            uint8_t reference_high : 8;    // bits 0:7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ReferencePressureHigh& operator=(ReferencePressureHigh&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ReferencePressureHigh volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ReferencePressureHigh const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint8_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint8_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint8_t.
        inline explicit operator uint8_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint8_t
        inline explicit operator uint8_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<ReferencePressureHigh>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ReferencePressureHigh) == 1UL, "Must be this exact size");
    /// Pressure Offset Low (RPDS_L)
    struct PressureOffsetLow final {
        /// Default Constructor
        PressureOffsetLow()
            : whole{0u} {}
        /// Copy Constructor from volatile
        PressureOffsetLow(PressureOffsetLow volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        PressureOffsetLow(PressureOffsetLow const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        PressureOffsetLow(PressureOffsetLow&&) = delete;
        /// Parameterized Constructor for constant references
        explicit PressureOffsetLow(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit PressureOffsetLow(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~PressureOffsetLow() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Lowest Order Byte of Pressure Offset (RPDS_L)
            uint8_t pressure_offset_low : 8;    // bits 0:7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        PressureOffsetLow& operator=(PressureOffsetLow&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PressureOffsetLow volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PressureOffsetLow const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint8_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint8_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint8_t.
        inline explicit operator uint8_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint8_t
        inline explicit operator uint8_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<PressureOffsetLow>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(PressureOffsetLow) == 1UL, "Must be this exact size");
    /// Pressure Offset High (RPDS_H)
    struct PressureOffsetHigh final {
        /// Default Constructor
        PressureOffsetHigh()
            : whole{0u} {}
        /// Copy Constructor from volatile
        PressureOffsetHigh(PressureOffsetHigh volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        PressureOffsetHigh(PressureOffsetHigh const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        PressureOffsetHigh(PressureOffsetHigh&&) = delete;
        /// Parameterized Constructor for constant references
        explicit PressureOffsetHigh(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit PressureOffsetHigh(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~PressureOffsetHigh() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Lowest Order Byte of Pressure Offset (RPDS_H)
            uint8_t pressure_offset_high : 8;    // bits 0:7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        PressureOffsetHigh& operator=(PressureOffsetHigh&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PressureOffsetHigh volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PressureOffsetHigh const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint8_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint8_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint8_t.
        inline explicit operator uint8_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint8_t
        inline explicit operator uint8_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<PressureOffsetHigh>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(PressureOffsetHigh) == 1UL, "Must be this exact size");
    /// Low Power Mode Configuration (RES_CONF)
    struct LowPowerModeConfiguration final {
        /// Default Constructor
        LowPowerModeConfiguration()
            : whole{0u} {}
        /// Copy Constructor from volatile
        LowPowerModeConfiguration(LowPowerModeConfiguration volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        LowPowerModeConfiguration(LowPowerModeConfiguration const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        LowPowerModeConfiguration(LowPowerModeConfiguration&&) = delete;
        /// Parameterized Constructor for constant references
        explicit LowPowerModeConfiguration(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit LowPowerModeConfiguration(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~LowPowerModeConfiguration() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Low Current Mode (LC_EN)
            uint8_t low_current_mode_enabled : 1;    // bit 0
            /// (reserved)
            uint8_t                          : 7;    // bits 1:7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        LowPowerModeConfiguration& operator=(LowPowerModeConfiguration&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(LowPowerModeConfiguration volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(LowPowerModeConfiguration const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint8_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint8_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint8_t.
        inline explicit operator uint8_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint8_t
        inline explicit operator uint8_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<LowPowerModeConfiguration>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(LowPowerModeConfiguration) == 1UL, "Must be this exact size");
    /// Interrupt Source Register (INT_SOURCE)
    struct InterruptSource final {
        /// Default Constructor
        InterruptSource()
            : whole{0u} {}
        /// Copy Constructor from volatile
        InterruptSource(InterruptSource volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        InterruptSource(InterruptSource const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        InterruptSource(InterruptSource&&) = delete;
        /// Parameterized Constructor for constant references
        explicit InterruptSource(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit InterruptSource(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~InterruptSource() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Differential Pressure High Interrupt Enabled
            uint8_t differential_pressure_high_interrupt : 1;    // bit 0
            /// Differential Pressure Low Interrupt Enabled
            uint8_t differential_pressure_low_interrupt  : 1;    // bit 1
            /// Interrupt Active
            uint8_t interrupt_active                     : 1;    // bit 2
            /// Boot Status (1 = rebooting, 0 = booted)
            uint8_t boot_status                          : 1;    // bit 3
            /// (reserved)
            uint8_t                                      : 4;    // bits 4:7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        InterruptSource& operator=(InterruptSource&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(InterruptSource volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(InterruptSource const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint8_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint8_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint8_t.
        inline explicit operator uint8_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint8_t
        inline explicit operator uint8_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<InterruptSource>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(InterruptSource) == 1UL, "Must be this exact size");
    /// Fifo Status register (FIFO_STATUS)
    struct FifoStatus final {
        /// Default Constructor
        FifoStatus()
            : whole{0u} {}
        /// Copy Constructor from volatile
        FifoStatus(FifoStatus volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        FifoStatus(FifoStatus const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        FifoStatus(FifoStatus&&) = delete;
        /// Parameterized Constructor for constant references
        explicit FifoStatus(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit FifoStatus(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~FifoStatus() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Fifo Stored Data Level (FSS)
            uint8_t fifo_stored_data_level : 6;    // bits 0:5
            /// Fifo Overrun (OVR
            uint8_t fifo_overrun           : 1;    // bit 6
            /// Fifo Threshold Status (FTH_FIFO)
            uint8_t fifo_threshold_status  : 1;    // bit 7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        FifoStatus& operator=(FifoStatus&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(FifoStatus volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(FifoStatus const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint8_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint8_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint8_t.
        inline explicit operator uint8_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint8_t
        inline explicit operator uint8_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<FifoStatus>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(FifoStatus) == 1UL, "Must be this exact size");
    /// Status register (STATUS)
    struct Status final {
        /// Default Constructor
        Status()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Status(Status volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Status(Status const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Status(Status&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Status(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Status(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Status() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Pressure Data Available (P_DA)
            uint8_t pressure_data_available    : 1;    // bit 0
            /// Temperature Data Available (T_DA)
            uint8_t temperature_data_available : 1;    // bit 1
            /// (reserved)
            uint8_t                            : 2;    // bits 2:3
            /// Pressure Data Overrun (P_OR)
            uint8_t pressure_data_overrun      : 1;    // bit 4
            /// Temperature Data Overrun (T_OR)
            uint8_t temperature_data_overrun   : 1;    // bit 5
            /// (reserved)
            uint8_t                            : 2;    // bits 6:7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Status& operator=(Status&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Status volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Status const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint8_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint8_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint8_t.
        inline explicit operator uint8_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint8_t
        inline explicit operator uint8_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<Status>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Status) == 1UL, "Must be this exact size");
    /// Pressure Xtra Low register (PRESS_OUT_XL)
    struct PressureOutputExtendedLow final {
        /// Default Constructor
        PressureOutputExtendedLow()
            : whole{0u} {}
        /// Copy Constructor from volatile
        PressureOutputExtendedLow(PressureOutputExtendedLow volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        PressureOutputExtendedLow(PressureOutputExtendedLow const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        PressureOutputExtendedLow(PressureOutputExtendedLow&&) = delete;
        /// Parameterized Constructor for constant references
        explicit PressureOutputExtendedLow(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit PressureOutputExtendedLow(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~PressureOutputExtendedLow() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Pressure output (PRESS_OUT_XL)
            uint8_t raw_pressure_extended_low : 8;    // bits 0:7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        PressureOutputExtendedLow& operator=(PressureOutputExtendedLow&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PressureOutputExtendedLow volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PressureOutputExtendedLow const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint8_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint8_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint8_t.
        inline explicit operator uint8_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint8_t
        inline explicit operator uint8_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<PressureOutputExtendedLow>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(PressureOutputExtendedLow) == 1UL, "Must be this exact size");
    /// Pressure Low register (PRESS_OUT_L)
    struct PressureOutputLow final {
        /// Default Constructor
        PressureOutputLow()
            : whole{0u} {}
        /// Copy Constructor from volatile
        PressureOutputLow(PressureOutputLow volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        PressureOutputLow(PressureOutputLow const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        PressureOutputLow(PressureOutputLow&&) = delete;
        /// Parameterized Constructor for constant references
        explicit PressureOutputLow(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit PressureOutputLow(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~PressureOutputLow() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Pressure output (PRESS_OUT_L)
            uint8_t raw_pressure_low : 8;    // bits 0:7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        PressureOutputLow& operator=(PressureOutputLow&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PressureOutputLow volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PressureOutputLow const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint8_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint8_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint8_t.
        inline explicit operator uint8_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint8_t
        inline explicit operator uint8_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<PressureOutputLow>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(PressureOutputLow) == 1UL, "Must be this exact size");
    /// Pressure High register (PRESS_OUT_H)
    struct PressureOutputHigh final {
        /// Default Constructor
        PressureOutputHigh()
            : whole{0u} {}
        /// Copy Constructor from volatile
        PressureOutputHigh(PressureOutputHigh volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        PressureOutputHigh(PressureOutputHigh const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        PressureOutputHigh(PressureOutputHigh&&) = delete;
        /// Parameterized Constructor for constant references
        explicit PressureOutputHigh(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit PressureOutputHigh(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~PressureOutputHigh() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Pressure output (PRESS_OUT_H)
            uint8_t raw_pressure_high : 8;    // bits 0:7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        PressureOutputHigh& operator=(PressureOutputHigh&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PressureOutputHigh volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PressureOutputHigh const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint8_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint8_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint8_t.
        inline explicit operator uint8_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint8_t
        inline explicit operator uint8_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<PressureOutputHigh>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(PressureOutputHigh) == 1UL, "Must be this exact size");
    /// Temperature Low register (TEMP_OUT_L)
    struct TemperatureOutputLow final {
        /// Default Constructor
        TemperatureOutputLow()
            : whole{0u} {}
        /// Copy Constructor from volatile
        TemperatureOutputLow(TemperatureOutputLow volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        TemperatureOutputLow(TemperatureOutputLow const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        TemperatureOutputLow(TemperatureOutputLow&&) = delete;
        /// Parameterized Constructor for constant references
        explicit TemperatureOutputLow(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit TemperatureOutputLow(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~TemperatureOutputLow() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Temperature output (TEMP_OUT_L)
            uint8_t raw_temperature_low : 8;    // bits 0:7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        TemperatureOutputLow& operator=(TemperatureOutputLow&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(TemperatureOutputLow volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(TemperatureOutputLow const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint8_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint8_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint8_t.
        inline explicit operator uint8_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint8_t
        inline explicit operator uint8_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<TemperatureOutputLow>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(TemperatureOutputLow) == 1UL, "Must be this exact size");
    /// Temperature High register (TEMP_OUT_H)
    struct TemperatureOutputHigh final {
        /// Default Constructor
        TemperatureOutputHigh()
            : whole{0u} {}
        /// Copy Constructor from volatile
        TemperatureOutputHigh(TemperatureOutputHigh volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        TemperatureOutputHigh(TemperatureOutputHigh const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        TemperatureOutputHigh(TemperatureOutputHigh&&) = delete;
        /// Parameterized Constructor for constant references
        explicit TemperatureOutputHigh(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit TemperatureOutputHigh(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~TemperatureOutputHigh() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Temperature output (TEMP_OUT_H)
            uint8_t raw_temperature_high : 8;    // bits 0:7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        TemperatureOutputHigh& operator=(TemperatureOutputHigh&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(TemperatureOutputHigh volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(TemperatureOutputHigh const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint8_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint8_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint8_t.
        inline explicit operator uint8_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint8_t
        inline explicit operator uint8_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<TemperatureOutputHigh>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(TemperatureOutputHigh) == 1UL, "Must be this exact size");
    /// Low Pass Filter Reset register (LPFP_RES)
    struct LowPassFilterReset final {
        /// Default Constructor
        LowPassFilterReset()
            : whole{0u} {}
        /// Copy Constructor from volatile
        LowPassFilterReset(LowPassFilterReset volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        LowPassFilterReset(LowPassFilterReset const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        LowPassFilterReset(LowPassFilterReset&&) = delete;
        /// Parameterized Constructor for constant references
        explicit LowPassFilterReset(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit LowPassFilterReset(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~LowPassFilterReset() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Low Pass Filter Reset (LPFP_RST)
            uint8_t read_to_reset : 8;    // bits 0:7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        LowPassFilterReset& operator=(LowPassFilterReset&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(LowPassFilterReset volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(LowPassFilterReset const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint8_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint8_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint8_t.
        inline explicit operator uint8_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint8_t
        inline explicit operator uint8_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<LowPassFilterReset>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(LowPassFilterReset) == 1UL, "Must be this exact size");

    //+=MEMORY======================================+
    uint8_t : 8;    // offset 0x0UL
    uint8_t : 8;    // offset 0x1UL
    uint8_t : 8;    // offset 0x2UL
    uint8_t : 8;    // offset 0x3UL
    uint8_t : 8;    // offset 0x4UL
    uint8_t : 8;    // offset 0x5UL
    uint8_t : 8;    // offset 0x6UL
    uint8_t : 8;    // offset 0x7UL
    uint8_t : 8;    // offset 0x8UL
    uint8_t : 8;    // offset 0x9UL
    uint8_t : 8;    // offset 0xaUL
    /// Interrupt configuration register (INTERRUPT_CFG)
    InterruptConfig interrupt_cfg;    // offset 0xbUL
    /// Pressure threshold low register (THS_P_L)
    PressureLowThreshold low_threshold;    // offset 0xcUL
    /// Pressure threshold high register (THS_P_H)
    PressureHighThreshold high_threshold;    // offset 0xdUL
    uint8_t : 8;                             // offset 0xeUL
    /// Identification register (WHO_AM_I)
    WhoAmI who_am_i;    // offset 0xfUL
    /// Control register 1 (CTRL_REG1)
    ControlReg1 control_reg1;    // offset 0x10UL
    /// Control register 2 (CTRL_REG2)
    ControlReg2 control_reg2;    // offset 0x11UL
    /// Control register 3 (CTRL_REG3)
    ControlReg3 control_reg3;    // offset 0x12UL
    uint8_t : 8;                 // offset 0x13UL
    /// Fifo control register (FIFO_CTRL)
    FifoControl fifo_control;    // offset 0x14UL
    /// Reference pressure extended low register (REF_P_XL)
    ReferencePressureExtendedLow reference_extended_low;    // offset 0x15UL
    /// Reference pressure low register (REF_P_L)
    ReferencePressureLow reference_low;    // offset 0x16UL
    /// Reference pressure high register (REF_P_H)
    ReferencePressureHigh reference_high;    // offset 0x17UL
    /// Pressure offset low register (RPDS_L)
    PressureOffsetLow pressure_offset_low;    // offset 0x18UL
    /// Pressure offset high register (RPDS_H)
    PressureOffsetHigh pressure_offset_high;    // offset 0x19UL
    /// Low Power Mode Configuration register (RES_CONF)
    LowPowerModeConfiguration low_power_mode;    // offset 0x1aUL
    uint8_t : 8;                                 // offset 0x1bUL
    uint8_t : 8;                                 // offset 0x1cUL
    uint8_t : 8;                                 // offset 0x1dUL
    uint8_t : 8;                                 // offset 0x1eUL
    uint8_t : 8;                                 // offset 0x1fUL
    uint8_t : 8;                                 // offset 0x20UL
    uint8_t : 8;                                 // offset 0x21UL
    uint8_t : 8;                                 // offset 0x22UL
    uint8_t : 8;                                 // offset 0x23UL
    uint8_t : 8;                                 // offset 0x24UL
    /// Interrupt source register (INT_SOURCE)
    InterruptSource interrupt_source;    // offset 0x25UL
    /// Fifo status register (FIFO_STATUS)
    FifoStatus fifo_status;    // offset 0x26UL
    /// Status register (STATUS)
    Status status;    // offset 0x27UL
    /// Pressure output register (PRESS_OUT_XL)
    PressureOutputExtendedLow pressure_output_extended_low;    // offset 0x28UL
    /// Pressure output register (PRESS_OUT_L)
    PressureOutputLow pressure_output_low;    // offset 0x29UL
    /// Pressure output register (PRESS_OUT_H)
    PressureOutputHigh pressure_output_high;    // offset 0x2aUL
    /// Temperature output register (TEMP_OUT_L)
    TemperatureOutputLow temperature_output_low;    // offset 0x2bUL
    /// Temperature output register (TEMP_OUT_H)
    TemperatureOutputHigh temperature_output_high;    // offset 0x2cUL
    uint8_t : 8;                                      // offset 0x2dUL
    uint8_t : 8;                                      // offset 0x2eUL
    uint8_t : 8;                                      // offset 0x2fUL
    uint8_t : 8;                                      // offset 0x30UL
    uint8_t : 8;                                      // offset 0x31UL
    uint8_t : 8;                                      // offset 0x32UL
    /// Low Pass Filter Reset register (LPFP_RES)
    LowPassFilterReset low_pass_filter_reset;    // offset 0x33UL
    //+=MEMORY======================================+
};
// Ensure the structure is in standard layout format
static_assert(std::is_standard_layout<RegisterSet>::value, "Must be standard layout");
// Ensure the offsets are all correct
static_assert(offsetof(RegisterSet, interrupt_cfg) == 0xbUL, "Must be located at this offset");
static_assert(offsetof(RegisterSet, low_threshold) == 0xcUL, "Must be located at this offset");
static_assert(offsetof(RegisterSet, high_threshold) == 0xdUL, "Must be located at this offset");
static_assert(offsetof(RegisterSet, who_am_i) == 0xfUL, "Must be located at this offset");
static_assert(offsetof(RegisterSet, control_reg1) == 0x10UL, "Must be located at this offset");
static_assert(offsetof(RegisterSet, control_reg2) == 0x11UL, "Must be located at this offset");
static_assert(offsetof(RegisterSet, control_reg3) == 0x12UL, "Must be located at this offset");
static_assert(offsetof(RegisterSet, fifo_control) == 0x14UL, "Must be located at this offset");
static_assert(offsetof(RegisterSet, reference_extended_low) == 0x15UL, "Must be located at this offset");
static_assert(offsetof(RegisterSet, reference_low) == 0x16UL, "Must be located at this offset");
static_assert(offsetof(RegisterSet, reference_high) == 0x17UL, "Must be located at this offset");
static_assert(offsetof(RegisterSet, pressure_offset_low) == 0x18UL, "Must be located at this offset");
static_assert(offsetof(RegisterSet, pressure_offset_high) == 0x19UL, "Must be located at this offset");
static_assert(offsetof(RegisterSet, low_power_mode) == 0x1aUL, "Must be located at this offset");
static_assert(offsetof(RegisterSet, interrupt_source) == 0x25UL, "Must be located at this offset");
static_assert(offsetof(RegisterSet, fifo_status) == 0x26UL, "Must be located at this offset");
static_assert(offsetof(RegisterSet, status) == 0x27UL, "Must be located at this offset");
static_assert(offsetof(RegisterSet, pressure_output_extended_low) == 0x28UL, "Must be located at this offset");
static_assert(offsetof(RegisterSet, pressure_output_low) == 0x29UL, "Must be located at this offset");
static_assert(offsetof(RegisterSet, pressure_output_high) == 0x2aUL, "Must be located at this offset");
static_assert(offsetof(RegisterSet, temperature_output_low) == 0x2bUL, "Must be located at this offset");
static_assert(offsetof(RegisterSet, temperature_output_high) == 0x2cUL, "Must be located at this offset");
static_assert(offsetof(RegisterSet, low_pass_filter_reset) == 0x33UL, "Must be located at this offset");

// Ensure the sizeof the entire structure is correct.
static_assert(sizeof(RegisterSet) == 0x34UL, "Must be this exact size");

}    // namespace lps35hw

#endif    // LPS35HW_HPP_

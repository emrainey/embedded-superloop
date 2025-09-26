#ifndef LSM9DS1_HPP
#define LSM9DS1_HPP

/// @file
/// The LSM9DS1 9-DOF Sensor Header

#include <core/Units.hpp>
#include <cstdint>

namespace lsm9ds1 {
using core::units::operator""_g;
using core::units::operator""_C;
using core::units::operator""_G;
constexpr static core::units::Acceleration MinimumAcceleration = -16.0_g;    ///< The minimum acceleration value in g
constexpr static core::units::Acceleration MaximumAcceleration = 16.0_g;     ///< The maximum acceleration value in g
constexpr static core::units::Temperature MinimumTemperature = -40.0_C;      ///< The minimum temperature value in Celsius
constexpr static core::units::Temperature MaximumTemperature = 85.0_C;       ///< The maximum temperature value in Celsius
constexpr static core::units::Gauss MinimumMagneticField = -8.0_G;           ///< The minimum magnetic field value in Gauss
constexpr static core::units::Gauss MaximumMagneticField = 8.0_G;            ///< The maximum magnetic field value in Gauss
constexpr static size_t LargestTransactionSize{16U};                         ///< The largest transactions (send + recv) to the chip

constexpr static core::units::MilliSeconds DefaultPollingInterval{8U};       ///< The default polling interval for the LSM9DS1 at 120Hz

/// Allows for easy access to the individual bytes of a 16-bit word
union word final {
    std::uint16_t as_u16[1];
    std::int16_t as_s16[1];
    std::uint8_t as_u08[2];
};

namespace acceleration {
using Raw = std::int16_t;    ///< The raw acceleration type returned by the LSM9DS1
constexpr float Sensitivity(int scale) {
    if (scale == 2) {
        return 0.000061f;    // 2g scale
    } else if (scale == 4) {
        return 0.000122f;    // 4g scale
    } else if (scale == 8) {
        return 0.000244f;    // 8g scale
    } else if (scale == 16) {
        return 0.000732f;    // 16g scale
    }
    return 0.0f;
}

/// Convert the raw g's value to an Acceleration object in "g"s using a scaling factor
constexpr core::units::Acceleration Convert(Raw raw_acceleration, float sensitivity) {
    return core::units::Acceleration{static_cast<float>(raw_acceleration) * sensitivity};
}

}    // namespace acceleration

namespace magnetic_field {
using Raw = std::int16_t;    ///< The raw magnetic field type returned by the LSM9DS1
constexpr float Sensitivity(int scale) {
    if (scale == 4) {
        return 0.00014f;
    } else if (scale == 8) {
        return 0.00029f;
    } else if (scale == 12) {
        return 0.00043f;
    } else if (scale == 16) {
        return 0.00058f;
    }
    return 0.0f;
}

/// Convert the raw magnetic field value to a Gauss object
constexpr core::units::Gauss Convert(Raw raw_magnetic_field, float sensitivity) {
    return core::units::Gauss{static_cast<float>(raw_magnetic_field) * sensitivity};
}
}    // namespace magnetic_field

namespace gyroscope {

using Raw = std::int16_t;    ///< The raw gyroscope type returned by the LSM9DS1

constexpr float Sensitivity(int scale) {
    if (scale == 245) {
        return 0.00875f;    // 245 dps scale
    } else if (scale == 500) {
        return 0.0175f;     // 500 dps scale
    } else if (scale == 2000) {
        return 0.07f;       // 2000 dps scale
    }
    return 0.0f;
}

/// Convert the raw gyroscope value to a Ratio<Degrees, Seconds> object
constexpr core::units::Ratio<core::units::Degrees, core::units::Seconds> Convert(Raw raw_gyroscope, float sensitivity) {
    return core::units::Ratio<core::units::Degrees, core::units::Seconds>{static_cast<float>(raw_gyroscope) * sensitivity};
}

}    // namespace gyroscope

namespace temperature {

using Raw = std::int16_t;    ///< The raw temperature type returned by the LSM9DS1

/// Convert the raw temperature value to a Temperature object
constexpr core::units::Temperature Convert(Raw raw_temperature) {
    return core::units::Temperature{static_cast<float>((raw_temperature) * 0.0625f) + 25.0f};
}

}    // namespace temperature
constexpr static std::uint8_t WhoAmI = 0x68;    ///< The value of the WHO_AM_I register for the LSM9DS1

union Address final {
    Address()
        : whole{0u} {}    ///< Default constructor initializes the address to 0
    Address(std::uint8_t v)
        : whole{v} {}     ///< Constructor to initialize the address from a uint8_t value
    //+=MEMORY======================================+
    struct Fields {
        std::uint8_t address : 7;    ///< The 7-bit address of the LSM9DS1
        std::uint8_t read    : 1;    ///< The read/write bit (1 for read, 0 for write)
    } bits;                          ///< The bitfields for the address
    std::uint8_t whole;              ///< The whole address byte
    //+=MEMORY======================================+
};
static_assert(sizeof(Address) == 1UL, "Address must be 1 byte in size");

/// LSM9DS1 Gyroscope/Accelerometer Sensor
struct Accelerometer final {
    /// Activity Threshold register (ACT_THS)
    struct ActivityThreshold final {
        /// Default Constructor
        ActivityThreshold()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ActivityThreshold(ActivityThreshold volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ActivityThreshold(ActivityThreshold const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ActivityThreshold(ActivityThreshold&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ActivityThreshold(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ActivityThreshold(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ActivityThreshold() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Threshold Value
            uint8_t threshold_value            : 7;    // bits 0:6
            /// Sleep on Inactivity Enable
            uint8_t sleep_on_inactivity_enable : 1;    // bit 7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ActivityThreshold& operator=(ActivityThreshold&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ActivityThreshold volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ActivityThreshold const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ActivityThreshold>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ActivityThreshold) == 1UL, "Must be this exact size");
    /// Interrupt Generation Configuration register (INT_GEN_CFG_XL)
    struct InterruptGenerationConfigurationXL final {
        /// Default Constructor
        InterruptGenerationConfigurationXL()
            : whole{0u} {}
        /// Copy Constructor from volatile
        InterruptGenerationConfigurationXL(InterruptGenerationConfigurationXL volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        InterruptGenerationConfigurationXL(InterruptGenerationConfigurationXL const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        InterruptGenerationConfigurationXL(InterruptGenerationConfigurationXL&&) = delete;
        /// Parameterized Constructor for constant references
        explicit InterruptGenerationConfigurationXL(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit InterruptGenerationConfigurationXL(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~InterruptGenerationConfigurationXL() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Enable interrupt generation on accelerometer X-axis low event. (XLIE_XL)
            uint8_t x_low_interrupt_enable    : 1;    // bit 0
            /// Enable interrupt generation on accelerometerX-axis high event. (XHIE_XL)
            uint8_t x_high_interrupt_enable   : 1;    // bit 1
            /// Enable interrupt generation on accelerometer Y-axis low event. (YLIE_YL)
            uint8_t y_low_interrupt_enable    : 1;    // bit 2
            /// Enable interrupt generation on accelerometer Y-axis high event. (YHIE_YL)
            uint8_t y_high_interrupt_enable   : 1;    // bit 3
            /// Enable interrupt generation on accelerometer Z-axis low event. (ZLIE_ZL)
            uint8_t z_low_interrupt_enable    : 1;    // bit 4
            /// Enable interrupt generation on accelerometer Z-axis high event. (ZHIE_ZL)
            uint8_t z_high_interrupt_enable   : 1;    // bit 5
            /// Enable 6-Direction mode. (6D)
            uint8_t six_direction_mode_enable : 1;    // bit 6
            /// AND, /OR combination of accelerometer interrupt events. (AOI_XL)
            uint8_t and_or_interrupt          : 1;    // bit 7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        InterruptGenerationConfigurationXL& operator=(InterruptGenerationConfigurationXL&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(InterruptGenerationConfigurationXL volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(InterruptGenerationConfigurationXL const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<InterruptGenerationConfigurationXL>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(InterruptGenerationConfigurationXL) == 1UL, "Must be this exact size");
    /// Interrupt Generation Duration Accelerometer register (INT_GEN_DUR_XL)
    struct InterruptGenerationDurationAccelerometer final {
        /// Default Constructor
        InterruptGenerationDurationAccelerometer()
            : whole{0u} {}
        /// Copy Constructor from volatile
        InterruptGenerationDurationAccelerometer(InterruptGenerationDurationAccelerometer volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        InterruptGenerationDurationAccelerometer(InterruptGenerationDurationAccelerometer const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        InterruptGenerationDurationAccelerometer(InterruptGenerationDurationAccelerometer&&) = delete;
        /// Parameterized Constructor for constant references
        explicit InterruptGenerationDurationAccelerometer(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit InterruptGenerationDurationAccelerometer(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~InterruptGenerationDurationAccelerometer() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Duration value (DUR_XL)
            uint8_t duration : 7;    // bits 0:6
            /// Wait function enabled on duration counter (WAIT_XL)
            uint8_t wait     : 1;    // bit 7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        InterruptGenerationDurationAccelerometer& operator=(InterruptGenerationDurationAccelerometer&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(InterruptGenerationDurationAccelerometer volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(InterruptGenerationDurationAccelerometer const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<InterruptGenerationDurationAccelerometer>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(InterruptGenerationDurationAccelerometer) == 1UL, "Must be this exact size");
    /// Interrupt1AccelerometerGyroscopePinControl (INT1_AG_CTRL)
    struct Interrupt1AccelerometerGyroscopePinControl final {
        /// Default Constructor
        Interrupt1AccelerometerGyroscopePinControl()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Interrupt1AccelerometerGyroscopePinControl(Interrupt1AccelerometerGyroscopePinControl volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Interrupt1AccelerometerGyroscopePinControl(Interrupt1AccelerometerGyroscopePinControl const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Interrupt1AccelerometerGyroscopePinControl(Interrupt1AccelerometerGyroscopePinControl&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Interrupt1AccelerometerGyroscopePinControl(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Interrupt1AccelerometerGyroscopePinControl(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Interrupt1AccelerometerGyroscopePinControl() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Accelerometer data ready on INT 1_A/G pin. (INT_DRDY_XL)
            uint8_t data_ready_accelerometer : 1;    // bit 0
            /// Gyroscope data ready on INT 1_A/G pin. (INT_DRDY_G)
            uint8_t data_ready_gyroscope     : 1;    // bit 1
            /// Boot Status on data ready on INT 1_A/G pin. (INT_BOOT)
            uint8_t boot_status              : 1;    // bit 2
            /// FIFO threshold on INT 1_A/G pin. (INT_FTH)
            uint8_t fifo_threshold           : 1;    // bit 3
            /// FIFO overrun on INT 1_A/G pin. (INT_OVR)
            uint8_t fifo_overrun             : 1;    // bit 4
            /// FSS5 interrupt enable on INT 1_A/G pin. (INT_FSS5)
            uint8_t fss5                     : 1;    // bit 5
            /// Accelerometer interrupt generator on INT 1_A/G pin. (INT_ IG_XL)
            uint8_t accelerometer_interrupt  : 1;    // bit 6
            /// Gyroscope interrupt generator on INT 1_A/G pin. (INT_ IG_G)
            uint8_t gyroscope_interrupt      : 1;    // bit 7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Interrupt1AccelerometerGyroscopePinControl& operator=(Interrupt1AccelerometerGyroscopePinControl&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Interrupt1AccelerometerGyroscopePinControl volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Interrupt1AccelerometerGyroscopePinControl const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Interrupt1AccelerometerGyroscopePinControl>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Interrupt1AccelerometerGyroscopePinControl) == 1UL, "Must be this exact size");
    /// Interrupt2AccelerometerGyroscopePinControl (INT2_AG_CTRL)
    struct Interrupt2AccelerometerGyroscopePinControl final {
        /// Default Constructor
        Interrupt2AccelerometerGyroscopePinControl()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Interrupt2AccelerometerGyroscopePinControl(Interrupt2AccelerometerGyroscopePinControl volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Interrupt2AccelerometerGyroscopePinControl(Interrupt2AccelerometerGyroscopePinControl const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Interrupt2AccelerometerGyroscopePinControl(Interrupt2AccelerometerGyroscopePinControl&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Interrupt2AccelerometerGyroscopePinControl(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Interrupt2AccelerometerGyroscopePinControl(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Interrupt2AccelerometerGyroscopePinControl() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Accelerometer data ready on INT 2_A/G pin. (INT_DRDY_XL)
            uint8_t data_ready_accelerometer : 1;    // bit 0
            /// Gyroscope data ready on INT 2_A/G pin. (INT_DRDY_G)
            uint8_t data_ready_gyroscope     : 1;    // bit 1
            /// Temperature data ready on INT 2_A/G pin. (INT_DRDY_TEMP)
            uint8_t data_ready_temperature   : 1;    // bit 2
            /// FIFO threshold on INT 2_A/G pin. (INT_FTH)
            uint8_t fifo_threshold           : 1;    // bit 3
            /// FIFO overrun on INT 2_A/G pin. (INT_OVR)
            uint8_t fifo_overrun             : 1;    // bit 4
            /// FSS5 interrupt enable on INT 2_A/G pin. (INT_FSS5)
            uint8_t fss5                     : 1;    // bit 5
            /// Inactivity interrupt output signal (INT2_INACT)
            uint8_t inactivity_interrupt     : 1;    // bit 6
            /// (reserved)
            uint8_t                          : 1;    // bit 7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Interrupt2AccelerometerGyroscopePinControl& operator=(Interrupt2AccelerometerGyroscopePinControl&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Interrupt2AccelerometerGyroscopePinControl volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Interrupt2AccelerometerGyroscopePinControl const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Interrupt2AccelerometerGyroscopePinControl>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Interrupt2AccelerometerGyroscopePinControl) == 1UL, "Must be this exact size");
    /// Control register 1 Gyroscope (CTRL_REG1_G)
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
        explicit Control1(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Control1(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Control1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Bandwidth Selection
            uint8_t bandwidth_selection        : 2;    // bits 0:1
            /// (reserved)
            uint8_t                            : 1;    // bit 2
            /// Full Scale Selection
            uint8_t full_scale_selection       : 2;    // bits 3:4
            /// Output Data Rate Selection
            uint8_t output_data_rate_selection : 3;    // bits 5:7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
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
    static_assert(std::is_standard_layout<Control1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Control1) == 1UL, "Must be this exact size");
    /// Control register 2 Gyroscope (CTRL_REG2_G)
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
        explicit Control2(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Control2(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Control2() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Output Selection
            uint8_t output_selection    : 2;    // bits 0:1
            /// Interrupt Selection
            uint8_t interrupt_selection : 2;    // bits 2:3
            /// (reserved)
            uint8_t                     : 4;    // bits 4:7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
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
    static_assert(std::is_standard_layout<Control2>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Control2) == 1UL, "Must be this exact size");
    /// Control register 1 Gyroscope (CTRL_REG1_G)
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
        explicit Control3(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Control3(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Control3() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// High Pass Filter cutoff frequency selection (HPCF_G)
            uint8_t high_pass_filter_cutoff_frequency : 4;    // bits 0:3
            /// (reserved)
            uint8_t                                   : 2;    // bits 4:5
            /// High Pass Filter Enable (HP_EN)
            uint8_t high_pass_filter_enable           : 1;    // bit 6
            /// Low Power Mode Enable (LP_G)
            uint8_t low_power_mode_enable             : 1;    // bit 7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
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
    static_assert(std::is_standard_layout<Control3>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Control3) == 1UL, "Must be this exact size");
    /// Orientation Configuration Gyroscope (ORIENT_CFG_G)
    struct OrientConfigurationGyroscope final {
        /// Default Constructor
        OrientConfigurationGyroscope()
            : whole{0u} {}
        /// Copy Constructor from volatile
        OrientConfigurationGyroscope(OrientConfigurationGyroscope volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        OrientConfigurationGyroscope(OrientConfigurationGyroscope const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        OrientConfigurationGyroscope(OrientConfigurationGyroscope&&) = delete;
        /// Parameterized Constructor for constant references
        explicit OrientConfigurationGyroscope(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit OrientConfigurationGyroscope(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~OrientConfigurationGyroscope() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Orientation Selection (ORIENT)
            uint8_t orientation_selection : 3;    // bits 0:2
            /// Sign Z Gyroscope
            uint8_t sign_z                : 1;    // bit 3
            /// Sign Y Gyroscope
            uint8_t sign_y                : 1;    // bit 4
            /// Sign X Gyroscope
            uint8_t sign_x                : 1;    // bit 5
            /// (reserved)
            uint8_t                       : 2;    // bits 6:7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        OrientConfigurationGyroscope& operator=(OrientConfigurationGyroscope&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(OrientConfigurationGyroscope volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(OrientConfigurationGyroscope const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<OrientConfigurationGyroscope>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(OrientConfigurationGyroscope) == 1UL, "Must be this exact size");
    /// Interrupt Generation Source Gyroscope (INT_GEN_SRC_G)
    struct InterruptGenerationSourceGyroscope final {
        /// Default Constructor
        InterruptGenerationSourceGyroscope()
            : whole{0u} {}
        /// Copy Constructor from volatile
        InterruptGenerationSourceGyroscope(InterruptGenerationSourceGyroscope volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        InterruptGenerationSourceGyroscope(InterruptGenerationSourceGyroscope const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        InterruptGenerationSourceGyroscope(InterruptGenerationSourceGyroscope&&) = delete;
        /// Parameterized Constructor for constant references
        explicit InterruptGenerationSourceGyroscope(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit InterruptGenerationSourceGyroscope(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~InterruptGenerationSourceGyroscope() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Pitch X Low (XL_G)
            uint8_t pitch_x_low      : 1;    // bit 0
            /// Pitch X High (XH_G)
            uint8_t pitch_x_high     : 1;    // bit 1
            /// Pitch Y Low (YL_G)
            uint8_t pitch_y_low      : 1;    // bit 2
            /// Pitch Y High (YH_G)
            uint8_t pitch_y_high     : 1;    // bit 3
            /// Pitch Z Low (ZL_G)
            uint8_t pitch_z_low      : 1;    // bit 4
            /// Pitch Z High (ZH_G)
            uint8_t pitch_z_high     : 1;    // bit 5
            /// Interrupt Active (IA_G)
            uint8_t interrupt_active : 1;    // bit 6
            /// (reserved)
            uint8_t                  : 1;    // bit 7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        InterruptGenerationSourceGyroscope& operator=(InterruptGenerationSourceGyroscope&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(InterruptGenerationSourceGyroscope volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(InterruptGenerationSourceGyroscope const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<InterruptGenerationSourceGyroscope>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(InterruptGenerationSourceGyroscope) == 1UL, "Must be this exact size");
    /// Status Register (STATUS_REG)
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
            /// Accelerometer Data Available (XLDA)
            uint8_t data_available_accelerometer   : 1;    // bit 0
            /// Gyroscope Data Available (GDA)
            uint8_t data_available_gyroscope       : 1;    // bit 1
            /// Temperature Data Available (TDA)
            uint8_t data_available_temperature     : 1;    // bit 2
            /// Boot Status (BOOT_STATUS)
            uint8_t boot_status                    : 1;    // bit 3
            /// Inactivity Interrupt Output (INACT)
            uint8_t inactivity_interrupt_output    : 1;    // bit 4
            /// Gyroscope Interrupt Output (IG_G)
            uint8_t gyroscope_interrupt_output     : 1;    // bit 5
            /// Accelerometer Interrupt Output (IG_XL)
            uint8_t accelerometer_interrupt_output : 1;    // bit 6
            /// (reserved)
            uint8_t                                : 1;    // bit 7
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
    /// Control register 4 (CTRL_REG4)
    struct Control4 final {
        /// Default Constructor
        Control4()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Control4(Control4 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Control4(Control4 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Control4(Control4&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Control4(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Control4(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Control4() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// 4 Dimensional Enabled On Interupt (4D_XL1)
            uint8_t four_dimensional_enabled_on_interrupt : 1;    // bit 0
            /// Latched Interrupt (LIR_XL1)
            uint8_t latched_interrupt                     : 1;    // bit 1
            /// (reserved)
            uint8_t                                       : 1;    // bit 2
            /// Gyroscope Enable X
            uint8_t gyroscope_enable_x                    : 1;    // bit 3
            /// Gyroscope Enable Y
            uint8_t gyroscope_enable_y                    : 1;    // bit 4
            /// Gyroscope Enable Z
            uint8_t gyroscope_enable_z                    : 1;    // bit 5
            /// (reserved)
            uint8_t                                       : 2;    // bits 6:7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Control4& operator=(Control4&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Control4 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Control4 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Control4>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Control4) == 1UL, "Must be this exact size");
    /// Control register 5 Accelerometer (CTRL_REG5_XL)
    struct Control5 final {
        /// Default Constructor
        Control5()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Control5(Control5 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Control5(Control5 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Control5(Control5&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Control5(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Control5(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Control5() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint8_t                          : 3;    // bits 0:2
            /// Accelerometer Enable X
            uint8_t accelerometer_enable_x   : 1;    // bit 3
            /// Accelerometer Enable Y
            uint8_t accelerometer_enable_y   : 1;    // bit 4
            /// Accelerometer Enable Z
            uint8_t accelerometer_enable_z   : 1;    // bit 5
            /// Decimation Configuration
            uint8_t decimation_configuration : 2;    // bits 6:7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Control5& operator=(Control5&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Control5 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Control5 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Control5>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Control5) == 1UL, "Must be this exact size");
    /// Control register 6 Accelerometer (CTRL_REG6_XL)
    struct Control6 final {
        /// Default Constructor
        Control6()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Control6(Control6 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Control6(Control6 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Control6(Control6&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Control6(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Control6(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Control6() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Anti-Aliasing Filter bandwidth selection (BW_XL)
            uint8_t bandwidth_selection : 2;    // bits 0:1
            /// Bandwidth selection (BW_SCAL_ODR)
            uint8_t bandwidth_or_odr    : 1;    // bit 2
            /// Full Scale Selection (FS_XL)
            uint8_t scale_selection     : 2;    // bits 3:4
            /// Output Data Rate and Power Mode (ODR_XL)
            uint8_t output_data_rate    : 3;    // bits 5:7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Control6& operator=(Control6&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Control6 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Control6 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Control6>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Control6) == 1UL, "Must be this exact size");
    /// Control register 7 Accelerometer (CTRL_REG7_XL)
    struct Control7 final {
        /// Default Constructor
        Control7()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Control7(Control7 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Control7(Control7 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Control7(Control7&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Control7(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Control7(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Control7() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// High Pass Filter Enable (HPIS1)
            uint8_t high_pass_filter_enable         : 1;    // bit 0
            /// (reserved)
            uint8_t                                 : 1;    // bit 1
            /// Filtered Data Selection (FDS)
            uint8_t filtered_data_selection         : 1;    // bit 2
            /// (reserved)
            uint8_t                                 : 2;    // bits 3:4
            /// Accelerometer Digital Filter Cutoff Slection (DCF)
            uint8_t digital_filter_cutoff_selection : 2;    // bits 5:6
            /// High Resolution Mode (HR)
            uint8_t high_resolution_mode            : 1;    // bit 7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Control7& operator=(Control7&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Control7 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Control7 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Control7>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Control7) == 1UL, "Must be this exact size");
    /// Control register 8 (CTRL_REG8)
    struct Control8 final {
        /// Default Constructor
        Control8()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Control8(Control8 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Control8(Control8 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Control8(Control8&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Control8(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Control8(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Control8() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Software Reset (SW_RESET)
            uint8_t software_reset              : 1;    // bit 0
            /// Big Little Endian Selection (BLE)
            uint8_t big_little_endian_selection : 1;    // bit 1
            /// Auto Increment Address (IF_ADD_INC)
            uint8_t auto_increment_address      : 1;    // bit 2
            /// Serial Interface Mode (SIM)
            uint8_t serial_interface_mode       : 1;    // bit 3
            /// Push/Pull Open/Drain on INT1_A/G Pin and INT2_A/G Pin (PP_OD)
            uint8_t push_pull_open_drain        : 1;    // bit 4
            /// Interrupt Activation Level (H_LACTIVE)
            uint8_t interrupt_activation_level  : 1;    // bit 5
            /// Block Data Update (BDU)
            uint8_t block_data_update           : 1;    // bit 6
            /// Reboot Memory contents (BOOT)
            uint8_t boot                        : 1;    // bit 7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Control8& operator=(Control8&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Control8 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Control8 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Control8>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Control8) == 1UL, "Must be this exact size");
    /// Control register 9 (CTRL_REG9)
    struct Control9 final {
        /// Default Constructor
        Control9()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Control9(Control9 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Control9(Control9 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Control9(Control9&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Control9(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Control9(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Control9() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Stop on FIFO Threshold (STOP_ON_FTH)
            uint8_t stop_on_fifo_threshold  : 1;    // bit 0
            /// FIFO Enable (FIFO_EN)
            uint8_t fifo_enable             : 1;    // bit 1
            /// I2C Disable (I2C_DISABLE)
            uint8_t i2c_disable             : 1;    // bit 2
            /// Data Ready Mask Bit (DRDY_MASK)
            uint8_t data_ready_mask_bit     : 1;    // bit 3
            /// FIFO Temperature Enable (FIFO_TEMP_EN)
            uint8_t fifo_temperature_enable : 1;    // bit 4
            /// (reserved)
            uint8_t                         : 1;    // bit 5
            /// Sleep Gyroscope (SLEEP_G)
            uint8_t sleep_gyroscope         : 1;    // bit 6
            /// (reserved)
            uint8_t                         : 1;    // bit 7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Control9& operator=(Control9&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Control9 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Control9 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Control9>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Control9) == 1UL, "Must be this exact size");
    /// Control register 9 (CTRL_REG9)
    struct Control10 final {
        /// Default Constructor
        Control10()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Control10(Control10 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Control10(Control10 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Control10(Control10&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Control10(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Control10(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Control10() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Linear Acceleration Self Test (ST_XL)
            uint8_t linear_acceleration_self_test : 1;    // bit 0
            /// (reserved)
            uint8_t                               : 1;    // bit 1
            /// Angular Rate Sensor Self Test (ST_G)
            uint8_t angular_rate_sensor_self_test : 1;    // bit 2
            /// (reserved)
            uint8_t                               : 5;    // bits 3:7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Control10& operator=(Control10&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Control10 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Control10 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Control10>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Control10) == 1UL, "Must be this exact size");
    /// Interrupt Generation Source Acceleration register (INT_GEN_SRC_XL)
    struct InterruptGenerationSourceAccelerometer final {
        /// Default Constructor
        InterruptGenerationSourceAccelerometer()
            : whole{0u} {}
        /// Copy Constructor from volatile
        InterruptGenerationSourceAccelerometer(InterruptGenerationSourceAccelerometer volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        InterruptGenerationSourceAccelerometer(InterruptGenerationSourceAccelerometer const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        InterruptGenerationSourceAccelerometer(InterruptGenerationSourceAccelerometer&&) = delete;
        /// Parameterized Constructor for constant references
        explicit InterruptGenerationSourceAccelerometer(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit InterruptGenerationSourceAccelerometer(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~InterruptGenerationSourceAccelerometer() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Accelerometer X-axis low event (XL_XL)
            uint8_t x_low_event      : 1;    // bit 0
            /// Accelerometer X-axis high event (XH_XL)
            uint8_t x_high_event     : 1;    // bit 1
            /// Accelerometer Y-axis low event (YL_YL)
            uint8_t y_low_event      : 1;    // bit 2
            /// Accelerometer Y-axis high event (YH_YL)
            uint8_t y_high_event     : 1;    // bit 3
            /// Accelerometer Z-axis low event (ZL_ZL)
            uint8_t z_low_event      : 1;    // bit 4
            /// Accelerometer Z-axis high event (ZH_ZL)
            uint8_t z_high_event     : 1;    // bit 5
            /// Interrupt Active
            uint8_t interrupt_active : 1;    // bit 6
            /// (reserved)
            uint8_t                  : 1;    // bit 7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        InterruptGenerationSourceAccelerometer& operator=(InterruptGenerationSourceAccelerometer&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(InterruptGenerationSourceAccelerometer volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(InterruptGenerationSourceAccelerometer const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<InterruptGenerationSourceAccelerometer>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(InterruptGenerationSourceAccelerometer) == 1UL, "Must be this exact size");
    /// FIFO Control Register (FIFO_CTRL)
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
            /// FIFO Threshold (FTH)
            uint8_t threshold : 5;    // bits 0:4
            /// FIFO Mode (FMODE)
            uint8_t mode      : 3;    // bits 5:7
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
    /// FIFO Source Register (FIFO_SRC)
    struct FifoSource final {
        /// Default Constructor
        FifoSource()
            : whole{0u} {}
        /// Copy Constructor from volatile
        FifoSource(FifoSource volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        FifoSource(FifoSource const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        FifoSource(FifoSource&&) = delete;
        /// Parameterized Constructor for constant references
        explicit FifoSource(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit FifoSource(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~FifoSource() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// FIFO Stored Samples (FSS)
            uint8_t stored_samples   : 6;    // bits 0:5
            /// Overrun (OVRN)
            uint8_t overrun          : 1;    // bit 6
            /// FIFO Threshold Status (FTH)
            uint8_t threshold_status : 1;    // bit 7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        FifoSource& operator=(FifoSource&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(FifoSource volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(FifoSource const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<FifoSource>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(FifoSource) == 1UL, "Must be this exact size");
    /// Interrupt Generation Configuration for Angular Sensor (INT_GEN_CFG_G)
    struct InterruptGenerationConfigurationGyroscope final {
        /// Default Constructor
        InterruptGenerationConfigurationGyroscope()
            : whole{0u} {}
        /// Copy Constructor from volatile
        InterruptGenerationConfigurationGyroscope(InterruptGenerationConfigurationGyroscope volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        InterruptGenerationConfigurationGyroscope(InterruptGenerationConfigurationGyroscope const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        InterruptGenerationConfigurationGyroscope(InterruptGenerationConfigurationGyroscope&&) = delete;
        /// Parameterized Constructor for constant references
        explicit InterruptGenerationConfigurationGyroscope(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit InterruptGenerationConfigurationGyroscope(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~InterruptGenerationConfigurationGyroscope() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// X-axis low interrupt enable
            uint8_t x_low_interrupt_enable  : 1;    // bit 0
            /// X-axis high interrupt enable
            uint8_t x_high_interrupt_enable : 1;    // bit 1
            /// Y-axis low interrupt enable
            uint8_t y_low_interrupt_enable  : 1;    // bit 2
            /// Y-axis high interrupt enable
            uint8_t y_high_interrupt_enable : 1;    // bit 3
            /// Z-axis low interrupt enable
            uint8_t z_low_interrupt_enable  : 1;    // bit 4
            /// Z-axis high interrupt enable
            uint8_t z_high_interrupt_enable : 1;    // bit 5
            /// Latch Gyroscope interrupt (LIR_G)
            uint8_t latch_interrupt         : 1;    // bit 6
            /// AND /OR Gyroscope interrupt (AOI_G)
            uint8_t and_or_interrupt        : 1;    // bit 7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        InterruptGenerationConfigurationGyroscope& operator=(InterruptGenerationConfigurationGyroscope&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(InterruptGenerationConfigurationGyroscope volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(InterruptGenerationConfigurationGyroscope const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<InterruptGenerationConfigurationGyroscope>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(InterruptGenerationConfigurationGyroscope) == 1UL, "Must be this exact size");
    /// Interrupt Generation Duration Gyroscope register (INT_GEN_DUR_G)
    struct InterruptGenerationDurationGyroscope final {
        /// Default Constructor
        InterruptGenerationDurationGyroscope()
            : whole{0u} {}
        /// Copy Constructor from volatile
        InterruptGenerationDurationGyroscope(InterruptGenerationDurationGyroscope volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        InterruptGenerationDurationGyroscope(InterruptGenerationDurationGyroscope const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        InterruptGenerationDurationGyroscope(InterruptGenerationDurationGyroscope&&) = delete;
        /// Parameterized Constructor for constant references
        explicit InterruptGenerationDurationGyroscope(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit InterruptGenerationDurationGyroscope(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~InterruptGenerationDurationGyroscope() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Duration value (DUR_G)
            uint8_t duration : 7;    // bits 0:6
            /// Wait function enabled on duration counter (WAIT_G)
            uint8_t wait     : 1;    // bit 7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        InterruptGenerationDurationGyroscope& operator=(InterruptGenerationDurationGyroscope&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(InterruptGenerationDurationGyroscope volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(InterruptGenerationDurationGyroscope const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<InterruptGenerationDurationGyroscope>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(InterruptGenerationDurationGyroscope) == 1UL, "Must be this exact size");

    //+=MEMORY======================================+
    uint8_t : 8;    // offset 0x0UL
    uint8_t : 8;    // offset 0x1UL
    uint8_t : 8;    // offset 0x2UL
    uint8_t : 8;    // offset 0x3UL
    /// Activity Threshold register (ACT_THS)
    ActivityThreshold activity_threshold;    // offset 0x4UL
    /// Activity Duration register (ACT_DUR)
    uint8_t activity_duration;    // offset 0x5UL
    /// Linear acceleration sensor interrupt generator configuration register. (INT_GEN_CFG_XL)
    InterruptGenerationConfigurationXL int_gen_cfg_xl;    // offset 0x6UL
    /// Linear acceleration sensor interrupt threshold register. (INT_GEN_THS_X_XL)
    uint8_t interrupt_generation_threshold_x_accelerometer;    // offset 0x7UL
    /// Linear acceleration sensor interrupt threshold register. (INT_GEN_THS_Y_XL)
    uint8_t interrupt_generation_threshold_y_accelerometer;    // offset 0x8UL
    /// Linear acceleration sensor interrupt threshold register. (INT_GEN_THS_Z_XL)
    uint8_t interrupt_generation_threshold_z_accelerometer;    // offset 0x9UL
    /// Linear acceleration sensor interrupt duration register. (INT_GEN_DUR_XL)
    InterruptGenerationDurationAccelerometer interrupt_generation_duration_accelerometer;    // offset 0xaUL
    /// Angular rate sensor reference value register for digital high-pass filter (r/w). (REFERENCE_G)
    uint8_t reference_gyroscope;    // offset 0xbUL
    /// Interrupt 2 A/G pin control register. (INT1_AG_CTRL)
    Interrupt1AccelerometerGyroscopePinControl interrupt_1_ag_pin_control;    // offset 0xcUL
    /// Interrupt 2 A/G pin control register. (INT2_AG_CTRL)
    Interrupt2AccelerometerGyroscopePinControl interrupt_2_ag_pin_control;    // offset 0xdUL
    uint8_t : 8;                                                              // offset 0xeUL
    /// Who Am I register (0x68). (WHO_AM_I)
    uint8_t who_am_i;    // offset 0xfUL
    /// Control register 1 Gyroscope (CTRL_REG1_G)
    Control1 control_register_1;    // offset 0x10UL
    /// Control register 2 (CTRL_REG2_G)
    Control2 control_register_2;    // offset 0x11UL
    /// Control register 3 (CTRL_REG3_G)
    Control3 control_register_3;    // offset 0x12UL
    /// Orient Configuration Gyroscope register (ORIENT_CFG_G)
    OrientConfigurationGyroscope orient_configuration_gyroscope;    // offset 0x13UL
    /// Interrupt Generation Source Gyroscope register (INT_GEN_SRC_G)
    InterruptGenerationSourceGyroscope interrupt_generation_source_gyroscope;    // offset 0x14UL
    /// Output Temperature Low (OUT_TEMP_L)
    uint8_t output_temperature_low;    // offset 0x15UL
    /// Output Temperature High (OUT_TEMP_H)
    uint8_t output_temperature_high;    // offset 0x16UL
    /// Status register (STATUS_REG)
    Status status1;    // offset 0x17UL
    /// Output X Gyroscope (OUT_X_G)
    uint8_t output_x_gyroscope[2];    // offset 0x18UL
    /// Output Y Gyroscope (OUT_Y_G)
    uint8_t output_y_gyroscope[2];    // offset 0x1aUL
    /// Output Z Gyroscope (OUT_Z_G)
    uint8_t output_z_gyroscope[2];    // offset 0x1cUL
    /// Control register 4 (CTRL_REG4_G)
    Control4 control_register_4;    // offset 0x1eUL
    /// Control register 5 (CTRL_REG5_XL)
    Control5 control_register_5;    // offset 0x1fUL
    /// Control register 6 (CTRL_REG6_XL)
    Control6 control_register_6;    // offset 0x20UL
    /// Control register 7 (CTRL_REG7_XL)
    Control7 control_register_7;    // offset 0x21UL
    /// Control register 8 (CTRL_REG8_XL)
    Control8 control_register_8;    // offset 0x22UL
    /// Control register 9 (CTRL_REG9)
    Control9 control_register_9;    // offset 0x23UL
    /// Control register 10 (CTRL_REG10)
    Control10 control_register_10;    // offset 0x24UL
    uint8_t : 8;                      // offset 0x25UL
    /// Interrupt Generation Source Accelerometer register (INT_GEN_SRC_XL)
    InterruptGenerationSourceAccelerometer interrupt_generation_source_accelerometer;    // offset 0x26UL
    /// Status register (STATUS_REG)
    Status status2;    // offset 0x27UL
    /// Output X Accelerometer (OUT_X_XL)
    uint8_t output_x_accelerometer[2];    // offset 0x28UL
    /// Output Y Accelerometer (OUT_Y_XL)
    uint8_t output_y_accelerometer[2];    // offset 0x2aUL
    /// Output Z Accelerometer (OUT_Z_XL)
    uint8_t output_z_accelerometer[2];    // offset 0x2cUL
    /// FIFO Control register (FIFO_CTRL)
    FifoControl fifo_control;    // offset 0x2eUL
    /// FIFO Source register (FIFO_SRC)
    FifoSource fifo_source;    // offset 0x2fUL
    /// Interrupt Generation Configuration Gyroscope (INT_GEN_CFG_G)
    InterruptGenerationConfigurationGyroscope interrupt_generation_configuration_gyroscope;    // offset 0x30UL
    /// Interrupt Generation Threshold Gyroscope X (INT_GEN_THS_X_G)
    uint8_t interrupt_generation_threshold_gyroscope_x[2];    // offset 0x31UL
    /// Interrupt Generation Threshold Gyroscope Y (INT_GEN_THS_Y_G)
    uint8_t interrupt_generation_threshold_gyroscope_y[2];    // offset 0x33UL
    /// Interrupt Generation Threshold Gyroscope Z (INT_GEN_THS_Z_G)
    uint8_t interrupt_generation_threshold_gyroscope_z[2];    // offset 0x35UL
    /// Interrupt Generation Duration Gyroscope (INT_GEN_DUR_G)
    InterruptGenerationDurationGyroscope interrupt_generation_duration_gyroscope;    // offset 0x37UL
    //+=MEMORY======================================+
};
// Ensure the structure is in standard layout format
static_assert(std::is_standard_layout<Accelerometer>::value, "Must be standard layout");
// Ensure the offsets are all correct
static_assert(offsetof(Accelerometer, activity_threshold) == 0x4UL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, activity_duration) == 0x5UL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, int_gen_cfg_xl) == 0x6UL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, interrupt_generation_threshold_x_accelerometer) == 0x7UL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, interrupt_generation_threshold_y_accelerometer) == 0x8UL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, interrupt_generation_threshold_z_accelerometer) == 0x9UL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, interrupt_generation_duration_accelerometer) == 0xaUL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, reference_gyroscope) == 0xbUL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, interrupt_1_ag_pin_control) == 0xcUL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, interrupt_2_ag_pin_control) == 0xdUL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, who_am_i) == 0xfUL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, control_register_1) == 0x10UL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, control_register_2) == 0x11UL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, control_register_3) == 0x12UL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, orient_configuration_gyroscope) == 0x13UL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, interrupt_generation_source_gyroscope) == 0x14UL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, output_temperature_low) == 0x15UL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, output_temperature_high) == 0x16UL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, status1) == 0x17UL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, output_x_gyroscope) == 0x18UL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, output_y_gyroscope) == 0x1aUL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, output_z_gyroscope) == 0x1cUL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, control_register_4) == 0x1eUL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, control_register_5) == 0x1fUL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, control_register_6) == 0x20UL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, control_register_7) == 0x21UL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, control_register_8) == 0x22UL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, control_register_9) == 0x23UL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, control_register_10) == 0x24UL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, interrupt_generation_source_accelerometer) == 0x26UL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, status2) == 0x27UL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, output_x_accelerometer) == 0x28UL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, output_y_accelerometer) == 0x2aUL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, output_z_accelerometer) == 0x2cUL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, fifo_control) == 0x2eUL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, fifo_source) == 0x2fUL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, interrupt_generation_configuration_gyroscope) == 0x30UL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, interrupt_generation_threshold_gyroscope_x) == 0x31UL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, interrupt_generation_threshold_gyroscope_y) == 0x33UL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, interrupt_generation_threshold_gyroscope_z) == 0x35UL, "Must be located at this offset");
static_assert(offsetof(Accelerometer, interrupt_generation_duration_gyroscope) == 0x37UL, "Must be located at this offset");

// Ensure the sizeof the entire structure is correct.
static_assert(sizeof(Accelerometer) == 0x38UL, "Must be this exact size");

/// LSM9DS1 Gyroscope/Accelerometer Sensor
struct Magnetometer final {
    /// Control register 1 Magnetometer (CTRL_REG1_M)
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
        explicit Control1(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Control1(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Control1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Self Test Enable
            uint8_t self_test_enable                : 1;    // bit 0
            /// (reserved)
            uint8_t                                 : 1;    // bit 1
            /// Output Data Rate Selection
            uint8_t output_data_rate_selection      : 3;    // bits 2:4
            /// X and Y Axis Operative Mode
            uint8_t xy_axis_operative_mode          : 2;    // bits 5:6
            /// Temperature Compensation Enable
            uint8_t temperature_compensation_enable : 1;    // bit 7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
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
    static_assert(std::is_standard_layout<Control1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Control1) == 1UL, "Must be this exact size");
    /// Control register 1 Magnetometer (CTRL_REG2_M)
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
        explicit Control2(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Control2(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Control2() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint8_t                        : 2;    // bits 0:1
            /// Soft Reset
            uint8_t self_test_enable       : 1;    // bit 2
            /// Reboot Memory Contents
            uint8_t reboot_memory_contents : 1;    // bit 3
            /// (reserved)
            uint8_t                        : 1;    // bit 4
            /// Full Scale Configuration
            uint8_t full_scale_selection   : 2;    // bits 5:6
            /// (reserved)
            uint8_t                        : 1;    // bit 7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
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
    static_assert(std::is_standard_layout<Control2>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Control2) == 1UL, "Must be this exact size");
    /// Control register 1 Magnetometer (CTRL_REG3_M)
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
        explicit Control3(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Control3(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Control3() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Operating Mode Selection (MD)
            uint8_t operating_mode_selection : 2;    // bits 0:1
            /// Serial Interface Mode (SIM)
            uint8_t serial_interface_mode    : 1;    // bit 2
            /// (reserved)
            uint8_t                          : 2;    // bits 3:4
            /// Low Power Mode (LP)
            uint8_t low_power_mode           : 1;    // bit 5
            /// (reserved)
            uint8_t                          : 1;    // bit 6
            /// I2C Disable (I2C_DISABLE)
            uint8_t i2c_disable              : 1;    // bit 7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
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
    static_assert(std::is_standard_layout<Control3>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Control3) == 1UL, "Must be this exact size");
    /// Control register 1 Magnetometer (CTRL_REG4_M)
    struct Control4 final {
        /// Default Constructor
        Control4()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Control4(Control4 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Control4(Control4 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Control4(Control4&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Control4(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Control4(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Control4() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint8_t                       : 1;    // bit 0
            /// Big/Little Endian (BLE)
            uint8_t big_little_endian     : 1;    // bit 1
            /// Z Axis Operative Mode (OMZ)
            uint8_t z_axis_operative_mode : 2;    // bits 2:3
            /// (reserved)
            uint8_t                       : 4;    // bits 4:7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Control4& operator=(Control4&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Control4 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Control4 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Control4>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Control4) == 1UL, "Must be this exact size");
    /// Control register 1 Magnetometer (CTRL_REG5_M)
    struct Control5 final {
        /// Default Constructor
        Control5()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Control5(Control5 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Control5(Control5 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Control5(Control5&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Control5(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Control5(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Control5() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint8_t                   : 6;    // bits 0:5
            /// Block Data Update (BDU)
            uint8_t block_data_update : 1;    // bit 6
            /// (reserved)
            uint8_t                   : 1;    // bit 7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Control5& operator=(Control5&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Control5 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Control5 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Control5>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Control5) == 1UL, "Must be this exact size");
    /// Control register 1 Magnetometer (CTRL_REG5_M)
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
            /// X-axis Data Ready (XDA)
            uint8_t x_axis_data_ready  : 1;    // bit 0
            /// Y-axis Data Ready (YDA)
            uint8_t y_axis_data_ready  : 1;    // bit 1
            /// Z-axis Data Ready (ZDA)
            uint8_t z_axis_data_ready  : 1;    // bit 2
            /// Z, Y, X Data Available (ZYXDA)
            uint8_t zyx_data_available : 1;    // bit 3
            /// X Data Overrun (XOR)
            uint8_t x_data_overrun     : 1;    // bit 4
            /// Y Data Overrun (YOR)
            uint8_t y_data_overrun     : 1;    // bit 5
            /// Z Data Overrun (ZOR)
            uint8_t z_data_overrun     : 1;    // bit 6
            /// Z, Y, X Data Overrun (ZYXOR)
            uint8_t zyx_data_overrun   : 1;    // bit 7
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
    /// Interrupt Configuration Register (INT_CFG_M)
    struct InterruptConfiguration final {
        /// Default Constructor
        InterruptConfiguration()
            : whole{0u} {}
        /// Copy Constructor from volatile
        InterruptConfiguration(InterruptConfiguration volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        InterruptConfiguration(InterruptConfiguration const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        InterruptConfiguration(InterruptConfiguration&&) = delete;
        /// Parameterized Constructor for constant references
        explicit InterruptConfiguration(uint8_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit InterruptConfiguration(uint8_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~InterruptConfiguration() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Interrupt Enable on INT_M pin
            uint8_t enable_on_int_m_pin            : 1;    // bit 0
            /// Latch Interrupt Request
            uint8_t latch_interrupt_request        : 1;    // bit 1
            /// Interrupt Enable on INT_MAG
            uint8_t enable_on_int_mag_pin          : 1;    // bit 2
            /// (reserved)
            uint8_t                                : 2;    // bits 3:4
            /// Interrupt Generation on Z Axis (ZIEN)
            uint8_t interrupt_generation_on_z_axis : 1;    // bit 5
            /// Interrupt Generation on Y Axis (YIEN)
            uint8_t interrupt_generation_on_y_axis : 1;    // bit 6
            /// Interrupt Generation on X Axis (XIEN)
            uint8_t interrupt_generation_on_x_axis : 1;    // bit 7
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint8_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        InterruptConfiguration& operator=(InterruptConfiguration&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(InterruptConfiguration volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(InterruptConfiguration const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<InterruptConfiguration>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(InterruptConfiguration) == 1UL, "Must be this exact size");
    /// Interrupt Source Register (INT_SRC_M)
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
            /// Interrupt Event Active
            uint8_t interrupt_active                : 1;    // bit 0
            /// Internal Measure Range Overflow (MROI)
            uint8_t internal_measure_range_overflow : 1;    // bit 1
            /// Negative Threshold on Z Axis (NTH_Z)
            uint8_t negative_threshold_on_z_axis    : 1;    // bit 2
            /// Negative Threshold on Y Axis (NTH_Y)
            uint8_t negative_threshold_on_y_axis    : 1;    // bit 3
            /// Negative Threshold on X Axis (NTH_X)
            uint8_t negative_threshold_on_x_axis    : 1;    // bit 4
            /// Positive Threshold on Z Axis (PTH_Z)
            uint8_t positive_threshold_on_z_axis    : 1;    // bit 5
            /// Positive Threshold on Y Axis (PTH_Y)
            uint8_t positive_threshold_on_y_axis    : 1;    // bit 6
            /// Positive Threshold on X Axis (PTH_X)
            uint8_t positive_threshold_on_x_axis    : 1;    // bit 7
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

    //+=MEMORY======================================+
    uint8_t : 8;    // offset 0x0UL
    uint8_t : 8;    // offset 0x1UL
    uint8_t : 8;    // offset 0x2UL
    uint8_t : 8;    // offset 0x3UL
    uint8_t : 8;    // offset 0x4UL
    /// Offset X Low (OFFSET_X_REG_L_M)
    uint8_t offset_x_low;    // offset 0x5UL
    /// Offset X High (OFFSET_X_REG_H_M)
    uint8_t offset_x_high;    // offset 0x6UL
    /// Offset Y Low (OFFSET_Y_REG_L_M)
    uint8_t offset_y_low;    // offset 0x7UL
    /// Offset Y High (OFFSET_Y_REG_H_M)
    uint8_t offset_y_high;    // offset 0x8UL
    /// Offset Z Low (OFFSET_Z_REG_L_M)
    uint8_t offset_z_low;    // offset 0x9UL
    /// Offset Z High (OFFSET_Z_REG_H_M)
    uint8_t offset_z_high;    // offset 0xaUL
    uint8_t : 8;              // offset 0xbUL
    uint8_t : 8;              // offset 0xcUL
    uint8_t : 8;              // offset 0xdUL
    uint8_t : 8;              // offset 0xeUL
    /// Who Am I (0x3D) (WHO_AM_I)
    uint8_t who_am_i;    // offset 0xfUL
    uint8_t : 8;         // offset 0x10UL
    uint8_t : 8;         // offset 0x11UL
    uint8_t : 8;         // offset 0x12UL
    uint8_t : 8;         // offset 0x13UL
    uint8_t : 8;         // offset 0x14UL
    uint8_t : 8;         // offset 0x15UL
    uint8_t : 8;         // offset 0x16UL
    uint8_t : 8;         // offset 0x17UL
    uint8_t : 8;         // offset 0x18UL
    uint8_t : 8;         // offset 0x19UL
    uint8_t : 8;         // offset 0x1aUL
    uint8_t : 8;         // offset 0x1bUL
    uint8_t : 8;         // offset 0x1cUL
    uint8_t : 8;         // offset 0x1dUL
    uint8_t : 8;         // offset 0x1eUL
    uint8_t : 8;         // offset 0x1fUL
    /// Control register 1 (CTRL_REG1_M)
    Control1 control1;    // offset 0x20UL
    /// Control register 2 (CTRL_REG2_M)
    Control2 control2;    // offset 0x21UL
    /// Control register 3 (CTRL_REG3_M)
    Control3 control3;    // offset 0x22UL
    /// Control register 4 (CTRL_REG4_M)
    Control4 control4;    // offset 0x23UL
    /// Control register 5 (CTRL_REG5_M)
    Control5 control5;    // offset 0x24UL
    uint8_t : 8;          // offset 0x25UL
    uint8_t : 8;          // offset 0x26UL
    /// Status register (STATUS_REG_M)
    Status status;    // offset 0x27UL
    /// Output X Low (OUT_X_L_M)
    uint8_t output_x_low;    // offset 0x28UL
    /// Output X High (OUT_X_H_M)
    uint8_t output_x_high;    // offset 0x29UL
    /// Output Y Low (OUT_Y_L_M)
    uint8_t output_y_low;    // offset 0x2aUL
    /// Output Y High (OUT_Y_H_M)
    uint8_t output_y_high;    // offset 0x2bUL
    /// Output Z Low (OUT_Z_L_M)
    uint8_t output_z_low;    // offset 0x2cUL
    /// Output Z High (OUT_Z_H_M)
    uint8_t output_z_high;    // offset 0x2dUL
    uint8_t : 8;              // offset 0x2eUL
    uint8_t : 8;              // offset 0x2fUL
    /// Interrupt Configuration (INT_CFG_M)
    InterruptConfiguration interrupt_configuration;    // offset 0x30UL
    /// Interrupt Source (INT_SRC_M)
    InterruptSource interrupt_source;    // offset 0x31UL
    /// Interrupt Threshold Low (INT_THS_L)
    uint8_t interrupt_threshold_low;    // offset 0x32UL
    /// Interrupt Threshold High (INT_THS_H)
    uint8_t interrupt_threshold_high;    // offset 0x33UL
    //+=MEMORY======================================+
};
// Ensure the structure is in standard layout format
static_assert(std::is_standard_layout<Magnetometer>::value, "Must be standard layout");
// Ensure the offsets are all correct
static_assert(offsetof(Magnetometer, offset_x_low) == 0x5UL, "Must be located at this offset");
static_assert(offsetof(Magnetometer, offset_x_high) == 0x6UL, "Must be located at this offset");
static_assert(offsetof(Magnetometer, offset_y_low) == 0x7UL, "Must be located at this offset");
static_assert(offsetof(Magnetometer, offset_y_high) == 0x8UL, "Must be located at this offset");
static_assert(offsetof(Magnetometer, offset_z_low) == 0x9UL, "Must be located at this offset");
static_assert(offsetof(Magnetometer, offset_z_high) == 0xaUL, "Must be located at this offset");
static_assert(offsetof(Magnetometer, who_am_i) == 0xfUL, "Must be located at this offset");
static_assert(offsetof(Magnetometer, control1) == 0x20UL, "Must be located at this offset");
static_assert(offsetof(Magnetometer, control2) == 0x21UL, "Must be located at this offset");
static_assert(offsetof(Magnetometer, control3) == 0x22UL, "Must be located at this offset");
static_assert(offsetof(Magnetometer, control4) == 0x23UL, "Must be located at this offset");
static_assert(offsetof(Magnetometer, control5) == 0x24UL, "Must be located at this offset");
static_assert(offsetof(Magnetometer, status) == 0x27UL, "Must be located at this offset");
static_assert(offsetof(Magnetometer, output_x_low) == 0x28UL, "Must be located at this offset");
static_assert(offsetof(Magnetometer, output_x_high) == 0x29UL, "Must be located at this offset");
static_assert(offsetof(Magnetometer, output_y_low) == 0x2aUL, "Must be located at this offset");
static_assert(offsetof(Magnetometer, output_y_high) == 0x2bUL, "Must be located at this offset");
static_assert(offsetof(Magnetometer, output_z_low) == 0x2cUL, "Must be located at this offset");
static_assert(offsetof(Magnetometer, output_z_high) == 0x2dUL, "Must be located at this offset");
static_assert(offsetof(Magnetometer, interrupt_configuration) == 0x30UL, "Must be located at this offset");
static_assert(offsetof(Magnetometer, interrupt_source) == 0x31UL, "Must be located at this offset");
static_assert(offsetof(Magnetometer, interrupt_threshold_low) == 0x32UL, "Must be located at this offset");
static_assert(offsetof(Magnetometer, interrupt_threshold_high) == 0x33UL, "Must be located at this offset");

// Ensure the sizeof the entire structure is correct.
static_assert(sizeof(Magnetometer) == 0x34UL, "Must be this exact size");

}    // namespace lsm9ds1

#endif    // LSM9DS1_HPP

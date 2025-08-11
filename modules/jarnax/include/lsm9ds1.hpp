#ifndef LSM9DS1_HPP
#define LSM9DS1_HPP

/// @file
/// The LSM9DS1 IMU/Gyro Sensor Header

#include <core/Units.hpp>
#include <cstdint>
#include "core/units/Gauss.hpp"

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

}    // namespace lsm9ds1

#endif    // LSM9DS1_HPP

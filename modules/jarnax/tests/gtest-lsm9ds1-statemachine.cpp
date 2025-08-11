#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <core/Units.hpp>
#include <jarnax/JumpTimer.hpp>
#include <lsm9ds1.hpp>

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

namespace jarnax {

using namespace core::units;

TEST(LSM9DS1Conversions, ConvertRawAcceleration) {
    ::lsm9ds1::acceleration::Raw raw_acceleration{0};
    auto acceleration = ::lsm9ds1::acceleration::Convert(raw_acceleration, ::lsm9ds1::acceleration::Sensitivity(2));
    EXPECT_EQ(acceleration, 0.0_g);

    raw_acceleration = INT16_MAX;
    acceleration = ::lsm9ds1::acceleration::Convert(raw_acceleration, ::lsm9ds1::acceleration::Sensitivity(2));
    EXPECT_GT(1.9987_g, acceleration) << "is " << acceleration.value();

    raw_acceleration = -INT16_MAX;
    acceleration = ::lsm9ds1::acceleration::Convert(raw_acceleration, ::lsm9ds1::acceleration::Sensitivity(2));
    EXPECT_LT(-1.9987_g, acceleration) << "is " << acceleration.value();
}

TEST(LSM9DS1Conversions, ConvertRawMagneticField) {
    ::lsm9ds1::magnetic_field::Raw raw_magnetic_field{0};
    auto magnetic_field = ::lsm9ds1::magnetic_field::Convert(raw_magnetic_field, ::lsm9ds1::magnetic_field::Sensitivity(4));
    EXPECT_EQ(magnetic_field, 0.0_G);

    raw_magnetic_field = INT16_MAX;
    magnetic_field = ::lsm9ds1::magnetic_field::Convert(raw_magnetic_field, ::lsm9ds1::magnetic_field::Sensitivity(4));
    EXPECT_GT(5.58_G, magnetic_field) << "is " << magnetic_field.value();

    raw_magnetic_field = -INT16_MAX;
    magnetic_field = ::lsm9ds1::magnetic_field::Convert(raw_magnetic_field, ::lsm9ds1::magnetic_field::Sensitivity(4));
    EXPECT_LT(-5.58_G, magnetic_field) << "is " << magnetic_field.value();
}

TEST(LSM9DS1Conversions, ConvertRawGyroscope) {
    ::lsm9ds1::gyroscope::Raw raw_gyroscope{0};
    auto gyroscope = ::lsm9ds1::gyroscope::Convert(raw_gyroscope, ::lsm9ds1::gyroscope::Sensitivity(245));
    EXPECT_EQ(gyroscope, 0.0_dps);

    raw_gyroscope = INT16_MAX;
    gyroscope = ::lsm9ds1::gyroscope::Convert(raw_gyroscope, ::lsm9ds1::gyroscope::Sensitivity(245));
    EXPECT_GT(2000.0_dps, gyroscope) << "is " << gyroscope.value();

    raw_gyroscope = -INT16_MAX;
    gyroscope = ::lsm9ds1::gyroscope::Convert(raw_gyroscope, ::lsm9ds1::gyroscope::Sensitivity(245));
    EXPECT_LT(-2000.0_dps, gyroscope) << "is " << gyroscope.value();
}

TEST(LSM9DS1Conversions, ConvertRawTemperature) {
    ::lsm9ds1::temperature::Raw raw_temperature{0};
    auto temperature = ::lsm9ds1::temperature::Convert(raw_temperature);
    EXPECT_EQ(temperature, 25.0_C);

    raw_temperature = 960;
    temperature = ::lsm9ds1::temperature::Convert(raw_temperature);
    EXPECT_EQ(::lsm9ds1::MaximumTemperature, temperature) << "is " << temperature.value();

    raw_temperature = -1040;
    temperature = ::lsm9ds1::temperature::Convert(raw_temperature);
    EXPECT_EQ(::lsm9ds1::MinimumTemperature, temperature) << "is " << temperature.value();
}

}    // namespace jarnax

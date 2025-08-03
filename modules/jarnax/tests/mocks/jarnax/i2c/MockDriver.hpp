#ifndef JARNAX_I2C_MOCK_DRIVER_HPP_
#define JARNAX_I2C_MOCK_DRIVER_HPP_

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "jarnax/i2c/Driver.hpp"
#include "jarnax/i2c/MockTransactor.hpp"

namespace jarnax {
namespace i2c {
/// @brief A mock driver for I2C transactions, used for testing purposes.
class MockDriver : public Driver, public jarnax::Executable {
public:
    MockDriver(MockTransactor& transactor)
        : Driver{transactor} {}

    MOCK_METHOD(core::Status, Initialize, (core::units::Hertz peripheral_frequency, core::units::Hertz desired_i2c_clock_frequency), (override));
    MOCK_METHOD(core::Status, Verify, (Transaction & transaction), (override));
    MOCK_METHOD(core::Status, Start, (Transaction & transaction), (override));
    MOCK_METHOD(core::Status, Check, (Transaction & transaction), (override));
    MOCK_METHOD(core::Status, Cancel, (Transaction & transaction), (override));
};

}    // namespace i2c
}    // namespace jarnax

#endif    // JARNAX_I2C_MOCK_DRIVER_HPP_

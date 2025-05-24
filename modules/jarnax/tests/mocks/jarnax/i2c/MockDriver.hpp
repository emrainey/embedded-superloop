#ifndef JARNAX_I2C_MOCK_DRIVER_HPP_
#define JARNAX_I2C_MOCK_DRIVER_HPP_

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "jarnax/i2c/Driver.hpp"
#include "jarnax/i2c/MockTransactor.hpp"

namespace jarnax {
namespace i2c {
/// @brief A mock driver for I2C transactions, used for testing purposes.
class MockDriver : public Driver, public jarnax::Loopable {
public:
    MockDriver(MockTransactor& transactor)
        : Driver{transactor} {}
    MOCK_METHOD0(Initialize, core::Status());
};

}    // namespace i2c
}    // namespace jarnax

#endif    // JARNAX_I2C_MOCK_DRIVER_HPP_
#include <gtest/gtest.h>

#include <stm32/i2c/Driver.hpp>

namespace stm32 {
namespace i2c {
class I2CDriverTest : public ::testing::Test {
public:
    I2CDriverTest()
        : i2c_driver_{stm32::registers::i2c1, dma_driver_, I2C1_TX, I2C1_RX} {
        // Constructor code, if needed
    }
    ~I2CDriverTest() override = default;
    void SetUp() override {
        // Code to set up the test environment, if needed
    }
    void TearDown() override {
        // Code to clean up after tests, if needed
    }

protected:
    stm32::dma::MockDriver dma_driver_;
    stm32::i2c::Driver i2c_driver_;
};
}    // namespace i2c
}    // namespace stm32
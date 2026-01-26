/// @file
/// GoogleMock LPS35HW Callback

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "jarnax/drivers/lps35hw/StateMachine.hpp"

namespace jarnax {
namespace drivers {
namespace lps35hw {

class MockCallback : public jarnax::drivers::lps35hw::Callback {
public:
    MOCK_METHOD(core::Status, StartRegisterRead, (uint8_t address, uint8_t count), (override));
    MOCK_METHOD(core::Status, StartRegisterWrite, (uint8_t address, uint8_t count, uint8_t value[]), (override));
    MOCK_METHOD(core::Status, GetRegisterValue, (uint8_t address, uint8_t count, uint8_t value[]), (override));
    MOCK_METHOD(void, OnError, (core::Status status), (override));
    MOCK_METHOD(void, OnReading, (::lps35hw::RawPressure pressure, ::lps35hw::RawTemperature temperature), (override));
    virtual ~MockCallback() = default;
};

}    // namespace lps35hw
}    // namespace drivers
}    // namespace jarnax

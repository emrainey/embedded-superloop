#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "jarnax/lps35hw/StateMachine.hpp"

namespace jarnax {

namespace lps35hw {

class MockCallback : public jarnax::lps35hw::Callback {
public:
    MOCK_METHOD(core::Status, StartRegisterRead, (uint8_t address, uint8_t count), ());
    MOCK_METHOD(core::Status, StartRegisterWrite, (uint8_t address, uint8_t count, uint8_t value[]), ());
    MOCK_METHOD(core::Status, GetRegisterValue, (uint8_t address, uint8_t count, uint8_t value[]), ());
    MOCK_METHOD(void, OnError, (core::Status status), ());
    MOCK_METHOD(void, OnReading, (::lps35hw::RawPressure pressure, ::lps35hw::RawTemperature temperature), ());
    virtual ~MockCallback() = default;
};

}    // namespace lps35hw

}    // namespace jarnax

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <core/Units.hpp>
#include <jarnax/JumpTimer.hpp>
#include <jarnax/lps35hw/MockCallback.hpp>
#include <jarnax/lps35hw/StateMachine.hpp>

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

namespace jarnax {

using namespace core::units;

TEST(LPS35HWConversions, ConvertRawPressure) {
    ::lps35hw::RawPressure raw_pressure{1064960};
    auto pressure = ::lps35hw::Convert(raw_pressure);
    EXPECT_EQ(pressure, ::lps35hw::MinimumPressure);

    raw_pressure = 5160960;
    pressure = ::lps35hw::Convert(raw_pressure);
    EXPECT_EQ(pressure, ::lps35hw::MaximumPressure);
}

TEST(LPS35HWConversions, ConvertRawTemperature) {
    ::lps35hw::RawTemperature raw_temperature{0U};
    auto temperature = ::lps35hw::Convert(raw_temperature);
    EXPECT_EQ(temperature, ::lps35hw::MinimumTemperature);

    raw_temperature = 6500U;    // 65.0 C in hundredths of a degree
    temperature = ::lps35hw::Convert(raw_temperature);
    EXPECT_EQ(temperature, ::lps35hw::MaximumTemperature);
}

class LPS35HWStateMachineTest : public ::testing::Test {
public:
    LPS35HWStateMachineTest()
        : jump_timer_{}
        , mock_callback_{}
        , state_machine_{jump_timer_, core::units::Iota{10U}, mock_callback_} {}

protected:
    void SetUp() override { state_machine_.Enter(); }

    void TearDown() override { Verify(); }

    void Verify() { ::testing::Mock::VerifyAndClearExpectations(&mock_callback_); }

    void Initialize() {
        // starts the state machine
        // the oncycle will be called and we'll exit Idling then enter the next state
        // on entry to Identifying state
        EXPECT_CALL(mock_callback_, StartRegisterRead(0x0F, 1)).WillOnce(Return(core::Status{}));
        state_machine_.Process(lps35hw::Event::Initialize);
        Verify();
        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        EXPECT_CALL(mock_callback_, GetRegisterValue(0x0F, 1, _)).WillOnce(Invoke([](uint8_t, uint8_t, uint8_t value[]) {
            value[0] = ::lps35hw::WhoAmI;    // WHO_AM_I value for LPS35HW
            return core::Status{};
        }));
        // on entry to Configuring state
        EXPECT_CALL(mock_callback_, StartRegisterWrite(0x10, 3, _)).WillOnce(Return(core::Status{}));
        state_machine_.Process(lps35hw::Event::None);    // keeps it going
        Verify();
        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        EXPECT_CALL(mock_callback_, GetRegisterValue(0x10, 3, _)).WillOnce(Invoke([](uint8_t, uint8_t, uint8_t[]) { return core::Status{}; }));
        // on entry to ReadingReference state
        EXPECT_CALL(mock_callback_, StartRegisterRead(0x15, 3)).WillOnce(Return(core::Status{}));
        state_machine_.Process(lps35hw::Event::None);    // keeps it going
        Verify();
        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        EXPECT_CALL(mock_callback_, GetRegisterValue(0x15, 3, _)).WillOnce(Invoke([this](uint8_t, uint8_t, uint8_t value[]) {
            value[0] = static_cast<uint8_t>(reference_pressure_ & 0xFF);
            value[1] = static_cast<uint8_t>((reference_pressure_ >> 8) & 0xFF);
            value[2] = static_cast<uint8_t>((reference_pressure_ >> 16) & 0xFF);
            return core::Status{};
        }));
        state_machine_.Process(lps35hw::Event::None);    // keeps it going
        Verify();
        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        ASSERT_TRUE(state_machine_.IsIdling());    // should be idling after initialization
    }

    void Measure() {
        EXPECT_CALL(mock_callback_, StartRegisterRead(0x28, 5)).WillOnce(Return(core::Status{}));
        state_machine_.Process(lps35hw::Event::Measure);    // starts the state machine
        Verify();
        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        EXPECT_CALL(mock_callback_, GetRegisterValue(0x28, 5, _)).WillOnce(Return(core::Status{core::Result::NotReady, core::Cause::State}));
        EXPECT_CALL(mock_callback_, OnError(core::Status{core::Result::NotReady, core::Cause::State})).Times(0);
        state_machine_.Process(lps35hw::Event::None);    // keeps it going
        Verify();
        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        EXPECT_CALL(mock_callback_, GetRegisterValue(0x28, 5, _)).WillOnce(Invoke([](uint8_t, uint8_t, uint8_t value[]) {
            int32_t differential_pressure = 0U;
            uint16_t temperature = 2000;    // 20.00 C in hundredths of a degree
            value[0] = static_cast<uint8_t>(differential_pressure & 0xFF);
            value[1] = static_cast<uint8_t>((differential_pressure >> 8) & 0xFF);
            value[2] = static_cast<uint8_t>((differential_pressure >> 16) & 0xFF);
            value[3] = static_cast<uint8_t>((temperature >> 0) & 0xFF);
            value[4] = static_cast<uint8_t>((temperature >> 8) & 0xFF);
            return core::Status{};
        }));
        EXPECT_CALL(mock_callback_, OnReading(_, _)).WillOnce(Invoke([this](::lps35hw::RawPressure pressure, ::lps35hw::RawTemperature temperature) {
            EXPECT_EQ(pressure, reference_pressure_);
            EXPECT_EQ(temperature, 2000U);
        }));
        EXPECT_CALL(mock_callback_, OnError(core::Status{core::Result::NotReady, core::Cause::State})).Times(0);

        state_machine_.Process(lps35hw::Event::None);    // keeps it going
        Verify();
        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        ASSERT_TRUE(state_machine_.IsIdling());    // should be idling after initialization
    }

    jarnax::JumpTimer jump_timer_;
    jarnax::lps35hw::MockCallback mock_callback_;
    jarnax::lps35hw::StateMachine state_machine_;
    int32_t const reference_pressure_{4058521};    // 800ft in hPa*4096
};

TEST_F(LPS35HWStateMachineTest, Empty) {}

TEST_F(LPS35HWStateMachineTest, Initialize) {
    Initialize();
}

TEST_F(LPS35HWStateMachineTest, Measure) {
    Initialize();
    Measure();
}

}    // namespace jarnax

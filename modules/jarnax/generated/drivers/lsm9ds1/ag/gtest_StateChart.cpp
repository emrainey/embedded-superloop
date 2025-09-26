#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "StateChart.hpp"
#include <gtest/JumpClock.hpp>

using ::testing::_;
using ::testing::Test;
using ::testing::Invoke;
using ::testing::Return;

namespace core {

class MockClock : public time::MonotonicClock {
public:
    MOCK_METHOD(time::MicroSeconds, Now, (), (const override));
};

} // namespace core

namespace jarnax::drivers::lsm9ds1 {

// Create a Mock of the Callbacks
class MockCallback : public StateChart::Callback {
public:
    MOCK_METHOD(core::Status, ReadIdentity, (), ( override));
    MOCK_METHOD(bool, IsCorrectIdentity, (), (const override));
    MOCK_METHOD(bool, ConfigurationComplete, (), (const override));
    MOCK_METHOD(core::Status, ReadDataReady, (), ( override));
    MOCK_METHOD(bool, DataReady, (), (const override));
    MOCK_METHOD(core::Status, ReadAcceleration, (), ( override));
    MOCK_METHOD(core::Status, ReadGyroscope, (), ( override));
    MOCK_METHOD(core::Status, ReadTemperature, (), ( override));
    MOCK_METHOD(bool, MeasurementComplete, (), (const override));
    MOCK_METHOD(void, OnOutput, (core::Event<Outputs> output), (override));
    virtual ~MockCallback() = default;
};

class StateChartTest : public ::testing::Test {
public:
    void SetUp() override {
        clock_.Jump(core::time::MicroSeconds{0U});
        // Initialize the state chart and any necessary state
        stateChart_.Enter();
    }
    void TearDown() override {
        // Clean up any resources used by the state chart
    }
    void SpinOnce() {
        stateChart_.Trigger(Inputs::None);
    }
protected:
    core::time::MicroSeconds current_time_;
    core::time::JumpClock clock_;
    MockCallback callback_;
    StateChart stateChart_{callback_, clock_};
};

TEST_F(StateChartTest, Empty) {} // Test SetUp/TearDown

TEST_F(StateChartTest, InitialState) {
    clock_.Jump(core::time::MicroSeconds{1000U});
    // Verify the initial state of the state chart
    EXPECT_TRUE(stateChart_.Is(State::Identifying));
    SpinOnce();
}

TEST_F(StateChartTest, Transition) {
    // @TODO Clients need to fill in the details of the state transitions are there's no way to replicate people with jinja templates :)
}

}  // namespace
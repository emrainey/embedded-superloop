#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "core/Units.hpp"
#include "jarnax/winbond/WinbondStateMachine.hpp"

using ::testing::Return;
// using ::testing::WillOnce;

namespace jarnax {

using namespace core::units;

class MockDriver : public winbond::Listener, public winbond::Executor {
public:
    MOCK_METHOD(void, OnEvent, (winbond::Event event, core::Status status), ());
    MOCK_METHOD(core::Status, Command, (winbond::Instruction instruction), ());
    MOCK_METHOD(bool, IsCommandComplete, (), (const));
    MOCK_METHOD(core::Status, GetStatusAndData, (), ());
    MOCK_METHOD(bool, IsPresent, (), (const));
};

class TestWinbondStateMachine : public ::testing::Test {
public:
    TestWinbondStateMachine()
        : mock_driver_{}
        , state_machine_{mock_driver_, mock_driver_} {}
    void SetUp() override {
        EXPECT_CALL(mock_driver_, OnEvent(winbond::Event::Entered, core::Status{core::Result::Success, core::Cause::State}));
        // Initialize the state machine
        state_machine_.Initialize();
        Verify();
    }
    void TearDown() override { Verify(); }

    void Verify() {
        ::testing::Mock::VerifyAndClearExpectations(&mock_driver_);
        ::testing::Mock::VerifyAndClearExpectations(&state_machine_);
    }

    void Startup() {
        EXPECT_CALL(mock_driver_, IsPresent()).WillOnce(Return(true));
        EXPECT_CALL(mock_driver_, Command(winbond::Instruction::EnableReset))
            .WillOnce(Return(core::Status{core::Result::Success, core::Cause::State}));
        state_machine_.Process(winbond::Event::None);
        ASSERT_FALSE(state_machine_.IsReady());
        Verify();
        // called the the oncycle
        EXPECT_CALL(mock_driver_, IsCommandComplete()).WillOnce(Return(false));
        state_machine_.Process(winbond::Event::None);
        Verify();
        //==========================
        // called the the oncycle
        EXPECT_CALL(mock_driver_, IsCommandComplete()).WillOnce(Return(true));
        EXPECT_CALL(mock_driver_, GetStatusAndData()).WillOnce(Return(core::Status{core::Result::Success, core::Cause::Hardware}));
        EXPECT_CALL(mock_driver_, OnEvent(winbond::Event::Reset, core::Status{core::Result::Success, core::Cause::Hardware}));
        EXPECT_CALL(mock_driver_, Command(winbond::Instruction::ReleasePowerDown))
            .WillOnce(Return(core::Status{core::Result::Success, core::Cause::State}));
        state_machine_.Process(winbond::Event::None);
        Verify();
        //==========================
        // called the the oncycle
        EXPECT_CALL(mock_driver_, IsCommandComplete()).WillOnce(Return(true));
        EXPECT_CALL(mock_driver_, GetStatusAndData()).WillOnce(Return(core::Status{core::Result::Success, core::Cause::Hardware}));
        EXPECT_CALL(mock_driver_, OnEvent(winbond::Event::PowerOn, core::Status{core::Result::Success, core::Cause::Hardware}));
        EXPECT_CALL(mock_driver_, Command(winbond::Instruction::ReadUniqueId))
            .WillOnce(Return(core::Status{core::Result::Success, core::Cause::State}));
        state_machine_.Process(winbond::Event::None);
        Verify();
        //==========================
        // called the the oncycle
        EXPECT_CALL(mock_driver_, IsCommandComplete()).WillOnce(Return(true));
        EXPECT_CALL(mock_driver_, GetStatusAndData()).WillOnce(Return(core::Status{core::Result::Success, core::Cause::Hardware}));
        EXPECT_CALL(mock_driver_, OnEvent(winbond::Event::Identify, core::Status{core::Result::Success, core::Cause::Hardware}));
        state_machine_.Process(winbond::Event::None);
        Verify();
        //==========================
        ASSERT_TRUE(state_machine_.IsReady());    // should be in Waiting
    }

    void PowerOff() {
        // called by the entry of PowerOff
        EXPECT_CALL(mock_driver_, Command(winbond::Instruction::PowerDown)).WillOnce(Return(core::Status{core::Result::Success, core::Cause::State}));
        state_machine_.Process(winbond::Event::PowerOff);
        Verify();
        //==========================
        // called the the oncycle
        EXPECT_CALL(mock_driver_, IsCommandComplete()).WillOnce(Return(false));
        state_machine_.Process(winbond::Event::None);
        Verify();
        //==========================
        // called the the oncycle
        EXPECT_CALL(mock_driver_, IsCommandComplete()).WillOnce(Return(true));
        EXPECT_CALL(mock_driver_, GetStatusAndData()).WillOnce(Return(core::Status{core::Result::Success, core::Cause::Hardware}));
        EXPECT_CALL(mock_driver_, OnEvent(winbond::Event::PowerOff, core::Status{core::Result::Success, core::Cause::Hardware}));
        state_machine_.Process(winbond::Event::None);
        ASSERT_TRUE(state_machine_.IsReady());    // should be in Waiting
        Verify();
    }

protected:
    MockDriver mock_driver_;
    winbond::WinbondStateMachine state_machine_;
};

TEST_F(TestWinbondStateMachine, EmptySetup) {
}

TEST_F(TestWinbondStateMachine, PowerCycle) {
    //==========================
    Startup();
    //==========================
    PowerOff();
    //==========================
}

}    // namespace jarnax
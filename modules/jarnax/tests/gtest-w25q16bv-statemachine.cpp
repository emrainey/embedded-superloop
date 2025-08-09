#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "core/Units.hpp"
#include "jarnax/drivers/w25q16bv/StateMachine.hpp"

using ::testing::Return;
// using ::testing::WillOnce;

namespace jarnax {

using namespace core::units;

class MockDriver : public drivers::w25q16bv::Listener, public drivers::w25q16bv::Executor {
public:
    MOCK_METHOD(void, OnEvent, (drivers::w25q16bv::Event event, core::Status status), ());
    MOCK_METHOD(core::Status, Command, (drivers::w25q16bv::Instruction instruction), ());
    MOCK_METHOD(bool, IsCommandComplete, (), (const));
    MOCK_METHOD(core::Status, GetStatusAndData, (), ());
    MOCK_METHOD(bool, IsPresent, (), (const));
    virtual ~MockDriver() = default;
};

class TestW25Q16VStateMachine : public ::testing::Test {
public:
    TestW25Q16VStateMachine()
        : mock_driver_{}
        , state_machine_{mock_driver_, mock_driver_} {}
    void SetUp() override {
        EXPECT_CALL(mock_driver_, OnEvent(drivers::w25q16bv::Event::Entered, core::Status{core::Result::Success, core::Cause::State}));
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
        EXPECT_CALL(mock_driver_, Command(drivers::w25q16bv::Instruction::EnableReset))
            .WillOnce(Return(core::Status{core::Result::Success, core::Cause::State}));
        state_machine_.Process(drivers::w25q16bv::Event::None);
        ASSERT_FALSE(state_machine_.IsReady());
        Verify();
        // called the the oncycle
        EXPECT_CALL(mock_driver_, IsCommandComplete()).WillOnce(Return(false));
        state_machine_.Process(drivers::w25q16bv::Event::None);
        Verify();
        //==========================
        // called the the oncycle
        EXPECT_CALL(mock_driver_, IsCommandComplete()).WillOnce(Return(true));
        EXPECT_CALL(mock_driver_, GetStatusAndData()).WillOnce(Return(core::Status{core::Result::Success, core::Cause::Hardware}));
        EXPECT_CALL(mock_driver_, OnEvent(drivers::w25q16bv::Event::Reset, core::Status{core::Result::Success, core::Cause::Hardware}));
        EXPECT_CALL(mock_driver_, Command(drivers::w25q16bv::Instruction::ReleasePowerDown))
            .WillOnce(Return(core::Status{core::Result::Success, core::Cause::State}));
        state_machine_.Process(drivers::w25q16bv::Event::None);
        Verify();
        //==========================
        // called the the oncycle
        EXPECT_CALL(mock_driver_, IsCommandComplete()).WillOnce(Return(true));
        EXPECT_CALL(mock_driver_, GetStatusAndData()).WillOnce(Return(core::Status{core::Result::Success, core::Cause::Hardware}));
        EXPECT_CALL(mock_driver_, OnEvent(drivers::w25q16bv::Event::PowerOn, core::Status{core::Result::Success, core::Cause::Hardware}));
        EXPECT_CALL(mock_driver_, Command(drivers::w25q16bv::Instruction::ReadUniqueId))
            .WillOnce(Return(core::Status{core::Result::Success, core::Cause::State}));
        state_machine_.Process(drivers::w25q16bv::Event::None);
        Verify();
        //==========================
        // called the the oncycle
        EXPECT_CALL(mock_driver_, IsCommandComplete()).WillOnce(Return(true));
        EXPECT_CALL(mock_driver_, GetStatusAndData()).WillOnce(Return(core::Status{core::Result::Success, core::Cause::Hardware}));
        EXPECT_CALL(mock_driver_, OnEvent(drivers::w25q16bv::Event::Identify, core::Status{core::Result::Success, core::Cause::Hardware}));
        state_machine_.Process(drivers::w25q16bv::Event::None);
        Verify();
        //==========================
        ASSERT_TRUE(state_machine_.IsReady());    // should be in Waiting
    }

    void PowerOff() {
        // called by the entry of PowerOff
        EXPECT_CALL(mock_driver_, Command(drivers::w25q16bv::Instruction::PowerDown))
            .WillOnce(Return(core::Status{core::Result::Success, core::Cause::State}));
        state_machine_.Process(drivers::w25q16bv::Event::PowerOff);
        Verify();
        //==========================
        // called the the oncycle
        EXPECT_CALL(mock_driver_, IsCommandComplete()).WillOnce(Return(false));
        state_machine_.Process(drivers::w25q16bv::Event::None);
        Verify();
        //==========================
        // called the the oncycle
        EXPECT_CALL(mock_driver_, IsCommandComplete()).WillOnce(Return(true));
        EXPECT_CALL(mock_driver_, GetStatusAndData()).WillOnce(Return(core::Status{core::Result::Success, core::Cause::Hardware}));
        EXPECT_CALL(mock_driver_, OnEvent(drivers::w25q16bv::Event::PowerOff, core::Status{core::Result::Success, core::Cause::Hardware}));
        state_machine_.Process(drivers::w25q16bv::Event::None);
        ASSERT_TRUE(state_machine_.IsReady());    // should be in Waiting
        Verify();
    }

protected:
    MockDriver mock_driver_;
    drivers::w25q16bv::StateMachine state_machine_;
};

TEST_F(TestW25Q16VStateMachine, EmptySetup) {}

TEST_F(TestW25Q16VStateMachine, PowerCycle) {
    //==========================
    Startup();
    //==========================
    PowerOff();
    //==========================
}

}    // namespace jarnax

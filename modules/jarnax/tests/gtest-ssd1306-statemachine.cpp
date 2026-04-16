#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "jarnax/drivers/ssd1306/MockClient.hpp"
#include "jarnax/drivers/ssd1306/StateMachine.hpp"

using ::testing::DoAll;
using ::testing::Invoke;
using ::testing::Return;
using ::testing::SetArgReferee;
using ::testing::StrictMock;

namespace jarnax {
namespace {

using drivers::ssd1306::Event;
using drivers::ssd1306::MockClient;
using drivers::ssd1306::Sequence;
using drivers::ssd1306::State;
using drivers::ssd1306::StateMachine;

const core::Status kSuccess{core::Result::Success, core::Cause::State};
const core::Status kFailure{core::Result::Failure, core::Cause::State};

core::Status VerifyPowerOnSequence(Sequence sequence) {
    EXPECT_EQ(sequence.size(), 46U);
    if (sequence.size() < 2U) {
        return kFailure;
    }
    EXPECT_EQ(sequence[0], ::ssd1306::Control::CommandMode);
    EXPECT_EQ(sequence[1], ::ssd1306::Command::DisplayOff);
    EXPECT_EQ(sequence[sequence.size() - 2U], ::ssd1306::Control::CommandMode);
    EXPECT_EQ(sequence[sequence.size() - 1U], ::ssd1306::Command::DisplayOn);
    return core::Status{core::Result::Success, core::Cause::State};
}

core::Status VerifyPowerOffSequence(Sequence sequence) {
    EXPECT_EQ(sequence.size(), 4U);
    if (sequence.size() != 4U) {
        return core::Status{core::Result::Failure, core::Cause::State};
    }
    EXPECT_EQ(sequence[0], ::ssd1306::Control::CommandMode);
    EXPECT_EQ(sequence[1], ::ssd1306::Command::InverseDisplay);
    EXPECT_EQ(sequence[2], ::ssd1306::Control::CommandMode);
    EXPECT_EQ(sequence[3], ::ssd1306::Command::DisplayOff);
    return core::Status{core::Result::Success, core::Cause::State};
}

core::Status VerifyRenderSequence(Sequence sequence) {
    EXPECT_EQ(sequence.size(), 17U);
    if (sequence.size() < 2U) {
        return core::Status{core::Result::Failure, core::Cause::State};
    }
    EXPECT_EQ(sequence[0], ::ssd1306::Control::CommandMode);
    EXPECT_EQ(sequence[1], ::ssd1306::Command::MemoryAddressingMode);
    EXPECT_EQ(sequence[sequence.size() - 1U], ::ssd1306::Control::DataMode);
    return core::Status{core::Result::Success, core::Cause::State};
}

class SSD1306StateMachineTest : public ::testing::Test {
public:
    SSD1306StateMachineTest()
        : mock_client_{}
        , state_machine_{mock_client_} {}

protected:
    void SetUp() override {
        state_machine_.Enter();
        ASSERT_TRUE(state_machine_.Is(State::Idle));
        // verify expectations in the setup sequence
        ::testing::Mock::VerifyAndClearExpectations(&mock_client_);
    }

    void TearDown() override { ::testing::Mock::VerifyAndClearExpectations(&mock_client_); }

    void BeginPowerOn() {
        state_machine_.Process(Event::PowerOn);
        ASSERT_TRUE(state_machine_.Is(State::PoweringOn));
        ::testing::Mock::VerifyAndClearExpectations(&mock_client_);
    }

    void BeginUpdate() {
        state_machine_.Process(Event::Update);
        // the SM will enter Updating but won't do it yet.
        ASSERT_TRUE(state_machine_.Is(State::Updating));
        ::testing::Mock::VerifyAndClearExpectations(&mock_client_);
    }

    void BeginPowerOff() {
        state_machine_.Process(Event::PowerOff);
        ASSERT_TRUE(state_machine_.Is(State::PoweringOff));
        ::testing::Mock::VerifyAndClearExpectations(&mock_client_);
    }

    void CompleteAwaiting(Event event, core::Status status) {
        EXPECT_CALL(mock_client_, CompleteCommand(::testing::_)).WillOnce(DoAll(SetArgReferee<0>(status), Return(true)));
        EXPECT_CALL(mock_client_, IsReadyForPreparation()).WillOnce(Return(true));
        EXPECT_CALL(mock_client_, OnEvent(event, status));

        state_machine_.Process(Event::None);

        ASSERT_TRUE(state_machine_.Is(State::Idle));
        ::testing::Mock::VerifyAndClearExpectations(&mock_client_);
    }

    StrictMock<MockClient> mock_client_;
    StateMachine state_machine_;
};

TEST_F(SSD1306StateMachineTest, EmptySetupStartsInIdle) {}

TEST_F(SSD1306StateMachineTest, NoPresenceLeadsToError) {
    BeginPowerOn();

    EXPECT_CALL(mock_client_, IsPresent()).WillRepeatedly(Return(false));
    EXPECT_CALL(mock_client_, OnEvent(Event::PowerOn, core::Status{core::Result::NotAvailable, core::Cause::Hardware}));
    state_machine_.Process(Event::None);
    EXPECT_TRUE(state_machine_.Is(State::Error));
}

TEST_F(SSD1306StateMachineTest, PowerOnCompletesOnlyAfterPreparationBecomesReady) {
    BeginPowerOn();

    EXPECT_CALL(mock_client_, IsPresent()).WillOnce(Return(true));
    EXPECT_CALL(mock_client_, PrepareCommand(::testing::_)).WillOnce(Invoke(VerifyPowerOnSequence));
    EXPECT_CALL(mock_client_, Issue()).WillOnce(Return(kSuccess));
    state_machine_.Process(Event::None);
    ASSERT_TRUE(state_machine_.Is(State::Awaiting));

    EXPECT_CALL(mock_client_, CompleteCommand(::testing::_)).WillOnce(Return(false));
    state_machine_.Process(Event::None);
    EXPECT_TRUE(state_machine_.Is(State::Awaiting));

    EXPECT_CALL(mock_client_, CompleteCommand(::testing::_)).WillOnce(DoAll(SetArgReferee<0>(kSuccess), Return(true)));
    EXPECT_CALL(mock_client_, IsReadyForPreparation()).WillOnce(Return(false));
    state_machine_.Process(Event::None);
    EXPECT_TRUE(state_machine_.Is(State::Awaiting));

    CompleteAwaiting(Event::PowerOn, core::Status{core::Result::Success, core::Cause::State});
}

TEST_F(SSD1306StateMachineTest, UpdateUsesRenderSequenceAndCompletes) {
    BeginUpdate();

    EXPECT_CALL(mock_client_, PrepareRender(::testing::_)).WillOnce(Invoke(VerifyRenderSequence));
    EXPECT_CALL(mock_client_, Issue()).WillOnce(Return(core::Status{core::Result::Success, core::Cause::State}));
    state_machine_.Process(Event::None);
    ASSERT_TRUE(state_machine_.Is(State::Awaiting));

    CompleteAwaiting(Event::Update, core::Status{core::Result::Success, core::Cause::State});
}

TEST_F(SSD1306StateMachineTest, DeferredUpdateWhileAwaitingRunsAfterFirstTransactionRecycles) {
    // Phase 1: expect transition into Updating.
    BeginUpdate();

    // Phase 2: expect first update transaction issue, then execute one cycle.
    EXPECT_CALL(mock_client_, PrepareRender(::testing::_)).WillOnce(Invoke(VerifyRenderSequence));
    EXPECT_CALL(mock_client_, Issue()).WillOnce(Return(core::Status{core::Result::Success, core::Cause::State}));
    state_machine_.Process(Event::None);
    ASSERT_TRUE(state_machine_.Is(State::Awaiting));
    ::testing::Mock::VerifyAndClearExpectations(&mock_client_);

    // Phase 3: while awaiting, expect in-flight completion check and queue a deferred update.
    EXPECT_CALL(mock_client_, CompleteCommand(::testing::_)).WillOnce(Return(false));
    state_machine_.Process(Event::Update);
    ASSERT_TRUE(state_machine_.Is(State::Awaiting));
    ::testing::Mock::VerifyAndClearExpectations(&mock_client_);

    // Phase 4: expect first update completion callback and return to Idle.
    CompleteAwaiting(Event::Update, core::Status{core::Result::Success, core::Cause::State});

    // Phase 5: expect deferred update to be consumed from Idle on the next cycle.
    state_machine_.Process(Event::None);
    ASSERT_TRUE(state_machine_.Is(State::Updating));
    ::testing::Mock::VerifyAndClearExpectations(&mock_client_);

    // Phase 6: expect deferred update to issue and then await completion.
    EXPECT_CALL(mock_client_, PrepareRender(::testing::_)).WillOnce(Invoke(VerifyRenderSequence));
    EXPECT_CALL(mock_client_, Issue()).WillOnce(Return(core::Status{core::Result::Success, core::Cause::State}));
    state_machine_.Process(Event::None);
    ASSERT_TRUE(state_machine_.Is(State::Awaiting));
    ::testing::Mock::VerifyAndClearExpectations(&mock_client_);

    // Phase 7: expect deferred update completion callback.
    CompleteAwaiting(Event::Update, core::Status{core::Result::Success, core::Cause::State});
}

TEST_F(SSD1306StateMachineTest, PowerOffUsesPowerOffSequenceAndCompletes) {
    BeginPowerOff();

    EXPECT_CALL(mock_client_, PrepareCommand(::testing::_)).WillOnce(Invoke(VerifyPowerOffSequence));
    EXPECT_CALL(mock_client_, Issue()).WillOnce(Return(core::Status{core::Result::Success, core::Cause::State}));
    state_machine_.Process(Event::None);
    ASSERT_TRUE(state_machine_.Is(State::Awaiting));
    ::testing::Mock::VerifyAndClearExpectations(&mock_client_);

    CompleteAwaiting(Event::PowerOff, core::Status{core::Result::Success, core::Cause::State});
}

TEST_F(SSD1306StateMachineTest, PowerOnPrepareFailureSignalsErrorThenReturnsIdle) {
    BeginPowerOn();

    EXPECT_CALL(mock_client_, IsPresent()).WillOnce(Return(true));
    EXPECT_CALL(mock_client_, PrepareCommand(::testing::_)).WillOnce(Return(kFailure));
    EXPECT_CALL(mock_client_, OnEvent(Event::PowerOn, core::Status{core::Result::Failure, core::Cause::State}));
    state_machine_.Process(Event::None);
    ASSERT_TRUE(state_machine_.Is(State::Error));
    ::testing::Mock::VerifyAndClearExpectations(&mock_client_);

    state_machine_.Process(Event::None);
    EXPECT_TRUE(state_machine_.Is(State::Idle));
    ::testing::Mock::VerifyAndClearExpectations(&mock_client_);
}

TEST_F(SSD1306StateMachineTest, PowerOnIssueFailureSignalsErrorThenReturnsIdle) {
    BeginPowerOn();

    EXPECT_CALL(mock_client_, IsPresent()).WillOnce(Return(true));
    EXPECT_CALL(mock_client_, PrepareCommand(::testing::_)).WillOnce(Return(kSuccess));
    EXPECT_CALL(mock_client_, Issue()).WillOnce(Return(kFailure));
    EXPECT_CALL(mock_client_, OnEvent(Event::PowerOn, kFailure));
    state_machine_.Process(Event::None);
    ASSERT_TRUE(state_machine_.Is(State::Error));
    ::testing::Mock::VerifyAndClearExpectations(&mock_client_);

    state_machine_.Process(Event::None);
    EXPECT_TRUE(state_machine_.Is(State::Idle));
    ::testing::Mock::VerifyAndClearExpectations(&mock_client_);
}

TEST_F(SSD1306StateMachineTest, UpdatePrepareFailureSignalsErrorThenReturnsIdle) {
    BeginUpdate();

    EXPECT_CALL(mock_client_, PrepareRender(::testing::_)).WillOnce(Return(kFailure));
    EXPECT_CALL(mock_client_, OnEvent(Event::Update, kFailure));
    state_machine_.Process(Event::None);
    ASSERT_TRUE(state_machine_.Is(State::Error));
    ::testing::Mock::VerifyAndClearExpectations(&mock_client_);

    state_machine_.Process(Event::None);
    EXPECT_TRUE(state_machine_.Is(State::Idle));
    ::testing::Mock::VerifyAndClearExpectations(&mock_client_);
}

TEST_F(SSD1306StateMachineTest, UpdateIssueFailureSignalsErrorThenReturnsIdle) {
    BeginUpdate();

    EXPECT_CALL(mock_client_, PrepareRender(::testing::_)).WillOnce(Return(kSuccess));
    EXPECT_CALL(mock_client_, Issue()).WillOnce(Return(kFailure));
    EXPECT_CALL(mock_client_, OnEvent(Event::Update, kFailure));
    state_machine_.Process(Event::None);
    ASSERT_TRUE(state_machine_.Is(State::Error));
    ::testing::Mock::VerifyAndClearExpectations(&mock_client_);

    state_machine_.Process(Event::None);
    EXPECT_TRUE(state_machine_.Is(State::Idle));
    ::testing::Mock::VerifyAndClearExpectations(&mock_client_);
}

TEST_F(SSD1306StateMachineTest, PowerOffIssueFailureSignalsErrorThenReturnsIdle) {
    BeginPowerOff();

    EXPECT_CALL(mock_client_, PrepareCommand(::testing::_)).WillOnce(Return(kSuccess));
    EXPECT_CALL(mock_client_, Issue()).WillOnce(Return(kFailure));
    EXPECT_CALL(mock_client_, OnEvent(Event::PowerOff, kFailure));
    state_machine_.Process(Event::None);
    ASSERT_TRUE(state_machine_.Is(State::Error));
    ::testing::Mock::VerifyAndClearExpectations(&mock_client_);

    state_machine_.Process(Event::None);
    EXPECT_TRUE(state_machine_.Is(State::Idle));
    ::testing::Mock::VerifyAndClearExpectations(&mock_client_);
}

TEST_F(SSD1306StateMachineTest, PowerOffPrepareFailureLeavesMachineInPoweringOff) {
    BeginPowerOff();

    EXPECT_CALL(mock_client_, PrepareCommand(::testing::_)).WillOnce(Return(kFailure));
    state_machine_.Process(Event::None);

    EXPECT_TRUE(state_machine_.Is(State::PoweringOff));
}

}    // namespace
}    // namespace jarnax

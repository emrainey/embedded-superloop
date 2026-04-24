#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "core/Status.hpp"
#include "core/Units.hpp"
#include "gtest/Status.hpp"
#include "jarnax/Context.hpp"
#include "jarnax/Coordinator.hpp"
#include "jarnax/JumpTimer.hpp"
#include "jarnax/TestContext.hpp"
#include "jarnax/Transactable.hpp"
#include "jarnax/Transactor.hpp"

using ::testing::Return;
// using ::testing::WillOnce;

namespace jarnax {

using namespace core::units;

class TestTransaction : public Transactable<TestTransaction, 3> {
public:
    TestTransaction(Timer& timer)
        : Transactable{timer} {}
    void Clear() { return; }
};

class MockTransactor : public Transactor<TestTransaction> {
public:
    MOCK_METHOD(core::Status, Verify, (TestTransaction&), (override));
    MOCK_METHOD(core::Status, Start, (TestTransaction&), (override));
    MOCK_METHOD(core::Status, Check, (TestTransaction&), (override));
    MOCK_METHOD(core::Status, Cancel, (TestTransaction&), (override));
    virtual ~MockTransactor() = default;
};

static constexpr std::size_t Depth = 1U;

class TestCoordinator : public Coordinator<TestTransaction, Depth> {
public:
    TestCoordinator(Transactor<TestTransaction>& driver)
        : Coordinator{driver} {}
};

class CoordinatorTest : public ::testing::Test {
public:
    CoordinatorTest() { jarnax::GetContext().Initialize(); }
    void SetUp() override {}
    void TearDown() override {}

protected:
    JumpTimer timer;
    TestTransaction txn{timer};
    MockTransactor mock;
    TestCoordinator coord{mock};
    core::Status success{core::Result::Success, core::Cause::State};
    core::Status busy{core::Result::Busy, core::Cause::State};
    core::Status full{core::Result::ExceededLimit, core::Cause::Resource};
    core::Status not_initialized{core::Result::NotInitialized, core::Cause::Parameter};
    core::Status invalid_value{core::Result::InvalidValue, core::Cause::Parameter};
    core::Status timeout{core::Result::Timeout, core::Cause::State};
    core::Status unavailable_hardware{core::Result::NotAvailable, core::Cause::Hardware};
    core::Status verify_failed{core::Result::NotSupported, core::Cause::Hardware};
};

TEST_F(CoordinatorTest, Empty) {}

TEST_F(CoordinatorTest, BadParameter) {
    core::Status status = coord.Schedule(nullptr);
    ASSERT_STATUS_EQ(status, core::Result::InvalidValue, core::Cause::Parameter);
    ASSERT_EQ(0, coord.GetCoordinatorStatistics().accepted);
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().rejected);
}

TEST_F(CoordinatorTest, NotInitialized) {
    core::Status status = coord.Schedule(&txn);
    ASSERT_STATUS_EQ(status, core::Result::NotInitialized, core::Cause::Parameter);
    ASSERT_EQ(0, coord.GetCoordinatorStatistics().accepted);
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().rejected);
}

TEST_F(CoordinatorTest, Verify) {
    EXPECT_TRUE(txn.Inform(TestTransaction::Event::Initialized));
    EXPECT_CALL(mock, Verify(testing::_)).WillOnce(Return(success));
    core::Status status = coord.Schedule(&txn);
    ASSERT_TRUE(txn.IsQueued());
    ASSERT_STATUS_EQ(status, core::Result::Success, core::Cause::State);
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().accepted);
    ASSERT_EQ(0, coord.GetCoordinatorStatistics().rejected);
}

TEST_F(CoordinatorTest, VerifyFailureIsReturned) {
    EXPECT_TRUE(txn.Inform(TestTransaction::Event::Initialized));
    EXPECT_CALL(mock, Verify(testing::_)).WillOnce(Return(verify_failed));
    core::Status status = coord.Schedule(&txn);
    ASSERT_FALSE(txn.IsQueued());
    ASSERT_FALSE(txn.IsComplete());
    ASSERT_TRUE(txn.IsInitialized());
    ASSERT_STATUS_EQ(status, core::Result::NotSupported, core::Cause::Hardware);
    ASSERT_EQ(0, coord.GetCoordinatorStatistics().accepted);
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().rejected);
}

TEST_F(CoordinatorTest, DuplicateScheduleReturnsNotInitialized) {
    EXPECT_TRUE(txn.Inform(TestTransaction::Event::Initialized));
    EXPECT_CALL(mock, Verify(testing::_)).WillOnce(Return(success));
    core::Status status = coord.Schedule(&txn);
    ASSERT_TRUE(txn.IsQueued());
    ASSERT_STATUS_EQ(status, core::Result::Success, core::Cause::State);
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().accepted);
    ASSERT_EQ(0, coord.GetCoordinatorStatistics().rejected);

    status = coord.Schedule(&txn);
    ASSERT_STATUS_EQ(status, core::Result::NotInitialized, core::Cause::Parameter);
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().accepted);
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().rejected);
}

TEST_F(CoordinatorTest, VerifyFailureDoesNotConsumeQueueSlot) {
    TestTransaction txn2{timer};
    EXPECT_TRUE(txn.Inform(TestTransaction::Event::Initialized));
    EXPECT_TRUE(txn2.Inform(TestTransaction::Event::Initialized));

    EXPECT_CALL(mock, Verify(testing::_)).WillOnce(Return(verify_failed));
    core::Status status = coord.Schedule(&txn);
    ASSERT_FALSE(txn.IsQueued());
    ASSERT_FALSE(txn.IsComplete());
    ASSERT_TRUE(txn.IsInitialized());
    ASSERT_STATUS_EQ(status, core::Result::NotSupported, core::Cause::Hardware);
    ASSERT_EQ(0, coord.GetCoordinatorStatistics().accepted);
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().rejected);

    EXPECT_CALL(mock, Verify(testing::_)).WillOnce(Return(success));
    status = coord.Schedule(&txn2);
    ASSERT_TRUE(txn2.IsQueued());
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().accepted);
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().rejected);
    ASSERT_STATUS_EQ(status, core::Result::Success, core::Cause::State);
}

TEST_F(CoordinatorTest, ScheduleRejectsInitializedTransactionThatTimedOutOnItsOwn) {
    EXPECT_TRUE(txn.Inform(TestTransaction::Event::Initialized));
    txn.SetDeadline(timer.GetMicroseconds() + 100_usec);
    timer.Jump(150_usec);

    // Progress the transaction without coordinator scheduling.
    EXPECT_TRUE(txn.Inform(TestTransaction::Event::None));
    ASSERT_TRUE(txn.IsComplete());
    ASSERT_STATUS_EQ(txn.GetStatus(), core::Result::Timeout, core::Cause::State);

    core::Status status = coord.Schedule(&txn);
    ASSERT_STATUS_EQ(status, core::Result::NotInitialized, core::Cause::Parameter);
    ASSERT_EQ(0, coord.GetCoordinatorStatistics().accepted);
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().rejected);
}

TEST_F(CoordinatorTest, Full) {
    EXPECT_TRUE(txn.Inform(TestTransaction::Event::Initialized));
    for (std::size_t i = 0; i < Depth; i++) {
        EXPECT_CALL(mock, Verify(testing::_)).WillOnce(Return(success));
        core::Status status = coord.Schedule(&txn);
        ASSERT_STATUS_EQ(status, core::Result::Success, core::Cause::State);
        ASSERT_TRUE(txn.IsQueued());
        ASSERT_EQ(i + 1, coord.GetCoordinatorStatistics().accepted);
        ASSERT_EQ(0, coord.GetCoordinatorStatistics().rejected);
    }
    // ===
    TestTransaction txn2{timer};
    EXPECT_TRUE(txn2.Inform(TestTransaction::Event::Initialized));
    core::Status status = coord.Schedule(&txn2);
    ASSERT_STATUS_EQ(status, core::Result::ExceededLimit, core::Cause::Resource);
    ASSERT_FALSE(txn2.IsQueued());
    ASSERT_FALSE(txn2.IsComplete());
    ASSERT_TRUE(txn2.IsInitialized());
    ASSERT_EQ(Depth, coord.GetCoordinatorStatistics().accepted);
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().rejected);
}

TEST_F(CoordinatorTest, CouldNotStart) {
    EXPECT_TRUE(txn.Inform(TestTransaction::Event::Initialized));
    EXPECT_CALL(mock, Verify(testing::_)).WillOnce(Return(success));
    core::Status status = coord.Schedule(&txn);
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().accepted);
    ASSERT_EQ(0, coord.GetCoordinatorStatistics().rejected);
    ASSERT_STATUS_EQ(status, core::Result::Success, core::Cause::State);
    EXPECT_CALL(mock, Start(testing::_)).WillOnce(Return(unavailable_hardware));
    coord.Execute();
    status = txn.GetStatus();
    ASSERT_TRUE(txn.IsComplete());
    ASSERT_STATUS_EQ(status, core::Result::NotAvailable, core::Cause::Hardware);
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().stalled);
}

TEST_F(CoordinatorTest, OnePass) {
    EXPECT_TRUE(txn.Inform(TestTransaction::Event::Initialized));
    EXPECT_CALL(mock, Verify(testing::_)).WillOnce(Return(success));
    core::Status status = coord.Schedule(&txn);
    ASSERT_STATUS_EQ(status, core::Result::Success, core::Cause::State);
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().accepted);
    ASSERT_EQ(0, coord.GetCoordinatorStatistics().rejected);
    ASSERT_EQ(0, coord.GetCoordinatorStatistics().started);

    EXPECT_CALL(mock, Start(testing::_)).WillOnce(Return(success));
    EXPECT_CALL(mock, Check(testing::_)).WillOnce(Return(busy));
    coord.Execute();
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().started);
    EXPECT_CALL(mock, Check(testing::_)).WillOnce(Return(success));
    coord.Execute();
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().completed);
    status = txn.GetStatus();
    ASSERT_TRUE(txn.IsComplete());
    ASSERT_STATUS_EQ(status, core::Result::Success, core::Cause::State);
}

TEST_F(CoordinatorTest, Deadline) {
    EXPECT_TRUE(txn.Inform(TestTransaction::Event::Initialized));
    txn.SetDeadline(timer.GetMicroseconds() + 100_usec);
    EXPECT_CALL(mock, Verify(testing::_)).WillOnce(Return(success));
    core::Status status = coord.Schedule(&txn);
    ASSERT_STATUS_EQ(status, core::Result::Success, core::Cause::State);
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().accepted);
    ASSERT_EQ(0, coord.GetCoordinatorStatistics().rejected);

    // ===
    ASSERT_TRUE(txn.IsQueued());
    timer.Jump(25_usec);
    EXPECT_CALL(mock, Start(testing::_)).WillOnce(Return(success));
    EXPECT_CALL(mock, Check(testing::_)).WillOnce(Return(busy));
    coord.Execute();
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().started);
    status = txn.GetStatus();
    EXPECT_STATUS_EQ(status, core::Result::Busy, core::Cause::State);
    ASSERT_FALSE(txn.IsComplete());
    ::testing::Mock::VerifyAndClearExpectations(&mock);
    // ===
    timer.Jump(25_usec);
    EXPECT_CALL(mock, Check(testing::_)).WillOnce(Return(busy));
    coord.Execute();
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().started);
    ASSERT_EQ(0, coord.GetCoordinatorStatistics().failed);
    ASSERT_EQ(0, coord.GetCoordinatorStatistics().deadline);
    ASSERT_EQ(0, coord.GetCoordinatorStatistics().completed);
    status = txn.GetStatus();
    EXPECT_STATUS_EQ(status, core::Result::Busy, core::Cause::State);
    ASSERT_FALSE(txn.IsComplete());
    ::testing::Mock::VerifyAndClearExpectations(&mock);
    // ===
    timer.Jump(25_usec);
    EXPECT_CALL(mock, Check(testing::_)).WillOnce(Return(busy));
    coord.Execute();
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().started);
    ASSERT_EQ(0, coord.GetCoordinatorStatistics().failed);
    ASSERT_EQ(0, coord.GetCoordinatorStatistics().deadline);
    ASSERT_EQ(0, coord.GetCoordinatorStatistics().completed);
    status = txn.GetStatus();
    ASSERT_LT(timer.GetMicroseconds().value(), txn.GetDeadline().value());
    EXPECT_STATUS_EQ(status, core::Result::Busy, core::Cause::State);
    EXPECT_FALSE(txn.IsComplete());
    ::testing::Mock::VerifyAndClearExpectations(&mock);
    // ===
    timer.Jump(26_usec);
    EXPECT_CALL(mock, Check(testing::_)).WillOnce(Return(busy));
    EXPECT_CALL(mock, Cancel(testing::_)).WillOnce(Return(success));
    coord.Execute();
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().started);
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().failed);
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().deadline);
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().completed);
    status = txn.GetStatus();
    EXPECT_TRUE(txn.IsComplete());
    ASSERT_GE(timer.GetMicroseconds(), txn.GetDeadline());
    EXPECT_STATUS_EQ(status, core::Result::Timeout, core::Cause::State);
    ::testing::Mock::VerifyAndClearExpectations(&mock);
}

TEST_F(CoordinatorTest, QueuedTransactionCanTimeoutWithoutDriverStartingIt) {
    EXPECT_TRUE(txn.Inform(TestTransaction::Event::Initialized));
    txn.SetDeadline(timer.GetMicroseconds() + 100_usec);
    EXPECT_CALL(mock, Verify(testing::_)).WillOnce(Return(success));

    core::Status status = coord.Schedule(&txn);
    ASSERT_STATUS_EQ(status, core::Result::Success, core::Cause::State);
    ASSERT_TRUE(txn.IsQueued());

    // Let the queued transaction miss its deadline before Execute tries to start it.
    timer.Jump(150_usec);

    EXPECT_CALL(mock, Start(testing::_)).Times(0);
    EXPECT_CALL(mock, Check(testing::_)).Times(0);
    EXPECT_CALL(mock, Cancel(testing::_)).Times(0);
    coord.Execute();

    ASSERT_TRUE(txn.IsComplete());
    ASSERT_STATUS_EQ(txn.GetStatus(), core::Result::Timeout, core::Cause::State);
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().accepted);
    ASSERT_EQ(0, coord.GetCoordinatorStatistics().rejected);
    ASSERT_EQ(0, coord.GetCoordinatorStatistics().started);
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().deadline);
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().completed);
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().forgotten);
}

TEST_F(CoordinatorTest, RetryExhaustedHardwareUnavailable) {
    EXPECT_TRUE(txn.Inform(TestTransaction::Event::Initialized));
    EXPECT_CALL(mock, Verify(testing::_)).WillOnce(Return(success));
    core::Status status = coord.Schedule(&txn);
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().accepted);
    ASSERT_EQ(0, coord.GetCoordinatorStatistics().rejected);
    ASSERT_TRUE(txn.IsQueued());
    ASSERT_STATUS_EQ(status, core::Result::Success, core::Cause::State);
    ::testing::Mock::VerifyAndClearExpectations(&mock);
    // ===
    EXPECT_CALL(mock, Start(testing::_)).WillOnce(Return(success));
    EXPECT_CALL(mock, Check(testing::_)).WillOnce(Return(unavailable_hardware));
    coord.Execute();
    status = txn.GetStatus();
    EXPECT_STATUS_EQ(status, core::Result::Busy, core::Cause::State);
    EXPECT_FALSE(txn.IsComplete());
    EXPECT_TRUE(txn.IsQueued());
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().started);
    ASSERT_EQ(0, coord.GetCoordinatorStatistics().failed);
    ASSERT_EQ(0, coord.GetCoordinatorStatistics().deadline);
    ASSERT_EQ(0, coord.GetCoordinatorStatistics().completed);
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().retried);
    ::testing::Mock::VerifyAndClearExpectations(&mock);
    // ===
    EXPECT_CALL(mock, Start(testing::_)).WillOnce(Return(success));
    EXPECT_CALL(mock, Check(testing::_)).WillOnce(Return(unavailable_hardware));
    coord.Execute();
    ASSERT_EQ(2, coord.GetCoordinatorStatistics().started);
    ASSERT_EQ(0, coord.GetCoordinatorStatistics().failed);
    ASSERT_EQ(0, coord.GetCoordinatorStatistics().deadline);
    ASSERT_EQ(0, coord.GetCoordinatorStatistics().completed);
    ASSERT_EQ(2, coord.GetCoordinatorStatistics().retried);
    status = txn.GetStatus();
    EXPECT_STATUS_EQ(status, core::Result::Busy, core::Cause::State);
    EXPECT_FALSE(txn.IsComplete());
    EXPECT_TRUE(txn.IsQueued());
    ::testing::Mock::VerifyAndClearExpectations(&mock);
    // ===
    EXPECT_CALL(mock, Start(testing::_)).WillOnce(Return(success));
    EXPECT_CALL(mock, Check(testing::_)).WillOnce(Return(unavailable_hardware));
    EXPECT_CALL(mock, Cancel(testing::_)).WillOnce(Return(success));
    coord.Execute();
    ASSERT_EQ(3, coord.GetCoordinatorStatistics().started);
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().failed);
    ASSERT_EQ(0, coord.GetCoordinatorStatistics().deadline);
    ASSERT_EQ(1, coord.GetCoordinatorStatistics().completed);
    ASSERT_EQ(2, coord.GetCoordinatorStatistics().retried);
    status = txn.GetStatus();
    EXPECT_TRUE(txn.IsComplete());
    EXPECT_STATUS_EQ(status, core::Result::NotAvailable, core::Cause::Hardware);
    ::testing::Mock::VerifyAndClearExpectations(&mock);
}

}    // namespace jarnax

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "core/Units.hpp"
#include "jarnax/Context.hpp"
#include "jarnax/Transactable.hpp"
#include "jarnax/Transactor.hpp"
#include "jarnax/Coordinator.hpp"
#include "TestContext.hpp"
#include "JumpTimer.hpp"

using ::testing::Return;
// using ::testing::WillOnce;

namespace jarnax {

using namespace core::units;

class TestTransaction : public Transactable<TestTransaction, 3> {
public:
    TestTransaction(Timer& timer) : Transactable{timer} {}
    void Clear() {
        return;
    }
};

class MockTransactor : public Transactor<TestTransaction> {
public:
    MOCK_METHOD(core::Status, Verify, (TestTransaction&), (override));
    MOCK_METHOD(core::Status, Start, (TestTransaction&), (override));
    MOCK_METHOD(core::Status, Check, (TestTransaction&), (override));
    MOCK_METHOD(core::Status, Cancel, (TestTransaction&), (override));
};

static constexpr std::size_t Depth = 1U;

class TestCoordinator : public Coordinator<TestTransaction, Depth> {
public:
    TestCoordinator(Transactor<TestTransaction>& driver)
        : Coordinator{driver} {}
};

class CoordinatorTest : public ::testing::Test {
public:
    CoordinatorTest() {
        jarnax::GetContext().Initialize();
    }
    void SetUp() override {

    }
    void TearDown() override {

    }
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
};

TEST_F(CoordinatorTest, Empty) {}

TEST_F(CoordinatorTest, BadParameter) {
    ASSERT_EQ(invalid_value, coord.Schedule(nullptr));
}

TEST_F(CoordinatorTest, NotInitialized) {
    ASSERT_EQ(not_initialized, coord.Schedule(&txn));
}

TEST_F(CoordinatorTest, Verify) {
    txn.Inform(TestTransaction::Event::Initialized);
    EXPECT_CALL(mock, Verify(testing::_)).WillOnce(Return(success));
    ASSERT_EQ(success, coord.Schedule(&txn));
}

TEST_F(CoordinatorTest, Full) {
    TestTransaction txn2{timer};
    txn.Inform(TestTransaction::Event::Initialized);
    txn2.Inform(TestTransaction::Event::Initialized);
    for (std::size_t i = 0; i < Depth; i++) {
        EXPECT_CALL(mock, Verify(testing::_)).WillOnce(Return(success));
        ASSERT_EQ(success, coord.Schedule(&txn));
    }
    ASSERT_EQ(full, coord.Schedule(&txn2));
}

TEST_F(CoordinatorTest, OnePass) {
    txn.Inform(TestTransaction::Event::Initialized);
    EXPECT_CALL(mock, Verify(testing::_)).WillOnce(Return(success));
    ASSERT_EQ(success, coord.Schedule(&txn));
    EXPECT_CALL(mock, Start(testing::_)).WillOnce(Return(success));
    EXPECT_CALL(mock, Check(testing::_)).WillOnce(Return(busy));
    coord.Execute();
    EXPECT_CALL(mock, Check(testing::_)).WillOnce(Return(success));
    coord.Execute();
    ASSERT_EQ(success, txn.GetStatus());
}

TEST_F(CoordinatorTest, Deadline) {
    txn.Inform(TestTransaction::Event::Initialized);
    txn.SetDeadline(timer.GetMicroseconds() + 100_usec);
    EXPECT_CALL(mock, Verify(testing::_)).WillOnce(Return(success));
    ASSERT_EQ(success, coord.Schedule(&txn));
    timer.Jump(200_usec);
    coord.Execute();
    ASSERT_EQ(timeout, txn.GetStatus());
}

} // namespace jarnax
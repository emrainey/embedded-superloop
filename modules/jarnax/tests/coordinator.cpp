#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "core/Units.hpp"
#include "jarnax/Context.hpp"
#include "jarnax/Transactable.hpp"
#include "jarnax/Transactor.hpp"
#include "jarnax/Coordinator.hpp"

using ::testing::Return;
// using ::testing::WillOnce;

namespace jarnax {

using namespace core::units;

class GlobalContext : public Context {
public:
    GlobalContext()
        : loop_{jarnax::GetTicker()} {}
    core::Status Initialize() override { return core::Status{}; }
    SuperLoop &GetSuperLoop(void) override { return loop_; }

protected:
    SuperLoop loop_;
};

Context &GetContext() {
    static GlobalContext my_context;
    return my_context;
}

class FakeTimer : public Timer {
public:
    FakeTimer()
        : current_{0U} {}

    Iota GetIotas(void) const override {
        Iota tmp;
        tmp = current_;
        current_ = Iota{current_.value() + 1U};
        return tmp;
    }

    MicroSeconds GetMicroseconds(void) const override {
        // 1:1 ratio of iotas to microseconds
        return MicroSeconds{GetIotas().value()};
    }

    void Jump(MicroSeconds delta) {
        // 1:1 ratio of iotas to microseconds
        current_ = current_ + Iota{delta.value()};
    }
protected:
    mutable Iota current_{0U};
};

class FakeTransaction : public Transactable<FakeTransaction, 3> {
public:
    FakeTransaction(Timer& timer) : Transactable{timer} {}
    void Clear() {
        return;
    }
};

class MockTransactor : public Transactor<FakeTransaction> {
public:
    MOCK_METHOD(core::Status, Verify, (FakeTransaction&), (override));
    MOCK_METHOD(core::Status, Start, (FakeTransaction&), (override));
    MOCK_METHOD(core::Status, Check, (FakeTransaction&), (override));
    MOCK_METHOD(core::Status, Cancel, (FakeTransaction&), (override));
};

static constexpr std::size_t Depth = 1U;

class FakeCoordinator : public Coordinator<FakeTransaction, Depth> {
public:
    FakeCoordinator(Transactor<FakeTransaction>& driver)
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
    FakeTimer timer;
    FakeTransaction txn{timer};
    MockTransactor mock;
    FakeCoordinator coord{mock};
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
    txn.Inform(FakeTransaction::Event::Initialized);
    EXPECT_CALL(mock, Verify(testing::_)).WillOnce(Return(success));
    ASSERT_EQ(success, coord.Schedule(&txn));
}

TEST_F(CoordinatorTest, Full) {
    FakeTransaction txn2{timer};
    txn.Inform(FakeTransaction::Event::Initialized);
    txn2.Inform(FakeTransaction::Event::Initialized);
    for (std::size_t i = 0; i < Depth; i++) {
        EXPECT_CALL(mock, Verify(testing::_)).WillOnce(Return(success));
        ASSERT_EQ(success, coord.Schedule(&txn));
    }
    ASSERT_EQ(full, coord.Schedule(&txn2));
}

TEST_F(CoordinatorTest, OnePass) {
    txn.Inform(FakeTransaction::Event::Initialized);
    EXPECT_CALL(mock, Verify(testing::_)).WillOnce(Return(success));
    ASSERT_EQ(success, coord.Schedule(&txn));
    EXPECT_CALL(mock, Start(testing::_)).WillOnce(Return(success));
    EXPECT_CALL(mock, Check(testing::_)).WillOnce(Return(busy));
    coord.Execute({});
    EXPECT_CALL(mock, Check(testing::_)).WillOnce(Return(success));
    coord.Execute({});
    ASSERT_EQ(success, txn.GetStatus());
}

TEST_F(CoordinatorTest, Deadline) {
    txn.Inform(FakeTransaction::Event::Initialized);
    txn.SetDeadline(timer.GetMicroseconds() + 100_usec);
    EXPECT_CALL(mock, Verify(testing::_)).WillOnce(Return(success));
    ASSERT_EQ(success, coord.Schedule(&txn));
    timer.Jump(200_usec);
    coord.Execute({});
    ASSERT_EQ(timeout, txn.GetStatus());
}

} // namespace jarnax
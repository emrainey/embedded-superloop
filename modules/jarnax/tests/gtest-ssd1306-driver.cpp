#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <jarnax/Context.hpp>
#include <jarnax/JumpTimer.hpp>
#include <jarnax/MockTransactor.hpp>
#include <jarnax/drivers/ssd1306/Driver.hpp>
#include "core/Status.hpp"
#include "core/units/MicroSeconds.hpp"
#include "gtest/Status.hpp"

using ::testing::InSequence;
using ::testing::Invoke;

namespace jarnax {
namespace {

using drivers::ssd1306::Driver;
using i2c::Transaction;

constexpr std::size_t kPowerOnSequenceSize{46U};
constexpr std::size_t kPowerOffSequenceSize{4U};
constexpr std::size_t kRenderSequenceSize{17U};
constexpr std::size_t kRenderTransferSize{kRenderSequenceSize + sizeof(::ssd1306::Image128x32)};
constexpr std::uint8_t kDisplayAddress{0x3CU};

class TestI2cDriver : public i2c::Driver {
public:
    explicit TestI2cDriver(i2c::Transactor& transactor)
        : i2c::Driver{transactor} {}

    ~TestI2cDriver() = default;
};

class SSD1306DriverTest : public ::testing::Test {
public:
    SSD1306DriverTest()
        : timer_{}
        , mock_transactor_{}
        , i2c_driver_{mock_transactor_}
        , driver_{timer_, i2c_driver_, core::GetDefaultAllocator()}
        , success_{core::Result::Success, core::Cause::State}
        , busy_{core::Result::Busy, core::Cause::State} {
        jarnax::GetContext().Initialize();
    }

protected:
    static void ExpectPowerOnTransaction(Transaction& transaction) {
        EXPECT_TRUE(transaction.IsInitialized());
        EXPECT_EQ(transaction.address.whole, i2c::Address{kDisplayAddress}.whole);
        EXPECT_EQ(transaction.desired_count, kPowerOnSequenceSize);
        EXPECT_EQ(transaction.actual_count, 0U);
        ASSERT_FALSE(transaction.buffer.IsEmpty());
        auto span = transaction.buffer.as_span();
        EXPECT_EQ(span[0], ::ssd1306::Control::CommandMode);
        EXPECT_EQ(span[1], ::ssd1306::Command::DisplayOff);
        EXPECT_EQ(span[kPowerOnSequenceSize - 2U], ::ssd1306::Control::CommandMode);
        EXPECT_EQ(span[kPowerOnSequenceSize - 1U], ::ssd1306::Command::DisplayOn);
    }

    static void ExpectRenderTransaction(Transaction& transaction) {
        EXPECT_TRUE(transaction.IsInitialized());
        EXPECT_EQ(transaction.address.whole, i2c::Address{kDisplayAddress}.whole);
        EXPECT_EQ(transaction.desired_count, kRenderTransferSize);
        EXPECT_EQ(transaction.actual_count, 0U);
        ASSERT_FALSE(transaction.buffer.IsEmpty());
        auto span = transaction.buffer.as_span();
        EXPECT_EQ(span[0], ::ssd1306::Control::CommandMode);
        EXPECT_EQ(span[1], ::ssd1306::Command::MemoryAddressingMode);
        EXPECT_EQ(span[kRenderSequenceSize - 1U], ::ssd1306::Control::DataMode);
        EXPECT_EQ(span[kRenderSequenceSize], 0x00U);
    }

    static void ExpectPowerOffTransaction(Transaction& transaction) {
        EXPECT_TRUE(transaction.IsInitialized());
        EXPECT_EQ(transaction.address.whole, i2c::Address{kDisplayAddress}.whole);
        EXPECT_EQ(transaction.desired_count, kPowerOffSequenceSize);
        EXPECT_EQ(transaction.actual_count, 0U);
        ASSERT_FALSE(transaction.buffer.IsEmpty());
        auto span = transaction.buffer.as_span();
        EXPECT_EQ(span[0], ::ssd1306::Control::CommandMode);
        EXPECT_EQ(span[1], ::ssd1306::Command::InverseDisplay);
        EXPECT_EQ(span[2], ::ssd1306::Control::CommandMode);
        EXPECT_EQ(span[3], ::ssd1306::Command::DisplayOff);
    }

    void loop(core::units::MicroSeconds duration, std::size_t iterations = 1U) {
        for (std::size_t i = 0; i < iterations; ++i) {
            std::cout << "Loop iteration " << i + 1 << "/" << iterations << ": Jumping " << duration.value() << " microseconds.\r\n";
            timer_.Jump(duration);
            i2c_driver_.Execute();
            driver_.Execute();
        }
    }

    void Initialize() {
        EXPECT_CALL(mock_transactor_, Verify(::testing::_)).WillOnce(Invoke([](Transaction& transaction) {
            ExpectPowerOnTransaction(transaction);
            return core::Status{core::Result::Success, core::Cause::State};
        }));
        EXPECT_CALL(mock_transactor_, Start(::testing::_)).WillOnce(Invoke([](Transaction& transaction) {
            EXPECT_TRUE(transaction.IsRunning());
            EXPECT_EQ(transaction.desired_count, kPowerOnSequenceSize);
            return core::Status{core::Result::Success, core::Cause::State};
        }));
        EXPECT_CALL(mock_transactor_, Check(::testing::_))
            .WillOnce(Invoke([this](Transaction& transaction) {
                EXPECT_TRUE(transaction.IsRunning());
                EXPECT_EQ(transaction.desired_count, kPowerOnSequenceSize);
                return busy_;
            }))
            .WillOnce(Invoke([](Transaction& transaction) {
                EXPECT_TRUE(transaction.IsRunning());
                transaction.actual_count = transaction.desired_count;
                return core::Status{core::Result::Success, core::Cause::State};
            }));

        // Execute: initialize, queue update while powering on, then drive both transactions to completion.
        EXPECT_EQ(driver_.Initialize(i2c::Address{kDisplayAddress}), success_);
        while (true) {
            core::Status status = driver_.GetStatus();
            if (not status.IsSuccess()) {
                ASSERT_STATUS_EQ(status, core::Result::NotReady, core::Cause::State);
            } else {
                break;
            }
            loop(core::units::MicroSeconds{1000U}, 1U);
        };
        EXPECT_TRUE(::testing::Mock::VerifyAndClearExpectations(&mock_transactor_));
    }

    void Idling(core::Result expected_result = core::Result::Success, core::Cause expected_cause = core::Cause::State) {
        // idle -> idle
        loop(core::units::MicroSeconds{100U}, 10U);
        // EXPECT_FALSE(driver_.IsUpdated());
        EXPECT_STATUS_EQ(driver_.GetStatus(), expected_result, expected_cause);
        EXPECT_TRUE(::testing::Mock::VerifyAndClearExpectations(&mock_transactor_));
    }

    void Update() {
        driver_.Update();
        // idle -> update
        loop(core::units::MicroSeconds{100U}, 1U);
        EXPECT_FALSE(driver_.IsUpdated());
        EXPECT_STATUS_EQ(driver_.GetStatus(), core::Result::Busy, core::Cause::State);
        ASSERT_TRUE(::testing::Mock::VerifyAndClearExpectations(&mock_transactor_));

        EXPECT_CALL(mock_transactor_, Verify(::testing::_)).WillOnce(Invoke([](Transaction& transaction) {
            ExpectRenderTransaction(transaction);
            return core::Status{core::Result::Success, core::Cause::State};
        }));
        loop(core::units::MicroSeconds{100U}, 1U);
        EXPECT_FALSE(driver_.IsUpdated());
        ASSERT_TRUE(::testing::Mock::VerifyAndClearExpectations(&mock_transactor_));

        EXPECT_CALL(mock_transactor_, Start(::testing::_)).WillOnce(Invoke([](Transaction& transaction) {
            EXPECT_TRUE(transaction.IsRunning());
            EXPECT_EQ(transaction.desired_count, kRenderTransferSize);
            return core::Status{core::Result::Success, core::Cause::State};
        }));
        EXPECT_CALL(mock_transactor_, Check(::testing::_))
            .WillOnce(Invoke([this](Transaction& transaction) {
                EXPECT_TRUE(transaction.IsRunning());
                EXPECT_EQ(transaction.desired_count, kRenderTransferSize);
                return busy_;
            }))
            .WillOnce(Invoke([](Transaction& transaction) {
                EXPECT_TRUE(transaction.IsRunning());
                transaction.actual_count = transaction.desired_count;
                return core::Status{core::Result::Success, core::Cause::State};
            }));
        while (true) {
            core::Status status = driver_.GetStatus();
            if (not status.IsSuccess()) {
                EXPECT_FALSE(driver_.IsUpdated());
                ASSERT_STATUS_EQ(status, core::Result::Busy, core::Cause::State);
            } else {
                EXPECT_TRUE(driver_.IsUpdated());
                ASSERT_STATUS_EQ(status, core::Result::Success, core::Cause::State);
                break;
            }
            loop(core::units::MicroSeconds{100U}, 1U);
        }
        loop(core::units::MicroSeconds{100U}, 1U);
        EXPECT_TRUE(::testing::Mock::VerifyAndClearExpectations(&mock_transactor_));
    }

    void UpdateTimeout() {
        core::units::MicroSeconds deadline{0u};
        driver_.Update();
        loop(core::units::MicroSeconds{100U}, 1U);
        EXPECT_FALSE(driver_.IsUpdated());
        ASSERT_TRUE(::testing::Mock::VerifyAndClearExpectations(&mock_transactor_));

        EXPECT_CALL(mock_transactor_, Verify(::testing::_)).WillOnce(Invoke([&deadline](Transaction& transaction) {
            ExpectRenderTransaction(transaction);
            deadline = transaction.GetDeadline();
            return core::Status{core::Result::Success, core::Cause::State};
        }));
        loop(core::units::MicroSeconds{100U}, 1U);
        EXPECT_FALSE(driver_.IsUpdated());
        ASSERT_TRUE(::testing::Mock::VerifyAndClearExpectations(&mock_transactor_));

        EXPECT_CALL(mock_transactor_, Start(::testing::_)).WillOnce(Invoke([](Transaction& transaction) {
            EXPECT_TRUE(transaction.IsRunning());
            EXPECT_EQ(transaction.desired_count, kRenderTransferSize);
            return core::Status{core::Result::Success, core::Cause::State};
        }));
        EXPECT_CALL(mock_transactor_, Check(::testing::_)).WillRepeatedly(Invoke([this](Transaction& transaction) {
            EXPECT_TRUE(transaction.IsRunning());
            EXPECT_EQ(transaction.desired_count, kRenderTransferSize);
            return busy_;
        }));
        EXPECT_CALL(mock_transactor_, Cancel(::testing::_)).WillOnce(Invoke([](Transaction& transaction) {
            EXPECT_TRUE(transaction.IsComplete());
            return core::Status{core::Result::Success, core::Cause::State};
        }));

        bool timed_out = false;
        for (std::size_t i = 0U; i < 10U; ++i) {
            core::Status status = driver_.GetStatus();
            if (not status.IsBusy()) {
                ASSERT_STATUS_EQ(status, core::Result::Timeout, core::Cause::State);
                timed_out = true;
                break;
            }
            EXPECT_FALSE(driver_.IsUpdated());
            // this only works because we're advancing the clock here _past_ the deadline in the transaction.
            loop(core::units::MicroSeconds{20'000U}, 1U);
        }
        ASSERT_GE(timer_.GetMicroseconds(), deadline);
        EXPECT_TRUE(timed_out);
        EXPECT_FALSE(driver_.IsUpdated());
        EXPECT_TRUE(::testing::Mock::VerifyAndClearExpectations(&mock_transactor_));
        EXPECT_STATUS_EQ(driver_.GetStatus(), core::Result::Timeout, core::Cause::State);
    }

    JumpTimer timer_;
    MockTransactor<Transaction> mock_transactor_;
    TestI2cDriver i2c_driver_;
    Driver driver_;
    core::Status success_;
    core::Status busy_;
};

TEST_F(SSD1306DriverTest, Empty) {}

TEST_F(SSD1306DriverTest, JustInitialize) {
    Initialize();
}

TEST_F(SSD1306DriverTest, Idling) {
    Initialize();
    Idling();
}

TEST_F(SSD1306DriverTest, LifeCycle) {
    Initialize();
    Idling();
    Update();
}

TEST_F(SSD1306DriverTest, LifeCycle2) {
    Initialize();
    Idling();
    Update();
    Idling();
    Update();
}

TEST_F(SSD1306DriverTest, UpdateTransactionTimeout) {
    Initialize();
    Update();
    Idling();
    UpdateTimeout();
    Idling();
    Update();
}

TEST_F(SSD1306DriverTest, BackToBackUpdate) {
    Initialize();
    Update();
    Update();
    Update();
    Update();
    Update();
}

}    // namespace
}    // namespace jarnax

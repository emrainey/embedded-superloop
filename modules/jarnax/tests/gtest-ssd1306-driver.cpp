#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <jarnax/Context.hpp>
#include <jarnax/JumpTimer.hpp>
#include <jarnax/MockTransactor.hpp>
#include <jarnax/drivers/ssd1306/Driver.hpp>
#include "core/units/MicroSeconds.hpp"

using ::testing::InSequence;
using ::testing::Invoke;

namespace jarnax {
namespace {

using drivers::ssd1306::Driver;
using i2c::Transaction;

constexpr std::size_t kPowerOnSequenceSize{46U};
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

    void loop(core::units::MicroSeconds duration, std::size_t iterations = 1U) {
        for (std::size_t i = 0; i < iterations; ++i) {
            timer_.Jump(duration);
            i2c_driver_.Execute();
            driver_.Execute();
        }
    }

    JumpTimer timer_;
    MockTransactor<Transaction> mock_transactor_;
    TestI2cDriver i2c_driver_;
    Driver driver_;
    core::Status success_;
    core::Status busy_;
};

TEST_F(SSD1306DriverTest, Empty) {}

TEST_F(SSD1306DriverTest, UpdateQueuedDuringPowerOnRunsAsSecondI2cTransaction) {
    // Expect: power-on transaction runs first, deferred update render transaction runs second.
    InSequence sequence;
    EXPECT_CALL(mock_transactor_, Verify(::testing::_)).WillOnce(Invoke([](Transaction& transaction) {
        ExpectPowerOnTransaction(transaction);
        return core::Status{core::Result::Success, core::Cause::State};
    }));
    // Execute: initialize, queue update while powering on, then drive both transactions to completion.
    EXPECT_EQ(driver_.Initialize(i2c::Address{kDisplayAddress}), success_);
    loop(core::units::MicroSeconds{100U}, 2U);
    EXPECT_TRUE(::testing::Mock::VerifyAndClearExpectations(&mock_transactor_));

    EXPECT_CALL(mock_transactor_, Start(::testing::_)).WillOnce(Invoke([](Transaction& transaction) {
        EXPECT_TRUE(transaction.IsRunning());
        EXPECT_EQ(transaction.desired_count, kPowerOnSequenceSize);
        return core::Status{core::Result::Success, core::Cause::State};
    }));
    EXPECT_CALL(mock_transactor_, Check(::testing::_)).WillOnce(Invoke([this](Transaction& transaction) {
        EXPECT_TRUE(transaction.IsRunning());
        EXPECT_EQ(transaction.desired_count, kPowerOnSequenceSize);
        return busy_;
    }));
    EXPECT_CALL(mock_transactor_, Check(::testing::_)).WillOnce(Invoke([](Transaction& transaction) {
        EXPECT_TRUE(transaction.IsRunning());
        transaction.actual_count = transaction.desired_count;
        return core::Status{core::Result::Success, core::Cause::State};
    }));

    driver_.Update();
    loop(core::units::MicroSeconds{100U}, 2U);
    EXPECT_TRUE(driver_.GetStatus().IsSuccess());
    EXPECT_TRUE(::testing::Mock::VerifyAndClearExpectations(&mock_transactor_));

    EXPECT_CALL(mock_transactor_, Verify(::testing::_)).WillOnce(Invoke([](Transaction& transaction) {
        ExpectRenderTransaction(transaction);
        return core::Status{core::Result::Success, core::Cause::State};
    }));
    loop(core::units::MicroSeconds{100U}, 2U);
    EXPECT_TRUE(driver_.GetStatus().IsBusy());
    EXPECT_TRUE(::testing::Mock::VerifyAndClearExpectations(&mock_transactor_));

    EXPECT_CALL(mock_transactor_, Start(::testing::_)).WillOnce(Invoke([](Transaction& transaction) {
        EXPECT_TRUE(transaction.IsRunning());
        EXPECT_EQ(transaction.desired_count, kRenderTransferSize);
        return core::Status{core::Result::Success, core::Cause::State};
    }));
    EXPECT_CALL(mock_transactor_, Check(::testing::_)).WillOnce(Invoke([](Transaction& transaction) {
        EXPECT_TRUE(transaction.IsRunning());
        transaction.actual_count = transaction.desired_count;
        return core::Status{core::Result::Success, core::Cause::State};
    }));
    loop(core::units::MicroSeconds{100U}, 2U);
    // Verify: update eventually completes successfully after the power-on command transaction.
    EXPECT_TRUE(driver_.GetStatus().IsSuccess());
    EXPECT_TRUE(driver_.IsUpdated());
    EXPECT_TRUE(::testing::Mock::VerifyAndClearExpectations(&mock_transactor_));
}

}    // namespace
}    // namespace jarnax

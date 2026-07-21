#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "core/Conversions.hpp"
#include "jarnax/JumpTimer.hpp"
#include "jarnax/net/ethernet/LAN8742A.hpp"
#include "jarnax/net/ethernet/MockPhy.hpp"

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

namespace jarnax {
namespace net {
namespace ethernet {

/// @brief Fixture to organize and run LAN8742A state machine and driver tests
class LAN8742AStateMachineTest : public ::testing::Test {
public:
    LAN8742AStateMachineTest()
        : jump_timer_{}
        , mock_phy_{}
        , driver_{jump_timer_, core::units::ConvertToIota(lan8742a::DefaultPollingInterval), mock_phy_, 0U} {}

protected:
    void SetUp() override {
        // In SetUp, trigger the initial Initialize() method.
        // Expect a write to BMCR (reg 0) with Reset bit set (0x8000).
        EXPECT_CALL(mock_phy_, Schedule(_)).WillOnce(Invoke([this](mdio::Transaction* txn) {
            EXPECT_EQ(txn->register_address, 0U);
            EXPECT_EQ(txn->operation, mdio::Operation::Write);
            EXPECT_EQ(txn->data, 0x8000U);
            last_txn_ = txn;
            txn->Inform(mdio::Transaction::Event::Scheduled);
            return core::Status{};
        }));
        driver_.Initialize();
        driver_.Execute();
        Verify();
    }

    void TearDown() override { Verify(); }

    /// @brief Verify mock expectations at checkpoints during the test
    void Verify() { ::testing::Mock::VerifyAndClearExpectations(&mock_phy_); }

    /// @brief Transition the driver from Resetting to AwaitingLink
    void ProgressReset() {
        ASSERT_NE(last_txn_, nullptr);
        last_txn_->Inform(mdio::Transaction::Event::Start);
        last_txn_->Inform(mdio::Transaction::Event::Completed, core::Status{});
        (void)last_txn_->NotifyCompletionListener();

        // Cycles the state machine, causing a read of BMCR to check reset completion status
        EXPECT_CALL(mock_phy_, Schedule(_)).WillOnce(Invoke([this](mdio::Transaction* txn) {
            EXPECT_EQ(txn->register_address, 0U);
            EXPECT_EQ(txn->operation, mdio::Operation::Read);
            last_txn_ = txn;
            txn->Inform(mdio::Transaction::Event::Scheduled);
            return core::Status{};
        }));
        driver_.Execute();
        Verify();

        // Simulate Reset still in progress (reset bit remains set)
        ASSERT_NE(last_txn_, nullptr);
        last_txn_->data = 0x8000U;
        last_txn_->Inform(mdio::Transaction::Event::Start);
        last_txn_->Inform(mdio::Transaction::Event::Completed, core::Status{});
        (void)last_txn_->NotifyCompletionListener();

        // Cycles the state machine, which schedules another read of BMCR
        EXPECT_CALL(mock_phy_, Schedule(_)).WillOnce(Invoke([this](mdio::Transaction* txn) {
            EXPECT_EQ(txn->register_address, 0U);
            EXPECT_EQ(txn->operation, mdio::Operation::Read);
            last_txn_ = txn;
            txn->Inform(mdio::Transaction::Event::Scheduled);
            return core::Status{};
        }));
        driver_.Execute();
        Verify();

        // Simulate Reset completion (reset bit cleared)
        ASSERT_NE(last_txn_, nullptr);
        last_txn_->data = 0x0000U;
        last_txn_->Inform(mdio::Transaction::Event::Start);
        last_txn_->Inform(mdio::Transaction::Event::Completed, core::Status{});
        (void)last_txn_->NotifyCompletionListener();

        // Enters ConfiguringAutoNegotiation, expects a write to BMCR with Auto-Negotiate Enable and Restart
        EXPECT_CALL(mock_phy_, Schedule(_)).WillOnce(Invoke([this](mdio::Transaction* txn) {
            EXPECT_EQ(txn->register_address, 0U);
            EXPECT_EQ(txn->operation, mdio::Operation::Write);
            EXPECT_EQ(txn->data, 0x1200U);
            last_txn_ = txn;
            txn->Inform(mdio::Transaction::Event::Scheduled);
            return core::Status{};
        }));
        driver_.Execute();
        Verify();

        // Complete Auto-Negotiation configuration write
        ASSERT_NE(last_txn_, nullptr);
        last_txn_->Inform(mdio::Transaction::Event::Start);
        last_txn_->Inform(mdio::Transaction::Event::Completed, core::Status{});
        (void)last_txn_->NotifyCompletionListener();

        // Cycles the state machine to transition to AwaitingLink
        driver_.Execute();
        Verify();
    }

    /// @brief Simulates link resolution and transitions the driver to LinkUp
    void EstablishLink(bool speed_100m, bool full_duplex) {
        // Wait for the polling timer to expire
        jump_timer_.Jump(core::units::ConvertToIota(lan8742a::DefaultPollingInterval) + core::units::Iota(1U));

        // Triggers transition to PollingLinkStatus, expects read of BMSR (reg 1)
        EXPECT_CALL(mock_phy_, Schedule(_)).WillOnce(Invoke([this](mdio::Transaction* txn) {
            EXPECT_EQ(txn->register_address, 1U);
            EXPECT_EQ(txn->operation, mdio::Operation::Read);
            last_txn_ = txn;
            txn->Inform(mdio::Transaction::Event::Scheduled);
            return core::Status{};
        }));
        driver_.Execute();
        Verify();

        // Complete the read: Link status set, Auto-negotiation complete (0x0004 | 0x0020 = 0x0024)
        ASSERT_NE(last_txn_, nullptr);
        last_txn_->data = 0x0024U;
        last_txn_->Inform(mdio::Transaction::Event::Start);
        last_txn_->Inform(mdio::Transaction::Event::Completed, core::Status{});
        (void)last_txn_->NotifyCompletionListener();

        // Triggers transition to ReadingLinkStatus, expects read of register 31 (Special Control/Status)
        EXPECT_CALL(mock_phy_, Schedule(_)).WillOnce(Invoke([this](mdio::Transaction* txn) {
            EXPECT_EQ(txn->register_address, 31U);
            EXPECT_EQ(txn->operation, mdio::Operation::Read);
            last_txn_ = txn;
            txn->Inform(mdio::Transaction::Event::Scheduled);
            return core::Status{};
        }));
        driver_.Execute();
        Verify();

        // Parse special register bits [4:2] for speed/duplex resolution
        uint16_t special_val = 0U;
        if (speed_100m) {
            special_val |= 0x0008U;
        }
        if (full_duplex) {
            special_val |= 0x0010U;
        }

        ASSERT_NE(last_txn_, nullptr);
        last_txn_->data = special_val;
        last_txn_->Inform(mdio::Transaction::Event::Start);
        last_txn_->Inform(mdio::Transaction::Event::Completed, core::Status{});
        (void)last_txn_->NotifyCompletionListener();

        // Expect ConfigureMacLink callback on the MAC side
        EXPECT_CALL(mock_phy_, ConfigureMacLink(speed_100m, full_duplex)).WillOnce(Return(core::Status{}));
        driver_.Execute();
        Verify();

        // Cycles one more time to transition into LinkUp state
        driver_.Execute();
        Verify();
        ASSERT_TRUE(driver_.IsLinkUp());
    }

    /// @brief Verify link-up polling is active and maintains the LinkUp state
    void VerifyLinkUpPoll() {
        jump_timer_.Jump(core::units::ConvertToIota(lan8742a::DefaultPollingInterval) + core::units::Iota(1U));

        EXPECT_CALL(mock_phy_, Schedule(_)).WillOnce(Invoke([this](mdio::Transaction* txn) {
            EXPECT_EQ(txn->register_address, 1U);
            EXPECT_EQ(txn->operation, mdio::Operation::Read);
            last_txn_ = txn;
            txn->Inform(mdio::Transaction::Event::Scheduled);
            return core::Status{};
        }));
        driver_.Execute();
        Verify();

        // Link is still up
        ASSERT_NE(last_txn_, nullptr);
        last_txn_->data = 0x0004U;
        last_txn_->Inform(mdio::Transaction::Event::Start);
        last_txn_->Inform(mdio::Transaction::Event::Completed, core::Status{});
        (void)last_txn_->NotifyCompletionListener();

        // Enters LinkUp again
        driver_.Execute();
        Verify();
        ASSERT_TRUE(driver_.IsLinkUp());
    }

    /// @brief Simulates link loss during LinkUp and verifies transition back to AwaitingLink
    void LoseLink() {
        jump_timer_.Jump(core::units::ConvertToIota(lan8742a::DefaultPollingInterval) + core::units::Iota(1U));

        EXPECT_CALL(mock_phy_, Schedule(_)).WillOnce(Invoke([this](mdio::Transaction* txn) {
            EXPECT_EQ(txn->register_address, 1U);
            EXPECT_EQ(txn->operation, mdio::Operation::Read);
            last_txn_ = txn;
            txn->Inform(mdio::Transaction::Event::Scheduled);
            return core::Status{};
        }));
        driver_.Execute();
        Verify();

        // Link is down (0x0000)
        ASSERT_NE(last_txn_, nullptr);
        last_txn_->data = 0x0000U;
        last_txn_->Inform(mdio::Transaction::Event::Start);
        last_txn_->Inform(mdio::Transaction::Event::Completed, core::Status{});
        (void)last_txn_->NotifyCompletionListener();

        // Enters AwaitingLink
        driver_.Execute();
        Verify();
        ASSERT_FALSE(driver_.IsLinkUp());
    }

    jarnax::JumpTimer jump_timer_;
    MockPhy mock_phy_;
    lan8742a::Driver driver_;
    mdio::Transaction* last_txn_{nullptr};
};

/// Empty test case for Setup/Teardown checks
TEST_F(LAN8742AStateMachineTest, Empty) {}

TEST_F(LAN8742AStateMachineTest, Initialization) {
    ProgressReset();
}

TEST_F(LAN8742AStateMachineTest, Link100MFull) {
    ProgressReset();
    EstablishLink(true, true);
    VerifyLinkUpPoll();
}

TEST_F(LAN8742AStateMachineTest, Link10MHalf) {
    ProgressReset();
    EstablishLink(false, false);
    VerifyLinkUpPoll();
}

TEST_F(LAN8742AStateMachineTest, LinkLoss) {
    ProgressReset();
    EstablishLink(true, true);
    LoseLink();
}

}  // namespace ethernet
}  // namespace net
}  // namespace jarnax

#include <gtest/gtest.h>

#include "gtest/Status.hpp"
#include "jarnax/JumpTimer.hpp"
#include "jarnax/cyphal/MockInterface.hpp"
#include "jarnax/cyphal/Node.hpp"
#include "jarnax/services/CyphalService.hpp"

namespace {

using jarnax::cyphal::MockInterface;
using jarnax::cyphal::Node;
using jarnax::cyphal::NodeId;
using jarnax::cyphal::UniqueId;

class CyphalServiceTest : public ::testing::Test {
protected:
    jarnax::JumpTimer timer;
    MockInterface interface;
    UniqueId unique_id{};
    Node node{timer, interface, NodeId{42U}, unique_id};
    jarnax::cyphal::CyphalService service;
};

TEST_F(CyphalServiceTest, EnlistAndDismissNode) {
    EXPECT_STATUS_EQ(service.Enlist(&node), core::Result::Success, core::Cause::Unknown);
    EXPECT_STATUS_EQ(service.Dismiss(&node), core::Result::Success, core::Cause::Unknown);
    EXPECT_STATUS_EQ(service.Dismiss(&node), core::Result::NotAvailable, core::Cause::Resource);
}

TEST_F(CyphalServiceTest, EnlistFailsWhenNoSlotIsAvailable) {
    Node second_node{timer, interface, NodeId{43U}, unique_id};

    EXPECT_STATUS_EQ(service.Enlist(&node), core::Result::Success, core::Cause::Unknown);
    EXPECT_STATUS_EQ(service.Enlist(&second_node), core::Result::NotAvailable, core::Cause::Resource);
}

TEST_F(CyphalServiceTest, ExecuteRunsEnlistedNodeAfterTimeJump) {
    EXPECT_STATUS_EQ(service.Enlist(&node), core::Result::Success, core::Cause::Unknown);

    timer.Jump(core::units::MicroSeconds{1000000U});

    EXPECT_TRUE(service.Execute());
}

}    // namespace

#include <gtest/gtest.h>

#include "jarnax/cyphal/Interface.hpp"
#include "jarnax/cyphal/Types.hpp"

namespace {

using jarnax::cyphal::Metadata;
using jarnax::cyphal::NodeId;
using jarnax::cyphal::PortId;
using jarnax::cyphal::ServiceId;
using jarnax::cyphal::SubjectId;
using jarnax::cyphal::UniqueId;

TEST(CyphalPortIdTest, SubjectPortStoresSubjectAndNeitherStyle) {
    SubjectId const subject{123U};
    PortId const port{subject};

    EXPECT_EQ(port.type, PortId::Type::Subject);
    EXPECT_EQ(port.style, PortId::Style::Neither);
    EXPECT_EQ(port.value<SubjectId>(), subject);
}

TEST(CyphalPortIdTest, ServicePortDefaultsToRequestStyle) {
    ServiceId const service{45U};
    PortId const port{service};

    EXPECT_EQ(port.type, PortId::Type::Service);
    EXPECT_EQ(port.style, PortId::Style::Request);
    EXPECT_EQ(port.value<ServiceId>(), service);
}

TEST(CyphalPortIdTest, ServicePortStoresResponseStyle) {
    ServiceId const service{45U};
    PortId const port{service, PortId::Style::Response};

    EXPECT_EQ(port.type, PortId::Type::Service);
    EXPECT_EQ(port.style, PortId::Style::Response);
    EXPECT_EQ(port.value<ServiceId>(), service);
}

TEST(CyphalMetadataTest, StoresAllTransferFields) {
    NodeId const source{7U};
    NodeId const recipient{9U};
    PortId const port{ServiceId{23U}, PortId::Style::Request};
    core::units::MicroSeconds const timestamp{1234U};

    Metadata const metadata{source, recipient, port, timestamp};

    EXPECT_EQ(metadata.source, source);
    EXPECT_EQ(metadata.recipient, recipient);
    EXPECT_EQ(metadata.port_id.type, PortId::Type::Service);
    EXPECT_EQ(metadata.port_id.style, PortId::Style::Request);
    EXPECT_EQ(metadata.port_id.value<ServiceId>(), ServiceId{23U});
    EXPECT_EQ(metadata.timestamp.value(), timestamp.value());
}

TEST(CyphalMetadataTest, CopyConstructorCopiesAllTransferFields) {
    Metadata const original{NodeId{7U}, NodeId{9U}, PortId{SubjectId{23U}}, core::units::MicroSeconds{1234U}};

    Metadata const copy{original};

    EXPECT_EQ(copy.source, original.source);
    EXPECT_EQ(copy.recipient, original.recipient);
    EXPECT_EQ(copy.port_id.type, original.port_id.type);
    EXPECT_EQ(copy.port_id.style, original.port_id.style);
    EXPECT_EQ(copy.port_id.value<SubjectId>(), original.port_id.value<SubjectId>());
    EXPECT_EQ(copy.timestamp.value(), original.timestamp.value());
}

TEST(CyphalTypesTest, UniqueIdEqualityDistinguishesDifferentBytes) {
    UniqueId const first{{0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 9U, 10U, 11U, 12U, 13U, 14U, 15U}};
    UniqueId second{first};
    UniqueId different{first};
    different[15] = 0xFFU;

    EXPECT_TRUE(first == second);
    EXPECT_FALSE(first == different);
}

TEST(CyphalTypesTest, SerializedMessageProvidesMutableByteSpan) {
    uint8_t bytes[] = {0x10U, 0x20U, 0x30U};
    jarnax::cyphal::SerializedMessage message{bytes, sizeof(bytes)};

    ASSERT_EQ(message.size(), sizeof(bytes));
    EXPECT_EQ(message.data(), bytes);
    message[1] = 0xAAU;
    EXPECT_EQ(bytes[1], 0xAAU);
}

TEST(CyphalTypesTest, ProtocolConstantsUseExpectedPortKinds) {
    EXPECT_EQ(jarnax::cyphal::HeartbeatSubjectId, SubjectId{7509U});
    EXPECT_EQ(jarnax::cyphal::GetInfoServiceId, ServiceId{430U});
    EXPECT_GT(jarnax::cyphal::HeartbeatExtent, sizeof(jarnax::cyphal::Heartbeat));
    EXPECT_GT(jarnax::cyphal::MaxExtent, 0U);
}

}    // namespace

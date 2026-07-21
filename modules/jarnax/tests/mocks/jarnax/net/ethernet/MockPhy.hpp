#ifndef JARNAX_NET_ETHERNET_MOCK_PHY_HPP
#define JARNAX_NET_ETHERNET_MOCK_PHY_HPP

#include <gmock/gmock.h>
#include "jarnax/net/ethernet/Phy.hpp"

namespace jarnax {
namespace net {
namespace ethernet {

/// @brief Mock implementation of the jarnax::net::ethernet::Phy interface
class MockPhy : public Phy {
public:
    MOCK_METHOD(core::Status, Initialize, (), (override));
    MOCK_METHOD(bool, Execute, (), (override));
    MOCK_METHOD(core::Status, Schedule, (mdio::Transaction* mdio), (override));
    MOCK_METHOD(core::Status, ConfigureMacLink, (bool speed_100m, bool full_duplex), (override));
};

}  // namespace ethernet
}  // namespace net
}  // namespace jarnax

#endif  // JARNAX_NET_ETHERNET_MOCK_PHY_HPP

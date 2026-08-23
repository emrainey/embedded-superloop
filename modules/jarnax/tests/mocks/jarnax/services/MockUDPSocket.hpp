#ifndef JARNAX_SERVICES_MOCK_UDP_SOCKET_HPP
#define JARNAX_SERVICES_MOCK_UDP_SOCKET_HPP

#include <gmock/gmock.h>

#include "jarnax/services/CyphalUDPSocket.hpp"

namespace jarnax {
namespace cyphal {
namespace udp {

class MockSocket : public Socket {
public:
    MOCK_METHOD(core::Status, Join, (Endpoint const& multicast_endpoint, DatagramHandler& handler), (override));
    MOCK_METHOD(core::Status, Leave, (Endpoint const& multicast_endpoint), (override));
    MOCK_METHOD(core::Status, Send, (Endpoint const& destination, core::Span<std::uint8_t const> payload), (override));

    virtual ~MockSocket() = default;
};

}    // namespace udp
}    // namespace cyphal
}    // namespace jarnax

#endif    // JARNAX_SERVICES_MOCK_UDP_SOCKET_HPP

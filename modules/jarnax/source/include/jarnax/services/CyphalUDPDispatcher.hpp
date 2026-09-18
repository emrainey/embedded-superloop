#ifndef JARNAX_SERVICES_CYPHAL_UDP_DISPATCHER_HPP
#define JARNAX_SERVICES_CYPHAL_UDP_DISPATCHER_HPP

#include <cstddef>
#include <cstdint>

#include <core/Span.hpp>
#include <core/Status.hpp>

namespace jarnax {
namespace cyphal {
namespace udp {

/// The UDP/IP endpoint of a Cyphal/UDP multicast group.
/// The IPv4 address is stored in host byte order with the most significant octet in bits [31:24].
struct Endpoint final {
    std::uint32_t ip_address{0U};
    std::uint16_t udp_port{0U};

    friend constexpr bool operator==(Endpoint const& lhs, Endpoint const& rhs) {
        return (lhs.ip_address == rhs.ip_address) and (lhs.udp_port == rhs.udp_port);
    }

    friend constexpr bool operator!=(Endpoint const& lhs, Endpoint const& rhs) {
        return not operator==(lhs, rhs);
    }
};

/// The handler of datagrams received by a Dispatcher.
/// Implementations are notified for every datagram the underlying UDP/IP stack delivers.
class DatagramHandler {
public:
    /// Called when a datagram is received and destined to the given multicast endpoint.
    /// @param destination The multicast endpoint the datagram was sent to.
    /// @param data The mutable payload of the datagram; ownership stays with the caller.
    /// @param size The size of the payload in bytes.
    virtual void OnDatagramReceived(Endpoint const& destination, std::uint8_t* data, std::size_t size) = 0;

protected:
    ~DatagramHandler() = default;
};

/// The narrow UDP/IP dispatch boundary required by Cyphal/UDP.
/// The production implementation wraps hypha; unit tests inject a mock.
/// All methods are non-blocking and return immediately.
class Dispatcher {
public:
    /// Begins delivering multicast datagrams for the endpoint to the handler.
    virtual core::Status Join(Endpoint const& multicast_endpoint, DatagramHandler& handler) = 0;

    /// Stops delivering multicast datagrams for the endpoint.
    virtual core::Status Leave(Endpoint const& multicast_endpoint) = 0;

    /// Transmits one datagram to the given multicast endpoint.
    virtual core::Status Send(Endpoint const& destination, core::Span<std::uint8_t const> payload) = 0;

protected:
    ~Dispatcher() = default;
};

}    // namespace udp
}    // namespace cyphal
}    // namespace jarnax

#endif    // JARNAX_SERVICES_CYPHAL_UDP_DISPATCHER_HPP
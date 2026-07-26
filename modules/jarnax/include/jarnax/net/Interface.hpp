#ifndef JARNAX_NET_INTERFACE_HPP
#define JARNAX_NET_INTERFACE_HPP

#include <cstddef>
#include "core/Printer.hpp"
#include "core/Statistician.hpp"

#include "jarnax/Loopable.hpp"
#include "jarnax/net/arp/Table.hpp"
#include "jarnax/net/ethernet/Driver.hpp"
#include "jarnax/net/eui/Address.hpp"
#include "jarnax/net/ip/v4/Address.hpp"

namespace jarnax {
namespace net {

/// The Statistics structure for the Interface class
struct Statistics {
    struct Frames {
        std::size_t transmitted{0};    ///< The number of frames transmitted by this interface
        std::size_t received{0};       ///< The number of frames received by this interface
        std::size_t dropped{0};        ///< The number of frames dropped by this interface (received but not able to process)
        std::size_t unsupported{0};    ///< The number of unsupported Ethernet types received by this interface
    } frames{};
    struct Arp {
        std::size_t requests{0};    ///< The number of ARP requests sent by this interface
        std::size_t replies{0};     ///< The number of ARP replies sent by this interface
    } arp{};
    struct IPv4 {
        std::size_t received{0};       ///< The number of IPv4 packets received by this interface
        std::size_t transmitted{0};    ///< The number of IPv4 packets transmitted by this interface
        std::size_t unsupported{0};    ///< A feature or setting in the header is not supported by this interface
        std::size_t dropped{0};        ///< The number of IPv4 packets dropped by this interface (not for us)
    } ipv4{};
};

/// The IPv4 Interface Class represents a network interface with an assigned IP address and other details.
class Interface : protected ethernet::Driver::Listener, public jarnax::Loopable, public core::Statistician<Statistics> {
public:
    Interface(ethernet::Driver& driver, eui48::Address mac, ip::v4::Address address, ip::v4::Address netmask);
    Interface(ethernet::Driver& driver, eui48::Address mac, ip::v4::Address address, ip::v4::Address netmask, ip::v4::Address gateway);

    /// Checks if this interface has a valid configuration (i.e. has an address and netmask, and the address is not the network or broadcast address
    /// for the subnet)
    bool IsValid() const;

    /// Checks if this interface could receive a packet sent from the given source address (i.e. if the source address is in the same subnet as this
    /// interface or is the broadcast address for the subnet)
    bool CouldReceiveFrom(ip::v4::Address source) const;

    /// Checks if this interface could receive a packet destined for the given destination address (i.e. if the destination address is in the same
    /// subnet as this interface or is the broadcast address for the subnet)
    bool CouldReceiveTo(ip::v4::Address destination) const;

    /// Checks if this interface could send a packet to the given destination address (i.e. if the destination address is in the same
    /// subnet as this interface or is the broadcast address for the subnet)
    bool CouldSendTo(ip::v4::Address destination) const;

    /// Sends an IPv4 packet to the specified destination address using this interface but within a Frame object.
    /// \param frame The Ethernet frame containing the IPv4 packet to be sent. Allocated by and owned by Sender.
    /// \param destination The IPv4 address of the destination.
    /// \return The status of the transmission attempt.
    core::Status Transmit(ethernet::Frame* frame, ip::v4::Address destination);

    //+=== Loopable Interface (requires Executable) ===+//
    bool Execute() override;

    /// Prints the Current Configuration of the Interface to the provided printer
    /// \param printer The printer to which the configuration will be printed.
    void PrintConfiguration(core::Printer& printer) const;

protected:
    ethernet::Driver& driver_;    ///< The Ethernet driver associated with this interface, which is used to send and receive packets on the network.
    arp::Table<arp::MaxEntries> arp_table_;    ///< The ARP table associated with this interface
    Statistics statistics_;                    ///< The statistics for this interface

    /// Listens for incoming Ethernet frames and handles them appropriately. This function is called by the Ethernet driver when a frame is received.
    void OnFrameReceived(ethernet::Frame* frame) override;

    /// Handles an incoming ARP packet contained within the given Ethernet frame.
    void HandleArpPacket(ethernet::Frame* frame);

    /// Handles an incoming IPv4 packet contained within the given Ethernet frame.
    void HandleIpv4Packet(ethernet::Frame* frame);

public:
    eui48::Address mac_address;    ///< The MAC address of this interface
    ip::v4::Address address;       ///< The IP address assigned to this interface
    ip::v4::Address netmask;       ///< The subnet mask for this interface
    ip::v4::Address network;       ///< The network range for this interface (deduced from the address and netmask)
    ip::v4::Address broadcast;     ///< The broadcast address for this interface (deduced from the address and netmask)
    ip::v4::Address gateway;       ///< The default gateway for this interface
};

namespace local {
/// The common interface for local addresses (i.e. 127.x.x.x)
extern Interface loopback_interface;
}    // namespace local

}    // namespace net
}    // namespace jarnax

#endif    // JARNAX_NET_INTERFACE_HPP

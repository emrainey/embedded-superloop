#include "jarnax/net/Interface.hpp"
#include "jarnax/print.hpp"

namespace jarnax {
namespace net {

Statistics* network_statistics = nullptr;

Interface::Interface(ethernet::Driver& driver, eui48::Address mac, ip::v4::Address a, ip::v4::Address n)
    : driver_{driver}
    , mac_address{mac}
    , address{a}
    , netmask{n}
    , network{a & n}
    , broadcast{network | ~n}
    , gateway{0} {
    network_statistics = &statistics_;
}

Interface::Interface(ethernet::Driver& driver, eui48::Address mac, ip::v4::Address a, ip::v4::Address n, ip::v4::Address g)
    : driver_{driver}
    , mac_address{mac}
    , address{a}
    , netmask{n}
    , network{a & n}
    , broadcast{network | ~n}
    , gateway{g} {
    network_statistics = &statistics_;
}

bool Interface::IsValid() const {
    // An interface is valid if it has an address and netmask, and the address is not the network or broadcast address for the subnet
    // and if the address is in the network defined given the mask.
    bool valid_address = (address != ip::v4::default_route) and (address != network) and (address != broadcast);
    bool valid_netmask = (netmask != ip::v4::Address{0});
    bool address_in_network = (address & netmask) == network;
    bool not_broadcast = (address != broadcast);
    bool not_limited_broadcast = (address != ip::v4::limited_broadcast);
    bool not_multicast = not address.IsMulticast();
    return valid_address and valid_netmask and address_in_network and not_broadcast and not_limited_broadcast and not_multicast;
}

bool Interface::CouldReceiveTo(ip::v4::Address destination) const {
    // An interface would receive a packet destined for a given address if the destination address is
    // * in the same subnet as this interface
    // * is the broadcast address for the subnet
    // * is the limited broadcast address
    // * is a multicast address
    bool is_for_us = (destination == address);    // should match normal IP and Localhost
    bool is_subnet_broadcast = (destination == broadcast);
    bool is_broadcast = destination.IsBroadcast();
    bool is_multicast = destination.IsMulticast();
    return is_for_us or is_subnet_broadcast or is_broadcast or is_multicast;
}

bool Interface::CouldReceiveFrom(ip::v4::Address source) const {
    // An interface would receive a packet from a source address if the source address is
    // * in the same subnet as this interface
    // * is the broadcast address for the subnet
    // * is the limited broadcast address
    // * is a multicast address
    bool same_subnet = (source & netmask) == network;
    bool is_broadcast = source == ip::v4::limited_broadcast || source == broadcast;
    bool is_multicast = source.IsMulticast();
    return same_subnet or is_broadcast or is_multicast;
}

void Interface::PrintConfiguration(core::Printer& printer) const {
    net::eui48::Print(printer, "MAC Address", mac_address);
    ip::v4::Print(printer, "Host", address);
    ip::v4::Print(printer, "Netmask", netmask);
    ip::v4::Print(printer, "Network", network);
    ip::v4::Print(printer, "Broadcast", broadcast);
    ip::v4::Print(printer, "Gateway", gateway);
}

core::Status Interface::Transmit(net::ethernet::Frame* frame, ip::v4::Address destination) {
    // look up the destination MAC address based on the IPv4 destination
    jarnax::net::eui48::Address destination_mac;
    auto* entry = arp_table_.Find(destination);
    if (entry != nullptr) {
        destination_mac = entry->mac;
    } else {
        // TODO initiate an ARP request, putting this frame aside until the ARP reply is received, and establishing a timeout to then cancel the frame
        // if no address found, failing for now
        return core::Status{core::Result::NotAvailable, core::Cause::Resource};
    }
    // fill in the type into the header
    frame->header.type = ethernet::EtherType::IPv4;
    // fill in the destination mac address
    frame->header.destination = destination_mac;
    // put our MAC address as the source
    frame->header.source = driver_.GetMacAddress();
    // flip the header to the network byte order
    frame->header.Flip();
    // account for the transmitted IPv4 packet
    statistics_.ipv4.transmitted++;
    // pass it down
    return driver_.Transmit(frame);
}

void Interface::HandleArpPacket(jarnax::net::ethernet::Frame* frame) {
    if (frame == nullptr) {
        return;
    }
    // Handle the ARP packet contained within the Ethernet frame.
    // flip the ARP header
    frame->payload.arp.Flip();
    // Check the ARP operation type
    if (frame->payload.arp.opcode == jarnax::net::arp::Opcode::Request) {
        // Handle ARP request that is targeted at this interface
        if (frame->payload.arp.target_ip == address) {
            // we got a request
            statistics_.arp.requests++;
            // Send an ARP reply, but save the sender info
            auto sender_mac = frame->payload.arp.sender_mac;
            auto sender_ip = frame->payload.arp.sender_ip;

            // reply to the ARP request in the same frame!
            frame->header.destination = sender_mac;
            frame->header.source = mac_address;
            frame->header.type = jarnax::net::ethernet::EtherType::ARP;

            frame->payload.arp.hardware_type = jarnax::net::arp::HardwareType::Ethernet;
            frame->payload.arp.protocol_type = jarnax::net::ethernet::EtherType::IPv4;
            frame->payload.arp.opcode = jarnax::net::arp::Opcode::Reply;
            frame->payload.arp.sender_mac = mac_address;
            frame->payload.arp.sender_ip = address;
            frame->payload.arp.target_mac = sender_mac;
            frame->payload.arp.target_ip = sender_ip;
            // flip the ARP packet to network byte order
            frame->payload.arp.Flip();
            frame->header.destination = sender_mac;
            frame->header.source = mac_address;
            // flip the ethernet header back around
            frame->header.Flip();
            // send the ARP reply
            driver_.Transmit(frame);
        }
    } else if (frame->payload.arp.opcode == jarnax::net::arp::Opcode::Reply) {
        // Handle ARP reply
        if (frame->payload.arp.target_ip == address) {
            // Update the ARP table with the sender's MAC and IP address
            jarnax::net::arp::Entry entry;
            entry.mac = frame->payload.arp.sender_mac;
            entry.ipv4 = frame->payload.arp.sender_ip;
            arp_table_.Insert(entry);
            statistics_.arp.replies++;
        }
    }
}

void Interface::HandleIpv4Packet(net::ethernet::Frame* frame) {
    if (frame == nullptr) {
        return;
    }
    statistics_.ipv4.received++;
    // Handle the IPv4 packet contained within the Ethernet frame.
    // flip the IPv4 header
    frame->payload.ipv4.HeaderFlip();

    if (not frame->payload.ipv4.header.IsValid()) {
        statistics_.ipv4.unsupported++;
    }
    // if (not frame)

    // The types of addresses we'll have to support:
    // Localhost
    // "Normal" IP addresses within the subnet
    // Subnet broadcast
    // broadcast
    // Multicast

    // we'll refuse packets not destined for us or a local broadcast or a multicast
    ip::v4::Address const& destination = frame->payload.ipv4.header.destination_address;
    if (not CouldReceiveTo(destination)) {
        statistics_.ipv4.dropped++;
        return;
    }
    // we'll also drop packets which don't originate from a valid source (e.g., not from our subnet, not a unicast, etc.)
    ip::v4::Address const& source = frame->payload.ipv4.header.source_address;
    if (not CouldReceiveFrom(source)) {
        statistics_.ipv4.dropped++;
        return;
    }

    // Pass to the Stack for further processing (IGMP/ICMP/UDP)
}

void Interface::OnFrameReceived(net::ethernet::Frame* frame) {
    // Handle the received Ethernet frame
    core::Printer& printer = core::GetPrinter();

    // flip the header
    frame->header.Flip();

    statistics_.frames.received++;

    printer(
        "Interface: RX %s src=%02X:%02X:%02X:%02X:%02X:%02X\r\n",
        jarnax::net::ethernet::ToString(frame->header.type),
        frame->header.source[0],
        frame->header.source[1],
        frame->header.source[2],
        frame->header.source[3],
        frame->header.source[4],
        frame->header.source[5]
    );
    if (frame->header.type == jarnax::net::ethernet::EtherType::ARP) {
        HandleArpPacket(frame);
    } else if (frame->header.type == jarnax::net::ethernet::EtherType::IPv4) {
        // since it's IPv4 we could scrape the MAC / IP out
        if constexpr (jarnax::net::arp::LearnAddresses) {
            // associate the MAC & IP of the sender automatically so we don't have to emit a separate ARP request later
            jarnax::net::arp::Entry entry;
            entry.mac = frame->header.source;
            entry.ipv4 = frame->payload.ipv4.header.source_address;
            arp_table_.Insert(entry);
        }
        HandleIpv4Packet(frame);
    } else {
        // unsupported type!
        statistics_.frames.unsupported++;
    }
}

bool Interface::Execute() {
    // Implement the loopable execution logic here
    core::Status status = driver_.Receive(*this);
    if (status.Is(core::Result::NotReady, core::Cause::Resource)) {
        // nothing came in
    } else if (status.Is(core::Result::NotSupported, core::Cause::State)) {
        // Handle failure
        statistics_.frames.dropped++;
    } else if (status.Is(core::Result::NotEnough, core::Cause::Resource)) {
        // Handle not enough resources
        statistics_.frames.dropped++;
    } else if (status.IsSuccess()) {
        // Handle successful reception
    }
    return true;
}

}    // namespace net
}    // namespace jarnax

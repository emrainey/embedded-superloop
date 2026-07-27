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

bool Interface::CouldReceive(ip::v4::Address source) const {
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
        // Handle ARP request
        if (frame->payload.arp.target_ip == address) {
            // we got a request
            statistics_.arp.requests++;
            // Send an ARP reply
            // TODO reply to the ARP request in the same frame!
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

void Interface::OnFrameReceived(net::ethernet::Frame* frame) {
    // Handle the received Ethernet frame
    core::Printer& printer = core::GetPrinter();

    // flip the header
    frame->header.Flip();

    statistics_.frames.received++;

    if (frame->header.type == jarnax::net::ethernet::EtherType::ARP) {
        printer(
            "Interface: RX ARP  src=%02X:%02X:%02X:%02X:%02X:%02X\r\n",
            frame->header.source[0],
            frame->header.source[1],
            frame->header.source[2],
            frame->header.source[3],
            frame->header.source[4],
            frame->header.source[5]
        );
        HandleArpPacket(frame);
    } else if (frame->header.type == jarnax::net::ethernet::EtherType::IPv4) {
        printer(
            "Interface: RX IPv4 src=%02X:%02X:%02X:%02X:%02X:%02X\r\n",
            frame->header.source[0],
            frame->header.source[1],
            frame->header.source[2],
            frame->header.source[3],
            frame->header.source[4],
            frame->header.source[5]
        );
        // since it's IPv4 we could scrape the MAC / IP out
        if constexpr (jarnax::net::arp::LearnAddresses) {
            // associate the MAC & IP of the sender automatically so we don't have to emit a separate ARP request later
            jarnax::net::arp::Entry entry;
            entry.mac = frame->header.source;
            entry.ipv4 = frame->payload.ipv4.header.source_address;
            arp_table_.Insert(entry);
        }
        statistics_.ipv4.received++;
        // TODO if a valid IPv4, pass it along

    } else {
        printer(
            "Interface: RX type=0x%04X src=%02X:%02X:%02X:%02X:%02X:%02X\r\n",
            static_cast<unsigned>(frame->header.type),
            frame->header.source[0],
            frame->header.source[1],
            frame->header.source[2],
            frame->header.source[3],
            frame->header.source[4],
            frame->header.source[5]
        );
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

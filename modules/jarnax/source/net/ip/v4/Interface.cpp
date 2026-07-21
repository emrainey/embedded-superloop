#include "jarnax/net/ip/v4/Interface.hpp"

namespace jarnax {
namespace net {
namespace ip {
namespace v4 {

Interface::Interface(Address a, Address n)
    : address{a}
    , netmask{n}
    , network{a & n}
    , broadcast{network | ~n}
    , gateway{0} {}

Interface::Interface(Address a, Address n, Address g)
    : address{a}
    , netmask{n}
    , network{a & n}
    , broadcast{network | ~n}
    , gateway{g} {}

bool Interface::IsValid() const {
    // An interface is valid if it has an address and netmask, and the address is not the network or broadcast address for the subnet
    // and if the address is in the network defined given the mask.
    bool valid_address = (address != default_route) and (address != network) and (address != broadcast);
    bool valid_netmask = (netmask != Address{0});
    bool address_in_network = (address & netmask) == network;
    bool not_broadcast = (address != broadcast);
    bool not_limited_broadcast = (address != limited_broadcast);
    bool not_multicast = not address.IsMulticast();
    return valid_address and valid_netmask and address_in_network and not_broadcast and not_limited_broadcast and not_multicast;
}

bool Interface::CouldReceive(Address source) const {
    // An interface would receive a packet from a source address if the source address is
    // * in the same subnet as this interface
    // * is the broadcast address for the subnet
    // * is the limited broadcast address
    // * is a multicast address
    bool same_subnet = (source & netmask) == network;
    bool is_broadcast = source == limited_broadcast || source == broadcast;
    bool is_multicast = source.IsMulticast();
    return same_subnet or is_broadcast or is_multicast;
}

}    // namespace v4
}    // namespace ip
}    // namespace net
}    // namespace jarnax

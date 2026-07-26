#include "jarnax/net/ethernet/Types.hpp"

namespace jarnax {
namespace net {
namespace ethernet {

char const* ToString(EtherType type) {
    switch (type) {
        case EtherType::IPv4:
            return "IPv4";
        case EtherType::ARP:
            return "ARP";
        // case EtherType::WakeOnLan: return "WakeOnLan";
        // case EtherType::IPv6: return "IPv6";
        // case EtherType::VLAN: return "VLAN";
        // case EtherType::EtherCAT: return "EtherCAT";
        default:
            return "Unknown";
    }
}

}    // namespace ethernet
}    // namespace net
}    // namespace jarnax

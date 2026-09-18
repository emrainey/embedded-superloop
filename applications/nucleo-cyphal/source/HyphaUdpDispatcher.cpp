#include "HyphaUdpDispatcher.hpp"

namespace nucleo {
namespace cyphal {

HyphaUdpDispatcher::HyphaUdpDispatcher(HyphaIpContext_t& context, HyphaIpNetworkInterface_t const& network_interface)
    : context_{context}
    , network_interface_{network_interface} {}

HyphaIpIPv4Address_t HyphaUdpDispatcher::ToHyphaAddress(std::uint32_t address) {
    return HyphaIpIPv4Address_t{
        static_cast<std::uint8_t>(address >> 24U), static_cast<std::uint8_t>(address >> 16U),
        static_cast<std::uint8_t>(address >> 8U), static_cast<std::uint8_t>(address)};
}

std::uint32_t HyphaUdpDispatcher::ToEndpointAddress(HyphaIpIPv4Address_t address) {
    return (static_cast<std::uint32_t>(address.a) << 24U) | (static_cast<std::uint32_t>(address.b) << 16U) |
           (static_cast<std::uint32_t>(address.c) << 8U) | static_cast<std::uint32_t>(address.d);
}

core::Status HyphaUdpDispatcher::ToStatus(HyphaIpStatus_e status) {
    return HyphaIpIsSuccess(status) ? core::Status{} : core::Status{core::Result::Failure, core::Cause::Unknown};
}

core::Status HyphaUdpDispatcher::Join(jarnax::cyphal::udp::Endpoint const& multicast_endpoint,
                                      jarnax::cyphal::udp::DatagramHandler& handler) {
    for (auto const& registration : registrations_) {
        if (registration.used and (registration.endpoint == multicast_endpoint)) {
            return core::Status{core::Result::NotExpected, core::Cause::State};
        }
    }
    Registration* slot = nullptr;
    for (auto& registration : registrations_) {
        if (not registration.used) {
            slot = &registration;
            break;
        }
    }
    if (slot == nullptr) {
        return core::Status{core::Result::ExceededLimit, core::Cause::Resource};
    }
    core::Status const status = ToStatus(
        HyphaIpPrepareUdpReceive(context_, ToHyphaAddress(multicast_endpoint.ip_address), multicast_endpoint.udp_port));
    if (status.IsSuccess()) {
        slot->used = true;
        slot->endpoint = multicast_endpoint;
        slot->handler = &handler;
    }
    return status;
}

core::Status HyphaUdpDispatcher::Leave(jarnax::cyphal::udp::Endpoint const& multicast_endpoint) {
    for (auto& registration : registrations_) {
        if (registration.used and (registration.endpoint == multicast_endpoint)) {
            // libhypha has no inverse to HyphaIpPrepareUdpReceive(); prevent local delivery instead.
            registration.used = false;
            registration.handler = nullptr;
            return core::Status{};
        }
    }
    return core::Status{core::Result::NotExpected, core::Cause::State};
}

core::Status HyphaUdpDispatcher::Send(jarnax::cyphal::udp::Endpoint const& destination,
                                      core::Span<std::uint8_t const> payload) {
    HyphaIpIPv4Address_t const destination_address = ToHyphaAddress(destination.ip_address);
    core::Status const prepared = ToStatus(HyphaIpPrepareUdpTransmit(context_, destination_address, destination.udp_port));
    if (not prepared.IsSuccess()) {
        return prepared;
    }
    HyphaIpMetaData_t metadata{};
    metadata.source_address = network_interface_.address;
    metadata.destination_address = destination_address;
    metadata.source_port = destination.udp_port;
    metadata.destination_port = destination.udp_port;
    metadata.timestamp = 0U;
    HyphaIpSpan_t const datagram{
        const_cast<std::uint8_t*>(payload.data()), static_cast<std::uint32_t>(payload.count() & 0x0FFFFFFFU),
        HyphaIpSpanTypeUint8_t};
    return ToStatus(HyphaIpTransmitUdpDatagram(context_, &metadata, datagram));
}

void HyphaUdpDispatcher::Dispatch(HyphaIpMetaData_t const& metadata, HyphaIpSpan_t datagram) {
    jarnax::cyphal::udp::Endpoint const endpoint{
        ToEndpointAddress(metadata.destination_address), metadata.destination_port};
    for (auto const& registration : registrations_) {
        if (registration.used and (registration.endpoint == endpoint) and (registration.handler != nullptr)) {
            registration.handler->OnDatagramReceived(
                endpoint, static_cast<std::uint8_t*>(datagram.pointer), HyphaIpSpanSize(datagram));
            return;
        }
    }
}

}    // namespace cyphal
}    // namespace nucleo
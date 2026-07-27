#include "CyphalApp.hpp"

#include "board.hpp"
#include "core/Conversions.hpp"
#include "core/vsnprint.hpp"
#include "jarnax/Assertion.hpp"
#include "stm32/h7xx/ethernet/Driver.hpp"

#include <cstring>

namespace {

using namespace jarnax::net::eui48;

constexpr std::size_t kFrameHeaderSize = 14U;

void CopyAddress(HyphaIpEthernetAddress_t& dest, Address const& src) {
    dest.oui[0] = src[0];
    dest.oui[1] = src[1];
    dest.oui[2] = src[2];
    dest.uid[0] = src[3];
    dest.uid[1] = src[4];
    dest.uid[2] = src[5];
}

void CopyAddress(Address& dest, HyphaIpEthernetAddress_t const& src) {
    dest[0] = src.oui[0];
    dest[1] = src.oui[1];
    dest[2] = src.oui[2];
    dest[3] = src.uid[0];
    dest[4] = src.uid[1];
    dest[5] = src.uid[2];
}

void CopyJarnaxFrameToHypha(HyphaIpEthernetFrame_t& destination, jarnax::net::ethernet::Frame const& source) {
    CopyAddress(destination.header.destination, source.header.destination);
    CopyAddress(destination.header.source, source.header.source);
    destination.header.type = static_cast<uint16_t>(source.header.type);
    std::memcpy(destination.payload, source.payload.data, sizeof(destination.payload));
}

void CopyHyphaFrameToJarnax(jarnax::net::ethernet::Frame& destination, HyphaIpEthernetFrame_t const& source) {
    CopyAddress(destination.header.destination, source.header.destination);
    CopyAddress(destination.header.source, source.header.source);
    destination.header.type = static_cast<jarnax::net::ethernet::EtherType>(source.header.type);
    std::memcpy(destination.payload.data, source.payload, sizeof(source.payload));
}

}    // namespace

namespace nucleo {
namespace cyphal {

CyphalApp::CyphalApp(jarnax::Ticker& ticker, jarnax::BoardContext& board_context)
    : board_context_{board_context}
    , ticker_{ticker}
    , ethernet_{board_context.GetEthernet()}
    , mac_addresses_{}
    , hypha_context_{nullptr}
    , network_interface_{}
    , external_interface_{}
    , frame_pool_{}
    , frame_in_use_{}
    , pending_rx_frame_{nullptr}
    , rx_frame_available_{false}
    , initialized_{false} {
    for (auto& in_use : frame_in_use_) {
        in_use = false;
    }

    std::memset(&external_interface_, 0, sizeof(external_interface_));
    external_interface_.acquire = &CyphalApp::OnAcquire;
    external_interface_.receive = &CyphalApp::OnReceive;
    external_interface_.transmit = &CyphalApp::OnTransmit;
    external_interface_.release = &CyphalApp::OnRelease;
    external_interface_.print = &CyphalApp::OnPrint;
    external_interface_.get_monotonic_timestamp = &CyphalApp::OnGetMonotonicTimestamp;
    external_interface_.report = &CyphalApp::OnReport;
    external_interface_.receive_udp = &CyphalApp::OnReceiveUdp;

    jarnax::net::eui48::Address const defined_mac = board_context_.GetDefinedMacAddress();
    CopyAddress(network_interface_.mac, defined_mac);

    network_interface_.address = HyphaIpIPv4Address_t{192, 168, 3, 3};
    network_interface_.netmask = HyphaIpIPv4Address_t{255, 255, 255, 0};
    network_interface_.gateway = HyphaIpIPv4Address_t{192, 168, 3, 1};

    mac_addresses_[0] = defined_mac;
    mac_addresses_[1] = jarnax::net::eui48::Address{};
    mac_addresses_[1][5] = 0x01U;
}

bool CyphalApp::Execute() {
    if (!initialized_) {
        core::Status const status = ethernet_.Configure(mac_addresses_);
        if (status.IsSuccess()) {
            HyphaIpStatus_e const hy_status = HyphaIpInitialize(
                &hypha_context_, &network_interface_, reinterpret_cast<HyphaIpExternalContext_t>(this), &external_interface_);
            if (HyphaIpIsSuccess(hy_status)) {
                initialized_ = true;
            }
        }
        return true;
    }

    ethernet_.Execute();

    HyphaIpRunOnce(hypha_context_);

    return true;
}

void CyphalApp::OnFrameReceived(jarnax::net::ethernet::Frame* frame) {
    if (frame != nullptr && pending_rx_frame_ != nullptr) {
        CopyJarnaxFrameToHypha(*pending_rx_frame_, *frame);
        rx_frame_available_ = true;
    }
}

HyphaIpEthernetFrame_t* CyphalApp::OnAcquire(HyphaIpExternalContext_t context) {
    auto* self = reinterpret_cast<CyphalApp*>(context);
    if (self == nullptr) {
        return nullptr;
    }
    for (std::size_t i = 0; i < FramePoolSize; ++i) {
        if (!self->frame_in_use_[i]) {
            self->frame_in_use_[i] = true;
            return &self->frame_pool_[i];
        }
    }
    return nullptr;
}

HyphaIpStatus_e CyphalApp::OnReceive(HyphaIpExternalContext_t context, HyphaIpEthernetFrame_t* frame) {
    auto* self = reinterpret_cast<CyphalApp*>(context);
    if (self == nullptr || frame == nullptr) {
        return HyphaIpStatusInvalidArgument;
    }

    self->pending_rx_frame_ = frame;
    self->rx_frame_available_ = false;

    auto const result = self->ethernet_.Receive(*self);
    (void)result;

    if (self->rx_frame_available_) {
        self->pending_rx_frame_ = nullptr;
        return HyphaIpStatusOk;
    }

    self->pending_rx_frame_ = nullptr;
    return HyphaIpStatusFailure;
}

HyphaIpStatus_e CyphalApp::OnTransmit(HyphaIpExternalContext_t context, HyphaIpEthernetFrame_t* frame) {
    auto* self = reinterpret_cast<CyphalApp*>(context);
    if (self == nullptr || frame == nullptr) {
        return HyphaIpStatusInvalidArgument;
    }

    auto& eth_driver = static_cast<stm32::ethernet::Driver&>(self->ethernet_);
    jarnax::net::ethernet::Frame* jarnax_frame = eth_driver.Acquire();
    if (jarnax_frame == nullptr) {
        return HyphaIpStatusOutOfMemory;
    }

    CopyHyphaFrameToJarnax(*jarnax_frame, *frame);

    core::Status const tx_status = self->ethernet_.Transmit(jarnax_frame);

    eth_driver.Release(jarnax_frame);

    return tx_status.IsSuccess() ? HyphaIpStatusOk : HyphaIpStatusFailure;
}

HyphaIpStatus_e CyphalApp::OnRelease(HyphaIpExternalContext_t context, HyphaIpEthernetFrame_t* frame) {
    auto* self = reinterpret_cast<CyphalApp*>(context);
    if (self == nullptr || frame == nullptr) {
        return HyphaIpStatusInvalidArgument;
    }
    for (std::size_t i = 0; i < FramePoolSize; ++i) {
        if (&self->frame_pool_[i] == frame) {
            self->frame_in_use_[i] = false;
            return HyphaIpStatusOk;
        }
    }
    return HyphaIpStatusInvalidArgument;
}

int CyphalApp::OnPrint(HyphaIpExternalContext_t context, char const* const format, ...) {
    (void)context;
    va_list args;
    va_start(args, format);
    char buffer[256U];
    unsigned long const result = core::vsnprint(buffer, sizeof(buffer), format, args);
    va_end(args);
    jarnax::print("%s", buffer);
    return static_cast<int>(result);
}

HyphaIpTimestamp_t CyphalApp::OnGetMonotonicTimestamp(HyphaIpExternalContext_t context) {
    auto* self = reinterpret_cast<CyphalApp*>(context);
    if (self == nullptr) {
        return 0;
    }
    auto const ticks = self->ticker_.GetTicksSinceBoot();
    return static_cast<HyphaIpTimestamp_t>(ticks.value());
}

void CyphalApp::OnReport(HyphaIpExternalContext_t context, HyphaIpStatus_e status, char const* const func,
                         char const* const file, unsigned int line) {
    (void)context;
    jarnax::print("HyphaIP: %d at %s:%u in %s\r\n", static_cast<int>(status), file, line, func);
}

HyphaIpStatus_e CyphalApp::OnReceiveUdp(HyphaIpExternalContext_t context, HyphaIpMetaData_t* metadata,
                                        HyphaIpSpan_t datagram) {
    (void)context;
    (void)metadata;
    jarnax::print("CyphalApp::UDP datagram received: %zu bytes\r\n", HyphaIpSpanSize(datagram));
    return HyphaIpStatusOk;
}

}    // namespace cyphal
}    // namespace nucleo

#include "CyphalApp.hpp"

#include "O1HeapPool.hpp"
#include "board.hpp"
#include "core/Conversions.hpp"
#include "core/vsnprint.hpp"
#include "hypha_ip/hypha_ip.h"
#include "jarnax/Assertion.hpp"
#include "memory.hpp"
#include "segger/rtt.hpp"
#include "stm32/h7xx/ethernet/Driver.hpp"
#include "strings.hpp"

#include <cstdarg>
#include <cstring>

namespace {

using namespace jarnax::net::eui48;

constexpr size_t PrintBufferSize{1024U};
char print_buffer_[PrintBufferSize];    ///< Reusable buffer for the OnPrint callback

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

uint32_t HyphaIpToU32(HyphaIpIPv4Address_t addr) {
    return (static_cast<uint32_t>(addr.a) << 24) | (static_cast<uint32_t>(addr.b) << 16) | (static_cast<uint32_t>(addr.c) << 8) |
           (static_cast<uint32_t>(addr.d));
}

HyphaIpIPv4Address_t U32ToHyphaIp(uint32_t addr) {
    HyphaIpIPv4Address_t result{};
    result.a = static_cast<uint8_t>(addr >> 24);
    result.b = static_cast<uint8_t>(addr >> 16);
    result.c = static_cast<uint8_t>(addr >> 8);
    result.d = static_cast<uint8_t>(addr);
    return result;
}

HyphaIpSpan_t MakeSpan(void const* data, std::size_t size) {
    HyphaIpSpan_t span{};
    span.pointer = const_cast<void*>(data);
    span.count = static_cast<decltype(span.count)>(size & 0x0FFFFFFFU);
    span.type = HyphaIpSpanTypeUint8_t;
    return span;
}

bool IsMulticastIPv4(HyphaIpIPv4Address_t addr) {
    return addr.a >= 224U && addr.a <= 239U;
}

void* UdpardAlloc(void* context, size_t size) {
    auto* heap = static_cast<O1HeapInstance*>(context);
    return o1heapAllocate(heap, size);
}

void UdpardFree(void* context, size_t size, void* pointer) {
    (void)size;
    auto* heap = static_cast<O1HeapInstance*>(context);
    o1heapFree(heap, pointer);
}

static udpard_mem_vtable_t const g_allocator_vtable = {
    .base = {.free = &UdpardFree},
    .alloc = &UdpardAlloc,
};

}    // namespace

namespace nucleo {
namespace cyphal {

CyphalApp::CyphalApp(jarnax::Ticker& ticker, jarnax::BoardContext& board_context)
    : board_context_{board_context}
    , ticker_{ticker}
    , ethernet_{board_context.GetEthernet()}
    , hypha_context_{nullptr}
    , network_interface_{}
    , external_interface_{}
    , frame_pool_{}
    , frame_in_use_{}
    , pending_rx_frame_{nullptr}
    , rx_frame_available_{false}
    , tx_{}
    , rx_{}
    , subscription_port_{}
    , unicast_port_{}
    , tx_vtable_{}
    , subscription_vtable_{}
    , unicast_vtable_{}
    , allocator_{}
    , tx_memory_{}
    , rx_memory_{}
    , udpard_initialized_{false}
    , arp_announced_{false}
    , initialized_{false}
    , filter_installed_{false}
    , stats_print_counter_{0U} {
    for (auto& in_use : frame_in_use_) {
        in_use = false;
    }

    std::memset(&external_interface_, 0, sizeof(external_interface_));
    external_interface_.acquire = &CyphalApp::OnAcquire;
    external_interface_.receive = &CyphalApp::TryReceive;
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
}

bool CyphalApp::Execute() {
    if (!initialized_) {
        // Ethernet was Configured in the Board, don't call it again here.
        // Just initialize Hypha IP and let it use the existing Ethernet driver.
        HyphaIpStatus_e const hy_status =
            HyphaIpInitialize(&hypha_context_, &network_interface_, reinterpret_cast<HyphaIpExternalContext_t>(this), &external_interface_);
        if (HyphaIpIsSuccess(hy_status)) {
            initialized_ = true;
        }
        return true;
    }
    if (!filter_installed_) {
        HyphaIpIPv4Address_t allowed_addresses[] = {
            {192, 168, 3, 1},
            {192, 168, 3, 2},
            {192, 168, 3, 4},
        };
        // add the filters for the local network?
        HyphaIpStatus_e status = HyphaIpPopulateIPv4Filter(hypha_context_, HYPHA_IP_DIMOF(allowed_addresses), allowed_addresses);
        if (not HyphaIpIsSuccess(status)) {
            jarnax::print("CyphalApp: HyphaIpPopulateIPv4Filter failed with status %d\r\n", static_cast<int>(status));
        } else {
            jarnax::print("CyphalApp: HyphaIpPopulateIPv4Filter succeeded\r\n");
        }
        filter_installed_ = true;
        return true;
    }
    // Ethernet driver is part of the SuperLoop, no need to call ethernet_.Execute() here
    // Do not process network buffers until the Ethernet link is up
    if (!board_context_.GetLan8742aDriver().IsLinkUp()) {
        return true;
    }

    // Send ARP announcement once so the switch learns our MAC
    if (!arp_announced_) {
        HyphaIpArpAnnouncement(hypha_context_);
        arp_announced_ = true;
    }

    // Lazy-init udpard after hypha is running
    if (!udpard_initialized_) {
        InitUdpard();
        udpard_initialized_ = true;
        // Clear RTT buffer after boot so runtime stats are visible
        rtt::control_block.GetUp(0).Clear();
    }

    HyphaIpRunOnce(hypha_context_);

    udpard_us_t const now = NowUs(ticker_);

    udpard_tx_poll(&tx_, now, 1U);
    udpard_rx_poll(&rx_, now);

    ++stats_print_counter_;
    if (stats_print_counter_ >= 200U) {
        stats_print_counter_ = 0U;
        HyphaIpStatistics_t const* stats = HyphaIpGetStatistics(hypha_context_);
        if (stats != nullptr) {
            jarnax::print(
                "Stats MAC: rx=%zu/%zu IP: rx=%zu/%zu UDP: rx=%zu/%zu "
                "IGMP: tx=%zu rx=%zu/%zu "
                "FRM: aq=%zu rl=%zu fl=%zu "
                "ARP: lk=%zu an=%zu ad=%zu rm=%zu\r\n",
                stats->counter.mac.rx.count,
                stats->mac.accepted,
                stats->counter.ipv4.rx.count,
                stats->ip.accepted,
                stats->counter.udp.rx.count,
                stats->udp.accepted,
                stats->counter.igmp.tx.count,
                stats->counter.igmp.rx.count,
                stats->igmp.accepted,
                stats->frames.acquires,
                stats->frames.releases,
                stats->frames.failures,
                stats->arp.lookups,
                stats->arp.announces,
                stats->arp.additions,
                stats->arp.removals
            );
        }
    }

    return true;
}

void CyphalApp::InitUdpard() {
    O1HeapInstance& heap = O1HeapPool::Instance();
    allocator_.vtable = &g_allocator_vtable;
    allocator_.context = &heap;

    // TX memory: transfer metadata and payload buffers
    tx_memory_.transfer = allocator_;
    for (auto& payload : tx_memory_.payload) {
        payload = allocator_;
    }

    // RX memory: sessions, slots, fragments
    rx_memory_.session = allocator_;
    rx_memory_.slot = allocator_;
    rx_memory_.fragment = allocator_;

    // Build local UID from MAC address padded to 64 bits
    uint64_t const local_uid =
        (static_cast<uint64_t>(network_interface_.mac.oui[0]) << 40) | (static_cast<uint64_t>(network_interface_.mac.oui[1]) << 32) |
        (static_cast<uint64_t>(network_interface_.mac.oui[2]) << 24) | (static_cast<uint64_t>(network_interface_.mac.uid[0]) << 16) |
        (static_cast<uint64_t>(network_interface_.mac.uid[1]) << 8) | (static_cast<uint64_t>(network_interface_.mac.uid[2]));

    tx_vtable_.eject = &CyphalApp::OnTxEject;

    bool ok = udpard_tx_new(&tx_, local_uid, static_cast<uint64_t>(NowUs(ticker_)), 32U, 1U, tx_memory_, &tx_vtable_);
    if (!ok) {
        jarnax::print("CyphalApp: udpard_tx_new failed\r\n");
        return;
    }

    udpard_rx_new(&rx_);
    rx_.user = this;

    udpard_udpip_ep_t const subject_ep = udpard_make_subject_endpoint(SubjectId);

    subscription_vtable_.on_message = &CyphalApp::OnRxMessage;
    ok = udpard_rx_port_new(&subscription_port_, CyphalApp::MaxUdpPayload + 128U, rx_memory_, &subscription_vtable_);
    if (!ok) {
        jarnax::print("CyphalApp: udpard_rx_port_new (subscription) failed\r\n");
        return;
    }

    unicast_vtable_.on_message = &CyphalApp::OnRxMessage;
    ok = udpard_rx_port_new_unicast(&unicast_port_, CyphalApp::MaxUdpPayload + 128U, rx_memory_, &unicast_vtable_);
    if (!ok) {
        jarnax::print("CyphalApp: udpard_rx_port_new_unicast failed\r\n");
        return;
    }

    // Prepare hypha to receive on the subject multicast address
    HyphaIpIPv4Address_t const subject_ip = U32ToHyphaIp(subject_ep.ip);
    HyphaIpPrepareUdpReceive(hypha_context_, subject_ip, UdpPort);
    subscription_port_.user = this;
    unicast_port_.user = this;

    jarnax::print("CyphalApp: udpard initialized\r\n");
}

void CyphalApp::OnFrameReceived(jarnax::net::ethernet::Frame* frame) {
    if (frame != nullptr) {
        CopyJarnaxFrameToHypha(rx_frame_, *frame);
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

HyphaIpStatus_e CyphalApp::TryReceive(HyphaIpExternalContext_t context, HyphaIpEthernetFrame_t* frame) {
    auto* self = reinterpret_cast<CyphalApp*>(context);
    if (self == nullptr || frame == nullptr) {
        return HyphaIpStatusInvalidContext;
    }

    self->pending_rx_frame_ = frame;
    self->rx_frame_available_ = false;

    auto const result = self->ethernet_.Receive(*self);
    (void)result;

    // if we received data, copy the frame into the caller's buffer and forget the pending pointer
    if (self->rx_frame_available_) {
        *frame = self->rx_frame_;
        self->pending_rx_frame_ = nullptr;
        return HyphaIpStatusOk;          // Frame successfully received
    }
    return HyphaIpStatusNotAvailable;    // no frame received, but not an error
}

HyphaIpStatus_e CyphalApp::OnTransmit(HyphaIpExternalContext_t context, HyphaIpEthernetFrame_t* frame) {
    auto* self = reinterpret_cast<CyphalApp*>(context);
    if (self == nullptr || frame == nullptr) {
        return HyphaIpStatusInvalidContext;
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
        return HyphaIpStatusInvalidContext;
    }
    for (std::size_t i = 0; i < FramePoolSize; ++i) {
        if (&self->frame_pool_[i] == frame) {
            self->frame_in_use_[i] = false;
            return HyphaIpStatusOk;
        }
    }
    return HyphaIpStatusInvalidArgument;
}

int CyphalApp::OnPrint(HyphaIpExternalContext_t, char const* const format, ...) {
    va_list list;
    va_start(list, format);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-nonliteral"
#endif
    unsigned long num = core::vsnprint(print_buffer_, sizeof(print_buffer_), format, list);
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
#pragma GCC diagnostic pop
    va_end(list);
    jarnax::print("%s", print_buffer_);
    return static_cast<int>(num);
}

HyphaIpTimestamp_t CyphalApp::OnGetMonotonicTimestamp(HyphaIpExternalContext_t context) {
    auto* self = reinterpret_cast<CyphalApp*>(context);
    if (self == nullptr) {
        return 0;
    }
    auto const ticks = self->ticker_.GetTicksSinceBoot();
    return static_cast<HyphaIpTimestamp_t>(ticks.value());
}

void CyphalApp::OnReport(HyphaIpExternalContext_t, HyphaIpStatus_e status, char const* const func, char const* const file, unsigned int line) {
    if (status != HyphaIpStatusOk and status != HyphaIpStatusNotAvailable) {
        char const* const short_path = strings::last_character(file, '/');
        char const* const tmp = short_path == nullptr ? file : short_path + 1;
        jarnax::print("CyphalApp: OnReport status=%d func=%s file=%s line=%u\r\n", static_cast<int>(status), func, tmp, line);
    }
}

HyphaIpStatus_e CyphalApp::OnReceiveUdp(HyphaIpExternalContext_t context, HyphaIpMetaData_t* metadata, HyphaIpSpan_t datagram) {
    auto* self = reinterpret_cast<CyphalApp*>(context);
    if (self == nullptr || metadata == nullptr) {
        return HyphaIpStatusInvalidArgument;
    }

    if (!self->udpard_initialized_) {
        return HyphaIpStatusOk;
    }

    size_t const payload_size = HyphaIpSpanSize(datagram);
    if (payload_size == 0 || payload_size > MaxUdpPayload) {
        return HyphaIpStatusOk;
    }

    O1HeapInstance& heap = O1HeapPool::Instance();
    void* copy = o1heapAllocate(&heap, payload_size);
    if (copy == nullptr) {
        return HyphaIpStatusOutOfMemory;
    }
    std::memcpy(copy, datagram.pointer, payload_size);

    udpard_udpip_ep_t source_ep{};
    source_ep.ip = HyphaIpToU32(metadata->source_address);
    source_ep.port = metadata->source_port;

    udpard_bytes_mut_t payload{};
    payload.data = copy;
    payload.size = payload_size;

    udpard_deleter_t const deleter = udpard_make_deleter(self->allocator_);

    udpard_us_t const timestamp = NowUs(self->ticker_);

    bool const is_multicast = IsMulticastIPv4(metadata->destination_address);

    bool pushed = false;
    if (is_multicast) {
        pushed = udpard_rx_port_push(&self->rx_, &self->subscription_port_, timestamp, source_ep, payload, deleter, 0U);
    } else {
        pushed = udpard_rx_port_push(&self->rx_, &self->unicast_port_, timestamp, source_ep, payload, deleter, 0U);
    }

    if (!pushed) {
        o1heapFree(&heap, copy);
    }

    return HyphaIpStatusOk;
}

// ------------------------------------------------------------------------------------------------------------------
// LibUDPard Callbacks
// ------------------------------------------------------------------------------------------------------------------

bool CyphalApp::OnTxEject(udpard_tx_t* tx, udpard_tx_ejection_t* ejection) {
    auto* self = static_cast<CyphalApp*>(tx->user);
    if (self == nullptr || ejection == nullptr) {
        return false;
    }

    HyphaIpMetaData_t metadata{};
    metadata.source_address = self->network_interface_.address;
    metadata.destination_address = U32ToHyphaIp(ejection->destination.ip);
    metadata.source_port = UdpPort;
    metadata.destination_port = ejection->destination.port;
    metadata.timestamp = static_cast<HyphaIpTimestamp_t>(ejection->now / 1000);

    HyphaIpSpan_t const span = MakeSpan(ejection->datagram.data, ejection->datagram.size);

    HyphaIpStatus_e const hy_status = HyphaIpTransmitUdpDatagram(self->hypha_context_, &metadata, span);
    return HyphaIpIsSuccess(hy_status);
}

void CyphalApp::OnRxMessage(udpard_rx_t* rx, udpard_rx_port_t* port, udpard_rx_transfer_t transfer) {
    (void)rx;
    (void)port;
    jarnax::print(
        "CyphalApp: msg prio=%d tid=%llu %zu/%zuB from ",
        static_cast<int>(transfer.priority),
        static_cast<unsigned long long>(transfer.transfer_id),
        transfer.payload_size_stored,
        transfer.payload_size_wire
    );
    for (uint_fast8_t iface = 0; iface < UDPARD_IFACE_COUNT_MAX; ++iface) {
        if (udpard_is_valid_endpoint(transfer.remote.endpoints[iface])) {
            uint32_t const ip = transfer.remote.endpoints[iface].ip;
            jarnax::print(
                "%d.%d.%d.%d:%u ",
                static_cast<int>((ip >> 24) & 0xFF),
                static_cast<int>((ip >> 16) & 0xFF),
                static_cast<int>((ip >> 8) & 0xFF),
                static_cast<int>(ip & 0xFF),
                transfer.remote.endpoints[iface].port
            );
        }
    }
    jarnax::print("uid=%llu", static_cast<unsigned long long>(transfer.remote.uid));

    jarnax::print(" payload=");
    udpard_fragment_t const* frag = udpard_fragment_seek(transfer.payload, 0);
    while (frag != nullptr) {
        uint8_t const* const data = static_cast<uint8_t const*>(frag->view.data);
        for (size_t i = 0; i < frag->view.size; ++i) {
            jarnax::print("%02X", data[i]);
        }
        frag = udpard_fragment_next(frag);
    }
    jarnax::print("\r\n");

    udpard_fragment_free_all(transfer.payload, udpard_make_deleter(port->memory.fragment));
}

udpard_us_t CyphalApp::NowUs(jarnax::Ticker const& ticker) {
    auto const ticks = ticker.GetTicksSinceBoot();
    return static_cast<udpard_us_t>(ticks.value()) * 1000LL;
}

}    // namespace cyphal
}    // namespace nucleo

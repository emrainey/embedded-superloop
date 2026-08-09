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

#include "uavcan/node/GetInfo_1_0.h"
#include "uavcan/node/Heartbeat_1_0.h"

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

void* UdpardAlloc(void* context, size_t size) {
    auto* heap = static_cast<O1HeapInstance*>(context);
    return o1heapAllocate(heap, size);
}

void UdpardFree(void* context, size_t size, void* pointer) {
    (void)size;
    auto* heap = static_cast<O1HeapInstance*>(context);
    o1heapFree(heap, pointer);
}

bool SameIPv4Address(HyphaIpIPv4Address_t const& a, HyphaIpIPv4Address_t const& b) {
    static_assert(sizeof(a) == sizeof(uint32_t), "Must be exactly this size");
    return std::memcmp(&a, &b, sizeof(a)) == 0;
}

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
    , node_id_{NodeId}
    , tx_{}
    , subscription_{}
    , tx_memory_{}
    , rx_memory_{}
    , service_dispatcher_{}
    , get_info_service_port_{}
    , service_group_address_{}
    , udpard_initialized_{false}
    , arp_announced_{false}
    , initialized_{false}
    , filter_installed_{false}
    , service_initialized_{false}
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

    network_interface_.address = HyphaIpIPv4Address_t{192, 168, 3, NodeId};
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

        // Add explicit MAC filter entries for the Cyphal multicast groups we participate in:
        //   Heartbeat subject 7509   -> 239.0.29.85  -> 01:00:5E:00:1D:55
        //   Service multicast node 103 -> 239.1.0.103 -> 01:00:5E:01:00:67
        HyphaIpEthernetAddress_t cyphal_multicast_macs[] = {
            {.oui = {0x01, 0x00, 0x5E}, .uid = {0x00, 0x1D, 0x55}},    // subject 7509 (Heartbeat)
            {.oui = {0x01, 0x00, 0x5E}, .uid = {0x01, 0x00, 0x67}},    // service multicast node 103
        };
        HyphaIpStatus_e mac_status =
            HyphaIpPopulateEthernetFilter(hypha_context_, HYPHA_IP_DIMOF(cyphal_multicast_macs), cyphal_multicast_macs);
        if (not HyphaIpIsSuccess(mac_status)) {
            jarnax::print("CyphalApp: HyphaIpPopulateEthernetFilter failed with status %d\r\n", static_cast<int>(mac_status));
        } else {
            jarnax::print("CyphalApp: HyphaIpPopulateEthernetFilter succeeded\r\n");
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

    // Lazy-init the service dispatcher after udpard is running
    if (!service_initialized_) {
        ServiceDispatcherInit();
        service_initialized_ = true;
    }

    HyphaIpRunOnce(hypha_context_);

    ProcessTransmitQueue();

    // Publish a Heartbeat at most once per second (uavcan.node.Heartbeat.1.0
    // MAX_PUBLICATION_PERIOD is 1 second, OFFLINE_TIMEOUT is 3 seconds).
    jarnax::Ticks const current_ticks = ticker_.GetTicksSinceBoot();
    if ((current_ticks.value() - last_heartbeat_ticks_.value()) >= ticker_.GetTicksPerSecond().value()) {
        last_heartbeat_ticks_ = current_ticks;
        PublishHeartbeat();
    }

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

    // v1.x memory resources wrap the same O1Heap-backed allocator.
    struct UdpardMemoryResource const memory = {
        .user_reference = &heap,
        .deallocate = &UdpardFree,
        .allocate = &UdpardAlloc,
    };
    tx_memory_ = memory;

    rx_memory_.session = memory;
    rx_memory_.fragment = memory;
    rx_memory_.payload = {
        .user_reference = &heap,
        .deallocate = &UdpardFree,
    };

    // TX pipeline: single (non-redundant) interface, capacity bounded by the O1Heap.
    int_fast8_t const tx_init = udpardTxInit(&tx_, &node_id_, 32U, tx_memory_);
    if (tx_init < 0) {
        jarnax::print("CyphalApp: udpardTxInit failed with %d\r\n", static_cast<int>(tx_init));
        return;
    }
    tx_.mtu = UDPARD_MTU_DEFAULT;

    // Subscription for the Heartbeat subject.
    int_fast8_t const sub_init = udpardRxSubscriptionInit(&subscription_, SubjectId, MaxUdpPayload + 128U, rx_memory_);
    if (sub_init < 0) {
        jarnax::print("CyphalApp: udpardRxSubscriptionInit failed with %d\r\n", static_cast<int>(sub_init));
        return;
    }

    // Prepare hypha to receive on the subject multicast address (and to send membership reports).
    HyphaIpIPv4Address_t const subject_ip = U32ToHyphaIp(subscription_.udp_ip_endpoint.ip_address);
    HyphaIpPrepareUdpReceive(hypha_context_, subject_ip, UdpPort);

    jarnax::print("CyphalApp: udpard v1 initialized\r\n");
}

void CyphalApp::ServiceDispatcherInit() {
    O1HeapInstance& heap = O1HeapPool::Instance();

    // The RPC dispatcher shares the same O1Heap-backed memory resources as the subjects pipeline.
    struct UdpardMemoryResource const memory = {
        .user_reference = &heap,
        .deallocate = &UdpardFree,
        .allocate = &UdpardAlloc,
    };
    struct UdpardRxMemoryResources const dispatcher_memory = {
        .session = memory,
        .fragment = memory,
        .payload = {
            .user_reference = &heap,
            .deallocate = &UdpardFree,
        },
    };

    int_fast8_t const dispatcher_init = udpardRxRPCDispatcherInit(&service_dispatcher_, dispatcher_memory);
    if (dispatcher_init < 0) {
        jarnax::print("CyphalApp: udpardRxRPCDispatcherInit failed with %d\r\n", static_cast<int>(dispatcher_init));
        return;
    }

    // The dispatcher derives the service-UDP multicast group from the local node-ID.
    struct UdpardUDPIPEndpoint service_endpoint{};
    int_fast8_t const dispatcher_start = udpardRxRPCDispatcherStart(&service_dispatcher_, node_id_, &service_endpoint);
    if (dispatcher_start < 0) {
        jarnax::print("CyphalApp: udpardRxRPCDispatcherStart failed with %d\r\n", static_cast<int>(dispatcher_start));
        return;
    }
    service_group_address_ = U32ToHyphaIp(service_endpoint.ip_address);

    // The service request port for uavcan.node.GetInfo (request direction = is_request=true).
    int_fast8_t const listen =
        udpardRxRPCDispatcherListen(&service_dispatcher_, &get_info_service_port_, GetInfoServiceId, true,
                                    uavcan_node_GetInfo_Response_1_0_EXTENT_BYTES_);
    if (listen < 0) {
        jarnax::print("CyphalApp: udpardRxRPCDispatcherListen failed with %d\r\n", static_cast<int>(listen));
        return;
    }

    // Join the service multicast group so incoming service requests are accepted.
    HyphaIpPrepareUdpReceive(hypha_context_, service_group_address_, UdpPort);

    jarnax::print("CyphalApp: GetInfo service (430) initialized\r\n");
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

    struct UdpardMutablePayload payload{};
    payload.data = copy;
    payload.size = payload_size;

    if (SameIPv4Address(metadata->destination_address, self->service_group_address_)) {
        // Service multicast datagram (e.g. a GetInfo request addressed to this node).
        if (self->service_initialized_) {
            struct UdpardRxRPCTransfer transfer{};
            int_fast8_t const result = udpardRxRPCDispatcherReceive(
                &self->service_dispatcher_, NowUs(self->ticker_), payload, 0U, nullptr, &transfer);
            if (result > 0) {
                self->ServiceResponseHandler(transfer);
                udpardRxFragmentFree(transfer.base.payload, self->rx_memory_.fragment, self->rx_memory_.payload);
            }
        } else {
            o1heapFree(&heap, copy);
        }
        return HyphaIpStatusOk;
    }

    struct UdpardRxTransfer transfer;
    udpardRxSubscriptionReceive(&self->subscription_, NowUs(self->ticker_), payload, 0U, &transfer);

    return HyphaIpStatusOk;
}

// ------------------------------------------------------------------------------------------------------------------
// LibUDPard v1.x: TX queue draining
// ------------------------------------------------------------------------------------------------------------------

void CyphalApp::ProcessTransmitQueue() {
    while (struct UdpardTxItem const* item = udpardTxPeek(&tx_)) {
        HyphaIpMetaData_t metadata{};
        metadata.source_address = network_interface_.address;
        metadata.destination_address = U32ToHyphaIp(item->destination.ip_address);
        metadata.source_port = UdpPort;
        metadata.destination_port = item->destination.udp_port;
        metadata.timestamp = static_cast<HyphaIpTimestamp_t>(item->deadline_usec / 1000);

        HyphaIpSpan_t const span = MakeSpan(item->datagram_payload.data, item->datagram_payload.size);
        HyphaIpStatus_e const hy_status = HyphaIpTransmitUdpDatagram(hypha_context_, &metadata, span);
        jarnax::print(
            "CyphalApp: tx %d.%d.%d.%d:%u %zuB -> %d\r\n",
            static_cast<int>((item->destination.ip_address >> 24) & 0xFF),
            static_cast<int>((item->destination.ip_address >> 16) & 0xFF),
            static_cast<int>((item->destination.ip_address >> 8) & 0xFF),
            static_cast<int>(item->destination.ip_address & 0xFF),
            item->destination.udp_port,
            item->datagram_payload.size,
            static_cast<int>(hy_status)
        );

        struct UdpardTxItem* const taken = udpardTxPop(&tx_, item);
        udpardTxFree(tx_memory_, taken);
        if (!HyphaIpIsSuccess(hy_status)) {
            break;    // do not spin; retry on the next Execute cycle
        }
    }
}

void CyphalApp::ServiceResponseHandler(struct UdpardRxRPCTransfer const& transfer) {
    // Only respond to GetInfo *requests* (is_request == true) for our service.
    if (!transfer.is_request || transfer.service_id != GetInfoServiceId) {
        return;
    }

    uavcan_node_GetInfo_Response_1_0 info{};
    std::memset(&info, 0, sizeof(info));    // All GetInfo defaults are zero; avoids the generated deserialize init.

    // Assigned node identification for now (not MAC-derived).
    info.protocol_version.major = 1U;
    info.protocol_version.minor = 0U;
    info.software_version.major = 1U;
    info.software_version.minor = 0U;
    info.software_vcs_revision_id = 0U;

    static constexpr char const NodeName[] = "com.emrainey.superloop.nucleo";
    info.name.count = sizeof(NodeName) - 1U;
    std::memcpy(info.name.elements, NodeName, info.name.count);

    uint8_t const assigned_unique_id[16U] = {0xDEU, 0xADU, 0xBEU, 0xEFU, 0x10U, 0x20U, 0x30U, 0x40U,
                                             0x50U, 0x60U, 0x70U, 0x80U, 0x90U, 0xA0U, 0xB0U, 0xC0U};
    std::memcpy(info.unique_id, assigned_unique_id, sizeof(assigned_unique_id));

    uint8_t buffer[uavcan_node_GetInfo_Response_1_0_SERIALIZATION_BUFFER_SIZE_BYTES_]{};
    size_t serialized_size = sizeof(buffer);
    int8_t const err = uavcan_node_GetInfo_Response_1_0_serialize_(&info, buffer, &serialized_size);
    if (err < 0) {
        return;
    }

    struct UdpardPayload const payload = {
        .size = serialized_size,
        .data = buffer,
    };

    int32_t const result = udpardTxRespond(&tx_, NowUs(ticker_) + 1000000U, UdpardPriorityNominal, GetInfoServiceId,
                                           transfer.base.source_node_id, transfer.base.transfer_id, payload, this);
    jarnax::print(
        "CyphalApp: GetInfo response sent=%d to node %u service_id=%u\r\n",
        static_cast<int>(result),
        static_cast<unsigned>(static_cast<uint16_t>(transfer.base.source_node_id)),
        static_cast<unsigned>(transfer.service_id)
    );
}

void CyphalApp::PublishHeartbeat() {
    uavcan_node_Heartbeat_1_0 heartbeat{};
    uavcan_node_Heartbeat_1_0_initialize_(&heartbeat);

    // Integer seconds since boot, not a float.
    heartbeat.uptime = static_cast<uint32_t>(NowUs(ticker_) / 1000000U);
    heartbeat.health.value = uavcan_node_Health_1_0_NOMINAL;
    heartbeat.mode.value = uavcan_node_Mode_1_0_OPERATIONAL;
    heartbeat.vendor_specific_status_code = 0U;

    uint8_t buffer[uavcan_node_Heartbeat_1_0_SERIALIZATION_BUFFER_SIZE_BYTES_]{};
    size_t serialized_size = sizeof(buffer);
    int8_t const err = uavcan_node_Heartbeat_1_0_serialize_(&heartbeat, buffer, &serialized_size);
    if (err < 0) {
        return;
    }

    struct UdpardPayload const payload = {
        .size = serialized_size,
        .data = buffer,
    };

    UdpardMicrosecond const now = NowUs(ticker_);
    static constexpr UdpardMicrosecond HeartbeatPeriodUs = 1000000U;

    int32_t const result = udpardTxPublish(
        &tx_, now + HeartbeatPeriodUs, UdpardPriorityNominal, SubjectId,
        heartbeat_transfer_id_++, payload, this
    );
    jarnax::print(
        "CyphalApp: heartbeat published=%d uptime=%lu tid=%llu\r\n",
        static_cast<int>(result), static_cast<unsigned long>(heartbeat.uptime),
        static_cast<unsigned long long>(heartbeat_transfer_id_ - 1U)
    );
}

UdpardMicrosecond CyphalApp::NowUs(jarnax::Ticker const& ticker) {
    auto const ticks = ticker.GetTicksSinceBoot();
    return static_cast<UdpardMicrosecond>(ticks.value()) * 1000LL;
}

}    // namespace cyphal
}    // namespace nucleo

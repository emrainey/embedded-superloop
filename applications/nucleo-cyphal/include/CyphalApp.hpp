#ifndef APP_CYPHAL_APP_HPP
#define APP_CYPHAL_APP_HPP

#include "BoardContext.hpp"
#include "GetInfoScanner.hpp"
#include "core/Allocator.hpp"
#include "jarnax/Loopable.hpp"
#include "jarnax/Ticker.hpp"
#include "jarnax/net/ethernet/Driver.hpp"

#include "jarnax/net/ethernet/Allocator.hpp"

extern "C" {
#include "hypha_ip/hypha_ip.h"
#include "udpard.h"
}

namespace nucleo {
namespace cyphal {

class CyphalApp final : public jarnax::Loopable, public jarnax::net::ethernet::Driver::Listener {
public:
    static constexpr std::size_t FramePoolSize = 4U;

    static constexpr uint16_t UdpPort = 9382U;
    static constexpr uint32_t SubjectId = 7509U;
    static constexpr UdpardPortID DiagnosticSubjectId = 8184U;
    static constexpr UdpardPortID GetInfoServiceId = 430U;
    static constexpr std::size_t MaxUdpPayload = 1400U;
    // Cyphal/UDP binds the node-ID to the last octet of the node's source IP.
    static constexpr UdpardNodeID NodeId = 103U;

    // GetInfo client scan window (server node-IDs, inclusive).
    static constexpr UdpardNodeID ScanFirstNode = 2U;
    static constexpr UdpardNodeID ScanLastNode = 10U;

    CyphalApp(jarnax::Ticker& ticker, jarnax::BoardContext& board_context);

    bool Execute() override;

protected:
    // jarnax::net::ethernet::Driver::Listener
    void OnFrameReceived(jarnax::net::ethernet::Frame* frame) override;

    // Hypha IP External Interface Callbacks
    static HyphaIpEthernetFrame_t* OnAcquire(HyphaIpExternalContext_t context);
    static HyphaIpStatus_e TryReceive(HyphaIpExternalContext_t context, HyphaIpEthernetFrame_t* frame);
    static HyphaIpStatus_e OnTransmit(HyphaIpExternalContext_t context, HyphaIpEthernetFrame_t* frame);
    static HyphaIpStatus_e OnRelease(HyphaIpExternalContext_t context, HyphaIpEthernetFrame_t* frame);
    static int OnPrint(HyphaIpExternalContext_t context, char const* const format, ...);
    static HyphaIpTimestamp_t OnGetMonotonicTimestamp(HyphaIpExternalContext_t context);
    static void OnReport(HyphaIpExternalContext_t context, HyphaIpStatus_e status, char const* const func, char const* const file, unsigned int line);
    static HyphaIpStatus_e OnReceiveUdp(HyphaIpExternalContext_t context, HyphaIpMetaData_t* metadata, HyphaIpSpan_t datagram);

    void InitUdpard();
    void PublishHeartbeat();
    void PublishRecord();
    void ProcessTransmitQueue();
    void ServiceDispatcherInit();
    void ServiceResponseHandler(struct UdpardRxRPCTransfer const& transfer);
    void GetInfoResponseHandler(struct UdpardRxRPCTransfer const& transfer);
    void SendGetInfoRequest(UdpardNodeID server_node_id);

    static UdpardMicrosecond NowUs(jarnax::Ticker const& ticker);

    jarnax::BoardContext& board_context_;
    jarnax::Ticker& ticker_;
    jarnax::net::ethernet::Driver& ethernet_;

    HyphaIpContext_t hypha_context_;
    HyphaIpNetworkInterface_t network_interface_;
    HyphaIpExternalInterface_t external_interface_;

    HyphaIpEthernetFrame_t frame_pool_[FramePoolSize];
    bool frame_in_use_[FramePoolSize];

    HyphaIpEthernetFrame_t* pending_rx_frame_;
    bool rx_frame_available_;
    HyphaIpEthernetFrame_t rx_frame_;

    // LibUDPard state (v1.x API)
    UdpardNodeID node_id_;
    UdpardTx tx_;
    UdpardRxSubscription subscription_;
    struct UdpardMemoryResource tx_memory_;
    struct UdpardRxMemoryResources rx_memory_;
    struct UdpardRxRPCDispatcher service_dispatcher_;
    struct UdpardRxRPCPort get_info_service_port_;
    struct UdpardRxRPCPort get_info_response_port_;
    HyphaIpIPv4Address_t service_group_address_;
    GetInfoScanner get_info_scanner_;

    bool udpard_initialized_;
    bool arp_announced_;
    bool initialized_;
    bool filter_installed_;
    bool service_initialized_;
    size_t stats_print_counter_;
    UdpardTransferID heartbeat_transfer_id_;
    jarnax::Ticks last_heartbeat_ticks_;
    UdpardTransferID record_transfer_id_;
    jarnax::Ticks last_record_ticks_;
    uint32_t record_counter_;
    jarnax::Ticks last_getinfo_scan_ticks_;
};

}    // namespace cyphal
}    // namespace nucleo

#endif    // APP_CYPHAL_APP_HPP

#ifndef APP_CYPHAL_APP_HPP
#define APP_CYPHAL_APP_HPP

#include "BoardContext.hpp"
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

class CyphalApp final : public jarnax::Loopable,
                        public jarnax::net::ethernet::Driver::Listener {
public:
    static constexpr std::size_t FramePoolSize = 4U;

    static constexpr uint16_t UdpPort = 9382U;
    static constexpr uint32_t SubjectId = 7509U;  
    static constexpr std::size_t MaxUdpPayload = 1400U;

    CyphalApp(jarnax::Ticker& ticker, jarnax::BoardContext& board_context);

    bool Execute() override;

protected:
    // jarnax::net::ethernet::Driver::Listener
    void OnFrameReceived(jarnax::net::ethernet::Frame* frame) override;

    // Hypha IP External Interface Callbacks
    static HyphaIpEthernetFrame_t* OnAcquire(HyphaIpExternalContext_t context);
    static HyphaIpStatus_e OnReceive(HyphaIpExternalContext_t context, HyphaIpEthernetFrame_t* frame);
    static HyphaIpStatus_e OnTransmit(HyphaIpExternalContext_t context, HyphaIpEthernetFrame_t* frame);
    static HyphaIpStatus_e OnRelease(HyphaIpExternalContext_t context, HyphaIpEthernetFrame_t* frame);
    static int OnPrint(HyphaIpExternalContext_t context, char const* const format, ...);
    static HyphaIpTimestamp_t OnGetMonotonicTimestamp(HyphaIpExternalContext_t context);
    static void OnReport(HyphaIpExternalContext_t context, HyphaIpStatus_e status, char const* const func,
                         char const* const file, unsigned int line);
    static HyphaIpStatus_e OnReceiveUdp(HyphaIpExternalContext_t context, HyphaIpMetaData_t* metadata,
                                        HyphaIpSpan_t datagram);

    // LibUDPard Callbacks
    static bool OnTxEject(udpard_tx_t* tx, udpard_tx_ejection_t* ejection);
    static void OnRxMessage(udpard_rx_t* rx, udpard_rx_port_t* port, udpard_rx_transfer_t transfer);

    void InitUdpard();

    static udpard_us_t NowUs(jarnax::Ticker const& ticker);

    jarnax::BoardContext& board_context_;
    jarnax::Ticker& ticker_;
    jarnax::net::ethernet::Driver& ethernet_;
    jarnax::net::ethernet::Driver::Addresses mac_addresses_;

    HyphaIpContext_t hypha_context_;
    HyphaIpNetworkInterface_t network_interface_;
    HyphaIpExternalInterface_t external_interface_;

    HyphaIpEthernetFrame_t frame_pool_[FramePoolSize];
    bool frame_in_use_[FramePoolSize];

    HyphaIpEthernetFrame_t* pending_rx_frame_;
    bool rx_frame_available_;

    // LibUDPard state
    udpard_tx_t tx_;
    udpard_rx_t rx_;
    udpard_rx_port_t subscription_port_;
    udpard_rx_port_t unicast_port_;
    udpard_tx_vtable_t tx_vtable_;
    udpard_rx_port_vtable_t subscription_vtable_;
    udpard_rx_port_vtable_t unicast_vtable_;
    udpard_mem_t allocator_;
    udpard_tx_mem_resources_t tx_memory_;
    udpard_rx_mem_resources_t rx_memory_;

    bool udpard_initialized_;

    bool initialized_;
};

}    // namespace cyphal
}    // namespace nucleo

#endif    // APP_CYPHAL_APP_HPP

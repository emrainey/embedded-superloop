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
}

namespace nucleo {
namespace cyphal {

class CyphalApp final : public jarnax::Loopable,
                        public jarnax::net::ethernet::Driver::Listener {
public:
    static constexpr std::size_t FramePoolSize = 4U;

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

    bool initialized_;
};

}    // namespace cyphal
}    // namespace nucleo

#endif    // APP_CYPHAL_APP_HPP

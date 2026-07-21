#ifndef JARNAX_ETHERNET_DRIVER_HPP
#define JARNAX_ETHERNET_DRIVER_HPP

/// @file
/// The Ethernet Driver Declaration

#include "jarnax/Driver.hpp"
#include "jarnax/net/configuration.hpp"
#include "jarnax/net/ethernet/Frame.hpp"
#include "jarnax/net/ethernet/Phy.hpp"
#include "jarnax/net/eui/Address.hpp"

namespace jarnax {
namespace net {
namespace ethernet {

/// The pure virtual interface which all Ethernet Drivers implement.
/// @details The Ethernet Driver is responsible for sending and receiving Ethernet frames on the network. It provides an interface for higher-level
/// network protocols (e.g., ARP, IP) to send and receive data over the network. The Ethernet Driver is typically implemented as a hardware driver
/// that interacts with the Ethernet controller on the microcontroller to send and receive frames.
class Driver : public jarnax::Driver {
public:
    /// The addresses list typed used to configure the MAC Addresses in the Controller.
    /// @note The size is determined by the MaxMACAddressCount constant defined in the configuration.hpp file, which should be set to the maximum
    /// number of addresses that the hardware can support.
    using Addresses = std::array<eui48::Address, MaxMACAddressCount>;

    /// Configures the Mac to use the provided addresses. The count of addresses must match the count provided by hardware!
    virtual core::Status Configure(Addresses const& addresses) = 0;

    /// Gets the MAC Address of the controller at the specified index. The index should be between 0 and the maximum number of addresses supported
    /// by the hardware (as defined by the MaxMACAddressCount constant in the configuration.hpp file).
    virtual net::eui48::Address GetMacAddress(size_t index = 0) const = 0;

    /// Sends an Ethernet frame on the network. This method is used by higher-level network protocols (e.g., ARP, IP) to send data over the network.
    /// The user is responsible for constructing the Ethernet frame with the appropriate headers and payload, and then transmitting it on
    /// the network.
    /// @param frame The Ethernet frame to send on the network. The payloads should be constructed, but the Driver will take care of the Ethernet
    /// Header
    /// @return A core::Status indicating the success or failure of the send operation. If the send operation is successful, the status will indicate
    /// success. If there is an error during the send operation (e.g., if the Ethernet controller is not initialized or if there is a hardware
    /// failure), the status will indicate the type of error that occurred.
    virtual core::Status Transmit(net::ethernet::Frame* frame) = 0;

    /// The Listener class is an interface that higher-level network protocols (e.g., ARP, IP) can implement to receive Ethernet frames from the
    /// network. The Ethernet Driver is responsible for listening for incoming Ethernet frames on the network, and when a frame is received it should
    /// be parsed and passed to the OnFrameReceived method of this Listener interface for processing by the higher-level network protocols.
    class Listener {
    public:
        /// Called when the Ethernet Driver receives an Ethernet frame from the network. This method is used by higher-level network protocols (e.g.,
        /// ARP, IP) to receive data from the network. The Ethernet Driver is responsible for listening for incoming Ethernet frames on the network,
        /// and when a frame is received it should be parsed and passed to this method for processing by the higher-level network protocols.
        /// @param frame The Ethernet frame that was received from the network. The frame should be parsed and constructed with the appropriate
        /// headers and payload before being passed to this method.
        virtual void OnFrameReceived(net::ethernet::Frame* frame) = 0;

    protected:
        ~Listener() = default;
    };

    /// Receives an Ethernet frame from the network. This method is used by higher-level network protocols (e.g., ARP, IP) to receive data from the
    /// network. The Ethernet Driver is responsible for listening for incoming Ethernet frames on the network, and when a frame is received it should
    /// be parsed and passed to this method for processing by the higher-level network protocols.
    /// @param listener The Listener that will handle the received Ethernet frames. The listener should implement the OnFrameReceived method to
    /// process the received frames.
    /// @return A core::Status indicating the success or failure of the receive operation. If the receive operation is successful, the status will
    /// indicate success. If there is an error during the receive operation (e.g., if the Ethernet controller is not initialized or if there is a
    /// hardware failure), the status will indicate the type of error that occurred.
    virtual core::Status Receive(Listener& listener) = 0;

    /// Indicates when the driver is ready to transmit and receive Ethernet frames.
    virtual bool IsReady() const = 0;

protected:
    ~Driver() = default;
};

}    // namespace ethernet
}    // namespace net
}    // namespace jarnax

#endif    // JARNAX_ETHERNET_DRIVER_HPP

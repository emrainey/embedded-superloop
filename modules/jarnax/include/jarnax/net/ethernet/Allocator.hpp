#ifndef JARNAX_NET_ETHERNET_ALLOCATOR_HPP
#define JARNAX_NET_ETHERNET_ALLOCATOR_HPP

/// @file
/// The Frame Allocator Declaration

#include "jarnax/net/ethernet/Frame.hpp"

namespace jarnax {
namespace net {
namespace ethernet {

/// The Allocator class is an interface that can be implemented to manage the memory of Ethernet frames. The Allocator is
/// responsible for allocating and deallocating memory for Ethernet frames for Drivers and higher-level network protocols (e.g., ARP, IP, UDP).
/// The Allocator interface provides methods to acquire and release Ethernet frames when processing incoming or outgoing frames from the network. The
/// Allocator can implement this Allocator interface to provide a mechanism for higher-level network protocols to manage the memory of Ethernet frames
/// in a way that is efficient and compatible with the hardware capabilities of the Ethernet controller on the microcontroller.
class Allocator {
public:
    /// Acquires an Ethernet frame from the Allocator. This method is used by the Driver to receive data or the high level protocols to transmit data
    /// to or from the network.
    /// @return A pointer to an Ethernet frame that was acquired from the Allocator. The frame should be constructed with the appropriate
    /// headers and payload after being returned by this method. If a nullptr is returned, this indicates that there was no memory available to
    /// acquire a new Frame.
    virtual Frame* Acquire(void) = 0;

    /// Releases an Ethernet frame back to the Allocator. This is used by the Driver after a frame was Transmitted or by the high level protocols once
    /// a frame was received.
    /// @param frame A pointer to the Ethernet frame that is being released back to the Allocator. The frame should have been previously
    /// acquired from the Allocator using the Acquire method. If the frame pointer is null, this method should handle it gracefully (e.g., by
    /// ignoring the release request or by logging an error) to prevent potential issues with the Allocator's memory management.
    virtual void Release(Frame* frame) = 0;

protected:
    ~Allocator() = default;
};

}    // namespace ethernet
}    // namespace net
}    // namespace jarnax

#endif    // JARNAX_NET_ETHERNET_ALLOCATOR_HPP

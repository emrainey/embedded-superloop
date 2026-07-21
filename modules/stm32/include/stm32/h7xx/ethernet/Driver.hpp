#ifndef STM32_H7XX_ETHERNET_DRIVER_HPP
#define STM32_H7XX_ETHERNET_DRIVER_HPP

/// @file
/// STM32H7xx Ethernet Driver Implementation

#include <core/Allocator.hpp>
#include <core/Buffer.hpp>
#include "jarnax/Driver.hpp"
#include "jarnax/net/ethernet/Allocator.hpp"
#include "jarnax/net/ethernet/Driver.hpp"
#include "jarnax/net/ethernet/Frame.hpp"
#include "jarnax/net/ethernet/Phy.hpp"

namespace stm32 {
namespace ethernet {

/// @brief STM32H7xx Ethernet peripheral driver implementation
/// @details Provides Ethernet communication for STM32H7xx microcontrollers.
/// Implements the jarnax::net::ethernet::Driver interface with STM32H7xx-specific hardware control and the Phy interface for controlling the Ethernet
/// PHY.
class Driver final : public jarnax::net::ethernet::Driver, public jarnax::net::ethernet::Phy, public jarnax::net::ethernet::Allocator {
public:
    /// @brief Constructor
    /// @param allocator The Allocator to use for Ethernet frame memory management
    Driver(core::Allocator& allocator);

    //+=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    // Jarnax::Driver Interface
    core::Status Initialize(void) override;
    bool Execute(void) override;
    //+=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    // jarnax::net::ethernet::Driver Interface
    core::Status Configure(Addresses const& addresses) override;
    jarnax::net::eui48::Address GetMacAddress(size_t index = 0) const override;
    core::Status Transmit(jarnax::net::ethernet::Frame const* frame) override;
    core::Status Receive(Listener& listener) override;
    //+=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    // jarnax::net::ethernet::Phy Interface
    core::Status Schedule(jarnax::net::ethernet::mdio::Transaction* txn) override;
    //+=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    // jarnax::net::ethernet::Allocator Interface
    jarnax::net::ethernet::Frame* Acquire(void) override;
    void Release(jarnax::net::ethernet::Frame* frame) override;

    ~Driver() = default;

protected:
    core::Allocator& allocator_;    ///< The Allocator used for Ethernet frame memory management
};

namespace dma {

/// The control for the CRC and padding of the frame for a transmit descriptor. This controls whether the DMA controller will calculate and append the
enum class CRCPadControl : uint32_t {
    PadAndCRC = 0b00,    ///< Pad the frame to the minimum Ethernet frame size if it is smaller than that, and also calculate and append the CRC to
                         ///< the end of the frame
    InsertionOnly =
        0b01,            ///< Only calculate and append the CRC to the end of the frame, without padding the frame to the minimum Ethernet frame size
    Nothing = 0b10,      ///< Do not calculate or append the CRC, and do not pad the frame to the minimum Ethernet frame size
    Replace = 0b11,      ///< Replace the frame's existing CRC (if any) with a newly calculated CRC, but do not pad the frame to the minimum Ethernet
                         ///< frame size
};

/// The control for the source address insertion for a transmit descriptor. This controls whether the DMA controller will insert the MAC address of
/// the Ethernet controller as the source address in the Ethernet frame, and if so, whether it will insert it in place of an existing source address
/// or in an empty field.
enum class SourceAddressInsertionControl : uint32_t {
    None = 0,       ///< No insertion, the frame is transmitted as-is
    Insert = 1,     ///< Insert the Unit in place (user must provide a zero'd field)
    Replace = 2,    ///< Replace the Unit in place (user must provide a filled in field, but the value may be overwritten)
};

/// The control for the checksum insertion for a transmit descriptor. This controls whether the DMA controller will calculate and insert the checksums
/// for the frame, and if so, which checksums it will calculate and insert.
enum class ChecksumInsertionControl : uint32_t {
    None = 0,       ///< No insertion, the frame is transmitted as-is
    IP_Only = 1,    ///< Inserts the IP checksum in place (user must provide a zero'd field), no others

    /// Inserts the TCP checksum in place (user must provide a zero'd field), and also inserts the IP checksum if it is an IP frame
    TCP_IP_Only = 2,
    All = 3,    ///< Inserts all relevant checksums in place (user must provide zero'd fields), including TCP, UDP, and IP checksums as appropriate
                ///< for the frame being transmitted
};

/// The control for the VLAN tag insertion or replacement for a transmit descriptor.
enum class InnerVLANControl : uint32_t {
    None = 0,       ///< No insertion, the frame is transmitted as-is
    Remove = 1,     ///< Remove the inner VLAN tag from the frame (should not be used with non-VLAN frames)
    Insert = 2,     ///< Insert the inner VLAN in place (user must provide a zero'd field)
    Replace = 3,    ///< Replace the inner VLAN in place (user must provide a filled in field, but the value may be overwritten)
};

/// The Ethernet DMA Descriptor structure. This is used to represent the DMA descriptors for the Ethernet DMA controller. The actual structure of the
/// descriptor is stored in system RAM and is defined by the STM32H7xx reference manual. This structure is used to manage the DMA descriptors in a
/// more C++ friendly way.
union Descriptor {
    struct TransmitRead final {
        // TDES0
        std::uintptr_t buffer1_address;    ///< The address of the buffer to transmit
        // TDES1
        std::uintptr_t buffer2_address;    ///< The address of the buffer to transmit
        // TDES2
        std::uint32_t buffer1_length                        : 14;    ///< The length of the buffer to transmit
        std::uint32_t vlan_tag_insertion_replacement        : 2;     ///< Whether to replace the VLAN tag in the frame
        std::uint32_t buffer2_length                        : 14;    ///< The length of the buffer to transmit
        std::uint32_t timestamp_enable                      : 1;     ///< Whether to enable transmit timestamping for this frame
        std::uint32_t interrupt_on_completion               : 1;     ///< Whether to generate an interrupt when this frame is transmitted
        // TDES3
        std::uint32_t                                       : 16;    // Reserved, this would be tcp_payload length if we supported that.
        ChecksumInsertionControl checksum_insertion_control : 2;     ///< Whether to control the checksum insertion for this frame
        std::uint32_t tcp_segmentation_control              : 1;     ///< Whether to control the TCP segmentation for this frame
        std::uint32_t total_header_length : 3;    ///< The length of the TCP header, if TCP segmentation is enabled for this frame (UDP => 2)
        SourceAddressInsertionControl source_address_insertion_control : 3;    ///< Whether to control the source address insertion for this frame
        CRCPadControl crc_pad_control                                  : 2;    ///< Whether to control the CRC and padding of the frame
        /// Whether this descriptor is the last descriptor of a frame (i.e. whether it contains the end of a frame to be transmitted)
        std::uint32_t last                                             : 1;
        /// Whether this descriptor is the first descriptor of a frame (i.e. whether it contains the start of a frame to be transmitted)
        std::uint32_t first                                            : 1;
        std::uint32_t context : 1;    ///< Whether this descriptor is a context descriptor (i.e. whether it contains context information for the next
                                      ///< frame to be transmitted)
        std::uint32_t own     : 1;    ///< Whether the DMA controller owns this descriptor (i.e. whether it is ready to be transmitted)
    } transmit_read;
#if defined(__arm__) || defined(__thumb__)
    static_assert(sizeof(TransmitRead) == 16UL, "TransmitRead descriptor must be exactly this size");
#endif
    struct TransmitWriteBack final {
        // TDES0 and 1
        uint64_t timestamp;    ///< The timestamp of when the frame was transmitted, if timestamping was enabled for this frame
        // TDES2
        std::uint32_t                        : 32;    // Reserved
        // TDES3
        std::uint32_t ip_header_error        : 1;    ///< Whether there was an IP header error in the frame that was transmitted
        std::uint32_t deferred               : 1;    ///< Whether the transmission of this frame was deferred due to the medium being busy
        std::uint32_t underflow              : 1;    ///< Whether there was an underflow error during the transmission of this frame
        std::uint32_t excessive_deferral     : 1;    ///< Whether there was an excessive deferral during the transmission of this frame
        std::uint32_t collision_count        : 4;    ///< The number of collisions that occurred during the transmission of this frame
        std::uint32_t excessive_collision    : 1;    ///< Whether there was an excessive collision during the transmission of this frame
        std::uint32_t late_collision         : 1;    ///< Whether there was a late collision during the transmission of this frame
        std::uint32_t no_carrier             : 1;    ///< Whether there was no carrier detected during the transmission of this frame
        std::uint32_t loss_carrier           : 1;    ///< Whether there was a carrier loss during the transmission of this frame
        /// Whether there was a payload checksum error in the frame that was transmitted (i.e. a TCP/UDP checksum error)
        std::uint32_t payload_checksum_error : 1;
        std::uint32_t packet_flushed         : 1;    ///< Whether the frame was flushed due to a flush command
        std::uint32_t jabber_timeout : 1;    ///< Whether there was a jabber timeout during the transmission of this frame (i.e. the frame took too
                                             ///< long to transmit, which could indicate a problem with the medium)
        /// Whether there was any error during the transmission of this frame (i.e. whether any of the above errors occurred)
        std::uint32_t error_summary  : 1;
        std::uint32_t                : 1;         // Reserved
        std::uint32_t timestamp_captured : 1;     ///< Whether a timestamp was captured for this frame (i.e. whether the timestamp field is valid)
        std::uint32_t                    : 10;    // Reserved
        /// Whether this descriptor is the last descriptor of a frame (i.e. whether it contains the end of a frame to be transmitted)
        std::uint32_t last               : 1;
        /// Whether this descriptor is the first descriptor of a frame (i.e. whether it contains the start of a frame to be transmitted)
        std::uint32_t first              : 1;
        std::uint32_t context : 1;    ///< Whether this descriptor is a context descriptor (i.e. whether it contains context information for the next
                                      ///< frame to be transmitted)
        std::uint32_t own     : 1;    ///< Whether the DMA controller owns this descriptor (i.e. whether it is ready to be transmitted)
    } transmit_write_back;
#if defined(__arm__) || defined(__thumb__)
    static_assert(sizeof(TransmitWriteBack) == 16UL, "TransmitWriteBack descriptor must be exactly this size");
#endif
    struct TransmitContext {
        // TDES0 and 1
        std::uint64_t timestamp;    ///< The timestamp to be used for the next frame to be transmitted, if timestamping is enabled for that frame
        // TDES2
        /// The maximum segment size for TCP segmentation offload, if TCP segmentation is enabled for the next frame to be transmitted
        std::uint32_t max_segment_size           : 14;
        std::uint32_t                            : 2;    // Reserved
        /// The inner VLAN tag to be inserted into the next frame to be transmitted, if VLAN tag insertion is enabled for that frame
        std::uint32_t inner_vlan_tag             : 16;
        // TDES3
        /// The VLAN tag to be inserted into the next frame to be transmitted, if VLAN tag insertion is enabled for that frame
        std::uint32_t vlan_tag                   : 16;
        std::uint32_t vlan_tag_valid             : 1;    ///< Whether the VLAN tag field contains a valid VLAN tag
        std::uint32_t inner_vlan_tag_valid       : 1;    ///< Whether the inner VLAN tag field contains a valid VLAN tag
        /// Whether to insert a VLAN tag or replace the existing VLAN tag for the next frame to be transmitted
        std::uint32_t insert_vlan_tag_or_replace : 2;
        std::uint32_t                            : 3;    ///< Whether to control the checksum insertion for the next frame to be transmitted
        std::uint32_t context_descriptor_error   : 1;    ///< Whether there was an error in this context descriptor (e.g. whether the DMA controller
                                                         ///< encountered an error while processing this context descriptor)
        std::uint32_t                            : 2;    // Reserved
        std::uint32_t one_time_timestamp_correction : 1;    ///< Whether to apply a one-time correction to the timestamp for the next frame to be
                                                            ///< transmitted, if timestamping is enabled for that frame
        std::uint32_t                               : 2;    // Reserved
        std::uint32_t context : 1;    ///< Whether this descriptor is a context descriptor (i.e. whether it contains context information for the next
                                      ///< frame to be transmitted)
        std::uint32_t own     : 1;    ///< Whether the DMA controller owns this descriptor (i.e. whether it is ready to be transmitted)
    } transmit_context;
#if defined(__arm__) || defined(__thumb__)
    static_assert(sizeof(TransmitContext) == 16UL, "TransmitContext descriptor must be exactly this size");
#endif

    struct ReceiveRead final {
        // RDES0
        std::uintptr_t buffer1_address;    ///< The address of the buffer to receive into
        // RDES1
        std::uint32_t : 32;    // Reserved
        // RDES2
        std::uintptr_t buffer2_address;    ///< The address of the buffer to receive into
        // RDES3
        std::uint32_t                         : 24;    // Reserved
        std::uint32_t buffer1_valid           : 1;     ///< Whether the first buffer contains valid data
        std::uint32_t buffer2_valid           : 1;     ///< Whether the second buffer contains valid data
        std::uint32_t                         : 4;     // Reserved
        std::uint32_t interrupt_on_completion : 1;     ///< Whether to generate an interrupt when a frame is received into this descriptor
        std::uint32_t own                     : 1;     ///< Whether the DMA controller owns this descriptor (i.e. whether it is ready to receive into)
    } receive_read;
#if defined(__arm__) || defined(__thumb__)
    static_assert(sizeof(ReceiveRead) == 16UL, "ReceiveRead descriptor must be exactly this size");
#endif
    struct ReceiveWriteBack final {
        // RDES0
        std::uint32_t outer_vlan_tag
            : 16;    ///< The outer VLAN tag of the received frame, if a VLAN tag was detected in the frame and the frame contained an outer VLAN tag
        std::uint32_t inner_vlan_tag
            : 16;    ///< The inner VLAN tag of the received frame, if a VLAN tag was detected in the frame and the frame contained an inner VLAN tag
        // RDES1
        std::uint32_t                                 : 16;    // Extended Status
        std::uint32_t mac_control_opcode              : 16;    ///< The MAC control opcode of the received frame, if a MAC control frame was received
        // RDES2
        std::uint32_t                                 : 10;    // Reserved
        /// If an ARP frame was received, whether the Ethernet controller did not generate an ARP reply for the frame
        std::uint32_t arp_reply_not_generated         : 1;
        std::uint32_t                                 : 4;    // Reserved
        std::uint32_t vlan_filter_status              : 1;    ///< Whether the received frame passed the VLAN filter
        std::uint32_t source_address_filter_fail      : 1;    ///< Whether the received frame failed the source address filter
        std::uint32_t destination_address_filter_fail : 1;    ///< Whether the received frame failed the destination address filter
        std::uint32_t hash_filter_status              : 1;    ///< Whether the received frame passed the hash filter
        std::uint32_t hash_or_mac_index : 1;    ///< Whether the hash filter or the MAC address index filter matched the received frame (i.e. whether
                                                ///< the hash index or the MAC address index field contains a valid index for this frame)
        std::uint32_t layer3_filter_match            : 1;    ///< Whether the received frame matched the layer 3 filter
        std::uint32_t layer4_filter_match            : 1;    ///< Whether the received frame matched the layer 4 filter
        /// The index of the layer 3 and layer 4 filters that matched the received frame, if any (0-7)
        std::uint32_t layer3_and_layer4_filter_index : 3;
        // RDES3
        std::uint32_t payload_checksum_error
            : 1;    ///< Whether there was a payload checksum error in the frame that was received (i.e. a TCP/UDP checksum error)
        std::uint32_t crc_error    : 1;    ///< Whether there was a CRC error in the frame that was received
        std::uint32_t length_error : 1;    ///< Whether there was a length error in the frame that was received (i.e. whether the length of the frame
                                           ///< did not match the length specified in the descriptor)
        std::uint32_t receive_watchdog_timeout : 1;    ///< Whether there was a receive watchdog timeout for this frame (i.e. whether the frame took
                                                       ///< too long to be received, which could indicate a problem with the medium)
        std::uint32_t late_collision           : 1;    ///< Whether there was a late collision during the reception of this frame
        std::uint32_t collision_count          : 4;    ///< The number of collisions that occurred during the reception of this frame
        std::uint32_t vlan_tag_detected        : 1;    ///< Whether a VLAN tag was detected in this frame
        std::uint32_t last                     : 1;    ///< Whether this descriptor contains the end of a received frame
        std::uint32_t first                    : 1;    ///< Whether this descriptor contains the start of a received frame
        std::uint32_t context : 1;    ///< Whether this descriptor is a context descriptor (i.e. whether it contains context information for the next
                                      ///< frame to be received)
        std::uint32_t own     : 1;    ///< Whether the DMA controller owns this descriptor (i.e. whether it is ready to be received into)
    };
#if defined(__arm__) || defined(__thumb__)
    static_assert(sizeof(ReceiveWriteBack) == 16UL, "Write descriptor must be exactly this size");
#endif
    uint32_t des[4];    ///< The raw 128 bits of the descriptor, which can be used for bulk operations or for initializing the descriptor to zero

    Descriptor()
        : des{0, 0, 0, 0} {}    ///< Default constructor initializes the descriptor to zero
};
#if defined(__arm__) || defined(__thumb__)
static_assert(sizeof(Descriptor) == 16UL, "Descriptor must be exactly this size");
#endif

}    // namespace dma

}    // namespace ethernet
}    // namespace stm32

#endif    // STM32_H7XX_ETHERNET_DRIVER_HPP

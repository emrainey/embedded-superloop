#ifndef STM32_H7XX_ETHERNET_DRIVER_HPP
#define STM32_H7XX_ETHERNET_DRIVER_HPP

/// @file
/// STM32H7xx Ethernet Driver Implementation

#include <array>
#include <core/Allocator.hpp>
#include <core/Array.hpp>
#include <core/Buffer.hpp>

#include "jarnax/Driver.hpp"
#include "jarnax/net/arp/Table.hpp"
#include "jarnax/net/configuration.hpp"
#include "jarnax/net/ethernet/Allocator.hpp"
#include "jarnax/net/ethernet/Driver.hpp"
#include "jarnax/net/ethernet/Frame.hpp"
#include "jarnax/net/ethernet/Phy.hpp"

namespace stm32 {
namespace ethernet {

/// @brief Allocates a new Ethernet frame from the provided allocator. The frame is constructed in place and returned to the caller. If the allocation
/// fails, nullptr is returned. The caller is responsible for deallocating the frame using DeallocateFrame when it is no longer needed.
jarnax::net::ethernet::Frame* AllocateFrame(core::Allocator& allocator);

/// @brief Deallocates an Ethernet frame that was previously allocated with AllocateFrame. The frame is destructed in place and the memory is returned
/// to the provided allocator. If the frame pointer is nullptr, the function does nothing.
void DeallocateFrame(core::Allocator& allocator, jarnax::net::ethernet::Frame* frame);

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
        std::uint32_t total_header_length : 4;    ///< The length of the TCP header, if TCP segmentation is enabled for this frame (UDP => 2)
        SourceAddressInsertionControl source_address_insertion_control : 2;    ///< Whether to control the source address insertion for this frame
        /// The source MAC address to use for this frame if source address insertion is enabled (0: MAC address 0, 1: MAC address 1)
        std::uint32_t mac_address_source                               : 1;
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
        /// (TCMSSV) Whether to apply the timestamp in this context descriptor as a one-time correction to the timestamp for the next
        /// frame to be transmitted, if timestamping is enabled for that frame (i.e. whether to use this timestamp as a reference for a
        /// one-time correction to the timestamp of the next frame, which can be used to correct for clock drift between the Ethernet
        /// controller and the actual time of transmission)
        std::uint32_t one_time_timestamp_correction_input_or_mss_valid : 1;
        std::uint32_t one_time_timestamp_correction : 1;    ///< (OSTC) Whether to apply a one-time correction to the timestamp for the next frame to
                                                            ///< be transmitted, if timestamping is enabled for that frame
        std::uint32_t                               : 2;    // Reserved
        std::uint32_t context : 1;    ///< (CTXT) Whether this descriptor is a context descriptor (i.e. whether it contains context information for
                                      ///< the next frame to be transmitted)
        std::uint32_t own     : 1;    ///< (OWN) Whether the DMA controller owns this descriptor (i.e. whether it is ready to be transmitted)
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
        /// The outer VLAN tag of the received frame, if a VLAN tag was detected in the frame and the frame contained an outer VLAN tag
        std::uint32_t outer_vlan_tag      : 16;
        /// The inner VLAN tag of the received frame, if a VLAN tag was detected in the frame and the frame contained an inner VLAN tag
        std::uint32_t inner_vlan_tag      : 16;
        // RDES1
        /// The payload type of the received frame (e.g. whether it is an IPv4 frame, an IPv6 frame, an ARP frame, etc.)
        std::uint32_t payload_type        : 3;
        std::uint32_t ip_header_error     : 1;    ///< Whether there was an IP header error in the frame that was received
        /// Whether an IPv4 header was present in the frame that was received (this is not necessarily mutually exclusive with the
        /// ip_header_error field, as there could be an IP header that is present but has an error)
        std::uint32_t ipv4_header_present : 1;
        /// Whether an IPv6 header was present in the frame that was received (this is not necessarily mutually exclusive with the
        /// ip_header_error field, as there could be an IP header that is present but has an error)
        std::uint32_t ipv6_header_present : 1;
        /// Whether the IP checksum was bypassed for this frame (i.e. whether the DMA controller did not check the IP checksum, which
        /// could indicate that the frame was received with an invalid IP checksum)
        std::uint32_t ip_checksum_bypass  : 1;
        std::uint32_t payload_error    : 1;    ///< Whether there was a payload error in the frame that was received (e.g. a TCP/UDP checksum error)
        std::uint32_t ptp_message_type : 4;    ///< If the received frame is a PTP frame, the message type of the PTP frame
        std::uint32_t ptp_packet_type : 1;    ///< Whether the received PTP frame is a two-step frame (i.e. whether it contains a follow-up message in
                                              ///< addition to the sync message)
        std::uint32_t ptp_version     : 1;    ///< If the received frame is a PTP frame, the version of the PTP protocol used in the frame
        std::uint32_t timestamp_available : 1;     ///< Whether a timestamp is available for this frame (i.e. whether the timestamp field is valid)
        std::uint32_t timestamp_dropped   : 1;     ///< Whether a timestamp was dropped for this frame (i.e. whether the DMA controller was unable to
                                                   ///< capture a timestamp for this frame)
        std::uint32_t mac_control_opcode  : 16;    ///< The MAC control opcode of the received frame, if a MAC control frame was received
        // RDES2
        std::uint32_t                     : 10;    // Reserved
        /// If an ARP frame was received, whether the Ethernet controller did not generate an ARP reply for the frame
        std::uint32_t arp_reply_not_generated         : 1;
        std::uint32_t                                 : 4;    // Reserved
        std::uint32_t vlan_filter_status              : 1;    ///< Whether the received frame passed the VLAN filter
        std::uint32_t source_address_filter_fail      : 1;    ///< Whether the received frame failed the source address filter
        std::uint32_t destination_address_filter_fail : 1;    ///< Whether the received frame failed the destination address filter
        std::uint32_t hash_filter_status              : 1;    ///< Whether the received frame passed the hash filter
        std::uint32_t hash_or_mac_index : 8;    ///< Whether the hash filter or the MAC address index filter matched the received frame (i.e. whether
                                                ///< the hash index or the MAC address index field contains a valid index for this frame)
        std::uint32_t layer3_filter_match            : 1;    ///< Whether the received frame matched the layer 3 filter
        std::uint32_t layer4_filter_match            : 1;    ///< Whether the received frame matched the layer 4 filter
        /// The index of the layer 3 and layer 4 filters that matched the received frame, if any (0-7)
        std::uint32_t layer3_and_layer4_filter_index : 3;
        // RDES3
        std::uint32_t packet_length                  : 15;    ///< The length of the received frame
        /// Whether there was any error during the reception of this frame (i.e. whether any of the above errors occurred)
        std::uint32_t error_summary                  : 1;
        std::uint32_t length_or_type    : 3;    ///< Whether the packet_length field contains the length of the received frame or the type of the
                                                ///< received frame (i.e. whether this is a short frame or a long frame)
        std::uint32_t dribble_bit_error : 1;    ///< Whether there was a dribble bit error in the frame that was received (i.e. whether there was an
                                                ///< extra bit at the end of the frame, which could indicate a problem with the medium)
        std::uint32_t receive_error : 1;    ///< Whether there was a receive error in the frame that was received (e.g. whether the frame was received
                                            ///< with an invalid CRC, which could indicate a problem with the medium)
        std::uint32_t overflow_error : 1;    ///< Whether there was an overflow error during the reception of this frame (i.e. whether the DMA
                                             ///< controller ran out of buffer space while receiving this frame, which could indicate a problem with
                                             ///< the medium or with the configuration of the DMA descriptors)
        std::uint32_t receive_watchdog_timeout : 1;    ///< Whether there was a receive watchdog timeout for this frame (i.e. whether the frame took
                                                       ///< too long to be received, which could indicate a problem with the medium)
        std::uint32_t giant_packet : 1;    ///< Whether the received frame was a giant packet (i.e. whether the length of the frame exceeded the
                                           ///< maximum frame size, which could indicate a
        std::uint32_t crc_error    : 1;    ///< Whether there was a CRC error in the frame that was received
        /// Whether the receive status in RDES0 is valid (i.e. whether the buffer1_valid and buffer2_valid fields are valid)
        std::uint32_t receive_status_des0_valid : 1;
        /// Whether the receive status in RDES1 is valid (i.e. whether the payload_type, error, and timestamp fields are valid)
        std::uint32_t receive_status_des1_valid : 1;
        /// Whether the receive status in RDES2 is valid (i.e. whether the fields in RDES2 are valid)
        std::uint32_t receive_status_des2_valid : 1;
        std::uint32_t last                      : 1;    ///< Whether this descriptor contains the end of a received frame
        std::uint32_t first                     : 1;    ///< Whether this descriptor contains the start of a received frame
        std::uint32_t context : 1;    ///< Whether this descriptor is a context descriptor (i.e. whether it contains context information for the next
                                      ///< frame to be received)
        std::uint32_t own     : 1;    ///< Whether the DMA controller owns this descriptor (i.e. whether it is ready to be received into)
    } receive_write_back;
#if defined(__arm__) || defined(__thumb__)
    static_assert(sizeof(ReceiveWriteBack) == 16UL, "Write descriptor must be exactly this size");
#endif
    uint32_t des[4];    ///< The raw 128 bits of the descriptor, which can be used for bulk operations or for initializing the descriptor to zero

    /// Default constructor initializes the descriptor to zero
    Descriptor()
        : des{0, 0, 0, 0} {}

    /// Clears the descriptor by setting all fields to zero
    void Clear() volatile {
        des[0] = 0;
        des[1] = 0;
        des[2] = 0;
        des[3] = 0;
    }
};
#if defined(__arm__) || defined(__thumb__)
static_assert(sizeof(Descriptor) == 16UL, "Descriptor must be exactly this size");
#endif

/// @brief A ring of DMA descriptors for the Ethernet controller. This is used to manage the DMA descriptors in a circular buffer, allowing for
/// efficient transmission and reception of Ethernet frames. The ring *may* get out of sync, so we don't use the core::Ring class, but instead manage
/// the indices ourselves.
template <std::size_t DescriptorCount>
class DescriptorRing {
public:
    /// @brief Constructor
    /// @param descriptors The array of descriptors to use for the ring
    DescriptorRing(core::Array<Descriptor volatile, DescriptorCount>& descriptors)
        : descriptors_(descriptors)
        , frames_{} {}    ///< Default constructor initializes the frames array to nullptr

    /// @brief Constructs the descriptor ring by initializing the descriptors and allocating frames for each descriptor. This should be called after
    /// the ring is constructed and before it is used. The frames are allocated using the provided allocator, and the
    /// descriptors are initialized to zero. The frames are stored in the frames_ array, which is used to keep track of the buffer addresses for each
    /// descriptor in the ring.
    bool Construct(core::Allocator& allocator) {
        for (std::size_t i = 0; i < descriptors_.count(); ++i) {
            descriptors_.data()[i].Clear();    // new descriptor is zeroed out
            frames_.data()[i] = nullptr;       // initialize frame pointer to nullptr
        }
        for (std::size_t i = 0; i < descriptors_.count(); ++i) {
            frames_.data()[i] = AllocateFrame(allocator);
            if (frames_.data()[i] == nullptr) {
                Destruct(allocator);    // clean up any previously allocated frames
                return false;
            }
        }
        return true;
    }

    /// @brief Destructs the descriptor ring by deallocating the frames and resetting the descriptors. This should be called when the ring is no
    /// longer needed. The frames are deallocated using the provided allocator, and the descriptors are reset to zero.
    void Destruct(core::Allocator& allocator) {
        for (std::size_t i = 0; i < descriptors_.count(); ++i) {
            DeallocateFrame(allocator, frames_.data()[i]);
            // The frame is already deallocated by DeallocateFrame, so just set the pointer to nullptr
            frames_.data()[i] = nullptr;
            descriptors_.data()[i].Clear();
        }
    }

    /// Get the base address of the descriptor ring, used for calculating the index of a descriptor and assigning the base address to the DMA
    /// controller
    Descriptor volatile* GetStart() const { return &descriptors_.data()[0]; }

    /// Get the exclusive end address of the descriptor ring, used for calculating the index of a descriptor and assigning the end address to the
    /// DMA controller
    Descriptor volatile* GetLimit() const { return &descriptors_.data()[descriptors_.count()]; }

    /// Passes the pointer to the current pointer in the ring and returns the index of that pointer in the ring. This is used to calculate the
    /// index of a descriptor in the ring.
    /// @param pointer A pointer to a descriptor in the ring
    /// @return The index of the descriptor in the ring, or -1 if the descriptor is not in the ring
    std::ptrdiff_t GetIndex(Descriptor volatile* pointer) const {
        std::ptrdiff_t index = pointer - GetStart();
        if (index < 0 || static_cast<std::size_t>(index) >= descriptors_.count()) {
            return -1;
        }
        return index;
    }

    /// Gets the descriptor at the given index in the ring. This is used to access a descriptor in the ring by its index.
    /// @param index The index of the descriptor in the ring
    /// @return A pointer to the descriptor at the given index, or nullptr if the index is out of bounds
    Descriptor volatile* GetDescriptor(std::size_t index) const {
        if (index >= descriptors_.count()) {
            return nullptr;
        }
        return &descriptors_.data()[index];
    }

    /// Gets the frame at the given index in the ring. This is used to access a frame in the ring by its index.
    /// @param index The index of the frame in the ring
    jarnax::net::ethernet::Frame* GetFrame(std::size_t index) const {
        if (index >= descriptors_.count()) {
            return nullptr;
        }
        return frames_.data()[index];
    }

    constexpr std::size_t Count() const { return descriptors_.count(); }    ///< Gets the number of descriptors in the ring

protected:
    /// The array of descriptors in the ring (note: this is must live in DMA memory!)
    core::Array<Descriptor volatile, DescriptorCount>& descriptors_;

    /// The array of buffer addresses for each descriptor in the ring (the descriptors will be cleared at some point, so we
    /// need to keep track of the buffer addresses separately)
    core::Array<jarnax::net::ethernet::Frame*, DescriptorCount> frames_;
};

}    // namespace dma

/// @brief STM32H7xx Ethernet peripheral driver implementation
/// @details Provides Ethernet communication for STM32H7xx microcontrollers.
/// Implements the jarnax::net::ethernet::Driver interface with STM32H7xx-specific hardware control and the Phy interface for controlling the Ethernet
/// PHY.
class Driver final : public jarnax::net::ethernet::Driver, public jarnax::net::ethernet::Phy, public jarnax::net::ethernet::Allocator {
public:
    /// @brief Total descriptors to allocate across RX/TX rings.
    constexpr static std::size_t RingDescriptorCount = 8U;
    /// @brief RX ring split ratio numerator (RX descriptors = total * numerator / denominator).
    constexpr static std::size_t ReceiveRingSplitNumerator = 1U;
    /// @brief RX ring split ratio denominator.
    constexpr static std::size_t ReceiveRingSplitDenominator = 2U;

    static_assert(ReceiveRingSplitDenominator > 0U, "Receive ring split denominator must be > 0");
    constexpr static std::size_t ReceiveDescriptorCount = (RingDescriptorCount * ReceiveRingSplitNumerator) / ReceiveRingSplitDenominator;
    constexpr static std::size_t TransmitDescriptorCount = RingDescriptorCount - ReceiveDescriptorCount;
    static_assert(ReceiveDescriptorCount > 0U, "Receive descriptor count must be > 0");
    static_assert(TransmitDescriptorCount > 0U, "Transmit descriptor count must be > 0");

    /// @brief Constructor
    /// @param stack_frame_allocator The allocator used for stack-owned Ethernet frame memory management
    /// @param dma_frame_allocator The allocator used for DMA-owned Ethernet ring frame storage
    /// @param transmit_descriptors Preallocated TX descriptor ring memory
    /// @param receive_descriptors Preallocated RX descriptor ring memory
    Driver(
        core::Allocator& stack_frame_allocator, core::Allocator& dma_frame_allocator,
        core::Array<dma::Descriptor volatile, TransmitDescriptorCount>& transmit_descriptors,
        core::Array<dma::Descriptor volatile, ReceiveDescriptorCount>& receive_descriptors
    );

    //+=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    // Jarnax::Driver Interface
    core::Status Initialize(void) override;
    bool Execute(void) override;
    //+=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    // jarnax::net::ethernet::Driver Interface
    core::Status Configure(Addresses const& addresses) override;
    jarnax::net::eui48::Address GetMacAddress(size_t index = 0) const override;
    core::Status Transmit(jarnax::net::ethernet::Frame* frame) override;
    core::Status Receive(Listener& listener) override;
    bool IsReady() const override;
    //+=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    // jarnax::net::ethernet::Phy Interface
    core::Status Schedule(jarnax::net::ethernet::mdio::Transaction* txn) override;
    core::Status ConfigureMacLink(bool speed_100m, bool full_duplex) override;
    //+=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    // jarnax::net::ethernet::Allocator Interface
    jarnax::net::ethernet::Frame* Acquire(void) override;
    void Release(jarnax::net::ethernet::Frame* frame) override;

    ~Driver();

protected:
    /// Released the Ring Allocated Descriptors and Frames, and resets the producer and consumer indices. This should be called on initialization
    /// failure to clean up any partial
    void ReleaseRings();

    core::Allocator& stack_frame_allocator_;    ///< Allocator used for stack-owned Ethernet frame memory management
    core::Allocator& dma_frame_allocator_;      ///< Allocator used for DMA-owned Ethernet ring frame storage
    dma::DescriptorRing<TransmitDescriptorCount> transmit_;
    dma::DescriptorRing<ReceiveDescriptorCount> receive_;
    std::size_t transmit_producer_index_{0U};
    std::size_t receive_consumer_index_{0U};
    jarnax::net::ethernet::mdio::Transaction* mdio_transaction_{nullptr};
    bool is_ready_;
};

}    // namespace ethernet
}    // namespace stm32

#endif    // STM32_H7XX_ETHERNET_DRIVER_HPP

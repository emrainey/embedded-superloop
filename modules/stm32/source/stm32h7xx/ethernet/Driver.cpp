#include "stm32/h7xx/ethernet/Driver.hpp"
#include "stm32/peripherals.hpp"

#include <new>

namespace {    // anonymous namespace for private helper functions and definitions

using jarnax::net::eui48::Address;

constexpr std::size_t kDmaSoftwareResetTimeout = 1000000U;
constexpr std::uint32_t kMdioAddressCommand = 0b00U;
constexpr std::uint32_t kMdioWriteCommand = 0b01U;
constexpr std::uint32_t kMdioReadCommand = 0b11U;

std::uint32_t PackAddressLow(Address const& address) {
    return static_cast<std::uint32_t>(address[0]) | (static_cast<std::uint32_t>(address[1]) << 8U) | (static_cast<std::uint32_t>(address[2]) << 16U) |
           (static_cast<std::uint32_t>(address[3]) << 24U);
}

std::uint16_t PackAddressHigh(Address const& address) {
    return static_cast<std::uint16_t>(static_cast<std::uint16_t>(address[4]) | (static_cast<std::uint16_t>(address[5]) << 8U));
}

Address UnpackAddress(std::uint32_t low, std::uint16_t high) {
    return Address{
        static_cast<std::uint8_t>((low >> 0U) & 0xFFU),
        static_cast<std::uint8_t>((low >> 8U) & 0xFFU),
        static_cast<std::uint8_t>((low >> 16U) & 0xFFU),
        static_cast<std::uint8_t>((low >> 24U) & 0xFFU),
        static_cast<std::uint8_t>((high >> 0U) & 0xFFU),
        static_cast<std::uint8_t>((high >> 8U) & 0xFFU)
    };
}

bool OwnBitCorrect() {
    stm32::ethernet::dma::Descriptor des;
    des.transmit_read.own = 1;
    bool read = (des.des[3] & (1U << 31)) != 0;
    des.des[3] = 0;    // Clear the word to avoid false positives from other bits
    des.receive_read.own = 1;
    bool write = (des.des[3] & (1U << 31)) != 0;
    des.des[3] = 0;    // Clear the word to avoid false positives from other bits
    des.transmit_write_back.own = 1;
    bool write_back = (des.des[3] & (1U << 31)) != 0;
    des.des[3] = 0;    // Clear the word to avoid false positives from other bits
    des.transmit_context.own = 1;
    bool context = (des.des[3] & (1U << 31)) != 0;
    des.des[3] = 0;    // Clear the word to avoid false positives from other bits
    des.receive_write_back.own = 1;
    bool receive_write_back = (des.des[3] & (1U << 31)) != 0;
    des.des[3] = 0;    // Clear the word
    return read && write && write_back && context && receive_write_back;
}

std::uint32_t DescriptorAddressRegisterValue(std::uintptr_t address) {
    return static_cast<std::uint32_t>(address & static_cast<std::uintptr_t>(0xFFFFFFFCU));
}

void CopyFrameBytes(jarnax::net::ethernet::Frame* destination, jarnax::net::ethernet::Frame const* source) {
    auto* destination_bytes = reinterpret_cast<std::uint8_t*>(destination);
    auto const* source_bytes = reinterpret_cast<std::uint8_t const*>(source);
    // TODO: Replace this byte loop with an optimized copy path once frame-length handling is wired.
    for (std::size_t i = 0; i < sizeof(jarnax::net::ethernet::Frame); ++i) {
        destination_bytes[i] = source_bytes[i];
    }
}

}    // anonymous namespace

namespace stm32 {
namespace ethernet {

jarnax::net::ethernet::Frame* AllocateFrame(core::Allocator& allocator) {
    void* memory = allocator.allocate(sizeof(jarnax::net::ethernet::Frame), alignof(jarnax::net::ethernet::Frame));
    if (memory == nullptr) {
        return nullptr;
    }
    return new (memory) jarnax::net::ethernet::Frame{};
}

void DeallocateFrame(core::Allocator& allocator, jarnax::net::ethernet::Frame* frame) {
    if (frame == nullptr) {
        return;
    }

    frame->~Frame();
    allocator.deallocate(frame, sizeof(jarnax::net::ethernet::Frame), alignof(jarnax::net::ethernet::Frame));
}

Driver::Driver(
    core::Allocator& stack_frame_allocator, core::Allocator& dma_frame_allocator,
    core::Array<dma::Descriptor volatile, TransmitDescriptorCount>& transmit_descriptors,
    core::Array<dma::Descriptor volatile, ReceiveDescriptorCount>& receive_descriptors
)
    : jarnax::net::ethernet::Driver()
    , jarnax::net::ethernet::Phy()
    , stack_frame_allocator_{stack_frame_allocator}
    , dma_frame_allocator_{dma_frame_allocator}
    , transmit_{transmit_descriptors}
    , receive_{receive_descriptors}
    , is_ready_{false} {}

Driver::~Driver() {
    ReleaseRings();
}

void Driver::ReleaseRings() {
    transmit_.Destruct(dma_frame_allocator_);
    receive_.Destruct(dma_frame_allocator_);
}

core::Status Driver::Initialize(void) {
    ReleaseRings();
    transmit_producer_index_ = 0U;
    receive_consumer_index_ = 0U;

    if (not OwnBitCorrect()) {
        return core::Status{core::Result::Failure, core::Cause::Configuration};
    }

    std::size_t timeout = kDmaSoftwareResetTimeout;
    while ((stm32::peripherals::ethernet_dma.mode.bits.software_reset != 0U) && (timeout > 0U)) {
        timeout--;
    }
    if (timeout == 0U) {
        return core::Status{core::Result::Timeout, core::Cause::Peripheral};
    }

    // Ethernet DMA is part of the ETH peripheral block; trigger its software reset and wait for completion.
    stm32::peripherals::EthernetDirectMemoryAccess::Mode dma_mode{stm32::peripherals::ethernet_dma.mode};    // load
    dma_mode.bits.software_reset = 1U;                                                                       // modify
    stm32::peripherals::ethernet_dma.mode = dma_mode;                                                        // store

    // reset the timeout
    timeout = kDmaSoftwareResetTimeout;
    while ((stm32::peripherals::ethernet_dma.mode.bits.software_reset != 0U) && (timeout > 0U)) {
        timeout--;
    }
    if (timeout == 0U) {
        return core::Status{core::Result::Timeout, core::Cause::Peripheral};
    }

    if (not transmit_.Construct(dma_frame_allocator_)) {
        return core::Status{core::Result::NotEnough, core::Cause::Resource};
    }
    if (not receive_.Construct(dma_frame_allocator_)) {
        ReleaseRings();
        return core::Status{core::Result::NotEnough, core::Cause::Resource};
    }

    for (std::size_t i = 0; i < transmit_.Count(); ++i) {
        auto descriptor = transmit_.GetDescriptor(i);
        descriptor->transmit_read.buffer1_address = reinterpret_cast<std::uintptr_t>(transmit_.GetFrame(i));
        descriptor->transmit_read.buffer2_address = 0U;
        descriptor->transmit_read.buffer1_length = 0U;
        descriptor->transmit_read.buffer2_length = 0U;
        descriptor->transmit_read.interrupt_on_completion = 1U;
        descriptor->transmit_read.checksum_insertion_control = dma::ChecksumInsertionControl::IP_Only;
        descriptor->transmit_read.crc_pad_control = dma::CRCPadControl::PadAndCRC;
        descriptor->transmit_read.first = 1U;
        descriptor->transmit_read.last = 1U;
        descriptor->transmit_read.own = 0U;
    }
    // SW owns all the tx descriptors at initialization, so the DMA will not process them until the client
    // fills them with frames to transmit and transfers the OWN bit to the DMA and updates the tail pointer register.

    for (std::size_t i = 0; i < receive_.Count(); ++i) {
        auto descriptor = receive_.GetDescriptor(i);
        descriptor->receive_read.buffer1_address = reinterpret_cast<std::uintptr_t>(receive_.GetFrame(i));
        descriptor->receive_read.buffer2_address = 0U;
        descriptor->receive_read.buffer1_valid = 1U;
        descriptor->receive_read.buffer2_valid = 0U;
        descriptor->receive_read.interrupt_on_completion = 1U;
        descriptor->receive_read.own = 1U;
    }
    // HW owns all the rx descriptors at initialization, so the DMA will process them as frames are received and transfer the OWN bit to SW when done.

    stm32::peripherals::EthernetDirectMemoryAccess::ChannelControl dma_channel_control;
    dma_channel_control = stm32::peripherals::ethernet_dma.channel_control;
    dma_channel_control.bits.descriptor_skip_length = 0U;
    stm32::peripherals::ethernet_dma.channel_control = dma_channel_control;

    stm32::peripherals::EthernetDirectMemoryAccess::ChannelReceiveControl dma_rx_control;
    dma_rx_control = stm32::peripherals::ethernet_dma.channel_receive_control;
    dma_rx_control.bits.receive_buffer_size = static_cast<std::uint32_t>(sizeof(jarnax::net::ethernet::Frame));
    dma_rx_control.bits.status = 0U;
    stm32::peripherals::ethernet_dma.channel_receive_control = dma_rx_control;

    stm32::peripherals::EthernetDirectMemoryAccess::ChannelTransmitDescriptorListAddress tx_descriptor_list_address;
    tx_descriptor_list_address.whole = DescriptorAddressRegisterValue(reinterpret_cast<std::uintptr_t>(transmit_.GetStart()));
    stm32::peripherals::ethernet_dma.channel_transmit_descriptor_list_address = tx_descriptor_list_address;

    stm32::peripherals::EthernetDirectMemoryAccess::ChannelReceiveDescriptorListAddress rx_descriptor_list_address;
    rx_descriptor_list_address.whole = DescriptorAddressRegisterValue(reinterpret_cast<std::uintptr_t>(receive_.GetStart()));
    stm32::peripherals::ethernet_dma.channel_receive_descriptor_list_address = rx_descriptor_list_address;

    stm32::peripherals::EthernetDirectMemoryAccess::ChannelTransmitDescriptorRingLength tx_ring_length;
    tx_ring_length = static_cast<std::uint32_t>(transmit_.Count() - 1U);
    stm32::peripherals::ethernet_dma.channel_transmit_descriptor_ring_length = tx_ring_length;

    stm32::peripherals::EthernetDirectMemoryAccess::ChannelReceiveDescriptorRingLength rx_ring_length;
    rx_ring_length = static_cast<std::uint32_t>(receive_.Count() - 1U);
    stm32::peripherals::ethernet_dma.channel_receive_descriptor_ring_length = rx_ring_length;

    // Set the tail to the head so that nothing is processed until the client has filled the ring with frames to transmit and receive.
    stm32::peripherals::EthernetDirectMemoryAccess::ChannelTransmitDescriptorTailPointer tx_tail_pointer;
    tx_tail_pointer.whole = DescriptorAddressRegisterValue(reinterpret_cast<std::uintptr_t>(transmit_.GetStart()));
    stm32::peripherals::ethernet_dma.channel_transmit_descriptor_tail_pointer = tx_tail_pointer;

    stm32::peripherals::EthernetDirectMemoryAccess::ChannelReceiveDescriptorTailPointer rx_tail_pointer;
    rx_tail_pointer.whole = DescriptorAddressRegisterValue(reinterpret_cast<std::uintptr_t>(receive_.GetLimit()));
    stm32::peripherals::ethernet_dma.channel_receive_descriptor_tail_pointer = rx_tail_pointer;

    stm32::peripherals::EthernetMediaTransactionLayer::TransmitQueueOperatingMode tx_queue;
    tx_queue = stm32::peripherals::ethernet_mtl.transmit_queue_operating_mode;
    tx_queue.bits.transmit_store_and_forward = 1U;
    tx_queue.bits.transmit_queue_enable = 0b10U;
    stm32::peripherals::ethernet_mtl.transmit_queue_operating_mode = tx_queue;

    stm32::peripherals::EthernetMediaTransactionLayer::ReceiveQueueOperatingMode rx_queue;
    rx_queue = stm32::peripherals::ethernet_mtl.receive_queue_operating_mode;
    rx_queue.bits.receive_store_and_forward = 1U;
    stm32::peripherals::ethernet_mtl.receive_queue_operating_mode = rx_queue;

    stm32::peripherals::EthernetMediaAccessController::OperatingModeConfiguration mac_mode;
    mac_mode = stm32::peripherals::ethernet_mac.operating_mode_configuration;
    // Enable hardware assist for network checksums and CRC handling.
    mac_mode.bits.ip_checksum_offload = 1U;
    mac_mode.bits.automatic_crc_stripping = 1U;
    mac_mode.bits.crc_stripping_for_type_packets = 1U;
    mac_mode.bits.transmitter_enable = 1U;
    mac_mode.bits.receiver_enable = 1U;
    stm32::peripherals::ethernet_mac.operating_mode_configuration = mac_mode;

    stm32::peripherals::EthernetMediaAccessController::PacketFilterControl packet_filter;
    packet_filter = stm32::peripherals::ethernet_mac.packet_filter_control;
    packet_filter.bits.promiscuous_mode = 1U;
    packet_filter.bits.receive_all = 1U;
    stm32::peripherals::ethernet_mac.packet_filter_control = packet_filter;

    stm32::peripherals::EthernetDirectMemoryAccess::ChannelTransmitControl dma_tx_control;
    dma_tx_control = stm32::peripherals::ethernet_dma.channel_transmit_control;
    dma_tx_control.bits.start = 1U;
    stm32::peripherals::ethernet_dma.channel_transmit_control = dma_tx_control;

    dma_rx_control = stm32::peripherals::ethernet_dma.channel_receive_control;
    dma_rx_control.bits.status = 1U;
    stm32::peripherals::ethernet_dma.channel_receive_control = dma_rx_control;

    // everything should be setup to run
    is_ready_ = true;

    return core::Status{};
}

bool Driver::IsReady() const {
    return is_ready_;
}

bool Driver::Execute(void) {
    if (mdio_transaction_ != nullptr) {
        if (mdio_transaction_->IsQueued()) {
            bool const is_clause22 = (mdio_transaction_->clause == jarnax::net::ethernet::mdio::Clause::_22);
            bool const is_clause45 = (mdio_transaction_->clause == jarnax::net::ethernet::mdio::Clause::_45);
            if (!is_clause22 && !is_clause45) {
                mdio_transaction_->Inform(
                    jarnax::net::ethernet::mdio::Transaction::Event::Completed, core::Status{core::Result::NotSupported, core::Cause::Configuration}
                );
                (void)mdio_transaction_->NotifyCompletionListener();
                mdio_transaction_ = nullptr;
                return true;
            }

            bool const is_op_address = (mdio_transaction_->operation == jarnax::net::ethernet::mdio::Operation::Address);
            bool const is_op_read = (mdio_transaction_->operation == jarnax::net::ethernet::mdio::Operation::Read);
            bool const is_op_write = (mdio_transaction_->operation == jarnax::net::ethernet::mdio::Operation::Write);

            if (!is_op_address && !is_op_read && !is_op_write) {
                mdio_transaction_->Inform(
                    jarnax::net::ethernet::mdio::Transaction::Event::Completed, core::Status{core::Result::NotSupported, core::Cause::Configuration}
                );
                (void)mdio_transaction_->NotifyCompletionListener();
                mdio_transaction_ = nullptr;
                return true;
            }

            if (is_clause22 && is_op_address) {
                mdio_transaction_->Inform(
                    jarnax::net::ethernet::mdio::Transaction::Event::Completed, core::Status{core::Result::NotSupported, core::Cause::Configuration}
                );
                (void)mdio_transaction_->NotifyCompletionListener();
                mdio_transaction_ = nullptr;
                return true;
            }

            if (stm32::peripherals::ethernet_mac.mdio_address.bits.management_busy != 0U) {
                mdio_transaction_->Inform(jarnax::net::ethernet::mdio::Transaction::Event::None);
                return true;
            }

            // Start the MAC MDIO transaction.
            stm32::peripherals::EthernetMediaAccessController::MdioData mdio_data;
            mdio_data = stm32::peripherals::ethernet_mac.mdio_data;
            if (is_clause45) {
                if (is_op_address) {
                    mdio_data.bits.register_address = static_cast<std::uint32_t>(mdio_transaction_->data);
                } else if (is_op_write) {
                    mdio_data.bits.mdio_data = static_cast<std::uint32_t>(mdio_transaction_->data);
                }
            } else if (is_op_write) {
                mdio_data.bits.mdio_data = static_cast<std::uint32_t>(mdio_transaction_->data);
            }
            stm32::peripherals::ethernet_mac.mdio_data = mdio_data;

            stm32::peripherals::EthernetMediaAccessController::MdioAddress mdio_address;
            mdio_address = stm32::peripherals::ethernet_mac.mdio_address;
            mdio_address.bits.clause45_phy_enable = is_clause45 ? 1U : 0U;
            mdio_address.bits.register_device_address = is_clause45 ? static_cast<std::uint32_t>(mdio_transaction_->device_address)
                                                                    : static_cast<std::uint32_t>(mdio_transaction_->register_address);
            mdio_address.bits.physical_address = static_cast<std::uint32_t>(mdio_transaction_->phy_address);
            if (is_op_address) {
                mdio_address.bits.mdio_operation_command = kMdioAddressCommand;
            } else if (is_op_read) {
                mdio_address.bits.mdio_operation_command = kMdioReadCommand;
            } else {
                mdio_address.bits.mdio_operation_command = kMdioWriteCommand;
            }
            // For clause 45 read/write operations, use a previously staged address transaction.
            mdio_address.bits.skip_address_packet = (is_clause45 && !is_op_address) ? 1U : 0U;
            mdio_address.bits.management_busy = 1U;
            stm32::peripherals::ethernet_mac.mdio_address = mdio_address;

            mdio_transaction_->Inform(jarnax::net::ethernet::mdio::Transaction::Event::Start);
        }

        if (mdio_transaction_ != nullptr && mdio_transaction_->IsRunning()) {
            if (stm32::peripherals::ethernet_mac.mdio_address.bits.management_busy != 0U) {
                mdio_transaction_->Inform(jarnax::net::ethernet::mdio::Transaction::Event::None);
                return true;
            }

            if (mdio_transaction_->operation == jarnax::net::ethernet::mdio::Operation::Read) {
                mdio_transaction_->data = static_cast<std::uint16_t>(stm32::peripherals::ethernet_mac.mdio_data.bits.mdio_data);
            }

            mdio_transaction_->Inform(
                jarnax::net::ethernet::mdio::Transaction::Event::Completed, core::Status{core::Result::Success, core::Cause::State}
            );
            (void)mdio_transaction_->NotifyCompletionListener();
            mdio_transaction_ = nullptr;
        }
    }

    return true;
}

core::Status Driver::Configure(Addresses const& addresses) {
    stm32::peripherals::EthernetMediaAccessController::Address0Low address0_low;
    address0_low.bits.address_low = PackAddressLow(addresses[0]);
    stm32::peripherals::ethernet_mac.address_0_low = address0_low;

    stm32::peripherals::EthernetMediaAccessController::Address0High address0_high;
    address0_high.bits.address_high = PackAddressHigh(addresses[0]);
    address0_high.bits.address_enable = 1U;
    stm32::peripherals::ethernet_mac.address_0_high = address0_high;

    stm32::peripherals::EthernetMediaAccessController::Address1Low address1_low;
    address1_low.bits.address_low = PackAddressLow(addresses[1]);
    stm32::peripherals::ethernet_mac.address_1_low = address1_low;

    stm32::peripherals::EthernetMediaAccessController::Address1High address1_high;
    address1_high.bits.address_high = PackAddressHigh(addresses[1]);
    address1_high.bits.mask_byte_control = 0U;
    address1_high.bits.source_address = 0U;
    address1_high.bits.address_enable = 1U;
    stm32::peripherals::ethernet_mac.address_1_high = address1_high;

    return core::Status{};
}

jarnax::net::eui48::Address Driver::GetMacAddress(size_t index) const {
    switch (index) {
        case 0: {
            return UnpackAddress(
                stm32::peripherals::ethernet_mac.address_0_low.bits.address_low,
                static_cast<std::uint16_t>(stm32::peripherals::ethernet_mac.address_0_high.bits.address_high)
            );
        }
        case 1: {
            return UnpackAddress(
                stm32::peripherals::ethernet_mac.address_1_low.bits.address_low,
                static_cast<std::uint16_t>(stm32::peripherals::ethernet_mac.address_1_high.bits.address_high)
            );
        }
        default:
            return jarnax::net::eui48::Address{};
    }
}

core::Status Driver::Transmit(jarnax::net::ethernet::Frame* frame) {
    if (frame == nullptr) {
        return core::Status{core::Result::InvalidValue, core::Cause::Parameter};
    }

    if (transmit_.GetFrame(transmit_producer_index_) == nullptr) {
        return core::Status{core::Result::NotInitialized, core::Cause::State};
    }

    auto descriptor = transmit_.GetDescriptor(transmit_producer_index_);
    if (descriptor->transmit_read.own == 1U) {
        // the DMA still owns this descriptor, so the ring is full and the client must wait for a slot to free up.
        return core::Status{core::Result::Busy, core::Cause::Resource};
    }

    // Copy client-owned frame into the next DMA-owned TX slot so descriptor order is independent of client Release timing.
    CopyFrameBytes(transmit_.GetFrame(transmit_producer_index_), frame);

    descriptor->transmit_read.buffer1_address = reinterpret_cast<std::uintptr_t>(transmit_.GetFrame(transmit_producer_index_));
    descriptor->transmit_read.buffer2_address = 0U;
    descriptor->transmit_read.buffer1_length = static_cast<unsigned int>(sizeof(jarnax::net::ethernet::Frame));
    descriptor->transmit_read.buffer2_length = 0U;
    descriptor->transmit_read.first = 1U;
    descriptor->transmit_read.last = 1U;
    descriptor->transmit_read.context = 0U;
    descriptor->transmit_read.interrupt_on_completion = 1U;
    descriptor->transmit_read.own = 1U;    // Transfer ownership to the DMA so it can process the descriptor.

    /// Modify the tail pointer register to point to the next descriptor in the ring, which will trigger the DMA to start processing the new
    /// descriptor.
    stm32::peripherals::EthernetDirectMemoryAccess::ChannelTransmitDescriptorTailPointer tx_tail_pointer;
    tx_tail_pointer.whole = DescriptorAddressRegisterValue(reinterpret_cast<std::uintptr_t>(descriptor));
    stm32::peripherals::ethernet_dma.channel_transmit_descriptor_tail_pointer = tx_tail_pointer;

    transmit_producer_index_ = (transmit_producer_index_ + 1U) % transmit_.Count();

    return core::Status{};
}

core::Status Driver::Receive(jarnax::net::ethernet::Driver::Listener& listener) {
    // The DMA fills RX descriptors in ring order, so the consumer index is the oldest unclaimed slot.
    // However, if the consumer index runs ahead of a parked frame (e.g. after a drop path re-armed and
    // advanced, or the ring wrapped), scan the whole ring for the first OWN=0 descriptor rather than
    // inspecting only the single slot at the consumer index. This guarantees a parked frame is never orphaned.
    for (std::size_t attempt = 0U; attempt < receive_.Count(); ++attempt) {
        std::size_t const index = (receive_consumer_index_ + attempt) % receive_.Count();

        if (receive_.GetFrame(index) == nullptr) {
            return core::Status{core::Result::NotInitialized, core::Cause::State};
        }

        auto descriptor = receive_.GetDescriptor(index);
        if (descriptor->receive_read.own == 1U) {
            // Still owned by the DMA: no frame ready at this slot, keep scanning for a ready slot.
            continue;
        }

        auto rearm_receive_descriptor = [this](dma::Descriptor volatile* d, std::size_t i) {
            d->receive_read.buffer1_address = reinterpret_cast<std::uintptr_t>(receive_.GetFrame(i));
            d->receive_read.buffer2_address = 0U;
            d->receive_read.buffer1_valid = 1U;
            d->receive_read.buffer2_valid = 0U;
            d->receive_read.interrupt_on_completion = 1U;
            d->receive_read.own = 1U;

            stm32::peripherals::EthernetDirectMemoryAccess::ChannelReceiveDescriptorTailPointer rx_tail_pointer;
            rx_tail_pointer.whole = DescriptorAddressRegisterValue(reinterpret_cast<std::uintptr_t>(d));
            stm32::peripherals::ethernet_dma.channel_receive_descriptor_tail_pointer = rx_tail_pointer;
        };

        bool const is_first = (descriptor->receive_write_back.first == 1U);
        bool const is_last = (descriptor->receive_write_back.last == 1U);
        // since the driver does not support multi-descriptor frames, any frame that is not both first and last is considered an error.
        if (((is_first == false) || (is_last == false)) && (descriptor->receive_write_back.error_summary == 1U)) {
            rearm_receive_descriptor(descriptor, index);
            receive_consumer_index_ = (index + 1U) % receive_.Count();
            return core::Status{core::Result::NotSupported, core::Cause::State};
        }

        // Copy from the DMA-owned RX ring buffer into a stack-owned frame so listener retention does not block the RX ring.
        jarnax::net::ethernet::Frame* stack_frame = Acquire();
        if (stack_frame == nullptr) {
            rearm_receive_descriptor(descriptor, index);
            receive_consumer_index_ = (index + 1U) % receive_.Count();
            return core::Status{core::Result::NotEnough, core::Cause::Resource};
        }

        CopyFrameBytes(stack_frame, receive_.GetFrame(index));

        rearm_receive_descriptor(descriptor, index);
        receive_consumer_index_ = (index + 1U) % receive_.Count();

        // pass to the interface to process, the driver is not involved in any "business" logic
        listener.OnFrameReceived(stack_frame);

        // now the driver has finished with the frame and it can be released back to the stack frame allocator
        Release(stack_frame);

        return core::Status{};
    }

    return core::Status{core::Result::NotReady, core::Cause::Resource};
}

core::Status Driver::Schedule(jarnax::net::ethernet::mdio::Transaction* transaction) {
    if (transaction == nullptr) {
        return core::Status{core::Result::InvalidValue, core::Cause::Parameter};
    }

    if (mdio_transaction_ != nullptr) {
        return core::Status{core::Result::Busy, core::Cause::Resource};
    }

    if (transaction->IsRunning()) {
        return core::Status{core::Result::NotReady, core::Cause::State};
    }

    if (!transaction->IsQueued()) {
        if (!transaction->Inform(jarnax::net::ethernet::mdio::Transaction::Event::Scheduled)) {
            return core::Status{core::Result::Failure, core::Cause::State};
        }
    }

    mdio_transaction_ = transaction;

    return core::Status{};
}

core::Status Driver::ConfigureMacLink(bool speed_100m, bool full_duplex) {
    auto mac_mode = stm32::peripherals::ethernet_mac.operating_mode_configuration;
    mac_mode.bits.fast_ethernet_speed = speed_100m ? 1U : 0U;
    mac_mode.bits.duplex_mode = full_duplex ? 1U : 0U;
    stm32::peripherals::ethernet_mac.operating_mode_configuration = mac_mode;
    return core::Status{};
}

jarnax::net::ethernet::Frame* Driver::Acquire(void) {
    return AllocateFrame(stack_frame_allocator_);
}

void Driver::Release(jarnax::net::ethernet::Frame* frame) {
    if (frame == nullptr) {
        return;
    }

    DeallocateFrame(stack_frame_allocator_, frame);
}

}    // namespace ethernet
}    // namespace stm32

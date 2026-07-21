#include "stm32/h7xx/ethernet/Driver.hpp"
#include "stm32/peripherals.hpp"

#include <new>

namespace {    // anonymous namespace for private helper functions and definitions

using jarnax::net::eui48::Address;

constexpr std::size_t kDmaSoftwareResetTimeout = 1000000U;
constexpr std::uint32_t kDescriptorOwnMask = (1UL << 31U);
constexpr std::uint32_t kDescriptorLastMask = (1UL << 28U);
constexpr std::uint32_t kDescriptorFirstMask = (1UL << 29U);
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

}    // anonymous namespace

namespace stm32 {
namespace ethernet {

Driver::Driver(
    core::Allocator& stack_frame_allocator, core::Allocator& dma_frame_allocator, core::Allocator& transmit_descriptor_allocator,
    core::Allocator& receive_descriptor_allocator
)
    : jarnax::net::ethernet::Driver()
    , jarnax::net::ethernet::Phy()
    , stack_frame_allocator_{stack_frame_allocator}
    , dma_frame_allocator_{dma_frame_allocator}
    , transmit_descriptor_allocator_{transmit_descriptor_allocator}
    , receive_descriptor_allocator_{receive_descriptor_allocator} {}

Driver::~Driver() {
    ReleaseRings();
}

void Driver::ReleaseRings() {
    for (auto& frame : transmit_ring_frames_) {
        if (frame != nullptr) {
            DeallocateFrame(dma_frame_allocator_, frame);
            frame = nullptr;
        }
    }
    for (auto& frame : receive_ring_frames_) {
        if (frame != nullptr) {
            DeallocateFrame(dma_frame_allocator_, frame);
            frame = nullptr;
        }
    }

    if (transmit_descriptors_ != nullptr) {
        transmit_descriptor_allocator_.deallocate(transmit_descriptors_, sizeof(dma::Descriptor) * TransmitDescriptorCount, alignof(dma::Descriptor));
        transmit_descriptors_ = nullptr;
    }
    if (receive_descriptors_ != nullptr) {
        receive_descriptor_allocator_.deallocate(receive_descriptors_, sizeof(dma::Descriptor) * ReceiveDescriptorCount, alignof(dma::Descriptor));
        receive_descriptors_ = nullptr;
    }
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

    transmit_descriptors_ = static_cast<dma::Descriptor*>(
        transmit_descriptor_allocator_.allocate(sizeof(dma::Descriptor) * TransmitDescriptorCount, alignof(dma::Descriptor))
    );
    if (transmit_descriptors_ == nullptr) {
        ReleaseRings();
        return core::Status{core::Result::NotEnough, core::Cause::Resource};
    }
    for (std::size_t i = 0; i < TransmitDescriptorCount; ++i) {
        new (&transmit_descriptors_[i]) dma::Descriptor{};
    }

    receive_descriptors_ = static_cast<dma::Descriptor*>(
        receive_descriptor_allocator_.allocate(sizeof(dma::Descriptor) * ReceiveDescriptorCount, alignof(dma::Descriptor))
    );
    if (receive_descriptors_ == nullptr) {
        ReleaseRings();
        return core::Status{core::Result::NotEnough, core::Cause::Resource};
    }
    for (std::size_t i = 0; i < ReceiveDescriptorCount; ++i) {
        new (&receive_descriptors_[i]) dma::Descriptor{};
    }

    for (std::size_t i = 0; i < TransmitDescriptorCount; ++i) {
        transmit_ring_frames_[i] = AllocateFrame(dma_frame_allocator_);
        if (transmit_ring_frames_[i] == nullptr) {
            ReleaseRings();
            return core::Status{core::Result::NotEnough, core::Cause::Resource};
        }

        dma::Descriptor& descriptor = transmit_descriptors_[i];
        descriptor.transmit_read.buffer1_address = reinterpret_cast<std::uintptr_t>(transmit_ring_frames_[i]);
        descriptor.transmit_read.buffer2_address = 0U;
        descriptor.transmit_read.buffer1_length = 0U;
        descriptor.transmit_read.buffer2_length = 0U;
        descriptor.transmit_read.interrupt_on_completion = 1U;
        descriptor.transmit_read.checksum_insertion_control = dma::ChecksumInsertionControl::IP_Only;
        descriptor.transmit_read.crc_pad_control = dma::CRCPadControl::PadAndCRC;
        descriptor.transmit_read.first = 1U;
        descriptor.transmit_read.last = 1U;
        descriptor.transmit_read.own = 0U;
    }

    for (std::size_t i = 0; i < ReceiveDescriptorCount; ++i) {
        receive_ring_frames_[i] = AllocateFrame(dma_frame_allocator_);
        if (receive_ring_frames_[i] == nullptr) {
            ReleaseRings();
            return core::Status{core::Result::NotEnough, core::Cause::Resource};
        }

        dma::Descriptor& descriptor = receive_descriptors_[i];
        descriptor.receive_read.buffer1_address = reinterpret_cast<std::uintptr_t>(receive_ring_frames_[i]);
        descriptor.receive_read.buffer2_address = 0U;
        descriptor.receive_read.buffer1_valid = 1U;
        descriptor.receive_read.buffer2_valid = 0U;
        descriptor.receive_read.interrupt_on_completion = 1U;
        descriptor.receive_read.own = 1U;
    }

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
    tx_descriptor_list_address.whole = DescriptorAddressRegisterValue(reinterpret_cast<std::uintptr_t>(transmit_descriptors_));
    stm32::peripherals::ethernet_dma.channel_transmit_descriptor_list_address = tx_descriptor_list_address;

    stm32::peripherals::EthernetDirectMemoryAccess::ChannelReceiveDescriptorListAddress rx_descriptor_list_address;
    rx_descriptor_list_address.whole = DescriptorAddressRegisterValue(reinterpret_cast<std::uintptr_t>(receive_descriptors_));
    stm32::peripherals::ethernet_dma.channel_receive_descriptor_list_address = rx_descriptor_list_address;

    stm32::peripherals::EthernetDirectMemoryAccess::ChannelTransmitDescriptorRingLength tx_ring_length;
    tx_ring_length.bits.transmit_descriptor_ring_length = static_cast<std::uint32_t>(TransmitDescriptorCount - 1U);
    stm32::peripherals::ethernet_dma.channel_transmit_descriptor_ring_length = tx_ring_length;

    stm32::peripherals::EthernetDirectMemoryAccess::ChannelReceiveDescriptorRingLength rx_ring_length;
    rx_ring_length.bits.receive_descriptor_ring_length = static_cast<std::uint32_t>(ReceiveDescriptorCount - 1U);
    stm32::peripherals::ethernet_dma.channel_receive_descriptor_ring_length = rx_ring_length;

    stm32::peripherals::EthernetDirectMemoryAccess::ChannelTransmitDescriptorTailPointer tx_tail_pointer;
    tx_tail_pointer.whole = DescriptorAddressRegisterValue(reinterpret_cast<std::uintptr_t>(&transmit_descriptors_[TransmitDescriptorCount - 1U]));
    stm32::peripherals::ethernet_dma.channel_transmit_descriptor_tail_pointer = tx_tail_pointer;

    stm32::peripherals::EthernetDirectMemoryAccess::ChannelReceiveDescriptorTailPointer rx_tail_pointer;
    rx_tail_pointer.whole = DescriptorAddressRegisterValue(reinterpret_cast<std::uintptr_t>(&receive_descriptors_[ReceiveDescriptorCount - 1U]));
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

    stm32::peripherals::EthernetDirectMemoryAccess::ChannelTransmitControl dma_tx_control;
    dma_tx_control = stm32::peripherals::ethernet_dma.channel_transmit_control;
    dma_tx_control.bits.start = 1U;
    stm32::peripherals::ethernet_dma.channel_transmit_control = dma_tx_control;

    dma_rx_control = stm32::peripherals::ethernet_dma.channel_receive_control;
    dma_rx_control.bits.status = 1U;
    stm32::peripherals::ethernet_dma.channel_receive_control = dma_rx_control;

    return core::Status{};
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
                mdio_transaction_ = nullptr;
                return true;
            }

            if (is_clause22 && is_op_address) {
                mdio_transaction_->Inform(
                    jarnax::net::ethernet::mdio::Transaction::Event::Completed, core::Status{core::Result::NotSupported, core::Cause::Configuration}
                );
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

core::Status Driver::Transmit(jarnax::net::ethernet::Frame const* frame) {
    if (frame == nullptr) {
        return core::Status{core::Result::InvalidValue, core::Cause::Parameter};
    }

    if ((transmit_descriptors_ == nullptr) || (transmit_ring_frames_[transmit_producer_index_] == nullptr)) {
        return core::Status{core::Result::NotInitialized, core::Cause::State};
    }

    dma::Descriptor& descriptor = transmit_descriptors_[transmit_producer_index_];
    if ((descriptor.des[3] & kDescriptorOwnMask) != 0U) {
        return core::Status{core::Result::Busy, core::Cause::Resource};
    }

    // Copy client-owned frame into the next DMA-owned TX slot so descriptor order is independent of client Release timing.
    CopyFrameBytes(transmit_ring_frames_[transmit_producer_index_], frame);

    descriptor.transmit_read.buffer1_address = reinterpret_cast<std::uintptr_t>(transmit_ring_frames_[transmit_producer_index_]);
    descriptor.transmit_read.buffer2_address = 0U;
    descriptor.transmit_read.buffer1_length = static_cast<unsigned int>(sizeof(jarnax::net::ethernet::Frame));
    descriptor.transmit_read.buffer2_length = 0U;
    descriptor.transmit_read.first = 1U;
    descriptor.transmit_read.last = 1U;
    descriptor.transmit_read.context = 0U;
    descriptor.transmit_read.interrupt_on_completion = 1U;
    descriptor.transmit_read.own = 1U;

    stm32::peripherals::EthernetDirectMemoryAccess::ChannelTransmitDescriptorTailPointer tx_tail_pointer;
    tx_tail_pointer.whole = DescriptorAddressRegisterValue(reinterpret_cast<std::uintptr_t>(&descriptor));
    stm32::peripherals::ethernet_dma.channel_transmit_descriptor_tail_pointer = tx_tail_pointer;

    transmit_producer_index_ = (transmit_producer_index_ + 1U) % TransmitDescriptorCount;

    return core::Status{};
}

core::Status Driver::Receive(jarnax::net::ethernet::Driver::Listener& listener) {
    if ((receive_descriptors_ == nullptr) || (receive_ring_frames_[receive_consumer_index_] == nullptr)) {
        return core::Status{core::Result::NotInitialized, core::Cause::State};
    }

    dma::Descriptor& descriptor = receive_descriptors_[receive_consumer_index_];
    if ((descriptor.des[3] & kDescriptorOwnMask) != 0U) {
        return core::Status{core::Result::NotReady, core::Cause::Resource};
    }

    auto rearm_receive_descriptor = [&descriptor, this]() {
        descriptor.receive_read.buffer1_address = reinterpret_cast<std::uintptr_t>(receive_ring_frames_[receive_consumer_index_]);
        descriptor.receive_read.buffer2_address = 0U;
        descriptor.receive_read.buffer1_valid = 1U;
        descriptor.receive_read.buffer2_valid = 0U;
        descriptor.receive_read.interrupt_on_completion = 1U;
        descriptor.receive_read.own = 1U;

        stm32::peripherals::EthernetDirectMemoryAccess::ChannelReceiveDescriptorTailPointer rx_tail_pointer;
        rx_tail_pointer.whole = DescriptorAddressRegisterValue(reinterpret_cast<std::uintptr_t>(&descriptor));
        stm32::peripherals::ethernet_dma.channel_receive_descriptor_tail_pointer = rx_tail_pointer;
    };

    std::uint32_t const descriptor_status = descriptor.des[3];
    if (((descriptor_status & kDescriptorFirstMask) == 0U) || ((descriptor_status & kDescriptorLastMask) == 0U)) {
        rearm_receive_descriptor();
        receive_consumer_index_ = (receive_consumer_index_ + 1U) % ReceiveDescriptorCount;
        return core::Status{core::Result::NotSupported, core::Cause::State};
    }

    // Copy from the DMA-owned RX ring buffer into a stack-owned frame so listener retention does not block the RX ring.
    jarnax::net::ethernet::Frame* stack_frame = Acquire();
    if (stack_frame == nullptr) {
        rearm_receive_descriptor();
        receive_consumer_index_ = (receive_consumer_index_ + 1U) % ReceiveDescriptorCount;
        return core::Status{core::Result::NotEnough, core::Cause::Resource};
    }

    CopyFrameBytes(stack_frame, receive_ring_frames_[receive_consumer_index_]);
    listener.OnFrameReceived(stack_frame);

    rearm_receive_descriptor();
    receive_consumer_index_ = (receive_consumer_index_ + 1U) % ReceiveDescriptorCount;

    return core::Status{};
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

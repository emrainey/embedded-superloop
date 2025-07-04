#include "board.hpp"
#include "jarnax/print.hpp"
#include "stm32/dma/Manager.hpp"

namespace stm32 {

dma::Manager* g_dma_instance = nullptr;

void dma1_stream0_isr() {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::DirectMemoryAccess1Stream0)]++;
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(0, 0);
    }
}
void dma1_stream1_isr() {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::DirectMemoryAccess1Stream1)]++;
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(0, 1);
    }
}
void dma1_stream2_isr() {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::DirectMemoryAccess1Stream2)]++;
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(0, 2);
    }
}
void dma1_stream3_isr() {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::DirectMemoryAccess1Stream3)]++;
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(0, 3);
    }
}
void dma1_stream4_isr() {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::DirectMemoryAccess1Stream4)]++;
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(0, 4);
    }
}
void dma1_stream5_isr() {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::DirectMemoryAccess1Stream5)]++;
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(0, 5);
    }
}
void dma1_stream6_isr() {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::DirectMemoryAccess1Stream6)]++;
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(0, 6);
    }
}
void dma1_stream7_isr() {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::DirectMemoryAccess1Stream7)]++;
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(0, 7);
    }
}

void dma2_stream0_isr() {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::DirectMemoryAccess2Stream0)]++;
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(1, 0);
    }
}
void dma2_stream1_isr() {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::DirectMemoryAccess2Stream1)]++;
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(1, 1);
    }
}
void dma2_stream2_isr() {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::DirectMemoryAccess2Stream2)]++;
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(1, 2);
    }
}
void dma2_stream3_isr() {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::DirectMemoryAccess2Stream3)]++;
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(1, 3);
    }
}
void dma2_stream4_isr() {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::DirectMemoryAccess2Stream4)]++;
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(1, 4);
    }
}
void dma2_stream5_isr() {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::DirectMemoryAccess2Stream5)]++;
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(1, 5);
    }
}
void dma2_stream6_isr() {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::DirectMemoryAccess2Stream6)]++;
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(1, 6);
    }
}
void dma2_stream7_isr() {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::DirectMemoryAccess2Stream7)]++;
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(1, 7);
    }
}

namespace dma {

Manager::Manager(stm32::registers::DirectMemoryAccess volatile (&dma)[stm32::registers::NumberOfDmaControllers])
    : dma_{dma}
    , used_{}
    , resources_{
          stm32::dma::Resource{0, 0},
          stm32::dma::Resource{0, 1},
          stm32::dma::Resource{0, 2},
          stm32::dma::Resource{0, 3},
          stm32::dma::Resource{0, 4},
          stm32::dma::Resource{0, 5},
          stm32::dma::Resource{0, 6},
          stm32::dma::Resource{0, 7},
          stm32::dma::Resource{1, 0},
          stm32::dma::Resource{1, 1},
          stm32::dma::Resource{1, 2},
          stm32::dma::Resource{1, 3},
          stm32::dma::Resource{1, 4},
          stm32::dma::Resource{1, 5},
          stm32::dma::Resource{1, 6},
          stm32::dma::Resource{1, 7}
      } {
    g_dma_instance = this;
}

jarnax::dma::Resource* Manager::Assign(Peripheral const& peripheral) {
    // this is called during Constructor-time. NONE of the peripherals are initialized or clocked yet, just assign pointer and leave
    for (size_t controller = 0U; controller < stm32::registers::NumberOfDmaControllers; controller++) {
        for (size_t index = 0U; index < NumStreamsPerController; index++) {
            size_t number = GetNumber(controller, index);
            if (number == DedicatedMemoryStream) {
                // this is dedicated to memory to memory transfers
                continue;
            }
            if (used_[number] == false) {
                for (size_t channel = 0U; channel < NumChannelsPerStream; channel++) {
                    if (peripheral == dma_endpoints[controller][index][channel]) {
                        used_[number] = true;
                        // assign the Channel!
                        if constexpr (jarnax::debug::dma) {
                            jarnax::print(
                                "Assigning DMA Stream: %u on controller: %u (%u) (will be channel %u)\n", index, controller, number, channel
                            );
                        }
                        return &resources_[number];
                    }
                }
            }
        }
    }
    return nullptr;
}

jarnax::dma::Resource* Manager::Acquire(size_t number, Peripheral const& peripheral) {
    // check to see if that index is used or not
    if (number <= NumStreams) {
        // is it already used?
        if (used_[number]) {
            return nullptr;    // already used, cannot acquire
        }
        used_[number] = true;
        size_t c{0U}, i{0U};
        dma::Manager::GetIndexes(number, c, i);
        if constexpr (jarnax::debug::dma) {
            jarnax::print("Acquiring DMA Stream: %u on controller: %u (%u)\n", i, c, number);
        }
        resources_[number].Initialize(peripheral);
        return &resources_[number];
    } else {
        return nullptr;
    }
}

core::Status Manager::Release(jarnax::dma::Resource*& resource) {
    // scan the DMA1 and DMA2 for the pointer to the stream and then set used_ to false
    for (size_t s = 0U; s < NumStreams; s++) {
        if (resource == &resources_[s]) {
            used_[s] = false;
            resource = nullptr;    // set the resource to nullptr
            return core::Status{};
        }
    }
    return core::Status{core::Result::InvalidValue, core::Cause::Parameter};
}

core::Status Manager::GetStreamStatus(size_t number, Flags& flags) {
    if (number >= NumStreams) {
        return core::Status{core::Result::InvalidValue, core::Cause::Parameter};
    }

    size_t controller{0U}, stream{0U};
    GetIndexes(number, controller, stream);
    auto low = stm32::registers::direct_memory_access[controller].low_interrupt_status;
    auto high = stm32::registers::direct_memory_access[controller].high_interrupt_status;

    switch (stream) {
        case 0:
            flags.fifo_error = low.bits.fifo_error_interrupt0;
            flags.direct_mode_error = low.bits.direct_mode_error_interrupt0;
            flags.error = low.bits.transfer_error_interrupt0;
            flags.half_complete = low.bits.half_transfer_interrupt0;
            flags.complete = low.bits.transfer_complete_interrupt0;
            break;
        case 1:
            flags.fifo_error = low.bits.fifo_error_interrupt1;
            flags.direct_mode_error = low.bits.direct_mode_error_interrupt1;
            flags.error = low.bits.transfer_error_interrupt1;
            flags.half_complete = low.bits.half_transfer_interrupt1;
            flags.complete = low.bits.transfer_complete_interrupt1;
            break;
        case 2:
            flags.fifo_error = low.bits.fifo_error_interrupt2;
            flags.direct_mode_error = low.bits.direct_mode_error_interrupt2;
            flags.error = low.bits.transfer_error_interrupt2;
            flags.half_complete = low.bits.half_transfer_interrupt2;
            flags.complete = low.bits.transfer_complete_interrupt2;
            break;
        case 3:
            flags.fifo_error = low.bits.fifo_error_interrupt3;
            flags.direct_mode_error = low.bits.direct_mode_error_interrupt3;
            flags.error = low.bits.transfer_error_interrupt3;
            flags.half_complete = low.bits.half_transfer_interrupt3;
            flags.complete = low.bits.transfer_complete_interrupt3;
            break;
        case 4:
            flags.fifo_error = high.bits.fifo_error_interrupt4;
            flags.direct_mode_error = high.bits.direct_mode_error_interrupt4;
            flags.error = high.bits.transfer_error_interrupt4;
            flags.half_complete = high.bits.half_transfer_interrupt4;
            flags.complete = high.bits.transfer_complete_interrupt4;
            break;
        case 5:
            flags.fifo_error = high.bits.fifo_error_interrupt5;
            flags.direct_mode_error = high.bits.direct_mode_error_interrupt5;
            flags.error = high.bits.transfer_error_interrupt5;
            flags.half_complete = high.bits.half_transfer_interrupt5;
            flags.complete = high.bits.transfer_complete_interrupt5;
            break;
        case 6:
            flags.fifo_error = high.bits.fifo_error_interrupt6;
            flags.direct_mode_error = high.bits.direct_mode_error_interrupt6;
            flags.error = high.bits.transfer_error_interrupt6;
            flags.half_complete = high.bits.half_transfer_interrupt6;
            flags.complete = high.bits.transfer_complete_interrupt6;
            break;
        case 7:
            flags.fifo_error = high.bits.fifo_error_interrupt7;
            flags.direct_mode_error = high.bits.direct_mode_error_interrupt7;
            flags.error = high.bits.transfer_error_interrupt7;
            flags.half_complete = high.bits.half_transfer_interrupt7;
            flags.complete = high.bits.transfer_complete_interrupt7;
            break;
    }
    return core::Status{};
}

std::size_t Manager::GetStreamNumber(stm32::registers::DirectMemoryAccess::Stream volatile& stream) {
    for (std::size_t c = 0U; c < stm32::registers::NumberOfDmaControllers; c++) {
        for (std::size_t i = 0U; i < NumStreamsPerController; i++) {
            if (&stream == &stm32::registers::direct_memory_access[c].streams[i]) {
                return dma::Manager::GetNumber(c, i);
            }
        }
    }
    return NumStreams;    // indicates not found
}

core::Status Manager::ClearStreamStatus(size_t number, Flags const& flags) {
    if (number >= NumStreams) {
        return core::Status{core::Result::InvalidValue, core::Cause::Parameter};
    }
    size_t controller{0U}, stream{0U};
    GetIndexes(number, controller, stream);
    auto low = stm32::registers::direct_memory_access[controller].low_interrupt_flag_clear;
    auto high = stm32::registers::direct_memory_access[controller].high_interrupt_flag_clear;

    switch (stream) {
        case 0:
            low.bits.clear_fifo_error_interrupt0 = flags.fifo_error;
            low.bits.clear_direct_mode_error_interrupt0 = flags.direct_mode_error;
            low.bits.clear_transfer_error_interrupt0 = flags.error;
            low.bits.clear_half_transfer_interrupt0 = flags.half_complete;
            low.bits.clear_transfer_complete_interrupt0 = flags.complete;
            stm32::registers::direct_memory_access[controller].low_interrupt_flag_clear = low;
            break;
        case 1:
            low.bits.clear_fifo_error_interrupt1 = flags.fifo_error;
            low.bits.clear_direct_mode_error_interrupt1 = flags.direct_mode_error;
            low.bits.clear_transfer_error_interrupt1 = flags.error;
            low.bits.clear_half_transfer_interrupt1 = flags.half_complete;
            low.bits.clear_transfer_complete_interrupt1 = flags.complete;
            stm32::registers::direct_memory_access[controller].low_interrupt_flag_clear = low;
            break;
        case 2:
            low.bits.clear_fifo_error_interrupt2 = flags.fifo_error;
            low.bits.clear_direct_mode_error_interrupt2 = flags.direct_mode_error;
            low.bits.clear_transfer_error_interrupt2 = flags.error;
            low.bits.clear_half_transfer_interrupt2 = flags.half_complete;
            low.bits.clear_transfer_complete_interrupt2 = flags.complete;
            stm32::registers::direct_memory_access[controller].low_interrupt_flag_clear = low;
            break;
        case 3:
            low.bits.clear_fifo_error_interrupt3 = flags.fifo_error;
            low.bits.clear_direct_mode_error_interrupt3 = flags.direct_mode_error;
            low.bits.clear_transfer_error_interrupt3 = flags.error;
            low.bits.clear_half_transfer_interrupt3 = flags.half_complete;
            low.bits.clear_transfer_complete_interrupt3 = flags.complete;
            stm32::registers::direct_memory_access[controller].low_interrupt_flag_clear = low;
            break;
        case 4:
            high.bits.clear_fifo_error_interrupt4 = flags.fifo_error;
            high.bits.clear_direct_mode_error_interrupt4 = flags.direct_mode_error;
            high.bits.clear_transfer_error_interrupt4 = flags.error;
            high.bits.clear_half_transfer_interrupt4 = flags.half_complete;
            high.bits.clear_transfer_complete_interrupt4 = flags.complete;
            stm32::registers::direct_memory_access[controller].high_interrupt_flag_clear = high;
            break;
        case 5:
            high.bits.clear_fifo_error_interrupt5 = flags.fifo_error;
            high.bits.clear_direct_mode_error_interrupt5 = flags.direct_mode_error;
            high.bits.clear_transfer_error_interrupt5 = flags.error;
            high.bits.clear_half_transfer_interrupt5 = flags.half_complete;
            high.bits.clear_transfer_complete_interrupt5 = flags.complete;
            stm32::registers::direct_memory_access[controller].high_interrupt_flag_clear = high;
            break;
        case 6:
            high.bits.clear_fifo_error_interrupt6 = flags.fifo_error;
            high.bits.clear_direct_mode_error_interrupt6 = flags.direct_mode_error;
            high.bits.clear_transfer_error_interrupt6 = flags.error;
            high.bits.clear_half_transfer_interrupt6 = flags.half_complete;
            high.bits.clear_transfer_complete_interrupt6 = flags.complete;
            stm32::registers::direct_memory_access[controller].high_interrupt_flag_clear = high;
            break;
        case 7:
            high.bits.clear_fifo_error_interrupt7 = flags.fifo_error;
            high.bits.clear_direct_mode_error_interrupt7 = flags.direct_mode_error;
            high.bits.clear_transfer_error_interrupt7 = flags.error;
            high.bits.clear_half_transfer_interrupt7 = flags.half_complete;
            high.bits.clear_transfer_complete_interrupt7 = flags.complete;
            stm32::registers::direct_memory_access[controller].high_interrupt_flag_clear = high;
            break;
    }
    return core::Status{};
}

void Manager::HandleInterrupt(uint32_t controller, uint32_t stream) {
    size_t number = dma::Manager::GetNumber(controller, stream);
    dma::Manager::Flags flags;
    auto status = GetStreamStatus(number, flags);
    if (status) {
        if constexpr (jarnax::debug::dma_isr) {
            jarnax::print(
                "DMA Interrupt: %" PRIu32 ", %" PRIu32 " status: c:%u h:%u e:%u dme:%u fe:%u\n",
                controller,
                stream,
                flags.complete,
                flags.half_complete,
                flags.error,
                flags.direct_mode_error,
                flags.fifo_error
            );
        }
        if (flags.complete) {
            resources_[number].Disable();
        }
        ClearStreamStatus(number, flags);
    }
}

core::Status Manager::Copy(
    std::uintptr_t destination,
    std::uintptr_t source,
    stm32::registers::DirectMemoryAccess::Stream::Configuration::DataSize data_size,
    std::size_t count
) {
    if (count > stm32::dma::Resource::MaximumMemoryCopyUnits) {
        return core::Status{core::Result::InvalidValue, core::Cause::Parameter};
    }
    // acquire a stream
    jarnax::dma::Resource* resource = Acquire(DedicatedMemoryStream, jarnax::_);
    if (resource) {
        using Direction = stm32::registers::DirectMemoryAccess::Stream::Configuration::DataTransferDirection;
        // ========================================
        stm32::registers::DirectMemoryAccess::Stream volatile& stream = resource->GetUnderlying();
        // ========================================
        stm32::registers::DirectMemoryAccess::Stream::FifoControl fifo_control = stream.fifo_control;            // read
        stm32::registers::DirectMemoryAccess::Stream::Configuration configuration = stream.configuration;        // read
        stm32::registers::DirectMemoryAccess::Stream::NumberOfDatum number_of_datum = stream.number_of_datum;    // read
        configuration.bits.stream_enable = 0;                                                                    // disable
        stream.configuration = configuration;                                                                    // write
        // ========================================
        // configure the stream
        fifo_control.bits.fifo_threshold = stm32::registers::DirectMemoryAccess::Stream::FifoControl::FifoThreshold::Empty;
        fifo_control.bits.fifo_error_interrupt_enable = 0;
        // memory to memory can't use Direct Mode
        fifo_control.bits.direct_mode_disable = 1U;
        stream.fifo_control = fifo_control;    // write
        // ========================================
        number_of_datum.bits.number_of_datum = static_cast<uint32_t>(count & 0xFFFFU);
        stream.number_of_datum = number_of_datum;    // write
        // ========================================
        // even though it's not a peripheral, we have to use this address
        stream.peripheral_address = reinterpret_cast<std::uintptr_t>(source);
        // ========================================
        stream.memory0_address = reinterpret_cast<std::uintptr_t>(destination);
        // ========================================
        // one shot
        configuration.bits.circular_mode = 0;
        // not a ping pong
        configuration.bits.double_buffer_mode = 0;
        configuration.bits.data_transfer_direction = Direction::MemoryToMemory;
        configuration.bits.memory_increment_mode = 1;    // increment after each element
        configuration.bits.memory_size = data_size;
        configuration.bits.memory_burst = stm32::registers::DirectMemoryAccess::Stream::Configuration::Burst::Increment4;
        configuration.bits.priority_level = stm32::registers::DirectMemoryAccess::Stream::Configuration::Priority::Low;
        configuration.bits.peripheral_flow_control = 0;               // DMA is flow controller
        configuration.bits.direct_mode_error_interrupt_enable = 0;    // Polling mode
        configuration.bits.transfer_error_interrupt_enable = 0;       // Polling mode
        configuration.bits.half_transfer_interrupt_enable = 0;        // Polling mode
        configuration.bits.transfer_complete_interrupt_enable = 0;    // Polling mode
        configuration.bits.stream_enable = 1;                         // enable
        stream.configuration = configuration;                         // write
        // ========================================
        // poll on completion (Use Stream 1 on Controller 1)
        while (stm32::registers::direct_memory_access[1].low_interrupt_status.bits.transfer_complete_interrupt1 == 0) {
        }
        // Clear the completion flag
        stm32::registers::direct_memory_access[1].low_interrupt_flag_clear.bits.clear_transfer_complete_interrupt1 = 1;
        // ========================================
        configuration = stream.configuration;    // read
        configuration.bits.stream_enable = 0;    // disable
        stream.configuration = configuration;    // write
        // ========================================
        // release the stream
        Release(resource);
        resource = nullptr;    // set the resource to nullptr
        return core::Status{};
    }
    return core::Status{core::Result::NotAvailable, core::Cause::Resource};
}

core::Status Manager::Copy(std::uint8_t destination[], std::uint8_t const source[], std::size_t count) {
    return Copy(
        reinterpret_cast<std::uintptr_t>(destination),
        reinterpret_cast<std::uintptr_t>(source),
        stm32::registers::DirectMemoryAccess::Stream::Configuration::DataSize::Bits8,
        count
    );
}

core::Status Manager::Copy(std::uint16_t destination[], std::uint16_t const source[], std::size_t count) {
    return Copy(
        reinterpret_cast<std::uintptr_t>(destination),
        reinterpret_cast<std::uintptr_t>(source),
        stm32::registers::DirectMemoryAccess::Stream::Configuration::DataSize::Bits16,
        count
    );
}

core::Status Manager::Copy(std::uint32_t destination[], std::uint32_t const source[], std::size_t count) {
    return Copy(
        reinterpret_cast<std::uintptr_t>(destination),
        reinterpret_cast<std::uintptr_t>(source),
        stm32::registers::DirectMemoryAccess::Stream::Configuration::DataSize::Bits32,
        count
    );
}

}    // namespace dma
}    // namespace stm32

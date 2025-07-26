#include "board.hpp"    // Board configuration Info
#include "jarnax/print.hpp"
#include "stm32/dma/Resource.hpp"
#include "stm32/dma/Manager.hpp"

namespace stm32 {
namespace dma {

Resource::Resource(size_t controller, size_t index)
    : stream_{stm32::registers::direct_memory_access[controller].streams[index]}
    , controller_index_{controller}
    , stream_index_{index}
    , stream_number_{dma::Manager::GetNumber(controller, index)} {
}

void Resource::Initialize(Peripheral const& peripheral) {
    stm32::registers::DirectMemoryAccess::Stream::Configuration configuration = stream_.configuration;    // read
    configuration.whole = 0U;                                                                             // clear the configuration
    stream_.configuration = configuration;                                                                // write back to clear everything
    // ========================================
    if (peripheral.sub == Peripheral::Sub::RX or peripheral.sub == Peripheral::Sub::IN) {
        configuration.bits.data_transfer_direction =
            stm32::registers::DirectMemoryAccess::Stream::Configuration::DataTransferDirection::PeripheralToMemory;
    } else if (peripheral.sub == Peripheral::Sub::TX or peripheral.sub == Peripheral::Sub::OUT) {
        configuration.bits.data_transfer_direction =
            stm32::registers::DirectMemoryAccess::Stream::Configuration::DataTransferDirection::MemoryToPeripheral;
    } else {
        // None, and other for now
        configuration.bits.data_transfer_direction =
            stm32::registers::DirectMemoryAccess::Stream::Configuration::DataTransferDirection::MemoryToMemory;
    }
    if (stream_number_ == stm32::dma::Manager::DedicatedMemoryStream) {
        configuration.bits.data_transfer_direction =
            stm32::registers::DirectMemoryAccess::Stream::Configuration::DataTransferDirection::MemoryToMemory;
    }
    size_t channel = stm32::dma::GetChannelFromStreamPeripheral(controller_index_, stream_index_, peripheral);
    if constexpr (jarnax::debug::dma) {
        jarnax::print("DMA Stream %u assigned to channel %" PRIz "\n", stream_number_, channel);
    }
    configuration.bits.channel_selection = (channel & 0x3U);    // mask to prevent overflow
    stream_.configuration = configuration;                      // write
    // ========================================
    stm32::registers::DirectMemoryAccess::Stream::FifoControl fifo_control = stream_.fifo_control;    // read
    fifo_control.whole = 0U;                                                                          // clear the FIFO control
    stream_.fifo_control = fifo_control;                                                              // write
    // ========================================
    stm32::dma::Manager::Flags flags;
    flags.all();                                                      // set all the flags
    stm32::dma::Manager::ClearStreamStatus(stream_number_, flags);    // clear the status flags
}

size_t Resource::GetIdentifier() const {
    return stream_number_;
}

core::Status Resource::ConfigureCopyToPeripheral(uintptr_t source, size_t count, size_t unit_size, uintptr_t destination) {
    if (count > stm32::dma::Resource::MaximumMemoryCopyUnits) {
        return core::Status{core::Result::InvalidValue, core::Cause::Parameter};
    }
    stm32::registers::DirectMemoryAccess::Stream::Configuration::DataSize data_size;
    if (unit_size == sizeof(uint8_t)) {
        data_size = stm32::registers::DirectMemoryAccess::Stream::Configuration::DataSize::Bits8;
    } else if (unit_size == sizeof(uint16_t)) {
        data_size = stm32::registers::DirectMemoryAccess::Stream::Configuration::DataSize::Bits16;
    } else if (unit_size == sizeof(uint32_t)) {
        data_size = stm32::registers::DirectMemoryAccess::Stream::Configuration::DataSize::Bits32;
    } else {
        return core::Status{core::Result::InvalidValue, core::Cause::Parameter};
    }

    // ========================================
    stm32::registers::DirectMemoryAccess::Stream::FifoControl fifo_control = stream_.fifo_control;            // read
    stm32::registers::DirectMemoryAccess::Stream::Configuration configuration = stream_.configuration;        // read
    stm32::registers::DirectMemoryAccess::Stream::NumberOfDatum number_of_datum = stream_.number_of_datum;    // read
    configuration.bits.circular_mode = 0;                                                                     // one shot
    configuration.bits.double_buffer_mode = 0;                                                                // not a ping pong
    configuration.bits.stream_enable = 0;                                                                     // disable
    stream_.configuration = configuration;                                                                    // write
    // ========================================
    // configure the stream
    fifo_control.bits.fifo_threshold = stm32::registers::DirectMemoryAccess::Stream::FifoControl::FifoThreshold::Empty;
    fifo_control.bits.fifo_error_interrupt_enable = 0;
    fifo_control.bits.direct_mode_disable = 0U;    // peripheral to memory
    stream_.fifo_control = fifo_control;           // write
    // ========================================
    number_of_datum.bits.number_of_datum = static_cast<uint32_t>(count & 0xFFFFU);
    stream_.number_of_datum = number_of_datum;    // write
    // ========================================
    stream_.peripheral_address = destination;    // peripheral address
    // ========================================
    stream_.memory0_address = source;    // memory address
    // ========================================
    configuration.bits.current_target = 0;               // use memory 0
    configuration.bits.peripheral_increment_mode = 0;    // do not increment the peripheral address
    configuration.bits.memory_increment_mode = 1;        // increment after each element
    configuration.bits.peripheral_data_size = data_size;
    configuration.bits.memory_size = data_size;
    configuration.bits.data_transfer_direction =
        stm32::registers::DirectMemoryAccess::Stream::Configuration::DataTransferDirection::MemoryToPeripheral;
    configuration.bits.memory_burst = stm32::registers::DirectMemoryAccess::Stream::Configuration::Burst::Single;
    configuration.bits.priority_level = stm32::registers::DirectMemoryAccess::Stream::Configuration::Priority::Medium;
    configuration.bits.peripheral_flow_control = 0;    // Peripheral is not flow controller, use the DMA NDTR, SDIO is only flow controller
    configuration.bits.direct_mode_error_interrupt_enable = 1;
    configuration.bits.transfer_error_interrupt_enable = 1;
    configuration.bits.half_transfer_interrupt_enable = 0;
    configuration.bits.transfer_complete_interrupt_enable = 1;
    stream_.configuration = configuration;    // write it out so we can see the settings
    if constexpr (jarnax::debug::dma) {
        jarnax::print("Configured Copy %p <= %p, %u elements\n", reinterpret_cast<void*>(destination), reinterpret_cast<void*>(source), count);
    }
    return core::Status{};
}

core::Status Resource::ConfigureCopyFromPeripheral(uintptr_t source, uintptr_t destination, size_t count, size_t unit_size) {
    if (count > stm32::dma::Resource::MaximumMemoryCopyUnits) {
        return core::Status{core::Result::InvalidValue, core::Cause::Parameter};
    }

    stm32::registers::DirectMemoryAccess::Stream::Configuration::DataSize data_size;
    if (unit_size == sizeof(uint8_t)) {
        data_size = stm32::registers::DirectMemoryAccess::Stream::Configuration::DataSize::Bits8;
    } else if (unit_size == sizeof(uint16_t)) {
        data_size = stm32::registers::DirectMemoryAccess::Stream::Configuration::DataSize::Bits16;
    } else if (unit_size == sizeof(uint32_t)) {
        data_size = stm32::registers::DirectMemoryAccess::Stream::Configuration::DataSize::Bits32;
    } else {
        return core::Status{core::Result::InvalidValue, core::Cause::Parameter};
    }

    // ========================================
    stm32::registers::DirectMemoryAccess::Stream::FifoControl fifo_control = stream_.fifo_control;        // read
    stm32::registers::DirectMemoryAccess::Stream::Configuration configuration = stream_.configuration;    // read
    configuration.bits.circular_mode = 0;                                                                 // one shot
    configuration.bits.stream_enable = 0;                                                                 // disable
    configuration.bits.double_buffer_mode = 0;                                                            // not a ping pong
    stream_.configuration = configuration;                                                                // write
    // ========================================
    // configure the stream
    fifo_control.bits.fifo_threshold = stm32::registers::DirectMemoryAccess::Stream::FifoControl::FifoThreshold::Empty;
    fifo_control.bits.fifo_error_interrupt_enable = 0;
    // peripheral to memory
    fifo_control.bits.direct_mode_disable = 0U;
    stream_.fifo_control = fifo_control;    // write
    // ========================================
    stream_.number_of_datum.bits.number_of_datum = static_cast<uint32_t>(count & 0xFFFFU);
    // ========================================
    stream_.peripheral_address = reinterpret_cast<std::uintptr_t>(source);
    // ========================================
    stream_.memory0_address = reinterpret_cast<std::uintptr_t>(destination);
    // ========================================
    configuration.bits.current_target = 0;               // use memory 0
    configuration.bits.peripheral_increment_mode = 0;    // do not increment the peripheral address
    configuration.bits.memory_increment_mode = 1;        // increment after each element
    configuration.bits.peripheral_data_size = data_size;
    configuration.bits.memory_size = data_size;
    configuration.bits.data_transfer_direction =
        stm32::registers::DirectMemoryAccess::Stream::Configuration::DataTransferDirection::PeripheralToMemory;
    configuration.bits.memory_burst = stm32::registers::DirectMemoryAccess::Stream::Configuration::Burst::Single;
    configuration.bits.priority_level = stm32::registers::DirectMemoryAccess::Stream::Configuration::Priority::Medium;
    configuration.bits.peripheral_flow_control = 0;    // Peripheral is flow controller
    configuration.bits.direct_mode_error_interrupt_enable = 1;
    configuration.bits.transfer_error_interrupt_enable = 1;
    configuration.bits.half_transfer_interrupt_enable = 0;
    configuration.bits.transfer_complete_interrupt_enable = 1;
    stream_.configuration = configuration;    // write it out so we can see the settings
    if constexpr (jarnax::debug::dma) {
        jarnax::print("Configured Copy %p => %p, %u elements\n", reinterpret_cast<void*>(source), reinterpret_cast<void*>(destination), count);
    }
    return core::Status{};
}

core::Status Resource::Enable() {
    // enable the stream
    stm32::registers::DirectMemoryAccess::Stream::Configuration configuration = stream_.configuration;    // read
    configuration.bits.stream_enable = 1;                                                                 // enable
    stream_.configuration = configuration;                                                                // write

    return core::Status{};
}

core::Status Resource::GetStatus(void) const {
    // get the status of the stream
    dma::Manager::Flags flags;
    stm32::dma::Manager::GetStreamStatus(stream_number_, flags);
    if constexpr (jarnax::debug::dma) {
        jarnax::print(
            "DMA Stream %u Status: Complete: %u, Half Complete: %u, Error: %u, Direct Mode Error: %u, FIFO Error: %u\n",
            stream_number_,
            flags.complete,
            flags.half_complete,
            flags.error,
            flags.direct_mode_error,
            flags.fifo_error
        );
    }
    stm32::dma::Manager::ClearStreamStatus(stream_number_, flags);
    if (flags.complete) {
        return core::Status{core::Result::Success, core::Cause::Peripheral};
    } else if (flags.error or flags.direct_mode_error or flags.fifo_error) {
        return core::Status{core::Result::Failure, core::Cause::Peripheral};
    } else {
        // half complete is not imporatnt to this implementation for now.
        return core::Status{core::Result::Busy, core::Cause::Peripheral};
    }
}

core::Status Resource::Disable() {
    // enable the stream
    stm32::registers::DirectMemoryAccess::Stream::Configuration configuration = stream_.configuration;    // read
    configuration.bits.stream_enable = 0;                                                                 // enable
    stream_.configuration = configuration;                                                                // write

    return core::Status{};
}

}    // namespace dma
}    // namespace stm32
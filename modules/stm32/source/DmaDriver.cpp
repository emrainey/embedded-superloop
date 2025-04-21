#include "board.hpp"
#include "jarnax/print.hpp"
#include "stm32/dma/Driver.hpp"

namespace stm32 {

dma::Driver* g_dma_instance = nullptr;

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

/// @brief Determine if the two peripherals are the same or if they are contained within each other.
/// @param lhs
/// @param rhs
/// @return
constexpr bool operator==(Peripheral const& lhs, Peripheral const& rhs) {
    // the type and instance must match, but the sub can be a subset or superset
    bool type_match = lhs.type == rhs.type;
    bool instance_match = lhs.instance == rhs.instance;
    bool sub_match = ((to_underlying(lhs.sub) & to_underlying(rhs.sub)) > 0U) or (to_underlying(lhs.sub) == 0U and to_underlying(rhs.sub) == 0U);
    return type_match and instance_match and sub_match;
}

constexpr Peripheral operator|(Peripheral const& lhs, Peripheral const& rhs) {
    return Peripheral{lhs.type, lhs.instance, static_cast<Peripheral::Sub>(to_underlying(lhs.sub) | to_underlying(rhs.sub))};
}

static_assert(ADC1 == ADC1, "Must be this value exactly");
static_assert((TIM8_CH1 | TIM8_CH2) == TIM8_CH1, "Must be this value exactly");
static_assert((TIM8_CH1 | TIM8_CH2 | TIM8_CH3) == TIM8_CH1, "Must be this value exactly");

/// @brief Per Table 43 in the reference manual.
constexpr static Peripheral dma_endpoints[stm32::registers::NumberOfDmaControllers][dma::Driver::NumStreamsPerController]
                                         [dma::Driver::NumChannelsPerStream] = {
                                             {{// Stream 0
                                               SPI3_RX,
                                               I2C1_RX,
                                               TIM4_CH1,
                                               I2S3_EXT_RX,
                                               UART5_RX,
                                               UART8_RX,
                                               TIM5_CH3 | TIM5_UP,
                                               _
                                              },
                                              {// Stream 1
                                               _,
                                               _,
                                               _,
                                               TIM2_UP | TIM2_CH3,
                                               USART3_RX,
                                               UART7_TX,
                                               TIM5_CH4 | TIM5_TRIG,
                                               TIM6_UP
                                              },
                                              {// Stream 2
                                               SPI3_RX,
                                               TIM7_UP,
                                               I2S3_EXT_RX,
                                               I2C3_RX,
                                               UART4_RX,
                                               TIM3_CH4,    // + TIM3_UP
                                               TIM5_CH1,
                                               I2C2_RX
                                              },
                                              {// Stream 3
                                               SPI2_RX,
                                               _,
                                               TIM4_CH2,
                                               I2S2_EXT_RX,
                                               USART3_TX,
                                               UART7_TX,
                                               TIM5_CH4,
                                               I2C2_RX
                                              },
                                              {// Stream 4
                                               SPI2_TX,
                                               TIM7_UP,
                                               I2S2_EXT_TX,
                                               I2C3_TX,
                                               UART4_TX,
                                               TIM3_CH1 | TIM3_TRIG,
                                               TIM5_CH2,
                                               USART3_TX
                                              },
                                              {// Stream 5
                                               SPI3_TX,
                                               I2C1_RX,
                                               I2S3_EXT_TX,
                                               TIM2_CH1,
                                               USART2_RX,
                                               TIM3_CH2,
                                               _,
                                               DAC1
                                              },
                                              {// Stream 6
                                               _,
                                               I2C1_TX,
                                               TIM4_UP,
                                               TIM2_CH2 | TIM2_CH4,
                                               USART2_TX,
                                               UART8_RX,
                                               TIM5_UP,
                                               DAC2
                                              },
                                              {// Stream 7
                                               SPI3_TX,
                                               I2C1_TX,
                                               TIM4_CH3,
                                               TIM2_UP | TIM2_CH4,
                                               UART5_TX,
                                               TIM3_CH3,
                                               _,
                                               I2C2_TX
                                              }},
                                             {{// Stream0/8,
                                               ADC1,
                                               _,
                                               ADC3,
                                               SPI1_RX,
                                               SPI4_RX,
                                               _,
                                               TIM1_TRIG,
                                               _
                                              },
                                              {// Stream1/9
                                               SAI1_A,
                                               DCMI,
                                               ADC3,
                                               _,
                                               SPI4_TX,
                                               USART6_TX,
                                               TIM1_CH1,
                                               TIM8_UP
                                              },
                                              {// Stream2/10
                                               TIM8_CH1 | TIM8_CH2 | TIM8_CH3,
                                               ADC2,
                                               _,
                                               SPI1_RX,
                                               USART1_RX,
                                               USART6_RX,
                                               TIM1_CH1,
                                               TIM8_UP
                                              },
                                              {/// Stream 3/11
                                               SAI1_A,
                                               ADC2,
                                               SPI5_RX,
                                               SPI1_TX,
                                               SDIO,
                                               SPI4_RX,
                                               TIM1_CH1,
                                               TIM1_CH2
                                              },
                                              {/// Stream 4/12
                                               ADC1,
                                               SAI1_B,
                                               SPI5_TX,
                                               _,
                                               _,
                                               SPI4_TX,
                                               TIM1_CH4 | TIM1_TRIG | TIM1_COM,
                                               TIM8_CH3
                                              },
                                              {/// Stream 5/13
                                               SAI1_B,
                                               SPI6_TX,
                                               CRYPTO_OUT,
                                               SPI1_TX,
                                               USART1_RX,
                                               _,
                                               TIM1_UP,
                                               SPI5_RX
                                              },
                                              {/// Stream 6/14
                                               TIM1_CH1 | TIM1_CH2 | TIM1_CH3,
                                               SPI6_RX,
                                               CRYPTO_IN,
                                               _,
                                               SDIO,
                                               USART6_TX,
                                               TIM1_CH3,
                                               SPI5_TX
                                              },
                                              {/// Stream 7/15
                                               _,
                                               DCMI,
                                               HASH_IN,
                                               _,
                                               USART1_TX,
                                               USART6_TX,
                                               _,
                                               TIM8_CH4 | TIM8_TRIG | TIM8_COM
                                              }}
};

constexpr std::size_t GetChannelFromStreamPeripheral(std::size_t number, Peripheral const& peripheral) {
    size_t controller{0U}, stream{0U};
    dma::Driver::GetIndexes(number, controller, stream);
    for (std::size_t channel = 0; channel < dma::Driver::NumChannelsPerStream; ++channel) {
        if (dma_endpoints[controller][stream][channel] == peripheral) {
            return channel;
        }
    }
    return dma::Driver::NumChannelsPerStream;    // indicates not found
}

// some simple tests for lookup
static_assert(GetChannelFromStreamPeripheral(0, SPI3_RX) == 0, "Must be this value exactly");
static_assert(GetChannelFromStreamPeripheral(5, TIM3_CH2) == 5, "Must be this value exactly");
static_assert(GetChannelFromStreamPeripheral(15, USART1_TX) == 4, "Must be this value exactly");
static_assert(GetChannelFromStreamPeripheral(15, TIM8_CH4) == 7, "Must be this value exactly");

Driver::Driver()
    : used_{} {
    g_dma_instance = this;
}

stm32::registers::DirectMemoryAccess::Stream volatile* Driver::Assign(Peripheral const& peripheral) {
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
                        jarnax::print("Assigning DMA Stream: %u on controller: %u (%u) (will be channel %u)\n", index, controller, number, channel);
                        return &stm32::registers::direct_memory_access[controller].streams[index];
                    }
                }
            }
        }
    }
    return nullptr;
}

void Driver::Initialize(stm32::registers::DirectMemoryAccess::Stream volatile& stream, size_t number, Peripheral const& peripheral) {
    stm32::registers::DirectMemoryAccess::Stream::Configuration configuration = stream.configuration;    // read
    configuration.whole = 0U;                                                                            // clear the configuration
    stream.configuration = configuration;                                                                // write back to clear everything
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
    if (number == DedicatedMemoryStream) {
        configuration.bits.data_transfer_direction =
            stm32::registers::DirectMemoryAccess::Stream::Configuration::DataTransferDirection::MemoryToMemory;
    }
    uint32_t channel = GetChannelFromStreamPeripheral(number, peripheral);
    jarnax::print("DMA Stream %u assigned to channel %lu\n", number, channel);
    configuration.bits.channel_selection = (channel & 0x3U);    // mask to prevent overflow
    stream.configuration = configuration;                       // write
    // ========================================
    stm32::registers::DirectMemoryAccess::Stream::FifoControl fifo_control = stream.fifo_control;    // read
    fifo_control.whole = 0U;                                                                         // clear the FIFO control
    stream.fifo_control = fifo_control;                                                              // write
    // ========================================
    dma::Driver::Flags flags;
    flags.all();                         // set all the flags
    ClearStreamStatus(number, flags);    // clear the status flags
}

core::Status Driver::Acquire(stm32::registers::DirectMemoryAccess::Stream volatile*& stream, size_t number, Peripheral const& peripheral) {
    // check to see if that index is used or not
    if (number <= NumStreams) {
        if (used_[number]) {
            return core::Status{core::Result::Busy, core::Cause::Resource};
        }
        used_[number] = true;
        size_t c{0U}, i{0U};
        GetIndexes(number, c, i);
        jarnax::print("Acquiring DMA Stream: %u on controller: %u (%u)\n", i, c, number);
        Initialize(stm32::registers::direct_memory_access[c].streams[i], number, peripheral);
        // assign the output stream
        stream = &stm32::registers::direct_memory_access[c].streams[i];
        return core::Status{};
    } else {
        return core::Status{core::Result::InvalidValue, core::Cause::Parameter};
    }
}

void Driver::Release(stm32::registers::DirectMemoryAccess::Stream volatile* stream) {
    // scan the DMA1 and DMA2 for the pointer to the stream and then set used_ to false
    for (size_t c = 0U; c < stm32::registers::NumberOfDmaControllers; c++) {
        for (size_t i = 0U; i < NumStreams; i++) {
            if (stream == &stm32::registers::direct_memory_access[c].streams[i]) {
                used_[i + (c * NumStreamsPerController)] = false;
                return;
            }
        }
    }
}

core::Status Driver::GetStreamStatus(size_t number, Flags& flags) {
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

std::size_t Driver::GetStreamIndex(stm32::registers::DirectMemoryAccess::Stream volatile& stream) const {
    for (std::size_t c = 0U; c < stm32::registers::NumberOfDmaControllers; c++) {
        for (std::size_t i = 0U; i < NumStreams; i++) {
            if (&stream == &stm32::registers::direct_memory_access[c].streams[i]) {
                return GetNumber(c, i);
            }
        }
    }
    return NumStreams;    // indicates not found
}

core::Status Driver::ClearStreamStatus(size_t number, Flags const& flags) {
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

void Driver::HandleInterrupt(uint32_t controller, uint32_t stream) {
    size_t number = dma::Driver::GetNumber(controller, stream);
    dma::Driver::Flags flags;
    auto status = GetStreamStatus(number, flags);
    if (status) {
        jarnax::print(
            "DMA Interrupt: %" PRIu32 ", %" PRIu32 " status: %u %u %u %u %u\n",
            controller,
            stream,
            flags.complete,
            flags.half_complete,
            flags.error,
            flags.direct_mode_error,
            flags.fifo_error
        );
        // clear the status, except the completions flags
        flags.complete = false;
        flags.half_complete = false;
        ClearStreamStatus(number, flags);
    }
}

core::Status Driver::Copy(
    std::uintptr_t destination,
    std::uintptr_t source,
    stm32::registers::DirectMemoryAccess::Stream::Configuration::DataSize data_size,
    std::size_t count
) {
    stm32::registers::DirectMemoryAccess::Stream volatile* stream{nullptr};
    if (count > MaximumMemoryCopyUnits) {
        return core::Status{core::Result::InvalidValue, core::Cause::Parameter};
    }
    // acquire a stream
    auto status = Acquire(stream, DedicatedMemoryStream);
    if (status and stream) {
        using Direction = stm32::registers::DirectMemoryAccess::Stream::Configuration::DataTransferDirection;
        // ========================================
        stm32::registers::DirectMemoryAccess::Stream::FifoControl fifo_control = stream->fifo_control;        // read
        stm32::registers::DirectMemoryAccess::Stream::Configuration configuration = stream->configuration;    // read
        configuration.bits.stream_enable = 0;                                                                 // disable
        stream->configuration = configuration;                                                                // write
        // ========================================
        // configure the stream
        fifo_control.bits.fifo_threshold = stm32::registers::DirectMemoryAccess::Stream::FifoControl::FifoThreshold::Empty;
        fifo_control.bits.fifo_error_interrupt_enable = 0;
        // memory to memory can't use Direct Mode
        fifo_control.bits.direct_mode_disable = 1U;
        stream->fifo_control = fifo_control;    // write
        // ========================================
        stream->number_of_datum.bits.number_of_datum = static_cast<uint32_t>(count & 0xFFFFU);
        // ========================================
        // even though it's not a peripheral, we have to use this address
        stream->peripheral_address = reinterpret_cast<std::uintptr_t>(source);
        // ========================================
        stream->memory0_address = reinterpret_cast<std::uintptr_t>(destination);
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
        stream->configuration = configuration;                        // write
        // ========================================
        // poll on completion (Use Stream 1 on Controller 1)
        while (stm32::registers::direct_memory_access[1].low_interrupt_status.bits.transfer_complete_interrupt1 == 0) {
        }
        // Clear the completion flag
        stm32::registers::direct_memory_access[1].low_interrupt_flag_clear.bits.clear_transfer_complete_interrupt1 = 1;
        // ========================================
        configuration = stream->configuration;    // read
        configuration.bits.stream_enable = 0;     // disable
        stream->configuration = configuration;    // write
        // ========================================
        // release the stream
        Release(stream);
        stream = nullptr;
        return core::Status{};
    }
    return core::Status{core::Result::NotAvailable, core::Cause::Resource};
}

core::Status Driver::Copy(std::uint8_t destination[], std::uint8_t const source[], std::size_t count) {
    return Copy(
        reinterpret_cast<std::uintptr_t>(destination),
        reinterpret_cast<std::uintptr_t>(source),
        stm32::registers::DirectMemoryAccess::Stream::Configuration::DataSize::Bits8,
        count
    );
}

core::Status Driver::Copy(std::uint16_t destination[], std::uint16_t const source[], std::size_t count) {
    return Copy(
        reinterpret_cast<std::uintptr_t>(destination),
        reinterpret_cast<std::uintptr_t>(source),
        stm32::registers::DirectMemoryAccess::Stream::Configuration::DataSize::Bits16,
        count
    );
}

core::Status Driver::Copy(std::uint32_t destination[], std::uint32_t const source[], std::size_t count) {
    return Copy(
        reinterpret_cast<std::uintptr_t>(destination),
        reinterpret_cast<std::uintptr_t>(source),
        stm32::registers::DirectMemoryAccess::Stream::Configuration::DataSize::Bits32,
        count
    );
}

template <>
core::Status Driver::CopyToPeripheral(
    stm32::registers::DirectMemoryAccess::Stream volatile& stream, uint32_t volatile* destination, uint8_t const source[], size_t count
) {
    return CopyToPeripheral(
        stream,
        reinterpret_cast<uintptr_t>(destination),
        reinterpret_cast<uintptr_t>(source),
        stm32::registers::DirectMemoryAccess::Stream::Configuration::DataSize::Bits8,
        count
    );
}

template <>
core::Status Driver::CopyToPeripheral(
    stm32::registers::DirectMemoryAccess::Stream volatile& stream, uint32_t volatile* destination, uint16_t const source[], size_t count
) {
    return CopyToPeripheral(
        stream,
        reinterpret_cast<uintptr_t>(destination),
        reinterpret_cast<uintptr_t>(source),
        stm32::registers::DirectMemoryAccess::Stream::Configuration::DataSize::Bits16,
        count
    );
}

template <>
core::Status Driver::CopyToPeripheral(
    stm32::registers::DirectMemoryAccess::Stream volatile& stream, uint32_t volatile* destination, uint32_t const source[], size_t count
) {
    return CopyToPeripheral(
        stream,
        reinterpret_cast<uintptr_t>(destination),
        reinterpret_cast<uintptr_t>(source),
        stm32::registers::DirectMemoryAccess::Stream::Configuration::DataSize::Bits32,
        count
    );
}

core::Status Driver::CopyToPeripheral(
    stm32::registers::DirectMemoryAccess::Stream volatile& stream,
    uintptr_t destination,
    uintptr_t source,
    stm32::registers::DirectMemoryAccess::Stream::Configuration::DataSize data_size,
    size_t count
) {
    if (count > MaximumMemoryCopyUnits) {
        return core::Status{core::Result::InvalidValue, core::Cause::Parameter};
    }
    // ========================================
    stm32::registers::DirectMemoryAccess::Stream::FifoControl fifo_control = stream.fifo_control;        // read
    stm32::registers::DirectMemoryAccess::Stream::Configuration configuration = stream.configuration;    // read
    configuration.bits.circular_mode = 0;                                                                // one shot
    configuration.bits.double_buffer_mode = 0;                                                           // not a ping pong
    configuration.bits.stream_enable = 0;                                                                // disable
    stream.configuration = configuration;                                                                // write
    // ========================================
    // configure the stream
    fifo_control.bits.fifo_threshold = stm32::registers::DirectMemoryAccess::Stream::FifoControl::FifoThreshold::Empty;
    fifo_control.bits.fifo_error_interrupt_enable = 0;
    fifo_control.bits.direct_mode_disable = 0U;    // peripheral to memory
    stream.fifo_control = fifo_control;            // write
    // ========================================
    stream.number_of_datum.bits.number_of_datum = static_cast<uint32_t>(count & 0xFFFFU);
    // ========================================
    stream.peripheral_address = reinterpret_cast<std::uintptr_t>(destination);    // peripheral address
    // ========================================
    stream.memory0_address = reinterpret_cast<std::uintptr_t>(source);    // memory address
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
    configuration.bits.transfer_complete_interrupt_enable = 0;
    stream.configuration = configuration;    // write it out so we can see the settings
    // ========================================
    configuration.bits.stream_enable = 1;    // enable
    stream.configuration = configuration;    // write

    return core::Status{};
}

template <>
core::Status Driver::CopyFromPeripheral(
    stm32::registers::DirectMemoryAccess::Stream volatile& stream, uint8_t destination[], uint32_t volatile const* source, size_t count
) {
    return CopyFromPeripheral(
        stream,
        reinterpret_cast<uintptr_t>(destination),
        reinterpret_cast<uintptr_t>(source),
        stm32::registers::DirectMemoryAccess::Stream::Configuration::DataSize::Bits8,
        count
    );
}

template <>
core::Status Driver::CopyFromPeripheral(
    stm32::registers::DirectMemoryAccess::Stream volatile& stream, uint16_t destination[], uint32_t volatile const* source, size_t count
) {
    return CopyFromPeripheral(
        stream,
        reinterpret_cast<uintptr_t>(destination),
        reinterpret_cast<uintptr_t>(source),
        stm32::registers::DirectMemoryAccess::Stream::Configuration::DataSize::Bits16,
        count
    );
}

template <>
core::Status Driver::CopyFromPeripheral(
    stm32::registers::DirectMemoryAccess::Stream volatile& stream, uint32_t destination[], uint32_t volatile const* source, size_t count
) {
    return CopyFromPeripheral(
        stream,
        reinterpret_cast<uintptr_t>(destination),
        reinterpret_cast<uintptr_t>(source),
        stm32::registers::DirectMemoryAccess::Stream::Configuration::DataSize::Bits32,
        count
    );
}

core::Status Driver::CopyFromPeripheral(
    stm32::registers::DirectMemoryAccess::Stream volatile& stream,
    uintptr_t destination,
    uintptr_t source,
    stm32::registers::DirectMemoryAccess::Stream::Configuration::DataSize data_size,
    size_t count
) {
    if (count > MaximumMemoryCopyUnits) {
        return core::Status{core::Result::InvalidValue, core::Cause::Parameter};
    }
    // ========================================
    stm32::registers::DirectMemoryAccess::Stream::FifoControl fifo_control = stream.fifo_control;        // read
    stm32::registers::DirectMemoryAccess::Stream::Configuration configuration = stream.configuration;    // read
    configuration.bits.circular_mode = 0;                                                                // one shot
    configuration.bits.stream_enable = 0;                                                                // disable
    configuration.bits.double_buffer_mode = 0;                                                           // not a ping pong
    stream.configuration = configuration;                                                                // write
    // ========================================
    // configure the stream
    fifo_control.bits.fifo_threshold = stm32::registers::DirectMemoryAccess::Stream::FifoControl::FifoThreshold::Empty;
    fifo_control.bits.fifo_error_interrupt_enable = 0;
    // peripheral to memory
    fifo_control.bits.direct_mode_disable = 0U;
    stream.fifo_control = fifo_control;    // write
    // ========================================
    stream.number_of_datum.bits.number_of_datum = static_cast<uint32_t>(count & 0xFFFFU);
    // ========================================
    stream.peripheral_address = reinterpret_cast<std::uintptr_t>(source);
    // ========================================
    stream.memory0_address = reinterpret_cast<std::uintptr_t>(destination);
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
    configuration.bits.transfer_complete_interrupt_enable = 0;
    stream.configuration = configuration;    // write it out so we can see the settings
    // ========================================
    configuration.bits.stream_enable = 1;    // enable
    stream.configuration = configuration;    // write

    return core::Status{};
}

}    // namespace dma
}    // namespace stm32

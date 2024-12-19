#include "stm32/dma/Driver.hpp"

namespace stm32 {

dma::Driver* g_dma_instance = nullptr;

void dma1_stream0_isr() {
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(0, 0);
    }
}
void dma1_stream1_isr() {
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(0, 1);
    }
}
void dma1_stream2_isr() {
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(0, 2);
    }
}
void dma1_stream3_isr() {
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(0, 3);
    }
}
void dma1_stream4_isr() {
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(0, 4);
    }
}
void dma1_stream5_isr() {
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(0, 5);
    }
}
void dma1_stream6_isr() {
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(0, 6);
    }
}
void dma1_stream7_isr() {
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(0, 7);
    }
}

void dma2_stream0_isr() {
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(1, 0);
    }
}
void dma2_stream1_isr() {
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(1, 1);
    }
}
void dma2_stream2_isr() {
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(1, 2);
    }
}
void dma2_stream3_isr() {
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(1, 3);
    }
}
void dma2_stream4_isr() {
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(1, 4);
    }
}
void dma2_stream5_isr() {
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(1, 5);
    }
}
void dma2_stream6_isr() {
    if (g_dma_instance) {
        g_dma_instance->HandleInterrupt(1, 6);
    }
}
void dma2_stream7_isr() {
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

constexpr size_t NumStreams = 8;
constexpr size_t NumChannels = 8;
/// @brief Per Table 43 in the reference manual.
constexpr static Peripheral dma1_endpoints[NumStreams][NumChannels] = {
    {// Stream 0
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
    }
};    // index by Stream first, then channel

/// @brief Per Table 44 in the reference manual.
constexpr static Peripheral dma2_peripherals[NumStreams][NumChannels] = {
    {// Stream0,
     ADC1,
     _,
     ADC3,
     SPI1_RX,
     SPI4_RX,
     _,
     TIM1_TRIG,
     _
    },
    {// Stream1
     SAI1_A,
     DCMI,
     ADC3,
     _,
     SPI4_TX,
     USART6_TX,
     TIM1_CH1,
     TIM8_UP
    },
    {// Stream2
     TIM8_CH1 | TIM8_CH2 | TIM8_CH3,
     ADC2,
     _,
     SPI1_RX,
     USART1_RX,
     USART6_RX,
     TIM1_CH1,
     TIM8_UP
    },
    {/// Stream 3
     SAI1_A,
     ADC2,
     SPI5_RX,
     SPI1_TX,
     SDIO,
     SPI4_RX,
     TIM1_CH1,
     TIM1_CH2
    },
    {/// Stream 4
     ADC1,
     SAI1_B,
     SPI5_TX,
     _,
     _,
     SPI4_TX,
     TIM1_CH4 | TIM1_TRIG | TIM1_COM,
     TIM8_CH3
    },
    {/// Stream 5
     SAI1_B,
     SPI6_TX,
     CRYPTO_OUT,
     SPI1_TX,
     USART1_RX,
     _,
     TIM1_UP,
     SPI5_RX
    },
    {/// Stream 6
     TIM1_CH1 | TIM1_CH2 | TIM1_CH3,
     SPI6_RX,
     CRYPTO_IN,
     _,
     SDIO,
     USART6_TX,
     TIM1_CH3,
     SPI5_TX
    },
    {/// Stream 7
     _,
     DCMI,
     HASH_IN,
     _,
     USART1_TX,
     USART6_TX,
     _,
     TIM8_CH4 | TIM8_TRIG | TIM8_COM
    }
};

constexpr std::size_t GetChannelFromStream(
    Peripheral const (&enpoints)[NumStreams][NumChannels], std::size_t stream_index, Peripheral const& peripheral
) {
    for (std::size_t i = 0; i < NumChannels; ++i) {
        if (enpoints[stream_index][i] == peripheral) {
            return i;
        }
    }
    return NumChannels;
}

// some simple tests for lookup
static_assert(GetChannelFromStream(dma1_endpoints, 0, SPI3_RX) == 0, "Must be this value exactly");
static_assert(GetChannelFromStream(dma1_endpoints, 5, TIM3_CH2) == 5, "Must be this value exactly");
static_assert(GetChannelFromStream(dma2_peripherals, 7, USART1_TX) == 4, "Must be this value exactly");
static_assert(GetChannelFromStream(dma2_peripherals, 7, TIM8_CH4) == 7, "Must be this value exactly");

Driver::Driver()
    : used_{} {
}

core::Status Driver::Acquire(stm32::registers::DirectMemoryAccess::Stream volatile*& channel, size_t number) {
    // check to see if that index is used or not
    if (number <= (NumStreams * stm32::registers::NumberOfDmaControllers)) {
        if (used_[number]) {
            return core::Status{core::Result::Busy, core::Cause::Resource};
        }
        used_[number] = true;
        size_t c = number / NumStreams;
        size_t i = number % NumStreams;
        channel = &stm32::registers::direct_memory_access[c].streams[i];
        return core::Status{};
    } else {
        return core::Status{core::Result::InvalidValue, core::Cause::Parameter};
    }
}

void Driver::Release(stm32::registers::DirectMemoryAccess::Stream volatile* channel) {
    // scan the DMA1 and DMA2 for the pointer to the stream and then set used_ to false
    for (size_t c = 0U; c < stm32::registers::NumberOfDmaControllers; c++) {
        for (size_t i = 0U; i < NumStreams; i++) {
            if (channel == &stm32::registers::direct_memory_access[c].streams[i]) {
                used_[i + (c * NumStreams)] = false;
                return;
            }
        }
    }
}

core::Status Driver::GetStreamStatus(size_t stream, Flags& flags) {
    if (stream >= (NumStreams * stm32::registers::NumberOfDmaControllers)) {
        return core::Status{core::Result::InvalidValue, core::Cause::Parameter};
    }

    size_t c = stream >= NumStreams ? 1 : 0;
    size_t i = stream >= NumStreams ? stream - NumStreams : stream;
    auto low = stm32::registers::direct_memory_access[c].low_interrupt_status;
    auto high = stm32::registers::direct_memory_access[c].high_interrupt_status;

    switch (i) {
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

core::Status Driver::ClearStreamStatus(size_t stream, Flags const& flags) {
    if (stream >= (NumStreams * stm32::registers::NumberOfDmaControllers)) {
        return core::Status{core::Result::InvalidValue, core::Cause::Parameter};
    }
    size_t c = stream >= NumStreams ? 1 : 0;
    size_t i = stream >= NumStreams ? stream - NumStreams : stream;
    auto low = stm32::registers::direct_memory_access[c].low_interrupt_flag_clear;
    auto high = stm32::registers::direct_memory_access[c].high_interrupt_flag_clear;

    switch (i) {
        case 0:
            low.bits.clear_fifo_error_interrupt0 = flags.fifo_error;
            low.bits.clear_direct_mode_error_interrupt0 = flags.direct_mode_error;
            low.bits.clear_transfer_error_interrupt0 = flags.error;
            low.bits.clear_half_transfer_interrupt0 = flags.half_complete;
            low.bits.clear_transfer_complete_interrupt0 = flags.complete;
            stm32::registers::direct_memory_access[c].low_interrupt_flag_clear = low;
            break;
        case 1:
            low.bits.clear_fifo_error_interrupt1 = flags.fifo_error;
            low.bits.clear_direct_mode_error_interrupt1 = flags.direct_mode_error;
            low.bits.clear_transfer_error_interrupt1 = flags.error;
            low.bits.clear_half_transfer_interrupt1 = flags.half_complete;
            low.bits.clear_transfer_complete_interrupt1 = flags.complete;
            stm32::registers::direct_memory_access[c].low_interrupt_flag_clear = low;
            break;
        case 2:
            low.bits.clear_fifo_error_interrupt2 = flags.fifo_error;
            low.bits.clear_direct_mode_error_interrupt2 = flags.direct_mode_error;
            low.bits.clear_transfer_error_interrupt2 = flags.error;
            low.bits.clear_half_transfer_interrupt2 = flags.half_complete;
            low.bits.clear_transfer_complete_interrupt2 = flags.complete;
            stm32::registers::direct_memory_access[c].low_interrupt_flag_clear = low;
            break;
        case 3:
            low.bits.clear_fifo_error_interrupt3 = flags.fifo_error;
            low.bits.clear_direct_mode_error_interrupt3 = flags.direct_mode_error;
            low.bits.clear_transfer_error_interrupt3 = flags.error;
            low.bits.clear_half_transfer_interrupt3 = flags.half_complete;
            low.bits.clear_transfer_complete_interrupt3 = flags.complete;
            stm32::registers::direct_memory_access[c].low_interrupt_flag_clear = low;
            break;
        case 4:
            high.bits.clear_fifo_error_interrupt4 = flags.fifo_error;
            high.bits.clear_direct_mode_error_interrupt4 = flags.direct_mode_error;
            high.bits.clear_transfer_error_interrupt4 = flags.error;
            high.bits.clear_half_transfer_interrupt4 = flags.half_complete;
            high.bits.clear_transfer_complete_interrupt4 = flags.complete;
            stm32::registers::direct_memory_access[c].high_interrupt_flag_clear = high;
            break;
        case 5:
            high.bits.clear_fifo_error_interrupt5 = flags.fifo_error;
            high.bits.clear_direct_mode_error_interrupt5 = flags.direct_mode_error;
            high.bits.clear_transfer_error_interrupt5 = flags.error;
            high.bits.clear_half_transfer_interrupt5 = flags.half_complete;
            high.bits.clear_transfer_complete_interrupt5 = flags.complete;
            stm32::registers::direct_memory_access[c].high_interrupt_flag_clear = high;
            break;
        case 6:
            high.bits.clear_fifo_error_interrupt6 = flags.fifo_error;
            high.bits.clear_direct_mode_error_interrupt6 = flags.direct_mode_error;
            high.bits.clear_transfer_error_interrupt6 = flags.error;
            high.bits.clear_half_transfer_interrupt6 = flags.half_complete;
            high.bits.clear_transfer_complete_interrupt6 = flags.complete;
            stm32::registers::direct_memory_access[c].high_interrupt_flag_clear = high;
            break;
        case 7:
            high.bits.clear_fifo_error_interrupt7 = flags.fifo_error;
            high.bits.clear_direct_mode_error_interrupt7 = flags.direct_mode_error;
            high.bits.clear_transfer_error_interrupt7 = flags.error;
            high.bits.clear_half_transfer_interrupt7 = flags.half_complete;
            high.bits.clear_transfer_complete_interrupt7 = flags.complete;
            stm32::registers::direct_memory_access[c].high_interrupt_flag_clear = high;
            break;
    }
    return core::Status{};
}

void Driver::HandleInterrupt(uint32_t controller, uint32_t stream) {
}

core::Status Driver::Copy(std::uint8_t* destination, std::uint8_t const* source, std::size_t count) {
    return core::Status{core::Result::NotImplemented, core::Cause::Configuration};
}

core::Status Driver::Copy(std::uint16_t* destination, std::uint16_t const* source, std::size_t count) {
    return core::Status{core::Result::NotImplemented, core::Cause::Configuration};
}

core::Status Driver::Copy(std::uint32_t* destination, std::uint32_t const* source, std::size_t count) {
    return core::Status{core::Result::NotImplemented, core::Cause::Configuration};
}

}    // namespace dma
}    // namespace stm32

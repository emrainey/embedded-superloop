#ifndef STM32_DMA_MANAGER_HPP
#define STM32_DMA_MANAGER_HPP

#include <jarnax/dma/Manager.hpp>
#include <jarnax/Copier.hpp>

#include "stm32/dma/Resource.hpp"

namespace stm32 {
namespace dma {

/// @brief The Manager class is used to manage DMA resources, allowing for assignment, acquisition, and release of resources.
class Manager final : public jarnax::dma::Manager, public jarnax::Copier {
public:
    ///< spread across DMA1 and DMA2
    static constexpr std::size_t NumStreams{16u};
    /// @brief The number of streams per controller
    static constexpr size_t NumStreamsPerController{8U};
    /// @brief The number of channels per stream
    static constexpr size_t NumChannelsPerStream{8U};
    /// only DMA2 can do memory to memory so the stream number must be >= 8
    static constexpr std::size_t DedicatedMemoryStream{9U};

    /// @brief The summary of the DMA stream's status.
    struct Flags {
        bool complete{false};
        bool half_complete{false};
        bool error{false};
        bool direct_mode_error{false};
        bool fifo_error{false};

        inline void all() {
            complete = true;
            half_complete = true;
            error = true;
            direct_mode_error = true;
            fifo_error = true;
        }
    };

    /// @brief Returns the stream index for the given stream.
    /// @param number The stream number to get the index for
    /// @param[out] controller The controller index of the stream
    /// @param[out] stream The stream index of the stream
    constexpr static void GetIndexes(size_t number, size_t& controller, size_t& stream) {
        controller = number >= NumStreamsPerController ? 1 : 0;
        stream = number >= NumStreamsPerController ? number - NumStreamsPerController : number;
    }

    /// @brief Returns the stream number for the given controller and stream index.
    /// @param controller The controller index of the stream
    /// @param stream The stream index of the stream
    /// @return The stream number, which is a combination of the controller and stream indices
    /// @note This method is used to convert the controller and stream indices into a single stream number.
    constexpr static size_t GetNumber(size_t controller, size_t stream) { return (controller * NumStreamsPerController) + stream; }

    /// @brief Returns the stream number for the given stream.
    /// @param stream The stream to get the number for
    /// @return The stream number, which is a combination of the controller and stream indices or NumStreams if the stream is invalid
    static std::size_t GetStreamNumber(stm32::registers::DirectMemoryAccess::Stream volatile& stream);

    /// @brief The default constructor
    Manager(stm32::registers::DirectMemoryAccess volatile (&dma)[stm32::registers::NumberOfDmaControllers]);

    /// @brief The destructor
    ~Manager() = default;

    //===[jarnax::dma::Manager]=============================================================================
    jarnax::dma::Resource* Assign(jarnax::Peripheral const& peripheral) override;
    jarnax::dma::Resource* Acquire(size_t index, jarnax::Peripheral const& peripheral = _) override;
    core::Status Release(jarnax::dma::Resource*& resource) override;

    //===[jarnax::Copier]===================================================================================
    core::Status Copy(std::uint8_t destination[], std::uint8_t const source[], std::size_t count) override;
    core::Status Copy(std::uint16_t destination[], std::uint16_t const source[], std::size_t count) override;
    core::Status Copy(std::uint32_t destination[], std::uint32_t const source[], std::size_t count) override;

    void HandleInterrupt(uint32_t controller, uint32_t stream);

    /// @brief Gets the status flags of the stream
    /// @param number The stream number to get the status flags for
    /// @param flags The flags to populate with the current status
    /// @return A core::Status indicating the result of the operation
    static core::Status GetStreamStatus(size_t number, Flags& flags);

    /// @brief Clears the status flags of the stream
    /// @param number The stream number to clear the status flags for
    /// @param flags The flags to clear
    /// @return A core::Status indicating the result of the operation
    /// @retval Result::Success if the status flags were cleared successfully
    /// @retval Result::InvalidValue if the stream number is invalid
    static core::Status ClearStreamStatus(size_t number, Flags const& flags);

protected:
    /// @brief The protected internal software copier interface
    /// @param destination The destination address to copy to
    /// @param source The source address to copy from
    /// @param data_size The data size to copy, which must be one of the DataSize enum values
    /// @param count The number of elements to copy, which must be less than or equal to 65535
    /// @return A core::Status indicating the result of the operation
    /// @retval Result::Success if the copy was successful
    /// @retval Result::InvalidValue if the parameters are invalid
    /// @retval Result::NotAvailable if the DMA controller is not available
    /// @note This method is used internally by the Copier interface to perform the actual copy operation.
    core::Status Copy(
        std::uintptr_t destination,
        std::uintptr_t source,
        stm32::registers::DirectMemoryAccess::Stream::Configuration::DataSize data_size,
        std::size_t count
    );

    /// @brief Gets the stream from the number
    /// @param number The stream number to get the stream for
    /// @return A pointer to the stream, or nullptr if the number is invalid
    stm32::registers::DirectMemoryAccess::Stream volatile* GetStreamFromNumber(size_t number);

    /// @brief The reference to the DMA controller registers
    stm32::registers::DirectMemoryAccess volatile (&dma_)[stm32::registers::NumberOfDmaControllers];

    /// @brief Tracks which streams are in use
    bool used_[NumStreams];

    /// @brief The resources for each stream in each DMA controller
    stm32::dma::Resource resources_[NumStreams];
};

/// @brief Per Table 43 in the reference manual.
// clang-format off
constexpr static jarnax::Peripheral dma_endpoints[stm32::registers::NumberOfDmaControllers][dma::Manager::NumStreamsPerController][dma::Manager::NumChannelsPerStream] = {
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
// clang-format on

constexpr std::size_t GetChannelFromStreamPeripheral(std::size_t controller, std::size_t stream, Peripheral const& peripheral) {
    for (std::size_t channel = 0; channel < dma::Manager::NumChannelsPerStream; ++channel) {
        if (dma_endpoints[controller][stream][channel] == peripheral) {
            return channel;
        }
    }
    return dma::Manager::NumChannelsPerStream;    // indicates not found
}

// some simple tests for lookup
static_assert(GetChannelFromStreamPeripheral(0, 0, SPI3_RX) == 0, "Must be this value exactly");
static_assert(GetChannelFromStreamPeripheral(0, 5, TIM3_CH2) == 5, "Must be this value exactly");
static_assert(GetChannelFromStreamPeripheral(1, 7, USART1_TX) == 4, "Must be this value exactly");
static_assert(GetChannelFromStreamPeripheral(1, 7, TIM8_CH4) == 7, "Must be this value exactly");

}    // namespace dma
}    // namespace stm32

#if not defined(UNITTEST)
namespace jarnax {
namespace dma {
using Manager = stm32::dma::Manager;
}    // namespace dma
}    // namespace jarnax
#endif

#endif    // STM32_DMA_MANAGER_HPP
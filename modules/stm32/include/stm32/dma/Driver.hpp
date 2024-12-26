#ifndef STM32_DMA_DRIVER_HPP
#define STM32_DMA_DRIVER_HPP

#include "polyfill.hpp"
#include "core/Status.hpp"
#include "jarnax/Copier.hpp"
#include "stm32/registers/DirectMemoryAccess.hpp"

namespace stm32 {
namespace dma {

/// @brief For the purposes of DMA we create a peripheral which enumerates it's type, instance and some sub-component information.
struct Peripheral {
    enum class Type : uint8_t {
        None,
        ADC,
        Crypto,
        DAC,
        DCMI,
        HASH,
        I2C,
        I2S_EXT,
        SAI,
        SDIO,
        SPI,
        TIMER,
        UART,
        USART,
    };
    enum class Sub : std::uint16_t {
        None = 0U,
        RX = (1U << 0U),
        TX = (1U << 1U),
        IN = (1U << 2U),
        OUT = (1U << 3U),
        CH1 = (1U << 4U),
        CH2 = (1U << 5U),
        CH3 = (1U << 6U),
        CH4 = (1U << 7U),
        TRIG = (1U << 8U),
        COM = (1U << 9U),
        UP = (1U << 10U),
        A = (1U << 11U),
        B = (1U << 12U),
    };
    Type type;
    uint8_t instance;
    Sub sub;    // a field of flags
};

constexpr static Peripheral _ = Peripheral{Peripheral::Type::None, 0, Peripheral::Sub::None};

constexpr static Peripheral ADC1 = Peripheral{Peripheral::Type::ADC, 1, Peripheral::Sub::None};
constexpr static Peripheral ADC2 = Peripheral{Peripheral::Type::ADC, 2, Peripheral::Sub::None};
constexpr static Peripheral ADC3 = Peripheral{Peripheral::Type::ADC, 3, Peripheral::Sub::None};
constexpr static Peripheral DAC1 = Peripheral{Peripheral::Type::DAC, 1, Peripheral::Sub::None};
constexpr static Peripheral DAC2 = Peripheral{Peripheral::Type::DAC, 2, Peripheral::Sub::None};
constexpr static Peripheral DCMI = Peripheral{Peripheral::Type::DCMI, 1, Peripheral::Sub::None};
constexpr static Peripheral CRYPTO_IN = Peripheral{Peripheral::Type::Crypto, 0, Peripheral::Sub::IN};
constexpr static Peripheral CRYPTO_OUT = Peripheral{Peripheral::Type::Crypto, 0, Peripheral::Sub::OUT};

constexpr static Peripheral HASH_IN = Peripheral{Peripheral::Type::HASH, 0, Peripheral::Sub::IN};
constexpr static Peripheral HASH_OUT = Peripheral{Peripheral::Type::HASH, 0, Peripheral::Sub::OUT};

constexpr static Peripheral I2C1_RX = Peripheral{Peripheral::Type::I2C, 1, Peripheral::Sub::RX};
constexpr static Peripheral I2C1_TX = Peripheral{Peripheral::Type::I2C, 1, Peripheral::Sub::TX};
constexpr static Peripheral I2C2_RX = Peripheral{Peripheral::Type::I2C, 2, Peripheral::Sub::RX};
constexpr static Peripheral I2C2_TX = Peripheral{Peripheral::Type::I2C, 2, Peripheral::Sub::TX};
constexpr static Peripheral I2C3_RX = Peripheral{Peripheral::Type::I2C, 3, Peripheral::Sub::RX};
constexpr static Peripheral I2C3_TX = Peripheral{Peripheral::Type::I2C, 3, Peripheral::Sub::TX};

constexpr static Peripheral I2S0_EXT_RX = Peripheral{Peripheral::Type::I2S_EXT, 0, Peripheral::Sub::RX};
constexpr static Peripheral I2S0_EXT_TX = Peripheral{Peripheral::Type::I2S_EXT, 0, Peripheral::Sub::TX};
constexpr static Peripheral I2S1_EXT_RX = Peripheral{Peripheral::Type::I2S_EXT, 1, Peripheral::Sub::RX};
constexpr static Peripheral I2S1_EXT_TX = Peripheral{Peripheral::Type::I2S_EXT, 1, Peripheral::Sub::TX};
constexpr static Peripheral I2S2_EXT_RX = Peripheral{Peripheral::Type::I2S_EXT, 2, Peripheral::Sub::RX};
constexpr static Peripheral I2S2_EXT_TX = Peripheral{Peripheral::Type::I2S_EXT, 2, Peripheral::Sub::TX};
constexpr static Peripheral I2S3_EXT_RX = Peripheral{Peripheral::Type::I2S_EXT, 3, Peripheral::Sub::RX};
constexpr static Peripheral I2S3_EXT_TX = Peripheral{Peripheral::Type::I2S_EXT, 3, Peripheral::Sub::TX};

constexpr static Peripheral SAI1_A = Peripheral{Peripheral::Type::SAI, 1, Peripheral::Sub::A};
constexpr static Peripheral SAI1_B = Peripheral{Peripheral::Type::SAI, 1, Peripheral::Sub::B};

constexpr static Peripheral SDIO = Peripheral{Peripheral::Type::SDIO, 0, Peripheral::Sub::None};

constexpr static Peripheral SPI1_RX = Peripheral{Peripheral::Type::SPI, 1, Peripheral::Sub::RX};
constexpr static Peripheral SPI1_TX = Peripheral{Peripheral::Type::SPI, 1, Peripheral::Sub::TX};
constexpr static Peripheral SPI2_RX = Peripheral{Peripheral::Type::SPI, 2, Peripheral::Sub::RX};
constexpr static Peripheral SPI2_TX = Peripheral{Peripheral::Type::SPI, 2, Peripheral::Sub::TX};
constexpr static Peripheral SPI3_RX = Peripheral{Peripheral::Type::SPI, 3, Peripheral::Sub::RX};
constexpr static Peripheral SPI3_TX = Peripheral{Peripheral::Type::SPI, 3, Peripheral::Sub::TX};
constexpr static Peripheral SPI4_RX = Peripheral{Peripheral::Type::SPI, 4, Peripheral::Sub::RX};
constexpr static Peripheral SPI4_TX = Peripheral{Peripheral::Type::SPI, 4, Peripheral::Sub::TX};
constexpr static Peripheral SPI5_RX = Peripheral{Peripheral::Type::SPI, 5, Peripheral::Sub::RX};
constexpr static Peripheral SPI5_TX = Peripheral{Peripheral::Type::SPI, 5, Peripheral::Sub::TX};
constexpr static Peripheral SPI6_RX = Peripheral{Peripheral::Type::SPI, 6, Peripheral::Sub::RX};
constexpr static Peripheral SPI6_TX = Peripheral{Peripheral::Type::SPI, 6, Peripheral::Sub::TX};

constexpr static Peripheral TIM1_CH1 = Peripheral{Peripheral::Type::TIMER, 1, Peripheral::Sub::CH1};
constexpr static Peripheral TIM1_CH2 = Peripheral{Peripheral::Type::TIMER, 1, Peripheral::Sub::CH2};
constexpr static Peripheral TIM1_CH3 = Peripheral{Peripheral::Type::TIMER, 1, Peripheral::Sub::CH3};
constexpr static Peripheral TIM1_CH4 = Peripheral{Peripheral::Type::TIMER, 1, Peripheral::Sub::CH4};
constexpr static Peripheral TIM1_TRIG = Peripheral{Peripheral::Type::TIMER, 1, Peripheral::Sub::TRIG};
constexpr static Peripheral TIM1_COM = Peripheral{Peripheral::Type::TIMER, 1, Peripheral::Sub::COM};
constexpr static Peripheral TIM1_UP = Peripheral{Peripheral::Type::TIMER, 1, Peripheral::Sub::UP};

constexpr static Peripheral TIM2_CH1 = Peripheral{Peripheral::Type::TIMER, 2, Peripheral::Sub::CH1};
constexpr static Peripheral TIM2_CH2 = Peripheral{Peripheral::Type::TIMER, 2, Peripheral::Sub::CH2};
constexpr static Peripheral TIM2_CH3 = Peripheral{Peripheral::Type::TIMER, 2, Peripheral::Sub::CH3};
constexpr static Peripheral TIM2_CH4 = Peripheral{Peripheral::Type::TIMER, 2, Peripheral::Sub::CH4};
constexpr static Peripheral TIM2_TRIG = Peripheral{Peripheral::Type::TIMER, 2, Peripheral::Sub::TRIG};
constexpr static Peripheral TIM2_COM = Peripheral{Peripheral::Type::TIMER, 2, Peripheral::Sub::COM};
constexpr static Peripheral TIM2_UP = Peripheral{Peripheral::Type::TIMER, 2, Peripheral::Sub::UP};

constexpr static Peripheral TIM3_CH1 = Peripheral{Peripheral::Type::TIMER, 3, Peripheral::Sub::CH1};
constexpr static Peripheral TIM3_CH2 = Peripheral{Peripheral::Type::TIMER, 3, Peripheral::Sub::CH2};
constexpr static Peripheral TIM3_CH3 = Peripheral{Peripheral::Type::TIMER, 3, Peripheral::Sub::CH3};
constexpr static Peripheral TIM3_CH4 = Peripheral{Peripheral::Type::TIMER, 3, Peripheral::Sub::CH4};
constexpr static Peripheral TIM3_TRIG = Peripheral{Peripheral::Type::TIMER, 3, Peripheral::Sub::TRIG};
constexpr static Peripheral TIM3_COM = Peripheral{Peripheral::Type::TIMER, 3, Peripheral::Sub::COM};
constexpr static Peripheral TIM3_UP = Peripheral{Peripheral::Type::TIMER, 3, Peripheral::Sub::UP};

constexpr static Peripheral TIM4_CH1 = Peripheral{Peripheral::Type::TIMER, 4, Peripheral::Sub::CH1};
constexpr static Peripheral TIM4_CH2 = Peripheral{Peripheral::Type::TIMER, 4, Peripheral::Sub::CH2};
constexpr static Peripheral TIM4_CH3 = Peripheral{Peripheral::Type::TIMER, 4, Peripheral::Sub::CH3};
constexpr static Peripheral TIM4_CH4 = Peripheral{Peripheral::Type::TIMER, 4, Peripheral::Sub::CH4};
constexpr static Peripheral TIM4_TRIG = Peripheral{Peripheral::Type::TIMER, 4, Peripheral::Sub::TRIG};
constexpr static Peripheral TIM4_COM = Peripheral{Peripheral::Type::TIMER, 4, Peripheral::Sub::COM};
constexpr static Peripheral TIM4_UP = Peripheral{Peripheral::Type::TIMER, 4, Peripheral::Sub::UP};

constexpr static Peripheral TIM5_CH1 = Peripheral{Peripheral::Type::TIMER, 5, Peripheral::Sub::CH1};
constexpr static Peripheral TIM5_CH2 = Peripheral{Peripheral::Type::TIMER, 5, Peripheral::Sub::CH2};
constexpr static Peripheral TIM5_CH3 = Peripheral{Peripheral::Type::TIMER, 5, Peripheral::Sub::CH3};
constexpr static Peripheral TIM5_CH4 = Peripheral{Peripheral::Type::TIMER, 5, Peripheral::Sub::CH4};
constexpr static Peripheral TIM5_TRIG = Peripheral{Peripheral::Type::TIMER, 5, Peripheral::Sub::TRIG};
constexpr static Peripheral TIM5_COM = Peripheral{Peripheral::Type::TIMER, 5, Peripheral::Sub::COM};
constexpr static Peripheral TIM5_UP = Peripheral{Peripheral::Type::TIMER, 5, Peripheral::Sub::UP};

constexpr static Peripheral TIM6_UP = Peripheral{Peripheral::Type::TIMER, 6, Peripheral::Sub::UP};

constexpr static Peripheral TIM7_UP = Peripheral{Peripheral::Type::TIMER, 7, Peripheral::Sub::UP};

constexpr static Peripheral TIM8_CH1 = Peripheral{Peripheral::Type::TIMER, 8, Peripheral::Sub::CH1};
constexpr static Peripheral TIM8_CH2 = Peripheral{Peripheral::Type::TIMER, 8, Peripheral::Sub::CH2};
constexpr static Peripheral TIM8_CH3 = Peripheral{Peripheral::Type::TIMER, 8, Peripheral::Sub::CH3};
constexpr static Peripheral TIM8_CH4 = Peripheral{Peripheral::Type::TIMER, 8, Peripheral::Sub::CH4};
constexpr static Peripheral TIM8_TRIG = Peripheral{Peripheral::Type::TIMER, 8, Peripheral::Sub::TRIG};
constexpr static Peripheral TIM8_COM = Peripheral{Peripheral::Type::TIMER, 8, Peripheral::Sub::COM};
constexpr static Peripheral TIM8_UP = Peripheral{Peripheral::Type::TIMER, 8, Peripheral::Sub::UP};

constexpr static Peripheral USART1_RX = Peripheral{Peripheral::Type::USART, 1, Peripheral::Sub::RX};
constexpr static Peripheral USART1_TX = Peripheral{Peripheral::Type::USART, 1, Peripheral::Sub::TX};
constexpr static Peripheral USART2_RX = Peripheral{Peripheral::Type::USART, 2, Peripheral::Sub::RX};
constexpr static Peripheral USART2_TX = Peripheral{Peripheral::Type::USART, 2, Peripheral::Sub::TX};
constexpr static Peripheral USART3_RX = Peripheral{Peripheral::Type::USART, 3, Peripheral::Sub::RX};
constexpr static Peripheral USART3_TX = Peripheral{Peripheral::Type::USART, 3, Peripheral::Sub::TX};
constexpr static Peripheral USART4_RX = Peripheral{Peripheral::Type::USART, 4, Peripheral::Sub::RX};
constexpr static Peripheral USART4_TX = Peripheral{Peripheral::Type::USART, 4, Peripheral::Sub::TX};
constexpr static Peripheral USART5_RX = Peripheral{Peripheral::Type::USART, 5, Peripheral::Sub::RX};
constexpr static Peripheral USART5_TX = Peripheral{Peripheral::Type::USART, 5, Peripheral::Sub::TX};
constexpr static Peripheral USART6_RX = Peripheral{Peripheral::Type::USART, 6, Peripheral::Sub::RX};
constexpr static Peripheral USART6_TX = Peripheral{Peripheral::Type::USART, 6, Peripheral::Sub::TX};

constexpr static Peripheral UART4_RX = Peripheral{Peripheral::Type::UART, 4, Peripheral::Sub::RX};
constexpr static Peripheral UART4_TX = Peripheral{Peripheral::Type::UART, 4, Peripheral::Sub::TX};
constexpr static Peripheral UART5_RX = Peripheral{Peripheral::Type::UART, 5, Peripheral::Sub::RX};
constexpr static Peripheral UART5_TX = Peripheral{Peripheral::Type::UART, 5, Peripheral::Sub::TX};
constexpr static Peripheral UART6_RX = Peripheral{Peripheral::Type::UART, 6, Peripheral::Sub::RX};
constexpr static Peripheral UART6_TX = Peripheral{Peripheral::Type::UART, 6, Peripheral::Sub::TX};
constexpr static Peripheral UART7_RX = Peripheral{Peripheral::Type::UART, 7, Peripheral::Sub::RX};
constexpr static Peripheral UART7_TX = Peripheral{Peripheral::Type::UART, 7, Peripheral::Sub::TX};
constexpr static Peripheral UART8_RX = Peripheral{Peripheral::Type::UART, 8, Peripheral::Sub::RX};
constexpr static Peripheral UART8_TX = Peripheral{Peripheral::Type::UART, 8, Peripheral::Sub::TX};

/// @brief  Coordinates data transfer between memory and peripherals,
class Driver : public jarnax::Copier {
public:
    Driver();
    ~Driver() = default;

    struct Flags {
        bool complete;
        bool half_complete;
        bool error;
        bool direct_mode_error;
        bool fifo_error;
    };

    /// @brief Used by constructors to initialize a driver to an exact Stream.
    /// @param periperhal The peripheral to assign the stream from.
    stm32::registers::DirectMemoryAccess::Stream volatile* Assign(Peripheral periperhal);

    /// @brief Acquires a DMA "Channel" for use.
    /// @param[out] channel The reference to a pointer to set.
    /// @return
    core::Status Acquire(stm32::registers::DirectMemoryAccess::Stream volatile*& channel, size_t number);

    /// @brief Release a DMA back to the system.
    /// @param channel
    void Release(stm32::registers::DirectMemoryAccess::Stream volatile* channel);

    /// @brief Get the status of the DMA stream.
    /// @param stream Stream Number
    /// @param[out] flags The flags to get
    core::Status GetStreamStatus(size_t stream, Flags& flags);

    /// @brief Clears the status flags for the stream.
    /// @param stream Stream Number
    /// @param flags The flags to clear.
    core::Status ClearStreamStatus(size_t stream, Flags const& flags);

    /// @brief The entry to handle the interrupt within the driver
    /// @param controller The controller index
    /// @param stream The stream index per controller (0-7 inclusive)
    void HandleInterrupt(uint32_t controller, uint32_t stream);

    /// @brief Copies data to the Peripheral.
    /// @tparam UNIT_TYPE The type of the data to copy.
    /// @param stream The pointer to the stream which has been acquired or assigned.
    /// @param destination The peripheral address
    /// @param source The UNIT_TYPE source array
    /// @param count The number of units to copy.
    /// @return
    template <typename UNIT_TYPE>
    core::Status CopyToPeripheral(
        stm32::registers::DirectMemoryAccess::Stream volatile& stream, uint32_t volatile* destination, UNIT_TYPE const source[], size_t count
    );

    /// @brief Copies data to the Peripheral.
    /// @param stream The pointer to the stream which has been acquired or assigned.
    /// @param destination The peripheral address
    /// @param source The source address
    /// @param count The number of units to copy.
    /// @return
    core::Status CopyToPeripheral(
        stm32::registers::DirectMemoryAccess::Stream volatile& stream,
        std::uintptr_t destination,
        std::uintptr_t source,
        stm32::registers::DirectMemoryAccess::Stream::Configuration::DataSize data_size,
        std::size_t count
    );

    /// @brief Copies data from the Peripheral.
    /// @tparam UNIT_TYPE The type of the data to copy.
    /// @param stream The pointer to the stream which has been acquired or assigned.
    /// @param destination The UNIT_TYPE destination array
    /// @param source The peripheral address
    /// @param count The number of units to copy.
    /// @return
    template <typename UNIT_TYPE>
    core::Status CopyFromPeripheral(
        stm32::registers::DirectMemoryAccess::Stream volatile& stream, UNIT_TYPE destination[], uint32_t volatile const* source, size_t count
    );

    /// @brief Copies data from the Peripheral.
    /// @param stream The pointer to the stream which has been acquired or assigned.
    /// @param destination The peripheral address
    /// @param source The source address
    /// @param count The number of units to copy.
    /// @return
    core::Status CopyFromPeripheral(
        stm32::registers::DirectMemoryAccess::Stream volatile& stream,
        std::uintptr_t destination,
        std::uintptr_t source,
        stm32::registers::DirectMemoryAccess::Stream::Configuration::DataSize data_size,
        std::size_t count
    );

    //===[jarnax::Copier]===================================================================================
    core::Status Copy(std::uint8_t destination[], std::uint8_t const source[], std::size_t count) override;
    core::Status Copy(std::uint16_t destination[], std::uint16_t const source[], std::size_t count) override;
    core::Status Copy(std::uint32_t destination[], std::uint32_t const source[], std::size_t count) override;
    //======================================================================================================
    core::Status Copy(
        std::uintptr_t destination,
        std::uintptr_t source,
        stm32::registers::DirectMemoryAccess::Stream::Configuration::DataSize data_size,
        std::size_t count
    );

protected:
    ///< spread across DMA1 and DMA2
    static constexpr std::size_t NumStreams{16u};
    /// only DMA2 can do memory to memory so the stream number must be >= 8
    static constexpr std::size_t DedicatedMemoryStream{9U};
    ///< The maximum number of units to copy in a single operation.
    static constexpr std::size_t MaximumMemoryCopyUnits{65535U};
    bool used_[NumStreams];
};
}    // namespace dma
}    // namespace stm32

#endif    // STM32_DMA_DRIVER_HPP
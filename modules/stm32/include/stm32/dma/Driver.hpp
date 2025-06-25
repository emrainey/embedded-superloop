#ifndef STM32_DMA_DRIVER_HPP
#define STM32_DMA_DRIVER_HPP

#include "polyfill.hpp"
#include "core/Status.hpp"
#include "jarnax/Copier.hpp"
#include "stm32/registers/DirectMemoryAccess.hpp"
#include "jarnax/dma/Manager.hpp"

namespace stm32 {
namespace dma {

/// @brief  Coordinates data transfer between memory and peripherals,
class Driver : public jarnax::Copier {
public:
    /// @brief The default constructor
    Driver();
    /// @brief The destructor
    ~Driver() = default;

    ///< spread across DMA1 and DMA2
    static constexpr std::size_t NumStreams{16u};
    /// @brief The number of streams per controller
    static constexpr size_t NumStreamsPerController{8U};
    /// @brief The number of channels per stream
    static constexpr size_t NumChannelsPerStream{8U};

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

    /// @brief Used by constructors to initialize a driver to an exact Stream.
    /// @param periperhal The peripheral to assign the stream from.
    stm32::registers::DirectMemoryAccess::Stream volatile* Assign(jarnax::Peripheral const& periperhal);

    /// @brief Acquires a DMA "Channel" for use.
    /// @param[out] channel The reference to a pointer to set.
    /// @param number The stream number to acquire.
    /// @param peripheral The peripheral to assign the stream from.
    /// @return
    core::Status Acquire(
        stm32::registers::DirectMemoryAccess::Stream volatile*& channel, size_t number, jarnax::Peripheral const& peripheral = jarnax::_
    );

    /// @brief Release a DMA back to the system.
    /// @param channel
    void Release(stm32::registers::DirectMemoryAccess::Stream volatile* channel);

    /// @brief Initialize the DMA Stream
    /// @param stream The stream to initialize
    /// @param number The stream number
    void Initialize(stm32::registers::DirectMemoryAccess::Stream volatile& stream, size_t number, jarnax::Peripheral const& peripheral);

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
    /// @post Start()
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
    /// @post Start()
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
    /// @post Start()
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
    /// @post Start()
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

    /// @brief Returns the stream index for the given stream.
    /// @param stream The reference to the stream
    /// @return The index of the stream or NumStreams if not found.
    size_t GetStreamIndex(stm32::registers::DirectMemoryAccess::Stream volatile& stream) const;

    constexpr static void GetIndexes(size_t number, size_t& controller, size_t& stream) {
        controller = number >= NumStreamsPerController ? 1 : 0;
        stream = number >= NumStreamsPerController ? number - NumStreamsPerController : number;
    }

    constexpr static size_t GetNumber(size_t controller, size_t stream) { return (controller * NumStreamsPerController) + stream; }

    /// @brief Starts the DMA stream.
    /// @param stream The stream to start
    void Start(stm32::registers::DirectMemoryAccess::Stream volatile& stream);

    /// @brief Stop the DMA stream.
    /// @param stream The stream to stop
    void Stop(stm32::registers::DirectMemoryAccess::Stream volatile& stream);

protected:
    /// only DMA2 can do memory to memory so the stream number must be >= 8
    static constexpr std::size_t DedicatedMemoryStream{9U};

    /// The maximum number of units to copy in a single operation.
    static constexpr std::size_t MaximumMemoryCopyUnits{65535U};

    /// @brief Tracks which streams are in use
    bool used_[NumStreams];
};
}    // namespace dma
}    // namespace stm32

#endif    // STM32_DMA_DRIVER_HPP
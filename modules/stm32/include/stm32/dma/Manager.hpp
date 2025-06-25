#ifndef STM32_DMA_MANAGER_HPP
#define STM32_DMA_MANAGER_HPP

#include "jarnax/dma/Manager.hpp"
#include "jarnax/dma/Resource.hpp"
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

    /// @brief The default constructor
    Manager(stm32::registers::DirectMemoryAccess volatile (&dma)[stm32::registers::NumberOfDmaControllers]);

    /// @brief The destructor
    ~Manager() = default;

    //===[jarnax::dma::Manager]=============================================================================
    core::Status Assign(jarnax::dma::Resource*& resource, jarnax::Peripheral const& peripheral) override;
    core::Status Acquire(jarnax::dma::Resource*& resource, size_t index, jarnax::Peripheral const& peripheral = _) override;
    core::Status Release(jarnax::dma::Resource*& resource) override;

    //===[jarnax::Copier]===================================================================================
    core::Status Copy(std::uint8_t destination[], std::uint8_t const source[], std::size_t count) override;
    core::Status Copy(std::uint16_t destination[], std::uint16_t const source[], std::size_t count) override;
    core::Status Copy(std::uint32_t destination[], std::uint32_t const source[], std::size_t count) override;

protected:
    core::Status Copy(
        std::uintptr_t destination,
        std::uintptr_t source,
        stm32::registers::DirectMemoryAccess::Stream::Configuration::DataSize data_size,
        std::size_t count
    );
    /// @brief The reference to the DMA controller registers
    stm32::registers::DirectMemoryAccess volatile (&dma_)[stm32::registers::NumberOfDmaControllers];
    /// @brief Tracks which streams are in use
    bool used_[NumStreams];
};

}    // namespace dma
}    // namespace stm32

#endif    // STM32_DMA_MANAGER_HPP
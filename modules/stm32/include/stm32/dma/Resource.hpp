#ifndef STM32_DMA_RESOURCE_HPP
#define STM32_DMA_RESOURCE_HPP

#include "jarnax/dma/Resource.hpp"
#include "stm32/registers/DirectMemoryAccess.hpp"

namespace stm32 {
namespace dma {
/// @brief The STM32 DMA Resource class is used to represent a DMA Resource which can be configured and used to perform transactions.
/// On STM32, this is a stream of the DMA controller.
class Resource final : public jarnax::dma::Resource {
public:
    /// The maximum number of units to copy in a single operation.
    static constexpr std::size_t MaximumMemoryCopyUnits{65535U};

    Resource(size_t controller, size_t index);
    ~Resource() = default;

    inline size_t GetNumber(void) const { return stream_number_; }

    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    // jarnax::dma::Resource Interface
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    void Initialize(Peripheral const& peripheral) override;
    core::Status ConfigureCopyToPeripheral(uintptr_t source, size_t count, size_t unit_size, uintptr_t destination) override;
    core::Status ConfigureCopyFromPeripheral(uintptr_t source, uintptr_t destination, size_t count, size_t unit_size) override;
    core::Status Enable(void) override;
    core::Status Disable(void) override;
    core::Status GetStatus(void) const override;
    size_t GetIdentifier(void) const override;

protected:
    /// The method to configure a copy to a peripheral from memory.
    stm32::registers::DirectMemoryAccess::Stream volatile& stream_;
    /// The index of the DMA controller this stream belongs to.
    std::size_t controller_index_;
    /// The index of the stream within the DMA controller.
    std::size_t stream_index_;
    /// The number of the stream. Between 0 and dma::Manager::NumStreams - 1.
    std::size_t stream_number_;
};
}    // namespace dma
}    // namespace stm32

#endif    // STM32_DMA_RESOURCE_HPP
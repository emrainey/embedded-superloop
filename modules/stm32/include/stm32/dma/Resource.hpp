#ifndef STM32_DMA_RESOURCE_HPP
#define STM32_DMA_RESOURCE_HPP

#include "jarnax/dma/Resource.hpp"
#include "stm32/registers/DirectMemoryAccess.hpp"

namespace stm32 {
namespace dma {

class Resource final : public jarnax::dma::Resource {
public:
    Resource(stm32::registers::DirectMemoryAccess::Stream volatile& stream)
        : stream_{stream} {}
    ~Resource() = default;

    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    // Resource Interface
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    template <>
    virtual core::Status ConfigureCopyToPeripheral(core::Span<std::uint8_t const> source, std::uintptr_t destination) override;
    template <>
    virtual core::Status ConfigureCopyToPeripheral(core::Span<std::uint16_t const> source, std::uintptr_t destination) override;
    template <>
    virtual core::Status ConfigureCopyToPeripheral(core::Span<std::uint32_t const> source, std::uintptr_t destination) override;
    template <>
    core::Status ConfigureCopyFromPeripheral(std::uintptr_t source, core::Span<std::uint8_t> destination) override;
    template <>
    core::Status ConfigureCopyFromPeripheral(std::uintptr_t source, core::Span<std::uint16_t> destination) override;
    template <>
    core::Status ConfigureCopyFromPeripheral(std::uintptr_t source, core::Span<std::uint32_t> destination) override;
    core::Status Enable(void) override;
    core::Status Disable(void) override;
    core::Status GetStatus(void) const override;

protected:
    stm32::registers::DirectMemoryAccess::Stream volatile& stream_;
};

}    // namespace dma
}    // namespace stm32

#endif    // STM32_DMA_RESOURCE_HPP
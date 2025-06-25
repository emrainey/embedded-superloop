#ifndef JARNAX_DMA_RESOURCE_HPP
#define JARNAX_DMA_RESOURCE_HPP

#include "core/Span.hpp"
#include "core/Status.hpp"
#include "jarnax/Copier.hpp"

namespace jarnax {
namespace dma {

/// @brief The Resource class is used to represent a DMA Resource which can be configured and used to perform transactions.
/// On some platforms this may be a stream or a channel depending on the naming scheme of the platform.
class Resource {
public:
    /// @brief The templatized method to configure a copy to a peripheral from memory.
    /// @param source The span over the source data to copy from, which must be a contiguous block of DMA-able memory.
    /// @param destination The destination address is the peripheral address to copy to. It is assumed that the peripheral is separately going to be
    /// configured to use DMA.
    /// @return Result::Success if the configuration was successful, Result::InvalidValue if the parameters are invalid.
    virtual core::Status ConfigureCopyToPeripheral(core::Span<std::uint8_t const> source, std::uintptr_t destination) = 0;

    /// @brief The templatized method to configure a copy from a peripheral to memory.
    /// @param source The peripheral address to copy from. It is assumed that the peripheral is separately going to be configured to use DMA.
    /// @param destination The span over the destination data to copy to, which must be a contiguous block of DMA-able memory.
    /// @return Result::Success if the configuration was successful, Result::InvalidValue if the parameters are invalid.
    virtual core::Status ConfigureCopyFromPeripheral(std::uintptr_t source, core::Span<std::uint8_t> destination) = 0;

    /// @brief Start the DMA Resource to perform a transaction.
    /// @retval Result::Success if the resource was started, Result::NotConfigured if the resource is not configured,
    virtual core::Status Enable(void) = 0;

    /// @brief Get the current state of the DMA Resource.
    /// @return The current state of the DMA Resource.
    /// @retval Result::Success if the resource is usable.
    /// @retval Result::Busy if the resource is still in use
    /// @retval Result::NotReady if the resource is not enabled.
    /// @retval Result::NotConfigured if the resource is not configured for a transaction.
    virtual core::Status GetStatus(void) const = 0;

    /// @brief Disable the DMA Resource from being used.
    /// @return Result::Success if the resource was disabled, Result::Busy if the resource is still in use.
    virtual core::Status Disable(void) = 0;
};
}    // namespace dma
}    // namespace jarnax

#endif    // JARNAX_DMA_RESOURCE_HPP

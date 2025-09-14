#ifndef JARNAX_DMA_RESOURCE_HPP
#define JARNAX_DMA_RESOURCE_HPP

#include <type_traits>
#include "core/Span.hpp"
#include "core/Status.hpp"
#include "cortex/Peripheral.hpp"

namespace jarnax {
namespace dma {

/// @brief The Peripheral type is used to specify the peripheral to which the DMA resource will be assigned.
using Peripheral = cortex::Peripheral;

/// @brief The Interface for a DMA Resource.
class Resource {
public:
    /// @brief Initializes the DMA Resource with a specific peripheral.
    /// @param peripheral The peripheral to assign the resource to
    virtual void Initialize(Peripheral const& peripheral) = 0;

    /// @brief The templatized method to configure a copy to a peripheral from memory.
    /// @param source The span over the source data to copy from, which must be a contiguous block of DMA-able memory.
    /// @param count The number of units to copy
    /// @param unit_size The size of each unit
    /// @param destination The destination address is the peripheral address to copy to. It is assumed that the peripheral is separately going to be
    /// configured to use DMA.
    virtual core::Status ConfigureCopyToPeripheral(uintptr_t source, size_t count, size_t unit_size, uintptr_t destination) = 0;

    template <typename UNIT_TYPE>
    core::Status ConfigureCopyToPeripheral(core::Span<UNIT_TYPE> span, uintptr_t destination) {
        constexpr size_t unit_size = sizeof(UNIT_TYPE);
        return ConfigureCopyToPeripheral(reinterpret_cast<uintptr_t>(span.data()), span.count(), unit_size, destination);
    }

    /// @brief The templatized method to configure a copy from a peripheral to memory.
    /// @param source The peripheral address to copy from. It is assumed that the peripheral is separately going to be configured to use DMA.
    /// @param destination The span over the destination data to copy to, which must be a contiguous block of DMA-able memory.
    /// @param count The number of units to copy
    /// @param unit_size The size of each unit
    virtual core::Status ConfigureCopyFromPeripheral(uintptr_t source, uintptr_t destination, size_t count, size_t unit_size) = 0;

    template <typename UNIT_TYPE>
    core::Status ConfigureCopyFromPeripheral(uintptr_t source, core::Span<UNIT_TYPE> span) {
        constexpr size_t unit_size = sizeof(UNIT_TYPE);
        return ConfigureCopyFromPeripheral(source, reinterpret_cast<uintptr_t>(span.data()), span.count(), unit_size);
    }

    /// @brief Start the DMA Resource to perform a transaction.
    virtual core::Status Enable(void) = 0;

    /// @brief Disable the DMA Resource from being used.
    virtual core::Status Disable(void) = 0;

    /// @brief Get the current state of the DMA Resource.
    /// @return The current state of the DMA Resource.
    /// @retval Result::Success if the resource is usable.
    /// @retval Result::Busy if the resource is still in use
    /// @retval Result::NotReady if the resource is not enabled.
    /// @retval Result::NotConfigured if the resource is not configured for a transaction.
    virtual core::Status GetStatus(void) const = 0;

    /// @return The unique identifier for the resource on this platform.
    virtual size_t GetIdentifier(void) const = 0;

protected:
    ~Resource() = default;
};

}    // namespace dma
}    // namespace jarnax

#endif    // JARNAX_DMA_RESOURCE_HPP

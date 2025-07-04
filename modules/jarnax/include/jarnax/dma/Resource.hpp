#ifndef JARNAX_DMA_RESOURCE_HPP
#define JARNAX_DMA_RESOURCE_HPP

#include <type_traits>
#include "core/Span.hpp"
#include "core/Status.hpp"
#include "jarnax/Copier.hpp"

namespace jarnax {
namespace dma {

/// @brief The Resource class is used to represent a DMA Resource which can be configured and used to perform transactions.
/// On some platforms this may be a stream or a channel depending on the naming scheme of the platform. We use CRTP to allow the
/// derived class to provide the specific implementation details for the platform.
template <typename DERIVED_TYPE>
class Resource_ {
public:
    /// @brief Initializes the DMA Resource with a specific peripheral.
    /// @param peripheral The peripheral to assign the resource to
    void Initialize(Peripheral const& peripheral) { return static_cast<DERIVED_TYPE&>(*this).Initialize(peripheral); }

    /// @brief The templatized method to configure a copy to a peripheral from memory.
    /// @tparam UNIT_TYPE The type of the unit to copy, which must be a standard integer type (e.g., uint8_t, uint16_t, uint32_t).
    /// @param source The span over the source data to copy from, which must be a contiguous block of DMA-able memory.
    /// @param destination The destination address is the peripheral address to copy to. It is assumed that the peripheral is separately going to be
    /// configured to use DMA.
    /// @return Result::Success if the configuration was successful, Result::InvalidValue if the parameters are invalid.
    template <typename UNIT_TYPE>
    core::Status ConfigureCopyToPeripheral(core::Span<UNIT_TYPE> source, std::uintptr_t destination) {
        return static_cast<DERIVED_TYPE&>(*this).ConfigureCopyToPeripheral(
            reinterpret_cast<std::uintptr_t>(source.data()), source.count(), sizeof(UNIT_TYPE), destination
        );
    }

    /// @brief The templatized method to configure a copy from a peripheral to memory.
    /// @tparam UNIT_TYPE The type of the unit to copy, which must be a standard integer type (e.g., uint8_t, uint16_t, uint32_t).
    /// @param source The peripheral address to copy from. It is assumed that the peripheral is separately going to be configured to use DMA.
    /// @param destination The span over the destination data to copy to, which must be a contiguous block of DMA-able memory.
    /// @return Result::Success if the configuration was successful, Result::InvalidValue if the parameters are invalid.
    template <typename UNIT_TYPE>
    core::Status ConfigureCopyFromPeripheral(std::uintptr_t source, core::Span<UNIT_TYPE> destination) {
        return static_cast<DERIVED_TYPE&>(*this).ConfigureCopyFromPeripheral(
            source, reinterpret_cast<std::uintptr_t>(destination.data()), destination.count(), sizeof(UNIT_TYPE)
        );
    }

    /// @brief Start the DMA Resource to perform a transaction.
    /// @retval Result::Success if the resource was started, Result::NotConfigured if the resource is not configured,
    core::Status Enable(void) { return static_cast<DERIVED_TYPE&>(*this).Enable(); }

    /// @brief Get the current state of the DMA Resource.
    /// @return The current state of the DMA Resource.
    /// @retval Result::Success if the resource is usable.
    /// @retval Result::Busy if the resource is still in use
    /// @retval Result::NotReady if the resource is not enabled.
    /// @retval Result::NotConfigured if the resource is not configured for a transaction.
    core::Status GetStatus(void) const { return static_cast<DERIVED_TYPE const&>(*this).GetStatus(); }

    /// @brief Disable the DMA Resource from being used.
    /// @return Result::Success if the resource was disabled, Result::Busy if the resource is still in use.
    core::Status Disable(void) { return static_cast<DERIVED_TYPE&>(*this).Disable(); }

    /// @brief Get the underlying implementation of the DMA Resource for use with Platform specific code.
    /// @return The same type as the underlying implementation
    /// @note This is a volatile reference to the underlying implementation, which is necessary for some platforms to ensure that the
    /// underlying implementation understands that the peripheral is likely to change at any time.
    auto volatile& GetUnderlying(void) const { return static_cast<DERIVED_TYPE const&>(*this).GetUnderlying_(); }

    size_t GetIdentifier(void) const {
        // This is a virtual method that allows the derived class to provide a unique identifier for the resource.
        return static_cast<DERIVED_TYPE const&>(*this).GetIdentifier();
    }
};
}    // namespace dma
}    // namespace jarnax

#endif    // JARNAX_DMA_RESOURCE_HPP

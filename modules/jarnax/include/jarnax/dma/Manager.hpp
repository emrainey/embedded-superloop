#ifndef JARNAX_DMA_MANAGER_HPP
#define JARNAX_DMA_MANAGER_HPP

#include "core/Span.hpp"
#include "core/Status.hpp"
#include "jarnax/Peripheral.hpp"
#include "jarnax/Copier.hpp"
#include "jarnax/dma/Resource.hpp"

namespace jarnax {
namespace dma {

/// @brief The Manager class is used to manage DMA resources, allowing for assignment, acquisition, and release of resources.
class Manager {
public:
    /// @brief Allows a resource to be assigned from a specififc peripheral.
    /// @param[inout] resource On input, nullptr, on output the assigned resource
    /// @param peripheral The peripheral to assign the resource from.
    /// @return Result::Success if the resource was assigned, Result::Busy if the peripheral resource is already assigned.
    virtual core::Status Assign(Resource*& resource, Peripheral const& peripheral) = 0;

    /// @brief Acquires a resource from the manager from the given index (which is platform specific)
    /// @param[inout] resource On input, nullptr, on output the acquired resource
    /// @param index The index of the resource to acquire, which is platform specific.
    /// @param peripheral The peripheral to assign the resource from, defaults to the empty peripheral.
    /// @return Result::Success if the resource was acquired, Result::Busy if the resource is already acquired.
    /// @note The index is platform specific and may not be the same across platforms.
    virtual core::Status Acquire(Resource*& resource, size_t index, Peripheral const& peripheral = _) = 0;

    /// @brief Releases a resource back to the manager.
    /// @param[inout] resource The resource to release, which will be set to nullptr on success.
    /// @return Result::Success if the resource was released, Result::Busy if the resource is still in use.
    virtual core::Status Release(Resource*& resource) = 0;

protected:
    ~Manager() = default;
};

}    // namespace dma
}    // namespace jarnax

#endif    // JARNAX_DMA_MANAGER_HPP

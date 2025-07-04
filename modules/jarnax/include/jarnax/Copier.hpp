#ifndef JARNAX_COPIER_HPP
#define JARNAX_COPIER_HPP

/// @file
/// The Copier Interface

#include <cstdint>
#include <cstddef>

#include "core/Status.hpp"
#include "jarnax/Peripheral.hpp"

namespace jarnax {

/// @brief The Copier interface is used to copy memory from one location to another.
/// @note It is not a template because the hardware only suppors these sizes explicitly
/// @todo Templatize this to allow for other sizes (which may call the supported types)
class Copier {
public:
    /// @brief Copy a block of memory from source to destination using hardware acceleration.
    /// @param destination The destination memory address.
    /// @param source The source address.
    /// @param count The number of the unit type to copy
    /// @retval core::Result::Success the copy was successful
    /// @retval core::Cause::Parameter the source or destination was nullptr or the count was zero
    virtual core::Status Copy(std::uint8_t destination[], std::uint8_t const source[], std::size_t count) = 0;
    /// @brief Copy a block of memory from source to destination using hardware acceleration.
    /// @param destination The destination memory address.
    /// @param source The source address.
    /// @param count The number of the unit type to copy
    /// @retval core::Result::Success the copy was successful
    /// @retval core::Cause::Parameter the source or destination was nullptr or the count was zero
    virtual core::Status Copy(std::uint16_t destination[], std::uint16_t const source[], std::size_t count) = 0;
    /// @brief Copy a block of memory from source to destination using hardware acceleration.
    /// @param destination The destination memory address.
    /// @param source The source address.
    /// @param count The number of the unit type to copy
    /// @retval core::Result::Success the copy was successful
    /// @retval core::Cause::Parameter the source or destination was nullptr or the count was zero
    virtual core::Status Copy(std::uint32_t destination[], std::uint32_t const source[], std::size_t count) = 0;

protected:
    ~Copier() = default;
};

/// @brief The PeripheralCopier interface is used to copy memory to and from a peripheral using hardware acceleration.
/// @note This interface is used to copy memory to and from a peripheral using hardware acceleration.
/// It is not a template because the hardware only supports a few sizes explicitly (which is hidden behind the scenes).
class PeripheralCopier {
public:
    /// @brief Initialize the Peripheral Copier with a specific peripheral.
    /// @param peripheral The peripheral to assign the resource to.
    virtual void Initialize(Peripheral const& peripheral) = 0;
    /// @brief Copy a block of memory to a peripheral destination from a memory source using hardware acceleration.
    /// @param source The memory address to copy from.
    /// @param destination The destination peripheral memory address.
    /// @param count The number of the unit type to copy
    /// @param unit_size The size of the unit type to copy, which must be one of the supported sizes (e.g., sizeof(uint8_t), sizeof(uint16_t),
    /// sizeof(uint32_t)).
    /// @retval core::Result::Success the copy was successful
    /// @retval core::Cause::Parameter the source or destination was nullptr or the count was zero
    virtual core::Status ConfigureCopyToPeripheral(std::uintptr_t source, size_t count, size_t unit_size, std::uintptr_t destination) = 0;
    /// @brief Copy a block of memory from a peripheral to a destination memory using hardware acceleration.
    /// @param source The peripheral address to copy from.
    /// @param destination The destination memory address.
    /// @param count The number of the unit type to copy
    /// @param unit_size The size of the unit type to copy, which must be one of the supported sizes (e.g., sizeof(uint8_t), sizeof(uint16_t),
    /// sizeof(uint32_t)).
    /// @retval core::Result::Success the copy was successful
    /// @retval core::Cause::Parameter the source or destination was nullptr or the count was zero
    virtual core::Status ConfigureCopyFromPeripheral(std::uintptr_t source, std::uintptr_t destination, std::size_t count, size_t unit_size) = 0;

    /// @brief Start the Peripheral Copier to perform a transaction.
    /// @retval Result::Success if the resource was started, Result::NotConfigured if the resource is not configured,
    virtual core::Status Enable(void) = 0;

    /// @brief Get the current state of the Peripheral Copier.
    /// @retval Result::Success if the resource is usable.
    /// @retval Result::Busy if the resource is still in use
    /// @retval Result::NotReady if the resource is not enabled.
    /// @retval Result::NotConfigured if the resource is not configured for a transaction.
    virtual core::Status GetStatus(void) const = 0;

    /// @brief Disable the Peripheral Copier from being used.
    /// @return Result::Success if the resource was disabled, Result::Busy if the resource is still in use.
    virtual core::Status Disable(void) = 0;

protected:
    ~PeripheralCopier() = default;
};

}    // namespace jarnax

#endif    // JARNAX_COPIER_HPP
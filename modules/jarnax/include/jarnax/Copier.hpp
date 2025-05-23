#ifndef JARNAX_COPIER_HPP
#define JARNAX_COPIER_HPP

/// @file
/// The Copier Interface

#include <cstdint>
#include <cstddef>

#include "core/Status.hpp"

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
}    // namespace jarnax

#endif    // JARNAX_COPIER_HPP
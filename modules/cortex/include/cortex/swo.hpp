#ifndef CORTEX_SWO_HPP_
#define CORTEX_SWO_HPP_

/// @file
/// The Cortex Microcontroller SWO Header

#include <cstddef>
#include <cstdint>

#include "core/Units.hpp"

#include "cortex/types.hpp"

namespace cortex {

/// The Serial Wire Output Namespace
namespace swo {

/// The fundamental type for ports
using PortType = std::uint32_t;

/// The enumerated list of ports
enum class Port : PortType {
    Errors = 0U,
    System = 1U,
    _max = System,
};

/// The mask of all enumerated types
constexpr static PortType PortMask = ((1U << to_underlying(Port::_max)) - 1U);

/// Emits a single value on a single port.
void emit(Port port, std::uint8_t value);

/// Emits an array of character values, synchronously, on a single port.
void emit(Port port, char const array[], std::size_t bytes);

/// Emits an array of character values until the null, on a single port.
void emit(Port port, char const* const str);

/// Emits an array of data values, synchronously, on a single port.
void emit(std::uint32_t port, std::uint8_t const array[], std::size_t bytes);
}    // namespace swo

}    // namespace cortex

#endif    // CORTEX_SWO_HPP_

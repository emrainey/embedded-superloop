#ifndef CORE_CONVERSIONS_HPP_
#define CORE_CONVERSIONS_HPP_

#include "core/Units.hpp"

/// @file
/// @brief Contains conversion functions between different time units to and from Iotas.
/// Iotas are a *custom* time unit defined externally and are subject to be different on different platforms.
/// Typically iotas are the highest resolution time unit available on the platform.

namespace core {
namespace units {

/// @brief Configures the conversion ratios for iotas based on the provided iotas per second. This should be called before using any of the conversion
/// functions.
void ConfigureIotas(std::uint32_t iotas_per_second);

/// @brief Converts Iota to MicroSeconds
/// @param value The iota value to convert
/// @return The MicroSeconds value
MicroSeconds ConvertToMicroSeconds(Iota const& value);

/// @brief Converts MicroSeconds to Iota
/// @param value The MicroSeconds value to convert
/// @return The Iota value
Iota ConvertToIota(MicroSeconds const& value);

/// @brief Converts Iota to MilliSeconds
/// @param value The iota value to convert
/// @return The MilliSeconds value
MilliSeconds ConvertToMilliSeconds(Iota const& value);

/// @brief Converts MilliSeconds to Iota
/// @param value The MilliSeconds value to convert
/// @return The Iota value
Iota ConvertToIota(MilliSeconds const& value);

/// @brief Converts Iota to Seconds
/// @param value The iota value to convert
/// @return The Seconds value
Seconds ConvertToSeconds(Iota const& value);

/// @brief Converts Seconds to Iota
/// @param value The Seconds value to convert
/// @return The Iota value
Iota ConvertToIota(Seconds const& value);

/// @brief Converts Seconds to Ticks
/// @param time The time to convert
/// @return The Ticks value
Ticks ConvertToTicks(Seconds const& time);

/// @brief Converts Ticks to Seconds
/// @param ticks The ticks to convert
/// @return The Seconds value
Seconds ConvertToSeconds(Ticks const& ticks);

}    // namespace units
}    // namespace core

#endif    // CORE_CONVERSIONS_HPP_

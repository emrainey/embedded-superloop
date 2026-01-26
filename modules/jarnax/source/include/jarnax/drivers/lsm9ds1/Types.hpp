#ifndef JARNAX_DRIVERS_LSM9DS1_TYPES_HPP
#define JARNAX_DRIVERS_LSM9DS1_TYPES_HPP

/// @file
/// LSM9DS1 Internal Type Definitions

#include <cstdint>

namespace jarnax {
namespace drivers {
namespace lsm9ds1 {

enum class Command : std::uint8_t {
    None = 0,       ///< No command
    Reset = 1,      ///< Reset the device from where it is back through identification.
    Measure = 2,    ///< Trigger a measurement, even if the device is not is not ready
};

enum class Milestones : std::uint8_t {
    None = 0,    ///< No milestone
    Identified,
    Configured,
    Polled,
    Measured,
};

}    // namespace lsm9ds1
}    // namespace drivers
}    // namespace jarnax

#endif    // JARNAX_DRIVERS_LSM9DS1_TYPES_HPP

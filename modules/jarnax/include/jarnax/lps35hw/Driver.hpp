#ifndef JARNAX_LPS35HW_DRIVER_HPP_
#define JARNAX_LPS35HW_DRIVER_HPP_

/// @file
/// The LPS35HW Driver Interface

#include <core/Buffer.hpp>
#include <core/Units.hpp>
#include <jarnax/Driver.hpp>

namespace jarnax {
/// @brief The LPS35HW Driver Namespace
namespace lps35hw {

/// @brief The LPS35HW Driver Interface
class Driver : public jarnax::Driver {
public:
    /// @return The last pressure reading
    virtual core::units::Pressure GetLastPressure() = 0;

    /// @return The last temperature reading
    virtual core::units::Temperature GetLastTemperature() = 0;

protected:
    ~Driver() = default;
};

}    // namespace lps35hw
}    // namespace jarnax

#endif    // JARNAX_LPS35HW_DRIVER_HPP_

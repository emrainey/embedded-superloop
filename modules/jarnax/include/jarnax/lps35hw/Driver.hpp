#ifndef JARNAX_LPS35HW_DRIVER_HPP_
#define JARNAX_LPS35HW_DRIVER_HPP_

#include <core/Buffer.hpp>
#include <core/Units.hpp>
#include <jarnax/Loopable.hpp>

namespace jarnax {
namespace lps35hw {

class Driver : public jarnax::Loopable {
public:
    /// @brief Initializes the LPS35HW Driver
    virtual core::Status Initialize() = 0;

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

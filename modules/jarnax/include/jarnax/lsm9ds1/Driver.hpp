#ifndef JARNAX_LSM9DS1_DRIVER_HPP
#define JARNAX_LSM9DS1_DRIVER_HPP

#include <core/Units.hpp>
#include <jarnax/Driver.hpp>
#include "core/units/MicroSeconds.hpp"

namespace jarnax {
namespace lsm9ds1 {

/// A triple of X, Y, Z scalars to form a vector
template <typename T>
struct Vector {
    T x;
    T y;
    T z;
};

/// A Sample structure to hold sensor data and its timestamp of the capture time.
template <typename T>
struct Sample {
    T data;
    core::units::MicroSeconds timestamp{0U};
};

/// A sample of a vector of acceleration in g's
using Tug = Sample<Vector<core::units::Acceleration>>;

/// A sample of a vector of angular velocity in degrees per second
using Twist = Sample<Vector<core::units::Ratio<core::units::Degrees, core::units::Seconds>>>;

/// A sample of a vector of magnetic field in Gauss
using Flux = Sample<Vector<core::units::Gauss>>;

/// A sample of a temperature value in Celsius
using Temp = Sample<core::units::Temperature>;

/// The LSM9DS1 driver interface
class Driver : public jarnax::Driver {
public:
    /// @return The last acceleration data
    virtual Tug GetLastAcceleration() = 0;

    /// @return The last gyroscope data
    virtual Twist GetLastGyroscope() = 0;

    /// @return The last temperature data
    virtual Temp GetLastTemperature() = 0;

    /// @return The last magnetic field reading
    virtual Flux GetLastFlux() = 0;

protected:
    ~Driver() = default;
};

}    // namespace lsm9ds1
}    // namespace jarnax

#endif    // JARNAX_LSM9DS1_DRIVER_HPP

#ifndef JARNAX_DRIVERS_LSM9DS1_DRIVER_HPP
#define JARNAX_DRIVERS_LSM9DS1_DRIVER_HPP

#include <core/Buffer.hpp>
#include <core/Statistician.hpp>
#include <jarnax/lsm9ds1/Driver.hpp>
#include <jarnax/spi/Driver.hpp>
#include "core/Status.hpp"
#include "jarnax/Timer.hpp"
#include "jarnax/drivers/lsm9ds1/StateChart.hpp"

namespace jarnax {
namespace drivers {
namespace lsm9ds1 {

struct Statistics {
    std::size_t read_acceleration_count{0};    ///< Count of acceleration reads
    std::size_t read_gyroscope_count{0};       ///< Count of gyroscope reads
    std::size_t read_temperature_count{0};     ///< Count of temperature reads
};

/// The LSM9DS1 driver interface
class Driver : public jarnax::lsm9ds1::Driver, public core::Statistician<Statistics>, protected Callback {
public:
    Driver(
        jarnax::Timer const& timer, core::units::Iota duration, jarnax::spi::Driver& driver, core::Allocator& allocator, jarnax::gpio::Output* cs_ag,
        jarnax::gpio::Output* cs_mag
    );
    virtual ~Driver() = default;

    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // jarnax::lsm9ds1::Driver implementation
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    core::Status Initialize() override;
    bool Execute(void) override;
    jarnax::lsm9ds1::Tug GetLastAcceleration() override;
    jarnax::lsm9ds1::Twist GetLastGyroscope() override;
    jarnax::lsm9ds1::Temp GetLastTemperature() override;
    jarnax::lsm9ds1::Flux GetLastFlux() override;

protected:
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // jarnax::drivers::lsm9ds1::Callback implementation
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    core::Status StartRegisterRead(uint8_t address, uint8_t count) override;
    core::Status StartRegisterWrite(uint8_t address, uint8_t count, uint8_t value[]) override;
    core::Status GetRegisterValue(uint8_t address, uint8_t count, uint8_t value[]) override;
    void OnError(core::Status status) override;
    void OnReadingAcceleration(::lsm9ds1::acceleration::Raw x, ::lsm9ds1::acceleration::Raw y, ::lsm9ds1::acceleration::Raw z) override;
    void OnReadingGyroscope(::lsm9ds1::gyroscope::Raw x, ::lsm9ds1::gyroscope::Raw y, ::lsm9ds1::gyroscope::Raw z) override;
    void OnReadingTemperature(::lsm9ds1::temperature::Raw temperature) override;
    void OnReadingFlux(::lsm9ds1::magnetic_field::Raw x, ::lsm9ds1::magnetic_field::Raw y, ::lsm9ds1::magnetic_field::Raw z) override;

    core::Status InitializeTransaction(bool is_read, uint8_t address, uint8_t count, uint8_t data[]);

    jarnax::Timer const& timer_;                            ///< The timer to use for timing operations
    jarnax::spi::Driver& spi_;                              ///< A reference to the SPI driver
    jarnax::gpio::Output* cs_ag_;                           ///< A reference to the chip select output for the accelerometer
    jarnax::gpio::Output* cs_mag_;                          ///< A reference to the chip select output for the magnetometer
    core::Buffer<jarnax::spi::DataUnit> buffer_;            ///< The buffer to use for communication with the chip.
    jarnax::spi::Transaction transaction_;                  ///< The SPI transaction to use for communication.
    jarnax::lsm9ds1::Tug last_acceleration_;                ///< The last set of acceleration readings
    jarnax::lsm9ds1::Twist last_gyroscope_;                 ///< The last set of gyroscope readings
    jarnax::lsm9ds1::Temp last_temperature_;                ///< The last temperature reading
    jarnax::lsm9ds1::Flux last_flux_;                       ///< The last magnetic field reading
    jarnax::drivers::lsm9ds1::StateChart state_machine_;    ///< The state machine for the LSM9DS1 driver
    jarnax::drivers::lsm9ds1::Event event_;                 ///< The current event to process
    size_t const data_padding_{0U};                         ///< The data padding size for the SPI transaction
};

}    // namespace lsm9ds1
}    // namespace drivers
}    // namespace jarnax

#endif    // JARNAX_LSM9DS1_DRIVER_HPP

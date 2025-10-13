#ifndef JARNAX_DRIVERS_LSM9DS1_StateChart_HPP
#define JARNAX_DRIVERS_LSM9DS1_StateChart_HPP

#include <core/StateChart.hpp>
#include <core/Status.hpp>
#include <cstdint>
#include <jarnax/CountDown.hpp>
#include <jarnax/Timer.hpp>
#include "core/units/Iota.hpp"
#include "core/units/MicroSeconds.hpp"
#include "lsm9ds1.hpp"

namespace jarnax {
namespace drivers {
namespace lsm9ds1 {

enum class State : std::uint8_t {
    Undefined = 0,          ///< Undefined state, required by the state machine
    Idling,                 ///< The state when the device is idling waiting for events
    IdentifyingAG,          ///< The state when the device is identifying the A/G
    IdentifyingMag,         ///< The state when the device is identifying the Mag
    Configuring,            ///< The state when the device is configuring the Chip
    Polling,                ///< The state when the device is polling for data
    ReadingAcceleration,    ///< The state when the device is reading acceleration data
    ReadingGyroscope,       ///< The state when the device is reading gyroscope data
    ReadingMagnetometer,    ///< The state when the device is reading magnetometer data
    ReadingTemperature,     ///< The state when the device is reading temperature data
    Error,                  ///< The state when the device is in error
    Final,
};

enum class Event : std::uint8_t {
    None = 0,            ///< No event, used to keep the state machine running, continuing previous invoked states potentially
    Reset,               ///< Reinitialize from an Error state
    Initialize,          ///< Event to initialize the LSM9DS1
    Measure,             ///< Event to trigger a measurement
    ReadAcceleration,    ///< Event to trigger a read of acceleration data
    ReadGyroscope,       ///< Event to trigger a read of gyroscope data
    ReadMagnetometer,    ///< Event to trigger a read of magnetometer data
    ReadTemperature      ///< Event to trigger a read of temperature data
};

/// @brief Callback interface for the LSM9DS1 state machine
/// This interface is used to communicate with the LSM9DS1 driver.
/// It allows the state machine to read and write registers, and to handle errors.
/// The interface is designed to be implemented by the client code that uses the LSM9DS1 StateChart (i.e. the Driver).
class Callback {
public:
    /// Read registers from the LSM9DS1
    virtual core::Status StartRegisterRead(uint8_t address, uint8_t count) = 0;
    /// Write registers to the LSM9DS1
    virtual core::Status StartRegisterWrite(uint8_t address, uint8_t count, uint8_t value[]) = 0;
    /// Get the value of a register read from the LSM9DS1
    virtual core::Status GetRegisterValue(uint8_t address, uint8_t count, uint8_t value[]) = 0;
    /// Informs the client of a problem
    virtual void OnError(core::Status status) = 0;
    /// Informs the client of a reading
    /// @param x The raw acceleration reading in X
    /// @param y The raw acceleration reading in Y
    /// @param z The raw acceleration reading in Z
    virtual void OnReadingAcceleration(::lsm9ds1::acceleration::Raw x, ::lsm9ds1::acceleration::Raw y, ::lsm9ds1::acceleration::Raw z) = 0;
    /// Informs the client of a reading
    /// @param x The raw gyroscope reading in X
    /// @param y The raw gyroscope reading in Y
    /// @param z The raw gyroscope reading in Z
    virtual void OnReadingGyroscope(::lsm9ds1::gyroscope::Raw x, ::lsm9ds1::gyroscope::Raw y, ::lsm9ds1::gyroscope::Raw z) = 0;
    /// Informs the client of a reading
    /// @param temperature The raw temperature reading
    virtual void OnReadingTemperature(::lsm9ds1::temperature::Raw temperature) = 0;
    /// Informs the client of a reading
    /// @param x The raw magnetic field reading in X
    /// @param y The raw magnetic field reading in Y
    /// @param z The raw magnetic field reading in Z
    virtual void OnReadingFlux(::lsm9ds1::magnetic_field::Raw x, ::lsm9ds1::magnetic_field::Raw y, ::lsm9ds1::magnetic_field::Raw z) = 0;

protected:
    ~Callback() = default;    ///< Protected destructor to prevent deletion through the interface
};

using Ordinal = core::StateChart<State>::Ordinal;

/// State machine for the LSM9DS1 driver
class StateChart final : public core::StateChart<State>, protected core::StateChart<State>::Callback {
public:
    StateChart(jarnax::Timer const& timer, core::units::Iota duration, lsm9ds1::Callback& callback);
    ~StateChart() = default;

    void Process(Event event);

    /// Check if the state machine is in the Idling state
    bool IsIdling() const;

protected:
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // StateChart
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    void OnEnter() override;
    void OnExit() override;
    void OnEntry(State state) override;
    Ordinal OnGuard(State state) const override;
    void OnCycle(State state) override;
    void OnExit(State state) override;
    State OnTransition(State from, Ordinal ordinal) override;

    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    jarnax::Timer const& timer_;                  ///< The timer to use for timing operations
    lsm9ds1::Callback& interface_;                ///< The callback interface to notify about state changes and request external actions
    Event event_;                                 ///< The current event to process
    core::Status entry_status_;                   ///< The current status of the Schedule Call
    core::Status result_status_;                  ///< The current status of the Result of the Transaction
    ::lsm9ds1::Accelerometer accel_registers_;    ///< A local copy of the internal registers
    ::lsm9ds1::Magnetometer mag_registers_;       ///< A local copy of the internal registers
    bool continuous_;                             ///< Whether the state machine is in continuous mode or not
    jarnax::CountDown countdown_;                 ///< Countdown timer for continuous mode
    bool initialized_;                            ///< Whether the state machine has been initialized or not
};

}    // namespace lsm9ds1
}    // namespace drivers
}    // namespace jarnax

#endif    // JARNAX_DRIVERS_LSM9DS1_StateChart_HPP

#pragma once

#include <core/StateChart.hpp> // parent
#include <core/time/CountDown.hpp>
#include <core/time/MonotonicClock.hpp>
#include <core/Event.hpp> // Inputs, Outputs
#include <core/Status.hpp>
#include <cstdint>
#include <limits>
#include <utility>
#include "lsm9ds1.hpp"
#include "jarnax/drivers/lsm9ds1/Types.hpp"
#include "core/units/MicroSeconds.hpp"

namespace jarnax::drivers::lsm9ds1 {

using Status = core::Status;
using MicroSeconds = core::time::MicroSeconds;
using MonotonicClock = core::time::MonotonicClock;

/// The State Enumeration by Bits.
/// @note No bits set is defined as the Undefined state and all bits set is defined as the Final State.
enum class State : std::uint32_t {
    Undefined = 0b0,
    Identifying = 0x01'00'00'00, ///< Identifying the external device
    Configuring = 0x02'00'00'00, ///< Configures the external device
    SampleRate = 0x02'01'00'00, ///< Configuring the Sample Rate
    ScaleRange = 0x02'02'00'00, ///< Configuring the Scale Range
    Enabled = 0x02'03'00'00, ///< Enabling the device
    Waiting = 0x03'00'00'00, ///< Waiting for the minimum time between samples to expire
    Polling = 0x04'00'00'00, ///< Polling Accelerator, Gyroscope and Temperature
    SamplingAcceleration = 0x05'00'00'00, ///< Capturing an acceleration measurement from the device
    SamplingGyroscope = 0x06'00'00'00, ///< Capturing a gyroscope measurement from the device
    SamplingTemperature = 0x07'00'00'00, ///< Capturing a temperature measurement from the device
    Error = 0x08'00'00'00, ///< An error has occurred
    Final = std::numeric_limits<std::uint32_t>::max()
};
constexpr static size_t NumberOfStates = 8U;
static_assert(std::is_integral<std::uint32_t>::value, "StateType must be an integral type");
static_assert(NumberOfStates < (std::numeric_limits<std::uint32_t>::max() - 2U), "The number of States can not exceed the max minus 2 (for reserved names)");

enum class Inputs : std::uint8_t {
    None = 0,
    Reset = 1, ///< Resets the state machine from either the Idle or the Error State.
    WroteDevice = 2, ///< Indicates that a write operation to the device has completed.
    ReadDevice = 3, ///< Indicates that a read operation to the device has completed.
    DeviceError = 4, ///< Indicates that an error has occurred during a device operation.
};

enum class Outputs : std::uint8_t {
    None = 0,
    Identified = 1, ///< Indicates that the device has been successfully identified
    Configured = 2, ///< Indicates that the device has been successfully configured
    SampledAcceleration = 3, ///< Indicates that an acceleration measurement has been successfully read
    SampledGyroscope = 4, ///< Indicates that a gyroscope measurement has been successfully read
    SampledTemperature = 5, ///< Indicates that a temperature measurement has been successfully read
    ErrorOccurred = 6, ///< Indicates that an error has occurred
};


class StateChart; // forward declaration
/// The StateChart implementation for StateChart
/// @note This class will be instantiated for the States which have SubStates.
class ConfiguringSubState final : public core::StateChart<State>, protected core::StateChart<State>::Callback {
public:
    explicit ConfiguringSubState(StateChart& parent, State parent_state);
    virtual ~ConfiguringSubState() = default;
protected:
    //=== core::StateChart<State> interface ===//
    void OnEnter() override;
    void OnEntry(State state) override;
    void OnCycle(State state) override;
    void OnExit(State state) override;
    Ordinal OnGuard(State state) const override;
    State OnTransition(State from, Ordinal ordinal) override;
    void OnExit() override;

    //===VARIABLES===//
    StateChart& parent_; ///< The reference to the callback object
    State parent_state_; ///< The state in the parent StateChart that this SubState belongs to
};

/// The StateChart implementation for StateChart
class StateChart final : public core::StateChart<State>, protected core::StateChart<State>::Callback {
public:
    /// Indicates the ordinal of the transition (1's based, 0 means no transition)
    using Ordinal = core::StateChart<State>::Ordinal;

    /// The callback for StateChart which users will implement.
    class Callback {
    public:
        /// Read the identity of the device
        virtual core::Status ReadIdentity(void) = 0;
        /// Returns true is the device identity matches the expected value
        virtual bool IsCorrectIdentity(void) const= 0;
        /// Returns true if the device configuration is complete
        virtual bool ConfigurationComplete(void) const= 0;
        /// Reads the data ready status from the device
        virtual core::Status ReadDataReady(void) = 0;
        /// Returns true if new data is ready to be read
        virtual bool DataReady(void) const= 0;
        /// Starts a reads of an acceleration measurement from the device
        virtual core::Status ReadAcceleration(void) = 0;
        /// Starts a reads of a gyroscope measurement from the device
        virtual core::Status ReadGyroscope(void) = 0;
        /// Starts a reads of a temperature measurement from the device
        virtual core::Status ReadTemperature(void) = 0;
        /// Returns true if the measurement read is complete
        virtual bool MeasurementComplete(void) const= 0;
        /// The output event callback
        virtual void OnOutput(core::Event<Outputs> output) = 0;
    protected:
        ~Callback() = default;
    };

    /// Constructor
    StateChart(Callback& callback, MonotonicClock& clock);

    // Remove the Copy and Move Constructors and Assignment Operators
    StateChart() = delete;
    StateChart(StateChart&&) = delete;
    StateChart(StateChart const&) = delete;
    StateChart& operator=(StateChart const&) = delete;
    StateChart& operator=(StateChart&&) = delete;
    virtual ~StateChart() = default;

    /// The interface to Raise events into the StateChart
    void Trigger(Inputs input);

    /// The Interface to get the Raised Outputs from the StateChart
    core::Event<Outputs> const& GetOutput() const;

    //=== core::StateChart<State> interface ===//
    void OnEnter() override;
    void OnEntry(State state) override;
    void OnCycle(State state) override;
    void OnExit(State state) override;
    Ordinal OnGuard(State state) const override;
    State OnTransition(State from, Ordinal ordinal) override;
    void OnExit() override;

protected:
    Callback& callback_; ///< The reference to the callback object
    core::time::MonotonicClock& clock_;
    mutable core::Event<Inputs> input_;
    core::Event<Outputs> output_;
    core::Status status_; ///< 
    core::time::CountDown timeout_; ///< A Countdown that triggers after 100 milliseconds
    ConfiguringSubState configuring_; ///< The SubState instance for Configuring

};

}  // namespace jarnax::drivers::lsm9ds1
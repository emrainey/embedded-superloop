#ifndef LPS35HW_STATEMACHINE_HPP_
#define LPS35HW_STATEMACHINE_HPP_

#include <lps35hw.hpp>
#include "core/StateMachine.hpp"
#include "core/Status.hpp"
#include "jarnax/CountDown.hpp"
#include "jarnax/print.hpp"

namespace jarnax {
namespace lps35hw {

/// @brief The states of the LPS35HW state machine
enum class State : std::uint8_t {
    Undefined = 0,       ///< Undefined state, required by the state machine
    Idling,              ///< The state when the device is idling waiting for events
    Identifying,         ///< The state when the device is identifying if the Chip is a LPS35HW
    Configuring,         ///< The state when the device is configuring the Chip
    ReadingReference,    ///< The state when the device is reading the reference pressure
    Polling,             ///< The state when the device is polling for a ready measurement
    Measuring,           ///< The state when the device is measuring
    Resetting,           ///< The state when the device is resetting
    Error                ///< The state when the device is in error
};

/// @brief The events that can occur in the LPS35HW state machine
enum class Event : std::uint8_t {
    None = 0,      ///< No event, used to keep the state machine running, continuing previous invoked states potentially
    Initialize,    ///< Event to initialize the LPS35HW
    Measure,       ///< Event to trigger a measurement
    Reset,         ///< Event to reset the LPS35HW
};

/// @brief Callback interface for the LPS35HW state machine
/// This interface is used to communicate with the LPS35HW driver.
/// It allows the state machine to read and write registers, and to handle errors.
/// The interface is designed to be implemented by the client code that uses the LPS35HW StateMachine (i.e. the Driver).
class Callback {
public:
    /// Read registers from the LPS35HW
    virtual core::Status StartRegisterRead(uint8_t address, uint8_t count) = 0;
    /// Write registers to the LPS35HW
    virtual core::Status StartRegisterWrite(uint8_t address, uint8_t count, uint8_t value[]) = 0;
    /// Get the value of a register read from the LPS35HW
    virtual core::Status GetRegisterValue(uint8_t address, uint8_t count, uint8_t value[]) = 0;
    /// Informs the client of a problem
    virtual void OnError(core::Status status) = 0;
    /// Informs the client of a reading
    /// @param pressure The raw pressure reading
    /// @param temperature The raw temperature reading
    virtual void OnReading(::lps35hw::RawPressure pressure, ::lps35hw::RawTemperature temperature) = 0;

protected:
    ~Callback() = default;    ///< Protected destructor to prevent deletion through the interface
};

/// @brief The state machine for the LPS35HW driver
/// This state machine handles the different states of the LPS35HW driver.
class StateMachine : public core::StateMachine<State>, protected core::StateMachine<State>::Callback {
public:
    StateMachine(jarnax::Timer const& timer, core::units::Iota duration, lps35hw::Callback& callback);
    virtual ~StateMachine() = default;

    /// Process an event in the state machine
    /// @param event The event to process
    /// @note This function will capture the event and process it through the state machine, forgetting it after processing. Cycle this until @ref
    /// IsIdling returns true.
    /// @post @ref IsIdling
    void Process(Event event);

    /// Check if the state machine is in the Idling state
    bool IsIdling() const;

protected:
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // StateMachine
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    void OnEnter() override;
    void OnExit() override;
    void OnEntry(State state) override;
    State OnCycle(State state) override;
    void OnExit(State state) override;
    void OnTransition(State from, State to) override;

    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    lps35hw::Callback& callback_;         ///< The callback interface to notify about state changes
    Event event_;                         ///< The current event to process
    core::Status status_;                 ///< The status of the last callback
    ::lps35hw::RegisterSet registers_;    ///< The register set for the LPS35HW
    bool continuous_;                     ///< Whether the state machine is in continuous mode or not
    jarnax::CountDown countdown_;         ///< Countdown timer for continuous mode
    bool initialized_;                    ///< Whether the state machine has been initialized or not
};

}    // namespace lps35hw
}    // namespace jarnax

#endif    // LPS35HW_STATEMACHINE_HPP_

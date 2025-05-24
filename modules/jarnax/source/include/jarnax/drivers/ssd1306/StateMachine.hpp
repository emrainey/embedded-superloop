#ifndef JARNAX_DRIVERS_SSD1306_STATEMACHINE_HPP
#define JARNAX_DRIVERS_SSD1306_STATEMACHINE_HPP

/// @file
/// The SSD1306 StateMachine implementation
/// @details This driver is used to represent the state machine for the SSD1306 OLED display.

#include "ssd1306.hpp"
#include "core/StateMachine.hpp"
#include "core/Span.hpp"
#include "core/Status.hpp"

namespace jarnax {
namespace drivers {
namespace ssd1306 {

enum class State {
    Undefined = 0,    ///< The driver state is undefined, required by StateMachine
    PoweringOn,       ///< The driver is in the process of powering on the display
    Awaiting,         ///< The driver is waiting for a command to process
    Idle,             ///< The driver is idle and not processing any transactions
    Updating,         ///< The driver is updating the display with new data
    PoweringOff,      ///< The driver is in the process of powering off the display
    Error             ///< The driver encountered an error during operation
};

enum class Event {
    None = 0,        ///< No event has occurred
    PowerOn,         ///< A request to power on the display has been made
    PowerOff,        ///< A request to power off the display has been made
    Update,          ///< A request to update the display has been made
    ErrorOccurred    ///< An error has occurred during operation
};

/// @brief A sequence of SSD1306 commands
using CommandSequence = core::Span<::ssd1306::Command>;

/// @brief To be implemented by the user of the SSD1306StateMachine (the Driver)
class Client {
public:
    virtual bool IsPresent(void) const = 0;
    virtual core::Status Prepare(CommandSequence sequence) = 0;
    virtual core::Status Issue(void) = 0;
    virtual core::Status AreCommandsComplete(void) const = 0;
    virtual void OnEvent(Event event, core::Status status) = 0;

protected:
    /// Do not allow destruction through the interface
    ~Client() = default;
};

/// @brief The SSD1306 State Machine
class StateMachine : public core::StateMachine<State>, protected core::StateMachine<State>::Callback {
public:
    /// @brief The parameter constructor
    /// @param client The reference to the callback interface
    StateMachine(Client& client);
    ~StateMachine() = default;

    /// @brief Processes the event for the state machine
    /// @param event
    /// @return
    void Process(Event event);

protected:
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    // core::StateMachine<State>::Callback interface
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    void OnEnter() override;
    void OnExit() override;
    State OnCycle(State current_state) override;
    void OnEntry(State state) override;
    void OnExit(State state) override;
    void OnTransition(State from, State to) override;

    Client& client_;         ///< The callback interface to interact with the SSD1306 commands
    Event event_;            ///< The current event being processed by the state machine
    core::Status status_;    ///< The status of the last operation performed by the state machine
};

}    // namespace ssd1306
}    // namespace drivers
}    // namespace jarnax

#endif    // JARNAX_SSD1306_SSD1306STATEMACHINE_HPP
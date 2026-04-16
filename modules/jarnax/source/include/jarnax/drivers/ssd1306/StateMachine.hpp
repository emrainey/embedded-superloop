#ifndef JARNAX_DRIVERS_SSD1306_STATEMACHINE_HPP
#define JARNAX_DRIVERS_SSD1306_STATEMACHINE_HPP

/// @file
/// The SSD1306 StateMachine implementation
/// @details This driver is used to represent the state machine for the SSD1306 OLED display.

#include "core/Span.hpp"
#include "core/StateMachine.hpp"
#include "core/Status.hpp"
#include "ssd1306.hpp"

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
    None = 0,    ///< No event has occurred
    PowerOn,     ///< A request to power on the display has been made
    PowerOff,    ///< A request to power off the display has been made
    Update,      ///< A request to update the display has been made
};

/// @brief A sequence of SSD1306 Commands or Data
using Sequence = core::Span<std::uint8_t const>;

/// @brief To be implemented by the user of the SSD1306StateMachine (i.e. the Driver)
class Client {
public:
    /// @brief Checks if the SSD1306 display is present and can be communicated with
    virtual bool IsPresent(void) const = 0;

    /// @brief Prepares a sequence of commands to be sent to the SSD1306 display.
    virtual core::Status PrepareCommand(Sequence sequence) = 0;

    /// @brief Prepares a sequence of commands or data to be sent to the SSD1306 display for rendering.
    virtual core::Status PrepareRender(Sequence sequence) = 0;

    /// @brief Issues the prepared commands or data to the SSD1306 display.
    virtual core::Status Issue(void) = 0;

    /// @brief Returns true if the issued commands or data have been completed by the SSD1306 display.
    virtual bool IsComplete() const = 0;

    /// @brief Checks if the issued commands have been completed by the SSD1306 display
    virtual bool CompleteCommand(core::Status& status) = 0;

    /// @brief Callback for when an event occurs in the state machine
    virtual void OnEvent(Event event, core::Status status) = 0;

    /// @brief Checks if the client is ready for preparation of a new command sequence
    virtual bool IsReadyForPreparation(void) const = 0;

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

    // Delete all copy/move ops
    StateMachine(StateMachine const&) = delete;
    StateMachine(StateMachine&&) = delete;
    StateMachine& operator=(StateMachine const&) = delete;
    StateMachine& operator=(StateMachine&&) = delete;

    /// Default Destructor
    virtual ~StateMachine() = default;

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
    Event input_event_;      ///< The current event being processed by the state machine
    Event pending_event_;    ///< Deferred event captured while the machine is busy
    Event last_event_;       ///< The last event processed by the state machine
    core::Status status_;    ///< The status of the last operation performed by the state machine
};

}    // namespace ssd1306
}    // namespace drivers
}    // namespace jarnax

#endif    // JARNAX_SSD1306_SSD1306STATEMACHINE_HPP

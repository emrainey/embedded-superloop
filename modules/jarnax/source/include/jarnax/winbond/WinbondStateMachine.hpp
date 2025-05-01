#ifndef JARNAX_WINBOND_STATE_MACHINE_HPP
#define JARNAX_WINBOND_STATE_MACHINE_HPP

#include "core/Printer.hpp"
#include "core/StateMachine.hpp"
#include "winbond.hpp"

namespace jarnax {
namespace winbond {

using Instruction = ::winbond::Instruction;    ///< The Winbond Instruction type

enum class State : std::uint8_t {
    Undefined = 0U,    ///< The undefined state, will be the initial state
    PowerUp,           ///< Sends the Power Up Command (Release Power Down)
    PowerDown,         ///< Sends the Power Down Command
    Waiting,           ///< The waiting state for Commands
    Error,             ///< The error state, will be the Final State
};

enum class Event : std::uint16_t {
    None = 0x0000U,        ///< No event
    Entered = 0x0001U,     ///< The StateMachine has been Entered
    Exited = 0xDEADU,      ///< The StateMachine has been Exited
    PowerOn = 0x0A15U,     ///< The power on event
    PowerOff = 0x0FFFU,    ///< The power off event
    Faulted = 0xBEEF,      ///< The fault event
};

/// @brief The listener interface for the StateMachine
class Listener {
public:
    /// @brief The event callback interface to be implemented by users of the StateMachine
    /// @details This is called when the StateMachine has an event to report.
    /// @param event The event that occurred
    /// @param status The status of the event
    virtual void OnEvent(Event event, core::Status status) = 0;

protected:
    ~Listener() = default;
};

/// @brief The executor interface for the StateMachine
/// @details This is called when the StateMachine has a command to execute.
class Executor {
public:
    /// @brief The command callback interface to be implemented by users of the StateMachine
    /// @details This is called when the StateMachine has a command to report.
    /// @param instruction The instruction to send
    virtual core::Status Command(winbond::Instruction instruction) = 0;
    /// @brief Is the command complete?
    virtual bool IsComplete(void) const = 0;
    virtual core::Status GetStatus(void) const = 0;

protected:
    ~Executor() = default;
};

class WinbondStateMachine : public core::StateMachine<State>, protected core::StateMachine<State>::Callback {
public:
    /// @brief The parameter constructor
    /// @param listener The reference to the Event Listener
    /// @param executor The reference to the Executor
    WinbondStateMachine(Listener& listener, Executor& executor);

    /// @brief The destructor
    ~WinbondStateMachine() = default;

    /// @brief Call this to initialize the StateMachine
    void Initialize(void);

    /// @brief Called to process an event into the StateMachine
    /// @param event The event to be processed
    /// @details This will call the StateMachine to process the event.
    void Process(Event event);

protected:
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // StateMachine Callbacks
    void OnEnter() override;
    void OnEntry(State state) override;
    State OnCycle(State state) override;
    void OnExit(State state) override;
    void OnTransition(State from, State to) override;
    void OnExit() override;
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    Listener& listener_;
    Executor& executor_;
    Event event_;
    core::Status status_;
};

}    // namespace winbond
}    // namespace jarnax

#endif    // JARNAX_WINBOND_STATE_MACHINE_HPP

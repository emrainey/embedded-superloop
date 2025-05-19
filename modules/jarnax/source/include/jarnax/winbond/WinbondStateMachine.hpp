#ifndef JARNAX_WINBOND_STATE_MACHINE_HPP
#define JARNAX_WINBOND_STATE_MACHINE_HPP

#include "core/Printer.hpp"
#include "core/StateMachine.hpp"
#include "w25q16bv.hpp"

namespace jarnax {
namespace winbond {

using Instruction = ::w25q16bv::Instruction;    ///< The Winbond Instruction type

enum class State : std::uint8_t {
    Undefined = 0U,    ///< The undefined state, required by StateMachine
    Detection,         ///< The state where the chip is detected
    Reset,             ///< The reset state
    PowerUp,           ///< Sends the Power Up Command (Release Power Down)
    Identify,          ///< The identify state
    Waiting,           ///< The waiting state for Commands
    PowerDown,         ///< Sends the Power Down Command
    Error,             ///< The error state, will be the Final State
};

enum class Event : std::uint16_t {
    None = 0x0000U,    ///< No event
    Entered,           ///< The StateMachine has been Entered
    Exited,            ///< The StateMachine has been Exited
    Reset,             ///< The reset event
    PowerOn,           ///< The power on event
    Identify,          ///< The identify event

    ReadPage,     ///< The read page event
    WritePage,    ///< The write page event
    ErasePage,    ///< The erase page event

    PowerOff,              ///< The power off event
    Faulted,               ///< The fault event
    Finalized = 0xFFFFU    ///< The machine is finalized and can not be started
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

    /// @brief Is the command done?
    virtual bool IsCommandComplete(void) const = 0;

    /// @brief Get the status of the command after it is complete
    /// @return core::Status
    virtual core::Status GetStatusAndData(void) = 0;

    /// @return True if the Winbond chip is present in the system.
    virtual bool IsPresent(void) const = 0;

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

    /// @brief Called to determine if the StateMachine is in a state which can take commands
    bool IsReady(void) const;

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
    /// @brief Helper to handle the transactions
    State WhenTransactionDone(State state, State on_success, State on_failure);
    Listener& listener_;
    Executor& executor_;
    Event event_;
    core::Status status_;
};

}    // namespace winbond
}    // namespace jarnax

#endif    // JARNAX_WINBOND_STATE_MACHINE_HPP

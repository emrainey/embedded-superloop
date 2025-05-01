#include "jarnax/winbond/WinbondStateMachine.hpp"

namespace jarnax {
namespace winbond {

WinbondStateMachine::WinbondStateMachine(Listener& listener, Executor& executor)
    : core::StateMachine<State>{*this, State::Undefined, State::Error}
    , listener_{listener}
    , executor_{executor}
    , event_{Event::None}
    , status_{core::Status{core::Result::Success, core::Cause::State}} {
}

void WinbondStateMachine::Initialize(void) {
    // Call the OnEnter() method
    event_ = Event::None;
    status_ = core::Status{core::Result::Success, core::Cause::State};
    OnEnter();
}

void WinbondStateMachine::Process(Event event) {
    // input event processing
    event_ = event;
    // cycle & input processing from queries to the functional APIs
    // This will call through the StateMachine to process the event
    // and call the Callbacks below
    RunOnce();
    // outputs happen in the form of callbacks to the listener and to functional APIs
}

void WinbondStateMachine::OnEnter() {
    listener_.OnEvent(Event::Entered, status_);
}

void WinbondStateMachine::OnEntry(State state) {
    if (state == State::Undefined) {
        // we don't know if the chip exists or if it's powered or what
    } else if (state == State::PowerUp) {
        // Send the Release Power Down command
        status_ = executor_.Command(Instruction::ReleasePowerDown);
    } else if (state == State::PowerDown) {
        // Send the Power Down Command
        status_ = executor_.Command(Instruction::PowerDown);
    } else if (state == State::Waiting) {
        // do nothing
    } else if (state == State::Error) {
        // We're entering the Final State, something went very wrong
        // status_ should have the failure cause
        listener_.OnEvent(Event::Faulted, status_);
    }
}

State WinbondStateMachine::OnCycle(State state) {
    if (state == State::Undefined) {
        // Check if the chip is present, powered and ready
    } else if (state == State::PowerUp or state == State::PowerDown) {
        // Check for Completion of the Power Down Command
        if (executor_.IsComplete()) {
            // Check the status of the command
            status_ = executor_.GetStatus();
            if (status_.IsSuccess()) {
                // Move to the PowerDown state
                state = State::PowerDown;
            } else {
                // Move to the Error state
                state = State::Error;
            }
        }
    } else if (state == State::Waiting) {
        // do nothing
    } else if (state == State::Error) {
        // In the Final State, something went very wrong
        // we should only do this once then Exit()
        status_ = core::Status{core::Result::Failure, core::Cause::State};
    }
    return state;
}

void WinbondStateMachine::OnExit(State state) {
    if (state == State::Undefined) {
        // do nothing
    } else if (state == State::PowerUp) {
        listener_.OnEvent(Event::PowerOn, status_);
    } else if (state == State::PowerDown) {
        listener_.OnEvent(Event::PowerOff, status_);
    } else if (state == State::Waiting) {
        // do nothing
    } else if (state == State::Error) {
        // do nothing
    }
}

void WinbondStateMachine::OnTransition(State from, State to) {
    // do nothing for now
    core::GetPrinter()("%hx -> %hx\r\n", to_underlying(from), to_underlying(to));
}

void WinbondStateMachine::OnExit() {
    listener_.OnEvent(Event::Exited, status_);
}

}    // namespace winbond
}    // namespace jarnax
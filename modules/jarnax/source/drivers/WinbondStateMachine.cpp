#include "jarnax/winbond/WinbondStateMachine.hpp"

namespace jarnax {
namespace winbond {

WinbondStateMachine::WinbondStateMachine(Listener& listener, Executor& executor)
    : core::StateMachine<State>{*this, State::Detection, State::Error}
    , listener_{listener}
    , executor_{executor}
    , event_{Event::None}
    , status_{core::Status{core::Result::Success, core::Cause::State}} {
}

void WinbondStateMachine::Initialize(void) {
    event_ = Event::None;
    status_ = core::Status{core::Result::Success, core::Cause::State};
    Enter();    // enter the StateMachine
}

bool WinbondStateMachine::IsReady(void) const {
    // Check if the StateMachine is in a state which can take commands
    return Is(State::Waiting);
}

void WinbondStateMachine::Process(Event event) {
    if (not IsFinal()) {
        // capture the input
        event_ = event;
        // This will call through the StateMachine to process the event
        // and call the Callbacks below
        // we are not in the final state
        RunOnce();
        // outputs happen in the form of callbacks to the listener and to functional APIs
    } else {
        listener_.OnEvent(Event::Finalized, core::Status{core::Result::Failure, core::Cause::State});
    }
}

void WinbondStateMachine::OnEnter() {
    listener_.OnEvent(Event::Entered, status_);
}

void WinbondStateMachine::OnEntry(State state) {
    if (state == State::Detection) {
        // we don't know if the chip exists or if it's powered or what
    } else if (state == State::PowerUp) {
        // Send the Release Power Down command
        status_ = executor_.Command(Instruction::ReleasePowerDown);
    } else if (state == State::PowerDown) {
        // Send the Power Down Command
        status_ = executor_.Command(Instruction::PowerDown);
    } else if (state == State::EnableReset) {
        // Send the Enable Reset Command
        status_ = executor_.Command(Instruction::EnableReset);
    } else if (state == State::Reset) {
        // Send the Reset Command
        status_ = executor_.Command(Instruction::ResetDevice);
    } else if (state == State::Waiting) {
        // do nothing, wait for events
    } else if (state == State::Error) {
        // We're entering the Final State, something went very wrong
        // status_ should have the failure cause
        listener_.OnEvent(Event::Faulted, status_);
    }
}

State WinbondStateMachine::OnCycle(State state) {
    if (state == State::Detection) {
        // Check if the chip is present, powered and ready
        if (executor_.IsPresent()) {
            state = State::Waiting;
        } else {
            status_ = core::Status{core::Result::NotSupported, core::Cause::Hardware};
            state = State::Error;
        }
    } else if (state == State::PowerUp or state == State::PowerDown) {
        // Check for Completion of the Power Down Command
        if (executor_.IsComplete()) {
            // Check the status of the command
            status_ = executor_.GetStatusAndData();
            if (status_.IsSuccess()) {
                // Move to the Waiting state for another command
                state = State::Waiting;
            } else {
                // Move to the Error state
                state = State::Error;
            }
        }
    } else if (state == State::EnableReset) {
        // Check for Completion of the Reset Command
        if (executor_.IsComplete()) {
            status_ = executor_.GetStatusAndData();
            if (status_.IsSuccess()) {
                state = State::Reset;
            } else {
                state = State::Error;
            }
        }
    } else if (state == State::Reset) {
        // Check for Completion of the Reset Command
        if (executor_.IsComplete()) {
            status_ = executor_.GetStatusAndData();
            if (status_.IsSuccess()) {
                state = State::Waiting;
            } else {
                state = State::Error;
            }
        }
    } else if (state == State::Waiting) {
        // do nothing
        if (event_ == Event::PowerOn) {
            state = State::PowerUp;
        } else if (event_ == Event::PowerOff) {
            state = State::PowerDown;
        } else if (event_ == Event::Reset) {
            state = State::EnableReset;
        }
    } else if (state == State::Error) {
        // In the Final State, something went very wrong
        // we should only do this once then become Final
    }
    return state;
}

void WinbondStateMachine::OnExit(State state) {
    if (state == State::Detection) {
        // do nothing
    } else if (state == State::PowerUp) {
        listener_.OnEvent(Event::PowerOn, status_);
    } else if (state == State::PowerDown) {
        listener_.OnEvent(Event::PowerOff, status_);
    } else if (state == State::Waiting) {
        // do nothing
    }    // else if (state == State::Error) {}
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
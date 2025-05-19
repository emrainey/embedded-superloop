#include "jarnax/winbond/WinbondStateMachine.hpp"

namespace jarnax {
namespace winbond {

WinbondStateMachine::WinbondStateMachine(Listener& listener, Executor& executor)
    : core::StateMachine<State>{*this, State::Detection}
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
        // we don't know if the chip exists or if it's powered so there's nothing to do
        // here, proceed to onCycle
    } else if (state == State::PowerUp) {
        // Send the Release Power Down command
        status_ = executor_.Command(Instruction::ReleasePowerDown);
    } else if (state == State::PowerDown) {
        // Send the Power Down Command
        status_ = executor_.Command(Instruction::PowerDown);
    } else if (state == State::Reset) {
        // Send the Enable Reset Command
        status_ = executor_.Command(Instruction::EnableReset);
    } else if (state == State::Identify) {
        // Send the Identify Command
        status_ = executor_.Command(Instruction::ReadUniqueId);
    } else if (state == State::Waiting) {
        // do nothing, wait for events
    } else if (state == State::Error) {
        // We're entering the Final State, something went very wrong
        // status_ should have the failure cause
        listener_.OnEvent(Event::Faulted, status_);
    }
}

State WinbondStateMachine::WhenTransactionDone(State state, State on_success, State on_failure) {
    if (executor_.IsCommandComplete()) {
        status_ = executor_.GetStatusAndData();
        if (status_.IsSuccess()) {
            state = on_success;
        } else {
            state = on_failure;
        }
    } else {
        status_ = core::Status{core::Result::Busy, core::Cause::State};
        listener_.OnEvent(event_, status_);
    }
    return state;
}

State WinbondStateMachine::OnCycle(State state) {
    if (state == State::Detection) {
        // Check if the chip is present, powered and ready
        if (executor_.IsPresent()) {
            state = State::Reset;
        } else {
            status_ = core::Status{core::Result::NotSupported, core::Cause::Hardware};
            state = State::Error;
        }
    } else if (state == State::Reset) {
        state = WhenTransactionDone(state, State::PowerUp, State::Error);
    } else if (state == State::PowerUp) {
        state = WhenTransactionDone(state, State::Identify, State::Error);
    } else if (state == State::PowerDown) {
        state = WhenTransactionDone(state, State::Waiting, State::Error);
    } else if (state == State::Identify) {
        state = WhenTransactionDone(state, State::Waiting, State::Error);
    } else if (state == State::Waiting) {
        // do nothing
        if (event_ == Event::PowerOn) {
            state = State::PowerUp;
        } else if (event_ == Event::PowerOff) {
            state = State::PowerDown;
        } else if (event_ == Event::Reset) {
            state = State::Reset;
        } else if (event_ == Event::Identify) {
            state = State::Identify;
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
    } else if (state == State::Reset) {
        listener_.OnEvent(Event::Reset, status_);
    } else if (state == State::Identify) {
        listener_.OnEvent(Event::Identify, status_);
    } else if (state == State::Waiting) {
        // listener_.OnEvent(Event::None, status_);
    }    // else if (state == State::Error) {}
}

void WinbondStateMachine::OnTransition(State from, State to) {
    // do nothing for now
    core::GetPrinter()("WinbondStateMachine %hx -> %hx\r\n", to_underlying(from), to_underlying(to));
}

void WinbondStateMachine::OnExit() {
    listener_.OnEvent(Event::Exited, status_);
}

}    // namespace winbond
}    // namespace jarnax
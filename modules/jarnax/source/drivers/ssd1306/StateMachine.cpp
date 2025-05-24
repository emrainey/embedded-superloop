#include "core/Array.hpp"
#include "jarnax/drivers/ssd1306/StateMachine.hpp"

namespace jarnax {
namespace drivers {
namespace ssd1306 {

StateMachine::StateMachine(Client& client)
    : core::StateMachine<State>{*this, State::PoweringOn}
    , client_{client} {
}

void StateMachine::Process(Event event) {
    if (not IsFinal()) {
        event_ = event;          // Set the event to be processed
        RunOnce();               // Process the event through the state machine
        event_ = Event::None;    // Reset the event after processing
    }
}

void StateMachine::OnEnter() {
    // do nothing for now
}

void StateMachine::OnEntry(State state) {
    // This is called when entering a new state
    if (state == State::Idle) {
        // do nothing here
    } else if (state == State::PoweringOn) {
        // do nothing here
    } else if (state == State::Awaiting) {
        // do nothing here
    } else if (state == State::Updating) {
        // do nothing here
    } else if (state == State::PoweringOff) {
        // do nothing here
    } else if (state == State::Error) {
        // do nothing here
    }
}

State StateMachine::OnCycle(State state) {
    if (state == State::Idle) {
        if (event_ == Event::PowerOn) {
            // Transition to PoweringOn state if PowerOn event is received
            state = State::PoweringOn;
        } else if (event_ == Event::Update) {
            // Transition to Updating state if Update event is received
            state = State::Updating;
        } else if (event_ == Event::PowerOff) {
            // Transition to PoweringOff state if PowerOff event is received
            state = State::PoweringOff;
        }
    } else if (state == State::PoweringOn) {
        if (client_.IsPresent()) {
            // Prepare the command sequence to power on the display
            static ::ssd1306::Command power_on_sequence[2] = {
                ::ssd1306::Command::DisplayOn,      // turn on the display
                ::ssd1306::Command::AllPixelsOn,    // set all pixels "on"?
            };
            status_ = client_.Prepare(CommandSequence{power_on_sequence, dimof(power_on_sequence)});    // Prepare the command sequence
            if (status_.IsSuccess()) {
                status_ = client_.Issue();    // Issue the command sequence
                if (status_.IsSuccess()) {
                    state = State::Idle;    // Transition to Idle state after powering on
                } else {
                    state = State::Error;    // Transition to Error state if issuing failed
                }
            } else {
                state = State::Error;    // Transition to Error state if preparing failed
            }
        }
    } else if (state == State::Awaiting) {
        if (client_.AreCommandsComplete()) {
            // If commands are complete, transition to Idle state
            state = State::Idle;
        }
        // If commands are not complete, stay in Awaiting state
    } else if (state == State::Updating) {
        // Issue the command sequence to update the display
        client_.OnEvent(Event::Update, status_);    // Notify the client that an update is requested
        state = State::Idle;
    } else if (state == State::PoweringOff) {
        if (client_.IsPresent()) {
            // Prepare the command sequence to power on the display
            static ::ssd1306::Command power_off_sequence[2] = {
                ::ssd1306::Command::InverseDisplay,    // invert all the pixels
                ::ssd1306::Command::DisplayOff,        // turn off the display
            };
            status_ = client_.Prepare(CommandSequence{power_off_sequence, dimof(power_off_sequence)});    // Prepare the command sequence
            if (status_.IsSuccess()) {
                status_ = client_.Issue();    // Issue the command sequence
                if (status_.IsSuccess()) {
                    state = State::Awaiting;    // Transition to Idle state after powering on
                } else {
                    state = State::Error;    // Transition to Error state if issuing failed
                }
            }
        }
    } else if (state == State::Error) {
        // Handle error state
        state = State::Idle;    // Placeholder, implement actual logic
    }
    return state;    // Stay in the same state if no conditions matched
}

void StateMachine::OnExit(State state) {
    // This is called when exiting a state
    if (state == State::Idle) {
        // nothing
    } else if (state == State::PoweringOn) {
        client_.OnEvent(Event::PowerOn, status_);    // Notify the client that the display is powered on
    } else if (state == State::Awaiting) {
        // nothing
    } else if (state == State::Updating) {
        client_.OnEvent(Event::Update, status_);    // Notify the client that an update has occurred
    } else if (state == State::PoweringOff) {
        client_.OnEvent(Event::PowerOff, status_);    // Notify the client that the display is powered off
    } else if (state == State::Error) {
        client_.OnEvent(Event::ErrorOccurred, status_);    // Notify the client that an error has occurred
    }
}

void StateMachine::OnExit() {
    // do nothing for now
}

void StateMachine::OnTransition(State from, State to) {
    // This is called when transitioning from one state to another
    if (from != to) {
        // Log or handle the transition if needed
    }
}

}    // namespace ssd1306
}    // namespace drivers
}    // namespace jarnax

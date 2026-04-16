#include "jarnax/drivers/ssd1306/StateMachine.hpp"
#include "core/Array.hpp"
#include "debug.hpp"
#include "jarnax/print.hpp"

namespace jarnax {
namespace drivers {
namespace ssd1306 {

namespace {
[[maybe_unused]] char const* ToString(State state) {
    switch (state) {
        case State::Undefined:
            return "Undefined";
        case State::PoweringOn:
            return "PoweringOn";
        case State::Awaiting:
            return "Awaiting";
        case State::Idle:
            return "Idle";
        case State::Updating:
            return "Updating";
        case State::PoweringOff:
            return "PoweringOff";
        case State::Error:
            return "Error";
    }
    return "<?>";
}

[[maybe_unused]] char const* ToString(Event event) {
    switch (event) {
        case Event::None:
            return "None";
        case Event::PowerOn:
            return "PowerOn";
        case Event::PowerOff:
            return "PowerOff";
        case Event::Update:
            return "Update";
    }
    return "<?>";
}
}    // namespace

// Prepare the command sequence to power on the display
static constexpr std::uint8_t const power_on_sequence[] = {
    ::ssd1306::Control::CommandMode,             // set the control byte to command mode
    ::ssd1306::Command::DisplayOff,              // turn off the display
    ::ssd1306::Control::CommandMode,             // set the control byte to command mode
    ::ssd1306::Command::SetMuxRatio,             // set the multiplex ratio
    ::ssd1306::Control::CommandMode,             // set the control byte to command
    0x1F,                                        // set the multiplex ratio to 31 (0x1F) for 32 rows
    ::ssd1306::Control::CommandMode,             // set the control byte to command mode
    ::ssd1306::Command::SetDisplayOffset,        // set the display offset
    ::ssd1306::Control::CommandMode,             // set the control byte to command
    0x00,                                        // set the start line to 0 (0x00)
    ::ssd1306::Control::CommandMode,             // set the control byte to command mode
    ::ssd1306::Command::SetStartLine | 0x00U,    // set the display start line to 0 (0x00)
    ::ssd1306::Control::CommandMode,             // set the control byte to command mode
    ::ssd1306::Command::SetSegmentRemap0,        // set the segment remap to col0=seg0
    ::ssd1306::Control::CommandMode,             // set the control byte to command
    ::ssd1306::Command::SetCOMScanUp,            // set the COM scan direction to up
    ::ssd1306::Control::CommandMode,             // set the control byte to command mode
    ::ssd1306::Command::SetCOMHwConfig,          // set the COM hardware configuration
    ::ssd1306::Control::CommandMode,             // set the control byte to command
    0x02,                                        // set the COM hardware configuration to 0x02 (COM0=COM31)
    ::ssd1306::Control::CommandMode,             // set the control byte to command mode
    ::ssd1306::Command::ContrastControl,         // set the contrast
    ::ssd1306::Control::CommandMode,             // set the control byte to command
    0x7F,                                        // set the contrast to maximum (0x7F)
    ::ssd1306::Control::CommandMode,             // set the control byte to command mode
    ::ssd1306::Command::Resume,                  // resume displaying whatever is in the display memory
    ::ssd1306::Control::CommandMode,             // set the control byte to command mode
    ::ssd1306::Command::NormalDisplay,           // set normal display mode
    ::ssd1306::Control::CommandMode,             // set the control byte to command
    ::ssd1306::Command::SetDisplayClock,         // set the display clock divide ratio and oscillator frequency
    ::ssd1306::Control::CommandMode,             // set the control byte to command
    0x80,                                        // set the display clock to 0x80 (default)
    ::ssd1306::Control::CommandMode,             // set the control byte to command mode
    ::ssd1306::Command::SetPreChargePeriod,      // set the pre-charge period
    ::ssd1306::Control::CommandMode,             // set the control byte to command
    0xF1,                                        // set the pre-charge period to 0xF1 (default)
    ::ssd1306::Control::CommandMode,             // set the control byte to command mode
    ::ssd1306::Command::SetVCOMH,                // set the VCOMH deselect level
    ::ssd1306::Control::CommandMode,             // set the control byte to command
    0x40,                                        // set the VCOMH deselect level to 0
    ::ssd1306::Control::CommandMode,             // set the control byte to command mode
    ::ssd1306::Command::ChargePump,              // set the charge pump for the display
    ::ssd1306::Control::CommandMode,             // set the control byte to command
    0x14,                                        // enable the charge pump (0x14)
    ::ssd1306::Control::CommandMode,             // set the control byte to command mode
    ::ssd1306::Command::DisplayOn,               // turn on the display
};    // namespace ssd1306

// Prepare the command sequence to power on the display
static constexpr std::uint8_t const power_off_sequence[] = {
    ::ssd1306::Control::CommandMode,       // set the control byte to command mode
    ::ssd1306::Command::InverseDisplay,    // invert all the pixels
    ::ssd1306::Control::CommandMode,       // set the control byte to command mode
    ::ssd1306::Command::DisplayOff,        // turn off the display
};

static constexpr std::uint8_t const render_image[] = {
    ::ssd1306::Control::CommandMode,             // set the control byte to command mode
    ::ssd1306::Command::MemoryAddressingMode,    // set the memory address to auto increment
    ::ssd1306::Control::CommandMode,             // set the control byte to command mode
    0x00,                                        // set the addressing mode to horizontal addressing mode
    ::ssd1306::Control::CommandMode,             // set the control byte to command mode
    ::ssd1306::Command::SetColumnAddress,        // set the column address
    ::ssd1306::Control::CommandMode,             // set the control byte to command mode
    0x00,                                        // start at column 0
    ::ssd1306::Control::CommandMode,             // set the control byte to command mode
    0x7F,                                        // end at column 127 (for 128 columns)
    ::ssd1306::Control::CommandMode,             // set the control byte to command mode
    ::ssd1306::Command::SetPageAddress,          // set the page address
    ::ssd1306::Control::CommandMode,             // set the control byte to command mode
    0x00,                                        // start at page 0
    ::ssd1306::Control::CommandMode,             // set the control byte to command mode
    0x03,                                        // end at page 3 (for 32 rows)
    ::ssd1306::Control::DataMode,                // set the control byte to data
};

StateMachine::StateMachine(Client& client)
    : core::StateMachine<State>{*this, State::Idle}
    , client_{client}
    , input_event_{Event::None}                                           // Initialize the input event to None
    , pending_event_{Event::None}                                         // Initialize deferred event storage
    , last_event_{Event::None}                                            // Initialize the last event to None
    , status_{core::Status{core::Result::Success, core::Cause::State}}    // Initialize the status to success
{}

void StateMachine::Process(Event event) {
    if (not IsFinal()) {
        if constexpr (debug::States) {
            if (event != Event::None) {
                jarnax::print("SSD1306 SM Process event=%s\r\n", ToString(event));
            }
        }
        if (event != Event::None) {
            if (Is(State::Idle) and input_event_ == Event::None) {
                input_event_ = event;
            } else if (pending_event_ == Event::None) {
                // Keep one deferred event while work is in flight.
                pending_event_ = event;
            }
        }
        RunOnce();                     // Process the event through the state machine
        input_event_ = Event::None;    // Reset the event after processing
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
        // Handle error state
        client_.OnEvent(last_event_, status_);    // Notify the client that an error has occurred
    }
}

State StateMachine::OnCycle(State state) {
    if (state == State::Idle) {
        if (input_event_ == Event::None and pending_event_ != Event::None) {
            input_event_ = pending_event_;
            pending_event_ = Event::None;
        }
        if (input_event_ == Event::PowerOn) {
            // Transition to PoweringOn state if PowerOn event is received
            state = State::PoweringOn;
            last_event_ = input_event_;    // Store the last event
        } else if (input_event_ == Event::Update) {
            // Transition to Updating state if Update event is received
            state = State::Updating;
            last_event_ = input_event_;    // Store the last event
        } else if (input_event_ == Event::PowerOff) {
            // Transition to PoweringOff state if PowerOff event is received
            state = State::PoweringOff;
            last_event_ = input_event_;    // Store the last event
        }
    } else if (state == State::PoweringOn) {
        if (client_.IsPresent()) {
            status_ = client_.PrepareCommand(Sequence{power_on_sequence});    // Prepare the command sequence
            if (status_.IsSuccess()) {
                status_ = client_.Issue();                                    // Issue the command sequence
                if (status_.IsSuccess()) {
                    state = State::Awaiting;                                  // Transition to Awaiting state after powering on
                } else {
                    state = State::Error;                                     // Transition to Error state if issuing failed
                }
            } else {
                state = State::Error;    // Transition to Error state if preparing failed
            }
        } else {
            // the display is not present, so this must fail!
            status_ = core::Status{core::Result::NotAvailable, core::Cause::Hardware};
            state = State::Error;
        }
    } else if (state == State::Awaiting) {
        if (client_.CompleteCommand(status_)) {
            // If commands are complete, recycle the transaction and wait for it to be uninitialized
            // Do NOT transition to Idle yet - we need to give the transaction time to fully recycle
            if (client_.IsReadyForPreparation()) {
                // Transaction has fully recycled, safe to move to Idle
                state = State::Idle;
            }
            // Otherwise, stay in Awaiting and wait for next cycle
        } else {
            // If commands are not complete, stay in Awaiting state
            if constexpr (debug::States) {
                static std::uint32_t awaiting_count{0U};
                awaiting_count++;
                if ((awaiting_count & 0x3FU) == 0U) {
                    jarnax::print("SSD1306 SM Awaiting... last status: ");
                    jarnax::print("", status_);
                }
            }
        }
    } else if (state == State::Updating) {
        status_ = client_.PrepareRender(render_image);    // Prepare the display with the current image
        if (status_.IsSuccess()) {
            status_ = client_.Issue();                    // Issue the command sequence
            if (status_.IsSuccess()) {
                state = State::Awaiting;                  // Transition to Awaiting state after powering on
            } else {
                state = State::Error;                     // Transition to Error state if issuing failed
            }
        } else {
            state = State::Error;    // Transition to Error state if rendering failed
        }
    } else if (state == State::PoweringOff) {
        status_ = client_.PrepareCommand(Sequence{power_off_sequence});    // Prepare the command sequence
        if (status_.IsSuccess()) {
            status_ = client_.Issue();                                     // Issue the command sequence
            if (status_.IsSuccess()) {
                state = State::Awaiting;                                   // Transition to Awaiting state after powering off
            } else {
                state = State::Error;                                      // Transition to Error state if issuing failed
            }
        }
    } else if (state == State::Error) {
        // Handle error state?
        state = State::Idle;    // Placeholder, implement actual logic
    }
    return state;               // Stay in the same state if no conditions matched
}

void StateMachine::OnExit(State state) {
    // This is called when exiting a state
    if (state == State::Idle) {
        // nothing
    } else if (state == State::PoweringOn) {
        //
    } else if (state == State::Awaiting) {
        client_.OnEvent(last_event_, status_);
        last_event_ = Event::None;    // Reset the last event after processing
    } else if (state == State::Updating) {
        //
    } else if (state == State::PoweringOff) {
        //
    } else if (state == State::Error) {
        last_event_ = Event::None;                                            // Reset the last event after processing
        status_ = core::Status{core::Result::Success, core::Cause::State};    // Reset the status once error callbacks
    }
}

void StateMachine::OnExit() {
    // do nothing for now
}

void StateMachine::OnTransition(State from, State to) {
    if constexpr (debug::States) {
        if (from != to) {
            jarnax::print("SSD1306 SM Transition: %s -> %s (event=%s)\r\n", ToString(from), ToString(to), ToString(last_event_));
        }
    }
}

}    // namespace ssd1306
}    // namespace drivers
}    // namespace jarnax

#include "jarnax/lps35hw/StateMachine.hpp"

namespace jarnax {
namespace lps35hw {

StateMachine::StateMachine(jarnax::Timer const& timer, core::units::Iota duration, lps35hw::Callback& callback)
    : core::StateMachine<State>{*this, State::Idling}
    , core::StateMachine<State>::Callback{}
    , callback_{callback}
    , event_{Event::None}
    , status_{}
    , continuous_{false}
    , countdown_{timer, core::units::Iota(duration)}
    , initialized_{false} {}

bool StateMachine::IsIdling() const {
    return Is(State::Idling);
}

void StateMachine::Process(Event event) {
    if (not IsFinal()) {
        // Capture the event to process
        event_ = event;
        // Process the event through the state machine
        RunOnce();
        // reset the event after processing
        event_ = Event::None;
    }
}

void StateMachine::OnEnter() {
    // Handle first entry logic
}

void StateMachine::OnExit() {
    // Handle last exit logic
}

void StateMachine::OnEntry(State state) {
    if (state == State::Idling) {
        if (initialized_) {
            // reset the timer
            countdown_.Reset();
        }
    } else if (state == State::Identifying) {
        status_ = callback_.StartRegisterRead(offsetof(::lps35hw::RegisterSet, who_am_i), 1);
    } else if (state == State::Configuring) {
        ::lps35hw::RegisterSet::ControlReg1 control_reg1;
        ::lps35hw::RegisterSet::ControlReg2 control_reg2;
        ::lps35hw::RegisterSet::ControlReg3 control_reg3;
        registers_.control_reg1.whole = 0;                          // Reset the control register
        registers_.control_reg1.bits.block_data_update = 1;         // block data update until both MSB and LSB are read to prevent 1/2 reads
        registers_.control_reg1.bits.low_pass_configuration = 1;    // Enable low pass configuration
        registers_.control_reg1.bits.enable_low_pass_filter = 1;    // Enable low pass filter
        registers_.control_reg1.bits.output_data_rate = 0b100;      // Set output data rate to 50Hz
        registers_.control_reg2.whole = 0;                          // Reset the control register
        registers_.control_reg2.bits.auto_increment = 1;            // Enable auto increment
        registers_.control_reg2.bits.i2c_disable = 1;               // Disable I2C
        registers_.control_reg3.whole = 0;                          // Reset the control register
        status_ = callback_.StartRegisterWrite(offsetof(::lps35hw::RegisterSet, control_reg1), 3, &registers_.control_reg1.whole);
    } else if (state == State::ReadingReference) {
        status_ = callback_.StartRegisterRead(offsetof(::lps35hw::RegisterSet, reference_extended_low), 3);
    } else if (state == State::Polling) {
        status_ = callback_.StartRegisterRead(offsetof(::lps35hw::RegisterSet, status), 1);
    } else if (state == State::Measuring) {
        status_ = callback_.StartRegisterRead(offsetof(::lps35hw::RegisterSet, pressure_output_extended_low), 5);
    } else if (state == State::Resetting) {
        registers_.control_reg2.whole = 0;                  // Reset the control register
        registers_.control_reg2.bits.software_reset = 1;    // Set the reset bit
        registers_.control_reg2.bits.i2c_disable = 1;       // Disable I2C
        registers_.control_reg2.bits.auto_increment = 1;    // Enable auto increment
        status_ = callback_.StartRegisterWrite(offsetof(::lps35hw::RegisterSet, control_reg2), 1, &registers_.control_reg2.whole);
        registers_.control_reg2.bits.software_reset = 0;    // Clear the reset bit (hardware will do this on it's own)
    } else if (state == State::Error) {
        callback_.OnError(status_);
    }
}

State StateMachine::OnCycle(State state) {
    if (state == State::Idling) {
        // Check for events and transition to the appropriate state
        if (event_ == Event::Initialize) {
            state = State::Identifying;
        } else if (event_ == Event::Measure) {
            state = State::Measuring;
        } else if (event_ == Event::Reset) {
            state = State::Resetting;
        }
        if (initialized_) {
            if (countdown_.IsExpired()) {
                state = State::Polling;    // If no events, go to Polling state
                countdown_.Reset();        // Reset the countdown timer
            }
        }
    } else if (state == State::Identifying) {
        if (status_.IsSuccess()) {
            // Get the value of the WHO_AM_I register
            status_ = callback_.GetRegisterValue(offsetof(::lps35hw::RegisterSet, who_am_i), 1, &registers_.who_am_i.whole);
            jarnax::print("LPS35HW: WHO_AM_I: %x\r\n", registers_.who_am_i.whole);
            if (status_.IsSuccess() && registers_.who_am_i.bits.id == ::lps35hw::WhoAmI) {
                // Transition to the Configuring state
                state = State::Configuring;
            } else if (status_ == core::Result::NotReady) {
                // wait until next time
                status_ = core::Status{};    // Reset status to success for next cycle
            } else {
                // Handle spi error
                state = State::Error;
            }
        } else {
            // Handle scheduling error
            state = State::Error;
        }
    } else if (state == State::Configuring) {
        if (status_.IsSuccess()) {
            status_ = callback_.GetRegisterValue(offsetof(::lps35hw::RegisterSet, control_reg1), 3, nullptr);
            if (status_.IsSuccess()) {
                state = State::ReadingReference;
            } else if (status_ == core::Result::NotReady) {
                // wait until next time
                status_ = core::Status{};    // Reset status to success for next cycles
            } else {
                // Handle spi error
                state = State::Error;
            }
        } else {
            // Handle scheduling error
            state = State::Error;
        }
    } else if (state == State::ReadingReference) {
        if (status_.IsSuccess()) {
            // Get the value of the reference pressure extended registers and save into the registers
            status_ =
                callback_.GetRegisterValue(offsetof(::lps35hw::RegisterSet, reference_extended_low), 3, &registers_.reference_extended_low.whole);
            if (status_.IsSuccess()) {
                initialized_ = true;      // Mark the state machine as initialized
                state = State::Idling;    // Transition to Idling state after reading reference
            } else if (status_ == core::Result::NotReady) {
                // wait until next time
                status_ = core::Status{};    // Reset status to success for next cycle
            } else {
                // Handle spi error
                state = State::Error;
            }
        } else {
            // Handle scheduling error
            state = State::Error;
        }
    } else if (state == State::Polling) {
        if (status_.IsSuccess()) {
            status_ = callback_.GetRegisterValue(offsetof(::lps35hw::RegisterSet, status), 1, &registers_.status.whole);
            if (status_.IsSuccess()) {
                if (registers_.status.bits.pressure_data_available and registers_.status.bits.temperature_data_available) {
                    // Data is available, transition to Measuring state
                    state = State::Measuring;
                } else {
                    // no data is available yet, so we will wait for the next cycle
                    state = State::Idling;
                }
            } else if (status_ == core::Result::NotReady) {
                // wait until next time
                status_ = core::Status{};    // Reset status to success for next cycle
            } else {
                // Handle spi error
                state = State::Error;
            }
        } else {
            // Handle scheduling error
            state = State::Error;
        }
    } else if (state == State::Measuring) {
        if (status_.IsSuccess()) {
            // Get the value of the pressure output extended registers
            status_ = callback_.GetRegisterValue(
                offsetof(::lps35hw::RegisterSet, pressure_output_extended_low), 5, &registers_.pressure_output_extended_low.whole
            );
            if (status_.IsSuccess()) {
                ::lps35hw::RawPressure ref_pressure = (static_cast<std::int32_t>(registers_.reference_extended_low.whole) << 0) |
                                                      (static_cast<std::int32_t>(registers_.reference_low.whole) << 8) |
                                                      (static_cast<std::int32_t>(registers_.reference_high.whole) << 16);
                ::lps35hw::RawPressure pressure = (static_cast<std::int32_t>(registers_.pressure_output_extended_low.whole) << 0) |
                                                  (static_cast<std::int32_t>(registers_.pressure_output_low.whole) << 8) |
                                                  (static_cast<std::int32_t>(registers_.pressure_output_high.whole) << 16);
                ::lps35hw::RawTemperature temperature = static_cast<std::uint16_t>(
                    (static_cast<std::uint16_t>(registers_.temperature_output_low.whole) << 0) |
                    (static_cast<std::uint16_t>(registers_.temperature_output_high.whole) << 8)
                );
                // Process the measurement data
                std::int32_t diff_pressure = pressure + ref_pressure;
                callback_.OnReading(diff_pressure, temperature);
                // Transition to Idling state after measurement
                state = State::Idling;
            } else if (status_ == core::Result::NotReady) {
                // wait until next time
                status_ = core::Status{};    // Reset status to success for next cycle
            } else {
                // Handle spi error
                state = State::Error;
            }
        } else {
            // Handle scheduling error
            state = State::Error;
        }
    } else if (state == State::Resetting) {
        if (status_.IsSuccess()) {
            // we wrote the values so we're just checking to see if the transaction is complete
            status_ = callback_.GetRegisterValue(offsetof(::lps35hw::RegisterSet, control_reg2), 1, nullptr);
            if (status_.IsSuccess()) {
                // Transition to the Configuring state
                state = State::Configuring;
            } else if (status_ == core::Result::NotReady) {
                // wait until next time
                status_ = core::Status{};    // Reset status to success for next cycle
            } else {
                // Handle spi error
                state = State::Error;
            }
        } else {
            // Handle scheduling error
            state = State::Error;
        }
    } else if (state == State::Error) {
        // wait for a reset to go back to Idling
        if (event_ == Event::Reset) {
            state = State::Resetting;
        }
    }
    return state;
}

void StateMachine::OnExit(State state) {
    // Handle exit logic for specific state, if any
    if (state == State::Idling) {
        // do nothing
    } else if (state == State::Identifying) {
        // do nothing
    } else if (state == State::Configuring) {
        // do nothing
    } else if (state == State::Measuring) {
        // do nothing
    } else if (state == State::Resetting) {
        // do nothing
    } else if (state == State::Error) {
        // do nothing
    }
}

void StateMachine::OnTransition(State from, State to) {
    static_cast<void>(from);    // Suppress unused variable warning
    static_cast<void>(to);      // Suppress unused variable warning
}

}    // namespace lps35hw
}    // namespace jarnax

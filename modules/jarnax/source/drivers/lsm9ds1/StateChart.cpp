#include "jarnax/drivers/lsm9ds1/StateChart.hpp"
#include "jarnax/print.hpp"
#include "jarnax/spi/Driver.hpp"
#include "lsm9ds1.hpp"

namespace jarnax {
namespace drivers {
namespace lsm9ds1 {

StateChart::StateChart(jarnax::Timer const& timer, core::units::Iota duration, lsm9ds1::Callback& interface)
    : core::StateChart<State>(static_cast<core::StateChart<State>::Callback&>(*this))    // , core::StateChart<State>::Callback{}
    , timer_{timer}
    , interface_{interface}
    , event_{Event::None}
    , entry_status_{}
    , result_status_{}
    , continuous_{false}
    , countdown_{timer, core::units::Iota(duration)}
    , initialized_{false} {}

bool StateChart::IsIdling() const {
    return Is(State::Idling);
}

void StateChart::Process(Event event) {
    if (not IsFinal()) {
        // Capture the event to process
        event_ = event;
        // Process the event through the state machine
        RunOnce();
        // reset the event after processing
        event_ = Event::None;
    }
}

void StateChart::OnEnter() {
    // Handle first entry logic
}

void StateChart::OnExit() {
    // Handle last exit logic
}

void StateChart::OnEntry(State state) {
    entry_status_ = core::Status{core::Result::NotInitialized, core::Cause::Unknown};    // start with undefined status
    if (state == State::IdentifyingAG) {
        entry_status_ = interface_.StartRegisterRead(offsetof(::lsm9ds1::Accelerometer, who_am_i), 1);
    } else if (state == State::IdentifyingMag) {
        entry_status_ = interface_.StartRegisterRead(offsetof(::lsm9ds1::Magnetometer, who_am_i), 1);
    } else if (state == State::Configuring) {
        // configure the device in most of the registers
        // status_ = callback_.StartRegisterWrite(offsetof(::lsm9ds1::Accelerometer, control_reg1), 3, &accel_registers_.control_reg1.whole);
    } else if (state == State::Idling) {
        if (initialized_) {
            // reset the timer
            countdown_.Reset();
        }
    } else if (state == State::Polling) {
        // status_ = callback_.StartRegisterRead(offsetof(::lsm9ds1::Accelerometer, status), 1);
    } else if (state == State::ReadingAcceleration) {
        // status_ = callback_.StartRegisterRead(offsetof(::lsm9ds1::Accelerometer, pressure_output_extended_low), 5);
    } else if (state == State::ReadingGyroscope) {
        // status_ = callback_.StartRegisterRead(offsetof(::lsm9ds1::Accelerometer, gyroscope_output), 6);
    } else if (state == State::ReadingTemperature) {
        // status_ = callback_.StartRegisterRead(offsetof(::lsm9ds1::Accelerometer, temperature_output), 2);
    } else if (state == State::Error) {
        interface_.OnError(entry_status_);
        interface_.OnError(result_status_);
    }
}

Ordinal StateChart::OnGuard(State state) const {
    bool good_schedule = false;
    bool good_result = false;
    if (state == State::IdentifyingAG or state == State::IdentifyingMag) {
        if (entry_status_.IsFailure()) {
            // the entry call didn't work, go to error state
            return 1;
        }
    }
    // for any state which needs to check to see if it was able to schedule a transaction, we need to check the status code
    if (state != State::Idling or state != State::Error) {
        good_schedule = (entry_status_.IsSuccess());
    }
    if (good_schedule) {
        // check the result of the transaction
        good_result = (entry_status_.IsSuccess());
    }
    static_cast<void>(good_result);    // avoid unused variable warning
    // don't transition on zero
    return 0;
}

void StateChart::OnCycle(State state) {
    if (state == State::IdentifyingAG) {
        if (entry_status_.IsSuccess()) {
            // Get the value of the WHO_AM_I register
            result_status_ = interface_.GetRegisterValue(offsetof(::lsm9ds1::Accelerometer, who_am_i), 1, &accel_registers_.who_am_i);
            jarnax::print("lsm9ds1: A/G WHO_AM_I: %x\r\n", accel_registers_.who_am_i);
            if (result_status_.IsSuccess() && accel_registers_.who_am_i == ::lsm9ds1::WhoAmI) {
                state = State::IdentifyingMag;
            } else if (result_status_ == core::Result::NotReady) {
                // wait until next time
                result_status_ = core::Status{};    // Reset status to success for next cycle
            } else {
                // Handle spi error
                state = State::Error;
            }
        } else {
            // Handle scheduling error
            state = State::Error;
        }
    } else if (state == State::IdentifyingMag) {
        if (entry_status_.IsSuccess()) {
            // Get the value of the WHO_AM_I register
            result_status_ = interface_.GetRegisterValue(offsetof(::lsm9ds1::Magnetometer, who_am_i), 1, &mag_registers_.who_am_i);
            jarnax::print("lsm9ds1: Mag WHO_AM_I: %x\r\n", mag_registers_.who_am_i);
            if (result_status_.IsSuccess() && mag_registers_.who_am_i == ::lsm9ds1::WhoAmI) {
                state = State::Idling;
            } else if (result_status_ == core::Result::NotReady) {
                // wait until next time
                result_status_ = core::Status{};    // Reset status to success for next cycle
            } else {
                // Handle spi error
                state = State::Error;
            }
        } else {
            // Handle scheduling error
            state = State::Error;
        }
    } else if (state == State::Configuring) {
        if (entry_status_.IsSuccess()) {
            // status_ = callback_.GetRegisterValue(offsetof(::lsm9ds1::RegisterSet, control1), 3, nullptr);
            if (result_status_.IsSuccess()) {
                initialized_ = true;    // Mark the state machine as initialized
                state = State::Idling;
            } else if (result_status_ == core::Result::NotReady) {
                // wait until next time
                result_status_ = core::Status{};    // Reset status to success for next cycles
            } else {
                // Handle spi error
                state = State::Error;
            }
        } else {
            // Handle scheduling error
            state = State::Error;
        }
    } else if (state == State::Polling) {
        if (entry_status_.IsSuccess()) {
            result_status_ = interface_.GetRegisterValue(offsetof(::lsm9ds1::Accelerometer, status1), 1, &accel_registers_.status1.whole);
            if (result_status_.IsSuccess()) {
                if (accel_registers_.status1.bits.data_available_gyroscope or accel_registers_.status1.bits.data_available_temperature) {
                    // Data is available, transition to Measuring state
                    state = State::ReadingGyroscope;
                } else {
                    // no data is available yet, so we will wait for the next cycle
                    state = State::Idling;
                }
            } else if (result_status_ == core::Result::NotReady) {
                // wait until next time
                result_status_ = core::Status{};    // Reset status to success for next cycle
            } else {
                // Handle spi error
                state = State::Error;
            }
        } else {
            // Handle scheduling error
            state = State::Error;
        }
    } else if (state == State::ReadingAcceleration) {
        if (entry_status_.IsSuccess()) {
            // Get the value of the reference pressure extended registers and save into the registers
            result_status_ = interface_.GetRegisterValue(
                offsetof(::lsm9ds1::Accelerometer, output_x_accelerometer), 6, &accel_registers_.output_x_accelerometer[0]
            );
            if (result_status_.IsSuccess()) {
                ::lsm9ds1::word word;
                word.as_u08[0] = accel_registers_.output_x_accelerometer[0];
                word.as_u08[1] = accel_registers_.output_x_accelerometer[1];
                ::lsm9ds1::acceleration::Raw x = word.as_s16[0];
                word.as_u08[0] = accel_registers_.output_y_accelerometer[0];
                word.as_u08[1] = accel_registers_.output_y_accelerometer[1];
                ::lsm9ds1::acceleration::Raw y = word.as_s16[0];
                word.as_u08[0] = accel_registers_.output_z_accelerometer[0];
                word.as_u08[1] = accel_registers_.output_z_accelerometer[1];
                ::lsm9ds1::acceleration::Raw z = word.as_s16[0];
                interface_.OnReadingAcceleration(x, y, z);
                state = State::Idling;    // Transition to Idling state after reading reference
            } else if (result_status_ == core::Result::NotReady) {
                // wait until next time
                result_status_ = core::Status{};    // Reset status to success for next cycle
            } else {
                // Handle spi error
                state = State::Error;
            }
        } else {
            // Handle scheduling error
            state = State::Error;
        }
    } else if (state == State::ReadingGyroscope) {
        if (entry_status_.IsSuccess()) {
            // Get the value of the reference pressure extended registers and save into the registers
            result_status_ =
                interface_.GetRegisterValue(offsetof(::lsm9ds1::Accelerometer, output_x_gyroscope), 6, &accel_registers_.output_x_gyroscope[0]);
            if (result_status_.IsSuccess()) {
                ::lsm9ds1::word word;
                word.as_u08[0] = accel_registers_.output_x_gyroscope[0];
                word.as_u08[1] = accel_registers_.output_x_gyroscope[1];
                ::lsm9ds1::gyroscope::Raw x = word.as_s16[0];
                word.as_u08[0] = accel_registers_.output_y_gyroscope[0];
                word.as_u08[1] = accel_registers_.output_y_gyroscope[1];
                ::lsm9ds1::gyroscope::Raw y = word.as_s16[0];
                word.as_u08[0] = accel_registers_.output_z_gyroscope[0];
                word.as_u08[1] = accel_registers_.output_z_gyroscope[1];
                ::lsm9ds1::gyroscope::Raw z = word.as_s16[0];
                interface_.OnReadingGyroscope(x, y, z);
                state = State::Idling;    // Transition to Idling state after reading reference
            } else if (result_status_ == core::Result::NotReady) {
                // wait until next time
                result_status_ = core::Status{};    // Reset status to success for next cycle
            } else {
                // Handle spi error
                state = State::Error;
            }
        } else {
            // Handle scheduling error
            state = State::Error;
        }
    } else if (state == State::ReadingTemperature) {
        if (entry_status_.IsSuccess()) {
            // Get the value of the reference pressure extended registers and save into the registers
            result_status_ =
                interface_.GetRegisterValue(offsetof(::lsm9ds1::Accelerometer, output_temperature_low), 2, &accel_registers_.output_temperature_low);
            if (result_status_.IsSuccess()) {
                ::lsm9ds1::word word;
                word.as_u08[0] = accel_registers_.output_temperature_low;
                word.as_u08[1] = accel_registers_.output_temperature_high;
                ::lsm9ds1::temperature::Raw value = word.as_s16[0];
                interface_.OnReadingTemperature(value);
                state = State::Idling;    // Transition to Idling state after reading reference
            } else if (result_status_ == core::Result::NotReady) {
                // wait until next time
                result_status_ = core::Status{};    // Reset status to success for next cycle
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
            state = State::Idling;
        }
    }
}

void StateChart::OnExit(State state) {
    // Handle exit logic for specific state, if any
    if (state == State::Idling) {
        // do nothing
    } else if (state == State::IdentifyingAG) {
        // do nothing
    } else if (state == State::IdentifyingMag) {
        // do nothing
    } else if (state == State::Configuring) {
        // do nothing
    } else if (state == State::Polling) {
        // do nothing
    } else if (state == State::ReadingAcceleration) {
        // do nothing
    } else if (state == State::ReadingGyroscope) {
        // do nothing
    } else if (state == State::ReadingTemperature) {
        // do nothing
    } else if (state == State::Error) {
        // do nothing
    }
}

State StateChart::OnTransition(State from, Ordinal ordinal) {
    State state = State::Final;
    if (from == State::Undefined) {    //<--- ENTRY
        state = State::IdentifyingAG;
    } else if (from == State::IdentifyingAG or from == State::IdentifyingMag) {
        if (ordinal == 1) {
            state = State::Error;
        }
    } else if (from == State::Configuring) {
        //
    } else if (from == State::Idling) {
        if (event_ == Event::Initialize) {
            state = State::IdentifyingAG;
        } else if (event_ == Event::Measure) {
            state = State::Polling;
        }
        if (countdown_.IsExpired()) {
            state = State::Polling;    // If no events, go to Polling state
        }
    } else if (from == State::IdentifyingAG) {
        state = State::IdentifyingMag;
    } else if (from == State::IdentifyingMag) {
        state = State::Configuring;
    } else if (from == State::Configuring) {
        state = State::Idling;
    } else if (from == State::Polling) {
        state = State::ReadingAcceleration;
    } else if (from == State::ReadingAcceleration) {
        state = State::ReadingGyroscope;
    } else if (from == State::ReadingGyroscope) {
        state = State::ReadingTemperature;
    } else if (from == State::ReadingTemperature) {
        state = State::Idling;
    } else if (from == State::Error) {
        // fall back to Final state
        state = State::Final;
    }
    return state;
}

}    // namespace lsm9ds1
}    // namespace drivers
}    // namespace jarnax

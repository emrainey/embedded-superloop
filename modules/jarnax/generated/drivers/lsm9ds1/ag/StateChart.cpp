
#include "StateChart.hpp"

namespace jarnax::drivers::lsm9ds1 {

StateChart::StateChart(Callback& callback, MonotonicClock& clock)
    : core::StateChart<State>{static_cast<core::StateChart<State>::Callback&>(*this)} // we are the callback to the parent StateChart base class
    , callback_{callback}
    , clock_{clock}
    , input_{Inputs::None}
    , output_{Outputs::None}
    , status_{ core::Result::NotInitialized, core::Cause::State }
    , timeout_{clock_, MicroSeconds{ 100U } } ///< A Countdown that triggers after 100 milliseconds
    , configuring_{ *this, State::Configuring } ///< The SubState instance for Configuring
    {}

void StateChart::Trigger(Inputs event) {
    output_ = Outputs::None; // lower any outputs in preparation for the next one
    input_ = event;
    RunOnce();
    if (output_.Peek() != Outputs::None) {
        callback_.OnOutput(std::move(output_));
    }
    // input is cleared in OnGuard after all guards have been evaluated
}

core::Event<Outputs> const& StateChart::GetOutput() const {
    return output_;
}

void StateChart::OnEnter() {
    // cpp_action(interface, None)
    // do nothing
}

void StateChart::OnEntry(State state) {
    switch (state) {
        case State::Identifying:
            // cpp_action(interface, None)
            // do nothing
            break;
        case State::Configuring:
            // cpp_action(interface, None)
            // do nothing
            break;
        case State::Waiting:
            // cpp_action(interface, {'expression': 'timeout_.Reset()'})
            timeout_.Reset();
            break;
        case State::Polling:
            // cpp_action(interface, {'call': {'name': 'ReadDataReady', 'parameters': 'void', 'assign': 'status_'}})
            status_ = callback_.ReadDataReady();
            break;
        case State::SamplingAcceleration:
            // cpp_action(interface, {'call': {'name': 'ReadAcceleration', 'parameters': 'void', 'assign': 'status_'}})
            status_ = callback_.ReadAcceleration();
            break;
        case State::SamplingGyroscope:
            // cpp_action(interface, {'call': {'name': 'ReadGyroscope', 'parameters': 'void', 'assign': 'status_'}})
            status_ = callback_.ReadGyroscope();
            break;
        case State::SamplingTemperature:
            // cpp_action(interface, {'call': {'name': 'ReadTemperature', 'parameters': 'void', 'assign': 'status_'}})
            status_ = callback_.ReadTemperature();
            break;
        case State::Error:
            // cpp_action(interface, None)
            // do nothing
            break;
        default:
            // Undefined or Final is not allowed!
            break;
    }
}

void StateChart::OnCycle(State state) {
    switch (state) {
        case State::Identifying:
            // cpp_action(interface, {'call': {'name': 'ReadIdentity', 'parameters': 'void', 'assign': 'status_'}})
            status_ = callback_.ReadIdentity();
            break;
        case State::Configuring:
            // cpp_action(interface, None)
            // do nothing
            break;
        case State::Waiting:
            // cpp_action(interface, None)
            // do nothing
            break;
        case State::Polling:
            // cpp_action(interface, None)
            // do nothing
            break;
        case State::SamplingAcceleration:
            // cpp_action(interface, None)
            // do nothing
            break;
        case State::SamplingGyroscope:
            // cpp_action(interface, None)
            // do nothing
            break;
        case State::SamplingTemperature:
            // cpp_action(interface, None)
            // do nothing
            break;
        case State::Error:
            // cpp_action(interface, {'output': 'ErrorOccurred'})
            output_ = Outputs::ErrorOccurred;
            break;
        default:
            // Undefined or Final is not allowed!
            break;
    }
}

void StateChart::OnExit(State state) {
    switch (state) {
        case State::Identifying:
            // cpp_action(interface, None)
            // do nothing
            break;
        case State::Configuring:
            // cpp_action(interface, None)
            // do nothing
            break;
        case State::Waiting:
            // cpp_action(interface, None)
            break;
        case State::Polling:
            // cpp_action(interface, None)
            break;
        case State::SamplingAcceleration:
            // cpp_action(interface, None)
            // do nothing
            break;
        case State::SamplingGyroscope:
            // cpp_action(interface, None)
            // do nothing
            break;
        case State::SamplingTemperature:
            // cpp_action(interface, None)
            // do nothing
            break;
        case State::Error:
            // cpp_action(interface, None)
            // do nothing
            break;
        default:
            // Undefined or Final is not allowed!
            break;
    }
}

StateChart::Ordinal StateChart::OnGuard(State state) const {
    StateChart::Ordinal ordinal = 0; // zero means to stay in the current state
    switch (state) {
        case State::Identifying: 
            // cpp_trigger({'input': 'ReadDevice'})
            if (input_.IsRaised() and input_.Peek() == Inputs::ReadDevice) {
                // cpp_guard(interface, {'call': {'name': 'IsCorrectIdentity', 'parameters': 'void'}})
                if (callback_.IsCorrectIdentity()) {
                    ordinal = 1;
                    break;
                }
            } 
            // cpp_trigger({'input': 'ReadDevice'})
            if (input_.IsRaised() and input_.Peek() == Inputs::ReadDevice) {
                // cpp_guard(interface, {'call': {'name': 'IsCorrectIdentity', 'parameters': 'void', 'expected': False}})
                if (false == callback_.IsCorrectIdentity()) {
                    ordinal = 2;
                    break;
                }
            }
            break;
        case State::Configuring: 
            // cpp_trigger({'input': 'WroteDevice'})
            if (input_.IsRaised() and input_.Peek() == Inputs::WroteDevice) {
                // cpp_guard(interface, {'call': {'name': 'ConfigurationComplete', 'parameters': 'void', 'expected': True}})
                if (true == callback_.ConfigurationComplete()) {
                    ordinal = 1;
                    break;
                }
            } 
            // cpp_trigger({'input': 'DeviceError'})
            if (input_.IsRaised() and input_.Peek() == Inputs::DeviceError) {
                // cpp_guard(interface, None)
                if constexpr (core::always) {
                    ordinal = 2;
                    break;
                }
            }
            break;
        case State::Waiting: 
            // cpp_trigger(always)
            if constexpr (core::always) {
                // cpp_guard(interface, {'condition': 'timeout_.IsExpired()'})
                if (timeout_.IsExpired()) {
                    ordinal = 1;
                    break;
                }
            }
            break;
        case State::Polling: 
            // cpp_trigger(always)
            if constexpr (core::always) {
                // cpp_guard(interface, {'condition': 'not status_.IsBusy() and status_.IsFailure()'})
                if (not status_.IsBusy() and status_.IsFailure()) {
                    ordinal = 1;
                    break;
                }
            } 
            // cpp_trigger({'input': 'ReadDevice'})
            if (input_.IsRaised() and input_.Peek() == Inputs::ReadDevice) {
                // cpp_guard(interface, {'call': {'name': 'DataReady', 'parameters': 'void', 'expected': True}})
                if (true == callback_.DataReady()) {
                    ordinal = 2;
                    break;
                }
            } 
            // cpp_trigger({'input': 'DeviceError'})
            if (input_.IsRaised() and input_.Peek() == Inputs::DeviceError) {
                // cpp_guard(interface, None)
                if constexpr (core::always) {
                    ordinal = 3;
                    break;
                }
            }
            break;
        case State::SamplingAcceleration: 
            // cpp_trigger(always)
            if constexpr (core::always) {
                // cpp_guard(interface, {'condition': 'not status_.IsBusy() and status_.IsFailure()'})
                if (not status_.IsBusy() and status_.IsFailure()) {
                    ordinal = 1;
                    break;
                }
            } 
            // cpp_trigger({'input': 'ReadDevice'})
            if (input_.IsRaised() and input_.Peek() == Inputs::ReadDevice) {
                // cpp_guard(interface, {'call': {'name': 'MeasurementComplete', 'parameters': 'void', 'expected': True}})
                if (true == callback_.MeasurementComplete()) {
                    ordinal = 2;
                    break;
                }
            } 
            // cpp_trigger({'input': 'DeviceError'})
            if (input_.IsRaised() and input_.Peek() == Inputs::DeviceError) {
                // cpp_guard(interface, None)
                if constexpr (core::always) {
                    ordinal = 3;
                    break;
                }
            }
            break;
        case State::SamplingGyroscope: 
            // cpp_trigger(always)
            if constexpr (core::always) {
                // cpp_guard(interface, {'condition': 'not status_.IsBusy() and status_.IsFailure()'})
                if (not status_.IsBusy() and status_.IsFailure()) {
                    ordinal = 1;
                    break;
                }
            } 
            // cpp_trigger({'input': 'ReadDevice'})
            if (input_.IsRaised() and input_.Peek() == Inputs::ReadDevice) {
                // cpp_guard(interface, {'call': {'name': 'MeasurementComplete', 'parameters': 'void', 'expected': True}})
                if (true == callback_.MeasurementComplete()) {
                    ordinal = 2;
                    break;
                }
            } 
            // cpp_trigger({'input': 'DeviceError'})
            if (input_.IsRaised() and input_.Peek() == Inputs::DeviceError) {
                // cpp_guard(interface, None)
                if constexpr (core::always) {
                    ordinal = 3;
                    break;
                }
            }
            break;
        case State::SamplingTemperature: 
            // cpp_trigger(always)
            if constexpr (core::always) {
                // cpp_guard(interface, {'condition': 'not status_.IsBusy() and status_.IsFailure()'})
                if (not status_.IsBusy() and status_.IsFailure()) {
                    ordinal = 1;
                    break;
                }
            } 
            // cpp_trigger({'input': 'ReadDevice'})
            if (input_.IsRaised() and input_.Peek() == Inputs::ReadDevice) {
                // cpp_guard(interface, {'call': {'name': 'MeasurementComplete', 'parameters': 'void', 'expected': True}})
                if (true == callback_.MeasurementComplete()) {
                    ordinal = 2;
                    break;
                }
            } 
            // cpp_trigger({'input': 'DeviceError'})
            if (input_.IsRaised() and input_.Peek() == Inputs::DeviceError) {
                // cpp_guard(interface, None)
                if constexpr (core::always) {
                    ordinal = 3;
                    break;
                }
            }
            break;
        case State::Error: 
            // cpp_trigger({'input': 'Reset'})
            if (input_.IsRaised() and input_.Peek() == Inputs::Reset) {
                // cpp_guard(interface, None)
                if constexpr (core::always) {
                    ordinal = 1;
                    break;
                }
            }
            break;
        default:
            // Undefined or Final is not allowed!
            break;
    }
    // we clear the input here after all guards have been evaluated
    // it must be triggered again to be seen
    input_.Clear();
    // zero indicates that no transition was taken
    return ordinal;
}

State StateChart::OnTransition(State from, StateChart::Ordinal ordinal) {
    if (ordinal == 0U) {
        // not allowed
        return State::Undefined;
    }
    switch (from) {
        case State::Undefined: // ordinal is ignored here
            return State::Identifying;
        case State::Identifying:
            if (ordinal == 1) { 
                // cpp_action(interface, {'output': 'Identified'})
                output_ = Outputs::Identified;
                return State::Configuring;
            }
            if (ordinal == 2) {
                return State::Final;
            }
            break;
        case State::Configuring:
            if (ordinal == 1) { 
                // cpp_action(interface, {'output': 'Configured'})
                output_ = Outputs::Configured;
                return State::Waiting;
            }
            if (ordinal == 2) { 
                // cpp_action(interface, {'output': 'ErrorOccurred'})
                output_ = Outputs::ErrorOccurred;
                return State::Error;
            }
            break;
        case State::Waiting:
            if (ordinal == 1) {
                return State::Polling;
            }
            break;
        case State::Polling:
            if (ordinal == 1) {
                return State::Error;
            }
            if (ordinal == 2) {
                return State::SamplingAcceleration;
            }
            if (ordinal == 3) { 
                // cpp_action(interface, {'output': 'ErrorOccurred'})
                output_ = Outputs::ErrorOccurred;
                return State::Error;
            }
            break;
        case State::SamplingAcceleration:
            if (ordinal == 1) {
                return State::Error;
            }
            if (ordinal == 2) { 
                // cpp_action(interface, {'output': 'SampledAcceleration'})
                output_ = Outputs::SampledAcceleration;
                return State::SamplingGyroscope;
            }
            if (ordinal == 3) { 
                // cpp_action(interface, {'output': 'ErrorOccurred'})
                output_ = Outputs::ErrorOccurred;
                return State::Error;
            }
            break;
        case State::SamplingGyroscope:
            if (ordinal == 1) {
                return State::Error;
            }
            if (ordinal == 2) { 
                // cpp_action(interface, {'output': 'SampledGyroscope'})
                output_ = Outputs::SampledGyroscope;
                return State::SamplingTemperature;
            }
            if (ordinal == 3) { 
                // cpp_action(interface, {'output': 'ErrorOccurred'})
                output_ = Outputs::ErrorOccurred;
                return State::Error;
            }
            break;
        case State::SamplingTemperature:
            if (ordinal == 1) {
                return State::Error;
            }
            if (ordinal == 2) { 
                // cpp_action(interface, {'output': 'SampledTemperature'})
                output_ = Outputs::SampledTemperature;
                return State::Waiting;
            }
            if (ordinal == 3) { 
                // cpp_action(interface, {'output': 'ErrorOccurred'})
                output_ = Outputs::ErrorOccurred;
                return State::Error;
            }
            break;
        case State::Error:
            if (ordinal == 1) {
                return State::Configuring;
            }
            break;
        default:
            // Undefined or Final is not allowed!
            break;
    }
    // if the state not take, return from where you came
    return from;
}

void StateChart::OnExit() {
    // cpp_action(interface, None)
    // do nothing
}

//=== SubStates ===//
ConfiguringSubState::ConfiguringSubState(StateChart& parent, State parent_state)
    : core::StateChart<State>{static_cast<core::StateChart<State>::Callback&>(*this)}
    , parent_{parent}
    , parent_state_{parent_state}
    {}

void ConfiguringSubState::OnEnter() {
    // cpp_action(interface, None)
    // do nothing
}

void ConfiguringSubState::OnExit() {
    // cpp_action(interface, None)
    // do nothing
}

void ConfiguringSubState::OnEntry(State state) {
    switch (state) {
        case State::SampleRate:
            // cpp_action(interface, {'call': {'name': 'WriteSampleRate', 'parameters': 'void', 'assign': 'status_'}})
            ;
            break;
        case State::ScaleRange:
            // cpp_action(interface, {'call': {'name': 'WriteScaleRange', 'parameters': 'void', 'assign': 'status_'}})
            ;
            break;
        case State::Enabled:
            // cpp_action(interface, {'call': {'name': 'WriteEnabled', 'parameters': 'void', 'assign': 'status_'}})
            ;
            break;
        default:
            // Undefined or Final is not allowed!
            break;
    }
}

void ConfiguringSubState::OnCycle(State state) {
    switch (state) {
        case State::SampleRate:
            // cpp_action(interface, None)
            // do nothing
            break;
        case State::ScaleRange:
            // cpp_action(interface, None)
            // do nothing
            break;
        case State::Enabled:
            // cpp_action(interface, None)
            // do nothing
            break;
        default:
            // Undefined or Final is not allowed!
            break;
    }
}
void ConfiguringSubState::OnExit(State state) {
    switch (state) {
        case State::SampleRate:
            // cpp_action(interface, None)
            // do nothing
            break;
        case State::ScaleRange:
            // cpp_action(interface, None)
            // do nothing
            break;
        case State::Enabled:
            // cpp_action(interface, None)
            // do nothing
            break;
        default:
            // Undefined or Final is not allowed!
            break;
    }
}

StateChart::Ordinal ConfiguringSubState::OnGuard(State state) const {
    static_cast<void>(state); // suppress unused parameter warning
    return 0;
}

State ConfiguringSubState::OnTransition(State from, StateChart::Ordinal ordinal) {
    static_cast<void>(from); // suppress unused parameter warning
    static_cast<void>(ordinal); // suppress unused parameter warning
    ordinal = 0; // not allowed
    return from;
}

} // namespace jarnax::drivers::lsm9ds1
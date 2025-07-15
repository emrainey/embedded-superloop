#ifndef TEST_USART_HPP
#define TEST_USART_HPP

#include <memory.hpp>
#include "jarnax/CountDown.hpp"
#include "jarnax/Loopable.hpp"
#include "jarnax/Timer.hpp"
#include "jarnax/Ticker.hpp"
#include "jarnax/Indicator.hpp"
#include "jarnax/Copier.hpp"
#include "jarnax/usart/Driver.hpp"
#include "jarnax/RandomNumberGenerator.hpp"
#include "core/StateMachine.hpp"
#include "core/Allocator.hpp"

using jarnax::Loopable;
using jarnax::LoopInfo;
using jarnax::Ticks;

enum class AppState : std::uint8_t {
    Undefined = 0U,
    Idle,
    Quote1,
    Speech,
    Error,
};

class UsartTest final : public jarnax::Loopable, protected core::StateMachine<AppState>::Callback {
public:
    UsartTest();
    bool Execute() override;

protected:
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    void OnEnter() override;
    void OnEntry(AppState state) override;
    AppState OnCycle(AppState state) override;
    void OnExit(AppState state) override;
    void OnTransition(AppState from, AppState to) override;
    void OnExit() override;
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    /// @brief Reference to the ticker
    jarnax::Ticker& ticker_;
    /// @brief Reference to the timer
    jarnax::Timer& timer_;
    /// @brief The reference to the USART driver
    jarnax::usart::Driver& usart_driver_;
    /// @brief The random number generator
    jarnax::RandomNumberGenerator& rng_;
    /// @brief The number of milliseconds to wait before switching states
    core::units::MilliSeconds countdown_time_msec_;
    /// @brief The number of iotas to wait before switching states
    core::units::Iota countdown_time_iotas_;
    /// @brief Our Countdown for looping the state machine
    jarnax::CountDown countdown_;
    /// @brief The number of dots for idle
    size_t idle_counter_;
    /// @brief The UsartTest State Machine
    core::StateMachine<AppState> state_machine_;
    /// @brief The index that the speech is on
    size_t speech_index_;
    bool delivered_;
};

#endif    // TEST_USART_HPP

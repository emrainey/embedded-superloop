#ifndef TEST_TIMERS_HPP
#define TEST_TIMERS_HPP

#include <memory.hpp>
#include "BoardContext.hpp"
#include "jarnax/CountDown.hpp"
#include "jarnax/Loopable.hpp"
#include "jarnax/Timer.hpp"
#include "jarnax/Ticker.hpp"
#include "jarnax/Indicator.hpp"
#include "jarnax/Copier.hpp"
#include "jarnax/i2c/Driver.hpp"
#include "core/Allocator.hpp"
#include "ssd1306.hpp"

using jarnax::Loopable;
using jarnax::LoopInfo;
using jarnax::Ticks;

enum class AppState : std::uint8_t {
    Undefined = 0U,
    High,
    Low,
};

class TimerTest final : public jarnax::Loopable, protected core::StateMachine<AppState>::Callback {
public:
    TimerTest();
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
    /// @brief Reference to the GPIO for measurement externally
    jarnax::Indicator& indicator_;
    /// @brief The number of milliseconds to wait before switching states
    core::units::MilliSeconds countdown_time_msec_;
    /// @brief The number of iotas to wait before switching states
    core::units::Iota countdown_time_iotas_;
    /// @brief Our Countdown for looping the state machine
    jarnax::CountDown countdown_;
    /// @brief The last value of the Timer
    core::units::Iota last_value_;
    /// @brief The TimerTest State Machine
    core::StateMachine<AppState> state_machine_;
};

#endif    // TEST_TIMERS_HPP

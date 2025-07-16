#ifndef TEST_I2C_HPP
#define TEST_I2C_HPP

#include <memory.hpp>
#include "BoardContext.hpp"
#include "jarnax/CountDown.hpp"
#include "jarnax/Loopable.hpp"
#include "jarnax/Timer.hpp"
#include "jarnax/Ticker.hpp"
#include "jarnax/Indicator.hpp"
#include "jarnax/Copier.hpp"
#include "jarnax/i2c/Driver.hpp"
#include "jarnax/drivers/ssd1306/Driver.hpp"
#include "core/Allocator.hpp"
#include "ssd1306.hpp"

using jarnax::Loopable;
using jarnax::LoopInfo;
using jarnax::Ticks;

enum class AppState : std::uint8_t {
    Undefined = 0U,
    Waiting,           ///< Waits for the display to be ready
    DisplayPowerOn,    ///< Displays Power On message
    Pattern1,
    Pattern2,
    Pattern3,
    Pattern4,
    Pattern5,
    Pattern6,           ///< Displays a pattern on the screen
    DisplayPowerOff,    ///< Displays Power Off message
    Error,
};

class DisplayTest final : public jarnax::Loopable, protected core::StateMachine<AppState>::Callback {
public:
    DisplayTest(jarnax::drivers::ssd1306::Driver& driver);
    bool Execute() override;

protected:
    void InitializeTransaction(void);

    void OnEnter() override;
    void OnEntry(AppState state) override;
    AppState OnCycle(AppState state) override;
    void OnExit(AppState state) override;
    void OnTransition(AppState from, AppState to) override;
    void OnExit() override;

    core::Status TransactionCycle(ssd1306::Command command);

    jarnax::Ticker& ticker_;
    jarnax::Timer& timer_;
    jarnax::drivers::ssd1306::Driver& display_driver_;
    core::units::MicroSeconds change_duration_;
    core::units::Iota change_duration_iota_;
    jarnax::CountDown countdown_;    ///< Countdown timer for state transitions
    core::StateMachine<AppState> state_machine_;
};

#endif    // TEST_I2C_HPP

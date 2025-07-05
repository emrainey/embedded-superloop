#ifndef TEST_I2C_HPP
#define TEST_I2C_HPP

#include <memory.hpp>
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
    StartUp,
    DisplayOn,
    DisplayOff,
    Waiting,
    Error,
};

class I2CTest final : public jarnax::Loopable, protected core::StateMachine<AppState>::Callback {
public:
    I2CTest();
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
    jarnax::i2c::Driver& i2c_driver_;
    jarnax::i2c::Transaction i2c_transaction_;
    core::Buffer<jarnax::i2c::DataUnit> i2c_buffer_;
    jarnax::CountDown i2c_countdown_;
    core::StateMachine<AppState> state_machine_;
};

#endif    // TEST_I2C_HPP

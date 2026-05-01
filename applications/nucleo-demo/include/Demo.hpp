#ifndef APP_DEMO_HPP
#define APP_DEMO_HPP

#include <memory.hpp>
#include "BoardContext.hpp"
#include "core/Allocator.hpp"
#include "jarnax/Button.hpp"
#include "jarnax/Copier.hpp"
#include "jarnax/CountDown.hpp"
#include "jarnax/Indicator.hpp"
#include "jarnax/Loopable.hpp"
#include "jarnax/RandomNumberGenerator.hpp"
#include "jarnax/Ticker.hpp"
#include "jarnax/Timer.hpp"
#include "jarnax/i2c/Driver.hpp"
#include "jarnax/usart/Driver.hpp"

using jarnax::Loopable;
using jarnax::LoopInfo;
using jarnax::Ticks;

enum class DemoState : std::uint8_t {
    Undefined = 0U,
    StartUp,
    KeyLoop,
    CopierTest,
    Idle,
    Error,
};

class Demo final : public jarnax::Loopable, protected core::StateMachine<DemoState>::Callback {
public:
    Demo();
    bool Execute() override;

protected:
    void InitializeTransaction(void);
    void KeyLoop(void);
    void CopierTest(void);
    void TestI2C(void);

    void OnEnter() override;
    void OnEntry(DemoState state) override;
    DemoState OnCycle(DemoState state) override;
    void OnExit(DemoState state) override;
    void OnTransition(DemoState from, DemoState to) override;
    void OnExit() override;

    jarnax::Ticker& ticker_;
    jarnax::Timer const& timer_;
    jarnax::usart::Driver& usart_driver_;
    jarnax::RandomNumberGenerator& rng_;
    jarnax::Indicator& error_indicator_;
    jarnax::Button& user_button_;
    jarnax::Copier& copier_;
    jarnax::CountDown countdown_;

    uint8_t buffer_one_[256U];
    uint8_t buffer_two_[256U];
    bool buffer_test_{false};
    core::StateMachine<DemoState> state_machine_;
};

#endif    // APP_DEMO_HPP

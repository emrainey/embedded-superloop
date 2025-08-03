#ifndef TEST_LPS35HW_HPP
#define TEST_LPS35HW_HPP

#include <memory.hpp>
#include "BoardContext.hpp"
#include "core/Allocator.hpp"
#include "jarnax/Copier.hpp"
#include "jarnax/CountDown.hpp"
#include "jarnax/Loopable.hpp"
#include "jarnax/Ticker.hpp"
#include "jarnax/Timer.hpp"
#include "jarnax/i2c/Driver.hpp"
#include "jarnax/lps35hw/Driver.hpp"
#include "ssd1306.hpp"

using jarnax::Loopable;
using jarnax::LoopInfo;
using jarnax::Ticks;

enum class AppState : std::uint8_t {
    Undefined = 0U,
    Idle,
};

class LPS35HWTest final : public jarnax::Loopable, protected core::StateMachine<AppState>::Callback {
public:
    LPS35HWTest();
    bool Execute() override;

protected:
    void OnEnter() override;
    void OnEntry(AppState state) override;
    AppState OnCycle(AppState state) override;
    void OnExit(AppState state) override;
    void OnTransition(AppState from, AppState to) override;
    void OnExit() override;

    core::StateMachine<AppState> state_machine_;
    jarnax::lps35hw::Driver& lps35hw_driver_;
    jarnax::CountDown countdown_;
};

#endif    // TEST_LPS35HW_HPP

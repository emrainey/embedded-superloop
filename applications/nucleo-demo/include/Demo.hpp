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
#include "jarnax/net/Interface.hpp"
#include "jarnax/net/ethernet/Driver.hpp"
#include "jarnax/usart/Driver.hpp"

using jarnax::Loopable;
using jarnax::LoopInfo;
using jarnax::Ticks;

/// Inputs to the State Chart
enum class Inputs : std::uint8_t {
    None = 0U,
    UserButtonPressed,
    UserButtonReleased,
};

/// Outputs from the State Chart
enum class Outputs : std::uint8_t {
    None = 0U,
    ErrorIndicatorActive,
    ErrorIndicatorInactive,
};

/// States of the Demonstration
enum class DemoState : std::uint8_t {
    Undefined = 0U,
    StartUp,
    Idle,
    Next,
    Error,
    Final,
};

class Demo final : public jarnax::Loopable, protected core::StateChart<DemoState>::Callback {
public:
    /// The ordinal type used by the state chart.
    using Ordinal = core::StateChart<DemoState>::Ordinal;

    /// The constructor for the Demonstration
    Demo(jarnax::Ticker& ticker, jarnax::BoardContext& board_context, jarnax::net::Interface& network_interface);

    //+=== Loopable Override ===+//
    bool Execute() override;

protected:
    //+=== StateChart Callback Overrides ===+//
    void OnEnter() override;
    void OnEntry(DemoState state) override;
    void OnCycle(DemoState state) override;
    void OnExit(DemoState state) override;
    Ordinal OnGuard(DemoState state) const override;
    DemoState OnTransition(DemoState from, Ordinal ordinal) override;
    void OnExit() override;
    //+======================================//

    jarnax::Ticker& ticker_;
    jarnax::Timer const& timer_;
    jarnax::usart::Driver& usart_driver_;
    jarnax::RandomNumberGenerator& rng_;
    jarnax::net::ethernet::Driver& ethernet_driver_;
    jarnax::Indicator& error_indicator_;
    jarnax::Button& user_button_;
    jarnax::net::Interface& network_interface_;
    jarnax::CountDown countdown_;
    core::StateChart<DemoState> state_chart_;
    Inputs inputs_;
    bool button_was_pressed_;
    Outputs outputs_;
};

#endif    // APP_DEMO_HPP

#ifndef APP_DEMO_HPP
#define APP_DEMO_HPP

#include <memory.hpp>
#include "jarnax/CountDown.hpp"
#include "jarnax/Loopable.hpp"
#include "jarnax/Timer.hpp"
#include "jarnax/Ticker.hpp"
#include "jarnax/RandomNumberGenerator.hpp"
#include "jarnax/Indicator.hpp"
#include "jarnax/Button.hpp"
#include "jarnax/Copier.hpp"
#include "jarnax/winbond/Driver.hpp"
#include "core/Allocator.hpp"

using jarnax::Loopable;
using jarnax::LoopInfo;
using jarnax::Ticks;

class Demo final : public jarnax::Loopable {
public:
    Demo();
    void DelayForTicks(Ticks ticks);
    bool Execute() override;

protected:
    void InitializeTransaction(void);
    void KeyLoop(void);
    void CopierTest(void);

    jarnax::Ticker& ticker_;
    jarnax::Timer& timer_;
    jarnax::RandomNumberGenerator& rng_;
    jarnax::Indicator& error_indicator_;
    jarnax::Indicator& status_indicator_;
    jarnax::Button& wakeup_button_;
    jarnax::Button& key0_button_;
    jarnax::Button& key1_button_;
    jarnax::Copier& copier_;
    jarnax::winbond::Driver& winbond_driver_;

    jarnax::CountDown countdown_;

    uint8_t buffer_one_[256U];
    uint8_t buffer_two_[256U];
    bool buffer_test_{false};
};

#endif    // APP_DEMO_HPP

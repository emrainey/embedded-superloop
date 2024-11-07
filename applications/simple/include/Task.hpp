#ifndef APP_TASK_HPP
#define APP_TASK_HPP

#include "jarnax.hpp"
#include "jarnax/RandomNumberGenerator.hpp"

using jarnax::Executable;
using jarnax::LoopInfo;
using jarnax::Ticks;

class Task final : public jarnax::Executable {
public:
    Task();
    void DelayForTicks(Ticks ticks);
    bool Execute(LoopInfo const& metadata) override;

protected:
    jarnax::Ticker& ticker_;
    jarnax::Timer& timer_;
    jarnax::RandomNumberGenerator& rng_;
    jarnax::Indicator& error_indicator_;
    jarnax::Indicator& status_indicator_;
    jarnax::Button& wakeup_button_;
    jarnax::Button& key0_button_;
    jarnax::Button& key1_button_;
};

#endif    // APP_TASK_HPP

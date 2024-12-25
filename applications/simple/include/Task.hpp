#ifndef APP_TASK_HPP
#define APP_TASK_HPP

#include "jarnax.hpp"
#include "jarnax/RandomNumberGenerator.hpp"

using jarnax::Loopable;
using jarnax::LoopInfo;
using jarnax::Ticks;

class Task final : public jarnax::Loopable {
public:
    Task();
    void DelayForTicks(Ticks ticks);
    bool Execute() override;

protected:
    jarnax::Ticker& ticker_;
    jarnax::Timer& timer_;
    jarnax::RandomNumberGenerator& rng_;
    jarnax::Indicator& error_indicator_;
    jarnax::Indicator& status_indicator_;
    jarnax::Button& wakeup_button_;
    jarnax::Button& key0_button_;
    jarnax::Button& key1_button_;
    jarnax::Copier& copier_;

    uint8_t buffer_one_[256U];
    uint8_t buffer_two_[256U];

    core::Buffer<jarnax::spi::DataUnit> spi_buffer_;
    jarnax::spi::Transaction spi_transaction_;
};

#endif    // APP_TASK_HPP

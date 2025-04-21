#ifndef APP_DEMO_HPP
#define APP_DEMO_HPP

#include "jarnax.hpp"
#include "jarnax/CountDown.hpp"

using jarnax::Loopable;
using jarnax::LoopInfo;
using jarnax::Ticks;

class Demo final : public jarnax::Loopable {
public:
    Demo();
    void DelayForTicks(Ticks ticks);
    bool Execute() override;

protected:
    void ResetTransaction(void);

    jarnax::Ticker& ticker_;
    jarnax::Timer& timer_;
    jarnax::RandomNumberGenerator& rng_;
    jarnax::Indicator& error_indicator_;
    jarnax::Indicator& status_indicator_;
    jarnax::Button& wakeup_button_;
    jarnax::Button& key0_button_;
    jarnax::Button& key1_button_;
    jarnax::Copier& copier_;

    jarnax::CountDown countdown_;

    uint8_t buffer_one_[256U];
    uint8_t buffer_two_[256U];

    jarnax::gpio::Output& flash_cs_;
    size_t spi_buffer_count_;
    core::Buffer<jarnax::spi::DataUnit> spi_buffer_;
    jarnax::spi::Transaction spi_transaction_;
    jarnax::spi::Driver& spi_driver_;
};

#endif    // APP_DEMO_HPP

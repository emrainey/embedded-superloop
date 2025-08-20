#ifndef TEST_LPS35HW_HPP
#define TEST_LPS35HW_HPP

#include <memory.hpp>
#include "BoardContext.hpp"
#include "core/Allocator.hpp"
#include "cortex/semihosting.hpp"
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

class DebugTest final : public jarnax::Loopable {
public:
    DebugTest();
    bool Execute() override;

protected:
    jarnax::CountDown countdown_;
    bool one_time_;
    cortex::semihosting::Handle handle_;
    cortex::semihosting::Handle readme_;
    char commandline_[256U];
};

#endif    // TEST_LPS35HW_HPP

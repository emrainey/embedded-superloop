#include "board.hpp"
#include "segger/rtt.hpp"
#include "jarnax.hpp"
#include "stm32/RandomNumberGenerator.hpp"

namespace stm32 {

/// The Clock configuration for this board.
ClockConfiguration const default_clock_configuration = {
    /* .use_internal = */ false,
    /* .use_bypass = */ false,
    /* .ahb_divider = */ 1,
    /* .low_speed_divider = */ 4,
    /* .high_speed_divider = */ 2,
    /* .mcu_clock1_divider = */ 2,
    /* .mcu_clock2_divider = */ 2,
    /* .rtc_divider = */ 8,    // 8Mhz/1Mhz
};

}    // namespace stm32

// Global Drivers
stm32::RandomNumberGenerator rng;

namespace stm32 {
namespace initialize {

void drivers(void) {
    jarnax::Status status;

    // @todo initialize watchdog
    // @todo initialize timer
    // @todo initialize gpio
    // @todo initialize can
    // @todo initialize adc
    status = rng.Initialize();
    if (status) {
        /// success
    }
}

}    // namespace initialize
}    // namespace stm32

namespace jarnax {
void banner(void) {
    jarnax::print(
        "                                                                    \r\n"
        "         _/    _/_/    _/_/_/    _/      _/    _/_/    _/      _/   \r\n"
        "        _/  _/    _/  _/    _/  _/_/    _/  _/    _/    _/  _/      \r\n"
        "       _/  _/_/_/_/  _/_/_/    _/  _/  _/  _/_/_/_/      _/         \r\n"
        "_/    _/  _/    _/  _/    _/  _/    _/_/  _/    _/    _/  _/        \r\n"
        " _/_/    _/    _/  _/    _/  _/      _/  _/    _/  _/      _/       \r\n"
        " -- %s\r\n",
        jarnax::VersionString
    );
}
}    // namespace jarnax
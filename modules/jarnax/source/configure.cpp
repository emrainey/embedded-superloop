#include "segger/rtt.hpp"
#include "jarnax/system.hpp"

namespace rtt {
/// Buffers for RTT[0] "Terminal"
uint8_t upward_buffer[kUpwardBufferSize];
/// Buffers for RTT[0] "Terminal"
uint8_t downward_buffer[kDownwardBufferSize];
/// RTT Control Block
ControlBlock control_block{};
}    // namespace rtt

namespace jarnax {

void configure(void) {
    // initialize the RTT buffers for Terminal
    rtt::control_block.emplace_up("Terminal", sizeof(rtt::upward_buffer), rtt::upward_buffer);
    rtt::control_block.emplace_down("Terminal", sizeof(rtt::downward_buffer), rtt::downward_buffer);

    jarnax::print("Configure...\r\n");
    // each vendors clock tree is a unique and confusing flower, let them deal with it!
    // vendor::initialize::clocks();
    // Get the
    clock_frequency = vendor::GetClockFrequency();
    cortex::initialize::tick(jarnax::ticks_per_second, clock_frequency);

    // TODO enable peripheral clock

    // initialize SWO
    cortex::initialize::swo(jarnax::swo::baudrate, clock_frequency);
    jarnax::print("Booting...\r\n");

    // TODO enable watchdog if you have one

    // TODO initialize the GPIO if you have them
    vendor::initialize::drivers();
}

}    // namespace jarnax

#include "segger/rtt.hpp"
#include "jarnax/system.hpp"

namespace jarnax {

void configure(void) {
    rtt::initialize();
    jarnax::print("Configure...\r\n");
    // each vendors clock tree is a unique and confusing flower, let them deal with it!
    vendor::initialize::clocks();
    jarnax::print("Core Clock Frequency is %lu Hz\r\n", vendor::GetClockFrequency().value());
    jarnax::print("System Clock Frequency is %lu Hz\r\n", vendor::GetSystemClockFrequency().value());
    // Set the clock frequency from the vendor
    cortex::SetClockFrequency(vendor::GetClockFrequency());
    cortex::SetSystemClockFrequency(vendor::GetSystemClockFrequency());
    // initialize the system tick
    jarnax::print("Initializing Tick @ %lu/sec from %lu\r\n", cortex::ticks_per_second.value(), cortex::GetSystemClockFrequency().value());
    cortex::initialize::tick(cortex::ticks_per_second, cortex::GetSystemClockFrequency());
    cortex::initialize::swo(cortex::swo::baudrate, cortex::GetClockFrequency());
    // vendor::initialize::watchdog();
    vendor::initialize::gpio();
    vendor::initialize::drivers();
    // once enabled statically configured drivers can start to receive interrupts
    cortex::initialize::nvic();
    jarnax::print("Configured\r\n");
}

}    // namespace jarnax

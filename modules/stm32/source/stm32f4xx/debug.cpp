
#include "stm32/Initialize.hpp"

namespace stm32 {
namespace initialize {

/// @brief Enables the DBGMCU trace port clocks.
/// @note F4 uses the standard Cortex-M TPIU (driven by the core clock) for SWO, which is
/// configured by cortex::initialize::swo(). No vendor specific trace blocks need clocking.
void enable_trace_port_clock(void) {
}

/// @brief Programs the Serial Wire Output path for UART trace on the SWO pin.
/// @note F4 uses the standard Cortex-M TPIU instead of the ST SWO/SWTF blocks, so this is a no-op.
void enable_serial_wire_output(core::units::Hertz trace_clock, std::uint32_t baud) {
    (void)trace_clock;
    (void)baud;
}

}    // namespace initialize
}    // namespace stm32

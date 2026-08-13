
#include "stm32/Initialize.hpp"
#include "stm32/peripherals.hpp"

namespace stm32 {
namespace initialize {

/// @brief Enables the DBGMCU trace port clocks so the ST trace blocks can drive the SWO pin.
/// @note RM0433 Rev 8 p.3167: TRACECK must be enabled via TRACECLKEN (bit 20) before trace is
/// sent to the trace blocks. D1DBGCKEN (bit 21) keeps the D1 debug components clocked while the
/// D1 core clock is active, and D3DBGCKEN (bit 22) does the same for the D3 domain which holds
/// the SWO (0x5C003000) and SWTF (0x5C004000) blocks.
void enable_trace_port_clock(void) {
    h7xx::Debug::Control control;
    control = h7xx::debug.control;    // read
    control.bits.trace_clock_enable = 1U;            // bit 20 TRACECLKEN
    control.bits.domain1_debug_clock_enable = 1U;    // bit 21 D1DBGCKEN
    control.bits.domain3_debug_clock_enable = 1U;    // bit 22 D3DBGCKEN
    h7xx::debug.control = control;    // write
}

/// @brief Programs the ST Serial Wire Output path (SWO + SWTF) for UART trace on the SWO pin.
/// @param trace_clock The frequency of the trace clock (TRACECK) driving the SWO block.
/// @param baud The desired SWO UART baud rate.
/// @note The Cortex-M7 TPIU (0xE0040000 alias) does not drive the SWO pin on the H7; the ST SWO
/// block (0x5C003000) does, and the SWTF funnel (0x5C004000) must forward the ITM trace bus to it.
void enable_serial_wire_output(core::units::Hertz trace_clock, std::uint32_t baud) {
    // the SWO/SWTF blocks sit in the D3 debug domain, so un-gate all the debug clocks first
    enable_trace_port_clock();

    // unlock the SWO and SWTF blocks
    h7xx::serial_wire_output.lock_access = h7xx::SwoLockValue;
    h7xx::swo_trace_funnel.lock_access = h7xx::SwoTraceFunnelLockValue;

    // configure the SWO block for UART (Async NRZ) mode
    h7xx::serial_wire_output.selected_pin_protocol.bits.transmit_mode = h7xx::Swo::Protocol::AsyncNRZ;
    // set the baud rate divider (zero based): baud = trace_clock / (prescaler + 1).
    // The CODR register only has a 13-bit PRESCALER field; write the whole register with the
    // masked value to avoid GCC -Wconversion on the truncated bitfield.
    h7xx::serial_wire_output.current_output_divisor.whole = ((trace_clock.value() / baud) - 1U) & 0x1FFFU;
    // enable the trace bus from the Cortex-M7 ITM to the SWO block
    h7xx::swo_trace_funnel.control.bits.enable_swo = 1U;
}

}    // namespace initialize
}    // namespace stm32

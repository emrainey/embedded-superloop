#include <cstdint>

#include <gtest/gtest.h>

#include <core/Units.hpp>
#include <jarnax/TestContext.hpp>
#include <stm32/Initialize.hpp>
#include <stm32/h7xx/Debug.hpp>
#include <stm32/h7xx/Swo.hpp>
#include <stm32/h7xx/SwoTraceFunnel.hpp>
#include <stm32/peripherals.hpp>

/// @brief Tests for the H7 trace/SWO enable path (issue-41).
/// @note These tests run against the UNITTEST RAM-backed `stm32::h7xx::debug`,
/// `stm32::h7xx::serial_wire_output` and `stm32::h7xx::swo_trace_funnel` globals so no
/// emulator or target is required.
class DebugTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Reset the registers to their reset values (all zero).
        stm32::h7xx::Debug::Control control;
        control.whole = 0U;
        stm32::h7xx::debug.control = control;
        stm32::h7xx::serial_wire_output.lock_access = 0U;
        stm32::h7xx::serial_wire_output.selected_pin_protocol.whole = 0U;
        stm32::h7xx::serial_wire_output.current_output_divisor.whole = 0U;
        stm32::h7xx::swo_trace_funnel.control.whole = 0U;
        stm32::h7xx::swo_trace_funnel.priority.whole = 0U;
        stm32::h7xx::swo_trace_funnel.lock_access = 0U;
    }
};

/// @brief Empty test to exercise SetUp/Teardown and confirm the registers reset cleanly.
TEST_F(DebugTest, ResetValue) {
    stm32::h7xx::Debug::Control control = stm32::h7xx::debug.control;
    EXPECT_EQ(control.whole, 0U);
    EXPECT_EQ(stm32::h7xx::serial_wire_output.current_output_divisor.whole, 0U);
    EXPECT_EQ(stm32::h7xx::swo_trace_funnel.control.whole, 0U);
}

/// @brief Enabling the trace port clock sets TRACECLKEN (20), D1DBGCKEN (21) and D3DBGCKEN (22).
/// @note D3DBGCKEN un-gates the D3 debug domain which holds the SWO/SWTF blocks on the H7.
TEST_F(DebugTest, EnableTracePortClockSetsExpectedBits) {
    stm32::initialize::enable_trace_port_clock();
    stm32::h7xx::Debug::Control control = stm32::h7xx::debug.control;
    EXPECT_EQ(control.bits.trace_clock_enable, 1U);             // bit 20 TRACECLKEN
    EXPECT_EQ(control.bits.domain1_debug_clock_enable, 1U);     // bit 21 D1DBGCKEN
    EXPECT_EQ(control.bits.domain3_debug_clock_enable, 1U);     // bit 22 D3DBGCKEN
}

/// @brief The enable is a read-modify-write and must preserve unrelated CR bits.
TEST_F(DebugTest, EnableTracePortClockPreservesOtherBits) {
    stm32::h7xx::Debug::Control control;
    control = stm32::h7xx::debug.control;
    control.bits.external_trigger_output_enable = 1U;    // bit 28 TRGOEN, unrelated
    stm32::h7xx::debug.control = control;

    stm32::initialize::enable_trace_port_clock();

    control = stm32::h7xx::debug.control;
    EXPECT_EQ(control.bits.external_trigger_output_enable, 1U);
    EXPECT_EQ(control.bits.trace_clock_enable, 1U);
    EXPECT_EQ(control.bits.domain1_debug_clock_enable, 1U);
    EXPECT_EQ(control.bits.domain3_debug_clock_enable, 1U);
}

/// @brief Calling the enable twice is idempotent.
TEST_F(DebugTest, EnableTracePortClockIsIdempotent) {
    stm32::initialize::enable_trace_port_clock();
    stm32::initialize::enable_trace_port_clock();
    stm32::h7xx::Debug::Control control = stm32::h7xx::debug.control;
    EXPECT_EQ(control.whole, (1U << 20U) | (1U << 21U) | (1U << 22U));
}

/// @brief Enabling the serial wire output also enables all of the trace port clocks.
TEST_F(DebugTest, EnableSerialWireOutputEnablesTracePortClocks) {
    stm32::initialize::enable_serial_wire_output(core::units::Hertz{100'000'000U}, 2'240'000U);
    stm32::h7xx::Debug::Control control = stm32::h7xx::debug.control;
    EXPECT_EQ(control.bits.trace_clock_enable, 1U);
    EXPECT_EQ(control.bits.domain1_debug_clock_enable, 1U);
    EXPECT_EQ(control.bits.domain3_debug_clock_enable, 1U);
}

/// @brief The SWO and SWTF blocks are unlocked with the CoreSight key.
TEST_F(DebugTest, EnableSerialWireOutputUnlocksBlocks) {
    stm32::initialize::enable_serial_wire_output(core::units::Hertz{100'000'000U}, 2'240'000U);
    EXPECT_EQ(stm32::h7xx::serial_wire_output.lock_access, 0xC5ACCE55U);
    EXPECT_EQ(stm32::h7xx::swo_trace_funnel.lock_access, 0xC5ACCE55U);
}

/// @brief The SWO block is configured for UART (Async NRZ) mode.
TEST_F(DebugTest, EnableSerialWireOutputSetsUartProtocol) {
    stm32::initialize::enable_serial_wire_output(core::units::Hertz{100'000'000U}, 2'240'000U);
    std::uint32_t whole = stm32::h7xx::serial_wire_output.selected_pin_protocol.whole;
    EXPECT_EQ(whole & 0x3U, static_cast<std::uint32_t>(stm32::h7xx::Swo::Protocol::AsyncNRZ));
}

/// @brief The CODR prescaler is zero based: prescaler = (trace_clock / baud) - 1.
TEST_F(DebugTest, EnableSerialWireOutputSetsBaudDivider) {
    stm32::initialize::enable_serial_wire_output(core::units::Hertz{100'000'000U}, 4'000'000U);
    std::uint32_t whole = stm32::h7xx::serial_wire_output.current_output_divisor.whole;
    EXPECT_EQ(whole & 0x1FFFU, 100'000'000U / 4'000'000U - 1U);    // 24
}

/// @brief The CODR prescaler for the default 2.24 MBaud config is 43.
TEST_F(DebugTest, EnableSerialWireOutputSetsDefaultBaudDivider) {
    stm32::initialize::enable_serial_wire_output(core::units::Hertz{100'000'000U}, 2'240'000U);
    std::uint32_t whole = stm32::h7xx::serial_wire_output.current_output_divisor.whole;
    EXPECT_EQ(whole & 0x1FFFU, 100'000'000U / 2'240'000U - 1U);    // 43
}

/// @brief The SWTF funnel is enabled so the ITM trace bus reaches the SWO block.
TEST_F(DebugTest, EnableSerialWireOutputEnablesFunnel) {
    stm32::initialize::enable_serial_wire_output(core::units::Hertz{100'000'000U}, 2'240'000U);
    std::uint32_t whole = stm32::h7xx::swo_trace_funnel.control.whole;
    EXPECT_EQ(whole & 0x1U, 1U);    // ENSO
}

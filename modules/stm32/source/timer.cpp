#include "board.hpp"
#include "cortex/nvic.hpp"
#include "jarnax/print.hpp"
#include "stm32/registers/Timer2.hpp"
#include "stm32/registers/Debug.hpp"
#include "stm32/Timer.hpp"
#include "stm32/registers/ResetAndClockControl.hpp"

namespace stm32 {
/// Holds the high order bits for the TIMER2 counter
std::uint32_t volatile timer2_high_order_bits{0U};

/// Called by Hardware when the TIMER2 counter overflows
__attribute__((used)) void timer2_isr(void) {
    // read a copy of the high order bits
    std::uint32_t count = timer2_high_order_bits;

    stm32::registers::Timer2::Status status;
    status = stm32::registers::timer2.status;    // read
    status.bits.update_interrupt = 0U;           // clear the update flag
    stm32::registers::timer2.status = status;    // write

    // store the update
    timer2_high_order_bits = count + 1U;

    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::Timer2)]++;
}

Timer::Timer(stm32::registers::Timer2 volatile& timer)
    : timer_{timer} {
}

core::Status Timer::Initialize(core::units::Hertz internal_clock, core::units::Hertz desired_timer_frequency) {
    stm32::registers::Timer2::Control1 control1;

    // disable the timer
    control1 = timer_.control1;    // read
    control1.bits.enable = 0U;     // disable
    timer_.control1 = control1;    // write

    // configure the timer
    control1.bits.direction = 0U;                     // upcounting
    control1.bits.one_pulse_mode = 0U;                // continuous mode
    control1.bits.auto_reload_preload_enable = 0U;    // disable auto-reload preload
    control1.bits.update_request_source = 1U;         // only counter overflow/underflow generates an update interrupt
    timer_.control1 = control1;                       // write

    // set the prescaler for a MicroSecond clock
    std::uint32_t prescalar = (internal_clock.value() / desired_timer_frequency.value()) - 1U;
    timer_.prescalar = prescalar;
    timer_.auto_reload = 0xFF'FF'FF'FFU;    // it's disabled, but we set it to the maximum value
    jarnax::print(
        "Timer::Initialize: CLK: %lu Hz, Desired: %lu Hz => Prescalar is %lu. Auto Reload is %lu\r\n",
        static_cast<unsigned long>(internal_clock.value()),
        static_cast<unsigned long>(desired_timer_frequency.value()),
        static_cast<unsigned long>(prescalar + 1U),
        static_cast<unsigned long>(timer_.auto_reload.whole)
    );

    // enable the update event
    stm32::registers::Timer2::EventGeneration event_generation;
    event_generation = timer_.event_generation;      // read
    event_generation.bits.update_generation = 1U;    // enable
    timer_.event_generation = event_generation;      // write

    stm32::registers::Timer2::DmaInterruptEnable dma_interrupt;
    dma_interrupt = timer_.dma_interrupt;    // read
    dma_interrupt.bits.update = 0U;          // disable
    timer_.dma_interrupt = dma_interrupt;    // write

    // stop the timer while we're in debug mode
    stm32::registers::Debug::DebugMcu_APB1_Freeze debug_mcu_apb1_freeze;
    debug_mcu_apb1_freeze = stm32::registers::debug.dbgmcu_apb1_freeze;    // read
    debug_mcu_apb1_freeze.bits.dbg_tim2_stop = 1U;                         // stop
    stm32::registers::debug.dbgmcu_apb1_freeze = debug_mcu_apb1_freeze;    // write

    // initialize the high order bits
    timer2_high_order_bits = 0U;

    // enable the timer
    control1.bits.enable = 1U;     // enable
    timer_.control1 = control1;    // write

    return core::Status{core::Result::Success, core::Cause::Unknown};
}

core::units::Iota Timer::GetIotas(void) const {
    // read the high order bits once
    std::uint32_t high_order_bits;
    std::uint32_t low_order_bits;
    do {
        // read the high order bits again
        high_order_bits = timer2_high_order_bits;
        // read the low order bits
        low_order_bits = timer_.counter.whole;
    } while (high_order_bits != timer2_high_order_bits);
    std::uint64_t value = std::uint64_t(high_order_bits) << 32U | std::uint64_t(low_order_bits);
    return core::units::Iota{value};
}

core::units::MicroSeconds Timer::GetMicroseconds(void) const {
    auto iotas = GetIotas();
    return core::units::ConvertToMicroSeconds(iotas);
}

core::units::Seconds Timer::GetSeconds(void) const {
    auto iotas = GetIotas();
    return core::units::ConvertToSeconds(iotas);
}

}    // namespace stm32

namespace jarnax {
Timer& GetTimer(void) {
    static stm32::Timer timer{stm32::registers::timer2};
    return timer;
}
}    // namespace jarnax

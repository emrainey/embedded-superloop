#include "board.hpp"
#include "cortex/nvic.hpp"
#include "stm32/registers/Timer2.hpp"
#include "stm32/registers/Debug.hpp"
#include "stm32/Timer.hpp"
#include "stm32/registers/ResetAndClockControl.hpp"

namespace core {
namespace units {

constexpr MicroSeconds ConvertToMicroSeconds(Iota const& value) {
    MicroSeconds::StorageType v = static_cast<MicroSeconds::StorageType>(value.value() / static_cast<Iota::StorageType>(stm32::iota_per_microsecond));
    return MicroSeconds{v};
}
}    // namespace units
}    // namespace core

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
}

Timer::Timer(stm32::registers::Timer2 volatile& timer)
    : timer_{timer} {
}

core::Status Timer::Initialize(core::units::Hertz internal_clock) {

    // enable clock (from APB1) for Timer2
    stm32::registers::ResetAndClockControl::APB1PeripheralClockEnable config;
    config = registers::reset_and_clock_control.apb1_peripheral_clock_enable;    // read
    config.bits.tim2en = 1U;
    registers::reset_and_clock_control.apb1_peripheral_clock_enable = config;    // write

    stm32::registers::Timer2::Control1 control1;

    // disable the timer
    control1 = timer_.control1;    // read
    control1.bits.enable = 0U;     // disable
    timer_.control1 = control1;    // write

    // configure the timer
    control1.bits.direction = 1U;       // downcounting
    control1.bits.one_pulse_mode = 0U;  // continuous mode
    control1.bits.auto_reload_preload_enable = 0U; // disable auto-reload preload
    control1.bits.update_request_source = 1U;      // only counter overflow/underflow generates an update interrupt
    timer_.control1 = control1;         // write

    // set the prescaler for a MicroSecond clock
    std::uint32_t prescalar = (internal_clock.value() / 1000000U) - 1U;
    timer_.prescalar = prescalar;
    timer_.auto_reload = internal_clock.value() / (prescalar + 1U); // should interrupt 1/sec

    // enable the update event
    stm32::registers::Timer2::EventGeneration event_generation;
    event_generation = timer_.event_generation;    // read
    event_generation.bits.update_generation = 1U;  // enable
    timer_.event_generation = event_generation;    // write

    stm32::registers::Timer2::DmaInterruptEnable  dma_interrupt;
    dma_interrupt = timer_.dma_interrupt;    // read
    dma_interrupt.bits.update = 1U;          // enable
    timer_.dma_interrupt = dma_interrupt;    // write

    // stop the timer while we're in debug mode
    stm32::registers::Debug::DebugMcu_APB1_Freeze debug_mcu_apb1_freeze;
    debug_mcu_apb1_freeze = stm32::registers::debug.dbgmcu_apb1_freeze;    // read
    debug_mcu_apb1_freeze.bits.dbg_tim2_stop = 1U;                   // stop
    stm32::registers::debug.dbgmcu_apb1_freeze = debug_mcu_apb1_freeze;    // write

    // initialize the high order bits
    timer2_high_order_bits = 0U;

    // enable the timer
    control1.bits.enable = 1U;  // enable
    timer_.control1 = control1; // write


    return core::Status{core::Result::Success, core::Cause::Unknown};
}

core::units::Iota Timer::GetIotas(void) const {
    // read the high order bits once
    std::uint32_t high_order_bits;
    std::uint32_t high_order_bits2;
    std::uint32_t low_order_bits;
    do {
        // read the high order bits again
        high_order_bits = timer2_high_order_bits;
        // read the low order bits
        low_order_bits = timer_.counter.whole;
    } while (high_order_bits != timer2_high_order_bits);
    std::uint64_t value = std::uint64_t(high_order_bits) << 32U | low_order_bits;
    return core::units::Iota{value};
}

core::units::MicroSeconds Timer::GetMicroseconds(void) const {
    auto iotas = GetIotas();
    return core::units::ConvertToMicroSeconds(iotas);
}

}    // namespace stm32

namespace jarnax {
Timer& GetTimer(void) {
    static stm32::Timer timer{stm32::registers::timer2};
    return timer;
}
}    // namespace jarnax

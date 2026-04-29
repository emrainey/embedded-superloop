//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#include "cortex/vectors.hpp"
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#include "jarnax/print.hpp"
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#include "core/Conversions.hpp"
#include "stm32/Timer.hpp"
#include "stm32/stm32.hpp"

namespace core {
namespace units {
// Holds the global values for the Conversion to and From Iotas
std::uint32_t time_source_iotas_per_second{0U};
std::uint32_t time_source_iotas_per_millisecond{0U};
std::uint32_t time_source_iotas_per_microsecond{0U};
}    // namespace units
}    // namespace core

namespace stm32 {
// Holds the high order bits for the TIMER2 counter
std::uint32_t volatile timer2_high_order_bits{0U};

/// Called by Hardware when the TIMER2 counter overflows
USED void timer2_isr(void) {
    // read a copy of the high order bits
    std::uint32_t count = timer2_high_order_bits;

    stm32::peripherals::Timer2::Status status;
    status = stm32::peripherals::timer2.status;    // read
    status.bits.update_interrupt = 0U;             // clear the update flag
    stm32::peripherals::timer2.status = status;    // write

    // store the update
    timer2_high_order_bits = count + 1U;

    cortex::extended_vector_statistics.count[polyfill::to_underlying(stm32::InterruptRequest::Timer2)]++;
}

Timer::Timer(stm32::peripherals::Timer2 volatile& timer)
    : timer_{timer}
    , reload_value_{0U}
    , initialized_{false} {}

core::Status Timer::Initialize(core::units::Hertz internal_clock, core::units::Hertz desired_timer_frequency) {
    stm32::peripherals::Timer2::Control1 control1;

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
    reload_value_ = desired_timer_frequency.value();    // number of counts per second
    timer_.auto_reload = reload_value_;
    core::units::time_source_iotas_per_second = desired_timer_frequency.value() / (1U * iso::prefix::none);
    core::units::time_source_iotas_per_millisecond = desired_timer_frequency.value() / (1U * iso::prefix::kilo);
    core::units::time_source_iotas_per_microsecond = desired_timer_frequency.value() / (1U * iso::prefix::mega);
    jarnax::print(
        "Timer::Initialize: CLK: %" PRIu32 " Hz, Desired: %" PRIu32 " Hz => Prescalar is %" PRIu32 ". Auto Reload is %" PRIu32 " (Sec: %" PRIu32
        ", Millis: %" PRIu32 ", Micro: %" PRIu32 ")\r\n",
        internal_clock.value(),
        desired_timer_frequency.value(),
        prescalar + 1U,
        timer_.auto_reload.whole,
        core::units::time_source_iotas_per_second,
        core::units::time_source_iotas_per_millisecond,
        core::units::time_source_iotas_per_microsecond
    );

    // enable the update event
    stm32::peripherals::Timer2::EventGeneration event_generation;
    event_generation = timer_.event_generation;      // read
    event_generation.bits.update_generation = 1U;    // enable
    timer_.event_generation = event_generation;      // write

    stm32::peripherals::Timer2::DmaInterruptEnable dma_interrupt;
    dma_interrupt = timer_.dma_interrupt;    // read
    dma_interrupt.bits.update = 1U;          // enable
    timer_.dma_interrupt = dma_interrupt;    // write

    // stop the timer while we're in debug mode
    stm32::peripherals::Debug::DebugMcu_APB1_Freeze debug_mcu_apb1_freeze;
    debug_mcu_apb1_freeze = stm32::peripherals::debug.dbgmcu_apb1_freeze;    // read
    debug_mcu_apb1_freeze.bits.dbg_tim2_stop = 1U;                           // stop
    stm32::peripherals::debug.dbgmcu_apb1_freeze = debug_mcu_apb1_freeze;    // write

    // initialize the high order bits
    timer2_high_order_bits = 0U;

    // enable the timer
    control1.bits.enable = 1U;     // enable
    timer_.control1 = control1;    // write
    initialized_ = true;

    return core::Status{core::Result::Success, core::Cause::Unknown};
}

core::units::Iota Timer::GetIotas(void) const {
    if (not initialized_) {
        return core::units::Iota{0U};
    }
    // read the high order bits once
    std::uint32_t high_order_bits;
    std::uint32_t low_order_bits;
    do {
        // read the high order bits again
        high_order_bits = timer2_high_order_bits;
        // read the low order bits
        low_order_bits = timer_.counter.whole;
    } while (high_order_bits != timer2_high_order_bits);
    std::uint64_t value = 0UL;
    if (reload_value_ == 0xFF'FF'FF'FFU) {
        value = std::uint64_t(high_order_bits) << 32U | std::uint64_t(low_order_bits);
    } else {
        value = (std::uint64_t(high_order_bits) * std::uint64_t(reload_value_)) + std::uint64_t(low_order_bits);
    }
    return core::units::Iota{value};
}

core::units::MicroSeconds Timer::GetMicroseconds(void) const {
    if (not initialized_) {
        return core::units::MicroSeconds{0U};
    }
    auto iotas = GetIotas();
    return core::units::ConvertToMicroSeconds(iotas);
}

core::units::Seconds Timer::GetSeconds(void) const {
    if (not initialized_) {
        return core::units::Seconds{0U};
    }
    auto iotas = GetIotas();
    return core::units::ConvertToSeconds(iotas);
}

}    // namespace stm32

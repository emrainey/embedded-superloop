#include "board.hpp"
#include "segger/rtt.hpp"
#include "jarnax.hpp"
#include "strings.hpp"
#include "core/BitMapHeap.hpp"
#include "stm32/RandomNumberGenerator.hpp"
#include "stm32/Timer.hpp"

namespace stm32 {

/// @brief Dedicate a chunk of memory for the DMA buffers
LINKER_SECTION(".dma_buffer") alignas(alignof(std::max_align_t)) static core::Array<uint8_t, DmaBlockSize * DmaBlockCount> dma_memory;
/// @brief Manage the DMA buffers with a bitmap allocator
static core::BitMapHeap<DmaBlockSize, DmaBlockCount> dma_heap_allocator{&dma_memory[0], dma_memory.size()};

/// @brief The Clock configuration for this board.
ClockConfiguration const default_clock_configuration = {
    /* .use_internal = */ false,
    /* .use_bypass = */ false,
    /* .external_clock_frequency */ high_speed_external_oscillator_frequency,
    /* .ahb_divider = */ 0b0000,          // /1
    /* .low_speed_divider = */ 0b101,     // /4
    /* .high_speed_divider = */ 0b100,    // /2
    /* .mcu_clock1_divider = */ 0b111,    // /5
    /* .mcu_clock2_divider = */ 0b111,    // /5
    /* .rtc_divider = */ 8,
    /* .pll_m = */ 8,
    /* .pll_n = */ 336,
    /* .pll_p = */ 0b00,    // /2
    /* .pll_q = */ 7
};

}    // namespace stm32

namespace jarnax {

DriverContext::DriverContext()
    : timer_{stm32::registers::timer2}
    , random_number_generator_{}
    , wakeup_pin_{stm32::gpio::Port::A, 0}
    , mco1_pin_{stm32::gpio::Port::A, 8}
    , mco2_pin_{stm32::gpio::Port::C, 9}
    , key0_pin_{stm32::gpio::Port::E, 4}
    , key1_pin_{stm32::gpio::Port::E, 3}
    , error_pin_{stm32::gpio::Port::A, 6}
    , status_pin_{stm32::gpio::Port::A, 7}
    , error_indicator_{error_pin_, stm32::Level::Low}
    , status_indicator_{status_pin_, stm32::Level::Low}
    , wakeup_button_{wakeup_pin_, true}
    , key0_button_{key0_pin_, false}
    , key1_button_{key1_pin_, false}
    , spi1_mosi_{stm32::gpio::Port::B, 5}
    , spi1_miso_{stm32::gpio::Port::B, 4}
    , spi1_sclk_{stm32::gpio::Port::B, 3}
    , flash_cs_{stm32::gpio::Port::B, 0}
    , nrf_cs_{stm32::gpio::Port::B, 7}
    , nrf_ce_{stm32::gpio::Port::B, 6}
    , nrf_irq_{stm32::gpio::Port::B, 8}
    , dma_driver_{}
    , spi1_driver_{stm32::registers::spi1, dma_driver_, stm32::dma::SPI1_RX, stm32::dma::SPI1_TX}
    , winbond_driver_{timer_, spi1_driver_, flash_cs_, GetDmaAllocator()}
    , usart1_tx_{stm32::gpio::Port::A, 9}
    , usart1_rx_{stm32::gpio::Port::A, 10}
    , usart1_driver_{stm32::registers::usart1, dma_driver_, stm32::dma::USART1_RX, stm32::dma::USART1_TX, GetDmaAllocator()} {
    // construct the driver objects as part of the constructor above.
}

DriverContext::~DriverContext() {
    // destruct the driver objects in the destructor below.
}

core::Status DriverContext::Initialize(void) {
    core::Status status;
    wakeup_pin_.SetMode(stm32::gpio::Mode::Input).SetResistor(stm32::gpio::Resistor::PullDown);
    mco1_pin_.SetOutputSpeed(stm32::gpio::Speed::VeryHigh).SetMode(stm32::gpio::Mode::AlternateFunction).SetAlternative(0);    // Alt 0 is MCO1
    mco2_pin_.SetOutputSpeed(stm32::gpio::Speed::VeryHigh).SetMode(stm32::gpio::Mode::AlternateFunction).SetAlternative(0);    // Alt 0 is MCO2
    key0_pin_.SetMode(stm32::gpio::Mode::Input).SetResistor(stm32::gpio::Resistor::PullUp);
    key1_pin_.SetMode(stm32::gpio::Mode::Input).SetResistor(stm32::gpio::Resistor::PullUp);
    error_pin_.SetMode(stm32::gpio::Mode::Output)
        .SetOutputSpeed(stm32::gpio::Speed::Medium)
        .SetOutputType(stm32::gpio::OutputType::OpenDrain)
        .SetResistor(stm32::gpio::Resistor::None);
    status_pin_.SetMode(stm32::gpio::Mode::Output)
        .SetOutputSpeed(stm32::gpio::Speed::Low)
        .SetOutputType(stm32::gpio::OutputType::OpenDrain)
        .SetResistor(stm32::gpio::Resistor::None);
    error_indicator_.Inactive();
    status_indicator_.Inactive();
    spi1_mosi_.SetMode(stm32::gpio::Mode::AlternateFunction)
        .SetAlternative(5)    // Alt 5 is SPI1
        .SetOutputSpeed(stm32::gpio::Speed::VeryHigh)
        .SetOutputType(stm32::gpio::OutputType::PushPull);
    spi1_miso_.SetMode(stm32::gpio::Mode::AlternateFunction)
        .SetAlternative(5)    // Alt 5 is SPI1
        .SetOutputSpeed(stm32::gpio::Speed::VeryHigh)
        .SetOutputType(stm32::gpio::OutputType::PushPull);
    spi1_sclk_.SetMode(stm32::gpio::Mode::AlternateFunction)
        .SetAlternative(5)    // Alt 5 is SPI1
        .SetOutputSpeed(stm32::gpio::Speed::VeryHigh)
        .SetOutputType(stm32::gpio::OutputType::PushPull);
    flash_cs_.SetMode(stm32::gpio::Mode::Output)
        .SetOutputSpeed(stm32::gpio::Speed::VeryHigh)
        .SetOutputType(stm32::gpio::OutputType::PushPull)
        .SetResistor(stm32::gpio::Resistor::None)
        .Value(true);    // CS is active low
    nrf_cs_.SetMode(stm32::gpio::Mode::Output)
        .SetOutputSpeed(stm32::gpio::Speed::VeryHigh)
        .SetOutputType(stm32::gpio::OutputType::PushPull)
        .SetResistor(stm32::gpio::Resistor::None);
    nrf_ce_.SetMode(stm32::gpio::Mode::Output)
        .SetOutputSpeed(stm32::gpio::Speed::VeryHigh)
        .SetOutputType(stm32::gpio::OutputType::PushPull)
        .SetResistor(stm32::gpio::Resistor::None);
    nrf_irq_.SetMode(stm32::gpio::Mode::Input).SetResistor(stm32::gpio::Resistor::PullUp);
    usart1_tx_.SetMode(stm32::gpio::Mode::AlternateFunction)
        .SetAlternative(7)    // Alt 7 is USART1
        .SetOutputSpeed(stm32::gpio::Speed::High)
        .SetOutputType(stm32::gpio::OutputType::PushPull);
    usart1_rx_.SetMode(stm32::gpio::Mode::AlternateFunction)
        .SetAlternative(7)    // Alt 7 is USART1
        .SetOutputSpeed(stm32::gpio::Speed::High)
        .SetOutputType(stm32::gpio::OutputType::PushPull);

    stm32::registers::ResetAndClockControl::AHB1PeripheralClockEnable ahb1_enable;
    stm32::registers::ResetAndClockControl::AHB2PeripheralClockEnable ahb2_enable;
    stm32::registers::ResetAndClockControl::APB1PeripheralClockEnable apb1_enable;
    stm32::registers::ResetAndClockControl::APB2PeripheralClockEnable apb2_enable;

    // Enable the RNG in the AHB2 Periperhals
    ahb2_enable = stm32::registers::reset_and_clock_control.ahb2_peripheral_clock_enable;    // read
    ahb2_enable.bits.random_number_generator_enable = 1U;
    stm32::registers::reset_and_clock_control.ahb2_peripheral_clock_enable = ahb2_enable;    // write

    // Reset the RNG
    stm32::registers::ResetAndClockControl::AHB2PeripheralReset reset;
    reset = stm32::registers::reset_and_clock_control.ahb2_peripheral_reset;    // read
    reset.bits.random_number_generator_reset = 1U;
    stm32::registers::reset_and_clock_control.ahb2_peripheral_reset = reset;    // write
    reset.bits.random_number_generator_reset = 0U;
    stm32::registers::reset_and_clock_control.ahb2_peripheral_reset = reset;    // write

    // enable the APB1 peripherals in the Reset and Clock Control register
    apb1_enable = stm32::registers::reset_and_clock_control.apb1_peripheral_clock_enable;    // read
    apb1_enable.bits.tim2en = 1U;
    stm32::registers::reset_and_clock_control.apb1_peripheral_clock_enable = apb1_enable;    // write

    // enable the AHB1 peripherals in the Reset and Clock Control register
    ahb1_enable = stm32::registers::reset_and_clock_control.ahb1_peripheral_clock_enable;    // read
    ahb1_enable.bits.dma1en = 1;                                                             // modify
    ahb1_enable.bits.dma2en = 1;                                                             // modify
    stm32::registers::reset_and_clock_control.ahb1_peripheral_clock_enable = ahb1_enable;    // write

    // enable the ABP2 peripherals in the Reset and Clock Control register
    apb2_enable = stm32::registers::reset_and_clock_control.apb2_peripheral_clock_enable;    // read
    apb2_enable.bits.spi1en = 1;                                                             // modify
    apb2_enable.bits.usart1en = 1;                                                           // modify
    stm32::registers::reset_and_clock_control.apb2_peripheral_clock_enable = apb2_enable;    // write

    jarnax::print(
        "Feature Clock is %lu\r\n"
        "APB1 Clock is %lu\r\n"
        "APB2 Clock is %lu\r\n",
        stm32::GetClockTree().fclk.value(),
        stm32::GetClockTree().apb1_peripheral.value(),
        stm32::GetClockTree().apb2_peripheral.value()
    );
    do {
        // RNG
        status = random_number_generator_.Initialize();
        if (not status.IsSuccess()) {
            jarnax::print("RNG failed to initialize\r\n");
            break;
        }
        // TIMER2
        status = timer_.Initialize(stm32::GetClockTree().tim_clk);
        if (not status.IsSuccess()) {
            jarnax::print("TIMER2 failed to initialize\r\n");
            break;
        }
        // SPI1
        status = spi1_driver_.Initialize(stm32::GetClockTree().apb2_peripheral, ::winbond::spi_clock_frequency);
        if (not status.IsSuccess()) {
            jarnax::print("SPI1 failed to initialize\r\n");
            break;
        }

        // USART1
        status = usart1_driver_.Initialize(stm32::GetClockTree().apb2_peripheral);    // APB2 Clock for USART1 and 6
        if (not status.IsSuccess()) {
            jarnax::print("USART1 failed to initialize\r\n");
            break;
        }
        status = usart1_driver_.Configure(stm32::usart1_baud_rate, false, 1);
        if (not status.IsSuccess()) {
            jarnax::print("USART1 failed to configure\r\n");
            break;
        }

        // force out
        break;
    } while (true);

    if (not status.IsSuccess()) {
        cortex::spinhalt();
    }

    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // External Devices have to be done after the buses are initialized
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    while (status.IsSuccess()) {
        status = winbond_driver_.Initialize();
        // force out
        break;
    }
    return status;
}

jarnax::Timer& DriverContext::GetTimer() {
    return timer_;
}

jarnax::RandomNumberGenerator& DriverContext::GetRandomNumberGenerator() {
    return random_number_generator_;
}

jarnax::Indicator& DriverContext::GetErrorIndicator() {
    return error_indicator_;
}

jarnax::Indicator& DriverContext::GetStatusIndicator() {
    return status_indicator_;
}

jarnax::Button& DriverContext::GetWakeupButton() {
    return wakeup_button_;
}

jarnax::Button& DriverContext::GetButton0() {
    return key0_button_;
}

jarnax::Button& DriverContext::GetButton1() {
    return key1_button_;
}

jarnax::Copier& DriverContext::GetCopier() {
    return dma_driver_;
}

jarnax::spi::Driver& DriverContext::GetSpiDriver() {
    return spi1_driver_;
}

jarnax::usart::Driver& DriverContext::GetDebugDriver() {
    return usart1_driver_;
}

jarnax::gpio::Output& DriverContext::GetFlashChipSelect() {
    return flash_cs_;
}

core::Allocator& DriverContext::GetDmaAllocator() {
    return stm32::dma_heap_allocator;
}

jarnax::winbond::Driver& DriverContext::GetWinbondDriver() {
    return winbond_driver_;
}

DriverContext& GetDriverContext() {
    static DriverContext context;
    return context;
}
}    // namespace jarnax

namespace stm32 {
namespace initialize {

bool are_drivers_initialized{false};

void drivers(void) {
    using namespace stm32::registers;
    core::Status status;
    status = jarnax::GetDriverContext().Initialize();
    if (status) {
        are_drivers_initialized = true;
    }
}

}    // namespace initialize
}    // namespace stm32

namespace jarnax {
void banner(void) {
    jarnax::print(
        "                  _/                                                \r\n"
        "         _/    _/_/    _/_/_/    _/      _/    _/_/    _/      _/   \r\n"
        "        _/  _/    _/  _/    _/  _/_/    _/  _/  _/_/    _/  _/      \r\n"
        "       _/  _/_/_/_/  _/_/_/    _/  _/  _/  _/    _/      _/         \r\n"
        "_/    _/  _/    _/  _/    _/  _/    _/_/  _/_/  _/    _/  _/        \r\n"
        " _/_/    _/    _/  _/    _/  _/      _/    _/_/    _/      _/       \r\n"
        " -- %s\r\n",
        jarnax::VersionString
    );
}
}    // namespace jarnax
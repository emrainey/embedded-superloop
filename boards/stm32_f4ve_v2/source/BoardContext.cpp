#include "BoardContext.hpp"
#include "jarnax.hpp"
#include "lps35hw.hpp"
#include "segger/rtt.hpp"
#include "strings.hpp"

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
    /* .ahb_divider = */ 0b0000,               // /1
    /* .apb1_low_speed_divider = */ 0b101,     // /4
    /* .apb2_high_speed_divider = */ 0b100,    // /2
    /* .mcu_clock1_divider = */ 0b111,         // /5
    /* .mcu_clock2_divider = */ 0b111,         // /5
    /* .rtc_divider = */ 8,
    /* .pll_m = */ 8,
    /* .pll_n = */ 336,
    /* .pll_p = */ 0b00,    // /2
    /* .pll_q = */ 7
};

}    // namespace stm32

namespace jarnax {

BoardContext::BoardContext()
    : timer_{stm32::registers::timer2}
    , random_number_generator_{}
    , wakeup_pin_{stm32::gpio::Port::A, 0}
    , mco1_pin_{stm32::gpio::Port::A, 8}
    , mco2_pin_{stm32::gpio::Port::C, 9}
    , key0_pin_{stm32::gpio::Port::E, 4}
    , key1_pin_{stm32::gpio::Port::E, 3}
    , error_pin_{stm32::gpio::Port::A, 6}
    , status_pin_{stm32::gpio::Port::A, 7}
    , performance_pin_{stm32::gpio::Port::A, 4}
    , timing_pin_{stm32::gpio::Port::A, 5}    // For debugging purposes
    , error_indicator_{error_pin_, stm32::Level::Low}
    , status_indicator_{status_pin_, stm32::Level::Low}
    , performance_indicator_{performance_pin_, stm32::Level::High}
    , timing_indicator_{timing_pin_, stm32::Level::High}
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
    , spi2_mosi_{stm32::gpio::Port::B, 15}
    , spi2_miso_{stm32::gpio::Port::B, 14}
    , spi2_sclk_{stm32::gpio::Port::B, 13}
    , spi2_nss_{stm32::gpio::Port::B, 12}
    , dma_manager_{stm32::registers::direct_memory_access}
    , i2c1_scl_{stm32::gpio::Port::B, 8}
    , i2c1_sda_{stm32::gpio::Port::B, 9}
    , i2c1_driver_{stm32::registers::i2c1, dma_manager_, stm32::I2C1_RX, stm32::I2C1_TX}
    , spi1_driver_{stm32::registers::spi1, dma_manager_, stm32::SPI1_RX, stm32::SPI1_TX}
    , spi2_driver_{stm32::registers::spi2, dma_manager_, stm32::SPI2_RX, stm32::SPI2_TX}
    , w25q16bv_driver_{timer_, spi1_driver_, flash_cs_, GetDmaAllocator()}
    , usart1_tx_{stm32::gpio::Port::A, 9}
    , usart1_rx_{stm32::gpio::Port::A, 10}
    , usart1_driver_{stm32::registers::usart1, dma_manager_, stm32::USART1_RX, stm32::USART1_TX, GetDmaAllocator()}
    , usart_console_{usart1_driver_}
    , lps35hw_driver_{timer_, core::units::ConvertToIota(::lps35hw::DefaultPollingInterval), spi2_driver_, GetDmaAllocator()} {
    // construct the driver objects as part of the constructor above.
}

BoardContext::~BoardContext() {
    // destruct the driver objects in the destructor below.
}

core::Status BoardContext::Initialize(void) {
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
        .SetOutputSpeed(stm32::gpio::Speed::Medium)
        .SetOutputType(stm32::gpio::OutputType::OpenDrain)
        .SetResistor(stm32::gpio::Resistor::None);
    performance_pin_.SetMode(stm32::gpio::Mode::Output)
        .SetOutputSpeed(stm32::gpio::Speed::Medium)
        .SetOutputType(stm32::gpio::OutputType::PushPull)
        .SetResistor(stm32::gpio::Resistor::PullDown);
    timing_pin_.SetMode(stm32::gpio::Mode::Output)
        .SetOutputSpeed(stm32::gpio::Speed::Medium)
        .SetOutputType(stm32::gpio::OutputType::PushPull)
        .SetResistor(stm32::gpio::Resistor::PullDown);
    error_indicator_.Inactive();
    status_indicator_.Inactive();
    performance_indicator_.Inactive();
    timing_indicator_.Inactive();
    i2c1_scl_.SetMode(stm32::gpio::Mode::AlternateFunction)
        .SetAlternative(4)    // Alt 4 is I2C1
        .SetOutputSpeed(stm32::gpio::Speed::VeryHigh)
        .SetOutputType(stm32::gpio::OutputType::PushPull);
    i2c1_sda_.SetMode(stm32::gpio::Mode::AlternateFunction)
        .SetAlternative(4)    // Alt 4 is I2C1
        .SetOutputSpeed(stm32::gpio::Speed::VeryHigh)
        .SetOutputType(stm32::gpio::OutputType::OpenDrain);
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
        .SetResistor(stm32::gpio::Resistor::None)
        .Value(true);
    nrf_ce_.SetMode(stm32::gpio::Mode::Output)
        .SetOutputSpeed(stm32::gpio::Speed::VeryHigh)
        .SetOutputType(stm32::gpio::OutputType::PushPull)
        .SetResistor(stm32::gpio::Resistor::None)
        .Value(false);
    nrf_irq_.SetMode(stm32::gpio::Mode::Input).SetResistor(stm32::gpio::Resistor::PullUp);
    spi2_miso_.SetMode(stm32::gpio::Mode::AlternateFunction)
        .SetAlternative(5)    // Alt 5 is SPI2
        .SetOutputSpeed(stm32::gpio::Speed::VeryHigh)
        .SetOutputType(stm32::gpio::OutputType::PushPull);
    spi2_mosi_.SetMode(stm32::gpio::Mode::AlternateFunction)
        .SetAlternative(5)    // Alt 5 is SPI2
        .SetOutputSpeed(stm32::gpio::Speed::VeryHigh)
        .SetOutputType(stm32::gpio::OutputType::PushPull);
    spi2_sclk_.SetMode(stm32::gpio::Mode::AlternateFunction)
        .SetAlternative(5)    // Alt 5 is SPI1
        .SetOutputSpeed(stm32::gpio::Speed::VeryHigh)
        .SetOutputType(stm32::gpio::OutputType::PushPull);
    spi2_nss_.SetMode(stm32::gpio::Mode::AlternateFunction)
        .SetAlternative(5)    // Alt 5 is SPI2
        .SetOutputSpeed(stm32::gpio::Speed::VeryHigh)
        .SetOutputType(stm32::gpio::OutputType::PushPull);
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
    apb1_enable.bits.tim2en = 1U;                                                            // modify
    apb1_enable.bits.i2c1en = 1U;                                                            // modify
    apb1_enable.bits.spi2en = 1U;                                                            // modify
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
        "APB1 Timer Clock is %lu\r\n"
        "APB2 Timer Clock is %lu\r\n"
        "APB1 Clock is %lu\r\n"
        "APB2 Clock is %lu\r\n",
        stm32::GetClockTree().fclk.value(),
        stm32::GetClockTree().apb1_timer_clk.value(),
        stm32::GetClockTree().apb2_timer_clk.value(),
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
        status = timer_.Initialize(stm32::GetClockTree().apb1_timer_clk, stm32::timer2_frequency);
        if (not status.IsSuccess()) {
            jarnax::print("TIMER2 failed to initialize\r\n");
            break;
        }
        // I2C1
        status = i2c1_driver_.Initialize(stm32::GetClockTree().apb1_peripheral, ::stm32::i2c1_bus_frequency);
        if (not status.IsSuccess()) {
            jarnax::print("I2C1 failed to initialize\r\n");
            break;
        }

        // SPI1
        status = spi1_driver_.Initialize(stm32::GetClockTree().apb2_peripheral, ::winbond::spi_bus_frequency);
        if (not status.IsSuccess()) {
            jarnax::print("SPI1 failed to initialize\r\n");
            break;
        }

        // SPI2
        status = spi2_driver_.Initialize(stm32::GetClockTree().apb1_peripheral, ::stm32::spi2_bus_frequency);
        if (not status.IsSuccess()) {
            jarnax::print("SPI2 failed to initialize\r\n");
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

    do {
        status = w25q16bv_driver_.Initialize();
        if (not status.IsSuccess()) {
            jarnax::print("W25Q16BV Flash failed to initialize\r\n");
            break;
        }

        status = lps35hw_driver_.Initialize();
        if (not status.IsSuccess()) {
            jarnax::print("LPS35HW failed to initialize\r\n");
            break;
        }

        // force out
        break;
    } while (true);

    if (not status.IsSuccess()) {
        cortex::spinhalt();
    }

    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // Initialize the NVIC for these drivers
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    // 0 is the highest priority
    cortex::nvic::Prioritize(to_underlying(stm32::InterruptRequest::Timer2), 1);
    cortex::nvic::Enable(to_underlying(stm32::InterruptRequest::Timer2));

    cortex::nvic::Enable(to_underlying(stm32::InterruptRequest::DirectMemoryAccess2Stream0));           // SPI1_RX
    cortex::nvic::Enable(to_underlying(stm32::InterruptRequest::DirectMemoryAccess2Stream3));           // SPI1_TX
    cortex::nvic::Prioritize(to_underlying(stm32::InterruptRequest::DirectMemoryAccess2Stream0), 2);    // SPI1_RX
    cortex::nvic::Prioritize(to_underlying(stm32::InterruptRequest::DirectMemoryAccess2Stream3), 2);    // SPI1_TX

    cortex::nvic::Enable(to_underlying(stm32::InterruptRequest::DirectMemoryAccess2Stream2));           // SPI2_RX
    cortex::nvic::Enable(to_underlying(stm32::InterruptRequest::DirectMemoryAccess2Stream7));           // SPI2_TX
    cortex::nvic::Prioritize(to_underlying(stm32::InterruptRequest::DirectMemoryAccess2Stream2), 2);    // SPI2_RX
    cortex::nvic::Prioritize(to_underlying(stm32::InterruptRequest::DirectMemoryAccess2Stream7), 2);    // SPI2_TX

    // enable the I2C1 event and error interrupts
    cortex::nvic::Enable(to_underlying(stm32::InterruptRequest::InterIntegratedCircuit1_Event));
    cortex::nvic::Prioritize(to_underlying(stm32::InterruptRequest::InterIntegratedCircuit1_Event), 3);
    cortex::nvic::Enable(to_underlying(stm32::InterruptRequest::InterIntegratedCircuit1_Error));
    cortex::nvic::Prioritize(to_underlying(stm32::InterruptRequest::InterIntegratedCircuit1_Error), 3);

    // enable the SPI1 interrupt and the DMA interrupts for SPI1_RX and SPI1_TX
    cortex::nvic::Enable(to_underlying(stm32::InterruptRequest::SerialPeripheralInterface1));
    cortex::nvic::Prioritize(to_underlying(stm32::InterruptRequest::SerialPeripheralInterface1), 3);

    // enable the SPI2 interrupt and the DMA interrupts for SPI2_RX and SPI2_TX
    cortex::nvic::Enable(to_underlying(stm32::InterruptRequest::SerialPeripheralInterface2));
    cortex::nvic::Prioritize(to_underlying(stm32::InterruptRequest::SerialPeripheralInterface2), 4);

    // enable the USART1 interrupt
    cortex::nvic::Enable(to_underlying(stm32::InterruptRequest::UniversalSynchronousAsynchronousReceiverTransmitter1));
    cortex::nvic::Prioritize(to_underlying(stm32::InterruptRequest::UniversalSynchronousAsynchronousReceiverTransmitter1), 5);

    return status;
}

jarnax::Timer& BoardContext::GetTimer() {
    return timer_;
}

jarnax::RandomNumberGenerator& BoardContext::GetRandomNumberGenerator() {
    return random_number_generator_;
}

jarnax::Indicator& BoardContext::GetErrorIndicator() {
    return error_indicator_;
}

jarnax::Indicator& BoardContext::GetStatusIndicator() {
    return status_indicator_;
}

jarnax::Indicator& BoardContext::GetPerformanceIndicator() {
    return performance_indicator_;
}

jarnax::Indicator& BoardContext::GetTimingIndicator() {
    return timing_indicator_;
}

jarnax::Button& BoardContext::GetWakeupButton() {
    return wakeup_button_;
}

jarnax::Button& BoardContext::GetButton0() {
    return key0_button_;
}

jarnax::Button& BoardContext::GetButton1() {
    return key1_button_;
}

jarnax::Copier& BoardContext::GetCopier() {
    return dma_manager_;
}

jarnax::i2c::Driver& BoardContext::GetI2cDriver() {
    return i2c1_driver_;
}

jarnax::spi::Driver& BoardContext::GetSpiDriver() {
    return spi1_driver_;
}

jarnax::spi::Driver& BoardContext::GetSpi2Driver() {
    return spi2_driver_;
}

jarnax::usart::Driver& BoardContext::GetCameraUsart() {
    return usart1_driver_;
}

jarnax::gpio::Output& BoardContext::GetFlashChipSelect() {
    return flash_cs_;
}

core::Allocator& BoardContext::GetDmaAllocator() {
    return stm32::dma_heap_allocator;
}

jarnax::w25q16bv::Driver& BoardContext::GetW25q16bvDriver() {
    return w25q16bv_driver_;
}

jarnax::console::Service& BoardContext::GetConsole() {
    return usart_console_;
}

jarnax::lps35hw::Driver& BoardContext::GetLps35hwDriver() {
    return lps35hw_driver_;
}

BoardContext& GetBoardContext() {
    static BoardContext board_context;
    return board_context;
}

}    // namespace jarnax

namespace stm32 {
namespace initialize {

bool are_drivers_initialized{false};

void drivers(void) {
    core::Status status;
    status = jarnax::GetBoardContext().Initialize();
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

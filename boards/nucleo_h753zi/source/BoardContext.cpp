#include <array>
#include <compiler.hpp>
#include <cortex/linker.hpp>
#include "BoardContext.hpp"
#include <cortex/linker.hpp>
#include "configure.hpp"
#include "core/Container.hpp"
#include "cortex/mcu.hpp"
#include "jarnax.hpp"
#include "jarnax/print.hpp"
#include "lps35hw.hpp"
#include "lsm9ds1.hpp"
#include "segger/rtt.hpp"
#include "stm32/h7xx/ResetAndClockControl.hpp"
#include "strings.hpp"

LINKER_TYPED_SYMBOL(__sram1_start, std::uint32_t);
LINKER_TYPED_SYMBOL(__sram1_limit, std::uint32_t);
LINKER_TYPED_SYMBOL(__sram2_start, std::uint32_t);
LINKER_TYPED_SYMBOL(__sram2_limit, std::uint32_t);
LINKER_TYPED_SYMBOL(__sram3_start, std::uint32_t);
LINKER_TYPED_SYMBOL(__sram3_limit, std::uint32_t);
LINKER_TYPED_SYMBOL(__sram4_start, std::uint32_t);
LINKER_TYPED_SYMBOL(__sram4_limit, std::uint32_t);

#if defined(UNITTEST)
static std::uint32_t mock_sram1[256];
static std::uint32_t mock_sram2[256];
static std::uint32_t mock_sram3[256];
static std::uint32_t mock_sram4[256];
std::uint32_t *__sram1_start = mock_sram1;
std::uint32_t *__sram1_limit = mock_sram1 + 256;
std::uint32_t *__sram2_start = mock_sram2;
std::uint32_t *__sram2_limit = mock_sram2 + 256;
std::uint32_t *__sram3_start = mock_sram3;
std::uint32_t *__sram3_limit = mock_sram3 + 256;
std::uint32_t *__sram4_start = mock_sram4;
std::uint32_t *__sram4_limit = mock_sram4 + 256;
#endif
namespace stm32 {

/// @brief Dedicate a chunk of memory for the DMA buffers
LINKER_SECTION(".dma_buffers") alignas(alignof(std::max_align_t)) static core::Array<uint8_t, DmaBlockSize * DmaBlockCount> dma_memory;
/// @brief Manage the DMA buffers with a bitmap allocator
static core::BitMapHeap<DmaBlockSize, DmaBlockCount> dma_heap_allocator{&dma_memory[0], dma_memory.size()};

/// @brief A second chunk of memory for the Ethernet's DMA Frames, but they go in the same location.
LINKER_SECTION(".ethernet_dma_buffers") alignas(alignof(std::max_align_t)) static core::Array<uint8_t, ethernet_dma_buffer_size> ethernet_dma_memory;
/// @brief Manage the Ethernet DMA buffers with a bitmap allocator
static core::BitMapHeap<ethernet_dma_block_size, ethernet_dma_block_count, alignof(std::max_align_t), std::uint8_t> ethernet_dma_heap{
    &ethernet_dma_memory[0], ethernet_dma_memory.size()
};

/// @brief Separate stack-owned Ethernet frame memory pool (decoupled from DMA rings).
alignas(alignof(std::max_align_t)) static core::Array<uint8_t, ethernet_dma_buffer_size> ethernet_stack_memory;
/// @brief Allocator for stack-owned Ethernet frames delivered up the network stack.
static core::BitMapHeap<ethernet_dma_block_size, ethernet_dma_block_count, alignof(std::max_align_t), std::uint8_t> ethernet_stack_heap{
    &ethernet_stack_memory[0], ethernet_stack_memory.size()
};

/// @brief Dedicated descriptor-ring memory for Ethernet TX descriptors.
LINKER_SECTION(".ethernet_dma_descriptors")
alignas(
    alignof(stm32::ethernet::dma::Descriptor)
) static core::Array<stm32::ethernet::dma::Descriptor, stm32::ethernet::Driver::TransmitDescriptorCount> ethernet_tx_descriptors{};

/// @brief Dedicated descriptor-ring memory for Ethernet RX descriptors.
LINKER_SECTION(".ethernet_dma_descriptors")
alignas(
    alignof(stm32::ethernet::dma::Descriptor)
) static core::Array<stm32::ethernet::dma::Descriptor, stm32::ethernet::Driver::ReceiveDescriptorCount> ethernet_rx_descriptors{};

/// @brief The Clock configuration for this board.
/// @note HSI @ 64 MHz: M=8 -> 8 MHz VCO input, N=100 -> 800 MHz VCO, P=2 -> 400 MHz sys_ck, Q=4, R=8
ClockConfiguration const default_clock_configuration = {
    /* .use_internal = */ true,
    /* .use_bypass = */ false,
    /* .use_csi = */ false,
    /* .use_pll_fracn = */ false,
    /* .external_clock_frequency = */ high_speed_external_oscillator_frequency,
    /* .low_speed_external_oscillator_frequency = */ low_speed_external_oscillator_frequency,
    /* .voltage_scaling = */ 0b11,             // VOS1 (up to 400 MHz without VOS0 boost)
    /* .d1_core_prescaler = */ 0b0000,         // /1 (cpu_ck = sys_ck)
    /* .ahb_divider = */ 0b1000,               // /2 (hclk3 = sys_ck/2)
    /* .apb1_low_speed_divider = */ 0b101,     // /4
    /* .apb2_high_speed_divider = */ 0b100,    // /2
    /* .apb3_divider = */ 0b100,               // /2 (apb3 = hclk3/2)
    /* .apb4_divider = */ 0b100,               // /2
    /* .mcu_clock1_divider = */ 0b111,         // /5
    /* .mcu_clock2_divider = */ 0b111,         // /5
    /* .rtc_divider = */ 8U,                   // /9 (40 kHz clock for RTC)
    /* .pll_source = */ 0U,                    // HSI
    /* .pll_m = */ 8U,                         // 64 MHz / 8 = 8 MHz
    /* .pll_n = */ 100U - 1U,                  // 8 MHz * 100 = 800 MHz VCO
    /* .pll_p = */ 2U - 1U,                    // 800 MHz / 2 = 400 MHz sys_ck
    /* .pll_q = */ 4U - 1U,                    // 800 MHz / 4 = 200 MHz
    /* .pll_r = */ 8U - 1U,                    // 800 MHz / 8 = 100 MHz
    /* .pll_fracn = */ 0
};

// Secondary Zero Init for SRAMx
struct SRAM {
    std::uint32_t *start;
    std::uint32_t *limit;
} srams[] = {
    { __sram1_start, __sram1_limit },
    { __sram2_start, __sram2_limit },
    { __sram3_start, __sram3_limit },
    { __sram4_start, __sram4_limit },
};

}    // namespace stm32

namespace jarnax {

BoardContext::BoardContext()
    : timer_{stm32::h7xx::timer2}
    , random_number_generator_{stm32::h7xx::random_number_generator}
    , mco1_pin_{stm32::gpio::Port::A, 8}
    , mco2_pin_{stm32::gpio::Port::C, 9}           // TODO this is also a SDMMC pin, so we may have to change it
    , user_button_pin_{stm32::gpio::Port::C, 13}
    , error_pin_{stm32::gpio::Port::B, 14}         // LD3 Red LED
    , status_pin_{stm32::gpio::Port::B, 0}         // LD1 Green LED
    , performance_pin_{stm32::gpio::Port::E, 1}    // LED2 Yellow LED
    , timing_pin_{stm32::gpio::Port::A, 3}         // GPIO
    , error_indicator_{error_pin_, stm32::Level::High}
    , status_indicator_{status_pin_, stm32::Level::High}
    , performance_indicator_{performance_pin_, stm32::Level::High}
    , timing_indicator_{timing_pin_, stm32::Level::High}
    , user_button_{user_button_pin_, false}
    , dma_manager_{stm32::h7xx::direct_memory_access}
    , i2c1_scl_{stm32::gpio::Port::B, 8}
    , i2c1_sda_{stm32::gpio::Port::B, 9}
    , i2c1_driver_{stm32::h7xx::i2c1, dma_manager_, stm32::I2C1_RX, stm32::I2C1_TX}
    , i2c2_scl_{stm32::gpio::Port::F, 1}
    , i2c2_sda_{stm32::gpio::Port::F, 0}
    , i2c2_smba_{stm32::gpio::Port::F, 2}
    , i2c2_driver_{stm32::h7xx::i2c2, dma_manager_, stm32::I2C2_RX, stm32::I2C2_TX}
    , spi1_mosi_{stm32::gpio::Port::B, 5}
    , spi1_miso_{stm32::gpio::Port::A, 6}
    , spi1_sclk_{stm32::gpio::Port::A, 5}
    , spi1_cs_{stm32::gpio::Port::D, 14}
    , spi1_driver_{stm32::h7xx::spi1, dma_manager_, stm32::SPI1_RX, stm32::SPI1_TX}
    , usart3_tx_{stm32::gpio::Port::D, 9}
    , usart3_rx_{stm32::gpio::Port::D, 10}
    , usart3_driver_{stm32::h7xx::usart3, dma_manager_, stm32::USART3_RX, stm32::USART3_TX, GetDmaAllocator(), stm32::usart_dma_buffer_size}
    , usart_console_{usart3_driver_}
    , eth_ref_clk_{stm32::gpio::Port::A, 1}    // RMII_REF_CLK
    , eth_mdio_{stm32::gpio::Port::A, 2}       // MDIO (JP6 must be ON)
    , eth_crs_dv_{stm32::gpio::Port::A, 7}     // RMII_CRS_DV
    , eth_txd1_{stm32::gpio::Port::B, 13}      // RMII_TXD1 (JP7 must be ON)
    , eth_mdc_{stm32::gpio::Port::C, 1}        // MDC
    , eth_rxd0_{stm32::gpio::Port::C, 4}       // RMII_RXD0
    , eth_rxd1_{stm32::gpio::Port::C, 5}       // RMII_RXD1
    , eth_tx_en_{stm32::gpio::Port::G, 11}     // RMII_TX_EN
    , eth_txd0_{stm32::gpio::Port::G, 13}      // RMII_TXD0
    , ethernet_{stm32::ethernet_stack_heap, stm32::ethernet_dma_heap, stm32::ethernet_tx_descriptors, stm32::ethernet_rx_descriptors} {
    // construct the driver objects as part of the constructor above.
}

BoardContext::~BoardContext() {
    // destruct the driver objects in the destructor below.
}

core::Status BoardContext::Initialize(void) {
    core::Status status;
    mco1_pin_.SetOutputSpeed(stm32::gpio::Speed::VeryHigh).SetMode(stm32::gpio::Mode::AlternateFunction).SetAlternative(0);    // Alt 0 is MCO1
    mco2_pin_.SetOutputSpeed(stm32::gpio::Speed::VeryHigh).SetMode(stm32::gpio::Mode::AlternateFunction).SetAlternative(0);    // Alt 0 is MCO2
    user_button_pin_.SetMode(stm32::gpio::Mode::Input).SetResistor(stm32::gpio::Resistor::PullUp);
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
    i2c2_scl_.SetMode(stm32::gpio::Mode::AlternateFunction)
        .SetAlternative(4)    // Alt 4 is I2C2
        .SetOutputSpeed(stm32::gpio::Speed::VeryHigh)
        .SetOutputType(stm32::gpio::OutputType::PushPull);
    i2c2_sda_.SetMode(stm32::gpio::Mode::AlternateFunction)
        .SetAlternative(4)    // Alt 4 is I2C2
        .SetOutputSpeed(stm32::gpio::Speed::VeryHigh)
        .SetOutputType(stm32::gpio::OutputType::OpenDrain);
    i2c2_smba_.SetMode(stm32::gpio::Mode::AlternateFunction)
        .SetAlternative(4)    // Alt 4 is I2C2
        .SetOutputSpeed(stm32::gpio::Speed::VeryHigh)
        .SetOutputType(stm32::gpio::OutputType::PushPull);
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
    spi1_cs_.SetMode(stm32::gpio::Mode::Output)
        .SetOutputSpeed(stm32::gpio::Speed::VeryHigh)
        .SetOutputType(stm32::gpio::OutputType::PushPull)
        .SetResistor(stm32::gpio::Resistor::None)
        .Value(true);         // CS is active low
    usart3_tx_.SetMode(stm32::gpio::Mode::AlternateFunction)
        .SetAlternative(7)    // Alt 7 is USART3
        .SetOutputSpeed(stm32::gpio::Speed::High)
        .SetOutputType(stm32::gpio::OutputType::PushPull);
    usart3_rx_.SetMode(stm32::gpio::Mode::AlternateFunction)
        .SetAlternative(7)    // Alt 7 is USART3
        .SetOutputSpeed(stm32::gpio::Speed::High)
        .SetOutputType(stm32::gpio::OutputType::PushPull);
    // Ethernet RMII pins — all use AF11 on STM32H7
    eth_ref_clk_.SetMode(stm32::gpio::Mode::AlternateFunction)
        .SetAlternative(11)    // Alt 11 is ETH
        .SetOutputSpeed(stm32::gpio::Speed::VeryHigh)
        .SetOutputType(stm32::gpio::OutputType::PushPull);
    eth_mdio_.SetMode(stm32::gpio::Mode::AlternateFunction)
        .SetAlternative(11)    // Alt 11 is ETH
        .SetOutputSpeed(stm32::gpio::Speed::VeryHigh)
        .SetOutputType(stm32::gpio::OutputType::PushPull);
    eth_crs_dv_.SetMode(stm32::gpio::Mode::AlternateFunction)
        .SetAlternative(11)    // Alt 11 is ETH
        .SetOutputSpeed(stm32::gpio::Speed::VeryHigh)
        .SetOutputType(stm32::gpio::OutputType::PushPull);
    eth_txd1_.SetMode(stm32::gpio::Mode::AlternateFunction)
        .SetAlternative(11)    // Alt 11 is ETH
        .SetOutputSpeed(stm32::gpio::Speed::VeryHigh)
        .SetOutputType(stm32::gpio::OutputType::PushPull);
    eth_mdc_.SetMode(stm32::gpio::Mode::AlternateFunction)
        .SetAlternative(11)    // Alt 11 is ETH
        .SetOutputSpeed(stm32::gpio::Speed::VeryHigh)
        .SetOutputType(stm32::gpio::OutputType::PushPull);
    eth_rxd0_.SetMode(stm32::gpio::Mode::AlternateFunction)
        .SetAlternative(11)    // Alt 11 is ETH
        .SetOutputSpeed(stm32::gpio::Speed::VeryHigh)
        .SetOutputType(stm32::gpio::OutputType::PushPull);
    eth_rxd1_.SetMode(stm32::gpio::Mode::AlternateFunction)
        .SetAlternative(11)    // Alt 11 is ETH
        .SetOutputSpeed(stm32::gpio::Speed::VeryHigh)
        .SetOutputType(stm32::gpio::OutputType::PushPull);
    eth_tx_en_.SetMode(stm32::gpio::Mode::AlternateFunction)
        .SetAlternative(11)    // Alt 11 is ETH
        .SetOutputSpeed(stm32::gpio::Speed::VeryHigh)
        .SetOutputType(stm32::gpio::OutputType::PushPull);
    eth_txd0_.SetMode(stm32::gpio::Mode::AlternateFunction)
        .SetAlternative(11)    // Alt 11 is ETH
        .SetOutputSpeed(stm32::gpio::Speed::VeryHigh)
        .SetOutputType(stm32::gpio::OutputType::PushPull);

    stm32::h7xx::ResetAndClockControl::AHB1PeripheralClockEnable ahb1_enable;
    stm32::h7xx::ResetAndClockControl::AHB1PeripheralReset ahb1_reset;
    stm32::h7xx::ResetAndClockControl::AHB2PeripheralClockEnable ahb2_enable;
    stm32::h7xx::ResetAndClockControl::AHB2PeripheralReset ahb2_reset;
    stm32::h7xx::ResetAndClockControl::APB1LowClockEnable apb1_enable;
    stm32::h7xx::ResetAndClockControl::APB2PeripheralClockEnable apb2_enable;
    stm32::h7xx::ResetAndClockControl::Processor1AHB4ClockEnable ahb4_enable;

    // Reset the AHB1 peripherals
    ahb1_reset = stm32::h7xx::reset_and_clock_control.ahb1_peripheral_reset;    // read
    ahb1_reset.bits.dma1_reset = 1U;
    ahb1_reset.bits.dma2_reset = 1U;
    ahb1_reset.bits.ethernet1_mac_reset = 1U;
    stm32::h7xx::reset_and_clock_control.ahb1_peripheral_reset = ahb1_reset;    // write
    ahb1_reset.bits.dma1_reset = 0U;
    ahb1_reset.bits.dma2_reset = 0U;
    ahb1_reset.bits.ethernet1_mac_reset = 0U;
    stm32::h7xx::reset_and_clock_control.ahb1_peripheral_reset = ahb1_reset;    // write

    // Reset the AHB2 peripherals
    ahb2_reset = stm32::h7xx::reset_and_clock_control.ahb2_peripheral_reset;    // read
    ahb2_reset.bits.random_number_generator_reset = 1U;
    stm32::h7xx::reset_and_clock_control.ahb2_peripheral_reset = ahb2_reset;    // write
    ahb2_reset.bits.random_number_generator_reset = 0U;
    stm32::h7xx::reset_and_clock_control.ahb2_peripheral_reset = ahb2_reset;    // write

    // Enable the RNG in the AHB2 Periperhals
    ahb2_enable = stm32::h7xx::reset_and_clock_control.ahb2_peripheral_clock_enable;    // read
    ahb2_enable.bits.random_number_generator_enable = 1U;
    ahb2_enable.bits.sram1_enable = 1U;
    ahb2_enable.bits.sram2_enable = 1U;
    ahb2_enable.bits.sram3_enable = 1U;
    stm32::h7xx::reset_and_clock_control.ahb2_peripheral_clock_enable = ahb2_enable;    // write

    // Now wait for the D2 Clock Ready (D2CKRDY)
    stm32::h7xx::ResetAndClockControl::Control control;
    do {
        control = stm32::h7xx::reset_and_clock_control.control;    // read
    } while (control.bits.domain2_clock_ready == 0);

    // Enable the SRAM4 in the AHB4 Periperhals
    ahb4_enable = stm32::h7xx::reset_and_clock_control.processor1_ahb4_clock_enable;    // read
    ahb4_enable.bits.sram4_enable = 1U;
    stm32::h7xx::reset_and_clock_control.processor1_ahb4_clock_enable = ahb4_enable;    // write

    // enable the APB1 peripherals in the Reset and Clock Control register
    apb1_enable = stm32::h7xx::reset_and_clock_control.apb1_low_clock_enable;    // read
    apb1_enable.bits.timer2_enable = 1U;                                         // modify
    apb1_enable.bits.i2c1_enable = 1U;                                           // modify
    apb1_enable.bits.i2c2_enable = 1U;                                           // modify
    apb1_enable.bits.usart3_enable = 1U;                                         // modify
    stm32::h7xx::reset_and_clock_control.apb1_low_clock_enable = apb1_enable;    // write

    // enable the AHB1 peripherals in the Reset and Clock Control register
    ahb1_enable = stm32::h7xx::reset_and_clock_control.ahb1_peripheral_clock_enable;    // read
    ahb1_enable.bits.dma1_enable = 1;                                                   // modify
    ahb1_enable.bits.dma2_enable = 1;                                                   // modify
    ahb1_enable.bits.ethernet1_mac_enable = 1;                                          // modify
    ahb1_enable.bits.ethernet1_transmit_clock_enable = 1;                               // modify
    ahb1_enable.bits.ethernet1_receive_clock_enable = 1;                                // modify
    stm32::h7xx::reset_and_clock_control.ahb1_peripheral_clock_enable = ahb1_enable;    // write

    // enable the ABP2 peripherals in the Reset and Clock Control register
    apb2_enable = stm32::h7xx::reset_and_clock_control.apb2_peripheral_clock_enable;    // read
    apb2_enable.bits.spi1_enable = 1;                                                   // modify
    stm32::h7xx::reset_and_clock_control.apb2_peripheral_clock_enable = apb2_enable;    // write

    if constexpr (stm32::use_rmii_for_ethernet) {
        // enable APB4 SYSCFG so PMCR can select the Ethernet PHY interface mode
        stm32::h7xx::ResetAndClockControl::APB4ClockEnable apb4_enable;
        apb4_enable = stm32::h7xx::reset_and_clock_control.apb4_clock_enable;    // read
        apb4_enable.bits.syscfg_enable = 1U;                                     // modify
        stm32::h7xx::reset_and_clock_control.apb4_clock_enable = apb4_enable;    // write

        // Select RMII in SYSCFG PMCR EPIS (0b100 = RMII, 0b000 = MII)
        stm32::h7xx::SystemConfiguration::PeripheralModeControl peripheral_mode_control;
        peripheral_mode_control = stm32::h7xx::system_configuration.peripheral_mode_control;    // read
        peripheral_mode_control.bits.ethernet_physical_interface_selection = 0b100U;            // RMII
        stm32::h7xx::system_configuration.peripheral_mode_control = peripheral_mode_control;    // write
    }

    // Since we just enabled SRAM1,2,3,4 we need to memset the whole parts for ECC
    // TODO: This is a hacky way to do this. We should be able to do this at compile time, but these 
    // CAN'T be done in the zero table as the parts aren't enable at boot
    for (size_t r = 0; r < dimof(stm32::srams); r++) {
        std::size_t size = static_cast<size_t>(stm32::srams[r].limit - stm32::srams[r].start) / sizeof(*stm32::srams[r].start);
        memory::fill<uint32_t>(stm32::srams[r].start, 0U, size);
    }

    jarnax::print("Feature Clock is %" PRIu32 "\r\n", stm32::GetClockTree().fclk.value());
    jarnax::print("APB1 Timer Clock is %" PRIu32 "\r\n", stm32::GetClockTree().apb1_timer_clk.value());
    jarnax::print("APB2 Timer Clock is %" PRIu32 "\r\n", stm32::GetClockTree().apb2_timer_clk.value());
    jarnax::print("APB1 Clock is %" PRIu32 "\r\n", stm32::GetClockTree().apb1_peripheral.value());
    jarnax::print("APB2 Clock is %" PRIu32 "\r\n", stm32::GetClockTree().apb2_peripheral.value());
    jarnax::print("APB3 Clock is %" PRIu32 "\r\n", stm32::GetClockTree().apb3_peripheral.value());
    jarnax::print("APB4 Clock is %" PRIu32 "\r\n", stm32::GetClockTree().apb4_peripheral.value());
    jarnax::print("AHB1 Clock is %" PRIu32 "\r\n", stm32::GetClockTree().ahb1_peripheral.value());
    jarnax::print("AHB2 Clock is %" PRIu32 "\r\n", stm32::GetClockTree().ahb2_peripheral.value());

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

        // I2C2
        status = i2c2_driver_.Initialize(stm32::GetClockTree().apb1_peripheral, ::stm32::i2c2_bus_frequency);
        if (not status.IsSuccess()) {
            jarnax::print("I2C2 failed to initialize\r\n");
            break;
        }

        // SPI1
        status = spi1_driver_.Initialize(stm32::GetClockTree().apb2_peripheral, ::stm32::spi1_bus_frequency);
        if (not status.IsSuccess()) {
            jarnax::print("SPI1 failed to initialize\r\n");
            break;
        }

        // USART3
        status = usart3_driver_.Initialize(stm32::GetClockTree().apb2_peripheral);    // APB2 Clock for USART3 and 6
        if (not status.IsSuccess()) {
            jarnax::print("USART3 failed to initialize\r\n");
            break;
        }
        status = usart3_driver_.Configure(stm32::usart3_baud_rate, false, 1);
        if (not status.IsSuccess()) {
            jarnax::print("USART3 failed to configure\r\n");
            break;
        }

        // Ethernet (does not take any parameters)
        status = ethernet_.Initialize();
        if (not status.IsSuccess()) {
            jarnax::print("Ethernet failed to initialize\r\n");
            break;
        }
        jarnax::net::ethernet::Driver::Addresses addresses{{
            stm32::default_mac_address,    // MAC address
            jarnax::net::eui48::invalid    // Empty
        }};
        status = ethernet_.Configure(addresses);
        if (not status.IsSuccess()) {
            jarnax::print("Ethernet failed to configure\r\n");
            break;
        }
        jarnax::print(
            "Ethernet MAC address is %02X:%02X:%02X:%02X:%02X:%02X\r\n",
            ethernet_.GetMacAddress()[0],
            ethernet_.GetMacAddress()[1],
            ethernet_.GetMacAddress()[2],
            ethernet_.GetMacAddress()[3],
            ethernet_.GetMacAddress()[4],
            ethernet_.GetMacAddress()[5]
        );

        // force out
        break;
    } while (true);

    if (not status.IsSuccess()) {
        jarnax::print("BoardContext failed to initialize, halting...\r\n");
        jarnax::print("Driver Init: ", status);
        cortex::spinhalt();
    }

    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // External Devices have to be done after the buses are initialized
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    do {
        // force out
        break;
    } while (true);

    if (not status.IsSuccess()) {
        cortex::spinhalt();
    }

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

jarnax::Button& BoardContext::GetUserButton() {
    return user_button_;
}

jarnax::Copier& BoardContext::GetCopier() {
    return dma_manager_;
}

jarnax::i2c::Driver& BoardContext::GetI2cA() {
    return i2c1_driver_;
}

jarnax::i2c::Driver& BoardContext::GetI2cB() {
    return i2c2_driver_;
}

jarnax::spi::Driver& BoardContext::GetSpiA() {
    return spi1_driver_;
}

jarnax::usart::Driver& BoardContext::GetUsartB() {
    return usart3_driver_;
}

core::Allocator& BoardContext::GetDmaAllocator() {
    return stm32::dma_heap_allocator;
}

jarnax::console::Service& BoardContext::GetConsole() {
    return usart_console_;
}

core::Container<BoardContext> board_context_container;

BoardContext& GetBoardContext() {
    if (not board_context_container) {
        board_context_container.emplace();
    }
    return *board_context_container;
}

}    // namespace jarnax

namespace stm32 {
namespace initialize {

void gpio(void) {
    using namespace stm32::peripherals;
    // Enable GPIO Clocks (for the ones enabled per board)
    ResetAndClockControl::AHB4ClockEnable ahb4_enable;
    ResetAndClockControl::AHB4Reset ahb4_reset;

    ahb4_enable = reset_and_clock_control.ahb4_clock_enable;    // load
    ahb4_enable.bits.gpioa_enable = 1U;
    ahb4_enable.bits.gpiob_enable = 1U;
    ahb4_enable.bits.gpioc_enable = 1U;
    ahb4_enable.bits.gpiod_enable = 1U;
    ahb4_enable.bits.gpioe_enable = 1U;
    ahb4_enable.bits.gpiof_enable = 1U;
    ahb4_enable.bits.gpiog_enable = 1U;
    ahb4_enable.bits.gpioh_enable = 1U;
    ahb4_enable.bits.gpioi_enable = 1U;
    reset_and_clock_control.ahb4_clock_enable = ahb4_enable;    // store
    // Reset GPIO Ports
    ahb4_reset = reset_and_clock_control.ahb4_reset;    // load
    ahb4_reset.bits.gpioa_reset = 1U;
    ahb4_reset.bits.gpiob_reset = 1U;
    ahb4_reset.bits.gpioc_reset = 1U;
    ahb4_reset.bits.gpiod_reset = 1U;
    ahb4_reset.bits.gpioe_reset = 1U;
    ahb4_reset.bits.gpiof_reset = 1U;
    ahb4_reset.bits.gpiog_reset = 1U;
    ahb4_reset.bits.gpioh_reset = 1U;
    ahb4_reset.bits.gpioi_reset = 1U;
    reset_and_clock_control.ahb4_reset = ahb4_reset;    // store
    // Release GPIO Ports
    ahb4_reset.bits.gpioa_reset = 0U;
    ahb4_reset.bits.gpiob_reset = 0U;
    ahb4_reset.bits.gpioc_reset = 0U;
    ahb4_reset.bits.gpiod_reset = 0U;
    ahb4_reset.bits.gpioe_reset = 0U;
    ahb4_reset.bits.gpiof_reset = 0U;
    ahb4_reset.bits.gpiog_reset = 0U;
    ahb4_reset.bits.gpioh_reset = 0U;
    ahb4_reset.bits.gpioi_reset = 0U;
    reset_and_clock_control.ahb4_reset = ahb4_reset;    // store
}

bool drivers(void) {
    core::Status status;
    status = jarnax::GetBoardContext().Initialize();
    return status.IsSuccess();
}

void nvic(void) {
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // Initialize the NVIC for these drivers
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    // 0 is the highest priority
    cortex::nvic::Prioritize(polyfill::to_underlying(stm32::InterruptRequest::Timer2), 1);
    cortex::nvic::Enable(polyfill::to_underlying(stm32::InterruptRequest::Timer2));

    cortex::nvic::Enable(polyfill::to_underlying(stm32::InterruptRequest::DirectMemoryAccess2Stream0));           // SPI1_RX
    cortex::nvic::Enable(polyfill::to_underlying(stm32::InterruptRequest::DirectMemoryAccess2Stream3));           // SPI1_TX
    cortex::nvic::Prioritize(polyfill::to_underlying(stm32::InterruptRequest::DirectMemoryAccess2Stream0), 2);    // SPI1_RX
    cortex::nvic::Prioritize(polyfill::to_underlying(stm32::InterruptRequest::DirectMemoryAccess2Stream3), 2);    // SPI1_TX

    cortex::nvic::Enable(polyfill::to_underlying(stm32::InterruptRequest::DirectMemoryAccess2Stream2));           // SPI2_RX
    cortex::nvic::Enable(polyfill::to_underlying(stm32::InterruptRequest::DirectMemoryAccess2Stream7));           // SPI2_TX
    cortex::nvic::Prioritize(polyfill::to_underlying(stm32::InterruptRequest::DirectMemoryAccess2Stream2), 2);    // SPI2_RX
    cortex::nvic::Prioritize(polyfill::to_underlying(stm32::InterruptRequest::DirectMemoryAccess2Stream7), 2);    // SPI2_TX

    // enable the I2C1 event and error interrupts
    cortex::nvic::Enable(polyfill::to_underlying(stm32::InterruptRequest::InterIntegratedCircuit1_Event));
    cortex::nvic::Prioritize(polyfill::to_underlying(stm32::InterruptRequest::InterIntegratedCircuit1_Event), 3);
    cortex::nvic::Enable(polyfill::to_underlying(stm32::InterruptRequest::InterIntegratedCircuit1_Error));
    cortex::nvic::Prioritize(polyfill::to_underlying(stm32::InterruptRequest::InterIntegratedCircuit1_Error), 3);

    // enable the SPI1 interrupt and the DMA interrupts for SPI1_RX and SPI1_TX
    cortex::nvic::Enable(polyfill::to_underlying(stm32::InterruptRequest::SerialPeripheralInterface1));
    cortex::nvic::Prioritize(polyfill::to_underlying(stm32::InterruptRequest::SerialPeripheralInterface1), 3);

    // enable the SPI2 interrupt and the DMA interrupts for SPI2_RX and SPI2_TX
    cortex::nvic::Enable(polyfill::to_underlying(stm32::InterruptRequest::SerialPeripheralInterface2));
    cortex::nvic::Prioritize(polyfill::to_underlying(stm32::InterruptRequest::SerialPeripheralInterface2), 4);

    // enable the USART1 interrupt
    cortex::nvic::Enable(polyfill::to_underlying(stm32::InterruptRequest::UniversalSynchronousAsynchronousReceiverTransmitter1));
    cortex::nvic::Prioritize(polyfill::to_underlying(stm32::InterruptRequest::UniversalSynchronousAsynchronousReceiverTransmitter1), 5);

    // enable the Ethernet Interrupts
    cortex::nvic::Enable(polyfill::to_underlying(stm32::InterruptRequest::Ethernet));
    cortex::nvic::Prioritize(polyfill::to_underlying(stm32::InterruptRequest::Ethernet), 6);

    // enable the RNG interrupt
    cortex::nvic::Enable(polyfill::to_underlying(stm32::InterruptRequest::RandomNumberGenerator));
    cortex::nvic::Prioritize(polyfill::to_underlying(stm32::InterruptRequest::RandomNumberGenerator), 7);
}

}    // namespace initialize
}    // namespace stm32

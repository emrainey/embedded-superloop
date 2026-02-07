#include "stm32/uart/Driver.hpp"
#include <cmath>    // for std::floor
#include <jarnax/print.hpp>
#include <memory.hpp>
#include "cortex/vectors.hpp"
#include "stm32/configure.hpp"

namespace stm32 {
/// Array of UART Driver instances for interrupt handling
uart::Driver* uart_instances[4] = {nullptr, nullptr, nullptr, nullptr};    // 4, 5, 7, 8
/// Array of UART statistics pointers for interrupt handling
uart::Statistics* uart_statistics[4] = {nullptr, nullptr, nullptr, nullptr};    // 4, 5, 7, 8

/// Interrupt service routine for UART4
void uart4_isr(void) {
    cortex::extended_vector_statistics.count[to_underlying(stm32::InterruptRequest::UniversalAsynchronousReceiverTransmitter4)]++;
    if (uart_instances[0]) {
        uart_instances[0]->HandleInterrupt();
    }
}

/// Interrupt service routine for UART5
void uart5_isr(void) {
    cortex::extended_vector_statistics.count[to_underlying(stm32::InterruptRequest::UniversalAsynchronousReceiverTransmitter5)]++;
    if (uart_instances[1]) {
        uart_instances[1]->HandleInterrupt();
    }
}

#if defined(STM32H7XX)
/// Interrupt service routine for UART7
void uart7_isr(void) {
    cortex::extended_vector_statistics.count[to_underlying(stm32::InterruptRequest::UniversalAsynchronousReceiverTransmitter7)]++;
    if (uart_instances[2]) {
        uart_instances[2]->HandleInterrupt();
    }
}

/// Interrupt service routine for UART8
void uart8_isr(void) {
    cortex::extended_vector_statistics.count[to_underlying(stm32::InterruptRequest::UniversalAsynchronousReceiverTransmitter8)]++;
    if (uart_instances[3]) {
        uart_instances[3]->HandleInterrupt();
    }
}
#endif

namespace uart {
Driver::Driver(
    peripherals::UniversalAsynchronousReceiverTransmitter volatile& uart, dma::Manager& dma_driver, cortex::Peripheral rx_peripheral,
    cortex::Peripheral tx_peripheral, core::Allocator& dma_allocator, std::size_t dma_allocation_size
)
    : Statistician{}
    , uart_{uart}
    , dma_manager_{dma_driver}
    , rx_peripheral_{rx_peripheral}
    , rx_dma_resource_{nullptr}
    , tx_peripheral_{tx_peripheral}
    , tx_dma_resource_{nullptr}
    , dma_allocator_{dma_allocator}
    , rx_dma_buffer_{dma_allocation_size, dma_allocator_}
    , rx_span_{}
    , tx_dma_buffer_{dma_allocation_size, dma_allocator_}
    , tx_ready_{true}
    , tx_span_{}
    , tx_index_{0U} {
    if (&uart == &peripherals::uart4) {
        uart_instances[0] = this;
        uart_statistics[0] = &statistics_;
    } else if (&uart == &peripherals::uart5) {
        uart_instances[1] = this;
        uart_statistics[1] = &statistics_;
    } else if (&uart == &peripherals::uart7) {
        uart_instances[2] = this;
        uart_statistics[2] = &statistics_;
    } else if (&uart == &peripherals::uart8) {
        uart_instances[3] = this;
        uart_statistics[3] = &statistics_;
    }
}

void Driver::ComputeBaudRate(uint32_t baud_rate) const {
    // The divider is calculated as follows:
    // Divider = (peripheral_frequency_ / (baud_rate * over8))
    // The USART peripheral uses a oversampling rate based on the control register.
    // The divider is a 12-bit value, so the maximum value is 0xFFF.
    // The minimum value is 0.
    // The divider is rounded to the nearest integer.
    // The divider is set in the BRR register.
    stm32::peripherals::UniversalAsynchronousReceiverTransmitter::BaudRate brr;
    stm32::peripherals::UniversalAsynchronousReceiverTransmitter::Control1 control1;
    control1 = uart_.control1;    // read
    uint32_t over8u = control1.bits.oversampling_mode == 1 ? 8 : 16;
    float over8f = control1.bits.oversampling_mode ? 8.0f : 16.0f;
    float divider = static_cast<float>(peripheral_frequency_.value()) / static_cast<float>(baud_rate * over8u);
    float floor = std::floor(divider);
    float fract = divider - floor;
    uint32_t mantissa = static_cast<uint32_t>(floor);
    uint32_t fraction = static_cast<uint32_t>(std::round(fract * over8f));
    brr.bits.div_mantissa = mantissa & 0xFFF;
    brr.bits.div_fraction = fraction & 0x0F;
    uart_.baudrate = brr;    // write
    if constexpr (debug::usart) {
        jarnax::print(
            "UART divider: %lf mantissa:%" PRIu32 " fraction:%" PRIu32 "\r\n",
            static_cast<double>(divider),
            static_cast<uint32_t>(brr.bits.div_mantissa),
            static_cast<uint32_t>(brr.bits.div_fraction)
        );
    }
}

uint32_t Driver::GetBaudRate(void) const {
    stm32::peripherals::UniversalAsynchronousReceiverTransmitter::Control1 control1 = uart_.control1;    // read
    stm32::peripherals::UniversalAsynchronousReceiverTransmitter::BaudRate brr = uart_.baudrate;         // read
    // uint32_t over8u = control1.bits.oversampling_mode == 1 ? 8 : 16;
    float over8f = control1.bits.oversampling_mode ? 8.0f : 16.0f;
    float divider = (static_cast<float>(brr.bits.div_mantissa) + (static_cast<float>(brr.bits.div_fraction) / over8f));
    uint32_t baud_rate = static_cast<uint32_t>(static_cast<float>(peripheral_frequency_.value()) / (divider * over8f));
    if constexpr (debug::usart) {
        jarnax::print(
            "UART divider: %lf mantissa:%" PRIu32 " fraction:%" PRIu32 " => BaudRate: %" PRIu32 "\r\n",
            static_cast<double>(divider),
            static_cast<uint32_t>(brr.bits.div_mantissa),
            static_cast<uint32_t>(brr.bits.div_fraction),
            static_cast<uint32_t>(baud_rate)
        );
    }
    return baud_rate;
}

core::Status Driver::Initialize(void) {
    return Initialize(peripheral_frequency_);
}

core::Status Driver::Initialize(core::units::Hertz peripheral_frequency) {
    rx_dma_resource_ = dma_manager_.Assign(rx_peripheral_);
    if (rx_dma_resource_ == nullptr) {
        return core::Status{core::Result::InvalidValue, core::Cause::Configuration};
    }
    tx_dma_resource_ = dma_manager_.Assign(tx_peripheral_);
    if (tx_dma_resource_ == nullptr) {
        dma_manager_.Release(rx_dma_resource_);
        return core::Status{core::Result::InvalidValue, core::Cause::Configuration};
    }
    // Initialize the DMA resources
    core::Status status{};
    peripheral_frequency_ = peripheral_frequency;
    rx_dma_resource_->Initialize(rx_peripheral_);
    tx_dma_resource_->Initialize(tx_peripheral_);

    stm32::peripherals::UniversalAsynchronousReceiverTransmitter::Control1 control1;
    stm32::peripherals::UniversalAsynchronousReceiverTransmitter::Control2 control2;
    stm32::peripherals::UniversalAsynchronousReceiverTransmitter::Control3 control3;
    // disable the UART
    control1 = uart_.control1;    // read
    control1.whole = 0U;          // clear
    uart_.control1 = control1;    // write

    control2 = uart_.control2;    // read
    control2.whole = 0U;          // clear
    uart_.control2 = control2;    // write

    control3 = uart_.control3;    // read
    control3.whole = 0U;          // clear
    uart_.control3 = control3;    // write
    return status;
}

core::Status Driver::Configure(uint32_t desired_baud_rate, bool parity, uint8_t stop_bits) {
    stm32::peripherals::UniversalAsynchronousReceiverTransmitter::Control1 control1;
    stm32::peripherals::UniversalAsynchronousReceiverTransmitter::Control2 control2;
    stm32::peripherals::UniversalAsynchronousReceiverTransmitter::Control3 control3;

    control1 = uart_.control1;    // read
    control2 = uart_.control2;    // read
    control3 = uart_.control3;    // read

    // control1
    control1.whole = 0U;                                     // clear
    control1.bits.parity_control_enable = parity ? 1 : 0;    // parity enabled or not
    if (parity) {
        control1.bits.parity_select = 1;                     // even parity
    }
    control1.bits.receiver_enable = 1;                       // receiver enabled
    control1.bits.transmitter_enable = 1;                    // transmitter enabled
    control1.bits.uxart_enable = 1;                          // USART enabled
    // control2
    control2.whole = 0U;                             // clear
    control2.bits.stop = stop_bits ? 0b00 : 0b10;    // 1 stop bit, 2 stop bits

    // control3
    control3.whole = 0U;          // clear

    uart_.control1 = control1;    // write
    uart_.control2 = control2;    // write
    uart_.control3 = control3;    // write

    ComputeBaudRate(desired_baud_rate);
    uint32_t actual_baud_rate = GetBaudRate();
    if (actual_baud_rate != desired_baud_rate) {
        uint32_t distance = (actual_baud_rate > desired_baud_rate) ? actual_baud_rate - desired_baud_rate : desired_baud_rate - actual_baud_rate;
        float error = static_cast<float>(distance) / static_cast<float>(desired_baud_rate);
        if constexpr (debug::usart) {
            jarnax::print("USART BaudRate error: %lf %% (%" PRIu32 ")\r\n", static_cast<double>(error * 100.0f), static_cast<uint32_t>(distance));
        }
    }

    // Enable RX DMA
    control3.bits.direct_memory_access_receiver = 1;    // DMA receiver enabled
    // control3.bits.direct_memory_access_transmitter = 1;    // DMA transmitter enabled
    uart_.control3 = control3;    // write

    // Setup the RX DMA stream
    rx_span_ = rx_dma_buffer_.as_span<DataUnit>();
    std::uintptr_t source = reinterpret_cast<std::uintptr_t>(&uart_.data.whole);
    rx_dma_resource_->ConfigureCopyFromPeripheral(source, rx_span_);
    rx_dma_resource_->Enable();    // start the DMA stream

    return core::Status{};
}

void Driver::HandleInterrupt(void) {
    peripherals::UniversalAsynchronousReceiverTransmitter::Status status = uart_.status;    // read
    if constexpr (debug::uart_isr) {
        jarnax::print(
            "UART Status: %" PRIx32 " pe:%" PRIu32 " fe:%" PRIu32 " nf:%" PRIu32 " oe:%" PRIu32 " id:%" PRIu32 " rxne:%" PRIu32 " txe:%" PRIu32
            " tc:%" PRIu32 "\r\n",
            status.whole,
            static_cast<uint32_t>(status.bits.parity_error),
            static_cast<uint32_t>(status.bits.framing_error),
            static_cast<uint32_t>(status.bits.noise_flag),
            static_cast<uint32_t>(status.bits.overrun_error),
            static_cast<uint32_t>(status.bits.idle),
            static_cast<uint32_t>(status.bits.receive_buffer_not_empty),
            static_cast<uint32_t>(status.bits.transmit_buffer_empty),
            static_cast<uint32_t>(status.bits.transmit_complete)
        );
    }

    statistics_.overrun_error += status.bits.overrun_error;
    statistics_.framing_error += status.bits.framing_error;
    statistics_.noise_error += status.bits.noise_flag;
    statistics_.parity_error += status.bits.parity_error;
    statistics_.idle += status.bits.idle;
    statistics_.receive_buffer_not_empty += status.bits.receive_buffer_not_empty;
    statistics_.transmit_buffer_empty += status.bits.transmit_buffer_empty;
    statistics_.transmit_complete += status.bits.transmit_complete;

    if (status.bits.transmit_buffer_empty) {
        if constexpr (configure::use_uart_as == configure::Mode::Interrupt) {
            if (tx_index_ < tx_span_.count()) {
                // write the next byte to the UART data register
                uart_.data.bits.data = tx_span_[tx_index_++];    // write
                // clear the TC flag too since we aren't done yet
                status.bits.transmit_complete = 0;    // clear TC flag
                uart_.status = status;                // write
                statistics_.bytes_transmitted++;
            } else {
                // disable TXE interrupt in Control1
                peripherals::UniversalAsynchronousReceiverTransmitter::Control1 control1 = uart_.control1;    // read
                control1.bits.transmit_empty_interrupt_enable = 0;                                            // disable TXE interrupt
                uart_.control1 = control1;                                                                    // write
            }
        } else {
            // DMA is used for TX, so we don't need to do anything here
            // the DMA will handle the TXE signal
        }
    }
    if (status.bits.transmit_complete) {
        // disable TC interrupt in Control1
        peripherals::UniversalAsynchronousReceiverTransmitter::Control1 control1 = uart_.control1;    // read
        control1.bits.transfer_complete_interrupt_enable = 0;                                         // disable TC interrupt
        uart_.control1 = control1;                                                                    // write

        tx_ready_ = true;     // set the flag to indicate that the DMA is ready to send more data
    }
    status.whole = 0U;        // clear all the flags
    uart_.status = status;    // write
}

bool Driver::Execute(void) {
    // not sure what to do yet...
    return true;
}

core::Status Driver::Enqueue(core::Span<DataUnit const> const& data) {
    core::Status status{};
    if (data.count() == 0) {
        status = core::Status{core::Result::InvalidValue, core::Cause::Parameter};
        return status;
    }
    peripherals::UniversalAsynchronousReceiverTransmitter::Control1 control1;
    if (tx_ready_) {
        // get a span of the rx buffer
        tx_span_ = tx_dma_buffer_.as_span<DataUnit>();
        if (tx_span_.IsEmpty()) {
            status = core::Status{core::Result::NotEnough, core::Cause::Resource};
            return status;
        }
        // copy the data into the buffer at the beginning
        memory::copy(tx_span_.data(), data.data(), data.count());
        // resize the tx span
        tx_span_.resize(data.count());
        tx_index_ = 0U;

        tx_ready_ = false;

        if constexpr (configure::use_usart_as == configure::Mode::Dma) {
            // setup the DMA stream
            tx_dma_resource_->ConfigureCopyToPeripheral(tx_span_, reinterpret_cast<std::uintptr_t>(&uart_.data.whole));
            // enable the DMA transmit stream in the USART
            peripherals::UniversalAsynchronousReceiverTransmitter::Control3 control3 = uart_.control3;    // read
            control3.bits.direct_memory_access_transmitter = 1;                                           // DMA transmitter enabled
            uart_.control3 = control3;                                                                    // write
            // clear the TC flag to indicate that the DMA is ready to send more data
            peripherals::UniversalAsynchronousReceiverTransmitter::Status status_reg = uart_.status;    // read
            status_reg.bits.transmit_complete = 0;                                                      // clear TC flag
            uart_.status = status_reg;                                                                  // write
            tx_dma_resource_->Enable();                                                                 // start the DMA stream
        } else {
            // don't write anything yet, let the TXE interrupt do it
            // enable TC interrupt in Control1 (we'll use that to end the TX sequence)
            control1 = uart_.control1;                               // read
            control1.bits.transfer_complete_interrupt_enable = 1;    // enable TC interrupt
            control1.bits.transmit_empty_interrupt_enable = 1;       // enable TXE interrupt
            uart_.control1 = control1;                               // write
        }
    } else {
        status = core::Status{core::Result::Busy, core::Cause::Resource};
    }
    return status;
}

core::Status Driver::Dequeue(core::Span<DataUnit>& data) {
    core::Status status{};
    if (data.count() == 0) {
        status = core::Status{core::Result::InvalidValue, core::Cause::Parameter};
    }
    return status;
}
}    // namespace uart
}    // namespace stm32

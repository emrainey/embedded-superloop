#include "stm32/usart/Driver.hpp"
#include <cmath>    // for std::floor
#include <jarnax/print.hpp>
#include <memory.hpp>
#include "cortex/vectors.hpp"
#include "stm32/configure.hpp"

namespace stm32 {
usart::Driver* usart_instances[4] = {nullptr, nullptr, nullptr, nullptr};         // 4, 5, 7, 8
usart::Statistics* usart_statistics[4] = {nullptr, nullptr, nullptr, nullptr};    // 4, 5, 7, 8

/// Interrupt service routine for USART1
void usart1_isr(void) {
    cortex::extended_vector_statistics.count[to_underlying(stm32::InterruptRequest::UniversalSynchronousAsynchronousReceiverTransmitter1)]++;
    if (usart_instances[0]) {
        usart_instances[0]->HandleInterrupt();
    }
}

/// Interrupt service routine for USART2
void usart2_isr(void) {
    cortex::extended_vector_statistics.count[to_underlying(stm32::InterruptRequest::UniversalSynchronousAsynchronousReceiverTransmitter2)]++;
    if (usart_instances[1]) {
        usart_instances[1]->HandleInterrupt();
    }
}

/// Interrupt service routine for USART3
void usart3_isr(void) {
    cortex::extended_vector_statistics.count[to_underlying(stm32::InterruptRequest::UniversalSynchronousAsynchronousReceiverTransmitter3)]++;
    if (usart_instances[2]) {
        usart_instances[2]->HandleInterrupt();
    }
}

/// Interrupt service routine for USART6
void usart6_isr(void) {
    cortex::extended_vector_statistics.count[to_underlying(stm32::InterruptRequest::UniversalSynchronousAsynchronousReceiverTransmitter6)]++;
    if (usart_instances[3]) {
        usart_instances[3]->HandleInterrupt();
    }
}

namespace usart {
Driver::Driver(
    peripherals::UniversalSynchronousAsynchronousReceiverTransmitter volatile& usart, dma::Manager& dma_driver, cortex::Peripheral rx_peripheral,
    cortex::Peripheral tx_peripheral, core::Allocator& dma_allocator, std::size_t dma_allocation_size
)
    : Statistician{}
    , usart_{usart}
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
    if (&usart == &peripherals::usart1) {
        usart_instances[0] = this;
        usart_statistics[0] = &statistics_;
    } else if (&usart == &peripherals::usart2) {
        usart_instances[1] = this;
        usart_statistics[1] = &statistics_;
    } else if (&usart == &peripherals::usart3) {
        usart_instances[2] = this;
        usart_statistics[2] = &statistics_;
    } else if (&usart == &peripherals::usart6) {
        usart_instances[3] = this;
        usart_statistics[3] = &statistics_;
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
    stm32::peripherals::UniversalSynchronousAsynchronousReceiverTransmitter::BaudRate brr;
    stm32::peripherals::UniversalSynchronousAsynchronousReceiverTransmitter::Control1 control1;
    control1 = usart_.control1;    // read
    uint32_t over8u = control1.bits.oversampling_mode == 1 ? 8 : 16;
    float over8f = control1.bits.oversampling_mode ? 8.0f : 16.0f;
    float divider = static_cast<float>(peripheral_frequency_.value()) / static_cast<float>(baud_rate * over8u);
    float floor = std::floor(divider);
    float fract = divider - floor;
    uint32_t mantissa = static_cast<uint32_t>(floor);
    uint32_t fraction = static_cast<uint32_t>(std::round(fract * over8f));
    brr.bits.div_mantissa = mantissa & 0xFFF;
    brr.bits.div_fraction = fraction & 0x0F;
    usart_.baudrate = brr;    // write
    if constexpr (debug::usart) {
        jarnax::print(
            "USART divider: %lf mantissa:%" PRIu32 " fraction:%" PRIu32 "\r\n",
            static_cast<double>(divider),
            static_cast<uint32_t>(brr.bits.div_mantissa),
            static_cast<uint32_t>(brr.bits.div_fraction)
        );
    }
}

uint32_t Driver::GetBaudRate(void) const {
    stm32::peripherals::UniversalSynchronousAsynchronousReceiverTransmitter::Control1 control1 = usart_.control1;    // read
    stm32::peripherals::UniversalSynchronousAsynchronousReceiverTransmitter::BaudRate brr = usart_.baudrate;         // read
    // uint32_t over8u = control1.bits.oversampling_mode == 1 ? 8 : 16;
    float over8f = control1.bits.oversampling_mode ? 8.0f : 16.0f;
    float divider = (static_cast<float>(brr.bits.div_mantissa) + (static_cast<float>(brr.bits.div_fraction) / over8f));
    uint32_t baud_rate = static_cast<uint32_t>(static_cast<float>(peripheral_frequency_.value()) / (divider * over8f));
    if constexpr (debug::usart) {
        jarnax::print(
            "USART divider: %lf mantissa:%" PRIu32 " fraction:%" PRIu32 " => BaudRate: %" PRIu32 "\r\n",
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

    stm32::peripherals::UniversalSynchronousAsynchronousReceiverTransmitter::Control1 control1;
    stm32::peripherals::UniversalSynchronousAsynchronousReceiverTransmitter::Control2 control2;
    stm32::peripherals::UniversalSynchronousAsynchronousReceiverTransmitter::Control3 control3;
    // disable the USART
    control1 = usart_.control1;    // read
    control1.whole = 0U;           // clear
    usart_.control1 = control1;    // write

    control2 = usart_.control2;    // read
    control2.whole = 0U;           // clear
    usart_.control2 = control2;    // write

    control3 = usart_.control3;    // read
    control3.whole = 0U;           // clear
    usart_.control3 = control3;    // write
    return status;
}

core::Status Driver::Configure(uint32_t desired_baud_rate, bool parity, uint8_t stop_bits) {
    stm32::peripherals::UniversalSynchronousAsynchronousReceiverTransmitter::Control1 control1;
    stm32::peripherals::UniversalSynchronousAsynchronousReceiverTransmitter::Control2 control2;
    stm32::peripherals::UniversalSynchronousAsynchronousReceiverTransmitter::Control3 control3;

    control1 = usart_.control1;    // read
    control2 = usart_.control2;    // read
    control3 = usart_.control3;    // read

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
    control3.whole = 0U;           // clear

    usart_.control1 = control1;    // write
    usart_.control2 = control2;    // write
    usart_.control3 = control3;    // write

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
    usart_.control3 = control3;    // write

    // Setup the RX DMA stream
    rx_span_ = rx_dma_buffer_.as_span<DataUnit>();
    std::uintptr_t source = reinterpret_cast<std::uintptr_t>(&usart_.data.whole);
    rx_dma_resource_->ConfigureCopyFromPeripheral(source, rx_span_);
    rx_dma_resource_->Enable();    // start the DMA stream

    return core::Status{};
}

void Driver::HandleInterrupt(void) {
    peripherals::UniversalSynchronousAsynchronousReceiverTransmitter::Status status = usart_.status;    // read
    if constexpr (debug::usart_isr) {
        jarnax::print(
            "USART Status: %" PRIx32 " pe:%" PRIu32 " fe:%" PRIu32 " nf:%" PRIu32 " oe:%" PRIu32 " id:%" PRIu32 " rxne:%" PRIu32 " txe:%" PRIu32
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
        if constexpr (configure::use_usart_as == configure::Mode::Interrupt) {
            if (tx_index_ < tx_span_.count()) {
                // write the next byte to the USART data register
                usart_.data.bits.data = tx_span_[tx_index_++];    // write
                // clear the TC flag too since we aren't done yet
                status.bits.transmit_complete = 0;    // clear TC flag
                usart_.status = status;               // write
                statistics_.bytes_transmitted++;
            } else {
                // disable TXE interrupt in Control1
                peripherals::UniversalSynchronousAsynchronousReceiverTransmitter::Control1 control1 = usart_.control1;    // read
                control1.bits.transmit_empty_interrupt_enable = 0;                                                        // disable TXE interrupt
                usart_.control1 = control1;                                                                               // write
            }
        } else {
            // DMA is used for TX, so we don't need to do anything here
            // the DMA will handle the TXE signal
        }
    }
    if (status.bits.transmit_complete) {
        // disable TC interrupt in Control1
        peripherals::UniversalSynchronousAsynchronousReceiverTransmitter::Control1 control1 = usart_.control1;    // read
        control1.bits.transfer_complete_interrupt_enable = 0;                                                     // disable TC interrupt
        usart_.control1 = control1;                                                                               // write

        tx_ready_ = true;      // set the flag to indicate that the DMA is ready to send more data
    }
    status.whole = 0U;         // clear all the flags
    usart_.status = status;    // write
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
    peripherals::UniversalSynchronousAsynchronousReceiverTransmitter::Control1 control1;
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
            tx_dma_resource_->ConfigureCopyToPeripheral(tx_span_, reinterpret_cast<std::uintptr_t>(&usart_.data.whole));
            // enable the DMA transmit stream in the USART
            peripherals::UniversalSynchronousAsynchronousReceiverTransmitter::Control3 control3 = usart_.control3;    // read
            control3.bits.direct_memory_access_transmitter = 1;                                                       // DMA transmitter enabled
            usart_.control3 = control3;                                                                               // write
            // clear the TC flag to indicate that the DMA is ready to send more data
            peripherals::UniversalSynchronousAsynchronousReceiverTransmitter::Status status_reg = usart_.status;    // read
            status_reg.bits.transmit_complete = 0;                                                                  // clear TC flag
            usart_.status = status_reg;                                                                             // write
            tx_dma_resource_->Enable();                                                                             // start the DMA stream
        } else {
            // don't write anything yet, let the TXE interrupt do it
            // enable TC interrupt in Control1 (we'll use that to end the TX sequence)
            control1 = usart_.control1;                              // read
            control1.bits.transfer_complete_interrupt_enable = 1;    // enable TC interrupt
            control1.bits.transmit_empty_interrupt_enable = 1;       // enable TXE interrupt
            usart_.control1 = control1;                              // write
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
}    // namespace usart
}    // namespace stm32

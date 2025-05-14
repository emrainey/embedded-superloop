#include "board.hpp"
#include <cmath>
#include "memory.hpp"
#include "jarnax/print.hpp"
#include "stm32/UsartDriver.hpp"

namespace stm32 {

UsartDriver* usart_instances[4] = {nullptr, nullptr, nullptr, nullptr};                 // 4, 5, 7, 8
UsartDriver::Statistics* usart_statistics[4] = {nullptr, nullptr, nullptr, nullptr};    // 4, 5, 7, 8

void usart1_isr(void) {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::UniversalSynchronousAsynchronousReceiverTransmitter1)]++;
    if (usart_instances[0]) {
        usart_instances[0]->HandleInterrupt();
    }
}

void usart2_isr(void) {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::UniversalSynchronousAsynchronousReceiverTransmitter2)]++;
    if (usart_instances[1]) {
        usart_instances[1]->HandleInterrupt();
    }
}

void usart3_isr(void) {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::UniversalSynchronousAsynchronousReceiverTransmitter3)]++;
    if (usart_instances[2]) {
        usart_instances[2]->HandleInterrupt();
    }
}

void usart6_isr(void) {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::UniversalSynchronousAsynchronousReceiverTransmitter6)]++;
    if (usart_instances[3]) {
        usart_instances[3]->HandleInterrupt();
    }
}

UsartDriver::UsartDriver(
    registers::UniversalSynchronousAsynchronousReceiverTransmitter volatile& usart,
    dma::Driver& dma_driver,
    dma::Peripheral rx_peripheral,
    dma::Peripheral tx_peripheral,
    core::Allocator& dma_allocator
)
    : usart_{usart}
    , dma_driver_{dma_driver}
    , rx_peripheral_{rx_peripheral}
    , rx_dma_stream_{*dma_driver_.Assign(rx_peripheral)}
    , rx_dma_stream_index_{dma::Driver::NumStreams}
    , tx_peripheral_{tx_peripheral}
    , tx_dma_stream_{*dma_driver_.Assign(tx_peripheral)}
    , tx_dma_stream_index_{dma::Driver::NumStreams}
    , dma_allocator_{dma_allocator}
    , rx_dma_buffer_{usart_rx_dma_buffer_size, dma_allocator_}
    , rx_span_{}
    , tx_dma_buffer_{usart_tx_dma_buffer_size, dma_allocator_}
    , tx_ready_{true}
    , tx_span_{}
    , tx_index_{0U} {
    if (&usart == &registers::usart1) {
        usart_instances[0] = this;
        usart_statistics[0] = &statistics_;
    } else if (&usart == &registers::usart2) {
        usart_instances[1] = this;
        usart_statistics[1] = &statistics_;
    } else if (&usart == &registers::usart3) {
        usart_instances[2] = this;
        usart_statistics[2] = &statistics_;
    } else if (&usart == &registers::usart6) {
        usart_instances[3] = this;
        usart_statistics[3] = &statistics_;
    }
}

void UsartDriver::ComputeBaudRate(uint32_t baud_rate) const {
    // The divider is calculated as follows:
    // Divider = (peripheral_frequency_ / (baud_rate * over8))
    // The USART peripheral uses a oversampling rate based on the control register.
    // The divider is a 12-bit value, so the maximum value is 0xFFF.
    // The minimum value is 0.
    // The divider is rounded to the nearest integer.
    // The divider is set in the BRR register.
    stm32::registers::UniversalSynchronousAsynchronousReceiverTransmitter::BaudRate brr;
    stm32::registers::UniversalSynchronousAsynchronousReceiverTransmitter::Control1 control1;
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
    if constexpr (jarnax::debug::usart) {
        jarnax::print("USART divider: %lf mantissa:%u fraction:%u\r\n", divider, brr.bits.div_mantissa, brr.bits.div_fraction);
    }
}

uint32_t UsartDriver::GetBaudRate(void) const {
    stm32::registers::UniversalSynchronousAsynchronousReceiverTransmitter::Control1 control1 = usart_.control1;    // read
    stm32::registers::UniversalSynchronousAsynchronousReceiverTransmitter::BaudRate brr = usart_.baudrate;         // read
    // uint32_t over8u = control1.bits.oversampling_mode == 1 ? 8 : 16;
    float over8f = control1.bits.oversampling_mode ? 8.0f : 16.0f;
    float divider = (static_cast<float>(brr.bits.div_mantissa) + (static_cast<float>(brr.bits.div_fraction) / over8f));
    uint32_t baud_rate = static_cast<uint32_t>(static_cast<float>(peripheral_frequency_.value()) / (divider * over8f));
    if constexpr (jarnax::debug::usart) {
        jarnax::print(
            "USART divider: %lf mantissa:%u fraction:%u => BaudRate: %lu\r\n", divider, brr.bits.div_mantissa, brr.bits.div_fraction, baud_rate
        );
    }
    return baud_rate;
}

core::Status UsartDriver::Initialize(core::units::Hertz peripheral_frequency) {
    core::Status status{};
    peripheral_frequency_ = peripheral_frequency;
    rx_dma_stream_index_ = dma_driver_.GetStreamIndex(rx_dma_stream_);
    tx_dma_stream_index_ = dma_driver_.GetStreamIndex(tx_dma_stream_);
    if (rx_dma_stream_index_ == dma::Driver::NumStreams) {
        return core::Status{core::Result::NotAvailable, core::Cause::Resource};
    }
    if (tx_dma_stream_index_ == dma::Driver::NumStreams) {
        return core::Status{core::Result::NotAvailable, core::Cause::Resource};
    }
    dma_driver_.Initialize(rx_dma_stream_, rx_dma_stream_index_, rx_peripheral_);
    dma_driver_.Initialize(tx_dma_stream_, tx_dma_stream_index_, tx_peripheral_);

    stm32::registers::UniversalSynchronousAsynchronousReceiverTransmitter::Control1 control1;
    stm32::registers::UniversalSynchronousAsynchronousReceiverTransmitter::Control2 control2;
    stm32::registers::UniversalSynchronousAsynchronousReceiverTransmitter::Control3 control3;
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

    // Allocate a buffer for the RX and TX streams
    return status;
}

core::Status UsartDriver::Configure(uint32_t desired_baud_rate, bool parity, uint8_t stop_bits) {
    stm32::registers::UniversalSynchronousAsynchronousReceiverTransmitter::Control1 control1;
    stm32::registers::UniversalSynchronousAsynchronousReceiverTransmitter::Control2 control2;
    stm32::registers::UniversalSynchronousAsynchronousReceiverTransmitter::Control3 control3;

    control1 = usart_.control1;    // read
    control2 = usart_.control2;    // read
    control3 = usart_.control3;    // read

    // control1
    control1.whole = 0U;                                     // clear
    control1.bits.parity_control_enable = parity ? 1 : 0;    // parity enabled or not
    if (parity) {
        control1.bits.parity_select = 1;    // even parity
    }
    control1.bits.receiver_enable = 1;       // receiver enabled
    control1.bits.transmitter_enable = 1;    // transmitter enabled
    control1.bits.uxart_enable = 1;          // USART enabled
    // control2
    control2.whole = 0U;                             // clear
    control2.bits.stop = stop_bits ? 0b00 : 0b10;    // 1 stop bit, 2 stop bits

    // control3
    control3.whole = 0U;    // clear

    usart_.control1 = control1;    // write
    usart_.control2 = control2;    // write
    usart_.control3 = control3;    // write

    ComputeBaudRate(desired_baud_rate);
    uint32_t actual_baud_rate = GetBaudRate();
    if (actual_baud_rate != desired_baud_rate) {
        uint32_t distance = (actual_baud_rate > desired_baud_rate) ? actual_baud_rate - desired_baud_rate : desired_baud_rate - actual_baud_rate;
        float error = static_cast<float>(distance) / static_cast<float>(desired_baud_rate);
        if constexpr (jarnax::debug::usart) {
            jarnax::print("USART BaudRate error: %f %% (%" PRIu32 ")\r\n", error * 100.0f, distance);
        }
    }

    // Enable RX DMA
    control3.bits.direct_memory_access_receiver = 1;    // DMA receiver enabled
    // control3.bits.direct_memory_access_transmitter = 1;    // DMA transmitter enabled
    usart_.control3 = control3;    // write

    // Setup the RX DMA stream
    rx_span_ = rx_dma_buffer_.as_span<DataUnit>();
    dma_driver_.CopyFromPeripheral(rx_dma_stream_, rx_span_.data(), &usart_.data.whole, rx_span_.count());
    dma_driver_.Start(rx_dma_stream_);    // start the DMA stream

    return core::Status{};
}

void UsartDriver::HandleInterrupt(void) {
    registers::UniversalSynchronousAsynchronousReceiverTransmitter::Status status = usart_.status;    // read
    if constexpr (jarnax::debug::usart_isr) {
        jarnax::print(
            "USART Status: %" PRIx32 " pe:%u fe:%u nf:%u oe:%u id:%u rxne:%u txe:%u tc:%u\r\n",
            status.whole,
            status.bits.parity_error,
            status.bits.framing_error,
            status.bits.noise_flag,
            status.bits.overrun_error,
            status.bits.idle,
            status.bits.receive_buffer_not_empty,
            status.bits.transmit_buffer_empty,
            status.bits.transmit_complete
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
        if constexpr (not use_dma_for_usart_tx) {
            if (tx_index_ < tx_span_.count()) {
                // write the next byte to the USART data register
                usart_.data.bits.data = tx_span_[tx_index_++];    // write
                // clear the TC flag too since we aren't done yet
                status.bits.transmit_complete = 0;    // clear TC flag
                usart_.status = status;               // write
                statistics_.bytes_transmitted++;
            } else {
                // disable TXE interrupt in Control1
                registers::UniversalSynchronousAsynchronousReceiverTransmitter::Control1 control1 = usart_.control1;    // read
                control1.bits.transmit_empty_interrupt_enable = 0;                                                      // disable TXE interrupt
                usart_.control1 = control1;                                                                             // write
            }
        } else {
            // DMA is used for TX, so we don't need to do anything here
            // the DMA will handle the TXE signal
        }
    }
    if (status.bits.transmit_complete) {
        // disable TC interrupt in Control1
        registers::UniversalSynchronousAsynchronousReceiverTransmitter::Control1 control1 = usart_.control1;    // read
        control1.bits.transfer_complete_interrupt_enable = 0;                                                   // disable TC interrupt
        usart_.control1 = control1;                                                                             // write

        tx_ready_ = true;    // set the flag to indicate that the DMA is ready to send more data
    }
    status.whole = 0U;         // clear all the flags
    usart_.status = status;    // write
}

core::Status UsartDriver::Enqueue(core::Span<DataUnit const> const& data) {
    core::Status status{};
    if (data.count() == 0) {
        status = core::Status{core::Result::InvalidValue, core::Cause::Parameter};
        return status;
    }
    registers::UniversalSynchronousAsynchronousReceiverTransmitter::Control1 control1;
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

        if constexpr (use_dma_for_usart_tx) {
            // setup the DMA stream
            dma_driver_.CopyToPeripheral(tx_dma_stream_, &usart_.data.whole, tx_span_.data(), tx_span_.count());
            // enable the DMA transmit stream in the USART
            registers::UniversalSynchronousAsynchronousReceiverTransmitter::Control3 control3 = usart_.control3;    // read
            control3.bits.direct_memory_access_transmitter = 1;                                                     // DMA transmitter enabled
            usart_.control3 = control3;                                                                             // write
            // clear the TC flag to indicate that the DMA is ready to send more data
            registers::UniversalSynchronousAsynchronousReceiverTransmitter::Status status_reg = usart_.status;    // read
            status_reg.bits.transmit_complete = 0;                                                                // clear TC flag
            usart_.status = status_reg;                                                                           // write

            dma_driver_.Start(tx_dma_stream_);    // start the DMA stream
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

core::Status UsartDriver::Dequeue(core::Span<DataUnit>& data) {
    core::Status status{};
    if (data.count() == 0) {
        status = core::Status{core::Result::InvalidValue, core::Cause::Parameter};
    }
    return status;
}

}    // namespace stm32
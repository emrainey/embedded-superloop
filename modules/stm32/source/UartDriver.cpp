#include "board.hpp"
#include "stm32/UartDriver.hpp"

namespace stm32 {

UartDriver* g_uart_instances[4] = {nullptr, nullptr, nullptr, nullptr};    // 4, 5, 7, 8

void uart4_isr(void) {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::UniversalAsynchronousReceiverTransmitter4)]++;
    if (g_uart_instances[0]) {
        g_uart_instances[0]->HandleInterrupt();
    }
}

void uart5_isr(void) {
    external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::UniversalAsynchronousReceiverTransmitter5)]++;
    if (g_uart_instances[1]) {
        g_uart_instances[1]->HandleInterrupt();
    }
}

void uart7_isr(void) {
    // external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::UniversalAsynchronousReceiverTransmitter7)]++;
    if (g_uart_instances[2]) {
        g_uart_instances[2]->HandleInterrupt();
    }
}

void uart8_isr(void) {
    // external_interrupt_statistics.count[to_underlying(stm32::InterruptRequest::UniversalAsynchronousReceiverTransmitter8)]++;
    if (g_uart_instances[3]) {
        g_uart_instances[3]->HandleInterrupt();
    }
}

UartDriver::UartDriver(
    registers::UniversalAsynchronousReceiverTransmitter volatile& uart,
    dma::Driver& dma_driver,
    dma::Peripheral rx_peripheral,
    dma::Peripheral tx_peripheral,
    core::Allocator& dma_allocator
)
    : uart_{uart}
    , dma_driver_{dma_driver}
    , rx_peripheral_{rx_peripheral}
    , rx_dma_stream_{*dma_driver_.Assign(rx_peripheral)}
    , rx_dma_stream_index_{dma::Driver::NumStreams}
    , tx_peripheral_{tx_peripheral}
    , tx_dma_stream_{*dma_driver_.Assign(tx_peripheral)}
    , tx_dma_stream_index_{dma::Driver::NumStreams}
    , dma_allocator_{dma_allocator} {
    if (&uart == &registers::uart4) {
        g_uart_instances[0] = this;
    } else if (&uart == &registers::uart5) {
        g_uart_instances[1] = this;
    } else if (&uart == &registers::uart7) {
        g_uart_instances[2] = this;
    } else if (&uart == &registers::uart8) {
        g_uart_instances[3] = this;
    }
}

core::Status UartDriver::Initialize(core::units::Hertz peripheral_frequency) {
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

    stm32::registers::UniversalAsynchronousReceiverTransmitter::Control1 control1;
    stm32::registers::UniversalAsynchronousReceiverTransmitter::Control2 control2;
    stm32::registers::UniversalAsynchronousReceiverTransmitter::Control3 control3;
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

core::Status UartDriver::Configure(uint32_t baud_rate, bool parity, uint8_t stop_bits) {
    static_cast<void>(baud_rate);
    static_cast<void>(parity);
    static_cast<void>(stop_bits);
    return core::Status{core::Result::NotImplemented, core::Cause::State};
}

void UartDriver::HandleInterrupt(void) {
    registers::UniversalAsynchronousReceiverTransmitter::Status status = uart_.status;    // read
    // if (status.bits.polarity_error) {
    //     jarnax::print("UART PE\n");
    // }
    // if (status.bits.framing_error) {
    //     jarnax::print("UART FE\n");
    // }
    // if (status.bits.noise_flag) {
    //     jarnax::print("UART NF\n");
    // }
    // if (status.bits.overrun_error) {
    //     jarnax::print("UART ORE\n");
    // }
    // if (status.bits.idle) {
    //     jarnax::print("UART IDLE\n");
    // }
}

core::Status UartDriver::Enqueue(core::Span<DataUnit> const& data) {
    core::Status status{};
    if (data.count() == 0) {
        status = core::Status{core::Result::InvalidValue, core::Cause::Parameter};
    }
    return status;
}

core::Status UartDriver::Dequeue(core::Span<DataUnit>& data) {
    core::Status status{};
    if (data.count() == 0) {
        status = core::Status{core::Result::InvalidValue, core::Cause::Parameter};
    }
    return status;
}

}    // namespace stm32

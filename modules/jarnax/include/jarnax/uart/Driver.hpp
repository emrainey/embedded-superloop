#ifndef JARNAX_UART_DRIVER_HPP
#define JARNAX_UART_DRIVER_HPP

#include "core/Status.hpp"
#include "core/Span.hpp"

namespace jarnax {

/// @brief The UART Namespace
namespace uart {

class Driver {
public:
    /// The data unit of the UART Driver
    using DataUnit = uint8_t;

    /// @brief Configures the UART Driver
    /// @param baud_rate The baud rate to use for the UART
    /// @return
    virtual core::Status Configure(uint32_t baud_rate, bool parity, uint8_t stop_bits) = 0;

    /// @brief Enqueues the data to be sent to the UART
    /// @param data The data to be sent
    /// @retval Success if the Data was enqueued.
    /// @retval NoResource if the queue is full.
    virtual core::Status Enqueue(core::Span<DataUnit> const& data) = 0;

    /// @brief Dequeues the data from the UART
    /// @param data The span to receive the data into
    /// @return Success if the data was dequeued.
    /// @retval NoResource if the queue is empty.
    virtual core::Status Dequeue(core::Span<DataUnit>& data) = 0;

protected:
    ~Driver() = default;
};

}    // namespace uart

}    // namespace jarnax

#endif    // JARNAX_UART_DRIVER_HPP

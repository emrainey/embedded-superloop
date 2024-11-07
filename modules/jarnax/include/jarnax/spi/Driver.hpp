#ifndef JARNAX_SPI_DRIVER_HPP
#define JARNAX_SPI_DRIVER_HPP

#include "jarnax/gpio/Output.hpp"
#include "jarnax/Coordinator.hpp"
#include "core/Buffer.hpp"

namespace jarnax {
namespace spi {

/// @brief The Clock Polarity (CPOL)
enum class ClockPolarity : bool {
    IdleLow = false,
    IdleHigh = true
};

/// @brief The Clock Phase (CPHA)
enum class ClockPhase : bool {
    ImmediateEdge = false,
    FirstAfterEdge = true
};

/// @brief Defines a CRTP Transactable object for SPI transactions
class Transaction : public jarnax::Transactable<Transaction, 3U> {
public:
    Transaction(jarnax::Timer& timer)
        : jarnax::Transactable<Transaction, 3>{timer}
        , polarity{ClockPolarity::IdleHigh}
        , phase{ClockPhase::FirstAfterEdge}
        // , chip_select{}
        {}

    /// The SPI Clock Polarity
    ClockPolarity polarity;
    /// The SPI Clock Phase
    ClockPhase phase;
    /// The NSS or Chip Select
    // jarnax::gpio::Output chip_select;
    /// Use Move Sematics on the Buffer to shift ownership/access to the transacton so that the Driver can use it
    /// The format of the data buffer and the expected send + response size must total the buffer size.
    core::Buffer<uint16_t> buffer;
    /// The number of bytes to send
    std::size_t send_size;
    /// The number of bytes to receive
    std::size_t receive_size;

    void Clear() {
        polarity = ClockPolarity::IdleHigh;
        phase = ClockPhase::FirstAfterEdge;
        // chip_select.Value(false);
    }
};

using Transactor = jarnax::Transactor<spi::Transaction>;
using Coordinator = jarnax::Coordinator<spi::Transaction, 8U>;

/// The SPI Driver Interface is a Transactor of SPI Transactions and the Coordinator of the SPI Transactions
class Driver : public spi::Coordinator {
public:
    Driver(spi::Transactor& tr) : spi::Coordinator{tr} {}
};

}  // namespace spi
}  // namespace jarnax

#endif // JARNAX_SPI_DRIVER_HPP
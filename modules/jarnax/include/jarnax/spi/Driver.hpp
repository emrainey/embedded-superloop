#ifndef JARNAX_SPI_DRIVER_HPP
#define JARNAX_SPI_DRIVER_HPP

#include "jarnax/gpio/Output.hpp"
#include "jarnax/Transactable.hpp"
#include "jarnax/Coordinator.hpp"
#include "core/Buffer.hpp"

namespace jarnax {

namespace spi {

/// @brief The default number of retries
static constexpr std::size_t DefaultRetries{3U};

/// @brief The number of transactions that can be queued
static constexpr std::size_t DefaultQueueDepth{8U};

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

/// @brief The Default data unit size of the SPI Driver
using DataUnit = uint8_t;

/// @brief Defines a CRTP Transactable object for SPI transactions
class Transaction : public jarnax::Transactable<Transaction, DefaultRetries> {
public:
    Transaction(jarnax::Timer& timer)
        : jarnax::Transactable<Transaction, DefaultRetries>{timer}
        , polarity{ClockPolarity::IdleLow}
        , phase{ClockPhase::ImmediateEdge}
        , chip_select{nullptr}
        , crc_polynomial{0x7U}    // default CRC-7
        , use_hardware_crc{false}
        , use_data_as_bytes{false}
        , buffer{}
        , send_size{0U}
        , receive_size{0U} {}

    /// The SPI Clock Polarity (CPOL)
    ClockPolarity polarity;
    /// The SPI Clock Phase (CPHA)
    ClockPhase phase;
    /// The NSS or Chip Select (nullptr if not used and the NSS is controlled by the peripheral)
    jarnax::gpio::Output* chip_select;
    /// The CRC Polynomial if using hardware CRC
    uint16_t crc_polynomial;
    /// Enable Hardware CRC Calculation as the last data unit
    bool use_hardware_crc;
    /// Use the data as bytes or shorts
    bool use_data_as_bytes;
    /// Use Move Sematics on the Buffer to shift ownership/access to the transacton so that the Driver can use it
    /// The format of the data buffer and the expected send + response size must total the buffer size.
    core::Buffer<DataUnit> buffer;
    /// The number of bytes to send
    std::size_t send_size;
    /// The number of bytes that have sent
    std::size_t sent_size;
    /// The offset to the location to start receiving data
    std::size_t receive_offset;
    /// The number of bytes to receive
    std::size_t receive_size;
    /// The number of bytes that have been received
    std::size_t received_size;

    /// @brief Indicates if the transaction is empty
    /// @return True if the transaction buffer is empty
    bool IsEmpty() const { return buffer.IsEmpty(); }

    /// @brief Moves the buffer into the transaction
    /// @param buf The buffer to move into the transaction
    void Assign(core::Buffer<DataUnit>&& buf) { buffer = std::move(buf); }

    /// @brief Removes the buffer from the transaction and returns it to the caller
    /// @return A container of the buffer
    /// @post @ref Release() must be called to release the transaction
    core::Buffer<DataUnit> Relinquish(void) { return std::move(buffer); }

    void Clear() {
        polarity = ClockPolarity::IdleLow;
        phase = ClockPhase::ImmediateEdge;
        if (chip_select) {
            chip_select->Value(true);    // almost all SPI devices are active low
        }
        crc_polynomial = 0x7U;    // default CRC-7
        use_hardware_crc = false;
        use_data_as_bytes = false;
        buffer.Release();
        send_size = 0U;
        sent_size = 0U;
        receive_offset = 0U;
        receive_size = 0U;
        received_size = 0U;
    }
};

using Transactor = jarnax::Transactor<spi::Transaction>;
using Coordinator = jarnax::Coordinator<spi::Transaction, DefaultQueueDepth>;

/// The SPI Driver Interface has a Transactor of SPI Transactions and is a Coordinator of the SPI Transactions
class Driver : public Coordinator {
public:
    Driver(spi::Transactor& tr)
        : Coordinator{tr} {}
};
}    // namespace spi
}    // namespace jarnax
#endif    // JARNAX_SPI_DRIVER_HPP

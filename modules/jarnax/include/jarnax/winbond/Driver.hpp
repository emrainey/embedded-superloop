#ifndef JARNAX_WINBOND_DRIVER_HPP
#define JARNAX_WINBOND_DRIVER_HPP

/// @file
/// The Winbond Flash Driver over SPI
/// @details This driver is used to communicate with the Winbond Flash memory over SPI.

#include <core/Status.hpp>
#include <core/Buffer.hpp>
#include <core/Printer.hpp>
#include <jarnax/Loopable.hpp>
#include <jarnax/spi/Driver.hpp>
#include <jarnax/Timer.hpp>
#include <jarnax/CountDown.hpp>

namespace jarnax {
namespace winbond {

/// @brief The Winbond Flash Driver over SPI
class Driver : public jarnax::Loopable {
public:
    /// @brief Parameterized constructor
    Driver(Timer& timer, spi::Driver& driver, gpio::Output& chip_select, core::Allocator& dma_allocator);
    /// @brief Destructor
    ~Driver();

    /// @brief Initializes the driver before main
    core::Status Initialize(void);

    //==========================
    bool Execute(void) override;
    //==========================

protected:
    core::Status Reinitialize(void);

    /// @brief The reference to the local printer
    core::Printer& printer_;
    /// @brief The reference to the timer
    Timer& timer_;
    /// @brief The reference to the spi driver
    spi::Driver& driver_;
    /// @brief The reference to the chip select pin
    gpio::Output& chip_select_;
    /// @brief The reference to the DMA allocator
    core::Allocator& dma_allocator_;
    /// @brief The SPI buffer size
    size_t buffer_size_;
    /// @brief The SPI transaction
    spi::Transaction transaction_;
    /// @brief The SPI buffer for transactions
    core::Buffer<spi::DataUnit> buffer_;
    /// @brief The countdown for the startup time
    jarnax::CountDown startup_countdown_;
};
}    // namespace winbond
}    // namespace jarnax

#endif    // JARNAX_WINBOND_DRIVER_HPP
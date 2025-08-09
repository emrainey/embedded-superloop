#ifndef JARNAX_WINBOND_DRIVER_HPP
#define JARNAX_WINBOND_DRIVER_HPP

/// @file
/// The Winbond Flash Driver over SPI
/// @details This driver is used to communicate with the Winbond Flash memory over SPI.

#include <core/Buffer.hpp>
#include <core/Printer.hpp>
#include <core/Span.hpp>
#include <core/Status.hpp>
#include <jarnax/CountDown.hpp>
#include <jarnax/Loopable.hpp>
#include <jarnax/Timer.hpp>
#include <jarnax/drivers/w25q16bv/StateMachine.hpp>
#include <jarnax/spi/Driver.hpp>
#include <jarnax/w25q16bv/Driver.hpp>

namespace jarnax {
namespace drivers {
namespace w25q16bv {

/// @brief A convenience class to be used as a callback for filling out instructions to write to the Chip
class Functor {
public:
    virtual void operator()(core::Span<uint8_t>& data) = 0;

protected:
    ~Functor() = default;
};

/// @brief The Winbond Flash Driver over SPI
class Driver : public jarnax::w25q16bv::Driver, public jarnax::Loopable, protected Listener, protected Executor {
public:
    /// @brief Parameterized constructor
    Driver(Timer& timer, spi::Driver& driver, gpio::Output& chip_select, core::Allocator& dma_allocator);
    /// @brief Destructor
    ~Driver();

    //==========================
    bool Execute(void) override;
    //==========================
    core::Status Initialize(void) override;
    void PowerUp(void) override;
    bool IsPowered(void) const override;
    bool IsIdentified(void) const override;
    bool IsReady(void) const override;
    void PowerDown(void) override;

protected:
    /// @brief Reinitializes the transaction
    /// @param instruction The instruction to send
    /// @param write_size The size of the write buffer
    /// @param read_size The size of the read buffer
    /// @param callback The callback used to write the data into the buffer
    /// @return
    core::Status Reinitialize(::w25q16bv::Instruction instruction, size_t write_size, size_t read_size, Functor& callback);
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // StateMachine Callbacks
    core::Status Command(::w25q16bv::Instruction instruction) override;
    bool IsCommandComplete(void) const override;
    core::Status GetStatusAndData(void) override;
    bool IsPresent(void) const override;
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    void OnEvent(Event event, core::Status status) override;
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

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
    /// @brief The StateMachine for the W25Q16BV driver
    jarnax::drivers::w25q16bv::StateMachine state_machine_;
    /// @brief Shortcut to know if the chip is powered
    bool powered_;
    /// @brief Shortcut to know if the chip is identified
    bool identified_;
    /// @brief The last Instruction
    Instruction last_instruction_;
    /// The next event to send to the state machine
    jarnax::drivers::w25q16bv::Event next_event_;
};
}    // namespace w25q16bv
}    // namespace drivers
}    // namespace jarnax

#endif    // JARNAX_WINBOND_DRIVER_HPP

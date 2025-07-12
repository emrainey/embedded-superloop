#ifndef JARNAX_DRIVERS_SSD1306_DRIVER_HPP
#define JARNAX_DRIVERS_SSD1306_DRIVER_HPP

/// @file
/// The SSD1306 Driver implementation
/// @details This driver is used to communicate with the SSD1306 OLED display over I2C.

#include "jarnax/Timer.hpp"
#include "jarnax/i2c/Driver.hpp"
#include "jarnax/ssd1306/Driver.hpp"
#include "jarnax/drivers/ssd1306/StateMachine.hpp"

namespace jarnax {
namespace drivers {
namespace ssd1306 {

/// The SSD1306 Driver Implementation which extends the Application's Interface for the SSD1306 Driver as well as
/// the client to the State Machine to support operations to the SSD1306 OLED display.
class Driver : public jarnax::ssd1306::Driver, public jarnax::Loopable, protected jarnax::drivers::ssd1306::Client {
public:
    /// @brief Constructs the SSD1306 Driver.
    /// @param timer The system timer to use for transactions.
    /// @param i2c_driver The I2C driver to use for communication.
    /// @param allocator The allocator to use for dynamic memory.
    Driver(jarnax::Timer& timer, jarnax::i2c::Driver& i2c_driver, core::Allocator& allocator);

    /// @brief Initializes the SSD1306 Driver with the given I2C address.
    /// @param address The I2C address of the SSD1306 display.
    /// @return The status of the initialization.
    core::Status Initialize(jarnax::i2c::Address address);

    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    // jarnax::ssd1306::Driver interface
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    core::Status GetStatus(void) const override;
    ::ssd1306::Image128x32& GetImage(void) override;
    ::ssd1306::Screen128x32& GetScreen(void) override;
    void Update(void) override;
    bool IsUpdated(void) const override;

    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    // jarnax::Loopable interface
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    bool Execute() override;

    struct Statistics {
        core::units::MicroSeconds elapsed_time;    ///< The elapsed time for the last operation
        size_t prepared{0U};                       ///< The number of commands prepared for the last operation
        size_t buffer_invalid{0U};                 ///< The number of times the buffer was invalid for starting a transaction
        size_t issued{0U};                         ///< The number of commands issued for the last operation
        size_t completed{0U};                      ///< The number of commands completed for the last operation
        size_t failures{0U};                       ///< The number of failures for the last operation
        size_t updated{0U};                        ///< The number of times the display was updated
    };

    /// @brief Returns the statistics of the last operation.
    /// @return The statistics of the last operation.
    Statistics const& GetStatistics(void) const;

protected:
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    // jarnax::ssd1306::StateMachine::Client interface
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    bool IsPresent(void) const override;
    core::Status Prepare(Sequence sequence) override;
    core::Status PrepareRender(Sequence sequence) override;
    core::Status Issue(void) override;
    bool AreCommandsComplete(core::Status& status) override;
    void OnEvent(Event event, core::Status status) override;

    jarnax::Timer& timer_;                              ///< The System Timer to use for transactions
    jarnax::i2c::Driver& i2c_driver_;                   ///< The I2C Driver to use
    core::Buffer<jarnax::i2c::DataUnit> i2c_buffer_;    ///< The I2C Buffer to use for transactions
    jarnax::i2c::Transaction i2c_transaction_;          ///< The I2C Transaction to use
    jarnax::i2c::Address address_;                      ///< The I2C Address of the SSD1306
    core::Allocator& allocator_;                        ///< The Allocator to use for the I2C Buffer
    ::ssd1306::Image128x32 image_;                      ///< The Image to display
    ::ssd1306::Screen128x32 screen_;                    ///< The Screen to display the Image on
    StateMachine state_machine_;                        ///< The State Machine to manage the SSD1306 Driver
    Event next_event_;                                  ///< The next event to process in the state machine
    bool powered_;                                      ///< Is the SSD1306 powered on?
    bool updated_;                                      ///< Has the SSD1306 been updated?
    Statistics statistics_;                             ///< The statistics of the last operation
    core::Status status_;                               ///< The status of the last operation
};
}    // namespace ssd1306
}    // namespace drivers
}    // namespace jarnax

#endif    // JARNAX_DRIVERS_SSD1306_DRIVER_HPP
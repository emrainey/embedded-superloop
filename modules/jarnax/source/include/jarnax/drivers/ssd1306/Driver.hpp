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
/// The SSD1306 Driver Implementation
class Driver : public jarnax::ssd1306::Driver, public jarnax::Loopable, protected jarnax::drivers::ssd1306::Client {
public:
    Driver(jarnax::Timer& timer, jarnax::i2c::Driver& i2c_driver, core::Allocator& allocator);

    /// @brief Initializes the SSD1306 Driver with the given I2C address.
    /// @param address
    /// @return
    core::Status Initialize(jarnax::i2c::Address address);

    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // jarnax::ssd1306::Driver interface
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    ::ssd1306::Image128x32& GetImage(void) override;
    ::ssd1306::Screen128x32& GetScreen(void) override;
    void Update(void) override;
    bool IsUpdated(void) const override;

    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // jarnax::Loopable interface
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    bool Execute() override;

protected:
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // jarnax::ssd1306::StateMachine::Client interface
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    bool IsPresent(void) const override;
    core::Status Prepare(CommandSequence sequence) override;
    core::Status Issue(void) override;
    core::Status AreCommandsComplete(void) const override;
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
};
}    // namespace ssd1306
}    // namespace drivers
}    // namespace jarnax

#endif    // JARNAX_DRIVERS_SSD1306_DRIVER_HPP
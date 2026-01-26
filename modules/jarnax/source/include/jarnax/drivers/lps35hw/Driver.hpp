#ifndef LPS35HW_DRIVER_HPP_
#define LPS35HW_DRIVER_HPP_

/// @file
/// LPS35HW Driver Internal Implementation

#include <core/Buffer.hpp>
#include <core/Units.hpp>
#include "jarnax/drivers/lps35hw/StateMachine.hpp"
#include "jarnax/lps35hw/Driver.hpp"
#include "jarnax/spi/Driver.hpp"
#include "lps35hw.hpp"

namespace jarnax {
namespace drivers {
namespace lps35hw {

class Driver final : public jarnax::lps35hw::Driver, protected Callback {
public:
    /// @brief Constructor for the LPS35HW Driver
    /// @param timer The Timer to use for the state machine.
    /// @param duration The duration for the state machine polling cycles.
    /// @param spi The SPI Driver to use for communication with the chip.
    /// @param allocator The Allocator to use for the buffer.
    Driver(jarnax::Timer const& timer, core::units::Iota duration, jarnax::spi::Driver& spi, core::Allocator& allocator);
    ~Driver() = default;

    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // jarnax::lps35hw::Driver
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    core::Status Initialize() override;
    core::units::Pressure GetLastPressure() override;
    core::units::Temperature GetLastTemperature() override;

    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // Loopable
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    bool Execute() override;

protected:
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // StateMachine::Callback
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    core::Status StartRegisterRead(uint8_t address, uint8_t count) override;
    core::Status StartRegisterWrite(uint8_t address, uint8_t count, uint8_t value[]) override;
    core::Status GetRegisterValue(uint8_t address, uint8_t count, uint8_t value[]) override;
    void OnError(core::Status status) override;
    void OnReading(::lps35hw::RawPressure pressure, ::lps35hw::RawTemperature temperature) override;
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    core::Status InitializeTransaction(bool is_read, uint8_t address, uint8_t count, uint8_t data[]);

private:
    jarnax::spi::Driver& spi_;                                ///< The SPI Driver to use for communication with the chip.
    core::Buffer<jarnax::spi::DataUnit> buffer_;              ///< The buffer to use for communication with the chip.
    jarnax::spi::Transaction transaction_;                    ///< The SPI transaction to use for communication.
    core::units::Pressure last_pressure_;                     ///< The last pressure reading
    core::units::Temperature last_temperature_;               ///< The last temperature reading
    jarnax::drivers::lps35hw::StateMachine state_machine_;    ///< The state machine for the LPS35HW driver
    jarnax::drivers::lps35hw::Event event_;                   ///< The current event to process
    size_t const data_padding_{0U};                           ///< The data padding size for the SPI transaction
};

}    // namespace lps35hw
}    // namespace drivers
}    // namespace jarnax

#endif    // LPS35HW_DRIVER_HPP_

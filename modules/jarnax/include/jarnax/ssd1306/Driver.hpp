#ifndef JARNAX_SSD1306_DRIVER_HPP
#define JARNAX_SSD1306_DRIVER_HPP

/// @file
/// SSD1306 OLED Display Driver

#include "jarnax/Loopable.hpp"
#include "ssd1306.hpp"

namespace jarnax {
namespace ssd1306 {

using Image128x32 = ::ssd1306::Image128x32;
using Screen128x32 = ::ssd1306::Screen128x32;

/// @brief The Abstract Interface for the SSD1306 Driver to be used by Applications.
class Driver {
public:
    /// @return The current status of the driver
    /// @retval core::Result::NotReady if the driver is not ready to process commands yet, wait until Success.
    virtual core::Status GetStatus(void) const = 0;

    /// @brief Gets the current image object of the SSD1306.
    /// The Image useful for non-character drawing operations.
    /// @return A reference to the current image.
    virtual Image128x32& GetImage(void) = 0;

    /// @brief Gets the current screen object of the SSD1306.
    /// The Screen is useful for character drawing operations.
    /// @return A reference to the current screen.
    virtual Screen128x32& GetScreen(void) = 0;

    /// @brief Updates the SSD1306 display with the current data.
    virtual void Update(void) = 0;

    /// @brief Checks if the SSD1306 display has been updated.
    /// @return True ONCE if the display has been updated, false otherwise afterwards.
    virtual bool IsUpdated(void) const = 0;

protected:
    ~Driver() = default;
};

}    // namespace ssd1306
}    // namespace jarnax

#endif    // JARNAX_SSD1306_DRIVER_HPP

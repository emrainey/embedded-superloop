#ifndef JARNAX_SSD1306_DRIVER_HPP
#define JARNAX_SSD1306_DRIVER_HPP

#include "ssd1306.hpp"
#include "jarnax/Loopable.hpp"

namespace jarnax {
namespace ssd1306 {

using Image128x32 = ::ssd1306::Image128x32;
using Screen128x32 = ::ssd1306::Screen128x32;

class Driver {
public:
    virtual ssd1306::Image128x32& GetImage(void) = 0;
    virtual ssd1306::Screen128x32& GetScreen(void) = 0;
    virtual void Update(void) = 0;
    virtual bool IsUpdated(void) const = 0;

protected:
    ~Driver() = default;
};

}    // namespace ssd1306
}    // namespace jarnax

#endif    // JARNAX_SSD1306_DRIVER_HPP
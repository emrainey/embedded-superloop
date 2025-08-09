#ifndef JARNAX_W25Q16BV_DRIVER_HPP
#define JARNAX_W25Q16BV_DRIVER_HPP
/// @file
/// The w25q16bv Flash Driver over SPI
/// @details This driver is used to communicate with the w25q16bv Flash memory over SPI.

#include <core/Buffer.hpp>
#include <core/Printer.hpp>
#include <core/Span.hpp>
#include <core/Status.hpp>

namespace jarnax {
namespace w25q16bv {

/// @brief A convenience class to be used as a callback for filling out instructions to write to the Chip
class Functor {
public:
    virtual void operator()(core::Span<uint8_t>& data) = 0;

protected:
    ~Functor() = default;
};

/// @brief The Winbond Flash Driver over SPI
class Driver {
public:
    /// @brief Initializes the driver before main
    virtual core::Status Initialize(void) = 0;
    /// @brief Initiates a Power Up sequence
    virtual void PowerUp(void) = 0;
    /// @return True if the chip is powered up, false otherwise
    virtual bool IsPowered(void) const = 0;
    /// @return True if the chip is identified, false otherwise
    virtual bool IsIdentified(void) const = 0;
    /// @return True if the chip is ready for operations, false otherwise
    virtual bool IsReady(void) const = 0;
    /// @brief Initiates a Power Down sequence
    virtual void PowerDown(void) = 0;

protected:
    ~Driver() = default;
};
}    // namespace w25q16bv
}    // namespace jarnax

#endif    // JARNAX_W25Q16BV_DRIVER_HPP

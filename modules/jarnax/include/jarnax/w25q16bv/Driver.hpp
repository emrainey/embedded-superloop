#ifndef JARNAX_W25Q16BV_DRIVER_HPP
#define JARNAX_W25Q16BV_DRIVER_HPP

/// @file
/// The w25q16bv Flash Driver
/// @details This driver is used to communicate with the w25q16bv Flash memory

#include <core/Buffer.hpp>
#include <core/Printer.hpp>
#include <core/Span.hpp>
#include <jarnax/Driver.hpp>

namespace jarnax {
namespace w25q16bv {

/// @brief A convenience class to be used as a callback for filling out instructions to write to the Chip
class Functor {
public:
    virtual void operator()(core::Span<uint8_t>& data) = 0;

protected:
    ~Functor() = default;
};

/// @brief The w25q16bv Flash Driver
class Driver : public jarnax::Driver {
public:
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

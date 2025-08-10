#ifndef JARNAX_DRIVER_HPP_
#define JARNAX_DRIVER_HPP_

/// @file
/// The Jarnax Driver interface

#include <compiler.hpp>
#include <core/Status.hpp>
#include <jarnax/Loopable.hpp>

namespace jarnax {

/// @brief The Driver class is the base class for all drivers in the Jarnax framework.
/// Drivers can't be copied, moved, heap allocated or destroyed.
/// All drivers must be Loopable and will have a default Initialize method
class Driver : public Loopable, public UnAllocatable, public UnCopyMoveable {
public:
    /// The default constructor
    Driver();

    /// @brief All drivers must implement the Initialize method and may overload it to take parameters with assumed defaults in the base method.
    /// @note Initialization is a step which occurs after construction but before the SuperLoop has started and thus can't depend on other Drivers
    /// to do any work. If some work does depend on other Drivers, it must be done in a separate step after initialization within the State Machine of
    /// the driver itself. Frequently initialization is limited to taking run-time parameters to state or configuration options (clock rates,
    /// addresses, etc). Typically these can't be known at Construction time.
    virtual core::Status Initialize() = 0;

protected:
    /// Destructing through this interface is not allowed.
    ~Driver() = default;
};

}    // namespace jarnax

#endif    // JARNAX_DRIVER_HPP_

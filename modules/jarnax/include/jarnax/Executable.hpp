#ifndef SYSTEM_EXECUTABLE_HPP_
#define SYSTEM_EXECUTABLE_HPP_

/// @file
/// jarnax::Executable Interface

#include "core/doublelink/Node.hpp"
#include "core/Units.hpp"
#include "jarnax/LoopInfo.hpp"

namespace jarnax {

/// @brief Object which are executable inherit this interface and implement the Execute method
/// which informs them of the current superloop
class Executable {
public:
    /// Clients implement this function to be called by the Super Loop.
    virtual bool Execute(LoopInfo const &metadata) = 0;

    /// @brief The Executable Object Information
    struct Info final {
        /// A small unique identifier for the Executable Object to be used to differentiate between objects.
        Id id;
        /// The desired cadence given at configuration. A cadence is a bit pattern starting at bit 0 up to 31. Each bit set to 1 indicates a loop to run.
        /// Each bit set to 0 indicates a loop to skip.
        Cadence cadence{0xFFFF'FFFFU};
        /// The number of times the Executable has been invoked
        std::size_t count{0U};
        /// The tick count when the Executable was finished with it's last Execute
        core::units::Ticks last_tick{0U};
        /// The tick duration of the last Execute
        core::units::Ticks last_duration{0U};
        /// The flag to indicate if the Executable should run again.
        bool is_active{false};
        /// The pointer to the parent Executable Object
        Executable* object{nullptr};
    };
protected:

    ~Executable() = default;

private: // Private to the Exectable but accessible to the SuperLoop

    /// @brief The information which the SuperLoop uses to manage the Executable Object
    core::doublelink::Node<Info> execute_info_;

    /// @brief The SuperLoop is allowed to alter the state of the Executable Object's Info
    friend class SuperLoop;

    /// Returns a reference to a mutable Info structure
    inline Info& GetInfo() { return execute_info_(); }

    inline void ResetInfo() {
        using core::units::operator""_ticks;
        execute_info_().id = 0;
        execute_info_().cadence = 0xFFFF'FFFFU;
        execute_info_().last_tick = 0_ticks;
        execute_info_().last_duration = 0_ticks;
        execute_info_().count = 0U;
        execute_info_().is_active = false;
        execute_info_().object = this;
    }

public:
    /// Allows read-only access to the Info structure for derived classes or others
    inline Info const& GetInfo() const { return execute_info_(); }
};

}    // namespace jarnax

#endif    // SYSTEM_EXECUTABLE_HPP_
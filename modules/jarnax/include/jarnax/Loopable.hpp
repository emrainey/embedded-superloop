#ifndef JARNAX_LOOPABLE_HPP
#define JARNAX_LOOPABLE_HPP

/// @file
/// jarnax::Executable Interface

#include "core/doublelink/Node.hpp"
#include "core/Units.hpp"
#include "jarnax/LoopInfo.hpp"
#include "jarnax/Executable.hpp"

namespace jarnax {

/// @brief Object which are executable inherit this interface and implement the Execute method
/// which informs them of the current superloop
class Loopable : public Executable {
public:
    /// @brief The Loopable Object Information
    struct Info final {
        /// A small unique identifier for the Loopable Object to be used to differentiate between objects.
        Id id;
        /// The desired cadence given at configuration. A cadence is a bit pattern starting at bit 0 up to 31. Each bit set to 1 indicates a loop to run.
        /// Each bit set to 0 indicates a loop to skip.
        Cadence cadence{0xFFFF'FFFFU};
        /// The number of times the Loopable has been invoked
        std::size_t count{0U};
        /// The tick count when the Loopable was finished with it's last Execute
        core::units::Ticks last_tick{0U};
        /// The tick duration of the last Execute
        core::units::Ticks last_duration{0U};
        /// The flag to indicate if the Loopable should run again.
        bool is_active{false};
        /// The pointer to the Loopable Object
        Loopable* object{nullptr};
    };

protected:
    /// The getter for the LoopInfo for the Loopable object for use by the Loopable itself.
    LoopInfo const& GetLoopInfo() { return loop_info_; }

private: // Private to the Exectable but accessible to the SuperLoop

    /// @brief The information which the SuperLoop uses to manage the Executable Object
    core::doublelink::Node<Info> execute_info_;

    /// @brief The location to store the SuperLoop information for this loopable object
    LoopInfo loop_info_;

    /// @brief The SuperLoop is allowed to alter the state of the Executable Object's Info
    friend class SuperLoop;

    /// Returns a mutable reference to an Info structure
    inline Info& GetMutableInfo() { return execute_info_(); }

    /// @brief Returns a mutable reference to the LoopInfo structure
    inline LoopInfo& GetMutableLoopInfo() { return loop_info_; }

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

#endif    // JARNAX_LOOPABLE_HPP
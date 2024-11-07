#ifndef CORE_SUPERLOOP_HPP_
#define CORE_SUPERLOOP_HPP_

/// @file
/// Superloop Object

#include "configure.hpp"
#include "core/Array.hpp"
#include "jarnax/Executable.hpp"
#include "jarnax/Ticker.hpp"

namespace jarnax {

using Cadence = std::uint32_t;
static constexpr std::size_t SlotsInCadence = sizeof(Cadence) * 8U;

/// @brief The Executable Object Information
struct ExecuteInfo final {
    /// A small unique identifier for the Executable Object to be used to differentiate between objects.
    std::uint32_t id;
    /// The desired cadence given at configuration. A cadence is a bit pattern starting at bit 0 up to 31. Each bit set to 1 indicates a loop to run.
    /// Each bit set to 0 indicates a loop to skip.
    Cadence cadence{0xFFFF'FFFFU};
    /// The number of times the Executable has been invoked
    std::size_t count{0U};
    /// The tick count when the Executable was finished with it's last Execute
    Ticks last_tick{0U};
    /// The tick duration of the last Execute
    Ticks last_duration{0U};
    /// The pointer to the object.
    Executable* object{nullptr};
    /// The flag to indicate if the Executable should run again.
    bool is_active{false};
};

/// The list of Executable Objects in the system
using ExecutableList = core::Array<ExecuteInfo, jarnax::num_executable_tasks>;

/// The core execution concept of the system. The SuperLoop iteratively calls all Executable objects.
/// Executable objects can be added or removed at runtime and may stop themselves from running again.
class SuperLoop final {
public:
    /// Constructs the Super Loop
    SuperLoop(Ticker& ticker);

    /// Allows users to enlist an object into the SuperLoop
    /// @param obj The reference to the Executable Object
    /// @param cadence A bit pattern representing the cadence of the object over the 32 cycles of the loop. Defaults to all 1's.
    bool Enlist(Executable& obj, Cadence cadence = 0xFFFF'FFFFU);

    /// Removes an Executable Object from the SuperLoop
    /// @param obj The reference to the Executable Object
    void Dismiss(Executable& obj);

    /// Runs all Executable Objects Once
    void RunAllOnce(void);

    /// Runs the SuperLoop forever
    void RunForever(void);

#if defined(UNITTEST)
    friend std::ostream& operator<<(std::ostream& os, SuperLoop const& loop);
#endif    // UNITTEST

protected:
    /// The reference to the Ticker
    Ticker& ticker_;
    /// The loop counter
    std::size_t loop_count_{0U};
    /// The list of executable objects.
    ExecutableList executables_;
    /// The next ID to hand out
    std::uint32_t next_id_;
};

}    // namespace jarnax

#endif    // CORE_SUPERLOOP_HPP_
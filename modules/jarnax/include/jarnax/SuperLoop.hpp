#ifndef CORE_SUPERLOOP_HPP_
#define CORE_SUPERLOOP_HPP_

/// @file
/// Superloop Object

#include "configure.hpp"
#include "core/Array.hpp"
#include "jarnax/Executable.hpp"

namespace jarnax {

/// @brief The Executable Object Information
struct ExecuteInfo final {
    /// The desired cadence
    std::size_t cadence{1U};
    /// The number of times the Executable has been invoked
    std::size_t count{1U};
    // @todo Last Tick
    // @todo Last Duration
    /// The pointer to the object.
    Executable* object;
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
    SuperLoop();

    /// Allows users to enlist an object into the SuperLoop
    /// @param obj The reference to the Executable Object
    /// @param cadence A non-zero number, 1 indicates each loop, 2 every other loop, etc.
    bool Enlist(Executable& obj, std::size_t cadence = 1U);

    /// @brief Removes an Executable Object from the SuperLoop
    /// @param obj The reference to the Executable Object
    void Dismiss(Executable& obj);

    /// Runs all Executable Objects Once
    void RunAllOnce(void);

protected:
    /// The loop counter
    std::size_t loop_count_{0U};
    /// @brief The list of executable objects.
    ExecutableList executables_;
};

}    // namespace jarnax

#endif    // CORE_SUPERLOOP_HPP_
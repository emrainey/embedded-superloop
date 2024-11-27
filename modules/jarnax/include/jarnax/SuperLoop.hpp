#ifndef CORE_SUPERLOOP_HPP_
#define CORE_SUPERLOOP_HPP_

/// @file
/// Superloop Object

#include "configure.hpp"
#include "core/doublelink/Node.hpp"
#include "jarnax/Executable.hpp"
#include "jarnax/Ticker.hpp"

namespace jarnax {

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
    /// The next ID to hand out
    std::uint32_t next_id_;
    /// The pointer to the Executable::Info Head Node
    core::doublelink::Node<Executable::Info>* head_;
    /// The pointer to the Executable::Info Tail Node
    core::doublelink::Node<Executable::Info>* tail_;
};

}    // namespace jarnax

#endif    // CORE_SUPERLOOP_HPP_
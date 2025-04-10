#ifndef JARNAX_CONTEXT_HPP_
#define JARNAX_CONTEXT_HPP_

/// @file
/// jarnax::Context Interface

#include "jarnax/Initializable.hpp"
#include "jarnax/SuperLoop.hpp"

namespace jarnax {

/// Contains the SuperLoop and any platform specific initializations.
class Context : public Initializable {
public:
    /// Retrieves the SuperLoop from the Context.
    /// @return The reference to the SuperLoop
    virtual SuperLoop& GetSuperLoop(void) = 0;
};

/// The mechanism to get the Context for the system.
extern Context& GetContext(void);

}    // namespace jarnax

#endif    // JARNAX_CONTEXT_HPP_
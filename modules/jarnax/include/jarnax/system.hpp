#ifndef JARNAX_SYSTEM_HPP_
#define JARNAX_SYSTEM_HPP_

/// @file
/// The System Interface
#include "compiler.hpp"
#include "jarnax/SuperLoop.hpp"
#include "jarnax/Ticker.hpp"
#include "jarnax/Timer.hpp"
#include "jarnax/print.hpp"

/// The namespace of the system level functions
namespace jarnax {

namespace system {
/// Requests a call to the system to yield
void yield(void);
}    // namespace system
}    // namespace jarnax

/// The one global symbol used by the Linker from the code.
extern "C" NAKED void reset_entry(void);

#endif    // JARNAX_SYSTEM_HPP_

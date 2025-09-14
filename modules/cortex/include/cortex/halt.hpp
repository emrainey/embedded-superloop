#ifndef CORTEX_HALT_HPP_
#define CORTEX_HALT_HPP_

/// @file
/// The Cortex Microcontroller Halt Header

namespace cortex {

/// Used for debug, trapping, bad handlers, and to catch bad behavior. This function
/// will enable the debug system and cause the processor to halt.
/// @warning Paths which enter this function do not leave and will not run user applications.
[[noreturn]] void halt(void);

/// Used for debug, trapping, bad handlers, and to catch bad behavior. This function
/// will spin forever in a tight loop.
/// @warning Paths which enter this function do not leave and will not run user applications.
[[noreturn]] void spinhalt(void);

}    // namespace cortex

#endif    // CORTEX_HALT_HPP_

#ifndef CORTEX_SYSTEM_HPP_
#define CORTEX_SYSTEM_HPP_

/// @file
/// The Cortex Microcontroller System Requirements Headers. This contains the definitions which the external system must implement

#include <cstddef>
#include <cstdint>
#include "compiler.hpp"
#include "cortex/halt.hpp"

namespace cortex {

/// The namespace used by the external system to define functions which cortex will use to initialize it's variables and classes.
namespace system {

/// This is called to configure the system after the core is initialized
/// but before the system is marked as configured.
/// @note This is defined by the external system, not by cortex
extern void configure(void);

/// This is the main entry point of the system after initialization
/// @note This is defined by the external system, not by cortex
/// @warning The stacks will be reset so this function cannot return!
[[noreturn]] extern void main(void);

}    // namespace system
}    // namespace cortex

#endif    // CORTEX_SYSTEM_HPP_

#ifndef CORTEX_CACHE_HPP_
#define CORTEX_CACHE_HPP_

/// @file
/// The Cortex Cache Control Header

#include <cstddef>
#include <cstdint>

namespace cortex {

/// Contains operations on the Cache subsystems
namespace cache {

/// Contains operations on the Data Cache
namespace data {

/// Invalidate the Data Cache
/// @pre cortex::initialize::globals
void invalidate(void);

/// Disable the Data Cache
/// @pre cortex::initialize::globals
void disable(void);

/// Enable the Data Cache
/// @pre cortex::initialize::globals
void enable(void);

}    // namespace data

/// Contains operations on the Instruction Cache
namespace instruction {

/// Disable the Instruction Cache
void disable(void);
/// Enable the Instruction Cache
void enable(void);

}    // namespace instruction

}    // namespace cache

}    // namespace cortex

#endif    // CORTEX_CACHE_HPP_

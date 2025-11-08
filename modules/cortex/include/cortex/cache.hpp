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

/// Invalidate the entire Data Cache
/// @pre cortex::initialize::globals
void invalidate(void);

/// Invalidate an address block from Data Cache
/// @pre cortex::initialize::globals
/// @param address The starting address to invalidate
/// @param size The size of the block to invalidate
void invalidate(std::uintptr_t address, std::size_t size);

/// Clean the entire Data Cache
/// @pre cortex::initialize::globals
void clean(void);

/// Clean an address block from Data Cache
/// @pre cortex::initialize::globals
/// @param address The starting address to clean
/// @param size The size of the block to clean
void clean(std::uintptr_t address, std::size_t size);

/// Flush (Clean and Invalidate) the entire Data Cache
/// @pre cortex::initialize::globals
void flush(void);

/// Flush (Clean and Invalidate) an address block from Data Cache
/// @pre cortex::initialize::globals
/// @param address The starting address to flush
/// @param size The size of the block to flush
void flush(std::uintptr_t address, std::size_t size);

/// Disable the Data Cache
/// @pre cortex::initialize::globals
void disable(void);

/// Enable the Data Cache
/// @pre cortex::initialize::globals
void enable(void);

}    // namespace data

/// Contains operations on the Instruction Cache
namespace instruction {

/// Invalidate the entire Instruction Cache
/// @pre cortex::initialize::globals
void invalidate(void);

/// Invalidate an address block from Instruction Cache
/// @pre cortex::initialize::globals
/// @param address The starting address to invalidate
/// @param size The size of the block to invalidate
void invalidate(std::uintptr_t address, std::size_t size);

/// Disable the Instruction Cache
void disable(void);

/// Enable the Instruction Cache
void enable(void);

}    // namespace instruction

}    // namespace cache

}    // namespace cortex

#endif    // CORTEX_CACHE_HPP_

#ifndef CORTEX_ADDRESSES_HPP_
#define CORTEX_ADDRESSES_HPP_

/// @file
/// The Cortex Microcontroller Address Header. The contains the definitions of the 32 bit address space of the Cortex Microcontroller processor

#include <cstddef>
#include <cstdint>
#include <polyfill.hpp>
#include "iso.hpp"

namespace cortex {

/// Used to determine if an address is valid for the Cortex Microcontroller processor
bool IsValidAddress(std::uintptr_t address);

}    // namespace cortex

#endif    // CORTEX_ADDRESSES_HPP_

#ifndef CORTEX_M_VENDOR_HPP_
#define CORTEX_M_VENDOR_HPP_

/// @file
/// Defined Vendor folder, this contains Vendor definitions within the Cortex namespace.

#include <cstdint>

namespace cortex {
namespace vendor {
/// @FIXME STM32 Vendor Fault Status Register for now is a uint32_t
/// Each bit maps to an AUXFAULT bit somewhere in the documentation.
using AuxiliaryFaultStatus = std::uint32_t;
}    // namespace vendor
}    // namespace cortex

// This will define the variant
#include "cortex/m4.hpp"

#endif    // CORTEX_M_VENDOR_HPP_
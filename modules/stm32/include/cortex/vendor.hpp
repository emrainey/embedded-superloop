#ifndef CORTEX_M_VENDOR_HPP_
#define CORTEX_M_VENDOR_HPP_

/// @file
/// Defined Vendor folder, this contains Vendor definitions within the Cortex namespace.

namespace cortex {
namespace vendor {
/// @FIXME STM32 Vendor Fault Status Register for now is a uint32_t
using AuxiliaryFaultStatus = std::uint32_t;
}    // namespace vendor
}    // namespace cortex

#endif    // CORTEX_M_VENDOR_HPP_
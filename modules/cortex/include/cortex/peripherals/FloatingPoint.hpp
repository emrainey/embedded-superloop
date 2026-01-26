#ifndef CORTEX_FLOATING_POINT_HPP_
#define CORTEX_FLOATING_POINT_HPP_

/// @file
/// The Cortex Microcontroller Floating Point Registers

#include <cstddef>
#include <cstdint>
#include "cortex/types.hpp"

namespace cortex {
namespace peripherals {
/// The Floating Point Block
struct FloatingPoint final {
    /// (FPCCR) Holds control data for the Floating Point Unit.
    struct ContextControl final {
        /// @brief The bitfield definition of the register
        struct Fields final {
            std::uint32_t lazy_preservation           : 1U;    ///< Enable lazy context preservation
            modes::Privileged privilege               : 1U;    ///< (Also know as USER)
            std::uint32_t                             : 1U;
            modes::Execution execution                : 1U;    ///< (THREAD)
            std::uint32_t hard_fault_pending          : 1U;    ///< Hard fault exception pending
            std::uint32_t memory_management_pending   : 1U;    ///< Memory management fault pending
            std::uint32_t bus_fault_pending           : 1U;    ///< Bus fault exception pending
            std::uint32_t                             : 1U;
            std::uint32_t debug_monitor_pending       : 1U;    ///< Debug monitor exception pending
            std::uint32_t                             : 21U;
            std::uint32_t lazy_context_save           : 1U;    ///< (LSPEN)
            std::uint32_t floating_point_context_save : 1U;    ///< (ASPEN)
        };
        union {
            Fields bits;
            std::uint32_t whole;
        };
    };

    ///  (FPCAR) Holds the location of the Floating Point Context
    struct ContextAddress final {
        /// @brief The bitfield definition of the register
        struct Fields final {
            std::uint32_t         : 3U;
            std::uint32_t address : 29U;    ///< Address of floating-point context (8-byte aligned)
        };
        union {
            Fields bits;
            std::uint32_t whole;
        };
    };

    /// (FPDSCR) Floating Point Default Control Register
    struct DefaultStatusControl final {
        /// @brief The bitfield definition of the register
        struct Fields final {
            std::uint32_t                : 22U;
            modes::Rounding rounding     : 2U;    ///< Default rounding mode for FP operations
            std::uint32_t flush_to_zero  : 1U;    ///< Flush-to-zero mode for denormal numbers
            std::uint32_t default_nan    : 1U;    ///< Default NaN mode
            std::uint32_t half_precision : 1U;    ///< Alternative half-precision format
            std::uint32_t                : 5U;
        };
        union {
            Fields bits;
            std::uint32_t whole;
        };
    };

    /// Media and Feature Register 0
    struct MediaFeatures0 final {
        /// @brief The bitfield definition of the register
        struct Fields final {
            std::uint32_t simd             : 4U;    ///< SIMD instruction support level
            std::uint32_t single_precision : 4U;    ///< Single-precision floating-point support
            std::uint32_t double_precision : 4U;    ///< Double-precision floating-point support
            std::uint32_t exception        : 4U;    ///< FP exception trapping support
            std::uint32_t divide           : 4U;    ///< Hardware divide instruction support
            std::uint32_t square_root      : 4U;    ///< Hardware square root support
            std::uint32_t short_vectors    : 4U;    ///< Short vector support
            std::uint32_t rounding         : 4U;    ///< Rounding modes supported
        };
        union {
            Fields bits;
            std::uint32_t whole;
        };
    };

    /// Media and Feature Register 0
    struct MediaFeatures1 final {
        /// @brief The bitfield definition of the register
        struct Fields final {
            std::uint32_t flush_to_zero       : 4U;    ///< Flush-to-zero support level
            std::uint32_t default_nan         : 4U;    ///< Default NaN mode support
            std::uint32_t                     : 16U;
            std::uint32_t half_precision      : 4U;    ///< Half-precision support level
            std::uint32_t multiply_accumulate : 4U;    ///< FP fused multiply-accumulate support
        };
        union {
            Fields bits;
            std::uint32_t whole;
        };
    };

    /// Media and Feature Register 0
    struct MediaFeatures2 final {
        /// @brief The bitfield definition of the register
        struct Fields final {
            std::uint32_t               : 4U;
            std::uint32_t miscellaneous : 4U;    ///< Miscellaneous FP features
            std::uint32_t               : 24U;
        };
        union {
            Fields bits;
            std::uint32_t whole;
        };
    };

    //==MEMORY===================================
    ContextControl context_control;                 ///< Floating-point context control register
    ContextAddress context_address;                 ///< Floating-point context address register
    DefaultStatusControl default_status_control;    ///< Floating-point default status control register
    MediaFeatures0 media_features_0;                ///< Media and VFP feature register 0
    MediaFeatures1 media_features_1;                ///< Media and VFP feature register 1
    MediaFeatures2 media_features_2;                ///< Media and VFP feature register 2
    //==MEMORY===================================
};

/// The Floating Point Extension registers
extern FloatingPoint volatile floating_point;
}    // namespace peripherals
}    // namespace cortex

#endif    // CORTEX_M_FLOATING_POINT_HPP_

#ifndef CORTEX_FLOATING_POINT_HPP_
#define CORTEX_FLOATING_POINT_HPP_

/// @file
/// The Cortex Microcontroller Floating Point Registers

#include <cstddef>
#include <cstdint>

namespace cortex {
namespace peripherals {
/// The Floating Point Block
struct FloatingPoint final {
    /// (FPCCR) Holds control data for the Floating Point Unit.
    struct ContextControl final {
        /// @brief The bitfield definition of the register
        struct Fields final {
            std::uint32_t lazy_preservation           : 1U;
            modes::Privileged privilege               : 1U;    ///< (Also know as USER)
            std::uint32_t                             : 1U;
            modes::Execution execution                : 1U;    ///< (THREAD)
            std::uint32_t hard_fault_pending          : 1U;
            std::uint32_t memory_management_pending   : 1U;
            std::uint32_t bus_fault_pending           : 1U;
            std::uint32_t                             : 1U;
            std::uint32_t debug_monitor_pending       : 1U;
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
            std::uint32_t address : 29U;
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
            modes::Rounding rounding     : 2U;
            std::uint32_t flush_to_zero  : 1U;
            std::uint32_t default_nan    : 1U;
            std::uint32_t half_precision : 1U;
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
            std::uint32_t simd             : 4U;
            std::uint32_t single_precision : 4U;
            std::uint32_t double_precision : 4U;
            std::uint32_t exception        : 4U;
            std::uint32_t divide           : 4U;
            std::uint32_t square_root      : 4U;
            std::uint32_t short_vectors    : 4U;
            std::uint32_t rounding         : 4U;
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
            std::uint32_t flush_to_zero       : 4U;
            std::uint32_t default_nan         : 4U;
            std::uint32_t                     : 16U;
            std::uint32_t half_precision      : 4U;
            std::uint32_t multiply_accumulate : 4U;
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
            std::uint32_t miscellaneous : 4U;
            std::uint32_t               : 24U;
        };
        union {
            Fields bits;
            std::uint32_t whole;
        };
    };

    //==MEMORY===================================
    ContextControl context_control;
    ContextAddress context_address;
    DefaultStatusControl default_status_control;
    MediaFeatures0 media_features_0;
    MediaFeatures1 media_features_1;
    MediaFeatures2 media_features_2;
    //==MEMORY===================================
};

/// The Floating Point Extension registers
extern FloatingPoint volatile floating_point;
}    // namespace peripherals
}    // namespace cortex

#endif    // CORTEX_M_FLOATING_POINT_HPP_

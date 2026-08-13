
#ifndef STM32_H7XX_SWO_TRACE_FUNNEL__HPP_
#define STM32_H7XX_SWO_TRACE_FUNNEL__HPP_

/// @file
/// Hand-written structure definitions for the SWO Trace Funnel (SWTF) trace block.
/// @note RM0433 Rev 8, Section 35.4 (SWO trace funnel SWTF). The block is memory mapped
/// at 0x5C004000 on the APB-D debug bus of the STM32H753. It forwards the ATB trace bus
/// from the Cortex-M7 ITM to the SWO block, and must be programmed before trace is enabled.

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace stm32 {
namespace h7xx {

/// The SWO Trace Funnel (SWTF) trace block.
struct SwoTraceFunnel final {
    /// SWTF Control register (SWTF_CTRL) at offset 0x000.
    /// @details Reset value 0x0000 0300 (MIN_HOLD_TIME = 3).
    struct Control final {
        struct Fields {
            std::uint32_t enable_swo       : 1U;    ///< Enable the trace bus from the Cortex-M7 ITM to the SWO block (ENSO)
            std::uint32_t                  : 7U;    ///< Reserved field
            std::uint32_t minimum_hold_time : 4U;   ///< Minimum hold time of the ATB bus (MIN_HOLD_TIME)
            std::uint32_t                  : 20U;   ///< Reserved field
        };
        union {
            Fields bits;
            std::uint32_t whole;
        };
    };

    /// SWTF Priority register (SWTF_PRIORITY) at offset 0x004.
    /// @details Reset value 0x0000 0008.
    struct Priority final {
        struct Fields {
            std::uint32_t port_priority : 3U;    ///< ATB bus priority (PRIPORTO)
            std::uint32_t               : 29U;   ///< Reserved field
        };
        union {
            Fields bits;
            std::uint32_t whole;
        };
    };

    Control control;                       ///< Offset 0x000 (SWTF_CTRL)
    Priority priority;                     ///< Offset 0x004 (SWTF_PRIORITY)
    std::uint32_t _reserved0[1002];        ///< Offset 0x008 to 0xFAC
    std::uint32_t lock_access;             ///< Offset 0xFB0 (SWTF_LAR)
};
static_assert(std::is_standard_layout<SwoTraceFunnel>::value, "Must be standard layout");
static_assert(offsetof(SwoTraceFunnel, control) == 0x000, "Must be at this offset");
static_assert(offsetof(SwoTraceFunnel, priority) == 0x004, "Must be at this offset");
static_assert(offsetof(SwoTraceFunnel, lock_access) == 0xFB0, "Must be at this offset");
static_assert(sizeof(SwoTraceFunnel) == 0xFB4, "Must be this exact size");

/// The value to write to the SWTF_LAR register to unlock the SWTF block (write 0xC5ACCE55).
constexpr static std::uint32_t SwoTraceFunnelLockValue = 0xC5ACCE55U;

}    // namespace h7xx
}    // namespace stm32
#endif    // STM32_H7XX_SWO_TRACE_FUNNEL__HPP_

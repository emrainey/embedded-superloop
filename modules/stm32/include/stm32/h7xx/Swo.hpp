
#ifndef STM32_H7XX_SWO__HPP_
#define STM32_H7XX_SWO__HPP_

/// @file
/// Hand-written structure definitions for the Serial Wire Output (SWO) trace block.
/// @note RM0433 Rev 8, Section 35.4 (SWO trace block) + Table 605. The block is memory mapped
/// at 0x5C003000 on the APB-D debug bus of the STM32H753. It is NOT the ARM CoreSight TPIU
/// (0xE0040000 alias / 0x5C015000 on the H7) which the Cortex-M7 reference peripheral maps to.

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace stm32 {
namespace h7xx {

/// The Serial Wire Output (SWO) trace block.
/// @details Transmits the trace stream (fed in by the SWO Trace Funnel) on the SWO pin in
/// Manchester or UART (Async NRZ) mode.
struct Swo final {
    /// The trace protocol on the SWO pin (SWO_SPPR)
    enum class Protocol : std::uint32_t {
        Reserved = 0U,        ///< Reserved
        AsyncManchester = 1U, ///< Asynchronous Manchester encoded
        AsyncNRZ = 2U,        ///< Asynchronous NRZ encoded (UART)
    };

    /// SWO Current Output Divisor register (SWO_CODR) at offset 0x010.
    /// @details The divider is zero based: the baud rate is the trace clock frequency divided by
    /// (prescaler + 1).
    struct CurrentOutputDivisor final {
        struct Fields {
            std::uint32_t prescaler : 13U;    ///< Divider value for the trace clock (zero based)
            std::uint32_t           : 19U;    ///< Reserved field
        };
        union {
            Fields bits;
            std::uint32_t whole;
        };
    };

    /// SWO Selected Pin Protocol register (SWO_SPPR) at offset 0x0F0.
    struct SelectedPinProtocol final {
        struct Fields {
            Protocol transmit_mode : 2U;    ///< Trace protocol selection
            std::uint32_t         : 30U;    ///< Reserved field
        };
        union {
            Fields bits;
            std::uint32_t whole;
        };
    };

    std::uint32_t _reserved0[4];                 ///< Offset 0x000 to 0x00C
    CurrentOutputDivisor current_output_divisor; ///< Offset 0x010 (SWO_CODR)
    std::uint32_t _reserved1[55];                ///< Offset 0x014 to 0x0EC
    SelectedPinProtocol selected_pin_protocol;   ///< Offset 0x0F0 (SWO_SPPR)
    std::uint32_t _reserved2[943];               ///< Offset 0x0F4 to 0xFAC
    std::uint32_t lock_access;                   ///< Offset 0xFB0 (SWO_LAR)
};
static_assert(std::is_standard_layout<Swo>::value, "Must be standard layout");
static_assert(offsetof(Swo, current_output_divisor) == 0x010, "Must be at this offset");
static_assert(offsetof(Swo, selected_pin_protocol) == 0x0F0, "Must be at this offset");
static_assert(offsetof(Swo, lock_access) == 0xFB0, "Must be at this offset");
static_assert(sizeof(Swo) == 0xFB4, "Must be this exact size");

/// The value to write to the SWO_LAR register to unlock the SWO block (write 0xC5ACCE55).
constexpr static std::uint32_t SwoLockValue = 0xC5ACCE55U;

}    // namespace h7xx
}    // namespace stm32
#endif    // STM32_H7XX_SWO__HPP_

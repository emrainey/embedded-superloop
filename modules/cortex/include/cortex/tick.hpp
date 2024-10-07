#ifndef CORTEX_M_TICKS_HPP_
#define CORTEX_M_TICKS_HPP_

/// @file
/// The Cortex M System Tick Header

#include "core/Units.hpp"
#include "cortex/core.hpp"

namespace cortex {

/// The System Tick Registers
struct SystemTick final {
    /// The Control Status Register
    struct ControlStatus final {
        ControlStatus()
            : whole{0} {}
        ControlStatus(ControlStatus const& other)
            : whole{other.whole} {}
        ControlStatus(ControlStatus volatile& other)
            : whole{other.whole} {}
        struct Fields final {
            std::uint32_t enable              : 1U;
            std::uint32_t interrupt           : 1U;
            std::uint32_t use_processor_clock : 1U;
            std::uint32_t                     : 13U;    ///< Reserved field
            std::uint32_t counted_down        : 1U;
            std::uint32_t                     : 15U;    ///< Reserved field
        };
        union {
            Fields bits;
            std::uint32_t whole;
        };
        void operator=(ControlStatus const& other) volatile { whole = other.whole; }
        void operator=(ControlStatus volatile& other) { whole = other.whole; }
    };
    struct Reload final {
        Reload()
            : whole{0} {}
        Reload(Reload const& other)
            : whole{other.whole} {}
        Reload(Reload volatile& other)
            : whole{other.whole} {}
        struct Fields final {
            std::uint32_t value : 24U;    ///< The value that is reloaded into the current value
            std::uint32_t       : 8U;     ///< Reserved field
        };
        union {
            Fields bits;
            std::uint32_t whole;
        };
        void operator=(Reload const& other) volatile { whole = other.whole; }
        void operator=(Reload volatile& other) { whole = other.whole; }
    };
    /// The Calibration Registers
    struct Calibration final {
        Calibration()
            : whole{0} {}
        Calibration(Calibration const& other)
            : whole{other.whole} {}
        Calibration(Calibration volatile& other)
            : whole{other.whole} {}
        struct Fields final {
            std::uint32_t ten_millisecond_count : 24U;    ///< The number of reference clocks per 10ms
            std::uint32_t                       : 6U;     ///< Reserved field
            std::uint32_t skew                  : 1U;     ///< Indicates if the
            std::uint32_t no_reference          : 1U;
        };
        union {
            Fields bits;
            std::uint32_t whole;
        };
        void operator=(Calibration const& other) volatile { whole = other.whole; }
        void operator=(Calibration volatile& other) { whole = other.whole; }
    };

    // ===================================
    ControlStatus control_status;
    Reload reload;
    std::uint32_t current;    ///< The current countdown value. If written to it will clear it.
    Calibration calibration;
    // ===================================
};
static_assert(offsetof(SystemTick, current) == 0x08, "Must be at this offset");
static_assert(sizeof(SystemTick) == 0x10, "Must be the exact size");

/// @brief Linker symbol to the peripheral hardware
extern SystemTick volatile system_tick;

/// @brief Ticks are held in unit
using Ticks = core::units::Ticks;

/// @brief The number of cycles per second
using Hertz = core::units::Hertz;

/// Gets the Current Ticks since Boot
Ticks GetTickCount(void);

/// Gets the Current Tick Rate per Second
Hertz GetTickRate();

/// Indicates if the System Tick has been enabled
bool IsTickEnabled();

}    // namespace cortex

#endif    // CORTEX_M_TICKS_HPP_
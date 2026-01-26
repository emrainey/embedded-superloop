#ifndef CORTEX_SYSTEM_TICK_HPP_
#define CORTEX_SYSTEM_TICK_HPP_

/// @file
/// The Cortex Microcontroller System Tick Header

#include "core/Units.hpp"
#include "cortex/types.hpp"

namespace cortex {
namespace peripherals {
/// The System Tick Registers
struct SystemTick final {
    /// The Control Status Register
    /// @brief System Timer Control and Status Register
    /// @details Controls the SysTick timer operation and reports its status
    struct ControlStatus final {
        /// Default constructor - initializes to zero
        ControlStatus()
            : whole{0} {}
        /// Copy constructor from another instance
        ControlStatus(ControlStatus const& other)
            : whole{other.whole} {}
        /// Copy constructor from volatile register
        ControlStatus(ControlStatus volatile& other)
            : whole{other.whole} {}
        /// @brief Bit field layout for the Control and Status register
        struct Fields final {
            std::uint32_t enable              : 1U;     ///< Enable SysTick counter
            std::uint32_t interrupt           : 1U;     ///< Enable SysTick interrupt
            std::uint32_t use_processor_clock : 1U;     ///< Use processor clock (vs external reference)
            std::uint32_t                     : 13U;    ///< Reserved field
            std::uint32_t counted_down        : 1U;     ///< Counter counted to zero since last read
            std::uint32_t                     : 15U;    ///< Reserved field
        };
        union {
            Fields bits;
            std::uint32_t whole;
        };
        /// Assignment from copy back to volatile registers
        void operator=(ControlStatus const& other) volatile { whole = other.whole; }
        /// Copy from volatile register to local copy
        void operator=(ControlStatus volatile& other) { whole = other.whole; }
    };
    /// @brief System Timer Reload Value Register
    /// @details Specifies the reload value for the SysTick counter
    struct Reload final {
        /// Default constructor - initializes to zero
        Reload()
            : whole{0} {}
        /// Copy constructor from another instance
        Reload(Reload const& other)
            : whole{other.whole} {}
        /// Copy constructor from volatile register
        Reload(Reload volatile& other)
            : whole{other.whole} {}
        /// @brief Bit field layout for the Reload register
        struct Fields final {
            std::uint32_t value : 24U;    ///< The value that is reloaded into the current value
            std::uint32_t       : 8U;     ///< Reserved field
        };
        union {
            Fields bits;
            std::uint32_t whole;
        };
        /// Assignment from copy back to volatile registers
        void operator=(Reload const& other) volatile { whole = other.whole; }
        /// Copy from volatile register to local copy
        void operator=(Reload volatile& other) { whole = other.whole; }
    };
    /// The Calibration Registers
    struct Calibration final {
        /// Default constructor - initializes to zero
        Calibration()
            : whole{0} {}
        /// Copy constructor from another instance
        Calibration(Calibration const& other)
            : whole{other.whole} {}
        /// Copy constructor from volatile register
        Calibration(Calibration volatile& other)
            : whole{other.whole} {}
        /// @brief Bit field layout for the Calibration register
        struct Fields final {
            std::uint32_t ten_millisecond_count : 24U;    ///< The number of reference clocks per 10ms
            std::uint32_t                       : 6U;     ///< Reserved field
            std::uint32_t skew                  : 1U;     ///< Indicates if the calibration value is inexact
            std::uint32_t no_reference          : 1U;     ///< No reference clock provided
        };
        union {
            Fields bits;
            std::uint32_t whole;
        };
        /// Assignment from copy back to volatile registers
        void operator=(Calibration const& other) volatile { whole = other.whole; }
        /// Copy from volatile register to local copy
        void operator=(Calibration volatile& other) { whole = other.whole; }
    };

    // ===================================
    ControlStatus control_status;    ///< Control and status register
    Reload reload;                   ///< Reload value register
    std::uint32_t current;           ///< The current countdown value. If written to it will clear it.
    Calibration calibration;         ///< Calibration value register
    // ===================================
};
static_assert(offsetof(SystemTick, current) == 0x08, "Must be at this offset");
static_assert(sizeof(SystemTick) == 0x10, "Must be the exact size");

/// @brief Linker symbol to the peripheral hardware
extern SystemTick volatile system_tick;
}    // namespace peripherals
}    // namespace cortex

#endif    // CORTEX_SYSTEM_TICK_HPP_

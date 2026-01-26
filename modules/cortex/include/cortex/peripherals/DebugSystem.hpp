#ifndef CORTEX_M_DEBUG_HPP_
#define CORTEX_M_DEBUG_HPP_

/// @file
/// The Cortex Microcontroller Debug Header

#include "cortex/types.hpp"

namespace cortex {
/// The Cortex Microcontroller Peripheral Namespace
namespace peripherals {
/// The Debug Register set
struct DebugSystem final {
    /// Halting Control Register
    struct HaltingControl final {
        HaltingControl()
            : whole{0} {}
        /// Copy constructor from const reference
        /// @param other The halting control to copy from
        HaltingControl(HaltingControl const& other)
            : whole{other.whole} {}
        /// Copy constructor from volatile reference (for reading hardware registers)
        /// @param other The volatile halting control to copy from
        HaltingControl(HaltingControl volatile& other)
            : whole{other.whole} {}

        /// @brief Read-only fields of the Debug Halting Control register
        struct Read final {
            std::uint32_t debug                 : 1U;     ///< Debug enabled
            std::uint32_t processor             : 1U;     ///< Processor halted for debug
            std::uint32_t step                  : 1U;     ///< Single-step mode enabled
            std::uint32_t mask_interrupts       : 1U;     ///< Mask interrupts when halted
            std::uint32_t                       : 1U;     ///< Reserved field
            std::uint32_t allow_imprecise_entry : 1U;     ///< Allow imprecise debug entry
            std::uint32_t                       : 10U;    ///< Reserved field
            std::uint32_t register_ready        : 1U;     ///< Core register data ready
            std::uint32_t halt                  : 1U;     ///< Processor is halted
            std::uint32_t sleeping              : 1U;     ///< Processor is sleeping
            std::uint32_t locked_up             : 1U;     ///< Processor is locked up
            std::uint32_t                       : 4U;     ///< Reserved field
            std::uint32_t retire                : 1U;     ///< Instruction retired (PMOV)
            std::uint32_t reset                 : 1U;     ///< Reset catch enabled
            std::uint32_t                       : 6U;     ///< Reserved field
        };
        /// @brief Write-only fields of the Debug Halting Control register
        struct Write final {
            std::uint32_t     : 16U;    ///< Reserved field
            std::uint32_t key : 16U;    ///< Write key value (0xA05F for write access)
        };

        /// The union of the read and write bitfields
        union {
            Read read;
            Write write;
            std::uint32_t whole;
        };
        /// Assignment from copy back to registers
        void operator=(HaltingControl const& other) volatile { whole = other.whole; }
        /// Copy from volatile register to local copy
        void operator=(HaltingControl volatile& other) { whole = other.whole; }
    };
    /// The Core Register Selector Register
    struct CoreRegisterSelector final {
        std::uint32_t selector : 7U;     ///< Register selector (0-20 for core regs, 33-47 for special regs)
        std::uint32_t          : 1U;     ///< Reserved field
        std::uint32_t access   : 1U;     ///< Access type (0=read, 1=write)
        std::uint32_t          : 15U;    ///< Reserved field
    };
    /// The Core Register Data Register
    struct CoreRegisterData final {
        std::uint32_t temporary_cache;    ///< Temporary cache for core register read/write operations
    };
    /// The Exception Monitor and Control Register
    struct ExceptionMonitorControl final {
        /// @brief The bitfield definition of the register
        struct Fields final {
            std::uint32_t enable_reset_vector_catch              : 1U;    ///< Halt processor on reset vector fetch
            std::uint32_t                                        : 3U;    ///< Reserved field
            std::uint32_t enable_halt_on_memory_management_fault : 1U;    ///< Halt on memory management fault
            std::uint32_t enable_halt_on_usage_fault_coprocessor : 1U;    ///< Halt on usage fault (coprocessor)
            std::uint32_t enable_halt_on_usage_fault_checking    : 1U;    ///< Halt on usage fault (checking error)
            std::uint32_t enable_halt_on_usage_fault_state       : 1U;    ///< Halt on usage fault (state error)
            std::uint32_t enable_halt_on_bus_fault               : 1U;    ///< Halt on bus fault
            std::uint32_t enable_halt_on_exception_entry_return  : 1U;    ///< Halt on exception entry/return
            std::uint32_t enable_halt_on_hard_fault              : 1U;    ///< Halt on hard fault
            std::uint32_t                                        : 5U;    ///< Reserved field
            std::uint32_t enable_debug_monitor_exception         : 1U;    ///< Enable debug monitor exception
            std::uint32_t pending_debug_monitor_exception        : 1U;    ///< Debug monitor exception pending
            std::uint32_t step_debug_monitor_exception           : 1U;    ///< Step debug monitor exception
            std::uint32_t                                        : 1U;    ///< debug_monitor_exception_request?
            std::uint32_t                                        : 4U;    ///< Reserved field
            std::uint32_t enable_trace                           : 1U;    ///< Enable trace output
            std::uint32_t                                        : 7U;    ///< Reserved field
        };
        /// @brief  The union of the register and the bitfield
        union {
            Fields bits;
            std::uint32_t whole;
        };
    };
    static_assert(sizeof(ExceptionMonitorControl) == 4U, "Must be this size");

    // MEMORY

    HaltingControl halting_control;                       ///< Debug halting control and status register
    CoreRegisterSelector core_register_selector;          ///< Core register selector for debug access
    CoreRegisterData core_register_data;                  ///< Core register data for debug read/write
    ExceptionMonitorControl exception_monitor_control;    ///< Exception and monitor control register
};
static_assert(sizeof(DebugSystem) == 0x10, "Must be this size");

/// The Debug Block
extern DebugSystem volatile debug_system;
}    // namespace peripherals
}    // namespace cortex

#endif    // CORTEX_M_DEBUG_HPP_

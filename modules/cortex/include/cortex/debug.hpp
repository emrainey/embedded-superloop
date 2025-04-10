#ifndef CORTEX_M_DEBUG_HPP_
#define CORTEX_M_DEBUG_HPP_

/// @file
/// The Cortex M Debug Header

#include "cortex/core.hpp"

namespace cortex {
/// The Debug Register set
struct DebugSystem final {
    /// Halting Control Register
    struct HaltingControl final {
        union {
            struct {
                std::uint32_t debug                 : 1U;
                std::uint32_t processor             : 1U;
                std::uint32_t step                  : 1U;
                std::uint32_t mask_interrupts       : 1U;
                std::uint32_t                       : 1U;    ///< Reserved field
                std::uint32_t allow_imprecise_entry : 1U;
                std::uint32_t                       : 10U;    ///< Reserved field
                std::uint32_t register_ready        : 1U;
                std::uint32_t halt                  : 1U;
                std::uint32_t sleeping              : 1U;
                std::uint32_t locked_up             : 1U;
                std::uint32_t                       : 4U;    ///< Reserved field
                std::uint32_t retire                : 1U;
                std::uint32_t reset                 : 1U;
                std::uint32_t                       : 6U;    ///< Reserved field
            } read;
            struct {
                std::uint32_t     : 16U;    ///< Reserved field
                std::uint32_t key : 16U;
            } write;
        } bits;
    };
    /// The Core Register Selector Register
    struct CoreRegisterSelector final {
        std::uint32_t selector : 7U;
        std::uint32_t          : 1U;    ///< Reserved field
        std::uint32_t access   : 1U;
        std::uint32_t          : 15U;    ///< Reserved field
    };
    /// The Core Register Data Register
    struct CoreRegisterData final {
        std::uint32_t temporary_cache;
    };
    /// The Exception Monitor and Control Register
    struct ExceptionMonitorControl final {
        /// @brief The bitfield definition of the register
        struct Fields final {
            std::uint32_t enable_reset_vector_catch              : 1U;
            std::uint32_t                                        : 3U;    ///< Reserved field
            std::uint32_t enable_halt_on_memory_management_fault : 1U;
            std::uint32_t enable_halt_on_usage_fault_coprocessor : 1U;
            std::uint32_t enable_halt_on_usage_fault_checking    : 1U;
            std::uint32_t enable_halt_on_usage_fault_state       : 1U;
            std::uint32_t enable_halt_on_bus_fault               : 1U;
            std::uint32_t enable_halt_on_exception_entry_return  : 1U;
            std::uint32_t enable_halt_on_hard_fault              : 1U;
            std::uint32_t                                        : 5U;    ///< Reserved field
            std::uint32_t enable_debug_monitor_exception         : 1U;
            std::uint32_t pending_debug_monitor_exception        : 1U;
            std::uint32_t step_debug_monitor_exception           : 1U;
            std::uint32_t                                        : 1U;    ///< debug_monitor_exception_request?
            std::uint32_t                                        : 4U;    ///< Reserved field
            std::uint32_t enable_trace                           : 1U;
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

    HaltingControl halting_control;
    CoreRegisterSelector core_register_selector;
    CoreRegisterData core_register_data;
    ExceptionMonitorControl exception_monitor_control;
};
static_assert(sizeof(DebugSystem) == 0x10, "Must be this size");

}    // namespace cortex

#endif    // CORTEX_M_DEBUG_HPP_

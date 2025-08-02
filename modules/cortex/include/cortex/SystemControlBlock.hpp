#ifndef CORTEX_M_SYSTEM_HPP_
#define CORTEX_M_SYSTEM_HPP_

/// @file
/// The Cortex M System Registers

#include "cortex/core.hpp"
#include "cortex/exceptions.hpp"
#include "cortex/tick.hpp"
#include "cortex/vendor.hpp"

namespace cortex {

namespace keys {
/// Used to write into the ApplicationInterruptResetControl::key field to reset the system
constexpr static std::uint32_t reset_value = 0x05FA;
}    // namespace keys

/// The peripheral bank mapped to 0xE000E000 in Cortex M processors to a group of system control registers
struct SystemControlBlock final {
    /// The CPU Identifier
    struct CpuIDBase final {
        /// @brief Default constructor
        CpuIDBase()
            : whole{0} {}
        /// @brief Copy constructor
        /// @param other
        CpuIDBase(CpuIDBase const& other)
            : whole{other.whole} {}
        /// @brief Copy constructor for volatile copy
        /// @param other
        CpuIDBase(CpuIDBase volatile& other)
            : whole{other.whole} {}
        /// @brief The bit field for the CPU ID Base Register
        struct Fields final {
            std::uint32_t revision    : 4;
            std::uint32_t part_number : 12;
            std::uint32_t             : 4;    ///< Reserved field
            std::uint32_t variant     : 4;
            std::uint32_t implementer : 8;
        };
        /// @brief The union of the bit field and the whole register
        union {
            Fields parts;
            std::uint32_t whole;
        };
        /// Assignment from copy back to registers
        void operator=(CpuIDBase const& other) volatile { whole = other.whole; }
        /// Copy from volatile register to local copy
        void operator=(CpuIDBase volatile& other) { whole = other.whole; }
    };

    /// The Interrupt Control State Register
    struct InterruptControlState final {
        InterruptControlState()
            : whole{0} {}
        InterruptControlState(InterruptControlState const& other)
            : whole{other.whole} {}
        InterruptControlState(InterruptControlState volatile& other)
            : whole{other.whole} {}

        /// @brief The bit field for the Interrupt Control State Register
        struct Fields final {
            std::uint32_t /* const */ vector_active                     : 9U;
            std::uint32_t                                               : 2U;    ///< Reserved field
            std::uint32_t /* const */ not_other_active                  : 1U;    //!< If 0, another exception is pending
            std::uint32_t /* const */ vector_pending                    : 9U;
            std::uint32_t                                               : 1U;    ///< Reserved field
            std::uint32_t /* const */ interrupt_service_routine_pending : 1U;
            std::uint32_t /* const */ interrupt_service_routine_preempt : 1U;
            std::uint32_t                                               : 1U;    ///< Reserved field
            std::uint32_t remove_pending_system_tick                    : 1U;
            std::uint32_t trigger_system_tick                           : 1U;
            std::uint32_t remove_pending_supervisor                     : 1U;
            std::uint32_t trigger_pending_supervisor                    : 1U;
            std::uint32_t                                               : 2U;    ///< Reserved field
            std::uint32_t trigger_non_maskable                          : 1U;
        };
        /// @brief The union of the bit field and the whole register
        union {
            Fields parts;
            std::uint32_t whole;
        };
        /// Assignment from copy back to registers
        void operator=(InterruptControlState const& other) volatile { whole = other.whole; }
        /// Copy from volatile register to local copy
        void operator=(InterruptControlState volatile& other) { whole = other.whole; }
    };
    static_assert(sizeof(InterruptControlState) == sizeof(std::uint32_t), "Must be exactly this size");

    /// The Application Interrupt Reset and Control Register
    struct ApplicationInterruptResetControl final {
        ApplicationInterruptResetControl()
            : whole{0} {}
        ApplicationInterruptResetControl(ApplicationInterruptResetControl const& other)
            : whole{other.whole} {}
        ApplicationInterruptResetControl(ApplicationInterruptResetControl volatile& other)
            : whole{other.whole} {}

        /// @brief The bit field for the Application Interrupt Reset and Control Register
        struct Fields final {
            std::uint32_t debug_state_vector_reset        : 1U;
            std::uint32_t debug_state_vector_clear_active : 1U;
            std::uint32_t system_reset_request            : 1U;
            std::uint32_t                                 : 5U;    ///< Reserved field
            std::uint32_t priority_group                  : 3U;
            std::uint32_t                                 : 4U;    ///< Reserved field
            std::uint32_t endianess                       : 1U;
            std::uint32_t key                             : 16U;
        };
        /// @brief The union of the bit field and the whole register
        union {
            Fields parts;
            std::uint32_t whole;
        };
        /// Assignment from copy back to registers
        void operator=(ApplicationInterruptResetControl const& other) volatile { whole = other.whole; }
        /// Copy from volatile register to local copy
        void operator=(ApplicationInterruptResetControl volatile& other) { whole = other.whole; }
    };
    static_assert(sizeof(ApplicationInterruptResetControl) == sizeof(std::uint32_t), "Must be exactly this size");

    /// The System Control Register
    struct SystemControl final {
        /// @brief The bit field for the System Control Register
        struct Fields final {
            std::uint32_t                       : 1U;    ///< Reserved field
            std::uint32_t sleep_on_exit         : 1U;
            std::uint32_t sleep_deep            : 1U;
            std::uint32_t                       : 1U;    ///< Reserved field
            std::uint32_t enable_pending_wakeup : 1U;
        };
        /// @brief The union of the bit field and the whole register
        union {
            Fields parts;
            std::uint32_t whole;
        };
    };
    static_assert(sizeof(SystemControl) == sizeof(std::uint32_t), "Must be exactly this size");

    /// The Configuration and Control Register
    struct ConfigurationControl final {
        /// @brief Default constructor
        ConfigurationControl()
            : whole{0} {}
        /// @brief Copy constructor
        ConfigurationControl(ConfigurationControl const& other)
            : whole{other.whole} {}
        /// @brief Copy constructor from volatile register
        ConfigurationControl(ConfigurationControl volatile& other)
            : whole{other.whole} {}
        /// @brief The bit field for the Configuration and Control Register
        struct Fields final {
            std::uint32_t allow_thread_mode_exception_return                     : 1U;
            std::uint32_t allow_unprivileged_access_to_software_trigger          : 1U;
            std::uint32_t                                                        : 1U;    ///< Reserved field
            std::uint32_t trap_unaligned_access                                  : 1U;
            std::uint32_t trap_divide_by_zero                                    : 1U;
            std::uint32_t                                                        : 3U;    ///< Reserved field
            std::uint32_t ignore_precise_data_access_faults_in_negative_priority : 1U;
            std::uint32_t stack_pointer_is_guaranteed_8_byte_aligned             : 1U;
            std::uint32_t                                                        : 6U;    ///< Reserved field
            std::uint32_t enable_data_cache                                      : 1U;
            std::uint32_t enable_instruction_cache                               : 1U;
            std::uint32_t enable_branch_prediction                               : 1U;
            std::uint32_t                                                        : 13U;    ///< Reserved field
        };
        /// @brief The union of the bit field and the whole register
        union {
            Fields parts;
            std::uint32_t whole;
        };
        /// Assignment from copy back to registers
        void operator=(ConfigurationControl const& other) volatile { whole = other.whole; }
        /// Copy from volatile register to local copy
        void operator=(ConfigurationControl volatile& other) { whole = other.whole; }
    };
    static_assert(sizeof(ConfigurationControl) == sizeof(std::uint32_t), "Must be exactly this size");

    /// The System Handler Priority 1 Register
    struct SystemHandlerPriority1 final {
        /// @brief The bit field for the System Handler Priority 1 Register
        struct Fields final {
            std::uint32_t priority_memory_management_fault : 8U;
            std::uint32_t priority_bus_fault               : 8U;
            std::uint32_t priority_usage_fault             : 8U;
            std::uint32_t priority_handler_7               : 8U;
        };
        /// @brief The union of the bit field and the whole register
        union {
            Fields parts;
            std::uint32_t whole;
        };
    };
    static_assert(sizeof(SystemHandlerPriority1) == sizeof(std::uint32_t), "Must be exactly this size");

    /// The System Handler Priority 2 Register
    struct SystemHandlerPriority2 final {
        std::uint32_t priority_handler_8       : 8U;
        std::uint32_t priority_handler_9       : 8U;
        std::uint32_t priority_handler_10      : 8U;
        std::uint32_t priority_supervisor_call : 8U;
    };
    static_assert(sizeof(SystemHandlerPriority2) == sizeof(std::uint32_t), "Must be exactly this size");

    /// The System Handler Priority 3 Register
    struct SystemHandlerPriority3 final {
        std::uint32_t priority_debug_monitor      : 8U;
        std::uint32_t priority_handler_13         : 8U;
        std::uint32_t priority_pending_supervisor : 8U;
        std::uint32_t priority_system_tick        : 8U;
    };
    static_assert(sizeof(SystemHandlerPriority3) == sizeof(std::uint32_t), "Must be exactly this size");

    /// The System Handler Control State Register
    struct SystemHandlerControlState final {
        /// @brief Default constructor
        SystemHandlerControlState()
            : whole{0} {}
        SystemHandlerControlState(SystemHandlerControlState const& other)
            : whole{other.whole} {}
        SystemHandlerControlState(SystemHandlerControlState volatile& other)
            : whole{other.whole} {}
        /// @brief The bit field for the System Handler Control State Register
        struct Fields final {
            std::uint32_t active_mem_fault          : 1;
            std::uint32_t active_bus_fault          : 1;
            std::uint32_t                           : 1;    ///< Reserved field
            std::uint32_t active_usage_fault        : 1;
            std::uint32_t                           : 3;    ///< Reserved field
            std::uint32_t active_supervisor_call    : 1;
            std::uint32_t active_debug_monitor      : 1;
            std::uint32_t                           : 1;    ///< Reserved field
            std::uint32_t active_pending_supervisor : 1;
            std::uint32_t active_system_tick        : 1;

            std::uint32_t pending_usage_fault     : 1;
            std::uint32_t pending_mem_fault       : 1;
            std::uint32_t pending_bus_fault       : 1;
            std::uint32_t pending_supervisor_call : 1;

            std::uint32_t enable_mem_fault   : 1;
            std::uint32_t enable_bus_fault   : 1;
            std::uint32_t enable_usage_fault : 1;

            std::uint32_t : 13;    ///< Reserved field
        };
        /// @brief The union of the bit field and the whole register
        union {
            Fields bits;
            std::uint32_t whole;
        };
        /// Assignment from copy back to registers
        void operator=(SystemHandlerControlState const& other) volatile { whole = other.whole; }
        /// Copy from volatile register to local copy
        void operator=(SystemHandlerControlState volatile& other) { whole = other.whole; }
    };
    static_assert(sizeof(SystemHandlerControlState) == sizeof(std::uint32_t), "Must be exactly this size");

    /// The Configuration Fault Status
    struct ConfigurationFaultStatus final {
        /// @brief Default constructor
        ConfigurationFaultStatus()
            : whole{0} {}
        ConfigurationFaultStatus(ConfigurationFaultStatus const& other)
            : whole{other.whole} {}
        ConfigurationFaultStatus(ConfigurationFaultStatus volatile& other)
            : whole{other.whole} {}
        /// @brief The bit field for the Configuration Fault Status Register
        struct Fields final {
            // Memory Management (MMFSR)
            std::uint32_t execute_never                        : 1U;
            std::uint32_t data_access                          : 1U;
            std::uint32_t                                      : 1U;    ///< Reserved field
            std::uint32_t derived_memory_management_on_return  : 1U;
            std::uint32_t derived_memory_management_on_entry   : 1U;
            std::uint32_t memory_management_on_float_lazy_eval : 1U;
            std::uint32_t                                      : 1U;    ///< Reserved field
            std::uint32_t mmfar_is_valid                       : 1U;
            // Bus Fault (BFSR)
            std::uint32_t instruction_prefetch                 : 1U;
            std::uint32_t precise_data_access                  : 1U;
            std::uint32_t imprecise_data_access                : 1U;
            std::uint32_t derived_bus_on_return                : 1U;
            std::uint32_t derived_bus_on_entry                 : 1U;
            std::uint32_t bus_fault_on_float_lazy_eval         : 1U;
            std::uint32_t                                      : 1U;    ///< Reserved field
            std::uint32_t bfar_is_valid                        : 1U;
            // Usage Fault (UFSR)
            std::uint32_t undefined_instruction                : 1U;
            std::uint32_t invalid_epsr_bits                    : 1U;
            std::uint32_t integrity_check_on_exc_return        : 1U;
            std::uint32_t coprocessor_access_error             : 1U;
            std::uint32_t                                      : 4U;    ///< Reserved field
            std::uint32_t unaligned_access                     : 1U;
            std::uint32_t divide_by_zero                       : 1U;
            std::uint32_t                                      : 6U;    ///< Reserved field
        };
        /// @brief The union of the bit field and the whole register
        union {
            Fields bits;
            std::uint32_t whole;
        };
        /// Assignment from copy back to registers
        void operator=(ConfigurationFaultStatus const& other) volatile { whole = other.whole; }
        /// Copy from volatile register to local copy
        void operator=(ConfigurationFaultStatus volatile& other) { whole = other.whole; }
    };
    static_assert(sizeof(ConfigurationFaultStatus) == sizeof(std::uint32_t), "Must be exactly this size");

    /// The Hard Fault Status Register (HFSR)
    struct HardFaultStatus final {
        HardFaultStatus()
            : whole{0} {}
        HardFaultStatus(HardFaultStatus const& other)
            : whole{other.whole} {}
        HardFaultStatus(HardFaultStatus volatile& other)
            : whole{other.whole} {}
        /// @brief The bit field for the Hard Fault Status Register
        struct Fields {
            std::uint32_t                   : 1U;    ///< Reserved field
            std::uint32_t vector_table_read : 1U;
            std::uint32_t                   : 28U;    ///< Reserved field
            std::uint32_t forced            : 1U;
            std::uint32_t debug_event       : 1U;
        };
        /// @brief The union of the bit field and the whole register
        union {
            Fields bits;
            std::uint32_t whole;
        };
        /// Assignment from copy back to registers
        void operator=(HardFaultStatus const& other) volatile { whole = other.whole; }
        /// Copy from volatile register to local copy
        void operator=(HardFaultStatus volatile& other) { whole = other.whole; }
    };
    static_assert(sizeof(HardFaultStatus) == sizeof(std::uint32_t), "Must be exactly this size");

    /// The Debug Fault Register (DFR)
    struct DebugFaultStatus final {
        DebugFaultStatus()
            : whole{0} {}
        DebugFaultStatus(DebugFaultStatus const& other)
            : whole{other.whole} {}
        DebugFaultStatus(DebugFaultStatus volatile& other)
            : whole{other.whole} {}
        /// @brief The bit field for the Debug Fault Register
        struct Fields {
            std::uint32_t halted           : 1U;
            std::uint32_t breakpoint       : 1U;
            std::uint32_t debug_event_trap : 1U;
            std::uint32_t vector_catch     : 1U;
            std::uint32_t external         : 1U;
            std::uint32_t                  : 27U;    ///< Reserved field
        };
        /// @brief The union of the bit field and the whole register
        union {
            Fields bits;
            std::uint32_t whole;
        };
        /// Assignment from copy back to registers
        void operator=(DebugFaultStatus const& other) volatile { whole = other.whole; }
        /// Copy from volatile register to local copy
        void operator=(DebugFaultStatus volatile& other) { whole = other.whole; }
    };
    static_assert(sizeof(DebugFaultStatus) == sizeof(std::uint32_t), "Must be exactly this size");

    /// The Memory Management Fault Address Register (MMFAR)
    struct MemoryManagementFaultAddress final {
        std::uintptr_t address;
    };
#if defined(__arm__)
    static_assert(sizeof(MemoryManagementFaultAddress) == sizeof(std::uint32_t), "Must be exactly this size");
#endif

    /// The Bus Fault Address Register (BFAR)
    struct BusFaultAddress final {
        std::uintptr_t address;    ///< The Address which faulted
    };
#if defined(__arm__)
    static_assert(sizeof(BusFaultAddress) == sizeof(std::uint32_t), "Must be exactly this size");
#endif

    /// The Co Processor Access Control Register
    struct CoProcessorAccessControl final {
        CoProcessorAccessControl()
            : whole{0} {}
        CoProcessorAccessControl(CoProcessorAccessControl const& other)
            : whole{other.whole} {}
        CoProcessorAccessControl(CoProcessorAccessControl volatile& other)
            : whole{other.whole} {}
        /// @brief The access values for the register
        enum class Access : std::uint32_t {
            Denied = 0b00,
            Privileged = 0b01,
            // Reserved = 0b10,
            Full = 0b11,
        };
        /// @brief The bitfield definition of the register
        struct Fields final {
            Access cp0    : 2U;    ///< Co processor 0
            Access cp1    : 2U;    ///< Co processor 1
            Access cp2    : 2U;    ///< Co processor 2
            Access cp3    : 2U;    ///< Co processor 3
            Access cp4    : 2U;    ///< Co processor 4
            Access cp5    : 2U;    ///< Co processor 5
            Access cp6    : 2U;    ///< Co processor 6
            Access cp7    : 2U;    ///< Co processor 7
            std::uint32_t : 4;     ///< Reserved field
            Access cp10   : 2U;    ///< Co processor 10
            Access cp11   : 2U;    ///< Co processor 11
            std::uint32_t : 8U;    ///< Reserved field
        };
        union {
            Fields bits;
            std::uint32_t whole;
        };
        /// Assignment from copy back to registers
        void operator=(CoProcessorAccessControl const& other) volatile { whole = other.whole; }
        /// Copy from volatile register to local copy
        void operator=(CoProcessorAccessControl volatile& other) { whole = other.whole; }
    };
    static_assert(sizeof(CoProcessorAccessControl) == sizeof(std::uint32_t), "Must be exactly this size");

    //===================================================
    // Storage Definitions
    CpuIDBase cpu_id_base;
    InterruptControlState interrupt_control_state;
    exceptions::VectorTable const* vector_table;
    ApplicationInterruptResetControl application_interrupt_reset_control;
    SystemControl system_control;
    ConfigurationControl configuration_control;
    SystemHandlerPriority1 handlers1;
    SystemHandlerPriority2 handlers2;
    SystemHandlerPriority3 handlers3;
    SystemHandlerControlState system_handler_control_state;
    ConfigurationFaultStatus configuration_fault_status;
    HardFaultStatus hard_fault_status;
    DebugFaultStatus debug_fault_status;
    MemoryManagementFaultAddress memory_management_fault_address;
    BusFaultAddress bus_fault_address;
    vendor::AuxiliaryFaultStatus auxiliary_fault_status;    ///< This is implementation defined (i.e. by Vendor)
    variant::CentralProcessingUnitIdentification cpu_id;    ///< Implementation defined
    CoProcessorAccessControl coprocessor_access_control;
    std::uint32_t : 32;
    //===================================================
};
#if defined(__arm__)
static_assert(sizeof(variant::CentralProcessingUnitIdentification) == 0x48, "Must be this exact size");

// Ensure the structure is in standard layout format
static_assert(std::is_standard_layout<SystemControlBlock>::value, "Must be standard layout");
// Ensure the offsets are all correct
static_assert(offsetof(SystemControlBlock, cpu_id_base) == 0x0UL, "Must be located at this offset");
static_assert(offsetof(SystemControlBlock, interrupt_control_state) == 0x4UL, "Must be located at this offset");
static_assert(offsetof(SystemControlBlock, vector_table) == 0x8UL, "Must be located at this offset");
static_assert(offsetof(SystemControlBlock, application_interrupt_reset_control) == 0xcUL, "Must be located at this offset");
static_assert(offsetof(SystemControlBlock, system_control) == 0x10UL, "Must be located at this offset");
static_assert(offsetof(SystemControlBlock, configuration_control) == 0x14, "Must be at this offset");
static_assert(offsetof(SystemControlBlock, handlers1) == 0x18UL, "Must be located at this offset");
static_assert(offsetof(SystemControlBlock, handlers2) == 0x1cUL, "Must be located at this offset");
static_assert(offsetof(SystemControlBlock, handlers3) == 0x20UL, "Must be located at this offset");
static_assert(offsetof(SystemControlBlock, system_handler_control_state) == 0x24UL, "Must be located at this offset");
static_assert(offsetof(SystemControlBlock, configuration_fault_status) == 0x28UL, "Must be located at this offset");
static_assert(offsetof(SystemControlBlock, hard_fault_status) == 0x2cUL, "Must be located at this offset");
static_assert(offsetof(SystemControlBlock, memory_management_fault_address) == 0x34UL, "Must be located at this offset");
static_assert(offsetof(SystemControlBlock, bus_fault_address) == 0x38UL, "Must be located at this offset");
static_assert(offsetof(SystemControlBlock, auxiliary_fault_status) == 0x3cUL, "Must be located at this offset");
static_assert(offsetof(SystemControlBlock, coprocessor_access_control) == 0x88, "Must be at this offset");
static_assert(sizeof(SystemControlBlock) == 0x90, "Must be this size");
#endif

/// The Interrupt Controller Type Register (ICTR) is outside the SCB.
struct InterruptControllerType final {
    uint32_t group_interrupt_lines_count;    ///< The total number of group of interrupt lines of this implementation.

    /// Returns the upper limit of individual number of interrupt lines
    inline uint32_t get_interrupt_lines_limit(void) { return (32U * (group_interrupt_lines_count + 1U)); }
};
static_assert(sizeof(InterruptControllerType) == sizeof(std::uint32_t), "Must be this exact size");

/// Import the definition of the Auxiliary Control from the Variant
using AuxiliaryControl = variant::AuxiliaryControl;

/// The special purpose Control Register (CONTROL)
struct Control final {
    /// @brief Default constructor
    constexpr Control()
        : whole{0U} {}
    /// @brief Parameterized constructor
    /// @param reg The value to put in the register
    Control(cortex::word reg)
        : whole{reg} {}
    /// @brief The bitfield definition of the register
    struct Fields final {
        modes::Privileged privilege : 1;     ///< Execution Privilege in Thread Mode
        modes::Stack stack          : 1;     ///< 0 is Main, 1 is Process
        std::uint32_t float_active  : 1;     ///< Floating Point Active
        std::uint32_t               : 29;    ///< Reserved field
    };
    /// @brief The union of the bitfield and the register as a whole.
    union {
        Fields parts;
        cortex::word whole;    ///< This is used via thumb instructions and thus should be a processor word and not a
                               ///< memory mapped register
    };
};

/// (FPSCR) Floating Point Status and Control Register
/// @see VMRS and VMSR thumb instructions
struct FloatingPointStatusControl final {
    /// @brief The bitfield definition of the register
    struct Fields final {
        std::uint32_t invalid_cumulative        : 1U;     ///< Invalid Operation
        std::uint32_t divide_by_zero_cumulative : 1U;     ///< Divide by Zero
        std::uint32_t overflow_cumulative       : 1U;     ///< Overflow
        std::uint32_t underflow_cumulative      : 1U;     ///< Underflow cumulative
        std::uint32_t inexact_cumulative        : 1U;     ///< Inexact cumulative
        std::uint32_t                           : 2U;     ///< Reserved
        std::uint32_t input_denormal_cumulative : 1U;     ///< Input denormal cumulative
        std::uint32_t                           : 14U;    ///< Reserved
        modes::Rounding rounding                : 2U;     ///< Rounding mode
        std::uint32_t flush_to_zero             : 1U;     ///< Flush to zero
        std::uint32_t default_nan               : 1U;     ///< Default NaN
        std::uint32_t half_precision            : 1U;     ///< Half precision
        std::uint32_t                           : 1U;     /// Reserved
        std::uint32_t overflow                  : 1U;     ///< Overflow
        std::uint32_t carry                     : 1U;     ///< Carry
        std::uint32_t zero                      : 1U;     ///< Zero
        std::uint32_t negative                  : 1U;     ///< Negative
    };
    /// @brief The union of the bitfield and the register as a whole.
    union {
        Fields parts;
        std::uint32_t whole;
    };
};

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

    //============================
    ContextControl context_control;
    ContextAddress context_address;
    DefaultStatusControl default_status_control;
    MediaFeatures0 media_features_0;
    MediaFeatures1 media_features_1;
    MediaFeatures2 media_features_2;
};

/// (STIR) The Software Triggered Interrupt Register
struct SoftwareTriggeredInterrupt final {
    /// @brief The bitfield definition of the register
    struct Fields final {
        std::uint32_t interrupt : 9U;
        std::uint32_t           : 23U;
    };
    union {
        Fields bits;
        std::uint32_t whole;
    };
};

}    // namespace cortex

#endif    // CORTEX_M_SYSTEM_HPP_
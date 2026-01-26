#ifndef CORTEX_PERIPHERALS_SYSTEM_CONTROL_BLOCK_HPP_
#define CORTEX_PERIPHERALS_SYSTEM_CONTROL_BLOCK_HPP_

/// @file
/// The Cortex Microcontroller System Control Block peripheral

#include "cortex/exceptions.hpp"
#include "cortex/partnumber.hpp"    // Pulls in the Vendor AuxiliaryFaultStatus definition
#include "cortex/types.hpp"

namespace cortex {

namespace keys {
/// Used to write into the ApplicationInterruptResetControl::key field to reset the system
constexpr static std::uint32_t reset_value = 0x05FA;
}    // namespace keys

namespace peripherals {
/// The peripheral bank mapped to 0xE000E000 in Cortex Microcontroller processors to a group of system control registers
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
            std::uint32_t revision    : 4;     ///< Revision number
            std::uint32_t part_number : 12;    ///< Part number
            std::uint32_t             : 4;
            std::uint32_t variant     : 4;     ///< Variant number
            std::uint32_t implementer : 8;     ///< Implementer code
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
        /// Default constructor - initializes to zero
        InterruptControlState()
            : whole{0} {}
        /// Copy constructor from another instance
        InterruptControlState(InterruptControlState const& other)
            : whole{other.whole} {}
        /// Copy constructor from volatile register
        InterruptControlState(InterruptControlState volatile& other)
            : whole{other.whole} {}

        /// @brief The bit field for the Interrupt Control State Register
        struct Fields final {
            std::uint32_t /* const */ vector_active                     : 9U;    ///< Exception number of currently active exception
            std::uint32_t                                               : 2U;
            std::uint32_t /* const */ not_other_active                  : 1U;    ///< If 0, another exception is pending
            std::uint32_t /* const */ vector_pending                    : 9U;    ///< Exception number of highest priority pending exception
            std::uint32_t                                               : 1U;
            std::uint32_t /* const */ interrupt_service_routine_pending : 1U;    ///< Interrupt pending flag (excludes NMI and Faults)
            std::uint32_t /* const */ interrupt_service_routine_preempt : 1U;    ///< Pre-empt pending flag
            std::uint32_t                                               : 1U;
            std::uint32_t remove_pending_system_tick                    : 1U;    ///< Clear SysTick pending status
            std::uint32_t trigger_system_tick                           : 1U;    ///< Set SysTick pending
            std::uint32_t remove_pending_supervisor                     : 1U;    ///< Clear PendSV pending status
            std::uint32_t trigger_pending_supervisor                    : 1U;    ///< Set PendSV pending
            std::uint32_t                                               : 2U;
            std::uint32_t trigger_non_maskable                          : 1U;    ///< Set NMI pending
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
        /// Default constructor - initializes to zero
        ApplicationInterruptResetControl()
            : whole{0} {}
        /// Copy constructor from another instance
        ApplicationInterruptResetControl(ApplicationInterruptResetControl const& other)
            : whole{other.whole} {}
        /// Copy constructor from volatile register
        ApplicationInterruptResetControl(ApplicationInterruptResetControl volatile& other)
            : whole{other.whole} {}

        /// @brief The bit field for the Application Interrupt Reset and Control Register
        struct Fields final {
            std::uint32_t debug_state_vector_reset        : 1U;     ///< Debug state reset control
            std::uint32_t debug_state_vector_clear_active : 1U;     ///< Clear all active state info
            std::uint32_t system_reset_request            : 1U;     ///< System reset request
            std::uint32_t                                 : 5U;
            std::uint32_t priority_group                  : 3U;     ///< Priority grouping (preemption/subpriority split)
            std::uint32_t                                 : 4U;
            std::uint32_t endianess                       : 1U;     ///< Endianness (0=little, 1=big)
            std::uint32_t key                             : 16U;    ///< Register key (0x05FA for writes)
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
            std::uint32_t                       : 1U;
            std::uint32_t sleep_on_exit         : 1U;    ///< Enter sleep on return from ISR
            std::uint32_t sleep_deep            : 1U;    ///< Use deep sleep as low power mode
            std::uint32_t                       : 1U;
            std::uint32_t enable_pending_wakeup : 1U;    ///< Send event on pending interrupt
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
            std::uint32_t allow_thread_mode_exception_return                     : 1U;    ///< Allow return to thread mode from any level
            std::uint32_t allow_unprivileged_access_to_software_trigger          : 1U;    ///< Unprivileged software can trigger interrupts
            std::uint32_t                                                        : 1U;
            std::uint32_t trap_unaligned_access                                  : 1U;    ///< Trap on unaligned accesses
            std::uint32_t trap_divide_by_zero                                    : 1U;    ///< Trap on divide by zero
            std::uint32_t                                                        : 3U;
            std::uint32_t ignore_precise_data_access_faults_in_negative_priority : 1U;    ///< Ignore data faults in negative priority handlers
            std::uint32_t stack_pointer_is_guaranteed_8_byte_aligned             : 1U;    ///< Stack guaranteed 8-byte aligned
            std::uint32_t                                                        : 6U;
            std::uint32_t enable_data_cache                                      : 1U;    ///< Enable data cache
            std::uint32_t enable_instruction_cache                               : 1U;    ///< Enable instruction cache
            std::uint32_t enable_branch_prediction                               : 1U;    ///< Always reads as 1 on Cortex-M*
            std::uint32_t                                                        : 13U;
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
            std::uint32_t priority_memory_management_fault : 8U;    ///< Priority of MemManage exception
            std::uint32_t priority_bus_fault               : 8U;    ///< Priority of BusFault exception
            std::uint32_t priority_usage_fault             : 8U;    ///< Priority of UsageFault exception
            std::uint32_t priority_handler_7               : 8U;    ///< Reserved handler priority
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
        std::uint32_t priority_handler_8       : 8U;    ///< Reserved handler priority
        std::uint32_t priority_handler_9       : 8U;    ///< Reserved handler priority
        std::uint32_t priority_handler_10      : 8U;    ///< Reserved handler priority
        std::uint32_t priority_supervisor_call : 8U;    ///< Priority of SVCall exception
    };
    static_assert(sizeof(SystemHandlerPriority2) == sizeof(std::uint32_t), "Must be exactly this size");

    /// The System Handler Priority 3 Register
    struct SystemHandlerPriority3 final {
        std::uint32_t priority_debug_monitor      : 8U;    ///< Priority of DebugMonitor exception
        std::uint32_t priority_handler_13         : 8U;    ///< Reserved handler priority
        std::uint32_t priority_pending_supervisor : 8U;    ///< Priority of PendSV exception
        std::uint32_t priority_system_tick        : 8U;    ///< Priority of SysTick exception
    };
    static_assert(sizeof(SystemHandlerPriority3) == sizeof(std::uint32_t), "Must be exactly this size");

    /// The System Handler Control State Register
    struct SystemHandlerControlState final {
        /// @brief Default constructor
        SystemHandlerControlState()
            : whole{0} {}
        /// Copy constructor from another instance
        SystemHandlerControlState(SystemHandlerControlState const& other)
            : whole{other.whole} {}
        /// Copy constructor from volatile register
        SystemHandlerControlState(SystemHandlerControlState volatile& other)
            : whole{other.whole} {}
        /// @brief The bit field for the System Handler Control State Register
        struct Fields final {
            std::uint32_t active_mem_fault          : 1;    ///< Active MemManage fault
            std::uint32_t active_bus_fault          : 1;    ///< Active BusFault
            std::uint32_t                           : 1;
            std::uint32_t active_usage_fault        : 1;    ///< Active UsageFault
            std::uint32_t                           : 3;
            std::uint32_t active_supervisor_call    : 1;    ///< Active SVCall
            std::uint32_t active_debug_monitor      : 1;    ///< Active DebugMonitor
            std::uint32_t                           : 1;
            std::uint32_t active_pending_supervisor : 1;    ///< Active PendSV
            std::uint32_t active_system_tick        : 1;    ///< Active SysTick

            std::uint32_t pending_usage_fault       : 1;    ///< Pending UsageFault
            std::uint32_t pending_mem_fault         : 1;    ///< Pending MemManage fault
            std::uint32_t pending_bus_fault         : 1;    ///< Pending BusFault
            std::uint32_t pending_supervisor_call   : 1;    ///< Pending SVCall

            std::uint32_t enable_mem_fault          : 1;    ///< Enable MemManage fault
            std::uint32_t enable_bus_fault          : 1;    ///< Enable BusFault
            std::uint32_t enable_usage_fault        : 1;    ///< Enable UsageFault

            std::uint32_t                           : 13;
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
        /// Copy constructor from another instance
        ConfigurationFaultStatus(ConfigurationFaultStatus const& other)
            : whole{other.whole} {}
        /// Copy constructor from volatile register
        ConfigurationFaultStatus(ConfigurationFaultStatus volatile& other)
            : whole{other.whole} {}
        /// @brief The bit field for the Configuration Fault Status Register
        struct Fields final {
            // Memory Management (MMFSR)
            std::uint32_t execute_never                        : 1U;    ///< Instruction access violation
            std::uint32_t data_access                          : 1U;    ///< Data access violation
            std::uint32_t                                      : 1U;
            std::uint32_t derived_memory_management_on_return  : 1U;    ///< Memory management fault on return from exception
            std::uint32_t derived_memory_management_on_entry   : 1U;    ///< Memory management fault on exception entry
            std::uint32_t memory_management_on_float_lazy_eval : 1U;    ///< Memory management fault during lazy FP state preservation
            std::uint32_t                                      : 1U;
            std::uint32_t mmfar_is_valid                       : 1U;    ///< MMFAR is valid
            // Bus Fault (BFSR)
            std::uint32_t instruction_prefetch                 : 1U;    ///< Instruction prefetch bus fault
            std::uint32_t precise_data_access                  : 1U;    ///< Precise data access bus fault
            std::uint32_t imprecise_data_access                : 1U;    ///< Imprecise data access bus fault
            std::uint32_t derived_bus_on_return                : 1U;    ///< Bus fault on return from exception
            std::uint32_t derived_bus_on_entry                 : 1U;    ///< Bus fault on exception entry
            std::uint32_t bus_fault_on_float_lazy_eval         : 1U;    ///< Bus fault during lazy FP state preservation
            std::uint32_t                                      : 1U;
            std::uint32_t bfar_is_valid                        : 1U;    ///< Bus Fault Address Register is valid
            // Usage Fault (UFSR)
            std::uint32_t undefined_instruction                : 1U;    ///< Undefined instruction usage fault
            std::uint32_t invalid_epsr_bits                    : 1U;    ///< Invalid EPSR usage fault
            std::uint32_t integrity_check_on_exc_return        : 1U;    ///< Integrity check usage fault on exception return
            std::uint32_t coprocessor_access_error             : 1U;    ///< Coprocessor access usage fault
            std::uint32_t                                      : 4U;
            std::uint32_t unaligned_access                     : 1U;    ///< Unaligned access usage fault
            std::uint32_t divide_by_zero                       : 1U;    ///< Divide by zero usage fault
            std::uint32_t                                      : 6U;
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
        /// Default constructor - initializes to zero
        HardFaultStatus()
            : whole{0} {}
        /// Copy constructor from another instance
        HardFaultStatus(HardFaultStatus const& other)
            : whole{other.whole} {}
        /// Copy constructor from volatile register
        HardFaultStatus(HardFaultStatus volatile& other)
            : whole{other.whole} {}
        /// @brief The bit field for the Hard Fault Status Register
        struct Fields {
            std::uint32_t                   : 1U;
            std::uint32_t vector_table_read : 1U;    ///< Vector table read fault
            std::uint32_t                   : 28U;
            std::uint32_t forced            : 1U;    ///< Forced hard fault
            std::uint32_t debug_event       : 1U;    ///< Debug event hard fault
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
        /// Default constructor - initializes to zero
        DebugFaultStatus()
            : whole{0} {}
        /// Copy constructor from another instance
        DebugFaultStatus(DebugFaultStatus const& other)
            : whole{other.whole} {}
        /// Copy constructor from volatile register
        DebugFaultStatus(DebugFaultStatus volatile& other)
            : whole{other.whole} {}
        /// @brief The bit field for the Debug Fault Register
        struct Fields {
            std::uint32_t halted           : 1U;    ///< Halted
            std::uint32_t breakpoint       : 1U;    ///< Breakpoint
            std::uint32_t debug_event_trap : 1U;    ///< Debug event trap
            std::uint32_t vector_catch     : 1U;    ///< Vector catch
            std::uint32_t external         : 1U;    ///< External debug request
            std::uint32_t                  : 27U;
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
        std::uintptr_t address;    ///< Address that caused the MemManage fault
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
        /// Default constructor - initializes to zero
        CoProcessorAccessControl()
            : whole{0} {}
        /// Copy constructor from another instance
        CoProcessorAccessControl(CoProcessorAccessControl const& other)
            : whole{other.whole} {}
        /// Copy constructor from volatile register
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
            std::uint32_t : 4;
            Access cp10   : 2U;    ///< Co processor 10
            Access cp11   : 2U;    ///< Co processor 11
            std::uint32_t : 8U;
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
    CpuIDBase cpu_id_base;                                                   ///< CPU ID base register
    InterruptControlState interrupt_control_state;                           ///< Interrupt control and state register
    exceptions::VectorTable const* vector_table;                             ///< Vector table offset register
    ApplicationInterruptResetControl application_interrupt_reset_control;    ///< Application interrupt and reset control
    SystemControl system_control;                                            ///< System control register
    ConfigurationControl configuration_control;                              ///< Configuration and control register
    SystemHandlerPriority1 handlers1;                                        ///< System handler priority register 1
    SystemHandlerPriority2 handlers2;                                        ///< System handler priority register 2
    SystemHandlerPriority3 handlers3;                                        ///< System handler priority register 3
    SystemHandlerControlState system_handler_control_state;                  ///< System handler control and state register
    ConfigurationFaultStatus configuration_fault_status;                     ///< Configurable fault status register
    HardFaultStatus hard_fault_status;                                       ///< Hard fault status register
    DebugFaultStatus debug_fault_status;                                     ///< Debug fault status register
    MemoryManagementFaultAddress memory_management_fault_address;            ///< Memory management fault address register
    BusFaultAddress bus_fault_address;                                       ///< Bus fault address register
    variant::AuxiliaryFaultStatus auxiliary_fault_status;                    ///< This is implementation defined (i.e. by the Variant)
    variant::CentralProcessingUnitIdentification cpu_id;                     ///< Implementation defined
    std::uint32_t : 32;                                                      // Reserved
#if defined(CORTEX_M) and (CORTEX_M == 4)
    std::uint32_t : 32;                                                      // Reserved
    std::uint32_t : 32;                                                      // Reserved
    std::uint32_t : 32;                                                      // Reserved
    std::uint32_t : 32;                                                      // Reserved
#elif defined(CORTEX_M) and (CORTEX_M == 7)
    variant::CacheInformation cache_information;
#endif
    CoProcessorAccessControl coprocessor_access_control;    ///< Coprocessor access control register
    std::uint32_t : 32;                                     // Reserved
    //===================================================
};
#if defined(__arm__)
static_assert(sizeof(variant::CentralProcessingUnitIdentification) == 13U * sizeof(std::uint32_t), "Must be this exact size");

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

/// The pointer to the System Control Block of the Cortex processor
/// @note Initialized in @see globals()
extern SystemControlBlock volatile system_control_block;

}    // namespace peripherals
}    // namespace cortex

#endif    // CORTEX_PERIPHERALS_SYSTEM_CONTROL_BLOCK_HPP_

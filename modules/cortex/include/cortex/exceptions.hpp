#ifndef CORTEX_M_EXCEPTIONS_HPP_
#define CORTEX_M_EXCEPTIONS_HPP_

/// @file
/// The Cortex M Hardware Exceptions Header

#include <cstdint>
#include "cortex/core.hpp"

namespace cortex {

/// The Hardware Exceptions Namespace
namespace exceptions {

/// The various exception types in the System
enum class Type : std::uint32_t {
    Reset = 1U,
    NonMaskable = 2U,
    HardFault = 3U,
    MemoryManagementFault = 4U,
    BusFault = 5U,
    UsageFault = 6U,
    // 7-10 Reserved
    SupervisorCall = 11U,
    // 12-13 Reserved
    PendingSupervisor = 14U,
    SystemTick = 15U,
    Interrupt = 16U,
};

/// The enumeration of Interrupt Request Numbers for the Cortex Micro-controllers
enum class InterruptRequest : std::int32_t {
    NonMaskable = -14,
    HardFault = -13,
    MemoryManagementFault = -12,
    BusFault = -11,
    UsageFault = -10,
    SupervisorCall = -5,
    DebugMonitor = -4,
    PendSV = -2,
    SysTick = -1,
};

/// Exception Priorities
enum class Priority : std::int32_t {
    Highest = -3,
    Higher = -2,
    High = -1,
    /// value between 0 - 255
};

/// The ISR enumeration
enum class InterruptServiceRoutine : std::uint32_t {
    Reset = 0U,
    // 1 is Reserved
    NonMaskable = 2U,
    HardFault = 3U,
    MemoryManagement = 4U,
    BusFault = 5U,
    UsageFault = 6U,
    // 6-10 is Reserved
    SupervisorCall = 11U,
    // 12 is Reserved for Debug
    // 13 is Reserved
    PendSV = 14U,
    SystemTick = 15U,
    // 16-255 is External Interrupts
    BaseExternal = 16U,
};

/// An ISR Handler takes no direct arguments
using HandlerFunction = void (*)(void);

/// The Cortex M Vector Table
struct VectorTable final {
    void* stack_pointer;
    /// Contains the Exception Handlers (Reset + Faults + Interrupts)
    struct Handlers final {
        HandlerFunction reset_entry;
        HandlerFunction non_maskable_interrupt;
        /// Contains the Fault Handlers
        struct FaultHandlers final {
            HandlerFunction hard;
            HandlerFunction memory_management;
            HandlerFunction bus;
            HandlerFunction usage;
        };
        FaultHandlers faults;
        HandlerFunction _reserved1;
        HandlerFunction _reserved2;
        HandlerFunction _reserved3;
        HandlerFunction _reserved4;
        HandlerFunction supervisor_call;
        HandlerFunction debug_monitor;
        HandlerFunction _reserved5;
        HandlerFunction pending_supervisor;
        HandlerFunction system_tick;
    };
    // static_assert(sizeof(Handlers) == 16*sizeof(Handler), "Must be exactly this size");
    Handlers handlers;
};
#if defined(__arm__)
// debug::ConstexprValueCompare<sizeof(VectorTable::Handlers), 15*sizeof(Handler)> test;
static_assert(sizeof(VectorTable) == 0x40U, "Must fit exactly");
#endif

/// The Basic Exception Frame push
struct BasicFrame final {
    cortex::word r0;                   ///< A scratch or temporary register
    cortex::word r1;                   ///< A scratch or temporary register
    cortex::word r2;                   ///< A scratch or temporary register
    cortex::word r3;                   ///< A scratch or temporary register
    cortex::word r12;                  ///< A scratch or temporary register
    std::uintptr_t link_return;        ///< The address to return to after the exception
    std::uintptr_t program_counter;    ///< The location of the program counter when the exception happened
    std::uint32_t xpsr;                ///< @todo implement this as a struct
};
#if defined(__arm__)
static_assert(sizeof(BasicFrame) == 0x20U, "Must be this big");
#endif

/// The Core Exception Frame plus the floating point registers
struct ExtendedFrame final {
    BasicFrame basic;       ///< The Basic Frame
    float s[16];            ///< Single Precision Scratch or Temporary Registers
    std::uint32_t fpcsr;    ///< @todo implement this as a struct
};
#if defined(__arm__)
static_assert(sizeof(ExtendedFrame) == 0x64U, "Must be this size exactly");
#endif

/// Also known as EXC_RETURN, this is the value that is placed back in the PC
/// when the Handler wants to return. Some combinations of flags are invalid.
struct ExceptionReturn final {
    constexpr ExceptionReturn()
        : whole{0xFF'FF'FF'E1UL} {}
    struct Fields final {
        std::uint32_t              : 2U;     ///< Reserved
        cortex::modes::Stack stack : 1U;     ///< Chooses between Main (0) and Process (1) Stack
        modes::Execution mode      : 1U;     ///< Chooses between Handler (0) and Thread (1) Mode
        modes::Frame frame         : 1U;     ///< Chooses between Extended (0) and Basic (1) Frame
        std::uint32_t              : 20U;    ///< Reserved
        std::uint32_t top          : 4U;     ///< Used to check if the value is a valid exception return
    };
    union {
        Fields parts;
        std::uint32_t whole;
    };

    /// Indicates if a ExceptionReturn is a valid type of return.
    /// @see armv7-m architecture manual
    /// @return true if valid, false otherwise
    bool is_valid(void) { return (parts.top == 0xFU); }

    /// Extracts the EXC_RETURN value from the LR.
    /// @return ExceptionReturn value
    __attribute__((always_inline)) inline static ExceptionReturn Extract(void) {
        ExceptionReturn exc_return;
#if defined(__arm__)
        asm volatile("mov %0, lr \r\n"           // ONLY during an exception will this work.
                     : "=r"(exc_return.whole)    // outputs
                     :                           // inputs
                     : "cc", "memory"            // clobbers
        );
#endif
        return exc_return;
    }

    /// A method used to return from an exception
    /// @note Normally this would be marked [[noreturn]] but the
    /// compiler seems to think that this function returns, which it can't.
    __attribute__((always_inline)) inline void return_from_exception(void) {
#if defined(__arm__)
        asm volatile("bx %0 \r\n"
                     :                         // outputs
                     : "r"(whole)              // inputs
                     : "r0", "cc", "memory"    // clobbers
        );
#endif
    }
};

/// The generic handler for all hardware exceptions
using ExtendedHandler = void (*)(cortex::exceptions::ExtendedFrame* frame, cortex::exceptions::ExceptionReturn exc_return);

}    // namespace exceptions
}    // namespace cortex

#endif    // CORTEX_M_EXCEPTIONS_HPP_
#ifndef CORTEX_M_HPP_
#define CORTEX_M_HPP_

/// @file
/// The Cortex Micro Controller Header

#include <cstdint>
#include <cstddef>
#include <limits>
#include "debug.hpp"
#include "iso.hpp"
#include "compiler.hpp"
#include "core/Split.hpp"
#include "cortex/thumb.hpp"
#include "cortex/system.hpp"
#include "cortex/exceptions.hpp"
#include "cortex/mpu.hpp"
#include "cortex/trace.hpp"
#include "cortex/debug.hpp"
#include "cortex/tick.hpp"
#include "cortex/clocks.hpp"
#include "cortex/nvic.hpp"
#include "cortex/bist.hpp"
#include "cortex/supervisor.hpp"

/// The Cortex M Namespace
namespace cortex {

/// The number of bits per byte on this processor
constexpr static std::uint32_t bits_per_byte = 8U;

namespace address {

/// Base Code Address
constexpr static uintptr_t code = 0x00000000;

/// Base SRAM Address
constexpr static uintptr_t sram = 0x20000000;

/// Base Peripherals Address
constexpr static uintptr_t peripheral = 0x40000000;

/// Base RAM0 Address
constexpr static uintptr_t ram0 = 0x60000000;

/// Base RAM1 Address
constexpr static uintptr_t ram1 = 0x80000000;

/// Base Device0 Address
constexpr static uintptr_t device_shared = 0xA0000000;

/// Base Device1 Address
constexpr static uintptr_t device_unshared = 0xC0000000;

/// Base System Address
constexpr static uintptr_t system = 0xE0000000;

/// Instruction Trace Macrocell (ITM) Address
constexpr static uintptr_t itm = 0xE0000000;

/// Debug Watch and Trace (DWT) Address
constexpr static uintptr_t dwt = 0xE0001000;

/// Flash Patch and Breakpoint (FPB) Address
constexpr static uintptr_t fpb = 0xE0002000;

/// The Interrupt Control Type (ICTR) Address
constexpr static uintptr_t ictr = 0xE000E004;

/// The Auxiliary Control (ACTLR) Address
constexpr static uintptr_t actlr = 0xE000E008;

/// The System Tick (Sys_TICK) Address
constexpr static uintptr_t systick = 0xE000E010;

/// The Nested Interrupt Controller
constexpr static uintptr_t nvic = 0xE000E100;

/// System Control Block (SCB) Address
constexpr static uintptr_t scb = 0xE000ED00;

/// Memory Protected Unit (MPU) Address
constexpr static uintptr_t mpu = 0xE000ED90;

/// Debug System Registers (DSR) Address
constexpr static uintptr_t dsr = 0xE000EDF0;

/// Software Triggered Interrupt Register
constexpr static uintptr_t stir = 0xE000EF00;

/// Floating Point Extension Registers
constexpr static uintptr_t fp = 0xE000EF34;

/// Trace Protocol Interface Unit (TPIU) Address
constexpr static uintptr_t tpiu = 0xE0040000;

/// Vendor Region (Vendor_SYS) Address
constexpr static uintptr_t vendor = 0xE0100000;

}    // namespace address

namespace sizes {
/// Code space is defined as 256 MB
constexpr static std::uint32_t code = 256U * iso::prefix::mebi;

/// SRAM space is defined as 256 MB
constexpr static std::uint32_t sram = 256U * iso::prefix::mebi;

/// Peripheral space is defined as 256 MB
constexpr static std::uint32_t peripheral = 256U * iso::prefix::mebi;

/// SRAM space is defined as 256 MB
constexpr static std::uint32_t ram0 = 256U * iso::prefix::mebi;

/// SRAM space is defined as 256 MB
constexpr static std::uint32_t ram1 = 256U * iso::prefix::mebi;

/// System space is defined as 1 MB
constexpr static std::uint32_t system = 256U * iso::prefix::mebi;

/// Private Peripheral Bus space is defined as 1 MB
constexpr static std::uint32_t private_peripheral = 1U * iso::prefix::mebi;

/// Vendor System space is defined as 256 MB minus 1 MB
constexpr static std::uint32_t vendor = (256U * iso::prefix::mebi) - private_peripheral;

/// The collection of the powers of 2 of the sizes
namespace power2 {

/// The Power of 2 of the code section
constexpr static std::uint32_t code = polyfill::log2(cortex::sizes::code);

/// The Power of 2 of the SRAM section
constexpr static std::uint32_t sram = polyfill::log2(cortex::sizes::sram);

/// The Power of 2 of the Peripheral space
constexpr static std::uint32_t peripheral = polyfill::log2(cortex::sizes::peripheral);

/// The Power of 2 of the System section
constexpr static std::uint32_t system = polyfill::log2(cortex::sizes::system);

/// The Power of 2 of the Private Peripherals section
constexpr static std::uint32_t private_peripheral = polyfill::log2(cortex::sizes::private_peripheral);
}    // namespace power2

}    // namespace sizes

namespace registers {

/// The Program Status Registers
struct ProgramStatus final {
    /// The Application Status Register
    struct Application final {
        std::uint32_t            : 16U;    ///< Reserved field
        std::uint32_t ge_flags   : 4U;     //!< GE
        std::uint32_t            : 7U;     ///< Reserved field
        std::uint32_t saturation : 1U;     //!< aka Q
        std::uint32_t overflow   : 1U;     //!< aka V
        std::uint32_t carry      : 1U;     //!< aka C
        std::uint32_t zero       : 1U;     //!< aka Z
        std::uint32_t negative   : 1U;     //!< aka N
    };
    /// The Interrupt Status Register
    struct Interrupt final {
        /// @see cortex::m4::IRQn or processor specific enum
        exceptions::InterruptServiceRoutine interrupt_service_routine : 9U;
        /// Reserved field
        std::uint32_t                                                 : 23U;
    };
    /// The Execution Status Register
    struct Execution final {
        std::uint32_t        : 10U;    ///< Reserved field
        std::uint32_t bottom : 6U;     //!< Bottom ICI/IT bits
        std::uint32_t        : 8U;     ///< Reserved field
        std::uint32_t thumb  : 1U;     //!< Thumb Mode
        std::uint32_t top    : 2U;     //!< Top ICI/IT Bits
        std::uint32_t        : 5U;     ///< Reserved field

        inline std::uint32_t get(void) const {
            std::uint32_t tmp = static_cast<uint32_t>(top << 6U);
            tmp |= bottom;
            return tmp;
        }
    };
};

// The Mask Register Set
struct Masks final {
    /// The Priority Mask Register
    struct Priority final {
        std::uint32_t mask : 1;
        std::uint32_t      : 31;    ///< Reserved field
    };
    /// The Fault Mask Register
    struct Fault final {
        std::uint32_t mask : 1;
        std::uint32_t      : 31;    ///< Reserved field
    };
    /// The Base Priority Mask Register
    struct BasePriority final {
        std::uint32_t mask : 8U;     //!< Not a bit mask but _masks_ priorities less than this value
        std::uint32_t      : 24U;    ///< Reserved field
    };
};

}    // namespace registers

// ==========================================================================================
// System Private Peripheral Bus Registers

/// The pointer to the System Control Block of the Cortex processor
/// @note Initialized in @see globals()
extern SystemControlBlock volatile system_control_block;

/// The Floating Point Extension registers
extern FloatingPoint volatile floating_point;

/// The Debug Block
extern DebugSystem volatile debug_system;

/// The pointer to the Memory Protection Unit
extern MemoryProtectionUnit volatile memory_protection_unit;

/// The pointer to the DWT module
extern DataWatchAndTrace volatile data_watch_and_trace;

/// The pointer to the TPIU module
extern TracePortInterfaceUnit volatile trace_port_interface_unit;

/// The pointer to the Interrupt Controller Type Register
extern InterruptControllerType volatile interrupt_controller_type;

/// The pointer to the Auxiliary Control Register
extern AuxiliaryControl volatile auxiliary_control;

/// The pointer to the Software Triggered Interrupt Register
extern SoftwareTriggeredInterrupt volatile software_triggered_interrupt;

// ==========================================================================================
// Micro Controller API

/// Requests a Reset to the External System (via signal?)
[[noreturn]] void request_external_reset(void);

/// Causes a Non Maskable Interrupt to Fire
void trigger_non_maskable_interrupt(void);

/// Causes a processor exception to enter into Pending Supervisor
void trigger_pending_supervisor(void);

/// Causes a system tick interrupt to fire.
void trigger_system_tick(void);

/// Contains the methods to initialize various parts of the MCU.
/// @warning These should ONLY be called by the boot sequence!
namespace initialize {
/// Initializes Simple Cortex Global variables needed to use across other calls.
void simple_globals(void);
/// Initializes Class Cortex Global variables needed to use across other calls.
void class_globals(void);

/// Grants access to the FPU
void fpu(void);

/// Initializes the MPU entries
void mpu(void);

/// Initializes the SWO output
void swo(std::uint32_t desired_baud, Hertz clock_frequency);

/// Initializes the Instruction Trace Macrocell
void itm(void);

/// Initializes the Trace Port Interface Unit
void tpiu(void);

/// Initializes the Standard Faults in the System
void faults(void);

/// Initializes the Nested Vector Interrupt Controller
void nvic(void);

/// Initializes the System Tick
void tick(Hertz ticks_per_second, Hertz reference_clock_frequency);
}    // namespace initialize

/// The Serial Wire Output Namespace
namespace swo {

/// The fundamental type for ports
using PortType = std::uint32_t;

/// The enumerated list of ports
enum class Port : PortType {
    Errors = 0U,
    System = 1U,
    _max = System,
};

/// The mask of all enumerated types
constexpr static PortType PortMask = ((1U << to_underlying(Port::_max)) - 1U);

/// Emits a single value on a single port.
void emit(Port port, std::uint8_t value);

/// Emits an array of character values, synchronously, on a single port.
void emit(Port port, char const array[], std::size_t bytes);

/// Emits an array of character values until the null, on a single port.
void emit(Port port, char const* const str);

/// Emits an array of data values, synchronously, on a single port.
void emit(std::uint32_t port, std::uint8_t const array[], std::size_t bytes);
}    // namespace swo

/// Contains operations on the Cache subsystems
namespace cache {
/// Contains operations on the Data Cache
namespace data {

/// Invalidate the Data Cache
/// @pre cortex::initialize::globals
void invalidate(void);

/// Disable the Data Cache
/// @pre cortex::initialize::globals
void disable(void);

/// Enable the Data Cache
/// @pre cortex::initialize::globals
void enable(void);
}    // namespace data
/// Contains operations on the Instruction Cache
namespace instruction {
/// Disable the Instruction Cache
void disable(void);
/// Enable the Instruction Cache
void enable(void);
}    // namespace instruction
}    // namespace cache

/// Used for debug, trapping, bad handlers, and to catch bad behavior.
/// @warning Paths which enter this function do not leave and will not run user applications.
[[noreturn]] void spinhalt(void);

}    // namespace cortex

#endif    // CORTEX_M_HPP_
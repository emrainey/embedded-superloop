#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

/// @file
/// The System Interface

#include <cstdint>
#include <cstddef>
#include <cinttypes>

// clang-format off
inline size_t operator""_Z( unsigned long long int value) {
    return size_t(value);
}
// clang-format on

#ifndef PRIz
#define PRIz "zu"
#endif

#if defined(UNITTEST)
#define ATTRIBUTE(x)
#else
#define ATTRIBUTE(x) __attribute__(x)
#endif

#include "configure.hpp"
#include "vectors.hpp"
#include "jarnax/SuperLoop.hpp"
#include "jarnax/Ticker.hpp"

/// The namespace of the system level functions
namespace jarnax {

/// An enumerated count of the various protected regions in the MPU
enum class ProtectedRegion : std::uint8_t {
    Code = 0U,              ///< The .text section
    Data = 1U,              ///< The section of RAM which contains the .bss and .data
    Stack = 2U,             ///< The Full Stack area
    MainStack = 3U,         ///< Just the Main Stack area (comes after Stack)
    ProcesStack = 4U,       ///< Just the Process Stack area (comes after Main)
    PrivilegedData = 5U,    ///< The section of RAM dedicated to the Privilege mode (comes after Data)
    Peripherals = 6U,       ///< Device memory mapped peripherals
    Backup = 7U,            ///< The backup RAM area (for low power mode), (must overlay Peripherals)
    System = 8U,            ///< The system processor memory map
};

/// The captured or computed value of the processor
extern std::uint32_t clock_frequency;

/// Indicates if the system was able to initialize correctly
extern bool is_system_initialized;

/// Indicates if the system was able to configure correctly
extern bool is_system_configured;

/// Indicates if the system was able to run BIST correctly.
extern bool is_system_functional;

// enum class Phase  {
//     Reset = 0U,
//     Initializing = 1U,
//     Configuring = 2U,
//     SelfTest = 3U,
//     Main = 4U,
// };

/// A namespace to cover the various types of initialization invoked from @see on_entry
namespace initialize {

/// Does system level (cortex specific) initialization such as FPU/MPU, Faults, etc.
void on_entry(void);

/// Fills the stack with a watermark
void watermark_stack(void);

/// Initializes the BSS Section
void zero_bss(void);

/// Loads the Data Section with Values
void load_data(void);

/// Calls the Static Constructors and Pre-initialized arrays
void static_constructors(void);

/// Calls the Static Destructors
void static_destructors(void);

/// Initializes global data for the system which were simple types
/// @pre zero_bss
/// @pre load_data
void simple_globals(void);

/// Initializes global data which had Class initialization
/// @pre class initializers
void class_globals(void);

}    // namespace initialize

/// Defines a type for generic functions.
using function = void (*)(void);

/// Jumps to the new location, reseting the stack and preventing a return.
[[noreturn]] void jump(void* stack, function func);

/// Configures the system beyond initialization.
/// Does system specific configuration such as
/// * configures clocks
/// * configures timers
/// * configures gpio
/// * configures watchdog
void configure(void);

/// Requests an external reset by emitting a signal from the processor.
[[noreturn]] void request_external_reset(void);

/// Used for debug, trapping, bad handlers, and to catch bad behavior.
/// @warning Paths which enter this function do not leave and will not run user applications.
[[noreturn]] void spinhalt(void);

/// Built In Self Test. Implemented to self-test the system during @see main.
/// @warning Called during boot, but can be called later as well.
/// @return True if bist passes. False otherwise.
bool bist(void);

/// @brief Primitive Printing Facility.
/// Supports %s, %d, %i, %u, %x, %b (binary), %f for float ONLY.
/// @param format The format string.
/// @param ... The variadic arguments.
void print(const char* format, ...) ATTRIBUTE((format(printf, 1, 2)));

/// The only normal while(true) loop allowed in the system is in "main"
[[noreturn]] void main(void);

/// Used to self-test on boot. The system will attempt to trigger each type of handler listed and collect the results.
struct BuiltInSelfTest final {
    /// Used to hold information about a specific test.
    struct Element final {
        bool is_testing{false};    //!< Indicates that the element is under test
        bool has_passed{false};    //!< Indicates that the test was able to pass
    };
    Element trigger_non_maskable_interrupt;     //!< Tests triggered the NMI
    Element trigger_hard_fault;                 //!< Tests triggering the hard-fault
    Element trigger_memory_management_fault;    //!< Tests triggering the memory management
                                                //!< (must happen *after* MPU is initialized)
    Element trigger_bus_fault;                  //!< Tests triggering the bus fault
    Element trigger_usage_fault;                //!< Tests triggering the usage fault
    Element trigger_supervisor_call;            //!< Test triggering the supervisor call
    Element trigger_pending_supervisor;         //!< Test triggering the pending supervisor
    Element trigger_system_tick;                //!< Test triggering the system tick
};

/// Used to self test on boot.
extern BuiltInSelfTest volatile built_in_self_test;

/// A known pattern used to detect correct stacking of the svc call @{
constexpr static std::uint32_t kBistArg0 = 0xFF'FF'FF'FFUL;
constexpr static std::uint32_t kBistArg1 = 0x11'11'11'11UL;
constexpr static std::uint32_t kBistArg2 = 0x22'22'22'22UL;
constexpr static std::uint32_t kBistArg3 = 0x33'33'33'33UL;
/// @}

namespace supervisor {

/// Raises from Privileged Low to High execution mode
/// @return The previous privilege level
cortex::modes::Privileged escalate(void);

/// Drops from Privileged High to Low execution mode
void deescalate(void);

/// Restore the previous privilege level
/// @param old The previous privilege level from @see escalate()
void restore(cortex::modes::Privileged old);

struct Marshal {
    /// The set of all Supervisor Calls (assembler limits to a 7 bit immediate field in assembly)
    enum class Calls : std::uint8_t {
        DisableDataCache = 1U,     //!< Disable Data Cache
        EnableDataCache = 2U,      //!< Enable Data Cache
        DisableInterrupts = 3U,    //!< Disable Interrupts
        EnableInterrupts = 4U,     //!< Enable Interrupts
        Reset = 5U,                //!< Resets the Core
        // Tick = 6U,              //!< Returns the system tick (from an elevated mode) @see
        BuiltInSelfTest = 0x7FU,    ///!< Built In Self Test (highest immediate value that can be used)
    };

    /// The call type
    Calls call;
    union Arguments {
        /// Used with @see Calls::BuiltInSelfTest
        struct BuiltInSelfTest {
            std::uint32_t arg0;
            std::uint32_t arg1;
            std::uint32_t arg2;
            std::uint32_t arg3;
        };
        // struct Tick {
        //     std::uint64_t* ptr;    ///< Pointer to the location to store the tick value.
        // };

        // ====================
        BuiltInSelfTest bist;
        thumb::Stacked generic;
        // ====================
    } type;
};

/// The Status value returned from a Supervisor Call. These are set to strange value to be visible in debuggers
enum class Status : std::uint32_t {
    Unknown = 0x00'00'00'00UL,
    Success = 0xBA'BE'BE'BAUL,
    Failure = 0xDE'AD'AD'DEUL,
};

/// Calls into the SVC with a known pattern to test call stacking
void bist();

/// Causes a reset
void reset(void);

/// Retrieves the system ticks
// jarnax::Ticks GetTicks(void);

}    // namespace supervisor
}    // namespace jarnax

/// The one global symbol used by the Linker from the code.
extern "C" void reset_entry(void) __attribute__((used));

#endif    // SYSTEM_HPP_
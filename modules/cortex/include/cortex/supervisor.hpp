#ifndef CORTEX_SUPERVISOR_HPP_
#define CORTEX_SUPERVISOR_HPP_

/// @file
/// Supervisor Mode Functions

#include "iso.hpp"
#include "cortex/core.hpp"
#include "cortex/thumb.hpp"

namespace cortex {

/// Functions in the system which are called by the supervisor or can be called in Supervisor Mode
namespace supervisor {

/// Raises from Privileged Low to High execution mode
/// @return The previous privilege level
cortex::modes::Privileged escalate(void);

/// Drops from Privileged High to Low execution mode
void deescalate(void);

/// @brief Returns the current state of the processor
cortex::modes::Privileged query(void);

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
        Reset = 5U,                //!< Resets the Core (does not return)
        Tick = 6U,                 //!< Returns the system tick
        Yield = 7U,                //!< Yield to the next task

        // INSERT NEW VALUES ABOVE HERE
        BuiltInSelfTest = 0x7FU,    ///!< Built In Self Test (highest immediate value that can be used)
        // NO VALUES BEYOND HERE
    };

    /// The call type
    Calls call;
    /// @brief  The union of argument types. All must be at most the size of the thumb::Stacked
    union Arguments {
        /// Used with @see Calls::BuiltInSelfTestP

        struct BuiltInSelfTest {
            std::uint32_t arg0;    ///< First Arg
            std::uint32_t arg1;    ///< Second Arg
            std::uint32_t arg2;    ///< Third Arg
            std::uint32_t arg3;    ///< Fourth Arg
        };
        // struct Tick {
        //     std::uint64_t* ptr;    ///< Pointer to the location to store the tick value.
        // };

        // ====================
        BuiltInSelfTest bist;    ///< Built in Self Test Args
        // Tick tick;               ///< The tick args
        thumb::Stacked generic;    ///< The stacked arguments
        // ====================
    } type;    ///< The union of argument types

    static_assert(sizeof(Arguments) == sizeof(thumb::Stacked), "The argument type must be less than or equal to the size of the union");
};

/// The Status value returned from calls invoked by the Supervisor Call.
/// These are set to strange value to be visible in debuggers.
enum class Status : std::uint32_t {
    Unknown = 0x00'00'00'00UL,
    Success = 0xBA'BE'BE'BAUL,
    Failure = 0xDE'AD'AD'DEUL,
};

/// Calls into the SVC with a known pattern to test call stacking
void bist();

/// Causes a processor reset, and does not return.
[[noreturn]] void reset(void);

}    // namespace supervisor

/// A shortcut method to know if the current mode is privileged
inline bool is_privileged(void) {
    return supervisor::query() == modes::Privileged::High;
}

}    // namespace cortex

#endif    // CORTEX_SUPERVISOR_HPP_
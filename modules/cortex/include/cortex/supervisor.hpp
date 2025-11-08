#ifndef CORTEX_SUPERVISOR_HPP_
#define CORTEX_SUPERVISOR_HPP_

/// @file
/// Supervisor Mode Functions

#include "cortex/bist.hpp"
#include "cortex/cache.hpp"
#include "cortex/clocks.hpp"
#include "cortex/thumb.hpp"
#include "cortex/types.hpp"
#include "iso.hpp"

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

/// @brief The structure used to marshal calls into the supervisor
struct Marshal {
    /// The set of all Supervisor Calls (assembler limits to a 7 bit immediate field in assembly)
    /// The Items in this list should not be individual functions, but rather groups of functions
    /// that can be further specified by arguments.
    enum class Calls : std::uint8_t {
        Unknown = 0U,             //!< Unknown Call (should return Unknown Status)
        DataCache = 1U,           //!< Data Cache, (args has further specifiers)
        InstructionCache = 2U,    //!< Instruction Cache, (args has further specifiers)
        Processor = 3U,           //!< Processor Functions (args has further specifiers)
        Nvic = 4U,                //!< NVIC Functions (args has further specifiers)
        Semihosting = 5U,         //!< Semihosting Functions (args has further specifiers)
        Swo = 6U,                 //!< SWO Functions (args has further specifiers)

        Yield = 0x7EU,            //!< Yield the processor (no args)
        // INSERT NEW VALUES ABOVE HERE

        BuiltInSelfTest = 0x7FU,    ///!< Built In Self Test (highest immediate value that can be used)
        // NO VALUES BEYOND HERE
    };

    /// The call type
    Calls call;
    /// @brief  The union of argument types. All must be at most the size of the thumb::Stacked
    union Arguments {
        /// Used with @see Calls::BuiltInSelfTest
        struct BuiltInSelfTest {
            std::uint32_t arg0;    ///< First Arg
            std::uint32_t arg1;    ///< Second Arg
            std::uint32_t arg2;    ///< Third Arg
            std::uint32_t arg3;    ///< Fourth Arg
        };
        /// Used with @see Calls::DataCache
        struct DataCache {
            /// Used by SVC calls the specify the operation in ARG1
            enum class Operations : std::uint8_t {
                Disable = 0U,                ///< Disable the Data Cache
                Enable = 1U,                 ///< Enable the Data Cache
                Invalidate = 2U,             ///< Invalidate the Data Cache
                InvalidateByAddress = 3U,    ///< Invalidate the Data Cache by Address (ARG2, ARG3)
                Clean = 4U,                  ///< Clean the Data Cache
                CleanByAddress = 5U,         ///< Clean the Data Cache by Address (ARG2, ARG3)
                Flush = 6U,                  ///< Flush (Clean and Invalidate) the Data Cache
                FlushByAddress = 7U,         ///< Flush (Clean and Invalidate) the Data Cache by Address (ARG2, ARG3)
            } operation;                     ///< The operation to perform
            std::uintptr_t address;          ///< The address to operate on
            std::size_t size;                ///< The size of the block to operate on
            std::uint32_t _;                 ///< Reserved for future use
        };
        /// Used with @see Calls::InstructionCache
        struct InstructionCache {
            /// Used by SVC calls the specify the operation in ARG1
            enum class Operations : std::uint8_t {
                Disable = 0U,                ///< Disable the Instruction Cache
                Enable = 1U,                 ///< Enable the Instruction Cache
                Invalidate = 2U,             ///< Invalidate the Instruction Cache
                InvalidateByAddress = 3U,    ///< Invalidate the Instruction Cache by Address
            } operation;                     ///< The operation to perform
            std::uintptr_t address;          ///< The address to operate on
            std::size_t size;                ///< The size of the block to operate on
            std::uint32_t _;                 ///< Reserved for future use
        };
        /// Used with @see Calls::Processor
        struct Processor {
            enum class Operations : std::uint32_t {
                DisableInterrupts = 0x0UL,              ///< Disable Interrupts, no args
                EnableInterrupts = 0x1UL,               ///< Enable Interrupts, no args
                GetTicks = 0x2UL,                       ///< Get the current tick count (arg1 has pointer to store ticks)
                GetCoreClockFrequency = 0x3UL,          ///< Get the current core clock frequency (arg1 has pointer to store frequency)
                GetSystemTickClockFrequency = 0x4UL,    ///< Get the current system tick clock frequency (arg1 has pointer to store frequency)
                SoftwareReset = 0x00DEAD00UL,           ///< Software Reset (does not return)
            } operation;                                ///< The operation to perform
            std::uint32_t arg1;                         ///< Additional argument
            std::uint32_t arg2;                         ///< Additional argument
            std::uint32_t arg3;                         ///< Additional argument
        };

        // MEMORY ====================
        BuiltInSelfTest bist;                  ///< Built in Self Test Args
        DataCache data_cache;                  ///< Data Cache args
        InstructionCache instruction_cache;    ///< Instruction Cache args
        Processor processor;                   ///< Processor args
        thumb::Stacked generic;                ///< The generic stacked arguments (used to load from stack)
        // MEMORY ====================
    } type;    ///< The union of argument types

    static_assert(sizeof(Arguments) == sizeof(thumb::Stacked), "The argument type must be less than or equal to the size of the union");
};

/// The Status value returned from calls invoked by the Supervisor Call.
/// These are set to strange value to be visible in debuggers.
enum class Status : std::uint32_t {
    Unknown = 0x00'00'00'00UL,
    Success = 0xBA'BE'BE'BAUL,
    Failure = 0xDE'AD'AD'DEUL,
    Missing = 0xFE'ED'ED'FEUL,
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

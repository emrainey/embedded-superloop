#ifndef CONFIGURATION_HPP_
#define CONFIGURATION_HPP_

/// @file
/// The Configuration of the Embedded SuperLoop system

#include <cstddef>
#include <cstdint>

#include "core/Units.hpp"

// The configuration only depends on the variant of the Cortex Microcontroller being used
#include "cortex/partnumber.hpp"

namespace cortex {

/// The number of cycles we'll spin at the reset entry point waiting for a debugger to attach before we do anything else. Set this to 0 to skip the
/// spin and boot immediately.
constexpr static std::uint32_t reset_entry_countdown_value{16'000U};    // at 32Khz, this is about 1/2 a second

/// When false, the boost up self tests will not run
constexpr static bool perform_boot_self_test{false};

/// Uses the linker script zeroing to clear all the memory at boot time
constexpr static bool use_zero_table{true};

/// Zeroes CCM at boot (if present)
constexpr static bool zero_ccm_at_boot{true};

/// Verifies the CCM is zeroed at boot (if present)
constexpr static bool verify_ccm_at_boot{true};

/// Zeroes ITCM at boot (if present)
constexpr static bool zero_itcm_at_boot{true};

/// Zeroes DTCM at boot (if present)
constexpr static bool zero_dtcm_at_boot{true};

/// Zeroes SRAM at boot (if present)
constexpr static bool zero_sram_at_boot{true};

/// Verifies the SRAM is zeroed at boot (if present)
constexpr static bool verify_sram_at_boot{true};

/// Enables access to the FPU at runtime.
constexpr static bool enable_access_to_fpu{true};

/// Configures the use of the default mpu configuration only (no additions from system)
constexpr static bool use_only_default_mpu_configuration{true};

/// Indicates if the system should run the preinitialization array
constexpr static bool has_preinitialization{true};

/// Indicates if the system should run the static constructors
constexpr static bool has_static_constructors{true};

/// Enables watermarking the stack at boot time
constexpr static bool use_stack_watermark{true};

/// The System Stack WaterMark. Typically a distinct Hex value which is noticeable in a debugger
/// and uncommon in usage. This is a hex palindrome so that it is visible in LE or BE.
constexpr static std::uint32_t stack_watermark = 0x55AAAA55;

/// Instructs the configuration to initialize the system clocks if they exist
constexpr static bool initialize_system_clocks{true};

/// @brief The number of Ticks in a second
constexpr static std::uint32_t ticks_per_second{128U};

/// Control SWO features
namespace swo {
/// The flag to control enabling the SWO and TPIU/ITM
constexpr static bool enable{true};
/// The desired SWO baudrate
constexpr static std::size_t baudrate{2'240'000U};
}    // namespace swo

/// When false, this will enable thread mode (or User Mode) with a separate stack, before calling the user application.
/// Some system level calls my then use the other stack and as such it needs to be sized appropriately.
/// When true, all code will run on in privileged mode on one stack.
constexpr static bool run_in_privileged_mode_only{true};

/// Enables the data and caches (if present)
constexpr static bool enable_data_cache{true};

/// Enables the instruction cache (if present)
constexpr static bool enable_instruction_cache{true};

/// Allow Low Privilege Access to Trigger Software Interrupts
constexpr static bool allow_unprivileged_software_trigger{false};

/// Allow returning to thread mode after an exception while exceptions are still pending.
constexpr static bool allow_thread_mode_exception_return{false};

/// Enable trapping of unaligned accesses into a Usage Fault.
/// @note Halfword and Word Acceases using LDM, STM, LDRD, and STRD will always fault when this is enabled.
constexpr static bool trap_unaligned_access{false};

/// Enable trapping of divide by zero operations into a Usage Fault.
/// @note This only applies to hardware divide instructions (SDIV and UDIV).When disabled, a value of zero is returned.
constexpr static bool trap_divide_by_zero{true};

/// Ignore Precise Data Access Faults in Negative Priority Levels. Only should be used to debug the system.
constexpr static bool ignore_precise_data_access_faults_in_negative_priority{false};

}    // namespace cortex

#endif    // CONFIGURATION_HPP_

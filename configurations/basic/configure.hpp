#ifndef CONFIGURATION_HPP_
#define CONFIGURATION_HPP_

/// @file
/// The Configuration of the Embedded SuperLoop system

#include <cstddef>
#include <cstdint>

#include "core/Units.hpp"

// The configuration only depends on the variant of the Cortex Microcontroller being used
#include "cortex/variant.hpp"

namespace cortex {

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

/// @brief Defines the system tick period value used to represent the passage of time in floats
constexpr static float tick_period{1.0F / cortex::ticks_per_second};

/// Control SWO features
namespace swo {
/// The flag to control enabling the SWO and TPIU/ITM
constexpr static bool enable{true};
/// The desired SWO baudrate
constexpr static std::size_t baudrate{2'240'000U};    // should be /75
}    // namespace swo

/// When false, this will enable thread mode (or User Mode) with a separate stack, before calling the user application.
/// Some system level calls my then use the other stack and as such it needs to be sized appropriately.
/// When true, all code will run on in privileged mode on one stack.
constexpr static bool run_in_privileged_mode_only{false};

}    // namespace cortex

#endif    // CONFIGURATION_HPP_

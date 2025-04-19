#ifndef CONFIGURATION_HPP_
#define CONFIGURATION_HPP_

/// @file
/// The Configuration of the Embedded SuperLoop system

#include <cstdint>
#include <cstddef>

#include "core/Units.hpp"

// things in the board can depend on the configuration above
#include "board.hpp"

namespace cortex {

/// When false, the boost up self tests will not run
constexpr static bool perform_boot_self_test{true};

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

/// Configures the use of the default mpu configuration only (no additions from system)
constexpr static bool use_only_default_mpu_configuration{true};

/// Defines the system tick value in the Cortex Tick Registers
constexpr static Hertz ticks_per_second{core::units::ticks_per_second.value()};

/// Defines the system tick period value used to represent the passage of time in floats
constexpr static float tick_period{1.0F / ticks_per_second.value()};

/// The System Stack WaterMark. Typically a distinct Hex value which is noticeable in a debugger
/// and uncommon in usage. This is a hex palindrome so that it is visible in LE or BE.
constexpr static std::uint32_t stack_watermark = 0x55AAAA55;

namespace address {
/// The Code for the System runs in Flash
constexpr static uintptr_t flash = ::vendor::address::flash;
/// The location where stack is stored
constexpr static uintptr_t stack = ::vendor::address::ccm;
/// The Backup RAM area
constexpr static uintptr_t backup = ::vendor::address::backup_sram;
}    // namespace address
namespace sizes {
/// The size of the code area
constexpr static std::uint32_t flash = ::vendor::sizes::flash;
/// The size of the stack area
constexpr static std::uint32_t stack = ::vendor::sizes::ccm;
/// The size of the backup area if present
constexpr static std::uint32_t backup = ::vendor::sizes::backup_sram;
namespace power2 {
/// The power of 2 of the size of the code area
constexpr static std::uint8_t flash = ::vendor::sizes::power2::flash;
/// The power of 2 of the size of the stack area
constexpr static std::uint8_t stack = polyfill::log2(cortex::sizes::stack);
/// The power of 2 of the size of the backup area if present
constexpr static std::uint8_t backup = ::vendor::sizes::power2::backup_sram;
}    // namespace power2

}    // namespace sizes

/// Control SWO features
namespace swo {
/// The flag to control enabling the SWO and TPIU/ITM
constexpr static bool enable{false};

/// The desired SWO baudrate
constexpr static std::size_t baudrate{50'000U};
}    // namespace swo

/// When false, this will enable thread mode (or User Mode) with a separate stack, before calling the user application.
/// When true, all code will run on in privileged mode on one stack.
constexpr static bool run_in_privileged_mode_only{false};

}    // namespace cortex

namespace jarnax {
namespace initialize {
/// Indicates if the system should run the preinitialization array
constexpr static bool has_preinitialization{true};
/// Indicates if the system should run the static constructors
constexpr static bool has_static_constructors{true};
}    // namespace initialize

/// Enables access to the FPU at runtime.
constexpr static bool enable_access_to_fpu{true};
}    // namespace jarnax

#endif    // CONFIGURATION_HPP_

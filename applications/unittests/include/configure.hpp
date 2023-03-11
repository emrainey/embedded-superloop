#ifndef CONFIGURATION_HPP_
#define CONFIGURATION_HPP_

#include <cstdint>
#include <cstddef>

#include "board.hpp"

namespace jarnax {

/// Enables access to the FPU at runtime.
constexpr static bool enable_access_to_fpu = true;

/// When false, this will enable thread mode (or User Mode) with a separate stack, before calling the user application.
/// When true, all code will run on in privileged mode on one stack.
constexpr static bool run_in_privileged_mode_only = false;

/// When false, the boost up self tests will not run
constexpr static bool perform_boot_self_test =
#if not defined(USE_BIST)
    false;
#else
    (USE_BIST == 1);
#endif

/// Defines the system tick value in the Cortex Tick Registers
constexpr static std::size_t ticks_per_second = 128U;

/// Defines the system tick period value used to represent the passage of time in floats
constexpr static float tick_period = 1.0F / ticks_per_second;

/// Control SWO features
namespace swo {
/// The flag to control enabling the SWO and TPIU/ITM
constexpr static bool enable = false;

/// The desired SWO baudrate
constexpr static std::size_t baudrate = 50'000U;
}    // namespace swo

/// Indicates the number of executable objects in the system
/// @todo make this statically determined at compile time via an initialized list?
constexpr static std::size_t num_executable_tasks = 4U;

/// Configures the use of the default mpu configuration only (no additions from system)
constexpr static bool use_only_default_mpu_configuration = true;

/// The System Stack WaterMark. Typically a distinct Hex value which is noticeable in a debugger
/// and uncommon in usage. This is a hex palindrome so that it is visible in LE or BE.
constexpr static std::uint32_t stack_watermark = 0x55AAAA55;

namespace address {
/// The Code for the System runs in Flash
constexpr static uintptr_t code = vendor::address::flash;
/// The location where stack is stored
constexpr static uintptr_t stack = vendor::address::ccm;
/// The SRAM is where it normally is
constexpr static uintptr_t sram = vendor::address::sram;
/// The Peripherals are where they normally are
constexpr static uintptr_t peripheral = cortex::address::peripheral;
/// The System is where it normally is
constexpr static uintptr_t system = cortex::address::system;
/// The Backup RAM area
constexpr static uintptr_t backup = vendor::address::backup_sram;
}    // namespace address
namespace sizes {
/// The size of the code area
constexpr static std::uint32_t code = vendor::sizes::flash;
/// The size of the stack area
constexpr static std::uint32_t stack = vendor::sizes::ccm;
/// The size of the SRAM area
constexpr static std::uint32_t sram = cortex::sizes::sram;
/// The size of the peripheral area
constexpr static std::uint32_t peripheral = cortex::sizes::peripheral;
/// The size of the system area
constexpr static std::uint32_t system = cortex::sizes::system;
/// The size of the backup area if present
constexpr static std::uint32_t backup = vendor::sizes::backup_sram;
namespace power2 {
/// The power of 2 of the size of the code area
constexpr static std::uint8_t code = vendor::sizes::power2::flash;
/// The power of 2 of the size of the SRAM area
constexpr static std::uint8_t sram = vendor::sizes::power2::sram;
/// The power of 2 of the size of the stack area
constexpr static std::uint8_t stack = iso::log2(jarnax::sizes::stack);
/// The power of 2 of the size of the peripheral area
constexpr static std::uint8_t peripheral = iso::log2(jarnax::sizes::peripheral);
/// The power of 2 of the size of the system area
constexpr static std::uint8_t system = iso::log2(jarnax::sizes::system);
/// The power of 2 of the size of the backup area if present
constexpr static std::uint8_t backup = vendor::sizes::power2::backup_sram;
}    // namespace power2

}    // namespace sizes

}    // namespace jarnax

#endif    // CONFIGURATION_HPP_

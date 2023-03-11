#ifndef LINKER_HPP_
#define LINKER_HPP_

/// @file
/// The exported symbols from the linker script and associated types

#include <cstdint>

extern std::uint32_t __ccm_end[];
extern std::uint32_t __ccm_beg[];
extern std::uint32_t __sram_end[];
extern std::uint32_t __sram_beg[];

/// Link Symbol of Start of Uninitialized Data
extern std::uint32_t __bss_start[];

/// Link Symbol of End of Uninitialized Data
extern std::uint32_t __bss_end[];

/// Link Symbol of Start of Initialized Data
extern std::uint32_t __data_start[];

/// Link Symbol of End of Initialized Data
extern std::uint32_t __data_end[];

/// Link Symbol of Load of Initialized Data
extern std::uint32_t __data_load[];

/// Linker Symbol of the Bottom of the Main Stack
extern std::uint32_t __main_stack_bottom[];

/// Linker Symbol of the Top of the Main Stack (one word past the end)
extern std::uint32_t __main_stack_top[];

/// Linker Symbol of the Ceiling of the Main Stack (last available word)
extern std::uint32_t __main_stack_ceiling[];

/// Linker Symbol of the Size of the Main Stack
extern std::uint32_t __main_stack_size[];

/// Linker Symbol of the Power of 2 Size of the Main Stack
extern std::uint32_t __main_stack_size_pow2[];

/// Linker Symbol of the Bottom of the Process Stack
extern std::uint32_t __process_stack_bottom[];

/// Linker Symbol of the Top of the Process Stack (one word past the end)
extern std::uint32_t __process_stack_top[];

/// Linker Symbol of the Ceiling of the Main Stack (last available word)
extern std::uint32_t __process_stack_ceiling[];

/// Linker Symbol of the Size of the Main Stack
extern std::uint32_t __process_stack_size[];

/// Linker Symbol of the Power of 2 Size of the Process Stack
extern std::uint32_t __process_stack_size_pow2[];

/// Linker Symbol of the Start of Privileged Data Section
extern std::uint32_t __privileged_data_start[];

/// Linker Symbol of the End of Privileged Data Section
extern std::uint32_t __privileged_data_end[];

/// Linker Symbol of the Size of Privileged Data Section
extern std::uint32_t __privileged_data_size[];

/// Linker Symbol of the Power of 2 Size of the Privileged Data Area
extern std::uint32_t __privileged_data_size_pow2[];

/// A function pointer to a constructor function
using constructor = void (*)(void);

/// A function pointer to a destructor function
using destructor = void (*)(void);

/// Link Symbol of Preinitialized Array Start
extern constructor __preinit_array_start[];

/// Link Symbol of Preinitialized Array End
extern constructor __preinit_array_end[];

/// Link Symbol of Initialized Array Start
extern constructor __init_array_start[];

/// Link Symbol of Initialized Array End
extern constructor __init_array_end[];

/// Link Symbol of Destructor Array Start
extern destructor __fini_array_start[];

/// Link Symbol of Destructor Array End
extern destructor __fini_array_end[];

#endif    // LINKER_HPP_
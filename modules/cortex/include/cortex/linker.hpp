#ifndef CORTEX_LINKER_HPP_
#define CORTEX_LINKER_HPP_

/// @file
/// The exported symbols from the linker script and associated types

#include <cstdint>

#if defined(UNITTEST)
/// Linker Symbol for the UnitTest
#define LINKER_TYPED_SYMBOL(symbol, type) extern type *symbol
#else
/// Linker Symbol for the On Target
#define LINKER_TYPED_SYMBOL(symbol, type) extern type symbol[]
#endif
/// Used to declare a Linker Symbol in C++ which does not have an explicit type
/// @note This typically is used to define the linked start and end of various sections in memory like Stack, or Heap
#define LINKER_SYMBOL(symbol) LINKER_TYPED_SYMBOL(symbol, std::uint32_t)

/// Link Symbol of the VectorTable
LINKER_SYMBOL(__vector_table_start);

/// Link Symbol of the End of the VectorTable
LINKER_SYMBOL(__vector_table_end);

/// Link Symbol of End of Coupled Memory
LINKER_SYMBOL(__ccm_end);

/// Link Symbol of Start of Coupled Memory
LINKER_SYMBOL(__ccm_beg);

/// Link Symbol of End of Instruction Tightly Coupled Memory
LINKER_SYMBOL(__itcm_end);

/// Link Symbol of Start of Instruction Tightly Coupled Memory
LINKER_SYMBOL(__itcm_beg);

/// Link Symbol of End of Data Tightly Coupled Memory
LINKER_SYMBOL(__dtcm_end);

/// Link Symbol of Start of Data Tightly Coupled Memory
LINKER_SYMBOL(__dtcm_beg);

/// Link Symbol of End of System RAM
LINKER_SYMBOL(__sram_end);

/// Link Symbol of Start of System RAM
LINKER_SYMBOL(__sram_beg);

/// Link Symbol of Start of Uninitialized Data
LINKER_SYMBOL(__bss_start);

/// Link Symbol of End of Uninitialized Data
LINKER_SYMBOL(__bss_end);

/// Link Symbol of Start of Initialized Data
LINKER_SYMBOL(__data_start);

/// Link Symbol of End of Initialized Data
LINKER_SYMBOL(__data_end);

/// Link Symbol of Load of Initialized Data
LINKER_SYMBOL(__data_load);

/// Linker Symbol of the Bottom of the Main Stack
LINKER_SYMBOL(__main_stack_bottom);

/// Linker Symbol of the Top of the Main Stack (one word past the end)
LINKER_SYMBOL(__main_stack_top);

/// Linker Symbol of the Ceiling of the Main Stack (last available word)
LINKER_SYMBOL(__main_stack_ceiling);

/// Linker Symbol of the Size of the Main Stack
LINKER_SYMBOL(__main_stack_size);

/// Linker Symbol of the Power of 2 Size of the Main Stack
LINKER_SYMBOL(__main_stack_size_pow2);

/// Linker Symbol of the Bottom of the Process Stack
LINKER_SYMBOL(__process_stack_bottom);

/// Linker Symbol of the Top of the Process Stack (one word past the end)
LINKER_SYMBOL(__process_stack_top);

/// Linker Symbol of the Ceiling of the Main Stack (last available word)
LINKER_SYMBOL(__process_stack_ceiling);

/// Linker Symbol of the Size of the Main Stack
LINKER_SYMBOL(__process_stack_size);

/// Linker Symbol of the Power of 2 Size of the Process Stack
LINKER_SYMBOL(__process_stack_size_pow2);

/// Linker Symbol of the Start of Privileged Data Section
LINKER_SYMBOL(__privileged_data_start);

/// Linker Symbol of the End of Privileged Data Section
LINKER_SYMBOL(__privileged_data_end);

/// Linker Symbol of the Size of Privileged Data Section
LINKER_SYMBOL(__privileged_data_size);

/// Linker Symbol of the Power of 2 Size of the Privileged Data Area
LINKER_SYMBOL(__privileged_data_size_pow2);

/// A function pointer to a constructor function
using constructor = void (*)(void);

/// A function pointer to a destructor function
using destructor = void (*)(void);

/// Link Symbol of Preinitialized Array Start
LINKER_TYPED_SYMBOL(__preinit_array_start, constructor);

/// Link Symbol of Preinitialized Array End
LINKER_TYPED_SYMBOL(__preinit_array_end, constructor);

/// Link Symbol of Initialized Array Start
LINKER_TYPED_SYMBOL(__init_array_start, constructor);

/// Link Symbol of Initialized Array End
LINKER_TYPED_SYMBOL(__init_array_end, constructor);

/// Link Symbol of Destructor Array Start
LINKER_TYPED_SYMBOL(__fini_array_start, destructor);

/// Link Symbol of Destructor Array End
LINKER_TYPED_SYMBOL(__fini_array_end, destructor);

#endif    // CORTEX_LINKER_HPP_
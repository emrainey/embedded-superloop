#ifndef CORTEX_LINKER_HPP_
#define CORTEX_LINKER_HPP_

/// @file
/// The exported symbols from the linker script and associated types

#include <core/Intervals.hpp>
#include <cortex/types.hpp>

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
LINKER_SYMBOL(__vector_table_limit);

/// Link Symbol of End of Coupled Memory
LINKER_SYMBOL(__ccm_limit);

/// Link Symbol of Start of Coupled Memory
LINKER_SYMBOL(__ccm_start);

/// Link Symbol of End of Instruction Tightly Coupled Memory
LINKER_SYMBOL(__itcm_limit);

/// Link Symbol of Start of Instruction Tightly Coupled Memory
LINKER_SYMBOL(__itcm_start);

/// Link Symbol of End of Data Tightly Coupled Memory
LINKER_SYMBOL(__dtcm_limit);

/// Link Symbol of Start of Data Tightly Coupled Memory
LINKER_SYMBOL(__dtcm_start);

/// Link Symbol of End of System RAM
LINKER_SYMBOL(__sram_limit);

/// Link Symbol of Start of System RAM
LINKER_SYMBOL(__sram_start);

/// Link Symbol of Start of Uninitialized Data
LINKER_SYMBOL(__static_data_start);

/// Link Symbol of End of Uninitialized Data
LINKER_SYMBOL(__static_data_limit);

/// Link Symbol of Start of Initialized Data
LINKER_SYMBOL(__const_static_data_start);

/// Link Symbol of End of Initialized Data
LINKER_SYMBOL(__const_static_data_limit);

/// Link Symbol of Load of Initialized Data
LINKER_SYMBOL(__const_static_data_load);

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
LINKER_SYMBOL(__privileged_data_limit);

/// Linker Symbol of the Size of Privileged Data Section
LINKER_SYMBOL(__privileged_data_size);

/// Linker Symbol of the Power of 2 Size of the Privileged Data Area
LINKER_SYMBOL(__privileged_data_size_pow2);

/// Link Symbol of Preinitialized Array Start
LINKER_TYPED_SYMBOL(__preinit_array_start, cortex::constructor);

/// Link Symbol of Preinitialized Array End
LINKER_TYPED_SYMBOL(__preinit_array_limit, cortex::constructor);

/// Link Symbol of Initialized Array Start
LINKER_TYPED_SYMBOL(__init_array_start, cortex::constructor);

/// Link Symbol of Initialized Array End
LINKER_TYPED_SYMBOL(__init_array_limit, cortex::constructor);

/// Link Symbol of Destructor Array Start
LINKER_TYPED_SYMBOL(__fini_array_start, cortex::destructor);

/// Link Symbol of Destructor Array End
LINKER_TYPED_SYMBOL(__fini_array_limit, cortex::destructor);

/// Link Symbol of the Begining of Flash
LINKER_SYMBOL(__cortex_flash_start);

/// Link Symbol of the End of Flash (past the last valid byte)
LINKER_SYMBOL(__cortex_flash_limit);

/// Link Symbol of the Size of Flash
LINKER_SYMBOL(__cortex_flash_size);

/// Link Symbol of the Power of 2 Size of Flash
LINKER_SYMBOL(__cortex_flash_pow2);

/// Link Symbol of the Start of the Stack
LINKER_SYMBOL(__cortex_stack_start);

/// Link Symbol of the End of the Stack (past the last valid byte)
LINKER_SYMBOL(__cortex_stack_limit);

/// Link Symbol of the Size of the Stack
LINKER_SYMBOL(__cortex_stack_size);

/// Link Symbol of the Power of 2 Size of the Stack
LINKER_SYMBOL(__cortex_stack_pow2);

/// Link Symbol of the Start of SRAM
LINKER_SYMBOL(__cortex_sram_start);

/// Link Symbol of the End of SRAM (past the last valid byte)
LINKER_SYMBOL(__cortex_sram_limit);

/// Link Symbol of the Size of SRAM
LINKER_SYMBOL(__cortex_sram_size);

/// Link Symbol of the Power of 2 Size of SRAM
LINKER_SYMBOL(__cortex_sram_pow2);

/// Link Symbol of the Start of SRAM1
LINKER_SYMBOL(__sram1_start);

/// Link Symbol of the End of SRAM1
LINKER_SYMBOL(__sram1_limit);

/// Link Symbol of the Start of SRAM2
LINKER_SYMBOL(__sram2_start);

/// Link Symbol of the End of SRAM2
LINKER_SYMBOL(__sram2_limit);

/// Link Symbol of the Start of SRAM3
LINKER_SYMBOL(__sram3_start);

/// Link Symbol of the End of SRAM3
LINKER_SYMBOL(__sram3_limit);

/// Link Symbol of the Start of SRAM4
LINKER_SYMBOL(__sram4_start);

/// Link Symbol of the End of SRAM4
LINKER_SYMBOL(__sram4_limit);

/// Link Symbol of the Start of System Private Peripherals Bus
LINKER_SYMBOL(__cortex_system_start);

/// Link Symbol of the End of System Private Peripherals Bus (past the last valid byte)
LINKER_SYMBOL(__cortex_system_limit);

/// Link Symbol of the Size of System Private Peripherals Bus
LINKER_SYMBOL(__cortex_system_size);

/// Link Symbol of the Power of 2 Size of System Private Peripherals Bus
LINKER_SYMBOL(__cortex_system_pow2);

/// Link Symbol of the Start of Peripheral Bus
LINKER_SYMBOL(__cortex_peripheral_start);

/// Link Symbol of the End of Peripheral Bus (past the last valid byte)
LINKER_SYMBOL(__cortex_peripheral_limit);

/// Link Symbol of the Size of Peripheral Bus
LINKER_SYMBOL(__cortex_peripheral_size);

/// Link Symbol of the Power of 2 Size of Peripheral Bus
LINKER_SYMBOL(__cortex_peripheral_pow2);

/// Link Symbol of the Start of Backup SRAM
LINKER_SYMBOL(__cortex_backup_start);

/// Link Symbol of the End of Backup SRAM (past the last valid byte)
LINKER_SYMBOL(__cortex_backup_limit);

/// Link Symbol of the Used Size of Backup SRAM
LINKER_SYMBOL(__cortex_backup_used);

/// Link Symbol of the Size of Backup SRAM
LINKER_SYMBOL(__cortex_backup_size);

/// Link Symbol of the Power of 2 Size of Backup SRAM
LINKER_SYMBOL(__cortex_backup_pow2);

/// Used to initialize memory to zero at boot without having to declare each type of memory separately
struct ZeroEntry {
    std::uintptr_t start;    ///< Starting address of memory region to zero
    std::uintptr_t limit;    ///< Ending address of memory region to zero
};

/// Linker Symbols for the Zero Initialization Table, Start
LINKER_TYPED_SYMBOL(__zero_table_start, ZeroEntry);

/// Linker Symbols for the Zero Initialization Table, Limit
LINKER_TYPED_SYMBOL(__zero_table_limit, ZeroEntry);

namespace cortex {
/// The Cortex Microcontroller processor memory regions
LINKER_TYPED_SYMBOL(sorted_memory_regions, core::Interval const);

/// Points to a LONG of the number of regions as defined in the linker scripts.
LINKER_TYPED_SYMBOL(sorted_region_count, std::uint32_t const);
}    // namespace cortex

#endif    // CORTEX_LINKER_HPP_

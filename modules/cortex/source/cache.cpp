#include "cortex/mcu.hpp"

namespace cortex {
namespace cache {

#if defined(CORTEX_M) and (CORTEX_M == 7)
namespace {
enum class DataCacheOp {
    Invalidate,
    Clean,
    Flush
};

static inline void perform_data_cache_op_setway(DataCacheOp op) {
    // Select Level 1 Data Cache in CSSELR (cache_size_selection)
    peripherals::system_control_block.cache_information.cache_size_selection.whole = 0U;
    thumb::data_synchronization_barrier();
    
    // Read CCSIDR (cache_size_id)
    std::uint32_t const ccsidr = peripherals::system_control_block.cache_information.cache_size_id.whole;
    
    // Extract sets, associativity (ways), and compute way_shift
    std::uint32_t const sets = (ccsidr >> 13U) & 0x7FFFU;
    std::uint32_t const ways = (ccsidr >> 3U) & 0x3FFU;
    std::uint32_t const way_shift = (ways == 0U) ? 0U : static_cast<std::uint32_t>(__builtin_clz(ways));
    
    for (std::uint32_t set = 0U; set <= sets; ++set) {
        for (std::uint32_t way = 0U; way <= ways; ++way) {
            std::uint32_t const set_way = (way << way_shift) | (set << 5U);
            switch (op) {
                case DataCacheOp::Invalidate:
                    peripherals::data_and_instruction_cache_control.invalidate_data_cache_by_setway = static_cast<std::uintptr_t>(set_way);
                    break;
                case DataCacheOp::Clean:
                    peripherals::data_and_instruction_cache_control.clean_data_cache_by_setway = static_cast<std::uintptr_t>(set_way);
                    break;
                case DataCacheOp::Flush:
                    peripherals::data_and_instruction_cache_control.clean_and_invalidate_data_cache_by_setway = static_cast<std::uintptr_t>(set_way);
                    break;
            }
        }
    }
}
} // namespace
#endif

namespace instruction {
void enable(void) {
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
#if defined(CORTEX_M) and (CORTEX_M == 7)
    // Invalidate the entire instruction cache
    peripherals::data_and_instruction_cache_control.invalidate_whole_instruction_cache = 0U;
#endif
    // Enable the instruction cache
    auto ccr = peripherals::system_control_block.configuration_control;
    ccr.parts.enable_instruction_cache = 1U;
    peripherals::system_control_block.configuration_control = ccr;
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
}

void disable(void) {
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
    auto ccr = peripherals::system_control_block.configuration_control;
    ccr.parts.enable_instruction_cache = 0U;
    peripherals::system_control_block.configuration_control = ccr;
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
}

void invalidate(void) {
    thumb::data_synchronization_barrier();
#if defined(CORTEX_M) and (CORTEX_M == 7)
    peripherals::data_and_instruction_cache_control.invalidate_whole_instruction_cache = 0U;
#endif
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
}

void invalidate(std::uintptr_t address, std::size_t size) {
    thumb::data_synchronization_barrier();
#if defined(CORTEX_M) and (CORTEX_M == 7)
    if (size > 0U) {
        constexpr std::uintptr_t line_size = 32U;
        std::uintptr_t const start = address & ~(line_size - 1U);
        std::uintptr_t const end = address + size;
        for (std::uintptr_t addr = start; addr < end; addr += line_size) {
            peripherals::data_and_instruction_cache_control.invalidate_instruction_cache_by_address = addr;
        }
    }
#else
    static_cast<void>(address);
    static_cast<void>(size);
#endif
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
}
} // namespace instruction

namespace data {
void invalidate(void) {
    thumb::data_synchronization_barrier();
#if defined(CORTEX_M) and (CORTEX_M == 7)
    perform_data_cache_op_setway(DataCacheOp::Invalidate);
#endif
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
}

void invalidate(std::uintptr_t address, std::size_t size) {
    thumb::data_synchronization_barrier();
#if defined(CORTEX_M) and (CORTEX_M == 7)
    if (size > 0U) {
        constexpr std::uintptr_t line_size = 32U;
        std::uintptr_t const start = address & ~(line_size - 1U);
        std::uintptr_t const end = address + size;
        for (std::uintptr_t addr = start; addr < end; addr += line_size) {
            peripherals::data_and_instruction_cache_control.invalidate_data_cache_by_address = addr;
        }
    }
#else
    static_cast<void>(address);
    static_cast<void>(size);
#endif
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
}

void clean(void) {
    thumb::data_synchronization_barrier();
#if defined(CORTEX_M) and (CORTEX_M == 7)
    perform_data_cache_op_setway(DataCacheOp::Clean);
#endif
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
}

void clean(std::uintptr_t address, std::size_t size) {
    thumb::data_synchronization_barrier();
#if defined(CORTEX_M) and (CORTEX_M == 7)
    if (size > 0U) {
        constexpr std::uintptr_t line_size = 32U;
        std::uintptr_t const start = address & ~(line_size - 1U);
        std::uintptr_t const end = address + size;
        for (std::uintptr_t addr = start; addr < end; addr += line_size) {
            peripherals::data_and_instruction_cache_control.clean_data_cache_to_coherency_by_address = addr;
        }
    }
#else
    static_cast<void>(address);
    static_cast<void>(size);
#endif
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
}

void flush(void) {
    thumb::data_synchronization_barrier();
#if defined(CORTEX_M) and (CORTEX_M == 7)
    perform_data_cache_op_setway(DataCacheOp::Flush);
#endif
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
}

void flush(std::uintptr_t address, std::size_t size) {
    thumb::data_synchronization_barrier();
#if defined(CORTEX_M) and (CORTEX_M == 7)
    if (size > 0U) {
        constexpr std::uintptr_t line_size = 32U;
        std::uintptr_t const start = address & ~(line_size - 1U);
        std::uintptr_t const end = address + size;
        for (std::uintptr_t addr = start; addr < end; addr += line_size) {
            peripherals::data_and_instruction_cache_control.clean_and_invalidate_data_cache_by_address = addr;
        }
    }
#else
    static_cast<void>(address);
    static_cast<void>(size);
#endif
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
}

void disable(void) {
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
#if defined(CORTEX_M) and (CORTEX_M == 7)
    // Clean and invalidate D-Cache before disabling
    flush();
#endif
    auto ccr = peripherals::system_control_block.configuration_control;
    ccr.parts.enable_data_cache = 0U;
    peripherals::system_control_block.configuration_control = ccr;
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
}

void enable(void) {
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
#if defined(CORTEX_M) and (CORTEX_M == 7)
    // Invalidate D-Cache before enabling
    invalidate();
#endif
    auto ccr = peripherals::system_control_block.configuration_control;
    ccr.parts.enable_data_cache = 1U;
    peripherals::system_control_block.configuration_control = ccr;
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
}
} // namespace data

} // namespace cache
} // namespace cortex

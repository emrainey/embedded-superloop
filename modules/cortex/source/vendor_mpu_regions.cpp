#include "configure.hpp"
#include "cortex/initialize.hpp"
#include "cortex/linker.hpp"

namespace cortex {
namespace initialize {

std::size_t vendor_mpu_regions(MpuRegionConfiguration* out_regions, std::size_t max_regions) {
    std::size_t count = 0U;

#if defined(STM32H753ZI) and (STM32H753ZI == 1)
    constexpr std::uint8_t kSram1Region = 9U;
    constexpr std::uint8_t kSram2Region = 10U;
    constexpr std::uint8_t kSram3Region = 11U;
    constexpr std::uint8_t kSram4Region = 12U;

    std::uintptr_t const starts[4] = {
        reinterpret_cast<std::uintptr_t>(__sram1_start),
        reinterpret_cast<std::uintptr_t>(__sram2_start),
        reinterpret_cast<std::uintptr_t>(__sram3_start),
        reinterpret_cast<std::uintptr_t>(__sram4_start),
    };
    std::uintptr_t const limits[4] = {
        reinterpret_cast<std::uintptr_t>(__sram1_limit),
        reinterpret_cast<std::uintptr_t>(__sram2_limit),
        reinterpret_cast<std::uintptr_t>(__sram3_limit),
        reinterpret_cast<std::uintptr_t>(__sram4_limit),
    };
    std::uint8_t const region_numbers[4] = {kSram1Region, kSram2Region, kSram3Region, kSram4Region};

    for (std::size_t idx = 0U; idx < 4U; idx++) {
        std::uint32_t const size = static_cast<std::uint32_t>(limits[idx] - starts[idx]);
        if (size == 0U) {
            continue;
        }
        if (count < max_regions) {
            out_regions[count].region_number = region_numbers[idx];
            out_regions[count].base_address = starts[idx];
            out_regions[count].size_bytes = size;
            out_regions[count].attribute = peripherals::MemoryProtectionUnit::Attribute::NormalNonCacheableSingle;
            out_regions[count].permissions = peripherals::MemoryProtectionUnit::Permissions::RW_Priv_RW_User;
            out_regions[count].execute_never = true;
        }
        count++;
    }
#else
    static_cast<void>(out_regions);
    static_cast<void>(max_regions);
#endif

    return count;
}

}    // namespace initialize
}    // namespace cortex

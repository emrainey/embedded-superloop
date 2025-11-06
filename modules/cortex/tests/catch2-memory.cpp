// #define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "cortex/mcu.hpp"

#include <iostream>

namespace cortex {
core::Interval const memory_regions[] = {
    {0x20000000, 0x2FFF'FFFF},
    {0x40000000, 0x4FFF'FFFF},
    {0x60000000, 0x6FFF'FFFF},
    {0x80000000, 0x8FFF'FFFF},
    {0xE0000000, 0xEFFF'FFFF},
};
std::uint32_t const regions_count = dimof(memory_regions);

// for some reason, which is likely to be the old "extern int[] is not extern int *"
// issue, we have to export as pointers to get the linking to work and for the &
// of the count to work on host.
core::Interval const* sorted_memory_regions = &memory_regions[0];
std::uint32_t const* sorted_region_count = &regions_count;
}    // namespace cortex

TEST_CASE("Memory") {
    std::cout << "sorted_memory_regions " << cortex::sorted_memory_regions << " count:" << cortex::sorted_region_count[0] << std::endl;
    for (size_t i = 0; i < cortex::regions_count; i++) {
        std::cout << cortex::sorted_memory_regions[i] << std::endl;
    }
    SECTION("Address Checks") {
        // REQUIRE(cortex::IsValidAddress(cortex::));
        REQUIRE(cortex::IsValidAddress(0x20000000));
        REQUIRE(cortex::IsValidAddress(0x40000000));
        REQUIRE(cortex::IsValidAddress(0x60000000));
        REQUIRE(cortex::IsValidAddress(0x80000000));
        REQUIRE(cortex::IsValidAddress(0xE0000000));
        REQUIRE_FALSE(cortex::IsValidAddress(0x10000000));
        REQUIRE_FALSE(cortex::IsValidAddress(0x30000000));
        REQUIRE_FALSE(cortex::IsValidAddress(0x50000000));
        REQUIRE_FALSE(cortex::IsValidAddress(0x70000000));
        REQUIRE_FALSE(cortex::IsValidAddress(0x90000000));
        REQUIRE_FALSE(cortex::IsValidAddress(0xB0000000));
        REQUIRE_FALSE(cortex::IsValidAddress(0xD0000000));
        REQUIRE_FALSE(cortex::IsValidAddress(0xF0000000));
    }
}

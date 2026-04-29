// #define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "core/BoundsChecker.hpp"

#include <iostream>

core::Interval const test_memory_regions[] = {
    {0x20000000, 0x2FFF'FFFF},
    {0x40000000, 0x4FFF'FFFF},
    {0x60000000, 0x6FFF'FFFF},
    {0x80000000, 0x8FFF'FFFF},
    {0xE0000000, 0xEFFF'FFFF},
};
std::uint32_t const test_regions_count = dimof(test_memory_regions);

TEST_CASE("Boundary Checker") {
    core::BoundsChecker checker{test_memory_regions, test_regions_count};
    std::cout << "test_memory_regions " << test_memory_regions << " count:" << test_regions_count << std::endl;
    for (size_t i = 0; i < test_regions_count; i++) {
        std::cout << test_memory_regions[i] << std::endl;
    }
    SECTION("Address Checks") {
        REQUIRE_FALSE(checker.IsValidAddress(0x00000000));
        REQUIRE(checker.IsValidAddress(0x20000000));
        REQUIRE(checker.IsValidAddress(0x40000000));
        REQUIRE(checker.IsValidAddress(0x60000000));
        REQUIRE(checker.IsValidAddress(0x80000000));
        REQUIRE(checker.IsValidAddress(0xE0000000));
        REQUIRE_FALSE(checker.IsValidAddress(0x10000000));
        REQUIRE_FALSE(checker.IsValidAddress(0x30000000));
        REQUIRE_FALSE(checker.IsValidAddress(0x50000000));
        REQUIRE_FALSE(checker.IsValidAddress(0x70000000));
        REQUIRE_FALSE(checker.IsValidAddress(0x90000000));
        REQUIRE_FALSE(checker.IsValidAddress(0xB0000000));
        REQUIRE_FALSE(checker.IsValidAddress(0xD0000000));
        REQUIRE_FALSE(checker.IsValidAddress(0xF0000000));
    }
}

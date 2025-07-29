// #define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "cortex/mcu.hpp"

#include <iostream>

TEST_CASE("Memory") {
    std::cout << "Memory Regions: " << std::hex << cortex::sorted_memory_regions << std::endl;

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
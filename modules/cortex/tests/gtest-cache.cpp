#include <gtest/gtest.h>
#include "cortex/mcu.hpp"
#include "jarnax/TestContext.hpp"

class CacheTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Clear all mock registers before each test
        cortex::peripherals::system_control_block.configuration_control.whole = 0U;
        cortex::peripherals::system_control_block.cache_information.cache_size_id.whole = 0U;
        cortex::peripherals::system_control_block.cache_information.cache_size_selection.whole = 0xFFFFFFFFU;
        
        cortex::peripherals::data_and_instruction_cache_control.invalidate_whole_instruction_cache = 0xFFFFFFFFU;
        cortex::peripherals::data_and_instruction_cache_control.invalidate_instruction_cache_by_address = 0U;
        cortex::peripherals::data_and_instruction_cache_control.invalidate_data_cache_by_address = 0U;
        cortex::peripherals::data_and_instruction_cache_control.invalidate_data_cache_by_setway = 0U;
        cortex::peripherals::data_and_instruction_cache_control.clean_data_cache_to_unity_by_address = 0U;
        cortex::peripherals::data_and_instruction_cache_control.clean_data_cache_to_coherency_by_address = 0U;
        cortex::peripherals::data_and_instruction_cache_control.clean_data_cache_by_setway = 0U;
        cortex::peripherals::data_and_instruction_cache_control.clean_and_invalidate_data_cache_by_address = 0U;
        cortex::peripherals::data_and_instruction_cache_control.clean_and_invalidate_data_cache_by_setway = 0U;
    }
};

TEST_F(CacheTest, InstructionCacheEnableDisable) {
#if defined(CORTEX_M) and (CORTEX_M == 7)
    // Enable Instruction Cache
    cortex::cache::instruction::enable();
    EXPECT_EQ(static_cast<std::uint32_t>(cortex::peripherals::system_control_block.configuration_control.parts.enable_instruction_cache), 1U);
    EXPECT_EQ(cortex::peripherals::data_and_instruction_cache_control.invalidate_whole_instruction_cache, 0U);

    // Disable Instruction Cache
    cortex::cache::instruction::disable();
    EXPECT_EQ(static_cast<std::uint32_t>(cortex::peripherals::system_control_block.configuration_control.parts.enable_instruction_cache), 0U);
#endif
}

TEST_F(CacheTest, InstructionCacheInvalidate) {
#if defined(CORTEX_M) and (CORTEX_M == 7)
    cortex::cache::instruction::invalidate();
    EXPECT_EQ(cortex::peripherals::data_and_instruction_cache_control.invalidate_whole_instruction_cache, 0U);
#endif
}

TEST_F(CacheTest, InstructionCacheInvalidateRange) {
#if defined(CORTEX_M) and (CORTEX_M == 7)
    // Invalidate 64 bytes starting at 0x08001004
    // Aligned start = 0x08001000
    // Lines: 0x08001000, 0x08001020
    cortex::cache::instruction::invalidate(0x08001004, 60);
    EXPECT_EQ(cortex::peripherals::data_and_instruction_cache_control.invalidate_instruction_cache_by_address, 0x08001020U);
#endif
}

TEST_F(CacheTest, DataCacheEnableDisable) {
#if defined(CORTEX_M) and (CORTEX_M == 7)
    // Mock CCSIDR for L1 D-Cache: 16KB, 4-way, 32-byte line size (sets = 128)
    // line_size = 1 (8 words/32 bytes)
    // associativity = 3 (4 ways)
    // number_of_sets = 127 (128 sets)
    cortex::peripherals::system_control_block.cache_information.cache_size_id.whole = (127U << 13U) | (3U << 3U) | 1U;

    // Enable
    cortex::cache::data::enable();
    EXPECT_EQ(static_cast<std::uint32_t>(cortex::peripherals::system_control_block.configuration_control.parts.enable_data_cache), 1U);
    // On enable, it should invalidate the whole cache first (last written set/way = 0xC0000FE0)
    EXPECT_EQ(cortex::peripherals::data_and_instruction_cache_control.invalidate_data_cache_by_setway, 0xC0000FE0U);

    // Reset register values
    cortex::peripherals::data_and_instruction_cache_control.clean_and_invalidate_data_cache_by_setway = 0U;

    // Disable
    cortex::cache::data::disable();
    EXPECT_EQ(static_cast<std::uint32_t>(cortex::peripherals::system_control_block.configuration_control.parts.enable_data_cache), 0U);
    // On disable, it should flush (clean and invalidate) the whole cache first (last written set/way = 0xC0000FE0)
    EXPECT_EQ(cortex::peripherals::data_and_instruction_cache_control.clean_and_invalidate_data_cache_by_setway, 0xC0000FE0U);
#endif
}

TEST_F(CacheTest, DataCacheMaintenanceSetWay) {
#if defined(CORTEX_M) and (CORTEX_M == 7)
    // Mock CCSIDR: 16KB, 4-way, 32-byte line size
    cortex::peripherals::system_control_block.cache_information.cache_size_id.whole = (127U << 13U) | (3U << 3U) | 1U;

    // Invalidate
    cortex::cache::data::invalidate();
    EXPECT_EQ(cortex::peripherals::system_control_block.cache_information.cache_size_selection.whole, 0U); // L1 D-Cache selected
    EXPECT_EQ(cortex::peripherals::data_and_instruction_cache_control.invalidate_data_cache_by_setway, 0xC0000FE0U);

    // Clean
    cortex::cache::data::clean();
    EXPECT_EQ(cortex::peripherals::data_and_instruction_cache_control.clean_data_cache_by_setway, 0xC0000FE0U);

    // Flush
    cortex::cache::data::flush();
    EXPECT_EQ(cortex::peripherals::data_and_instruction_cache_control.clean_and_invalidate_data_cache_by_setway, 0xC0000FE0U);
#endif
}

TEST_F(CacheTest, DataCacheRangeOperations) {
#if defined(CORTEX_M) and (CORTEX_M == 7)
    // Range invalidate: 100 bytes starting at 0x24000010
    // Aligned start = 0x24000000
    // end = 0x24000010 + 100 = 0x24000074
    // Lines: 0x24000000, 0x24000020, 0x24000040, 0x24000060
    cortex::cache::data::invalidate(0x24000010, 100);
    EXPECT_EQ(cortex::peripherals::data_and_instruction_cache_control.invalidate_data_cache_by_address, 0x24000060U);

    // Range clean
    cortex::cache::data::clean(0x24000010, 100);
    EXPECT_EQ(cortex::peripherals::data_and_instruction_cache_control.clean_data_cache_to_coherency_by_address, 0x24000060U);

    // Range flush
    cortex::cache::data::flush(0x24000010, 100);
    EXPECT_EQ(cortex::peripherals::data_and_instruction_cache_control.clean_and_invalidate_data_cache_by_address, 0x24000060U);
#endif
}
